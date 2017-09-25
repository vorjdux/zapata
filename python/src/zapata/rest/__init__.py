import zpt
import re

PERFORMATIVES = ['get', 'post', 'put', 'patch', 'delete', 'head']
PARAM_PATTERN = re.compile(r'(\{[^\}]+\})')
VARIABLE_PATTERN = re.compile(r'\{(?P<variable>[^\}:]+):?(?P<type>[^\}:]+)?:?(?P<extra>[^\}]+)?\}')

class RestHandler(object):

    def __init__(self):
        self.resource_topic = None
        self.datum_topic = None
        self.datum_topic_params = None
        self.allowed_performatives = PERFORMATIVES
        self.unauthorized_status = 401
        self.unauthorized_code = 1019
        self.unauthorized_text = 'unauthorized access to this resource'

    def __getattribute__(self, name):

        try:
            return object.__getattribute__(self, name)
        except Exception as e:

            if name in self.allowed_performatives:
                return self.dispatch
            elif name in PERFORMATIVES:
                return self.performative_not_accepted
            elif name in ['{}_callback'.format(performative) for performative in self.allowed_performatives]:
                return RestHandler.default_callback

        super(RestHandler, self).__getattribute__(name)

    def __setattribute__(self, name, value):

        if name == 'allowed_performatives':
            return [performative for performative in self.__allowed_performatives if performative in PERFORMATIVES]

        super(RestHandler, self).__setattribute__(name, value)
        
    def authorize(self, performative, topic, envelope, context):

        identity = zpt.authorize(self.resource_topic, envelope)
        
        if not identity:
            return RestHandler.reply(envelope, status=self.unauthorized_status, payload={
                'code': self.unauthorized_code,
                'text': self.unauthorized_text
            })

        return identity

    @staticmethod
    def default_callback(performative, topic, reply, context):
        return zpt.reply(context, reply)

    def path_discover(self, template_path, original_path, endpoint):

        template_path_parts = template_path.split('/')
        original_path_parts = original_path.split('/')

        if len(template_path_parts) != len(original_path_parts):
            raise Exception('The template topic and topic pattern received doesn\'t match.')

        groups = PARAM_PATTERN.findall(template_path)
        params = {}

        for group in groups:
            params[re.sub(r'[\{\}]', '', group)] = original_path_parts[template_path_parts.index(group)]

        return (endpoint.format(**params), params)

    def variables_resolver(self, _object, _variables):

        _object_type = type(_object)

        if _object_type is str:
            return re.sub(VARIABLE_PATTERN, r'{\1}', _object).format(**_variables)
            
        elif _object_type is dict:
            for key, value in _object.items():
                _object[key] = self.variables_resolver(value, _variables)
                                 
        elif _object_type is list:
            for item in _object:
                item = self.variables_resolver(item, _variables)

        return _object

    def variables_extractor(self, _object, result={}):

        _object_type = type(_object)

        if _object_type is str:
            
            variables = {}
            
            for item in re.findall(VARIABLE_PATTERN, _object):

                _name, _type, _extra = item
                variables.update({_name: '{_type}|{_extra}'.format(
                    _type=_type if _type else 'string',
                    _extra=_extra if _extra else 'required'
                )})
                
            return variables
                                 
        elif _object_type is dict:

            for key, value in _object.items():
                 result.update(self.variables_extractor(value, result=result))
                                 
        elif _object_type is list:
                                 
            for item in _object:
                result.update(self.variables_extractor(item, result=result))

        return result

    def performative_not_accepted(self, performative, topic, envelope, context=None):
        return RestHandler.reply(envelope, status=405, payload={
            'code': 1300,
            'text': 'Performative is not accepted for the given resource'
        })

    def dispatch(self, performative, topic, envelope, context=None):

        if self.datum_topic is None:
            return self.performative_not_accepted(performative, topic, envelope, context)
    
        identity = self.authorize(performative, topic, envelope, context)

        if not identity:
            return # cancel the dispatch

        endpoint, variables = self.path_discover(self.resource_topic, topic, self.datum_topic)
        extra_params = self.variables_resolver(self.datum_topic_params, variables)

        params = zpt.merge(envelope.get('params'), extra_params) if envelope.get('params') else extra_params
        payload = zpt.merge(envelope.get('payload'), extra_params) if envelope.get('payload') else extra_params

        return self.datum_request(performative, endpoint, envelope, identity, params=params, payload=payload)

    def datum_request(self, performative, endpoint, envelope, identity, params = None, payload = None, callback = None):
        return zpt.route(
            performative,
            endpoint,
            {
                'headers': zpt.auth_headers(identity),
                'params': params, # TODO: remove the if condition after merge function is working with a nil object
                'payload': payload # TODO: remove the if condition after merge function is working with a nil object
            },
            {'context': envelope},
            getattr(self, '{}_callback'.format(performative)) if not callback else callback
        )

    @staticmethod
    def reply(envelope, **kwargs):
        return zpt.reply(envelope, kwargs)


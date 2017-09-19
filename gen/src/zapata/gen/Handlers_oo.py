import zpt
from zpt.rest import RestHandler

class $[resource.handler.class.name](RestHandler) :

    def __init__(self):
        super($[resource.handler.class.name], self).__init__()
        self.base_topic = '$[resource.topic.regex]'
        $[resource.proxy.enpoint]
        self.methods_allowed = $[resource.allowed.performatives]

        
handler = $[resource.handler.class.name]()
zpt.on("$[resource.topic.regex]", handler, {'http': True, '0mq': True, 'amqp': True})

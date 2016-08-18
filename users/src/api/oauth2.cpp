/*
                                         ._wwwmQQWQQQmywa,.                                         
                                       syQQ8TY1vlllll1YT$QQ/                                        
                                      jQQEvvvvvvvvvvvvngmQQ[                                        
                                       $QEvnvnvnnnvnnnUQQQQQ,                                       
                             ._ssaaaaaamQmwgwqoonnnonnnnnnQQ6                                       
                    ._aaaZ$WmQmmwmwmmmdgm#WhmUQ@VWQggpno2odQQL                                      
               .sayWQQW#WBWmBmmmmBBmmmWBBWmWWmQmWS$ETWQmpoS$QQ,                                     
            _awW#mmmmmmmmmmmmBmWmmmBmmmmmmmmmmmBWWWmZ4WWQmS2QWm                                     
          .jm##mmmmmmmmmmmmmmmm##mmmmmmmmmmmmmmm##WWQWwmQQZXdQQL                                    
      _aw#m#######################################ZWQQwVQQmXZ#QQ/                                   
    .wW#Z#Z##Z#Z#Z#Z#UU#Z##Z#UZ#Z#Z#Z#Z#Z#Z#Z#Z#ZUZ#QQ@VQQQmZZQQm                                   
   _QWZZ#ZZZZZZ#ZZZ#ZZZZZZZZZZUZZZUZZZZZZZZZZZZZZZUZQWQ@oQQQm##WQc                                  
  <QWZZZZXZZZZZZXZZZXZZZZZZZZZZXZZZXZZZZZZZZZZZZZZZXZQWQQoQQQQm#QQ,                                 
 _QQXXXXXXZXXZXXXZXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX$QQQmdQQQQWQ6                                 
 mQ#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXSdWWQmm#WQQQQc                           awaa,
)QQXSSSSSSS2X2SSS2SS2SS2SS2SS2SS2SS2SS2S2S2S2S2S2S2S22S22dWQQQg#$WQQQwaa.                  ._amQWWQQ
jQBo2222222222So2222222222222222222222222222222222222222SooXUQQQQyBQWQWWQQQwaaaaaaaaaaawmQWHBmQQQQQE
mQ#o222o2o2222o222o222o222o22o22o2o2o2o2o2o2o2o2o2o2o2oooo2onoXUWQQWmWQQQQQQBHUBUUUUUUXSS2SSqQQQQQW'
QQEooooooooooooooooooooooooooooooooooooooooooooooooooooooooooonnnXVWQQQQQQQQQQmmqXXXXSXXmmmQWQQQQQ^ 
WQmnnnonononnnnnnnnnnnnnnnnnnnnnogmpnnnnnnnnnnnnnnnnnnnnnnnnnnnnnvnvXVQWQQQQQQQWQQQQQQQQWWWWQQQQ@'  
3QQvnnvnnvnnvnnvnnvnnvnnvnnvnnvndQQQpvnvnnvnnvnnvnvnvnvvnvnvvnvvvnvvvvvXYVVHUHHBHHVHHVVVHWQQQQQY    
)WQpvvvvvvvvvvvvvvvvvvvvvvvvvvvvmQQQWguvvvvvvnnuwyggggmQQWQQmmgwvvvvvvvIvvvIIvIvIIvIIvqmQQQQQY`     
 4QQplvvvvvvvvvvvvvvvvvvvvvvvvomQQQQQQQQQQQQQQQQQQQQQQQQWWWWQWQQQmgggyyyyyyyyyyyymmQQQQQQQD!        
  $QWpiIIlIlIlIlIlIowwywymmQWQQQQQQ$QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWQQQQQWQWQQWQQWQQQ@T??`          
   4QQgzlllIllllqmQQQQQWQQQQQQQQQQQ-QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ/^"""""""^~-                   
    "$QQmuIllIlqWWQQQQQQQQQQQQQQQQE )WQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWm,                             
      "9QQQmyuumQQQQQQQQQQQQQQQQQQ'  "$QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQm                             
         "?HWQQQQQQQQQQQQQQQQQQWD'     ??WWWWWWWWWWWBBUHHVTTTV$QWQQQQQQL                            
              -QQWP???????!!""~                                 -9WQQQQQ,                           
               QW[                                                -$QQQQL                           
               $W.                                                 -QWQQQ/                          
                                                                    -^^^"~                          

The MIT License (MIT)

Copyright (c) 2014 n@zgul <naazgull@dfz.pt>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <zapata/rest.h>
#include <zapata/redis.h>
#include <zapata/users.h>
#include <ctime>
#include <memory>

zpt::authenticator::OAuth2::OAuth2(zpt::JSONPtr _options) : __options(_options) {
}

zpt::authenticator::OAuth2::~OAuth2() {
}

zpt::JSONPtr zpt::authenticator::OAuth2::options() {
	return this->__options;
}

std::string zpt::authenticator::OAuth2::name() {
	return "oauth2.0";
}

zpt::JSONPtr zpt::authenticator::OAuth2::authorize(zpt::ev::Performative _performative, zpt::JSONPtr _envelope, zpt::EventEmitterPtr _emitter) {
	assertz(
		_envelope[ZPT_PAYLOAD]->ok() &&
		_envelope[ZPT_PAYLOAD]["response_type"]->ok(),
		"required fields: 'response_type'", 412, 0);

	std::string _response_type((std::string) _envelope[ZPT_PAYLOAD]["response_type"]);
	zpt::redis::Client* _db = (zpt::redis::Client*) _emitter->get_kb("redis.oauth").get();

	if (_response_type == "code") {
		assertz(
			_envelope[ZPT_PAYLOAD]->ok() &&
			_envelope[ZPT_PAYLOAD]["client_id"]->ok() &&
			_envelope[ZPT_PAYLOAD]["redirect_uri"]->ok(),
			"required fields: 'client_id' & 'redirect_uri'", 412, 0);

		if (!_envelope["headers"]["Cookie"]->ok()) {
			std::string _state(std::string("scope=") + (_envelope[ZPT_PAYLOAD]["scope"]->ok() ? _envelope[ZPT_PAYLOAD]["scope"]->str() : "defaults") + std::string("&client_id=") + _envelope[ZPT_PAYLOAD]["client_id"]->str() + std::string("&redirect_uri=") + _envelope[ZPT_PAYLOAD]["redirect_uri"]->str() + std::string("&state=") + ((std::string) _envelope[ZPT_PAYLOAD]["state"]));
			zpt::base64::encode(_state);
			zpt::url::encode(_state);
			std::string _login_url(this->__options["url"]["auth"]["login"]->str());
			return JPTR(
				ZPT_STATUS << (_performative == zpt::ev::Post ? 303 : 307) <<
				ZPT_HEADERS << JSON(
					"Location" << (_login_url + (_login_url.find("?") != string::npos ? "&" : "?") + std::string("state=") + _state)
				)
			);
		}

		std::string _user_uri(std::string("/api/") + _emitter->options()["rest"]["version"]->str() + std::string("/users/me"));
		zpt::JSONPtr _user = _emitter->route(zpt::ev::Get, _user_uri,
			JPTR(
				ZPT_HEADERS << JSON(
					"Cookie" << _envelope[ZPT_HEADERS]["Cookie"]
				)
			)
		);
		if (!_user->ok() || ((int) _user[ZPT_STATUS]) != 200) {
			std::string _state(std::string("scope=") + _envelope[ZPT_PAYLOAD]["scope"]->str() + std::string("&client_id=") + _envelope[ZPT_PAYLOAD]["client_id"]->str() + std::string("&redirect_uri=") + _envelope[ZPT_PAYLOAD]["redirect_uri"]->str() + std::string("&state=") + ((std::string) _envelope[ZPT_PAYLOAD]["state"]));
			zpt::base64::encode(_state);
			zpt::url::encode(_state);
			std::string _login_url(this->__options["url"]["auth"]["login"]->str());
			return JPTR(
				ZPT_STATUS << (_performative == zpt::ev::Post ? 303 : 307) <<
				ZPT_HEADERS << JSON(
					"Location" << (_login_url + (_login_url.find("?") != string::npos ? "&" : "?") + std::string("state=") + _state)
				)
			);
		}
		
		std::string _app_uri(std::string("/api/") + _emitter->options()["rest"]["version"]->str() + std::string("/apps/") + ((std::string) _envelope[ZPT_PAYLOAD]["client_id"]));
		zpt::JSONPtr _application = _emitter->route(zpt::ev::Get, _app_uri, zpt::undefined);
		std::string _redirect_uri(_envelope[ZPT_PAYLOAD]["redirect_uri"]->str());
		if (_application[ZPT_STATUS] == 200) {
			std::string _code = _db->insert("codes", std::string("/api/") + this->__options["rest"]["version"]->str() + std::string("/apps/") + ((std::string) _envelope[ZPT_PAYLOAD]["client_id"]) + std::string("/codes"),
				JPTR(
					"client_id" << _envelope[ZPT_PAYLOAD]["client_id"] <<
					"scope" << _envelope[ZPT_PAYLOAD]["scope"] <<
					"application" << _application[ZPT_PAYLOAD] << 
					"user" << _user[ZPT_PAYLOAD]
				)
			);
			return JPTR(
				ZPT_STATUS << (_performative == zpt::ev::Post ? 303 : 307) <<
				ZPT_HEADERS << JSON(
					"Location" << (_redirect_uri + (_redirect_uri.find("?") != string::npos ? std::string("&") : std::string("?")) +
						std::string("code=") + _code +
						(_envelope[ZPT_PAYLOAD]["state"]->ok() ? std::string("&state=") + _envelope[ZPT_PAYLOAD]["state"]->str() : std::string("")))
				)
			);
		}
		else {
			return JPTR(
				ZPT_STATUS << (_performative == zpt::ev::Post ? 303 : 307) <<
				ZPT_HEADERS << JSON(
					"Location" << (_redirect_uri + (_redirect_uri.find("?") != string::npos ? std::string("&") : std::string("?")) + std::string("error=true&reason=no+such+application"))
				)
			);
		}
	}
	else if (_response_type == "password") {
		assertz(
			_envelope[ZPT_PAYLOAD]->ok() &&
			_envelope[ZPT_PAYLOAD]["client_id"]->ok() &&
			_envelope[ZPT_PAYLOAD]["redirect_uri"]->ok() &&
			_envelope[ZPT_PAYLOAD]["username"]->ok() &&
			_envelope[ZPT_PAYLOAD]["password"]->ok(),
			"required fields: 'client_id', 'redirect_uri', 'username' & 'password'", 412, 0);

		std::string _user_uri(std::string("/api/") + _emitter->options()["rest"]["version"]->str() + std::string("/users/me"));
		zpt::JSONPtr _user = _emitter->route(zpt::ev::Get, _user_uri,
			JPTR(
				ZPT_PAYLOAD << JSON(
					"username" << _envelope[ZPT_PAYLOAD]["username"] <<
					"password" << _envelope[ZPT_PAYLOAD]["password"]
				)
			)
		);
		if (_user->ok() && ((int) _user[ZPT_STATUS]) == 200) {
			std::string _authorization_url(this->__options["url"]["auth"]["authorization"]->str());
			zpt::JSONPtr _token = this->generate_token(_user[ZPT_PAYLOAD]["_id"], std::string("/api/") + _emitter->options()["rest"]["version"]->str() + std::string("/apps/") + _envelope[ZPT_PAYLOAD]["client_id"]->str(), _envelope[ZPT_PAYLOAD]["client_id"]->str(), "", "me{rwx},users{r}", _response_type, _emitter);
			return JPTR(
				ZPT_STATUS << (_performative == zpt::ev::Post ? 303 : 307) <<
				ZPT_HEADERS << JSON(
					"Set-Cookie" << (std::string("path=/; ") + _user["id"]->str() + std::string("@") + _token["access_token"]->str()) << 
					"Location" << (_authorization_url + (_authorization_url.find("?") != string::npos ? "&" : "?") +
						std::string("access_token=") + _token["access_token"]->str() +
						std::string("&refresh_token=") + _token["refresh_token"]->str() +
						std::string("&expires=") + ((std::string) _token["expires"]) +
						std::string("&state=") + ((std::string) _envelope[ZPT_PAYLOAD]["state"]))
				)
			);
		}
		return zpt::undefined;
	}					
	else if (_response_type == "implicit") {
		return zpt::undefined;
	}					
	else if (_response_type == "client_credentials") {
		return zpt::undefined;
	}					
	assertz(false, "\"response_type\" not valid", 400, 0);
}

zpt::JSONPtr zpt::authenticator::OAuth2::token(zpt::ev::Performative _performative, zpt::JSONPtr _envelope, zpt::EventEmitterPtr _emitter) {
	assertz(
		_envelope[ZPT_PAYLOAD]->ok() &&
		_envelope[ZPT_PAYLOAD]["client_id"]->ok() &&
		_envelope[ZPT_PAYLOAD]["client_secret"]->ok() &&
		_envelope[ZPT_PAYLOAD]["code"]->ok(),
		"required fields: 'client_id', 'client_secret' & 'code'", 412, 0);

	zpt::redis::Client* _db = (zpt::redis::Client*) _emitter->get_kb("redis.oauth").get();
	std::string _client_id((std::string) _envelope[ZPT_PAYLOAD]["client_id"]);
	zpt::JSONPtr _code = _db->get("codes", std::string("/api/") + this->__options["rest"]["version"]->str() + std::string("/apps/") + _client_id + std::string("/codes/") + ((std::string) _envelope[ZPT_PAYLOAD]["code"]));
	assertz(_code->ok(), "invalid parameter: no such code", 404, 0);
	std::string _client_secret((std::string) _envelope[ZPT_PAYLOAD]["client_secret"]);

	return JPTR(
		ZPT_STATUS << 200 <<
		ZPT_PAYLOAD << this->generate_token(_code["user"]["_id"]->str(), _code["application"]["_id"]->str(), _client_id, _client_secret, "code",  _code["scope"]->str(), _emitter)
	);
}

zpt::JSONPtr zpt::authenticator::OAuth2::generate_token(std::string _owner_url, std::string _application_url, std::string _client_id, std::string _client_secret, std::string _scope, std::string _grant_type, zpt::EventEmitterPtr _emitter) {
	zpt::redis::Client* _db = (zpt::redis::Client*) _emitter->get_kb("redis.oauth").get();
	zpt::JSONPtr _owner = _emitter->route(zpt::ev::Get, _owner_url, zpt::undefined);
	assertz(_owner[ZPT_STATUS] == 200, "invalid resource: no such resource owner", 404, 0);
	zpt::JSONPtr _application = _emitter->route(zpt::ev::Get, _application_url, zpt::undefined);
	assertz(_application[ZPT_STATUS] == 200, "invalid resource: no such application", 404, 0);
	assertz(_client_secret.length() == 0 || _application[ZPT_PAYLOAD]["client_secret"]->str() == _client_secret, "invalid parameter: no such client secret", 401, 0);
	
	std::string _access_token(_owner[ZPT_PAYLOAD]["id"]->str() + std::string("@") + _application[ZPT_PAYLOAD]["id"]->str() + std::string("/") + _scope + std::string("/") + _grant_type + std::string("/") + zpt::generate_key() + zpt::generate_key());
	std::string _refresh_token(zpt::generate_key() + zpt::generate_key());
	zpt::timestamp_t _expires = (zpt::timestamp_t) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + (90L * 24L * 3600L * 1000L);
	zpt::JSONPtr _token = JPTR(
		"id" << _access_token <<
		"access_token" << _access_token <<
		"refresh_token" << _refresh_token <<
		"expires" << _expires <<
		"scope" << _scope <<
		"grant_type" << _grant_type <<
		"application" << _application <<
		"owner" << _owner
	);
	_db->insert("tokens", std::string("/api/") + this->__options["rest"]["version"]->str() + std::string("/oauth2.0/tokens"), _token);
	return JPTR(
		"access_token" << _access_token <<
		"refresh_token" << _refresh_token <<
		"expires" << _expires
	);
}

/***
  # OAuth2.0 API
***/ 
extern "C" void restify(zpt::EventEmitterPtr _emitter) {
	assertz(_emitter->options()["redis"]["oauth"]->ok(), "no 'redis.oauth' object found in provided configuration", 500, 0);
	_emitter->add_kb("redis.oauth", zpt::KBPtr(new zpt::redis::Client(_emitter->options(), "redis.oauth")));
	_emitter->add_kb("authenticator.oauth", zpt::KBPtr(new zpt::authenticator::OAuth2(_emitter->options())));

	/*
	  4.1.  Authorization Code Grant
	  4.2.  Implicit Grant
	  4.3.  Resource Owner Password Credentials Grant
	  4.4.  Client Credentials Grant
	*/
	_emitter->on(std::string("^/api/") + _emitter->options()["rest"]["version"]->str() + std::string("/oauth2.0/authorize$"),
		{
			{
				zpt::ev::Post,
				[ & ] (zpt::ev::Performative _performative, std::string _resource, zpt::JSONPtr _envelope, zpt::EventEmitterPtr _emitter) -> zpt::JSONPtr {
					zpt::authenticator::OAuth2* _oauth = (zpt::authenticator::OAuth2*) _emitter->get_kb("authenticator.oauth").get();
					return _oauth->authorize(_performative, _envelope, _emitter);
				}
			},
			{
				zpt::ev::Get,
				[ & ] (zpt::ev::Performative _performative, std::string _resource, zpt::JSONPtr _envelope, zpt::EventEmitterPtr _emitter) -> zpt::JSONPtr {
					zpt::authenticator::OAuth2* _oauth = (zpt::authenticator::OAuth2*) _emitter->get_kb("authenticator.oauth").get();
					return _oauth->authorize(_performative, _envelope, _emitter);
				}
			}			
		}
	);

	_emitter->on(std::string("^/api/") + _emitter->options()["rest"]["version"]->str() + std::string("/oauth2.0/token$"),
		{
			{
				zpt::ev::Post,
				[ & ] (zpt::ev::Performative _performative, std::string _resource, zpt::JSONPtr _envelope, zpt::EventEmitterPtr _emitter) -> zpt::JSONPtr {
					assertz(
						_envelope[ZPT_PAYLOAD]->ok() &&
						_envelope[ZPT_PAYLOAD]["name"]->ok() &&
						_envelope[ZPT_PAYLOAD]["e-mail"]->ok() &&
						_envelope[ZPT_PAYLOAD]["password"]->ok(),
						"required fields: 'name', 'e-mail' and 'password'", 412, 0);
				
					zpt::redis::Client* _db = (zpt::redis::Client*) _emitter->get_kb("redis.oauth").get();
					std::string _id = _db->insert("users", _resource, _envelope[ZPT_PAYLOAD]);
					return JPTR(
						ZPT_STATUS << 200 <<
						ZPT_PAYLOAD << JSON(
							"id" << _id <<
							"href" << (_resource + (_resource.back() != '/' ? std::string("/") : std::string("")) + _id)
						)
					);
				}
			}
		}
	);

	_emitter->on(std::string("^/api/") + _emitter->options()["rest"]["version"]->str() + std::string("/oauth2.0/tokens/([^/]+)$"),
		{
			{
				zpt::ev::Get,
				[ & ] (zpt::ev::Performative _performative, std::string _resource, zpt::JSONPtr _envelope, zpt::EventEmitterPtr _emitter) -> zpt::JSONPtr {
					zpt::redis::Client* _db = (zpt::redis::Client*) _emitter->get_kb("redis.oauth").get();
					zpt::JSONPtr _document = _db->get("tokens", _resource);
					if (!_document->ok()) {
						return JPTR(
							ZPT_STATUS << 404
						);
					}
					return JPTR(
						ZPT_STATUS << 200 <<
						ZPT_PAYLOAD << _document
					);
				}
			}
		}
	);
}
/*
The MIT License (MIT)

Copyright (c) 2017 n@zgul <n@zgul.me>

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

#pragma once

#include <zapata/base.h>
#include <zapata/json.h>
#include <zapata/events.h>
#include <string>
#include <map>
#include <memory>
#include <zmq.hpp>
#include <mutex>
#include <zapata/zmq/SocketStreams.h>
#include <zapata/http/HTTPObj.h>
#include <poll.h>
#include <zmq.h>

using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

#define ZMQ_PUB_SUB -1
#define ZMQ_XPUB_XSUB -2
#define ZMQ_ROUTER_DEALER -3
#define ZMQ_ASSYNC_REQ -4
#define ZMQ_HTTP_RAW -5
#define ZMQ_MQTT_RAW -6
#define ZMQ_UPNP_RAW -7

#define ZPT_SELF_CERTIFICATE 0
#define ZPT_PEER_CERTIFICATE 1

namespace zpt {
extern zmq::context_t __context;

auto str2type(std::string _type) -> short;
auto type2str(short _type) -> std::string;

namespace assync {
typedef std::function<std::string(zpt::json _envelope)> reply_fn;
}

class ZMQPoll : public zpt::Poll {
      public:
	ZMQPoll(zpt::json _options, zpt::ev::emitter _emiter = nullptr);
	virtual ~ZMQPoll();

	virtual auto options() -> zpt::json;
	virtual auto emitter() -> zpt::ev::emitter;
	virtual auto self() const -> zpt::poll;

	virtual auto get(std::string _uuid) -> zpt::socket_ref;
	virtual auto relay(std::string _key) -> zpt::Channel*;
	virtual auto add(short _type, std::string _connection, bool _new_connection = false) -> zpt::socket_ref;
	virtual auto add(zpt::Channel* _underlying) -> zpt::socket_ref;
	virtual auto remove(zpt::socket_ref _socket) -> void;
	virtual auto vanished(std::string _connection, zpt::ev::initializer _callback = nullptr) -> void;
	virtual auto vanished(zpt::Channel* _underlying, zpt::ev::initializer _callback = nullptr) -> void;
	virtual auto pretty() -> std::string;

	virtual auto poll(zpt::socket_ref _socket) -> void;
	virtual auto clean_up(zpt::socket_ref _socket, bool _force = false) -> void;

	virtual auto loop() -> void;

      private:
	zpt::json __options;
	std::map<std::string, zpt::Channel*> __by_refs;
	std::vector<zpt::socket_ref> __by_socket;
	std::vector<zmq::pollitem_t> __items;
	::pthread_t __id;
	zmq::socket_ptr __sync[2];
	std::mutex __mtx[2];
	zpt::poll __self;
	zpt::ev::emitter __emitter;
	bool __needs_rebuild;
	std::map<zpt::socket_ref, std::string> __to_add;
	std::map<zpt::socket_ref, zpt::ev::initializer> __to_remove;

	auto bind(short _type, std::string _connection) -> zpt::Channel*;
	auto signal(std::string _message) -> void;
	auto notify(std::string _message) -> void;
	auto wait() -> void;
	auto repoll() -> void;
	auto reply(zpt::json _envelope, zpt::socket_ref _socket) -> void;
};

class ZMQReq : public zpt::Channel {
      public:
	ZMQReq(std::string _connection, zpt::json _options);
	virtual ~ZMQReq();

	// virtual zpt::json send(zpt::json _envelope);

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket;
};

class ZMQRep : public zpt::Channel {
      public:
	ZMQRep(std::string _connection, zpt::json _options);
	virtual ~ZMQRep();

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket;
};

class ZMQXPubXSub : public zpt::Channel {
      public:
	ZMQXPubXSub(std::string _connection, zpt::json _options);
	virtual ~ZMQXPubXSub();

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket_sub;
	zmq::socket_ptr __socket_pub;
};

class ZMQPubSub : public zpt::Channel {
      public:
	ZMQPubSub(std::string _connection, zpt::json _options);
	virtual ~ZMQPubSub();

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

	virtual void subscribe(std::string _prefix);

      private:
	zmq::socket_ptr __socket_sub;
	zmq::socket_ptr __socket_pub;
	std::mutex __out_mtx;
};

class ZMQPub : public zpt::Channel {
      public:
	ZMQPub(std::string _connection, zpt::json _options);
	virtual ~ZMQPub();

	virtual zpt::json recv();

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket;
};

class ZMQSub : public zpt::Channel {
      public:
	ZMQSub(std::string _connection, zpt::json _options);
	virtual ~ZMQSub();

	virtual zpt::json send(zpt::json _envelope);

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

	virtual void subscribe(std::string _prefix);

      private:
	zmq::socket_ptr __socket;
};

class ZMQPush : public zpt::Channel {
      public:
	ZMQPush(std::string _connection, zpt::json _options);
	virtual ~ZMQPush();

	virtual zpt::json recv();

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket;
};

class ZMQPull : public zpt::Channel {
      public:
	ZMQPull(std::string _connection, zpt::json _options);
	virtual ~ZMQPull();

	virtual zpt::json send(zpt::json _envelope);

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket;
};

class ZMQRouterDealer : public zpt::Channel {
      public:
	ZMQRouterDealer(std::string _connection, zpt::json _options);
	virtual ~ZMQRouterDealer();

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket_router;
	zmq::socket_ptr __socket_dealer;
};

class ZMQRouter : public zpt::Channel {
      public:
	ZMQRouter(std::string _connection, zpt::json _options);
	virtual ~ZMQRouter();

	virtual auto send(zpt::json _envelope) -> zpt::json;
	virtual auto recv() -> zpt::json;

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket;
	std::map<std::string, zmq::message_t*> __sock_id;
	std::mutex __sock_mtx;
	std::mutex __in_mtx;
	std::mutex __out_mtx;
};

class ZMQDealer : public zpt::Channel {
      public:
	ZMQDealer(std::string _connection, zpt::json _options);
	virtual ~ZMQDealer();

	virtual auto send(zpt::json _envelope) -> zpt::json;
	virtual auto recv() -> zpt::json;

	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;

      private:
	zmq::socket_ptr __socket;
};

class ZMQHttp : public zpt::Channel {
      public:
	ZMQHttp(zpt::socketstream_ptr _underlying, zpt::json _options);
	virtual ~ZMQHttp();

	virtual auto recv() -> zpt::json;
	virtual auto send(zpt::json _envelope) -> zpt::json;

	virtual auto underlying() -> zpt::socketstream_ptr;
	virtual auto socket() -> zmq::socket_ptr;
	virtual auto in() -> zmq::socket_ptr;
	virtual auto out() -> zmq::socket_ptr;
	virtual auto fd() -> int;
	virtual auto in_mtx() -> std::mutex&;
	virtual auto out_mtx() -> std::mutex&;
	virtual auto type() -> short int;
	virtual auto protocol() -> std::string;
	virtual auto close() -> void;
	virtual auto available() -> bool;

      private:
	zpt::socketstream_ptr __underlying;
	short __state;
	std::string __cid;
	std::string __resource;
	;
};

namespace net {
auto getip(std::string _if = "") -> std::string;
}

namespace rest {
auto http2zmq(zpt::http::req _request) -> zpt::json;
auto http2zmq(zpt::http::rep _reply) -> zpt::json;
auto zmq2http_rep(zpt::json _out) -> zpt::http::rep;
auto zmq2http_req(zpt::json _out, std::string _host) -> zpt::http::req;

namespace http {
zpt::json deserialize(std::string _body);
}
}
}

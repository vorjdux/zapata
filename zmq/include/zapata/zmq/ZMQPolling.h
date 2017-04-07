/*
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

using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

#define ZMQ_PUB_SUB -1
#define ZMQ_XPUB_XSUB -2
#define ZMQ_ROUTER_DEALER -3
#define ZMQ_ASSYNC_REQ -4
#define ZMQ_HTTP_RAW -5

#define ZPT_SELF_CERTIFICATE 0
#define ZPT_PEER_CERTIFICATE 1

namespace zmq {
	typedef std::shared_ptr< zmq::socket_t > socket_ptr;
}

namespace zpt {
	extern zmq::context_t __context;

	short str2type(std::string _type);
	
	class ZMQPoll;
	class ZMQ;

	class ZMQPollPtr : public std::shared_ptr<zpt::ZMQPoll> {
	public:
		ZMQPollPtr(zpt::json _options, zpt::ev::emitter _emiter);
		ZMQPollPtr(zpt::json _options);
		ZMQPollPtr(zpt::ZMQPoll * _ptr);
		virtual ~ZMQPollPtr();
	};
	
	typedef zpt::ZMQPollPtr poll;
	typedef std::shared_ptr< zpt::ZMQ > socket;

	namespace assync {
		typedef std::function< std::string (zpt::json _envelope) > reply_fn;
	}

	class socket_ref : public std::string {
	public:
		socket_ref();
		socket_ref(std::string _rhs, zpt::poll _poll);
		socket_ref(const zpt::socket_ref& _rhs);
		
		auto poll(zpt::poll _poll);
		auto poll() -> zpt::poll;
		auto operator->() -> zpt::ZMQ*;
		auto operator*() -> zpt::ZMQ*;

	private:
		zpt::poll __poll;
	};
	
	class ZMQPoll {
	public:
		ZMQPoll(zpt::json _options, zpt::ev::emitter _emiter = nullptr);
		virtual ~ZMQPoll();
		
		virtual auto options() -> zpt::json;
		virtual auto emitter() -> zpt::ev::emitter;
		virtual auto self() const -> zpt::ZMQPollPtr;

		virtual auto get(std::string _uuid) -> zpt::socket_ref;
		virtual auto relay(std::string _key) -> zpt::ZMQ*;
		virtual auto add(short _type, std::string _connection) -> zpt::socket_ref;
		virtual auto add(zpt::ZMQ* _underlying) -> zpt::socket_ref;
		virtual auto remove(zpt::socket_ref _socket) -> void;

		virtual auto poll(zpt::socket_ref _socket) -> void;
		
		virtual auto loop() -> void;
			
	private:
		zpt::json __options;
		std::map< std::string, zpt::ZMQ* > __by_refs;
		std::vector< zpt::socket_ref > __by_socket;
		std::vector< zmq::pollitem_t > __items;
		::pthread_t __id;
		zmq::socket_ptr __sync[2];
		std::mutex __mtx[2];
		zpt::ZMQPollPtr __self;
		zpt::ev::emitter __emitter;
		bool __need_rebuild;
		
		auto bind(short _type, std::string _connection) -> zpt::ZMQ*;
		auto signal(std::string _message) -> void;
		auto notify(std::string _message) -> void;
		auto wait() -> void;
		auto repoll() -> void;
	};

	class ZMQ {
	public:
		ZMQ(std::string _connection, zpt::json _options);
		virtual ~ZMQ();
		
		virtual auto id() -> std::string;
		virtual auto options() -> zpt::json;
		virtual auto connection() -> std::string;
		virtual auto connection(std::string _connection) -> void;
		virtual auto uri(size_t _idx = 0) -> zpt::json;
		virtual auto uri(std::string _connection) -> void;
		virtual auto detach() -> void;
		virtual auto close() -> void;
		
		virtual auto recv() -> zpt::json;
		virtual auto send(zpt::ev::performative _performative, std::string _resource, zpt::json _payload) -> zpt::json;
		virtual auto send(zpt::json _envelope) -> zpt::json;
		
		static auto recv(zmq::socket_ptr _socket) -> zpt::json;
		static auto send(zpt::ev::performative _performative, std::string _resource, zpt::json _payload, zmq::socket_ptr _socket) -> zpt::json;
		static auto send(zpt::json _envelope, zmq::socket_ptr _socket) -> zpt::json;
		
		virtual void relay_for(zpt::socketstream_ptr _socket, zpt::assync::reply_fn _transform);
		virtual void relay_for(zpt::socket_ref _socket);

		//virtual auto self() const -> zpt::socket_ref = 0;
		virtual auto socket() -> zmq::socket_ptr = 0;
		virtual auto in() -> zmq::socket_ptr = 0;
		virtual auto out() -> zmq::socket_ptr = 0;
		virtual auto fd() -> int = 0;
		virtual auto in_mtx() -> std::mutex& = 0;
		virtual auto out_mtx() -> std::mutex& = 0;
		virtual auto type() -> short int = 0;
		
	private:
		zpt::json __options;
		std::string __connection;
		std::string __id;
		zpt::json __uri;

	protected:
		std::mutex __mtx;
		zpt::poll __poll;
		
	};

	class ZMQReq : public zpt::ZMQ {
	public:
		ZMQReq(std::string _connection, zpt::json _options);
		virtual ~ZMQReq();
		
		virtual zpt::json send(zpt::json _envelope);
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket;
		// zpt::socket_ref __self;
	};
	
	class ZMQRep : public zpt::ZMQ {
	public:
		ZMQRep(std::string _connection, zpt::json _options);
		virtual ~ZMQRep();
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket;
		// zpt::socket_ref __self;
	};
	
	class ZMQXPubXSub : public zpt::ZMQ {
	public:
		ZMQXPubXSub(std::string _connection, zpt::json _options);
		virtual ~ZMQXPubXSub();
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr ;
		virtual auto in() -> zmq::socket_ptr ;
		virtual auto out() -> zmq::socket_ptr ;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket_sub;
		zmq::socket_ptr __socket_pub;
		// zpt::socket_ref __self;
	};
	
	class ZMQPubSub : public zpt::ZMQ {
	public:
		ZMQPubSub(std::string _connection, zpt::json _options);
		virtual ~ZMQPubSub();
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		virtual void subscribe(std::string _prefix);
		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket_sub;
		zmq::socket_ptr __socket_pub;
		// zpt::socket_ref __self;
		std::mutex __out_mtx;
	};
	
	class ZMQPub : public zpt::ZMQ {
	public:
		ZMQPub(std::string _connection, zpt::json _options);
		virtual ~ZMQPub();
		
		virtual zpt::json recv();
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket;
		// zpt::socket_ref __self;
	};
	
	class ZMQSub : public zpt::ZMQ {
	public:
		ZMQSub(std::string _connection, zpt::json _options);
		virtual ~ZMQSub();
		
		virtual zpt::json send(zpt::json _envelope);
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		virtual void subscribe(std::string _prefix);
		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket;
		// zpt::socket_ref __self;
	};
	
	class ZMQPush : public zpt::ZMQ {
	public:
		ZMQPush(std::string _connection, zpt::json _options);
		virtual ~ZMQPush();
		
		virtual zpt::json recv();
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket;
		// zpt::socket_ref __self;
	};

	class ZMQPull : public zpt::ZMQ {
	public:
		ZMQPull(std::string _connection, zpt::json _options);
		virtual ~ZMQPull();
		
		virtual zpt::json send(zpt::json _envelope);
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket;
		// zpt::socket_ref __self;
	};

	class ZMQRouterDealer : public zpt::ZMQ {
	public:
		ZMQRouterDealer(std::string _connection, zpt::json _options);
		virtual ~ZMQRouterDealer();
		
		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket_router;
		zmq::socket_ptr __socket_dealer;
		// zpt::socket_ref __self;
	};

	class ZMQHttp : public zpt::ZMQ {
	public:
		ZMQHttp(zpt::socketstream_ptr _underlying, zpt::json _options);
		virtual ~ZMQHttp();
		
		virtual auto recv() -> zpt::json;
		virtual auto send(zpt::json _envelope) -> zpt::json;

		// virtual auto self() const -> zpt::socket;
		virtual auto socket() -> zmq::socket_ptr;
		virtual auto in() -> zmq::socket_ptr;
		virtual auto out() -> zmq::socket_ptr;
		virtual auto fd() -> int;
		virtual auto in_mtx() -> std::mutex&;
		virtual auto out_mtx() -> std::mutex&;
		virtual auto type() -> short int;
		virtual auto close() -> void;

		
	private:
		// zmq::context_t __context;
		zmq::socket_ptr __socket;
		zpt::socketstream_ptr __underlying;
		// zpt::socket_ref __self;
	};

	namespace net {
		auto getip() -> std::string;
	}


	namespace rest {
		auto http2zmq(zpt::http::req _request) -> zpt::json;
		auto http2zmq(zpt::http::rep _reply) -> zpt::json;
		auto zmq2http(zpt::json _out) -> zpt::HTTPRep;

		namespace http {
			zpt::json deserialize(std::string _body);
		}
	}
	
}


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

#include <zapata/json.h>
#include <hiredis/hiredis.h>
#include <ossp/uuid++.hh>
#include <mutex>

 using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

namespace zpt {

	namespace redis {

		class Client : public zpt::KB {
		public:
			Client(zpt::JSONPtr _options, std::string _conf_path);
			virtual ~Client();

			virtual zpt::JSONPtr options();
			virtual std::string name();

			virtual void connect(string _host, uint _port);
			virtual void reconnect();

			virtual std::string insert(std::string _collection, std::string _id_prefix, zpt::JSONPtr _record);
			virtual int save(std::string _collection, std::string _url, zpt::JSONPtr _record);
			virtual int set(std::string _collection, std::string _url, zpt::JSONPtr _record);
			virtual int unset(std::string _collection, std::string _url, zpt::JSONPtr _document);
			virtual int remove(std::string _collection, std::string _url);
			virtual zpt::JSONPtr get(std::string _collection, std::string _url);
			virtual zpt::JSONPtr query(std::string _collection, std::string _regex);
			virtual zpt::JSONPtr all(std::string _collection);

		private:
			zpt::JSONPtr __options;
			zpt::JSONPtr __redis_conf;
			std::string __conf_path;
			std::mutex __mtx;
			redisContext* __conn;
			std::string __host;
			uint __port;
		};

		class ClientPtr : public std::shared_ptr<zpt::redis::Client> {
		public:
			/**
			 * @brief Creates an std::shared_ptr to an Self instance.
			 * 
			 * @param _options the configuration object retrieved from the configuration JSON file
			 */
			ClientPtr(zpt::redis::Client * _target);
			ClientPtr(zpt::JSONPtr _options, std::string _conf_path);

			/**
			 * @brief Destroys the current Self instance, freeing all allocated memory.
			 */
			virtual ~ClientPtr();
		};
	}
}
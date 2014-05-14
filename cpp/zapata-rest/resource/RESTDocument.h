#pragma once

#include <resource/RESTResource.h>

namespace zapata {

	class RESTDocument: public RESTResource {
		public:
			RESTDocument(string _url_pattern);
			virtual ~RESTDocument();

			virtual void get(HTTPReq& _req, HTTPRep& _rep);
			virtual void put(HTTPReq& _req, HTTPRep& _rep);
			virtual void post(HTTPReq& _req, HTTPRep& _rep) final;
			virtual void remove(HTTPReq& _req, HTTPRep& _rep);
			virtual void head(HTTPReq& _req, HTTPRep& _rep);
			virtual void patch(HTTPReq& _req, HTTPRep& _rep);

	};

}

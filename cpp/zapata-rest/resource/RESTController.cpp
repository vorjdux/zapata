#include <resource/RESTController.h>

zapata::RESTController::RESTController(string _url_pattern) : RESTResource(_url_pattern) {
}

zapata::RESTController::~RESTController(){
}

void zapata::RESTController::get(HTTPReq& _req, HTTPRep& _rep) {
	_rep->status(zapata::HTTP405);
}

void zapata::RESTController::put(HTTPReq& _req, HTTPRep& _rep) {
	_rep->status(zapata::HTTP405);
}

void zapata::RESTController::post(HTTPReq& _req, HTTPRep& _rep) {
	_rep->status(zapata::HTTP201);
}

void zapata::RESTController::remove(HTTPReq& _req, HTTPRep& _rep) {
	_rep->status(zapata::HTTP405);
}

void zapata::RESTController::head(HTTPReq& _req, HTTPRep& _rep) {
	_rep->status(zapata::HTTP405);
}

void zapata::RESTController::patch(HTTPReq& _req, HTTPRep& _rep) {
	_rep->status(zapata::HTTP405);
}
#ifndef FOUNDATION_NETWORK_REQUEST_H_
#define FOUNDATION_NETWORK_REQUEST_H_

#include <curl\curl.h>
#include <curl\easy.h>

struct RequestFormElement {
	int type;
	char* name;
	char* data;
};

class HTTPRequest {
public:
	enum {
		ELEMENT_TYPE_TEXT = CURLFORM_COPYCONTENTS,
		ELEMENT_TYPE_FILE = CURLFORM_FILE
	};

	HTTPRequest(const char* url);
	~HTTPRequest();

	void AddFormElement(const char* name, const char* value, int type = ELEMENT_TYPE_TEXT);

	const char* url() {return this->url_.c_str();}
	void set_url(const char* url) {this->url_.assign(url);};

	std::deque<RequestFormElement*>* form_elements() {return &this->form_elements_;} 
private:
	std::string url_;
	std::deque<RequestFormElement*> form_elements_;

	DISALLOW_COPY_AND_ASSIGN(HTTPRequest);
};

#endif // FOUNDATION_NETWORK_REQUEST_H_
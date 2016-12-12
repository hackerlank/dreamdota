#include "stdafx.h"
#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(const char* url) {
	this->url_.assign(url);
}

HTTPRequest::~HTTPRequest() {
	if (this->form_elements_.size()) {
		std::deque<RequestFormElement*>::iterator iterator;
		for (iterator = this->form_elements_.begin(); iterator != this->form_elements_.end(); iterator++) {
			delete [] (*iterator)->data;
			delete [] (*iterator)->name;
		}
	}
}

void HTTPRequest::AddFormElement(const char* name, const char* value, int type) {
	RequestFormElement* element = new RequestFormElement;
	
	size_t len = strlen(name);
	element->name = new char[len + 1];
	strcpy_s(element->name, len + 1, name);

	element->type = type;

	size_t data_size = strlen(value);
	element->data = new char[data_size + 1];
	memcpy_s(element->data, data_size + 1, value, data_size + 1);
	
	this->form_elements_.push_back(element);
}
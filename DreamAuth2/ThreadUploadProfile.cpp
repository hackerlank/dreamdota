#include "stdafx.h"
#include "ThreadUploadProfile.h"
#include "HTTPRequest.h"
#include "LocaleString.h"
#include "Auth.h"
#include "../DreamWarcraft/Profile.h"
#include "SMRoamingProfile.h"

void ThreadUploadProfile::Work() {
	bool rv = false;
	if (!this->url_.size()) {
		this->url_ = StringManager::StringUTF8(STR::ROAMING_PROFILE_SERVICE_URL) + "upload/";
	}

	std::string url = this->url_ + Auth::GetSessionId();

	HTTPRequest req(url.c_str());
	req.AddFormElement("file", PROFILE_FILENAMEA, HTTPRequest::ELEMENT_TYPE_FILE);
	req.AddFormElement("name", (char*)this->arg());
	if (0 == this->http_.Request(&req)) {
		const HTTP::ResponseData* result_data = this->http_.GetResponseData();
		rv = SMRoamingProfile::GetInstance()->ParseJSON((char*)result_data->buffer, result_data->data_size);
	}
	this->set_result(rv);
}

void ThreadUploadProfile::Term() {
	this->http_.SetCancelFlag(true);
	this->http_.WaitComplete();
}
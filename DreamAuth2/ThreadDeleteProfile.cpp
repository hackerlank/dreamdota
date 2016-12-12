#include "stdafx.h"
#include "ThreadDeleteProfile.h"
#include "HTTPRequest.h"
#include "LocaleString.h"
#include "Auth.h"
#include "SMRoamingProfile.h"

void ThreadDeleteProfile::Work() {
	bool rv = false;
	if (!this->url_.size()) {
		this->url_ = StringManager::StringUTF8(STR::ROAMING_PROFILE_SERVICE_URL) + "del/";
	}

	std::string url = this->url_ + Auth::GetSessionId();

	HTTPRequest req(url.c_str());
	char id[11];
	sprintf_s(id, 11, "%d", (int)this->arg());
	req.AddFormElement("id", id);
	if (0 == this->http_.Request(&req)) {
		const HTTP::ResponseData* result_data = this->http_.GetResponseData();
		rv = SMRoamingProfile::GetInstance()->ParseJSON((char*)result_data->buffer, result_data->data_size);
	}
	this->set_result(rv);
}

void ThreadDeleteProfile::Term() {
	this->http_.SetCancelFlag(true);
	this->http_.WaitComplete();
}
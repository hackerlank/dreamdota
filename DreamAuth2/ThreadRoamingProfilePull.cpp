#include "stdafx.h"
#include "SMRoamingProfile.h"
#include "ThreadRoamingProfilePull.h"
#include "Auth.h"
#include "LocaleString.h"
#include "HTTP.h"
#include <json-c\json.h>

void ThreadRoamingProfilePull::Work() {
	bool rv = false;
	if (!this->url_.size()) {
		this->url_ = StringManager::StringUTF8(STR::ROAMING_PROFILE_SERVICE_URL) + "pull/";
	}
	
	std::string url = this->url_ + Auth::GetSessionId();

	if (0 == this->http_.SimpleRequest(url.c_str())) {
		const HTTP::ResponseData* result_data = this->http_.GetResponseData();
		rv = SMRoamingProfile::GetInstance()->ParseJSON((char*)result_data->buffer, result_data->data_size);
	}
	this->set_result(rv);
}

void ThreadRoamingProfilePull::Term() {
	this->http_.SetCancelFlag(true);
	this->http_.WaitComplete();
}
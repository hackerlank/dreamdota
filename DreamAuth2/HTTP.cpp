#include "stdafx.h"
#include "HTTP.h"
#include "HTTPRequest.h"

HTTP::HTTP() {
	this->data_.buffer = new BYTE[INITIAL_BUFFER_SIZE];
	this->data_.data_size = 0;
	this->data_.buffer_size = INITIAL_BUFFER_SIZE;

	this->canceled_ = false;
	this->mutex_ = CreateMutex(NULL, FALSE, NULL);
}

HTTP::~HTTP() {
	Lock();

	delete [] this->data_.buffer;
	
	Unlock();

	CloseHandle(this->mutex_);
}

HTTP::RequestCompleteCodeEnum HTTP::DownloadFile(const char* url, const char* save_as) {
	Lock();
	this->canceled_ = false;

	RequestCompleteCodeEnum rv;
	FILE* fp;
	if (0 != fopen_s(&fp, save_as, "wb")) {
		return REQUEST_ERROR_IO;
	}

	CURL* curl;

	curl = curl_easy_init();
 
	// Set url
	curl_easy_setopt(curl, CURLOPT_URL, url);
 
	// Set data collector function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataWriteToFile);
 
	// Set progress function
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0); 
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);

	// SSL related
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, NULL);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, NULL); 
	curl_easy_setopt(curl, CURLOPT_CAINFO, NULL); 
	curl_easy_setopt(curl, CURLOPT_CAPATH, NULL); 
 
	// Timeout
	//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); //in seconds
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
 
	// Set result buffer
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	CURLcode code = curl_easy_perform(curl);
 
	if (0 == code)
	{
		rv = REQUEST_SUCCESS;
	}
	else
	{
		rv = (code == CURLE_ABORTED_BY_CALLBACK ? REQUEST_CANCELED : REQUEST_ERROR_NET);
	}
 
	curl_easy_cleanup(curl);

	fclose(fp);

	Unlock();
	return rv;
}

HTTP::RequestCompleteCodeEnum HTTP::SimpleRequest(const char* url, uint32_t timeout) {
	Lock();

	this->canceled_ = false;
	this->data_.data_size = 0;

	RequestCompleteCodeEnum rv;
	CURL* curl;

	curl = curl_easy_init();
 
	// Set url
	curl_easy_setopt(curl, CURLOPT_URL, url);
 
	// Set data collector function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataWriteToBuffer);
 
	// Set progress function
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0); 
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);

	// SSL related
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, NULL);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, NULL); 
	curl_easy_setopt(curl, CURLOPT_CAINFO, NULL); 
	curl_easy_setopt(curl, CURLOPT_CAPATH, NULL); 
 
	// Timeout
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); //in seconds
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

	CURLcode code = curl_easy_perform(curl);
 
	if (0 == code)
	{
		rv = REQUEST_SUCCESS;
	}
	else
	{
		rv = REQUEST_ERROR_NET;
	}
 
	curl_easy_cleanup(curl);

	Unlock();
	return rv;
}

HTTP::RequestCompleteCodeEnum HTTP::Request(HTTPRequest* request, uint32_t timeout) {
	Lock();

	this->canceled_ = false;
	this->data_.data_size = 0;

	RequestCompleteCodeEnum rv;
	bool has_form = false;
	CURL* curl;
 	struct curl_httppost *formpost=NULL;
	struct curl_httppost *lastptr=NULL;
	struct curl_slist *headerlist=NULL;
	static const char buf[] = "Expect:";

	//Form

	//TODO: Move this part into Class HTTPRequest
	std::deque<RequestFormElement*>* elements = request->form_elements();
	if (elements->size()) {
		has_form = true;

		curl_global_init(CURL_GLOBAL_ALL);

		std::deque<RequestFormElement*>::iterator i;
		RequestFormElement* element;
		for (i = elements->begin(); i != elements->end(); i++) {
			element = *i;
			curl_formadd(
				&formpost,
				&lastptr,
				CURLFORM_COPYNAME, element->name,
				element->type, element->data,
				CURLFORM_END);
		}

		headerlist = curl_slist_append(headerlist, buf);
	}

	curl = curl_easy_init();
 
	if (has_form) {
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	}

	// Set url
	curl_easy_setopt(curl, CURLOPT_URL, request->url());
 
	// Set data collector function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataWriteToBuffer);

	// Set progress function
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0); 
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
 
	// SSL related
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, NULL);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, NULL); 
	curl_easy_setopt(curl, CURLOPT_CAINFO, NULL); 
	curl_easy_setopt(curl, CURLOPT_CAPATH, NULL); 
 
	// Timeout
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); //in seconds
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
	
	CURLcode code = curl_easy_perform(curl);
	
	if (0 == code)
	{
		rv = REQUEST_SUCCESS;
	}
	else
	{
		rv = REQUEST_ERROR_NET;
	}

	curl_easy_cleanup(curl);

	if (has_form) {

		/* then cleanup the formpost chain */ 
		curl_formfree(formpost);
		/* free slist */ 
		curl_slist_free_all (headerlist);
	}

	Unlock();
	return rv;
}

size_t HTTP::DataWriteToBuffer(void *ptr, size_t size, size_t nmemb, HTTP *t) {
#ifdef _DEBUG
	OutputDebug("Received data: %u * %u = %u bytes.\n", size, nmemb, size * nmemb);
#endif
	size_t remain = t->data_.buffer_size - t->data_.data_size;
	size_t bytes = size * nmemb;
	if (bytes > remain) {
#ifdef _DEBUG
		OutputDebug("Buffer overflow: old size = %u bytes.\n", t->data_.buffer_size);
#endif
		size_t new_size = t->data_.buffer_size * 2;
		while (new_size < bytes)
			new_size *= 2;
		BYTE* new_buffer = new BYTE[new_size];
		memcpy_s(new_buffer, new_size, t->data_.buffer, t->data_.data_size);
		t->data_.buffer_size = new_size;
		delete [] t->data_.buffer;
		t->data_.buffer = new_buffer;
		remain = new_size - t->data_.data_size;
#ifdef _DEBUG
		OutputDebug("New size = %u bytes.\n", t->data_.buffer_size);
#endif
	}

	memcpy_s(t->data_.buffer + t->data_.data_size, remain, ptr, bytes);

	t->data_.data_size += bytes;
 
	return bytes;
}

int HTTP::ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
	HTTP* n = (HTTP*)clientp;
	ProgressInfo data;
	if (dltotal > 0) {
		data.total = dltotal;
		data.now = dlnow;
		n->onDownloadProgress.Invoke(&data);
	} else if (ultotal > 0) {
		data.total = ultotal;
		data.now = ulnow;
		n->onUploadProgress.Invoke(&data);
	}
	return n->canceled_ ? 1 : 0;
}

size_t HTTP::DataWriteToFile(void* ptr, size_t size, size_t nmemb, FILE *fp) {
	return fwrite(ptr, size, nmemb, fp) * size;
}
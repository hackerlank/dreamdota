#ifndef FOUNDATION_NETWORK_H_
#define FOUNDATION_NETWORK_H_

#include <SimpleUI\Delegate.h>

class HTTPRequest;

class HTTP {
public:
	static const uint32_t INITIAL_BUFFER_SIZE = 1024;

	enum RequestCompleteCodeEnum {
		REQUEST_SUCCESS,
		REQUEST_ERROR_NET,
		REQUEST_ERROR_IO,
		REQUEST_CANCELED
	};
	struct ProgressInfo {
		double now;
		double total;
	};

	struct ResponseData {
		BYTE *buffer;
		size_t data_size;
		size_t buffer_size;
	};

	SimpleUI::Delegate<const ProgressInfo*> onUploadProgress;
	SimpleUI::Delegate<const ProgressInfo*> onDownloadProgress;
	SimpleUI::Delegate<RequestCompleteCodeEnum> onRequestComplete;

	const ResponseData* GetResponseData() {return &this->data_;}

	HTTP();
	~HTTP();

	void SetCancelFlag(bool v) {this->canceled_ = v;}

	RequestCompleteCodeEnum SimpleRequest(const char* url, uint32_t timeout = 15);
	RequestCompleteCodeEnum DownloadFile(const char* url, const char* save_as);
	RequestCompleteCodeEnum Request(HTTPRequest* request, uint32_t timeout = 30);

	void WaitComplete() {this->Lock();this->Unlock();}
private:
	static size_t DataWriteToBuffer(void *ptr, size_t size, size_t nmemb, HTTP *data);
	static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
	static size_t DataWriteToFile(void* ptr, size_t size, size_t nmemb, FILE *fp);
	
	ResponseData data_;
	volatile bool canceled_;
	HANDLE mutex_;
	void Lock() {WaitForSingleObject(this->mutex_, INFINITE);}
	void Unlock() {ReleaseMutex(this->mutex_);}

	DISALLOW_COPY_AND_ASSIGN(HTTP);
};



#endif // FOUNDATION_NETWORK_H_
#include "ThreadFileDownload.h"

void ThreadFileDownload::Work() {
	FileDownloadInfo* info = (FileDownloadInfo*)this->arg();
	this->network_obj_.SetCancelFlag(false);
	this->set_result(HTTP::REQUEST_SUCCESS == this->network_obj_.DownloadFile(info->url.c_str(), info->save_as.c_str()));
}
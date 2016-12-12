#ifndef SM_ROAMING_PROFILE_
#define SM_ROAMING_PROFILE_

#include "ServiceModule.h"
#include "SingleInstanceObject.h"
#include "DialogRoamingProfile.h"
#include "DialogUploadProfile.h"
#include "ThreadRoamingProfilePull.h"
#include "ThreadUploadProfile.h"
#include "ThreadDeleteProfile.h"
#include "ThreadFileDownload.h"

class SMRoamingProfile : public ServiceModule, public SingleInstanceObject<SMRoamingProfile> {
public:
	static INT_PTR SMRoamingProfile::ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void onPullThreadComplete(WorkerThread* thread);
	static void onUploadThreadComplete(WorkerThread* thread);
	static void onDeleteThreadComplete(WorkerThread* thread);
	static void onDownloadThreadComplete(WorkerThread* thread);
	static void onCommand(SimpleUI::Control* ctl);
	static void onUploadDialogCommand(SimpleUI::Control* ctl);
	static void onProgress(const HTTP::ProgressInfo* pi);

	enum {
		RESULT_OK				= 0,
		RESULT_NO_QUOTA			= 1, 
		RESULT_UPLOAD_FAILED	= 2,
		RESULT_FILE_NOT_FOUND	= 3
	};

	const wchar_t* TranslateResult(int code) {
		switch(code) {

		case RESULT_NO_QUOTA:
			return ResString::GetString(ResString::RESULT_NO_QUOTA);

		case RESULT_UPLOAD_FAILED:
			return ResString::GetString(ResString::RESULT_UPLOAD_FAILED);

		case RESULT_FILE_NOT_FOUND:
			return ResString::GetString(ResString::RESULT_FILE_NOT_FOUND);

		}
		return ResString::GetString(ResString::SERVICE_UNAVAILABLE);
	}

	struct ProfileData {
		uint32_t id;
		std::string name;
		std::string url;
		uint32_t date;
	};

	typedef std::list<ProfileData> ParsedItemsListType;

	struct PullOption {
		int result;
		ParsedItemsListType items;
		int quota;
		int used;
	};

	bool ParseJSON(const char* json, size_t len);

	SMRoamingProfile();
	~SMRoamingProfile();
	virtual void Perform();
	virtual void Term();
private:
	static bool SameNameExists();

	DialogRoamingProfile* dialog_;
	DialogUploadProfile* dialog_upload_;
	PullOption pull_option_;
	ThreadRoamingProfilePull thread_pull_;
	ThreadUploadProfile thread_upload_;
	ThreadDeleteProfile thread_delete_;

	ThreadFileDownload::FileDownloadInfo di_;
	ThreadFileDownload thread_download_;

	void InitUI();
	void DisposeUI();
	bool ui_inited_;
};

#endif
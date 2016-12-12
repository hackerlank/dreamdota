#include "stdafx.h"
#ifndef THREADLOGIN_H_
#define THREADLOGIN_H_

#include "WorkerThread.h"
#include "Auth.h"
#include <openssl\md5.h>

class ThreadLogin : public WorkerThread {
public:
	struct ResultDataType {
		bool connect_success;
		Auth::LoginResultEnumType server_response;
	};

	virtual void Work();
	
	ThreadLogin() {
		this->account_ = NULL;
		this->password_ = NULL;
	}

	void ClearCredencial() {
		if (this->account_) {
			delete [] this->account_;
			this->account_ = NULL;
		}
		if (this->password_) {
			delete [] this->password_;
			this->password_ = NULL;
		}
	}
	
	bool SetCredencial(const wchar_t* account, const wchar_t* password) {
		bool rv = false;
		if (account && password) {
			size_t len_account = wcslen(account), len_password = wcslen(password);
			int size_account = WideCharToMultiByte(CP_UTF8, NULL, account, len_account, NULL, 0, NULL, NULL);
			int size_password = WideCharToMultiByte(CP_UTF8, NULL, password, len_password, NULL, 0, NULL, NULL);
			if (size_account && size_password) {
				this->ClearCredencial();
				this->account_ = new char[size_account + 1];
				this->account_[size_account] = '\0';
				this->password_ = new char[size_password + 1];
				this->password_[size_password] = '\0';
				if (WideCharToMultiByte(CP_UTF8, NULL, account, len_account, this->account_, size_account + 1, NULL, NULL) > 0 &&
					WideCharToMultiByte(CP_UTF8, NULL, password, len_password, this->password_, size_password + 1, NULL, NULL) > 0) {
					this->HashPassword();
					
#ifdef _DEBUG
						OutputDebug("Account: %s, Password: %s(%s)\n", this->account_, this->password_md5_, this->password_);
#endif

					rv = true;
				} else
					this->ClearCredencial();
			}
		}
		return rv;
	}

	const ResultDataType* login_result() {return &(this->login_result_);}
	const char* GetPasswordHash() {return this->password_md5_;}

	virtual ~ThreadLogin() {
		this->ClearCredencial();
	}
private:
	void HashPassword() {
		//如果长度等于32视为已经hash过
		if (strlen(this->password_) != 32) {
			BYTE result[MD5_DIGEST_LENGTH];
			const char* map = "0123456789abcdef";

			MD5_CTX ctx;
			MD5_Init(&ctx);
			MD5_Update(&ctx, this->password_, strlen(this->password_));
			MD5_Final(result, &ctx);

			for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
				this->password_md5_[i * 2] = map[result[i] / 0x10];
				this->password_md5_[i * 2 + 1] = map[result[i] % 0x10];
			}
			this->password_md5_[32] = '\0';
		} else {
			memcpy_s(this->password_md5_, 33, this->password_, 33);
		}
	}

	NOINLINE void Login();

	char* account_;
	char* password_;
	char password_md5_[33];
	ResultDataType login_result_;

	DISALLOW_COPY_AND_ASSIGN(ThreadLogin);
};

#endif
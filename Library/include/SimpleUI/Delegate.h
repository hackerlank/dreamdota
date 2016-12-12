#ifndef SIMPLEUI_DELEGATE_
#define SIMPLEUI_DELEGATE_

#include <list>
#include <algorithm>
#include <Windows.h>

namespace SimpleUI {

template <typename ArgumentType>
class Delegate {
public:
	typedef void (*HandlerType)(ArgumentType arg);

	void Invoke(ArgumentType arg) {
		if (this->handler_list_.size()) {
			HandlerListType copy = this->handler_list_;
			for (HandlerListType::iterator iter = copy.begin();
					iter != copy.end();
					++iter) {
				(*iter)(arg);
			}
		}
	}

	void operator()(ArgumentType arg) {
		this->Invoke(arg);
	}


	void Add(HandlerType handler) {
		EnterCriticalSection(&this->cs_); 
		this->handler_list_.push_back(handler);	
		LeaveCriticalSection(&this->cs_); 
	}

	void Remove(HandlerType handler) {
		EnterCriticalSection(&this->cs_); 
		HandlerListType::iterator iter = std::find(this->handler_list_.begin(), this->handler_list_.end(), handler);
		if (iter != this->handler_list_.end()) {
			this->handler_list_.erase(iter);
		}
		LeaveCriticalSection(&this->cs_); 
	}

	void RemoveAll() {
		EnterCriticalSection(&this->cs_);
		this->handler_list_.clear();
		LeaveCriticalSection(&this->cs_); 
	}

	Delegate& operator+=(HandlerType handler) {
		this->Add(handler);
		return *this;
	}

	Delegate& operator-=(HandlerType handler) {
		this->Remove(handler);
		return *this;
	}

	Delegate() {InitializeCriticalSectionAndSpinCount(&this->cs_, 0x00000400);}
	~Delegate() {DeleteCriticalSection(&this->cs_);}
private:
	typedef std::list<HandlerType> HandlerListType;
	HandlerListType handler_list_;
	CRITICAL_SECTION cs_;
};

template <>
class Delegate<void> {
public:
	typedef void (*HandlerType)(void);

	void Invoke() {
		if (this->handler_list_.size()) {
			HandlerListType copy = this->handler_list_;
			for (HandlerListType::iterator iter = copy.begin();
					iter != copy.end();
					++iter) {
				(*iter)();
			}
		}
	}

	void operator()(void) {
		this->Invoke();
	}


	void Add(HandlerType handler) {
		EnterCriticalSection(&this->cs_); 
		this->handler_list_.push_back(handler);	
		LeaveCriticalSection(&this->cs_); 
	}

	void Remove(HandlerType handler) {
		EnterCriticalSection(&this->cs_); 
		HandlerListType::iterator iter = std::find(this->handler_list_.begin(), this->handler_list_.end(), handler);
		if (iter != this->handler_list_.end()) {
			this->handler_list_.erase(iter);
		}
		LeaveCriticalSection(&this->cs_); 
	}

	void RemoveAll() {
		EnterCriticalSection(&this->cs_);
		this->handler_list_.clear();
		LeaveCriticalSection(&this->cs_); 
	}

	Delegate& operator+=(HandlerType handler) {
		this->Add(handler);
		return *this;
	}

	Delegate& operator-=(HandlerType handler) {
		this->Remove(handler);
		return *this;
	}

	Delegate() {InitializeCriticalSectionAndSpinCount(&this->cs_, 0x00000400);}
	~Delegate() {DeleteCriticalSection(&this->cs_);}
private:
	typedef std::list<HandlerType> HandlerListType;
	HandlerListType handler_list_;
	CRITICAL_SECTION cs_;
};

} //namespace

#endif
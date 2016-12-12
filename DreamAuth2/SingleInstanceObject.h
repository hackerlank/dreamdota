#ifndef SIMGLEINSTANCEOBJECT_H_
#define SIMGLEINSTANCEOBJECT_H_

template <class T>
class SingleInstanceObject {
public:
	typedef SingleInstanceObject<T> InstanceWrapperType;

	static T* GetInstance() {
		if (!SingleInstanceObject<T>::Instance) {
			SingleInstanceObject<T>::Instance = new T();
		}
		return SingleInstanceObject<T>::Instance;
	}

	static void DestoryInstance() {
		if (SingleInstanceObject<T>::Instance) {
			delete SingleInstanceObject<T>::Instance;
			SingleInstanceObject<T>::Instance = NULL;
		}
	}

	SingleInstanceObject() {
		assert(SingleInstanceObject<T>::Instance == NULL);
	}

	~SingleInstanceObject() {
		SingleInstanceObject<T>::Instance = NULL;
	}
private:
	static T* Instance;
};

template <class T>
T* SingleInstanceObject<T>::Instance = NULL;

#endif
#include "stdafx.h"
#ifndef JASS_NATIVE_HOOK_H_
#define JASS_NATIVE_HOOK_H_

#include "Tools.h"
#include "Jass.h"

namespace JassNativeHook {

	template <typename NativeT>
	NativeT SetNativeDetour(const char* name, NativeT detour) {
		NativeT rv = NULL;
		war3::NativeFunc* node = GetNativeFuncNode(name);
		if (node) {
			rv = (NativeT)node->func;
			node->func = detour;
		}
		return rv;
	}

	//未完成，如果以后需要大量使用再完成
	/*
	template <typename ReturnT> 
	struct LastCallResultT {
		ReturnT value;
		ReturnT operator ReturnT() {
			return this->value;
		}
	};

	template <typename NativeT>
	struct NativeDetourList {
		typedef std::list<NativeT> Type;
	};

	template <typename ReturnT>
	extern LastCallResultT<ReturnT> LastCallResult;

	template <typename NativeT>
	extern NativeDetourList<NativeT>::Type PreDetours;

	template <typename NativeT>
	extern NativeDetourList<NativeT>::Type PostDetours;

	template <typename NativeT>
	void AddPreDetour(NativeT detour);

	template <typename NativeT>
	void AddPostDetour(NativeT detour);

	template <typename NativeT>
	void RemoveHook(NativeT detour);

	template <typename NativeT, typename ReturnT>
	ReturnType CallNextHook();
	*/
};

#define SetJassNativeDetour(NAME, DETOUR) \
	JassNativeHook::SetNativeDetour<JASS_PROTOTYPE_##NAME>(#NAME, DETOUR) 

#endif
#pragma once
#include "pch.h"
#include "../Domain/atomic_fn.h"
#include "../Domain/button_event_stream.h"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

template<class T, class Self>
T AtomicFn<T, Self>::Run(Self& self, T(Self::* memFn)()) {	
	auto response = CALL_MEMBER_FN(self, memFn)();	

	return response;
}

template<class Self>
void AtomicFnVoid<Self>::Run(Self& self, void (Self::* memFn)(unsigned long), unsigned long arg) {
	CALL_MEMBER_FN(self, memFn)(arg);
}

template class AtomicFn<ButtonEvent, ButtonEventStream>;
template class AtomicFnVoid<ButtonEventStream>;
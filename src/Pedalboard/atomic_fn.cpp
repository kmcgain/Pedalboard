#pragma once
#include "../Domain/atomic_fn.h"
#include "../Domain/button_event_stream.h"

__inline__ static void disable_interrupts(void)
{
	__asm__ __volatile__("cpsid i" ::);
}

__inline__ static void enable_interrupts(void)
{
	__asm__ __volatile__("cpsie i" ::);
}

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

template<class T, class Self>
T AtomicFn<T, Self>::Run(Self& self, T(Self::* memFn)()) {
	disable_interrupts();
	auto response = CALL_MEMBER_FN(self, memFn)();
	enable_interrupts();

	return response;
}

template<class Self>
void AtomicFnVoid<Self>::Run(Self& self, void (Self::* memFn)(unsigned long), unsigned long arg) {
	disable_interrupts();
	CALL_MEMBER_FN(self, memFn)(arg);
	enable_interrupts();
}

template class AtomicFn<ButtonEvent, ButtonEventStream>;
template class AtomicFnVoid<ButtonEventStream>;
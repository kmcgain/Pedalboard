#pragma once

template<class T, class Self>
class AtomicFn {
public:
	static T Run(Self& self, T (Self::* memFn)());
};

template<class Self>
class AtomicFnVoid {
public:
	static void Run(Self& self, void (Self::* memFn)(unsigned long), unsigned long arg);
};
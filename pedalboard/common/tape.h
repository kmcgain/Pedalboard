#ifndef TAPE_H
#define TAPE_H

#include "maybe.h"

template <class TData>
class Tape {
    public:
        static const int MAX_SIZE; // TODO: Dynamic

        Tape();
        void Add(TData item) volatile;
        Maybe<TData> ReadFromStart(int pos) volatile;
        Maybe<TData> LastAdded() volatile;
        Maybe<TData> TakeFromStart(int pos) volatile;
};

#endif
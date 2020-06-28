#ifndef TAPE_H
#define TAPE_H

#include "maybe.h"

template <class TData>
class Tape {
    public:
        static const int MAX_SIZE; // TODO: Dynamic

        Tape();
        void Add(TData item);
        Maybe<TData> ReadFromStart(int pos);
        Maybe<TData> LastAdded();
        Maybe<TData> TakeFromStart(int pos);
};

#endif
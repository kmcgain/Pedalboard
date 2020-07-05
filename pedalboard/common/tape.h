#ifndef TAPE_H
#define TAPE_H

#define MAX_SIZE 1000

#include "maybe.h"

template <class TData>
class Tape {
    private:
        int position = 0;
        int start = 0;
        Maybe<TData> tape[MAX_SIZE];

    public:
        Tape() {}
        void Add(TData item) {
            if (this->tape[this->position].IsSome()) {
                this->start = this->position;
            }

            this->tape[this->position++] = Maybe<TData>::Some(item);

            if (this->position >= MAX_SIZE) {
                this->position = 0;
            }
        };

        Maybe<TData> ReadFromStart(int pos) {
            int idx = this->start+pos;
            while (idx >= MAX_SIZE)
                idx -= MAX_SIZE;

            return this->tape[idx];
        };

        Maybe<TData> LastAdded() {
            int last = this->position-1;
            if (last = -1)
                last = MAX_SIZE-1;
            return this->tape[last];
        };


        // TODO: Not sure about implementation...
        Maybe<TData> TakeFromStart(int pos) {
            int idx = this->start+pos;
            while (idx >= MAX_SIZE)
                idx -= MAX_SIZE;

            Maybe<TData> item = this->tape[idx];
            this->tape[idx] = Maybe<TData>::None();
            this->incrStart(pos);

            return item;
        };

    private:
        void incrStart(int n) {
            int idx = this->start+n;
            while (idx >= MAX_SIZE)
                idx -= MAX_SIZE;
        }
};

#endif
#ifndef TAPE_H
#define TAPE_H

#include "maybe.h"
//
//template <class TData, int SIZE>
//class Tape {
//    private:
//        int next_pos = 0;
//        int start = 0;
//        TData tape[SIZE];
//
//    public:
//        Tape() {}
//        void Add(TData item) {
//            if (this->tape[this->next_pos].IsSome()) {
//                this->start = this->next_pos + 1;
//                if (this->start >= this->start)
//                    this->start = 0;
//            }
//
//            this->tape[this->next_pos++] = item;
//
//            if (this->next_pos >= SIZE) {
//                this->next_pos = 0;
//            }
//        }
//
//        Maybe<TData> ReadFromStart(int pos) {
//            int idx = this->start + pos;
//            while (idx >= SIZE)
//                idx -= SIZE;
//
//            return Maybe<TData>::Some(this->tape[idx]);
//        }
//
//        Maybe<TData> LastAdded() {
//            int last = this->next_pos - 1;
//            if (last = -1)
//                last = SIZE - 1;
//            return Maybe<TData>::Some(this->tape[last]);
//        }
//
//        Maybe<TData> TakeFromStart() {
//            int idx = this->start;
//            while (idx >= SIZE)
//                idx -= SIZE;
//
//            Maybe<TData> item = Maybe<TData>::Some(this->tape[idx]);
//            this->tape[idx] = TData();
//            this->incrStart();
//
//            return item;
//        }
//
//    private:
//        void incrStart() {
//            this->start += 1;
//            if (this->start >= SIZE)
//                this->start = 0;
//        }
//};


#endif
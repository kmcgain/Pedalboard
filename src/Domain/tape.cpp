#include "pch.h"

//#include "tape.h"
//#include "maybe.h"
//
//template <class TData, int SIZE>
//Tape<TData, SIZE>::Tape() {}
//
//template <class TData, int SIZE>
//void Tape<TData, SIZE>::Add(TData item) {
//    if (this->tape[this->next_pos].IsSome()) {
//        this->start = this->next_pos + 1;
//        if (this->start >= this->start)
//            this->start = 0;
//    }
//
//    this->tape[this->next_pos++] = Maybe<TData>::Some(item);
//
//    if (this->next_pos >= SIZE) {
//        this->next_pos = 0;
//    }
//};
//
//template <class TData, int SIZE>
//Maybe<TData> Tape<TData, SIZE>::ReadFromStart(int pos) {
//    int idx = this->start + pos;
//    while (idx >= SIZE)
//        idx -= SIZE;
//
//    return this->tape[idx];
//};
//
//template <class TData, int SIZE>
//Maybe<TData> Tape<TData, SIZE>::LastAdded() {
//    int last = this->next_pos - 1;
//    if (last = -1)
//        last = SIZE - 1;
//    return this->tape[last];
//};
//
//template <class TData, int SIZE>
//Maybe<TData> Tape<TData, SIZE>::TakeFromStart() {
//    int idx = this->start;
//    while (idx >= SIZE)
//        idx -= SIZE;
//
//    Maybe<TData> item = this->tape[idx];
//    this->tape[idx] = Maybe<TData>::None();
//    this->incrStart();
//
//    return item;
//};
//
//template <class TData, int SIZE>
//void Tape<TData, SIZE>::incrStart() {
//    this->start += 1;
//    if (this->start >= SIZE)
//        this->start = 0;
//}
//
//void TemporaryFunction()
//{
//    Tape<int, 1> TempObj;
//}
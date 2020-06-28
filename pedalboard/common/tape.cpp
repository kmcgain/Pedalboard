#include "maybe.h"

template <class TData>
class Tape {
    private:
        int position = 0;
        int start = 0;

    public:
        Tape() {
        }

        void Add(TData data) {
            if (this->tape[this->position].IsSome()) {
                this->start = this->position;
            }

            this->tape[this->position++] = data;

            if (this->position >= Tape::MAX_SIZE) {
                this->position = 0;
            }
        }

        Maybe<TData> TakeFromStart(int pos) {
            int idx = this->start+pos;
            while (idx >= Tape::MAX_SIZE)
                idx -= Tape::MAX_SIZE;

            TData item = this->tape[idx];
            this->tape[idx] = Maybe<TData>::None();
            this->incrStart();

            return item;
        }

        Maybe<TData> ReadFromStart(int pos) {
            int idx = this->start+pos;
            while (idx >= Tape::MAX_SIZE)
                idx -= Tape::MAX_SIZE;

            return this->tape[idx];
        }

        Maybe<TData> LastAdded() {
            int last = this->position-1;
            if (last = -1)
                last = Tape::MAX_SIZE-1;
            return this->tape[last];
        }

    private:
        void incrStart(int n) {
            int idx = this->start+n;
            while (idx >= Tape::MAX_SIZE)
                idx -= Tape::MAX_SIZE;
        }
};
#ifndef MAYBE_H
#define MAYBE_H

template <class T>
class Maybe {
    private:
        T data;
        bool hasValue;

    public:
        static Maybe<T> &None() {static Maybe<T> maybe = Maybe<T>(T(), false); return maybe; }
        static Maybe<T> &Some(T value) {Maybe<T> maybe = Maybe<T>(value, true); return maybe; }

        Maybe() {
            this->hasValue = false;
        }

        Maybe(T data, bool hasValue) {
            this->data = data;
            this->hasValue = hasValue;
        }
        
    
        bool IsNone() {
            return !this->hasValue;
        }

        bool IsSome() {
            return this->hasValue;
        }

        T Value() {
            return this->data;
        }
    
};

#endif
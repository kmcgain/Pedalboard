
#include <Arduino.h>
#include "button_event.h"
#include "button.h"


Button::Button() {}

// interrupt
void Button::OnPress() {
    // this->buttonEventStream.RecordPress(millis());
}

// interrupt
void Button::OnRelease()  {
    // this->buttonEventStream.RecordRelease(millis());
}

Maybe<ButtonEvent> Button::TakeEvent() {
    return Maybe<ButtonEvent>::None();
    // return this->buttonEventStream.Take();
}

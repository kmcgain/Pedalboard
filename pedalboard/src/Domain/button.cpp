
#include "pch.h"

#include "time_record.h"
#include "button.h"
#include "maybe.h"


Button::Button() {}

// interrupt
void Button::OnPress() {
    this->buttonEventStream.RecordPress(time_millis());
}

// interrupt
void Button::OnRelease()  {    
    this->buttonEventStream.RecordRelease(time_millis());
}

Maybe<ButtonEvent> Button::TakeEvent() {
    return this->buttonEventStream.Take();
}

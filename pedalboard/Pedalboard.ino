//#include <Arduino.h>
//#include <AxeFxControl.h>
//#include "src/function.h"
//#include "src/function_impl.h"
//#include "src/layout_definition.h"
//
//#include "Pedalboard/time_record.h"
#include "src/Domain/layout_manager.h"
#include "src/Domain/interrupt.h"
#include "src/Domain/layout_setup.h"
//#include <Pedalboard/Pedalboard.Domain/layout_setup.h>
//#include <Pedalboard.Domain/interrupt.h>
//
void setup() {
	layoutMgr = new LayoutManager();

	setup_interrupts();
	layoutMgr->init();
}


void loop() {
	// put your main code here, to run repeatedly:

}
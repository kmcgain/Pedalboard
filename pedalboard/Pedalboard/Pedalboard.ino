//#include <Arduino.h>
//#include <AxeFxControl.h>
#include "src/interrupt.h"
#include "src/layout_setup.h"
#include "src/layout_manager.h"
#include "src/constants.h"
//#include "src/function.h"
//#include "src/function_impl.h"
//#include "src/layout_definition.h"
#include "src/layout_setup.h"

void setup() {
	layoutMgr = new LayoutManager();

	setup_interrupts();
	layoutMgr->init();
}



void loop() {
	// put your main code here, to run repeatedly:

}
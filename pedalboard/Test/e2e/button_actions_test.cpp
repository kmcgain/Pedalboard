
#include "pch.h"

#include "../../src/Domain/worker_process.h"

#include "fake_interrupt_registrar.h"
#include "../../src/Domain/constants.h"
#include "../../src/Domain/interrupt_manager.h"
#include "../../src/Domain/interrupt_manager.cpp"

#include "../fake_time_factory.h"

using namespace fakeit;

struct ButtonActionsTest : testing::Test {
    FakeInterruptRegistrar* interruptMgr;
    BoardConstants bc;
    
    ButtonActionsTest() {
        this->bc.Falling = 1;
        this->bc.Rising = 2;
    }
    
    void holdButton(int pinForBtn, int holdTime) {
        this->interruptMgr->fireInterrupt(pinForBtn, bc.Rising);    
        FakeTimeFactory::GetFakeTime()->IncrementTime(holdTime);    
        this->interruptMgr->fireInterrupt(pinForBtn, bc.Falling);
    }
};

TEST_F(ButtonActionsTest, ShouldPerformMidiActionOnButtonPress) {    
    this->interruptMgr = new FakeInterruptRegistrar(bc);
    setup_interrupts(interruptMgr, bc);

    Mock<AxeController> axeControllerMock;   
    Fake(Method(axeControllerMock, SendSceneChange));

    Mock<ScreenFactory> screenFactoryMock;

    AxeController& axeController = axeControllerMock.get();
    ScreenFactory& screenFactory = screenFactoryMock.get();
    auto layoutChanger = new LayoutChanger();
    auto lm = new LayoutManager(new FunctionFactory(layoutChanger, &axeController), layoutChanger, &screenFactory);
    lm->init();
    registerLayoutManager(lm);

    // Press button
    auto pinForSceneSelect1 = 12;
    this->holdButton(pinForSceneSelect1, 100);

    // Process loop
	auto wp = WorkerProcess();
    wp.OneStep();
    
    Verify(Method(axeControllerMock, SendSceneChange)).Once();
}


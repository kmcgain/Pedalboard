
#include "pch.h"

#include "../../src/Domain/worker_process.h"

#include "fake_interrupt_registrar.h"
#include "../../src/Domain/constants.h"
#include "../../src/Domain/interrupt_manager.h"
#include "../../src/Domain/interrupt_manager.cpp"
#include "../../src/Domain/screen.h"

#include "../fake_time_factory.h"
#include "../fake_preset.h"
#include "../impl/pin.h"

using namespace fakeit;

struct ButtonActionsTest : testing::Test {
    FakeInterruptRegistrar* interruptRegistrar;
    BoardConstants bc;
    
    ButtonActionsTest() {
        this->bc.Falling = 3;
        this->bc.Rising = 4;
        this->bc.Change = 2;
    }
    
    void holdButton(int pinForBtn, int holdTime) {    
        setPinState(pinForBtn, true);
        this->interruptRegistrar->fireInterrupt(pinForBtn, bc.Change);
        FakeTimeFactory::GetFakeTime()->IncrementTime(holdTime);    
        setPinState(pinForBtn, false);
        this->interruptRegistrar->fireInterrupt(pinForBtn, bc.Change);
    }
};


void cbTempo(){}

TEST_F(ButtonActionsTest, ShouldPerformMidiActionOnButtonPress) {        
    this->interruptRegistrar = new FakeInterruptRegistrar(bc);
    setup_interrupts(interruptRegistrar, bc);

    Mock<AxeController> axeControllerMock;   
    Fake(Method(axeControllerMock, Init));
    Fake(Method(axeControllerMock, Update));
    Fake(Method(axeControllerMock, SendSceneChange));
    When(Method(axeControllerMock, tunerEngaged)).Return(false);

    Mock<Screen> screenMock;
    Fake(Method(screenMock, DisplayFunction));

    Screen& screen = screenMock.get();
    Mock<ScreenFactory> screenFactoryMock;
    When(Method(screenFactoryMock, CreateScreen)).AlwaysReturn(&screen);

    Mock<Expression> expMock;
    Fake(Method(expMock, OneStep));

    AxeController& axeController = axeControllerMock.get();
    ScreenFactory& screenFactory = screenFactoryMock.get();
    Expression& exp1 = expMock.get();
    Expression& exp2 = expMock.get();

    auto layoutChanger = new LayoutChanger();
    auto lm = new LayoutManager(new FunctionFactory(layoutChanger, &axeController), layoutChanger, &screenFactory, &exp1, &exp2);
    lm->init();
    registerLayoutManager(lm);

    TunerData tunerData;

    start_recording();

    // Press button
    auto pinForSceneSelect1 = 12;
    this->holdButton(pinForSceneSelect1, 100);

    //Process loop
	auto wp = WorkerProcess(&axeController, &exp1, &exp2);
    wp.OneStep(new FakePreset(), tunerData);
    
    Verify(Method(axeControllerMock, SendSceneChange)).Once();
}


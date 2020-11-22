#include "pch.h"

#include "..\src\Domain\layout_manager.h"

using namespace fakeit;

void mockFunctionFactory(Mock<FunctionFactory>& ffMock, Function& fn) {
	When(Method(ffMock, LayoutSelect)).AlwaysReturn(&fn);
	When(Method(ffMock, LayoutDecrement)).AlwaysReturn(&fn);
	When(Method(ffMock, SceneSelect)).AlwaysReturn(&fn);
	When(Method(ffMock, SceneIncrement)).AlwaysReturn(&fn);
	When(Method(ffMock, SceneDecrement)).AlwaysReturn(&fn);
	When(Method(ffMock, ExpToggle)).AlwaysReturn(&fn);
	When(Method(ffMock, TunerToggle)).AlwaysReturn(&fn);
	When(Method(ffMock, TapTempo)).AlwaysReturn(&fn);
	When(Method(ffMock, PresetIncrement)).AlwaysReturn(&fn);
	When(Method(ffMock, PresetDecrement)).AlwaysReturn(&fn);
	When(Method(ffMock, PresetDisplay)).AlwaysReturn(&fn);
	When(Method(ffMock, PresetFullSelect)).AlwaysReturn(&fn);
	When(Method(ffMock, Mute)).AlwaysReturn(&fn);
	When(Method(ffMock, Effect)).AlwaysReturn(&fn);
}

TEST(LayoutManagerTest, ShouldRegisterInterruptsAvoidingUnwantedPins) {
	Mock<Function> function1Mock;
	Mock<Function> function2Mock;


	Fake(Method(function1Mock, Execute));
	When(Method(function1Mock, Name)).Return("F1");
	Fake(Method(function2Mock, Execute));
	When(Method(function2Mock, Name)).Return("F2");

	Mock<Screen> screenMock;
    Fake(Method(screenMock, DisplayFunction));

    Screen& screen = screenMock.get();
	Mock<ScreenFactory> screenFactoryMock;
	When(Method(screenFactoryMock, CreateScreen)).AlwaysReturn(&screen);
	ScreenFactory& screenFactory = screenFactoryMock.get();

	Function& functionExpectingCall = function1Mock.get();
	Function& functionNotExpectingCall = function2Mock.get();
	
	Mock<FunctionFactory> functionFactoryMock;
	When(Method(functionFactoryMock, LayoutIncrement)).AlwaysReturn(&functionExpectingCall);
	mockFunctionFactory(functionFactoryMock, functionNotExpectingCall);

	FunctionFactory & funcFac = functionFactoryMock.get();
	Mock<Expression> expMock;
	auto layoutChanger = new LayoutChanger();
	Expression& exp1 = expMock.get();
	
	auto mgr = new LayoutManager(&funcFac, layoutChanger, &screenFactory, &exp1, &exp1);

	mgr->init();

	// Top-left
	mgr->OnPress(2, 0);
	mgr->OnRelease(2, 0);

	mgr->CurrentLayout()->ProcessOutstanding();

	Verify(Method(function1Mock, Execute)).Once();
	Verify(Method(function2Mock, Execute)).Never();
}
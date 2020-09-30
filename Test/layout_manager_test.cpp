#include "pch.h"

#include "..\src\Domain\layout_manager.h"

using namespace fakeit;

TEST(LayoutManagerTest, ShouldRegisterInterruptsAvoidingUnwantedPins) {
	Mock<Function> function1Mock;
	Mock<Function> function2Mock;
	Mock<FunctionFactory> functionFactoryMock;


	Fake(Method(function1Mock, Execute));
	When(Method(function1Mock, Name)).Return("F1");
	Fake(Method(function2Mock, Execute));
	When(Method(function2Mock, Name)).Return("F2");

	Mock<ScreenFactory> screenFactoryMock;
	ScreenFactory& screenFactory = screenFactoryMock.get();

	Function& function1 = function1Mock.get();
	Function& function2 = function2Mock.get();
	When(Method(functionFactoryMock, LayoutSelect).Using(1)).Return(&function1);
	When(Method(functionFactoryMock, LayoutSelect).Using(2)).Return(&function2);

	FunctionFactory & funcFac = functionFactoryMock.get();
	LayoutManager mgr = LayoutManager(&funcFac, new LayoutChanger(), &screenFactory);

	mgr.init();

	mgr.OnPress(0, 0);
	mgr.OnRelease(0, 0);

	mgr.CurrentLayout()->ProcessOutstanding();

	Verify(Method(function1Mock, Execute)).Once();
	Verify(Method(function2Mock, Execute)).Never();
}
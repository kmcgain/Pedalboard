# How to add a new function

The example I'll use here is adding a mute function. 

## Requirements
* This function should by default by unmuted
* The screen should display 'Mute' when unmuted
* The screen should display 'Unmute' when muted
* Pressing the footswitch should:
  * Change the state from muted to unmuted and vice-versa
  * Send a CC message to Axe FX for CC# 100 with a value of 127 when unmuting and a value of 0 when muting

## Steps
1. Define a new function type in Domain/function/function_type.h and assign the next enum number
   1. Eg. ftMute = 14
2. Define a FunctionState type to store our Muted/Unmuted state. This will be stored against the Control and can be accessed during button execution or screen updates
   1. Function states are designed to be reused across functions so keep them generic. In our case we don't have a boolean based state so we introduce a ToggleFunctionState in Domain/function/function_state.h
   2. The new class should inherit from public Function
   3. It should have a boolean field to represet our toggle position and appropriate functions to modify / return this state.
3. Define a new function class in Domain/function called mute.h
   1. All functions must implement the Name, Type public functions and execute, createState protected functions
      1. Name can be "Mute"
      2. Type should be the new enum value ftMute
      3. createState will return the new ToggleFunctionState
      4. execute should implement the action to run when the button is pressed. In our case we know we need to update our toggle state so the screen can be updated, but also we need to talk to our AxeFx so we'll delegate to the AxeController for this job
4. Add a 'mute' function to Domain/axe_controller.h that accepts a boolean indicating if we should send a mute or unmute
5. Add a 'mute' function to Pedalboard/Axe/axe_controller.cpp
   1. The mute function will call axe.sendControlChange with a CC number of 100 and cc value of 127 or 0 based on toggle flag
6. Modify Domain/function/function_factory.h to add a Mute() function
7. Modify Domain/function/function_factory.cpp to add a Mute() function
   1. This will return a new instance of the MuteFunction we previously defined
8. Modify Domain/layout_definition.h to add a new FunctionName enum member for mute
   1. This is different to the function type - for example with scene selection we have multiple scene selection functions all of the same function type
9.  Modify Domain/layout_manager.cpp setup_functions function to call the function factory and store the mute function instance in the functions array
   2. this->functions[FunctionName::mute] = functionFactory->Mute();
10. Modify Domain/layout_manager.h functions field to increase the array size
   3. eg. Function* functions[32]; => Function* functions[33];
11. Update the Display logic in Pedalboard/tft_screen.cpp
    1. The DisplayFunction has a switch statement, add a case for the new function type ftMute
    2. You can cast the provided functionState to your ToggleFunctionState because you know Mute functions are associated with this kind of State
    3. Use the toggle state to then draw text on the screen using appropriate background / foreground colour
    4. You can switch colours based on the state as well
12. Add the new function to a layout
    1.  Modify Domain/layout_definition.h and include FunctionName::mute where you like
13. Upload the new code by running upload.ps1


That's it! A new function is now available
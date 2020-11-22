#include "pch.h"



int main(int argc, char **argv) {
  //if( !IsDebuggerPresent() )
  //{
    // _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    // _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

    // _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    // _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

    // _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    // _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    // _set_abort_behavior(_CALL_REPORTFAULT, _CALL_REPORTFAULT);

  //}

  
  
  
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

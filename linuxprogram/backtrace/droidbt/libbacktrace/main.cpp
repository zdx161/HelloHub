#include <backtrace/Backtrace.h>
#include <stdio.h>

int main() {

   Backtrace* backtrace(Backtrace::Create(BACKTRACE_CURRENT_PROCESS, -1));
    
    if (!backtrace->Unwind(1)) {
        printf("%s: Failed to unwind callstack.", __FUNCTION__);
    }
    for (size_t i = 0; i < backtrace->NumFrames(); i++) {
      printf("%s\n",backtrace->FormatFrameData(i).c_str());
    }

    return 0;
}

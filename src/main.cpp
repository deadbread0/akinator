#include <stdio.h>
#include "choose_mode.h"

int main(const int argc, const char* argv[])
{
    const char* mode = argc > 1 ? argv[1] : "-h";
    ChooseModeAndRunFunctions(mode);
    return 0;
}


#include <stdio.h>

void ChooseModeAndRunFunctions(const char* mode);

int main(const int argc, const char* argv[])
{
    const char* mode = argc > 0? argv[1] : "-h";
    ChooseModeAndRunFunctions(mode);
    return 0;
}


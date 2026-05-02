#include <cstdio>

#ifndef TYPES
#include "types.h"
#endif

#ifndef USER
#include "functions_for_user.h"
#endif

#ifndef BASE
#include "work_with_data_base.h"
#endif

#ifndef TREE
#include "functions_for_tree.h"
#endif

#include "akinator_dump.h"

static const int MAX_LEN_OF_FLAG = 2;
static const int CAPACITY = 10;

void DescriptionMode();
void GuessMode();
void Help();
void MenuMode();
void UnknownMode();
void DataBaseDumpMode();
void CompareMode();

static flag_t Flags[] = {{(char*)"-h", Help, (char*)"the flag will show all flags and their purpose"},
                  {(char*)"-d", DescriptionMode, (char*)"show a description of object"},
                  {(char*)"-g", GuessMode, (char*)"standard akinator"},
                  {(char*)"-b", DataBaseDumpMode, (char*)"show data base"},
                  {(char*)"-c", CompareMode, (char*)"compare 2 elements"},
                  {(char*)"-m", MenuMode, (char*)"use this flag if you want work with different modes"}};

static modee_t ProgramMode[] = {{GUESS, GuessMode, (char*)"standard akinator"},
                        {DESCRIPTION, DescriptionMode, (char*)"show a description of object"},
                        {DATA_BASE, DataBaseDumpMode, (char*)"show data base"},
                        {COMPARE, CompareMode, (char*)"compare 2 objects"},
                        {UNKNOWN, UnknownMode, (char*)""}};//unknown всегда должен быть последним

void ChooseModeAndRunFunctions(const char* mode);
node_t* FillTreeFromDataBase(char* data, const char* const_filee_name, int* size, errors_t* error);
void EndOfMode(errors_t* error, node_t* first_node);
mode AskUserAboutModeAndGetAnswer();

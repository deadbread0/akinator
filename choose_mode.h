#include <cstdio>
#include "types.h"
#include "const.h"

char* PutTreeFromFileToBuffer(errors_t* error, int size);
node_t* ReadNode(int* pos, char* buffer, errors_t* error);
void FillPrevValues(node_t* node);
int GetSizeOfInputFile(const char* file_name);
tree_elem_t* MakeStatementFromStr(tree_elem_t* str);

void DescriptionMode();
void GuessMode();
void Help();

flag_t Flags[] = {{(char*)"-h", Help, (char*)"the flag will show all flags and their purpose"},
                  {(char*)"-d", DescriptionMode, (char*)"show a description of object"},
                  {(char*)"-g", GuessMode, (char*)"standard akinator"}};

node_t* MakeFirstNode(errors_t*);
void DumpTree(const node_t* node, FILE* filee);
void FreeTree(node_t* node);
void PrintNode(const node_t* node);
answer_t GetShortAnswer();
node_t* ChooseNextOperation(answer_t answer, node_t* node, bool* user_wants_use_program, errors_t* errors);
bool DecideProgramRestart(answer_t answer);
void AskUserAboutNewCharacterAndMakeNewNode(node_t* node, errors_t* error);
answer_t InviteToUseProgramAgain();
tree_elem_t* MakeQuestionFromStr(tree_elem_t* str);
void VerifyProgram(errors_t* error);
node_t* FindNodeByValue(tree_elem_t* elem, node_t* node, errors_t* error);
char* GetElemFromUser(errors_t* error);
void ChooseModeAndRunFunctions(const char* mode);
void AddNewElemInDataBase(node_t* node, FILE* filee);
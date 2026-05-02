#define USER
#include <cstdio>
#include <cstdlib>

#ifndef TYPES
#include "types.h"
#endif

static const int MAX_LEN_OF_SHORT_ANSWER = 3;
static const int MAX_LEN_OF_NAME = 100;
static const int MAX_LEN_OF_DESCRIPTIONN = 1000;

node_t* ChooseNextOperation(answer_t answer, node_t* node, bool* user_wants_use_program, errors_t* errors, const char* function);
bool DecideProgramRestart(answer_t answer);
void AskUserAboutNewCharacterAndMakeNewNode(node_t* node, errors_t* error);
void AskUserAboutNameAndGetAnswer(errors_t* error, tree_elem_t* name_of_new_character);
void AskUserAboutDeacriptionAndGetAnswer(errors_t* error, tree_elem_t* name_of_new_character, tree_elem_t* description_of_new_character, node_t* node);
tree_elem_t* MakeQuestionFromStr(tree_elem_t* str);
tree_elem_t* MakeStatementFromStr(tree_elem_t* str);
answer_t InviteToUseProgramAgain(const char* function);
answer_t GetShortAnswer();
char* GetElemFromUser(errors_t* error);


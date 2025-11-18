#include <cstdio>
#include "types.h"
#include "const.h"

node_t* MakeFirstNode(errors_t*);
answer_t GetShortAnswer();
node_t* ChooseNextOperation(answer_t answer, node_t* node, bool* user_wants_use_program, errors_t* errors);
bool DecideProgramRestart(answer_t answer);
void AskUserAboutNewCharacterAndMakeNewNode(node_t* node, errors_t* error);
answer_t InviteToUseProgramAgain();
tree_elem_t* MakeQuestionFromStr(tree_elem_t* str);
void AskUserAboutNameAndGetAnswer(errors_t* error, tree_elem_t* name_of_new_character);
void AskUserAboutDeacriptionAndGetAnswer(errors_t* error, tree_elem_t* name_of_new_character, tree_elem_t* description_of_new_character, node_t* node);

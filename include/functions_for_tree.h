#define TREE
#include <cstdlib>

#ifndef TYPES
#include "types.h"
#endif

static const int MAX_LEN_OF_DESCRIPTION = 1000;

void FreeTree(node_t* node);
node_t* MakeFirstNode(errors_t* error);
node_t* FindNodeByValue(tree_elem_t* elem, node_t* node, errors_t* error);
void VerifyProgram(errors_t* error);
node_t* MakeNode(errors_t* error);
void FillPrevValues(node_t* node);

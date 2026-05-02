#define BASE

#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef TYPES
#include "types.h"
#endif

#ifndef TREE
#include "functions_for_tree.h"
#endif

static const char* const_filee_name = "data_base.txt";
static const char* NILNIL = "nil nil ";

char* PutTreeFromFileToBuffer(errors_t* error, int size);
int GetSizeOfInputFile(const char* file_name);
node_t* ReadNode(int* pos, char* buffer, errors_t* error);
tree_elem_t* ReturnDataOfNode(int* pos, char* buffer, errors_t* error);
void AddNewElemInDataBase(node_t* node, FILE* filee);

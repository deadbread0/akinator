#include "types.h"
#include "const.h"
#include <sys/types.h>
#include <sys/stat.h>

const char* const_filee_name = "data_base.txt";

node_t* MakeNode(errors_t* error);
void VerifyProgram(errors_t* error);
tree_elem_t* ReturnDataOfNode(int* pos, char* buffer, errors_t* error);


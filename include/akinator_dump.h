#include <cstdio>

#ifndef TYPES
#include "types.h"
#endif

void DumpTree(const node_t* node, FILE* filee);
void PrintNode(const node_t* node);
void DumpGraphNode(const node_t* node, FILE* filee);
void MakeCommunicationBetweenNodes(const node_t* node, FILE* filee);

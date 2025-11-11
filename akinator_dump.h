#include <cstdio>
typedef char* tree_elem_t;

struct node_t {
    tree_elem_t data;
    node_t* left;
    node_t* right;
};

void DumpTree(const node_t* node, FILE* filee);
void DumpGraphNode(const node_t* node, FILE* filee);
void MakeCommunicationBetweenNodes(const node_t* node, FILE* filee);
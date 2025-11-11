#include <stdio.h>
#include <assert.h>

#include "akinator_dump.h"

void DumpTree(const node_t* node, FILE* filee)
{
    assert(node != nullptr);
    assert(filee != nullptr);
    
    fprintf(filee, "digraph {\n");
    DumpGraphNode(node, filee);
    MakeCommunicationBetweenNodes(node, filee);
    fprintf(filee, "}\n");

}

void PrintNode(const node_t* node)
{
    assert(node != nullptr);
    
    printf("%s?\n", node->data);
}

void DumpGraphNode(const node_t* node, FILE* filee)
{
    assert(node != nullptr);
    assert(filee != nullptr);

    if (node->left)
        DumpGraphNode(node->left, filee);
    if (node->right)
        DumpGraphNode(node->right, filee);
    fprintf(filee, "%u [shape=Mrecord; style = filled; fillcolor = \"#c0f2f2ff\"; color = \"#4682B4\"; rankdir=TB; label = \"{%x}|{%s}|{no\\n %x|yes\\n %x}\"];\n", &node->data, &node->data, node->data, node->left, node->right);
}

void MakeCommunicationBetweenNodes(const node_t* node, FILE* filee)
{
    assert(node != nullptr);
    assert(filee != nullptr);

    if (node->left)
    {
        fprintf(filee, "%u -> %u ", &node->data, node->left);
        MakeCommunicationBetweenNodes(node->left, filee);
    }

    if (node->right)
    {
        fprintf(filee, "%u -> %u ", &node->data, node->right);
        MakeCommunicationBetweenNodes(node->right, filee);
    }
}

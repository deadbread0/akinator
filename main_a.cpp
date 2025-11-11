#include <stdio.h>
#include <assert.h>
#include <cstring>

#include "main_a.h"

int main()
{
    node_t* first_node = MakeFirstNode();
    node_t* node = first_node;
    bool user_wants_use_program = true;

    while (user_wants_use_program)
    {
        PrintNode(node);
        answer_t answer = GetShortAnswer();
        node_t* next_node = ChooseNextOperation(answer, node, &user_wants_use_program);
        if (next_node == node->left || next_node == node->right)
            node = next_node;
        else
            node = first_node;
    };

    FILE* dump_filee = fopen("dump_akinator.txt", "w");
    DumpTree(first_node, dump_filee);
    // FreeTree(first_node);
    return 0;
}



void FreeTree(node_t* node)
{
    assert(node != nullptr);

    if (node->left)
        FreeTree(node->left);
    if (node->right)
        FreeTree(node->right);
    // free(node);
}
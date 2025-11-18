#include <stdio.h>
#include <assert.h>

#include "functions_for_tree.h"
#include <cstring>

void FreeTree(node_t* node)
{
    assert(node != nullptr);

    if (node->left)
        FreeTree(node->left);
    if (node->right)
        FreeTree(node->right);
    free(node);
}

node_t* MakeFirstNode(errors_t* error)
{
    assert(error != nullptr);

    node_t* new_node = (node_t*)calloc(1, sizeof(node_t));

    if (new_node == nullptr)
        *error = MEMORY_ALLOCATION;

    VerifyProgram(error);

    new_node->data = (char*)"unknown thing?";
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->prev = nullptr;

    return new_node;///
}

node_t* FindNodeByValue(tree_elem_t* elem, node_t* node, errors_t* error)
{
    assert(elem != nullptr);
    assert(node != nullptr);
    assert(error != nullptr);

    node_t* this_node = (node_t*)calloc(1, sizeof(node_t*));

    if (!this_node)
        *error = MEMORY_ALLOCATION;
    
    int f = strncmp(elem, node->data, MAX_LEN_OF_DESCRIPTION);

    if (f == 0)
        return node;

    if (node->left)
    {
        this_node = FindNodeByValue(elem, node->left, error);
        if (this_node)
            return this_node;
    }

    if (node->right)
    {
        this_node = FindNodeByValue(elem, node->right, error);
        if (this_node)
            return this_node;
    }

    return nullptr;
} 

void VerifyProgram(errors_t* error)
{
    assert(error != nullptr);

    if (*error == MEMORY_ALLOCATION)
    {
        printf("ohh no, it seems you have encountered a memory allocation error. \n"
               "try restarting the program\n");
    }

    else if (*error == FILE_DIDNT_OPEN)
    {
        printf("file didn't open, try again(\n");
    }

    else if (*error == NO_SUCH_NODE)
    {
        printf("sorry, this character isn't in the database yet.\n");
    }

    else if (*error == PROBLEMS_WITH_READING_FILE)
    {
        printf("there is a problem reading data from the file, please try again later.\n");
    }
}

node_t* MakeNode(errors_t* error)
{
    assert(error != nullptr);

    node_t* new_node = (node_t*)calloc(1, sizeof(node_t));

    if (!new_node)
        *error = MEMORY_ALLOCATION;

    new_node->data = nullptr;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->prev = nullptr;

    return new_node;
}

void FillPrevValues(node_t* node)
{
    assert(node != nullptr);

    if (node->left)
    {
        (node->left)->prev = node;
        FillPrevValues(node->left);
    }
    if (node->right)
    {
        (node->right)->prev = node;
        FillPrevValues(node->right);
    }
}
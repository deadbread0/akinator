#include <stdio.h>
#include <assert.h>
#include <cstring>
#include "work_with_data_base.h"

char* PutTreeFromFileToBuffer(errors_t* error, int size)
{
    assert(error != nullptr);

    char* buffer = (char*)calloc(size, sizeof(char));

    if (!buffer)
        *error = MEMORY_ALLOCATION;

    FILE* filee = fopen(const_filee_name, "r");
    buffer = fgets(buffer, size, filee);

    if (!buffer)
        *error = PROBLEMS_WITH_READING_FILE;

    fclose(filee);
    return buffer;
}

int GetSizeOfInputFile(const char* file_name)
{
    assert(file_name != nullptr);

    struct stat StructStat;
    stat(file_name, &StructStat);
    return StructStat.st_size;
}

node_t* ReadNode(int* pos, char* buffer, errors_t* error)
{
    assert(pos != nullptr);
    assert(buffer != nullptr);
    assert(error != nullptr);

    if (buffer[*pos] == ' ')
        (*pos)++;

    if (buffer[*pos] == '(')
    {
        node_t* new_node = MakeNode(error);
        VerifyProgram(error);
        (*pos)++;

        while(buffer[*pos] != '\"')
            (*pos)++;

        (*pos)++;
        new_node->data = ReturnDataOfNode(pos, buffer, error);
        (*pos)++;

        new_node->left = ReadNode(pos, buffer, error);
        new_node->right = ReadNode(pos, buffer, error);

        while(buffer[*pos] != ')')
            (*pos)++;

        (*pos)++;

        return new_node;
    }

    if (buffer[*pos] == 'n' && buffer[(*pos) + 1] == 'i' && buffer[(*pos) + 2] == 'l')
        (*pos) += strlen("nil");

    return nullptr;
}

tree_elem_t* ReturnDataOfNode(int* pos, char* buffer, errors_t* error)
{
    assert(pos != nullptr);
    assert(buffer != nullptr);

    tree_elem_t* node_data = (tree_elem_t*)calloc(MAX_LEN_OF_DESCRIPTION, sizeof(tree_elem_t));

    if (!node_data)
        *error = MEMORY_ALLOCATION;

    int i = 0;

    while(buffer[*pos] != '\"')
    {        
        node_data[i] = buffer[*pos];
        i++;
        (*pos)++;
    }

    (*pos)++;
    return node_data;
}

void AddNewElemInDataBase(node_t* node, FILE* filee)
{
    assert(node != nullptr);
    assert(filee != nullptr);

    fprintf(filee, "(");
    fprintf(filee, " \"%s\" ", node->data);

    if (!node->left && !node->right)
        fprintf(filee, "%s", NILNIL);
        
    if (node->left)
        AddNewElemInDataBase(node->left, filee);
        
    if (node->right)
        AddNewElemInDataBase(node->right, filee);
        
    fprintf(filee, ")");
}
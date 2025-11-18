#include <stdio.h>
#include <cstring>

#include "choose_mode.h"
#include <cstdlib>

void ChooseModeAndRunFunctions(const char* mode)
{
    int amount_of_called_func = 0;
    int flag_arr_size = sizeof(Flags) / sizeof(Flags[0]);

    for (int i = 0; i < flag_arr_size; i++)
    {
        int res_of_comparison = strncmp(Flags[i].flag, mode, MAX_LEN_OF_FLAG);

        if (res_of_comparison == 0)
        {
            func_ptr pt = Flags[i].ptr;
            pt();
            amount_of_called_func++;
        }

    }

    if (amount_of_called_func == 0)
        printf("enter \"-h\" pls\n");
}

void Help()
{
    int amount_of_flags = sizeof(Flags) / sizeof(Flags[0]);

    for (int i = 0; i < amount_of_flags; i++)
        printf("%s %s\n", Flags[i].flag, Flags[i].description);
}

void DescriptionMode()
{
    const char* const_filee_name = "data_base.txt";
    errors_t error = NO_ERRORS;

    int size = GetSizeOfInputFile(const_filee_name);
    char* data = (char*)calloc(size + 1, sizeof(char));

    if (!data)
        error = MEMORY_ALLOCATION;

    data = PutTreeFromFileToBuffer(&error, size + 1);
    int pos = 0;
    node_t* nodee = ReadNode(&pos, data, &error);
    FillPrevValues(nodee);

    node_t* node = nodee;
    node_t* first_node = nodee;
    bool user_wants_use_program = true;

    while (user_wants_use_program && error == NO_ERRORS)//
    {
        printf("enter subject\n");
        tree_elem_t* elem_from_user = GetElemFromUser(&error);
        tree_elem_t* last = elem_from_user;
        node_t* prev_node = nullptr, *current_node = nullptr;

        current_node = FindNodeByValue(elem_from_user, first_node, &error);
        prev_node = current_node->prev;

        if (prev_node == nullptr)
            error = NO_SUCH_NODE;

        VerifyProgram(&error);
        printf("%s is:\n", elem_from_user);

        while (prev_node != nullptr)
        {
            if (strncmp(last, (prev_node->left)->data, MAX_LEN_OF_DESCRIPTION) == 0)//
                printf("not ");

            last = prev_node->data;/// 
            printf("%s\n", MakeStatementFromStr(prev_node->data));

            prev_node = prev_node->prev;

        }

        VerifyProgram(&error);

        answer_t answer = InviteToUseProgramAgain();
        user_wants_use_program = DecideProgramRestart(answer);

        error = NO_ERRORS;
    }

    VerifyProgram(&error);

    FILE* dump_filee = fopen("dump_akinator.txt", "w");
    if (!dump_filee)
        error = FILE_DIDNT_OPEN;
    VerifyProgram(&error);

    DumpTree(first_node, dump_filee);
    FreeTree(first_node);
}


void GuessMode()
{
    const char* const_filee_name = "data_base.txt";
    errors_t error = NO_ERRORS;

    int size = GetSizeOfInputFile(const_filee_name);
    char* data = (char*)calloc(size + 1, sizeof(char));///
    data = PutTreeFromFileToBuffer(&error, size + 1);
    int pos = 0;
    node_t* nodee = ReadNode(&pos, data, &error);
    FillPrevValues(nodee);

    node_t* node = nodee;
    node_t* first_node = nodee;
    bool user_wants_use_program = true;

    while (user_wants_use_program && error == NO_ERRORS)
    {
        PrintNode(node);
        answer_t answer = GetShortAnswer();
        node_t* next_node = ChooseNextOperation(answer, node, &user_wants_use_program, &error);
        if ((next_node == node->left || next_node == node->right) && next_node)
            node = next_node;
        else
            node = nodee;
    };
    VerifyProgram(&error);

    FILE* dump_filee = fopen("dump_akinator.txt", "w");//copypaste
    if (!dump_filee)
        error = FILE_DIDNT_OPEN;
    VerifyProgram(&error);

    FILE* filee = fopen(const_filee_name, "w");
    AddNewElemInDataBase(first_node, filee);
    DumpTree(first_node, dump_filee);
    
    FreeTree(first_node);
}

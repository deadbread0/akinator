#include <stdio.h>
#include <cstring>
#include <assert.h>
#include <cstdlib>

#include "choose_mode.h"

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

node_t* FillTreeFromDataBase(char* data, const char* const_filee_name, int* size, errors_t* error)
{
    if (!data)
        *error = MEMORY_ALLOCATION;

    data = PutTreeFromFileToBuffer(error, (*size) + 1);
    int pos = 0;
    node_t* nodee = ReadNode(&pos, data, error);
    FillPrevValues(nodee);

    return nodee;
}

void DescriptionMode()
{
    const char* function = __func__;
    const char* const_filee_name = "data_base.txt";
    errors_t error = NO_ERRORS;

    int size = GetSizeOfInputFile(const_filee_name);
    char* data = (char*)calloc(size + 1, sizeof(char));

    node_t* first_node = FillTreeFromDataBase(data, const_filee_name, &size, &error);
    bool user_wants_use_program = true;

    while (user_wants_use_program && error == NO_ERRORS)//
    {
        printf("enter subject\n");
        tree_elem_t* elem_from_user = GetElemFromUser(&error);
        tree_elem_t* last = elem_from_user;
        node_t* prev_node = nullptr, *current_node = nullptr;

        current_node = FindNodeByValue(elem_from_user, first_node, &error);

        if (current_node == nullptr)
        {
            error = NO_SUCH_NODE;
            VerifyProgram(&error);
            answer_t answer = InviteToUseProgramAgain(function);
            user_wants_use_program = DecideProgramRestart(answer);
            error = NO_ERRORS;
            continue;
        }

        prev_node = current_node->prev; 

        VerifyProgram(&error);
        printf("%s is:\n", elem_from_user);

        while (prev_node != nullptr)
        {
            if (strncmp(last, (prev_node->left)->data, MAX_LEN_OF_DESCRIPTION) == 0)
                printf("not ");

            last = prev_node->data;
            printf("%s\n", MakeStatementFromStr(prev_node->data));

            prev_node = prev_node->prev;

        }

        VerifyProgram(&error);

        answer_t answer = InviteToUseProgramAgain(function);
        user_wants_use_program = DecideProgramRestart(answer);

        error = NO_ERRORS;
    }

    VerifyProgram(&error);
    EndOfMode(&error, first_node);
}


void GuessMode()
{
    const char* function = __func__;
    const char* const_filee_name = "data_base.txt";
    errors_t error = NO_ERRORS;

    int size = GetSizeOfInputFile(const_filee_name);
    char* data = (char*)calloc(size + 1, sizeof(char));

    node_t* first_node = FillTreeFromDataBase(data, const_filee_name, &size, &error);
    node_t* node = first_node;
    bool user_wants_use_program = true;

    while (user_wants_use_program && error == NO_ERRORS)
    {
        PrintNode(node);
        answer_t answer = GetShortAnswer();
        node_t* next_node = ChooseNextOperation(answer, node, &user_wants_use_program, &error, function);

        if ((next_node == node->left || next_node == node->right) && next_node)
            node = next_node;
        else
            node = first_node;
    };

    FILE* filee = fopen(const_filee_name, "w");
    AddNewElemInDataBase(first_node, filee);
    VerifyProgram(&error);

    EndOfMode(&error, first_node);
}

void MenuMode()
{
    const char* function = __func__;
    bool user_wants_use_program = true;
    int amount_of_modes = sizeof(ProgramMode) / sizeof(ProgramMode[0]);

    while (user_wants_use_program)
    {
        mode users_mode = AskUserAboutModeAndGetAnswer();

        for (int i = 0; i < amount_of_modes; i++)
        {
            if (ProgramMode[i].modee == users_mode)
                ProgramMode[i].ptr();
        }

        answer_t answer = InviteToUseProgramAgain(function);
        user_wants_use_program = DecideProgramRestart(answer);
    }

}

void CompareMode()
{
    const char* function = __func__;
    const char* const_filee_name = "data_base.txt";
    errors_t error = NO_ERRORS;

    int size = GetSizeOfInputFile(const_filee_name);
    char* data = (char*)calloc(size + 1, sizeof(char));

    node_t* first_node = FillTreeFromDataBase(data, const_filee_name, &size, &error);
    bool user_wants_use_program = true;

    while (user_wants_use_program && error == NO_ERRORS)
    {
        printf("enter first subject\n");
        tree_elem_t *elem_from_user1 = GetElemFromUser(&error);

        printf("enter second subject\n");
        tree_elem_t *elem_from_user2 = GetElemFromUser(&error);

        tree_elem_t *last1 = elem_from_user1, *last2 = elem_from_user2;
        node_t *prev_node1 = nullptr, *current_node1 = nullptr, 
               *prev_node2 = nullptr, *current_node2 = nullptr;

        current_node1 = FindNodeByValue(elem_from_user1, first_node, &error);
        current_node2 = FindNodeByValue(elem_from_user2, first_node, &error);

        if (current_node1 == nullptr || current_node2 == nullptr)
        {
            error = NO_SUCH_NODE;
            VerifyProgram(&error);
            error = NO_ERRORS;
            continue;
        }

        prev_node1 = current_node1->prev; 
        prev_node2 = current_node1->prev;

        VerifyProgram(&error);

        node_t** arr_of_nodes1 = (node_t**)calloc(CAPACITY, sizeof(node_t*));
        node_t** arr_of_nodes2 = (node_t**)calloc(CAPACITY, sizeof(node_t*));///verify

        int counter1 = 0, counter2 = 0;

        while (prev_node1 != nullptr)
        {
            arr_of_nodes1[counter1] = prev_node1;
            prev_node1 = prev_node1->prev;
            printf("(%s)\n", prev_node1->data);
            counter1++;
        }

        while (prev_node2 != nullptr)
        {
            arr_of_nodes2[counter2] = prev_node2;
            printf("*(%s)\n", prev_node1->data);
            prev_node2 = prev_node2->prev;
            counter2++;
        }

        int index_common1 = 0, index_common2 = 0;

        for (int i = 1; i <= counter1; i++)
        {
            for (int j = 1; j <= counter2; j++)
            {
                printf("%s - %s\n", arr_of_nodes1[counter1 - i]->data, arr_of_nodes2[counter2 - j]->data);
                if (arr_of_nodes1[counter1 - i] == arr_of_nodes2[counter2 - j])
                {
                    index_common1 = counter1 - i, index_common2 = counter2 - j;
                    break;
                } 
            }
        }

        VerifyProgram(&error);

        answer_t answer = InviteToUseProgramAgain(function);
        user_wants_use_program = DecideProgramRestart(answer);

        error = NO_ERRORS;
    }

    VerifyProgram(&error);
    EndOfMode(&error, first_node);
}

void DataBaseDumpMode()
{
    system("dot -Tpng dump_akinator.dot -o dump_akinator.png");
    system(".\\base_dump.htm ");
}

void UnknownMode()
{
    printf("you entered unknown mode, try again\n");
    MenuMode();
}

void EndOfMode(errors_t* error, node_t* first_node)
{
    assert(error != nullptr);
    assert(first_node != nullptr);

    FILE* dump_filee = fopen("dump_akinator.dot", "w");
    if (!dump_filee)
        *error = FILE_DIDNT_OPEN;
    VerifyProgram(error);

    DumpTree(first_node, dump_filee);
    FreeTree(first_node);
}

mode AskUserAboutModeAndGetAnswer()
{
    printf("Choose mode\n");
    int amount_of_modes = sizeof(ProgramMode) / sizeof(ProgramMode[0]);

    for (int i = 0; i < amount_of_modes - 1; i++)
        printf("%d - %s\n", ProgramMode[i].modee, ProgramMode[i].description);

    int answer = 0, counter = 0;
    scanf("%d", &answer);
    for (int i = 0; i < amount_of_modes - 1; i++)
    {
        if (answer == ProgramMode[i].modee)
        {
            return ProgramMode[i].modee;
        }
    }
    return UNKNOWN;
}
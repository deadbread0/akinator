#include <stdio.h>
#include <assert.h>
#include <cstring>

#include "functions_for_user.h"

node_t* ChooseNextOperation(answer_t answer, node_t* node, bool* user_wants_use_program, errors_t* errors)
{
    assert(node != nullptr);
    assert(user_wants_use_program != nullptr);
    assert(errors != nullptr);

    if (answer == YES && node->right)
        return node->right;

    else if (answer == YES && !node->right)
    {
        printf("I just read minds)\n");
        answer = InviteToUseProgramAgain();
        *user_wants_use_program = DecideProgramRestart(answer);
    }

    else if (answer == NO && node->left)
        return node->left;

    else if (answer == NO && !node->left)
    {
        AskUserAboutNewCharacterAndMakeNewNode(node, errors);
        answer = InviteToUseProgramAgain();
        *user_wants_use_program = DecideProgramRestart(answer);
    }

    else 
    {
        while (answer == ELSE)//anon
        {
            printf("enter yes or no\n");
            answer = GetShortAnswer();
        }
        ChooseNextOperation(answer, node, user_wants_use_program, errors);
    }  

    return nullptr;
}

bool DecideProgramRestart(answer_t answer)
{
    if (answer == YES)
        return true;
    else if (answer == NO)
        return false;
    else 
    {
        while (answer == ELSE)
        {
            printf("enter yes or no\n");
            answer = GetShortAnswer();
        }
        return DecideProgramRestart(answer);
    } 
}

void AskUserAboutNewCharacterAndMakeNewNode(node_t* node, errors_t* error)
{
    assert(node != nullptr);
    assert(error != nullptr);

    tree_elem_t* name_of_new_character = (tree_elem_t*)calloc(MAX_LEN_OF_NAME, sizeof(char));
    AskUserAboutNameAndGetAnswer(error, name_of_new_character);

    tree_elem_t* description_of_new_character = (tree_elem_t*)calloc(MAX_LEN_OF_DESCRIPTION, sizeof(char));
    AskUserAboutDeacriptionAndGetAnswer(error, name_of_new_character, description_of_new_character, node);

    node_t* node_for_new_character = (node_t*)calloc(1, sizeof(node_t));
    node_t* node_for_last_character = (node_t*)calloc(1, sizeof(node_t));//free

    if (node_for_new_character == nullptr || node_for_last_character == nullptr)
    {
        *error = MEMORY_ALLOCATION;
        return;
    }

    node_for_last_character->prev = node;
    node_for_new_character->prev = node;

    node_for_last_character->data = node->data;
    node_for_new_character->data = name_of_new_character;

    node->data = MakeQuestionFromStr(description_of_new_character);
    node->left = node_for_last_character;
    node->right = node_for_new_character;

}
void AskUserAboutNameAndGetAnswer(errors_t* error, tree_elem_t* name_of_new_character)
{
    assert(error != nullptr);

    printf("who is this?\n");
    if (name_of_new_character == nullptr)
    {
        *error = MEMORY_ALLOCATION;
        return;
    }
    scanf("%s", name_of_new_character);
}

void AskUserAboutDeacriptionAndGetAnswer(errors_t* error, tree_elem_t* name_of_new_character, tree_elem_t* description_of_new_character, node_t* node)
{
    assert(error != nullptr);
    assert(node != nullptr);
    assert(name_of_new_character != nullptr);

    printf("how is %s different from %s? He/she...", name_of_new_character, node->data);
    if (name_of_new_character == nullptr)
    {
        *error = MEMORY_ALLOCATION;
        return;
    }
    scanf("%s", description_of_new_character);
}

tree_elem_t* MakeQuestionFromStr(tree_elem_t* str)
{
    assert(str != nullptr);

    int len = strlen(str);
    str[len] = '?';
    return str;
}

tree_elem_t* MakeStatementFromStr(tree_elem_t* str)
{
    assert(str != nullptr);

    int len = strlen(str);
    str[len - 1] = '\0';
    return str;
}

answer_t InviteToUseProgramAgain()
{
    printf("Do you want to try again?\n");
    return GetShortAnswer();
}

answer_t GetShortAnswer()
{
    char answer[MAX_LEN_OF_SHORT_ANSWER] = {};
    scanf("%s", answer);

    int yes = strncmp(answer, "yes", MAX_LEN_OF_SHORT_ANSWER);
    int no = strncmp(answer, "no", MAX_LEN_OF_SHORT_ANSWER);

    if (!yes)
        return YES;
    else if (!no)
        return NO;
    else
        return ELSE;
}

char* GetElemFromUser(errors_t* error)
{
    tree_elem_t* elem = (tree_elem_t*)calloc(MAX_LEN_OF_NAME, sizeof(tree_elem_t));

    if (!elem)
    {
        *error = MEMORY_ALLOCATION;
        return nullptr;
    }

    scanf("%s", elem);
    return elem;
}


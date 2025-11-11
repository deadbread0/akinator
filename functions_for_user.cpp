#include <stdio.h>
#include <assert.h>
#include <cstring>

#include "functions_for_user.h"

node_t* ChooseNextOperation(answer_t answer, node_t* node, bool* user_wants_use_program)//enum
{
    assert(node != nullptr);

    if (answer == YES && node->right)
        return node->right;
    else if (answer == YES && !node->right)
    {
        InviteToUseProgrammAgain();
        answer = GetShortAnswer();
        *user_wants_use_program = DecideProgramRestart(answer);
    }
    else if (answer == NO && node->left)
        return node->left;
    else if (answer == NO && !node->left)
    {
        AskUserAboutNewCharacterAndMakeNewNode(node);
        InviteToUseProgrammAgain();
        answer = GetShortAnswer();
        *user_wants_use_program = DecideProgramRestart(answer);
    }
    else 
    {
        while (answer == ELSE)
        {
            printf("enter yes or no\n");
            answer = GetShortAnswer();
        }
        ChooseNextOperation(answer, node, user_wants_use_program);
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

void AskUserAboutNewCharacterAndMakeNewNode(node_t* node)
{
    printf("who is this?\n");
    tree_elem_t* name_of_new_character = (tree_elem_t*)calloc(MAX_LEN_OF_NAME, sizeof(char));
    scanf("%s", name_of_new_character);

    printf("how is %s different from %s? He/she...", name_of_new_character, node->data);
    tree_elem_t* description_of_new_character = (tree_elem_t*)calloc(MAX_LEN_OF_DESCRIPTION, sizeof(char));
    scanf("%s", description_of_new_character);

    node_t* node_for_new_character = (node_t*)calloc(1, sizeof(node_t));
    node_t* node_for_last_character = (node_t*)calloc(1, sizeof(node_t));

    node_for_last_character->data = node->data;
    node_for_new_character->data = name_of_new_character;

    node->data = MakeQuestionFromStr(description_of_new_character);
    node->left = node_for_last_character;
    node->right = node_for_new_character;

}

tree_elem_t* MakeQuestionFromStr(tree_elem_t* str)
{
    int len = strlen(str);
    str[len] = '?';
    return str;
}

void InviteToUseProgrammAgain()
{
    printf("Do you want to try again?\n");
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

node_t* MakeFirstNode()
{
    node_t* new_node = (node_t*)calloc(1, sizeof(node_t));
    new_node->data = (char*)"unknown thing";
    new_node->left = nullptr;
    new_node->right = nullptr;

    return new_node;///
}
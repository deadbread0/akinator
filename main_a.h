const int MAX_LEN_OF_SHORT_ANSWER = 3;
const int MAX_LEN_OF_NAME = 100;
const int MAX_LEN_OF_DESCRIPTION = 1000;

typedef char tree_elem_t;

struct node_t {
    tree_elem_t* data;
    node_t* left;
    node_t* right;
};

enum answer_t {
    YES,
    NO,
    ELSE
};


node_t* MakeFirstNode();
void DumpTree(const node_t* node, FILE* filee);
void FreeTree(node_t* node);
void PrintNode(const node_t* node);
answer_t GetShortAnswer();
node_t* ChooseNextOperation(answer_t answer, node_t* node, bool* user_wants_use_program);
bool DecideProgramRestart(answer_t answer);
void AskUserAboutNewCharacterAndMakeNewNode(node_t* node);
void InviteToUseProgrammAgain();
tree_elem_t* MakeQuestionFromStr(tree_elem_t* str);


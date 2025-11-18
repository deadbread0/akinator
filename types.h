typedef char tree_elem_t;
typedef void (*func_ptr)(void);

struct node_t {
    tree_elem_t* data;
    node_t* left;
    node_t* right;
    node_t* prev;
};

enum answer_t {
    YES,
    NO,
    ELSE
};

enum errors_t
{
    NO_ERRORS,
    FILE_DIDNT_OPEN,
    MEMORY_ALLOCATION,
    NO_SUCH_NODE,
    PROBLEMS_WITH_READING_FILE
};

struct flag_t{
    char* flag;
    func_ptr ptr;
    char* description;
};
struct node
{
    struct node* next;
    struct node* left;
    void* key;
    struct node* right;
};
struct tree
{
    struct node* root;
    struct node* current;
};
typedef struct node node;
typedef struct tree tree;

node* newNode(void* p, int b);

tree* newTree();


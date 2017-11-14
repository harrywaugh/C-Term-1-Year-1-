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
    int bytes;
};
typedef struct node node;
typedef struct tree tree;

node* newNode(void* p, int b);

tree* newTree(int b);

int treeLength(tree* t);

void startTree(tree* t);

void getVal(tree *t, node* n, void *p);

void setVal(tree *t, node* n, void *p);
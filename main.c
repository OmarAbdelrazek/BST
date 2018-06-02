#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct
{
    char data[100];
    struct node *left,*right;
} node;
typedef struct
{
    char name[100]
} words;
words wordsArray[3000];
int elements = 0;
node *root;
node *rootOfTree;
words notFoundWords[100];
int notFoundCounter=0;
int notFoundFlage = 0;
node* newNode(char word[100])
{
    node* n = malloc(sizeof(node));
    strcpy(n->data,word);
    n->left = NULL;
    n->right = NULL;
    return n;
}



node* addLeft(node* n, char word[100])
{
    if(n!=NULL)
    {
        node* nw = newNode(word);
        n->left = word;
        return nw;
    }
    return NULL;
}
node* addRight(node* n, char word[100])
{
    if(n!=NULL)
    {
        node* nw = newNode(word);
        n->right = nw;
        return nw;

    }
    return NULL;
}
node* insertt(node* node, char word[100])
{

    if(node == NULL)
    {

        return newNode(word);

    }
    if(my_strcmp(word,node->data) == -1)
    {

        node->right = insertt(node->right,word);

    }
    else if(my_strcmp(word,node->data) == 1)
    {

        node->left = insertt(node->left,word);

    }
    return node;
}

node * minValue( node* noode)
{
    node* current = noode;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}
void inOrderSuccessor(node *rot,  node *n)
{
    // step 1 of the above algorithm
    if( n->right != NULL )
        return minValue(n->right);

    node *succ = NULL;

    // Start from root and search for successor down the tree
    while (rot != NULL)
    {
        if (my_strcmp(n->data, rot->data) == -1)
        {
            succ = rot;
            rot = rot->left;
        }
        else if (my_strcmp(n->data, rot->data) == 1)
            rot = rot->right;
        else
            break;
    }
    printf("succ: %s",&succ->data);

}



node* search(node* t, char *word)
{
    int count = 0;
    node *pp = NULL;
    node* preD = NULL;
    node * succ = NULL;
    while(t != NULL)
    {
        // printf("\n%s" , t->data);
        if(my_strcmp(t->data,word) == 0)
        {
            printf(">>found\n" );
            return t;

        }
        if(my_strcmp(t->data,word) == 1)
        {
            count++;
            // printf("%s\tright\n" , t->data);
            if(count == 9 || count ==10 )
                succ = t;
            if(count == 10 || count ==11 )
                pp = t;
            preD = t;
            t = t->left;


        }
        else if(my_strcmp(t->data,word) == -1)
        {
            count++;
            //  printf("%s\tleft\n" , t->data);
            if(count == 9 || count ==10 )
                succ = t;
            if(count == 10 || count ==11 )
                pp = t;
            preD = t;
            t = t->right;


        }
    }
    printf(">>not found\n" );
    strcpy(notFoundWords[notFoundCounter].name,word);
    notFoundCounter++;
    // printf("Pre: %s ",preD->data);
    //findSuccessor(preD);
    notFoundFlage = 1;


    printf("---Predecessor: %s", preD->data);
    printf("\n---Successor: %s", succ->data);
    printf("\n---parent: %s", pp->data);
    return NULL;
}

void findSuccessor(node *preD)
{
    inOrderSuccessor(root,preD);
    //  printf("Successor: %s",s->data);

}


void readFile()
{
    FILE *file;
    char *filename = "names";
    file = fopen(filename,"r");
    if(file == NULL)
    {
        printf("file not found");
        return;
    }
    int i;
    for(i = 0 ; i < 3000 ; i++)
    {
        fscanf(file,"%s\n", wordsArray[i].name);

    }

    fclose(file);

    constructBalancedTree();



}
char* max(int a, int b)
{
    return a>b?a:b;
}

int getHeight(node* n)
{
    if(n == NULL)
        return 0;

    return (1 + max(getHeight(n->left), getHeight(n->right)));
}
int flag = 0;

void create_balanced_bin_tree(node **rooot, int start, int end)
{
    if (start <= end)
    {
        flag++;
        int mid = (start + end + 1) / 2;

        *rooot = newNode(wordsArray[mid].name);

        create_balanced_bin_tree(&((*rooot)->left),  start, mid - 1);
        create_balanced_bin_tree(&((*rooot)->right),  mid + 1, end);
    }
}
void constructBalancedTree()
{
    root = NULL;
    create_balanced_bin_tree(&root,0,2999);
    // search(root,"zone");




}

void preOrder(node* t)
{
    if(t != NULL)
    {
        printf("%s\n", t->data);
        preOrder(t->left);
        preOrder(t->right);
    }
}


void printWords()
{
    int i;
    for(i=0 ; i< 3000 ; i++)
    {
        printf("%s-",wordsArray[i].name);
    }



}




int my_strcmp(const char *a, const char *b)
{
    for(; *a && *b && *a == *b; ++a, ++b)
        ;
    if(*a < *b)
        return -1;
    return *a > *b;
}

void validate(char* word)
{
    char str[100] ;
    strcpy(str,word);
    char *token;

    token = strtok(str, " ");

    while( token != NULL )
    {
        // printf("%s\n", token );
        printf("%s ",token);

        search(root,token);
        printf("\n");
        token = strtok(NULL, " ");
    }
}
void enterWordsMenu()
{

//system("clear");
    char* word;

    printf("enter your words here-separete them with spaces- :  ");
    gets(word);
    gets(word);
    validate(word);
}

int main()
{
    readFile();
    system("clear");

    int dis ;
    int truee = 1;
    int h ;


    while(truee)
    {

    printf("1.Enter a sentance");
    printf("\n2.Tree height");
    printf("\n3.Exit\n\n--->");
    scanf("%d", &dis);
        switch(dis)
        {
        case 1:
            enterWordsMenu();
            break;
        case 2 :
            h= getHeight(root);
            printf("Height >>> %d\n",h);

            break;
        case 3:
            truee = 0;
        }
    }





    return 0;
}

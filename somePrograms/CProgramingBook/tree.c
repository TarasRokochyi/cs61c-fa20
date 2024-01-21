#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addTree(struct tnode *root, char *word);

void printTree(struct tnode *root);

char *copy(char* word);


int main(void){

    char *words[] = { "now", "is", "the", "time", "for", "all", "good", "men", "to", "come", "to", "the", "good", "aid", "of", "their", "the", "party", '\0'};

    struct tnode *root;

    root = NULL;

    int count = 0;
    char *word;
    for (int i = 0; (word = words[i]); i++){
        root = addTree(root, word);
    }

    printTree(root);
}


struct tnode *addTree(struct tnode *root, char *word){
    
    int cond;

    if (root == NULL){
        root = (struct tnode *) malloc(sizeof(struct tnode));
        root->word = copy(word);
        root->count = 1;
        root->left = NULL;
        root->right = NULL;
    }
    else if ((cond = strcmp(word, root->word)) == 0){
        root->count++;
    }
    else if (cond < 0){
        root->left = addTree(root->left, word);
    }
    else if (cond > 0){
        root->right = addTree(root->right, word);
    }


    return root;
}



void printTree(struct tnode *root){

    if (root != NULL){
        printTree(root->left);
        printf("%s  %d\n", root->word, root->count); 
        printTree(root->right);
    }
}


char *copy(char *word){

    char *result;

    result = (char *) malloc(strlen(word)+1);

    strcpy(result, word);

    return result;
}


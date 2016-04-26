#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
/*the CFG
S>ABAC
A>aA|$
B>bB|$
C>c
*/
/*List produced  
    SABAC
    AaA
    A$
    BbB
    B$
    Cc*/
/*Desired Result
    SABAC
    SABC
    SBAC
    SBC
    AaA
    BbB
    Bb
    Cc*/
typedef struct node {
    struct node * next;
    //struct node * prev;
    char arr[7];//the array to save CFG per line
    }node_t;
char print_list(node_t * root);
//char first_set(node_t * root,char c);
char traversal(node_t * root);//To see which nodes have null productions
char rightTraversal(node_t * root,char);//Passing the nodes which have null production then removing them from list.
char c, temp, nonTerminal; int i=0; bool flag = true;
char null_list[7];
int null_counter = 0;


int main() {
    node_t * head = malloc(sizeof(node_t));
    node_t * current = malloc(sizeof(node_t));
    node_t * root = malloc(sizeof(node_t));
    head = current;
    for(int j=0; j<7; j++){
        null_list[j] = '#';
        
    }
    
    FILE *fp;
    //char c, temp; int i=0; bool flag = true;
    fp = fopen("cfg.txt", "r");
    while((c = fgetc(fp)) != EOF) {
        if(c == '\n') {
          current->next = malloc(sizeof(node_t));
          //current->next->next = NULL;
          current = current->next;
          current->next = NULL;
            
          flag = true; i=0;
        }else if(c == '>' || c == ' '){continue;}
        else if(c == '|'){
            current->next = malloc(sizeof(node_t));
            current = current->next;
            i = 0;
            current->arr[i] = temp;
            i++;
            continue;
        }
         else {
            current->arr[i] = c;
            i++;
            current->next = NULL;
            //current->prev = NULL;
            if(flag){
                temp = c;
                flag = false;
            }
           // continue;
        }
    }
    fclose(fp);
    root = head;
    
   traversal(root);
     /*for(int j=0; j<7; j++){
         if(null_list[j] != '#'){
        printf("%c\n",null_list[j]);
         }
    }*/
   rightTraversal(root, null_list[0]);
   rightTraversal(root, null_list[1]); 
}
char print_list(node_t * root) {
    while(root->next != NULL){
        for(i=0; i<7; i++) {
            printf("%c", root->arr[i]);
        }
        printf("\n");
        root = root->next;
    }
    return 0;
}
char traversal(node_t * root) {
    while(root->next != NULL){
        for(i=0; i<7; i++) {
            if(root->arr[i] == '$'){
                null_list[null_counter] = root->arr[0];
                null_counter++;
                
            }
        }
        root = root->next;
    }
    return 0;
}
char rightTraversal(node_t * root, char c){
    node_t * shoot = root;
    while(shoot->next != NULL){
        for(int i=1; i<7; i++){
            if(shoot->arr[i] == c){
                node_t * temp_node = malloc(sizeof(node_t));
                /*printf("%c\n", shoot->arr[0]);*/
                
                for(int i=0; i<7; i++){
                    temp_node->arr[i] = shoot->arr[i];
                }
                for(int k=1; k<7; k++){
                    if(temp_node->arr[k]==c){
                        temp_node->arr[k] = ' ';
                        break;
                    }   
                }
                temp_node->next = shoot->next;
                shoot->next = temp_node;
                break;
                //shoot->next = malloc(sizeof(node_t));
                //shoot = shoot->next;
            }
        }
        shoot = shoot->next;
    }
        print_list(root);   
}

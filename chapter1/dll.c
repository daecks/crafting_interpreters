#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node{
    char* data; // null terminated strings
    struct node* next;
    struct node* prev;
};

struct node *head = 0;

struct node* create_new_node(char *data){
    struct node *new_node = (struct node*) malloc(sizeof(struct node));
    int data_length = strlen(data);
    new_node->data = (char *) malloc(data_length);
    memcpy(new_node->data, data, data_length);
    new_node->next = NULL;
    new_node->prev = NULL;
}

void add_node_to_head(char* data){
    printf("Adding node with data: %s\n", data);

    struct node* new_node = create_new_node(data);

    if(head == NULL){
        head = new_node;
        return;
    }

    head->prev = new_node;
    new_node->next = head;
    head = new_node;
}

void add_node_to_tail(char* data){
}

int get_node_count(void){

    if(head == NULL) return 0;

    int node_count = 0;
    struct node* current_node = head;

    while(current_node != NULL){
        node_count++;
        current_node = current_node->next;
    }

    return node_count;

}

void delete_node_containing_data(char* data){
    printf("Deleting node with data: %s\n", data);

    int comparison_result;

    if(head == NULL){
        printf("No nodes exist to delete!\n");
    }else{
        struct node* current_node = head;
        while(current_node != NULL){
            comparison_result = memcmp(data, current_node->data, strlen(current_node->data)-1);
            // If there is a match...
            if(comparison_result == 0){

                // Free current buffer
                free(current_node->data);

                // If the current node is head, update to be next node to be the head
                if(current_node == head) head = current_node->next;

                // Update next node to point to previous node
                if(current_node->next != NULL){
                    current_node->next->prev = current_node->prev;
                }

                // Update previous node to point to next node
                if(current_node->prev != NULL){
                    current_node->prev->next = current_node->next;
                }

                // Pointers are adjusted! Now let's free the current node.
                free(current_node);
                return;
            }
            current_node = current_node->next;
        }
    }
}

void print_contents(void){
    if(head == NULL){
        printf("No data!\n");
    }else{
        struct node* current_node = head;
        while(current_node != NULL){
            printf("Node data is %s\n", current_node->data);
            current_node = current_node->next;
        }
    }
}

int main(){
    #ifdef USE_STDIN
    #define MAX_INPUT_SIZE 10
    char input[MAX_INPUT_SIZE];

    while(fgets(input, MAX_INPUT_SIZE, stdin)){
        int input_length = strlen(input);
        if(input_length > 1){
            printf("Got string: %s with length %zd\n", input, strlen(input));
            add_node_to_head(input);
        }else{
            break;
        }
    }
    #endif

    // Null-terminated strings are assumed to be the norm around here

    add_node_to_head("now!");
    add_node_to_head("choppa!");
    add_node_to_head("the");
    add_node_to_head("to");
    add_node_to_head("Get");
    printf("Number of nodes is: %d\n", get_node_count());
    print_contents();

    delete_node_containing_data("yolo");
    printf("Number of nodes is: %d\n", get_node_count());

    delete_node_containing_data("now!");
    printf("Number of nodes is: %d\n", get_node_count());

    print_contents();

}

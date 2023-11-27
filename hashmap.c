#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char *key;
    char *value;
}KeyValuePair;

typedef struct Node Node;

struct Node {
    int index;
    KeyValuePair data;
    Node *next;
};

int length = 0;

KeyValuePair createPair(const char *key, const char *value) {
    KeyValuePair pair;
    pair.key = strdup(key);
    pair.value = strdup(value);
    return pair;
}

Node* createNode(KeyValuePair pair) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->index = length;
    node->data = pair;
    node->next = NULL;
    length++;
    return node;
}

void insert(Node *head_node, const char *key, const char *value) {
    KeyValuePair pair = createPair(key, value);
    Node *newNode = createNode(pair);
    Node *temp = head_node;

    if (head_node == NULL) 
    {
        printf("Creating head node first\n");
        return;
    }
    
    while (temp->next != NULL) 
    {
        temp = temp->next;
    }
    
    temp->next = newNode;
}

char *get(Node *head_node, const char *key) {
    Node *temp = head_node;

    if (head_node == NULL) 
    {
        printf("Creating head node first\n");
        return NULL;
    }
    
    while (temp->next != NULL) 
    {
        if (strcmp(temp->data.key, key) == 0)
        {
            return temp->data.value;
        }
        temp = temp->next;
    }
    printf("Invalid variable name %s\n", key);
    return NULL;
}

char *getViaIndex(Node *head_node, const int index) {
    Node *temp = head_node;

    if (head_node == NULL) 
    {
        printf("Creating head node first\n");
        return NULL;
    }
    
    while (temp->next != NULL) 
    {
        if (temp->index == index)
        {
            return temp->data.value;
        }
        temp = temp->next;
    }
    printf("Invalid index %d\n", index);
    return NULL;
}

void print_dict(Node *head_node) {
    Node *temp = head_node;

    if (head_node == NULL) 
    {
        printf("Creating head node first\n");
        return;
    }
    
    while (temp != NULL) 
    {
        printf("(%d, %s, %s)\n", temp->index, temp->data.key, temp->data.value);
        temp = temp->next;
    }
}

int getDictLength() {
    return length + 1;
}

// int main(int argc, char const *argv[])
// {
//     Node *head_node = createNode(createPair("",""));
//     insert(head_node, "one", "1");
//     insert(head_node, "two", "2");
//     insert(head_node, "three", "3");
//     insert(head_node, "four", "4");

//     printf("Value at 'two': %s\n", get(head_node, "two"));

//     print_dict(head_node);

//     return 0;
// }

#ifndef LIST_H
#define LIST_H

struct Node {
    int value;
    Node* next;
};

Node* create_node(int value);
void insert_value(Node* tail, int value);
void append_value(Node* head, int value);
void print_list(Node* head);
void free_list(Node* head);
void insert_value_at(Node* head, int value, int index);

void operation_1();
void operation_2();
void operation_3();

#endif  // LIST_H
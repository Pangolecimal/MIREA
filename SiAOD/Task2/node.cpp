#include "node.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

Node* create_node(int value) {
    Node* node = new Node;
    node->value = value;
    node->next = nullptr;

    return node;
};

void insert_value(Node* node, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    node->next = newNode;
}

void append_value(Node* head, int value) {
    Node* tail = head;
    while (tail->next != nullptr)
        tail = tail->next;

    insert_value(tail, value);
}

void insert_value_at(Node* head, int value, int index) {
    Node* node = head;
    for (int i = 0; i < index && node->next != nullptr; i++)
        node = node->next;

    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = node->next;

    node->next = newNode;
}

void delete_node(Node* head, Node* node) {
    Node* before = head;
    while (before->next != node)
        before = before->next;

    before->next = node->next;
    delete node;
}

int get_value_at(Node* head, int index) {
    Node* node = head;
    for (int i = 0; i < index && node->next != nullptr; i++)
        node = node->next;

    return node->value
}

void print_list(Node* head) {
    std::cout << "List: ";
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->value << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

void free_list(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void operation_1() {
    int num_nodes = 12;
    Node* head = create_node(0);
    for (int i = 0; i < num_nodes; i++)
        append_value(head, rand() % num_nodes);

    print_list(head);

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < i; j++) {
            int value_i = get_value_at(i);
            int value_j = get_value_at(j);
            if (value_i == value_j)
                std::cout << "Found repeating value: " << value_i;
        }
    }

    free_list(head);
}

void operation_2() {}
void operation_3() {}
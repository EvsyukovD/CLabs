#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Info {
	char* s;
	float x;
} Info;

typedef struct Node {
	Info info;
	unsigned int key;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
	struct Node* next;
	struct Node* prev;
}Node;

typedef struct tree {
	Node* root;
}tree;

tree* new_tree();

char* get_str();

int get_int(unsigned int* x);

int get_key(unsigned int* x);

Node* tree_search_one(unsigned int key, tree* t);

Node* tree_search_all(unsigned int key, tree* t);

Node* tree_max(Node* p);

Node* tree_min(Node* p);

Node* successor(Node* p);

Node* predecessor(Node* p);

int tree_insert(Node* p, tree* t);

int tree_delete(unsigned int key, tree* t);

int show(Node* p);

int d_show_max(tree* t);

int d_delete(tree* t);

int d_insert(tree* t);

int d_search(tree* t);

int d_search_max(tree* t);

void delete_tree(tree* t);

int null(tree* t);

int dialog(char* s[], int size);

Node* f_to_e(FILE* fd);

int d_show_tree(tree* t);

tree* f_to_tr(char* fname);

int d_time(void* s);
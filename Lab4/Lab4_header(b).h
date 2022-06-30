#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
typedef struct Info {
	float x;
	float y;
	char* s;
}Info;

typedef struct Point {
	int key[2];
	Info* info;
}Point;

typedef struct Node {
	Point p;
	struct Node* left;
	struct Node* right;
	Point* level;
	int n;
	struct Node* parent;
	//int depth;
}Node;

typedef struct Pair {
	Node* x;
	Node* y;
}Pair;

typedef struct tree {
	Node* root;
	int N;
}tree;

tree* new_tree();

char* get_str(); 

int get_float(float* x); 

int get_int(int* x); 

void lend_left(Point* l, int size, int idx);

void delete_in_array(Point* s, int key[], int size);

unsigned int maximum(unsigned int x, unsigned int y);

unsigned int minimum(unsigned int x, unsigned int y);

void swap(Point* x, Point* y);

void lend_right(Point* l, int size);

void insert_p(Point* l, int size, Point p, int axis);

void round_level(Node* ptr, Node* p, int depth, int axis);

Node* search(int key[], tree* t);

void round_max_dist(int x, int y, Node* v, unsigned int* d2);

void round_min_dist(int x, int y, Node* v, unsigned int* d2);

void show(Node* v);

void round_equal_dist(int x, int y, Node* v, unsigned int d2);

void region_max(int x, int y, tree* t);

void first_equal_min_dist(int x, int y, Node* v, unsigned int d2, Node** ptr);

void search_fixup(Point* s, int key[], int size, tree* t);

Node* successor(Node* p, tree* t);

/*Node* tree_delete(int key[],tree* t) {
    int l = 0;
    Node* x = search(key, t);
    if (!x) {
        return 0;
    }
    Node* y = NULL, * p = NULL, * par = NULL;
    if ((x->left == NULL) || (x->right == NULL)) {
        y = x;
    }
    else {
        y = successor(x,t);
    }
    if (y->left) {
        p = y->left;
    }
    else {
        p = y->right;
    }
    par = y->parent;
    if (p) {
        p->parent = par;
    }
    if (!par) {
        t->root = p;
    }
    else {
        if (par->left == y) {
            par->left = p;
        }
        else {
            par->right = p;
        }
    }
    if (y != x) {
        l = 1;
        x->p.key[0] = y->p.key[0];
        x->p.key[1] = y->p.key[1];
        free(x->p.info->s);
        x->p.info = y->p.info;
        delete_in_array(x->level, x->p.key, x->n);
        --(x->n);
        int axis = (x->depth) % 2;
        insert_p(x->level, x->n, x->p, axis);
    }

    if (!l) {
        free(y->p.info->s);
    }

    free(y);
    return 1;
}
*/
int insert(Node* p, tree* t);

Node* minNode(Node* x, Node* y, Node* z, int d);

Node* findMinRec(Node* root, int d, unsigned depth);

Node* deleteNodeRec(Node* root, int point[], int depth, tree* t);

Node* deleteNode(int point[], tree* t);

Node* findMin(Node* root, int d); 

Node* merge(Node* l, Node* r);

Pair split(Node* p, int x);

Node* tree_search_one(unsigned int key, tree* t);

int d_search(tree* t);

int d_insert(tree* t);

int d_delete(tree* t);

int delete_tree(tree* t);

int d_show(tree* t);

int d_search_max(tree* t);

int d_show_tree(tree* t);

int dialog(char* s[], int size);

int d_timing(tree* t);

/*Node* insertRec(Node* root, int point[], unsigned depth){
  if (root == NULL)
        return newNode(point);
    unsigned cd = depth % k;
    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);
    return root;
}*/

int null(tree* t);
#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct Info {
	float x;
	float y;
	char* s;

}Info;

typedef struct Item {
	Info* info;
	char* key1;
	unsigned int key2;
	char* p1;

}Item;

typedef struct Keyspace1 {
	char* key;
	char* par;
	struct Item* info;

}Keyspace1;

typedef struct Keyspace2 {
	unsigned int key;
	Item* info;
	struct Keyspace2* next;

}Keyspace2;

typedef struct table {
	Keyspace1* ks1;
	Keyspace2* ks2;
	int csize1;
	int msize1;
	int msize2;

}table;

Keyspace1* key1_table(int size);

Keyspace2* key2_table(int size);

int hash(int key, int size);

char* get_str();

int get_float(float* x);

int get_int(unsigned int* x);

Item* search_key2(table* T, unsigned int key2);

Item* search_key1(table* T, char* key1);

void swap(void* a, void* b, size_t size);

table* new_table(int size1, int size2);

int dialog(char* s[], int size);

void push(Keyspace2* head, Item* I);

Item* search_item(table* T, char* key1, unsigned int key2);

void insert_keys1(table* table, Item* I);

void insert_keys2(table* table, Item* I);

int insert(table* T, Item* I);

void delete_keys1(Keyspace1* table, int size);

void delete_list(Keyspace2* head);

void delete_keys2(Keyspace2* table, int size);

void delete_item(Item* inf);

void delete_table(table* T);

int d_add(table* t);

int null(void* t);

table* init_table();

void show_item(Item* I);

int d_show(table* t);

int d_search(table* t);

void full_delete_item(table* t, Item* I);

int delete_with_par(table* t, char* par);

int d_delete(table* t);

int d_search_with_par(table* t);

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
typedef struct vertex {
	char* name;
	int point[2];
	struct vertex* next;
} vertex;

typedef struct Graph {
	vertex* ptr;
	int n;
	int msize;
}Graph;

typedef struct Queue {
	vertex* head;
}Queue;

Queue* new_queue();

Graph* new_graph(int N);

void insert_in_queue(Queue* q, vertex* s);

int d_insert_vertex(Graph* G);

int d_insert_edge(Graph* G);

int d_delete_edge(Graph* G);

int null(Graph* G);

int dialog(char* s[], int size);

void delete_graph(Graph* G);

int d_delete_vertex(Graph* G);

int d_show(Graph* G);

int d_search_path_BFS(Graph* G);

int d_search_min_path_from_s(Graph* G);

int d_search_path_FW(Graph* G);

int d_timing(Graph* G);
//void BFS(char* v1, char* v2, Graph* G);

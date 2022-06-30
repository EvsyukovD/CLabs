#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "Lab5_header.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	setlocale(LC_ALL, "rus");
	int (*fptrs[])(Graph*) = {null,d_insert_vertex,d_insert_edge,d_delete_edge,d_delete_vertex,d_show,d_search_path_BFS,d_search_min_path_from_s,d_search_path_FW,d_timing};
	char* msgs[] = { "0.Выход","1.Вставить новую вершину","2.Вставить новое ребро","3.Удалить ребро","4.Удалить вершину","5.Вывод графа","6.Поиск пути из данной вершины в данную","7.Поиск минимального пути из данной вершины в данную","8.Вывод первых трёх минимальных путей","9.Время поиска"};
	int size = sizeof(msgs) / sizeof(char*);
	int rc;
	int N, res;
	Graph* G = (Graph*)calloc(1, sizeof(Graph));
	puts("Введите максимальное количество элементов:");
	res = get_int(&N);
	if (!res) {
		return 0;
	}
	//printf("%d\n", INT_MAX);
	G->msize = N;
	G->ptr = (vertex*)calloc(N, sizeof(vertex));
	do {
		while (fptrs[rc = dialog(msgs, size)](G));
	} while (rc);
	delete_graph(G);
	return 0;
}

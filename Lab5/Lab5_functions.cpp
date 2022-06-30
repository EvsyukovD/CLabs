#include "Lab5_header.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <math.h>
#include <time.h>
Queue* new_queue() {
	return (Queue*)calloc(1, sizeof(Queue));
}

unsigned int** new_d(int size) {
	unsigned int** d = (unsigned int**)calloc(size, sizeof(unsigned int*));
	int i;
	for (i = 0; i < size; i++) {
	     d[i] = (unsigned int*)calloc(size, sizeof(unsigned int));
	}
	return d;
}

int** new_pi(int size) {
	int** p = (int**)calloc(size, sizeof(int*));
	int i;
	for (i = 0; i < size; i++) {
		p[i] = (int*)calloc(size, sizeof(int));
	}
	return p;
}

char* get_str() {
	char buf[81] = { 0 };
	char* res = NULL;
	int len = 0;
	int n = 0;
	do {
		n = scanf_s("%80[^\n]", buf, sizeof(buf));
		if (n < 0) {
			if (!res) {
				return NULL;
			}
		}
		else if (n > 0) {
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		}
		else {
			scanf_s("%*c");
		}
	} while (n > 0);

	if (len > 0) {
		res[len] = '\0';
	}
	else {
		res = calloc(1, sizeof(char));
	}

	return res;
}

void swap(vertex* a, vertex* b) {
	vertex v = *a;
	*a = *b;
	*b = v;
}

void lend_up(Graph* G,int idx) {
	int i,n = G->n;
	vertex* r = G->ptr;
	for (i = idx + 1; i < n; i++) {
		swap(&r[i - 1], &r[i]);
	}
}

int get_int(int* x) {
	int n;
	char* msg = "Error input.Try again";
	do {
		n = scanf_s("%d", x, sizeof(int));
		if (n < 0) {
			return 0;
		}
		if (n == 0) {
			puts(msg);
			scanf_s("%*c");
		}

	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return 1;
}

Graph* new_graph(int N) {
	Graph* G = (Graph*)calloc(1, sizeof(Graph));
	G->ptr = (vertex*)calloc(N, sizeof(vertex));
	return G;
}

vertex* create_v_with_copy(vertex s) {
	vertex* z = (vertex*)calloc(1, sizeof(vertex));
	int size = strlen(s.name) + 1;
	z->name = (char*)calloc(size, sizeof(char));
	strcpy_s(z->name, size, s.name);
	z->point[0] = s.point[0];
	z->point[1] = s.point[1];
	return z;
}

void insert_in_queue(Queue* q, vertex* s) {
	vertex* ptr = q->head;
	if (!ptr) {
		q->head = s;
		return;
	}
	while (ptr) {
		if (ptr->next == NULL) {
			ptr->next = s;
			ptr = s;
		}
		ptr = ptr->next;
	}
}

void delete_vertex(vertex* v) {
	free(v->name);
	free(v);
}

vertex* extract_from_queue(Queue* q) {
	vertex* ptr = q->head;
	if (q->head != NULL) {
		q->head = q->head->next;
	}
	return ptr;
}

void delete_queue(Queue* q) {
	vertex* ptr = extract_from_queue(q);
	while (ptr) {
		free(ptr->name);
		free(ptr);
		ptr = extract_from_queue(q);
	}
	free(q);
}

int idx(char* s, Graph* G) {
	int i,size = G->n;
	for (i = 0; i < size; i++) {
		if (!strcmp(s,G->ptr[i].name)) {
			return i;
		}
	}
	return -1;
}

int search_in_array(char* v, vertex* arr,int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (!strcmp(arr[i].name, v)) {
			return 1;
		}
	}
	return 0;
}

vertex** BFS(int idx_s,int idx_w, Graph* G) {
	int WHITE = 0,GREY = 1,BLACK = 2;
	int* color = (int*)calloc(G->n, sizeof(int));
	vertex** pred = (vertex**)calloc(G->n, sizeof(vertex*));
	int* d = (int*)calloc(G->n, sizeof(int));
	int i,size = G->n,idx_v,idx_u;
	for (i = 0; i < size; i++) {
		d[i] = INT_MAX;
	}
	color[idx_s] = GREY;
	d[idx_s] = 0;
	Queue* q = new_queue();
	vertex* p = create_v_with_copy(G->ptr[idx_s]);
	insert_in_queue(q,p);
	while (q->head) {
		vertex* u = extract_from_queue(q);
		vertex* v = G->ptr[idx_u = idx(u->name, G)].next;
		while (v) {
			if (color[idx_v = idx(v->name, G)] == WHITE) {
				color[idx_v] = GREY;
				d[idx_v] = d[idx_u] + 1;
				if (u == NULL) {
					free(pred[idx_v]);
					pred[idx_v] == NULL;
				}
				else {
					free(pred[idx_v]);
					pred[idx_v] = create_v_with_copy(*u);
				}
				p = create_v_with_copy(*v);
				insert_in_queue(q, p);

			}
			v = v->next;
			if (!v) {
				if (u) {
					free(u->name);
					free(u);
				}
			}
		}
		color[idx_u] = BLACK;
	}
	/*vertex* ptr = &G->ptr[idx_w];
	if (pred[idx_w] == NULL) {
		printf("Path from %s to %s not exist\n", G->ptr[idx_s].name, ptr->name);
		free(pred);
		free(color);
		free(d);
		delete_queue(q);
		return;
	}
	puts("Path from %s to %s :");
	printf("( %s )", ptr->name);
	i = idx_w;
	while (ptr) {
		i = idx(pred[i], G);
		ptr = &G->ptr[i];
		printf("<-( %s )", ptr->name);
	}*/
	free(color);
	free(d);
	delete_queue(q);
	return pred;
}

void print_path(int idx_s,int idx_w, vertex** pred,Graph* G) {
	/*int idx_pred;
	if (idx_s == idx_v) {
		printf("( %s )", G->ptr[idx_s].name);
	}
	else {
		if (pred[idx_v] == NULL) {
			puts("Path not exist");
			return;
		}
		else {
		
		}
	}*/
	vertex* ptr = &G->ptr[idx_w];
	if (pred[idx_w] == NULL) {
		printf("Путь из %s в %s не существует\n", G->ptr[idx_s].name, ptr->name);
		//free(pred);
		return;
	}
	printf("Путь из %s в %s :\n", G->ptr[idx_s].name, ptr->name);
	printf("( %s )", ptr->name);
	int i = idx_w;
	while (ptr && i != idx_s) {
		i = idx(pred[i]->name, G);
		ptr = &G->ptr[i];
		printf("<-( %s )", ptr->name);
	}

}

int insert(vertex v, Graph* G) {
	int size = strlen(v.name) + 1;
	G->ptr[G->n].name = (char*)calloc(size,sizeof(char));
	strcpy_s(G->ptr[G->n].name, size, v.name);
	G->ptr[G->n].point[0] = v.point[0];
	G->ptr[G->n].point[1] = v.point[1];
	G->n++;
	return 1;
}

void adj(vertex *v,vertex u) {
		if (!v->next) {
			v->next = create_v_with_copy(u);
		}
		else {
			vertex* p = v->next;
			v->next = create_v_with_copy(u);
			v->next->next = p;
		}
}

void add_adjs(int idx_v,Graph* G) {
	int i,point[2],N,res,idx_u;
	char* s = NULL;
	puts("Введите число вершин смежных с данной:");
	get_int(&N);
	for (i = 0; i < N; i++) {
		puts("Введите имя вершины :");
		s = get_str();
		puts("Введите 1 ключ :");
		res = get_int(&point[0]);
		if (!res) {
			return 0;
		}
		puts("Введите 2 ключ :");
		res = get_int(&point[1]);
		if (!res) {
			return 0;
		}
		vertex* v = (vertex*)calloc(1, sizeof(vertex));
		v->name = s;
		v->point[0] = point[0];
		v->point[1] = point[1];
		if (!search_in_array(s, G->ptr, G->n)) {
			insert(*v, G);
			delete_vertex(v);
			v = NULL;
			idx_u = G->n - 1;
		}
		else {
		    
		}
		//adj(idx_v, *v, G);
	}
}

int d_insert_vertex(Graph* G) {
	if (G->n == G->msize) {
		puts("Граф полностью заполнен");
		return 0;
	}
	int point[2],res,N,i;
	char* s = NULL;
	vertex v = { NULL,NULL,{0}};
	/*puts("Введите количество новых вершин :");
	res = get_int(&N);
	if (!res) {
		return 0;
	}
	if (G->n + N > G->msize) {
		puts("Слишком много вершин");
		return 0;
	}*/
	//for (i = 0; i < N; i++) {
		puts("Введите имя вершины :");
		s = get_str();
		puts("Введите 1 ключ :");
		get_int(&point[0]);
		puts("Введите 2 ключ :");
		get_int(&point[1]);
		if (idx(s,G) != -1) {
			puts("Элемент уже существует");
			free(s);
			return 0;
		}
		else {
			v.name = s;
			v.point[0] = point[0];
			v.point[1] = point[1];
			insert(v, G);
			free(v.name);
			return 1;
		}
	//}
	/*puts("Добавление рёбер:");
	int n = G->n;
	for (i = 0; i < n; i++) {
		printf("Введите вершину смежную с вершиной %s.Если таких вершин нет введите NULL:\n", G->ptr[i].name);

	}*/

	/*puts("Введите 1 ключ :");
	res = get_int(&point[0]);
	if (!res) {
		return 0;
	}
	puts("Введите 2 ключ :");
	res = get_int(&point[1]);
	if (!res) {
		return 0;
	}
	puts("Введите имя вершины :");
	s = get_str();
	if (search_in_array(s, G->ptr, G->n)) {
		puts("Элемент уже существует");
		free(s);
		return 0;
	}
	vertex* v = (vertex*)calloc(1, sizeof(vertex));
	v->name = s;
	v->point[0] = point[0];
	v->point[1] = point[1];
	insert(v, G);
	delete_vertex(v);
	puts("Введите число вершин смежных с данной:");
	get_int(&N);
	if (N == 0) {
		puts("Элемент добавлен");
		return 1;
	}
	int* idxs = (int*)calloc(N, sizeof(int));
	for (i = 0; i < N; i++) {
		puts("Введите имя вершины");
		s = get_str();
		if (!search_in_array(s,G->ptr,G->n)) {
			puts("Элемент с таким именем уже существует");
			puts("Введите 1 ключ :");
			res = get_int(&point[0]);
			if (!res) {
				return 0;
			}
			puts("Введите 2 ключ :");
			res = get_int(&point[1]);
			if (!res) {
				return 0;
			}
			v = (vertex*)calloc(1, sizeof(vertex));
			v->name = s;
			v->point[0] = point[0];
			v->point[1] = point[1];
			insert(v, G);
			adj()
			delete_vertex(v);
		}
	}*/
}

int search_edge(vertex* head, char* s) {
	vertex* ptr = head;
	while (ptr) {
		if (!strcmp(ptr->name, s)) {
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

int d_insert_edge(Graph* G) {
	int n = G->n,i,j;
	puts("Введите имя 1-ой вершины :");
	char* s1 = get_str();
	if (!s1) {
		return 0;
	}
	i = idx(s1, G);
	if (i == -1) {
		puts("Вершины не существует");
		free(s1);
		return 0;
	}
	puts("Введите имя 2-ой вершины :");
	char* s2 = get_str();
	if (!s2) {
		free(s1);
		return 0;
	}
	j = idx(s2, G);
	if (j == -1) {
		puts("Вершины не существует");
		free(s1);
		free(s2);
		return 0;
	}
	if (search_edge(G->ptr[i].next, G->ptr[j].name)) {
		puts("Ребро уже существует");
		free(s1);
		free(s2);
		return 0;
	}
	adj(&G->ptr[i], G->ptr[j]);
	adj(&G->ptr[j], G->ptr[i]);
	free(s1);
	free(s2);
	//printf("Введите вершину смежную с вершиной %s.Если таких вершин нет введите NULL:\n", G->ptr[i].name);
	return 1;
}

void delete_edge(vertex* fv, char* s) {
	vertex* ptr = fv;
	vertex* tmp = NULL;
	while (ptr) {
		if (ptr->next && (!strcmp(ptr->next->name,s))) {
			tmp = ptr->next;
			ptr->next = tmp->next;
			free(tmp->name);
			free(tmp);
		}
		else {
			ptr = ptr->next;
		}
	}
}

vertex* search_list(char* s, Graph* G) {
	int i,n = G->n;
	vertex* ptr = NULL;
	//ptr = &G->ptr[0];
	for (i = 0; i < n; i++) {
		ptr = &G->ptr[i];
		while (ptr) {
			if (!strcmp(ptr->name,s)) {
				return ptr;
			}
			ptr = ptr->next;
		}
	}
}

int d_delete_edge(Graph* G) {
	int i,j;
	puts("Введите имя 1-ой вершины :");
	char* s1 = get_str();
	if (!s1) {
		return 0;
	}
	i = idx(s1, G);
	if (i == -1) {
		puts("Вершины не существует");
		free(s1);
		return 0;
	}
	puts("Введите имя 2-ой вершины :");
	char* s2 = get_str();
	if (!s2) {
		free(s1);
		return 0;
	}
	j = idx(s2, G);
	if (j == -1) {
		puts("Вершины не существует");
		free(s1);
		free(s2);
		return 0;
	}
	if (!search_edge(G->ptr[i].next, G->ptr[j].name)) {
		puts("Ребра не существует");
		free(s1);
		free(s2);
		return 0;
	}
	delete_edge(&G->ptr[i], s2);
	delete_edge(&G->ptr[j], s1);
	free(s1);
	free(s2);
	return 1;
}

void fix_delete_edge(vertex* prev, vertex* ptr) {
	prev->next = ptr->next;
	free(ptr->name);
	free(ptr);
}

void delete_list(vertex* head) {
	vertex* ptr = head;
	while (head) {
		head = head->next;
		free(ptr->name);
		free(ptr);
		ptr = head;
	}
}

int d_delete_vertex(Graph* G) {
	int i,j;
	puts("Введите имя вершины :");
	char* s = get_str();
	if (!s) {
		return 0;
	}
	i = idx(s, G);
	if (i == -1) {
		puts("Вершины не существует");
		free(s);
		return 0;
	}
	//vertex* x = &G->ptr[i];
	vertex* ptr = G->ptr[i].next;
	vertex* prev = &G->ptr[i];
	while (ptr) {
		j = idx(ptr->name, G);
		delete_edge(&G->ptr[j], G->ptr[i].name);
		//ptr = ptr->next;
		fix_delete_edge(prev, ptr);
		ptr = prev->next;
		//ptr = ptr->next;
	}
	if (i == G->n - 1) {
		//delete_list(G->ptr[i].next);
		//G->ptr[i].next = NULL;
		free(G->ptr[i].name);
		G->n--;
	}
	else {
		//delete_list(G->ptr[i].next);
		//G->ptr[i].next = NULL;
		free(G->ptr[i].name);
		lend_up(G, i);
		G->n--;
	}
	puts("Вершина удалена");
	free(s);
	return 1;
}

void delete_graph(Graph* G) {
	if (G) {
		int n = G->n, i;
		for (i = 0; i < n; i++) {
			delete_list(G->ptr[i].next);
			free(G->ptr[i].name);
		}
		free(G->ptr);
	}
		free(G);
}

int dialog(char* s[], int size) {
	//char* s[] = {"0.Quit","1.Insert new element","2.Show table","3.Search element","4.Delete element","5.Search with parent key"};
	int choice, i, n;
	//int size = sizeof(s) / sizeof(char*);
	char* error = "Wrong choice.Try again";
	do {
		n = 0;
		printf("Menu:\n");
		for (i = 0; i < size; i++) {
			puts(s[i]);
		}
		puts("Choose option:");
		n = scanf_s("%d", &choice, sizeof(int));
		if (n < 0) {
			return 0;
		}
		printf("Your choice: %d\n", choice);
		if (choice < 0 || choice >(size - 1)) {
			puts(error);
		}
		scanf_s("%*[^\n]");
		scanf_s("%*c");
	} while (choice < 0 || choice >(size - 1));
	return choice;
}

void show(vertex v) {
	printf("%s", v.name);
}

unsigned int w(vertex v, vertex u) {
	return (v.point[0] - u.point[0]) * (v.point[0] - u.point[0]) + (v.point[1] - u.point[1]) * (v.point[1] - u.point[1]);
}

void delete_pred(vertex** pred, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (pred[i] != NULL && pred[i]->name != NULL) {
			free(pred[i]->name);
			free(pred[i]);
		}
		//vertex* v = pred[2];
	}
	free(pred);
}

vertex** Bellman_Ford(Graph* G, int idx_s, unsigned int(*w)(vertex,vertex),int **dist) {
	int i,j, n = G->n,idx_v;
	unsigned int* d = (unsigned int*)calloc(n, sizeof(unsigned int));
	vertex** pred = (vertex**)calloc(n, sizeof(vertex*));
	for (i = 0; i < n; i++) {
		d[i] = UINT_MAX;
	}
	vertex* v = NULL;
	d[idx_s] = 0;
	for (i = 1; i < n; i++) {
		for (j = 0; j < n; j++) {
			v = G->ptr[j].next;
			while (v) {
				if (d[idx_v = idx(v->name, G)] > d[j] + w(G->ptr[j], *v)) {
					d[idx_v] = d[j] + w(G->ptr[j], *v);
					if (pred[idx_v] != NULL) {
						free(pred[idx_v]->name);
						free(pred[idx_v]);
					}
					pred[idx_v] = create_v_with_copy(G->ptr[j]);
				}
				v = v->next;
			}
		}
	}
	for (j = 0; j < n; j++) {
		v = G->ptr[j].next;
		while (v) {
			if (d[idx(v->name, G)] > d[j] + w(G->ptr[j], *v)) {
				puts("Отказ");
				delete_pred(pred, n);
				free(d);
				return NULL;
			}
			v = v->next;
		}
	}
	*dist = d;
	return pred;
}

int d_show(Graph* G) {
	int i;
	if (!G->n) {
		puts("Пустой граф");
		return 0;
	}
	int n = G->n;
	vertex* v = NULL;
	puts("Граф :");
	for (i = 0; i < n; i++) {
		show(G->ptr[i]);
		v = G->ptr[i].next;
		if (v) {
			printf("-");
		}
		while (v) {
			printf("%s", v->name);
			if (v->next) {
				printf(",");
			}
			v = v->next;
		}
		printf("\n");
	}
	return 1;
}

int d_search_path_BFS(Graph* G) {
	int i, j;
	puts("Введите имя 1-ой вершины :");
	char* s1 = get_str();
	if (!s1) {
		return 0;
	}
	i = idx(s1, G);
	if (i == -1) {
		puts("Вершины не существует");
		free(s1);
		return 0;
	}
	puts("Введите имя 2-ой вершины :");
	char* s2 = get_str();
	if (!s2) {
		free(s1);
		return 0;
	}
	j = idx(s2, G);
	if (j == -1) {
		puts("Вершины не существует");
		free(s1);
		free(s2);
		return 0;
	}
	vertex** pred = BFS(i,j,G);
	if (pred) {
		print_path(i, j, pred, G);
		puts("");
	}
	free(s1);
	free(s2);
	//pred[i - 1];
	delete_pred(pred, G->n);
	return 1;
}

int d_search_min_path_from_s(Graph* G) {
	int i, j;
	puts("Введите имя 1-ой вершины :");
	char* s1 = get_str();
	if (!s1) {
		return 0;
	}
	i = idx(s1, G);
	if (i == -1) {
		puts("Вершины не существует");
		free(s1);
		return 0;
	}
	puts("Введите имя 2-ой вершины :");
	char* s2 = get_str();
	if (!s2) {
		free(s1);
		return 0;
	}
	j = idx(s2, G);
	if (j == -1) {
		puts("Вершины не существует");
		free(s1);
		free(s2);
		return 0;
	}
	int *dist = NULL;
	vertex** pred = Bellman_Ford(G, i, w,&dist);
	if (pred) {
		//puts("Путь:");
		printf("Расстояние: %d\n", dist[j]);
		print_path(i, j, pred, G);
		printf("\n");
	}
	free(s1);
	free(s2);
	delete_pred(pred,G->n);
	free(dist);
	return 1;
}

unsigned int minimum(unsigned int x, unsigned int y) {
	return (x < y) ? x : y;
}

void print_matr_pi(int** P, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", P[i][j]);
		}
		printf("\n");
	}
}

void print_matr_d(unsigned int** P, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%u ", P[i][j]);
		}
		printf("\n");
	}
}

void dist(unsigned int** d, Graph* G,int k, unsigned int(*w)(vertex, vertex)) {
	int i, j, n = G->n;
	unsigned int x, y;
	if (k == 0) {
		//int i,j, n = G->n;
		vertex* v = NULL;
		for (i = 0; i < n; i++) {
			v = &G->ptr[i];
			while (v) {
				/*if (d[idx_v = idx(v->name, G)] > d[j] + w(G->ptr[j], *v)) {
					d[idx_v] = d[j] + w(G->ptr[j], *v);
					pred[idx_v] = create_v_with_copy(G->ptr[j]);
				}*/
				j = idx(v->name, G);
				d[i][j] = w(G->ptr[i], *v);
				v = v->next;
			}
		}
	}
	else {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (d[i][k - 1] <= UINT_MAX - d[k - 1][j]) {
					if (d[i][j] > d[i][k - 1] + d[k - 1][j]) {
						d[i][j] = d[i][k - 1] + d[k - 1][j];
					}
				}
			}
		}
	}
}

void pi(int** P, Graph* G, int k,unsigned int** d) {
	int i, j, n = G->n;
	if (k == 0) {
		//int i,j, n = G->n;
		//vertex* v = NULL;
		/*for (i = 0; i < n; i++) {
			v = G->ptr[i].next;
			while (v) {
				j = idx(v->name, G);
				if (d[i][j] == UINT_MAX || i == j) {
					P[i][j] = -1;
				}
				else {
					P[i][j] = i;
				}
				v = v->next;
			}
		}*/
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (d[i][j] == UINT_MAX || i == j) {
					P[i][j] = -1;
				}
				else {
					P[i][j] = i;
				}
			}
		}
	}
	else {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (d[i][k - 1] <= UINT_MAX - d[k - 1][j]) {
					if (d[i][j] > d[i][k - 1] + d[k - 1][j]) {
						P[i][j] = P[k - 1][j];
					}
				}
			}
		}
	}
}

int** Floyd_Warshall(Graph* G, unsigned int(*w)(vertex, vertex),unsigned int*** distance) {
	unsigned int** d = new_d(G->n);
	int** P = new_pi(G->n);
	int k = 0,i,j,n = G->n;
	for (i = 0; i < n; i++) {
		for (j = 0;j < n; j++) {
			d[i][j] = UINT_MAX;	
		}
	}
	//dist(d,G,k,w);
	/*pi(P, G, k, w, d);
	dist(d, G, k, w);
	k++;*/
	while (k <= n) {
		if (k == 0) {
			dist(d, G, k, w);
			pi(P, G, k, d);
		}
		else {
			pi(P, G, k, d);
			dist(d, G, k, w);
		}
		print_matr_d(d, n);
		puts("");
		print_matr_pi(P, n);
		puts("");
		k++;
	}
	/*for (i = 0; i < n; i++) {
		free(d[i]);
	}*/
	*distance = d;
	return P;
}

void path(int idx_s, int idx_v, int** P,Graph* G) {
	double s = 0.0;
	printf("( %s )<-", G->ptr[idx_v].name);
	int idx = P[idx_s][idx_v],prev_idx = idx_v;
	while (idx != idx_s && idx != -1) {
		printf("( %s )<-", G->ptr[idx].name);
		s = s + sqrt(w(G->ptr[prev_idx], G->ptr[idx]));
		prev_idx = idx;
		idx = P[idx_s][idx];
	}
	if (idx == -1) {
		puts("");
		puts("Не существует такого пути");
			return;
	}
	printf("( %s )\n", G->ptr[idx_s].name);
	s = s + sqrt(w(G->ptr[prev_idx], G->ptr[idx]));
	printf("Длина пути: %lf\n",s);
}

void matr_cpy(unsigned int** dest, int size, unsigned int** source) {
	int i, j, n = size;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			dest[i][j] = source[i][j];
		}
	}
}

void first_three_min_paths(unsigned int** d, int fidxs[], int sidxs[],int size) {
	int n = size,i,j,l,k,s;
	//unsigned int mind[3];
	unsigned int** dist = new_d(n);
	matr_cpy(dist, n, d);
	unsigned int min = UINT_MAX;
	for (s = 0; s < 3; s++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (min > dist[i][j] && i != j) {
					min = dist[i][j];
					l = i;
					k = j;
				}
			}
		}
		fidxs[s] = l;
		sidxs[s] = k;
		dist[l][k] = UINT_MAX;
		min = UINT_MAX;
	}
	for (i = 0; i < n; i++) {
		free(dist[i]);
	}
	free(dist);
}

int d_search_path_FW(Graph* G) {
	if (G->n < 3) {
		puts("Мало вершин");
			return 0;
	}
	unsigned int** d = NULL;
	int** P = Floyd_Warshall(G, w,&d);
	int n = G->n, i, j,k = 3;
	/*puts("Введите имя 1-ой вершины :");
	char* s1 = get_str();
	if (!s1) {
		return 0;
	}
	i = idx(s1, G);
	if (i == -1) {
		puts("Вершины не существует");
		free(s1);
		return 0;
	}
	puts("Введите имя 2-ой вершины :");
	char* s2 = get_str();
	if (!s2) {
		free(s1);
		return 0;
	}
	j = idx(s2, G);
	if (j == -1) {
		puts("Вершины не существует");
		free(s1);
		free(s2);
		return 0;
	}*/
	puts("Первые три кратчайших пути:");
	int fidxs[3], sidxs[3];
	first_three_min_paths(d, fidxs, sidxs, G->n);
	printf("Путь из %s  в %s :\n", G->ptr[fidxs[0]].name, G->ptr[sidxs[0]].name);
    path(fidxs[0], sidxs[0], P, G);
	puts("");
	printf("Путь из %s  в %s :\n", G->ptr[fidxs[1]].name, G->ptr[sidxs[1]].name);
	path(fidxs[1], sidxs[1], P, G);
	puts("");
	printf("Путь из %s  в %s :\n", G->ptr[fidxs[2]].name, G->ptr[sidxs[2]].name);
	path(fidxs[2], sidxs[2], P, G);
	for (i = 0; i < n; i++) {
		free(P[i]);
		free(d[i]);
	}
	free(d);
	free(P);
}

void f_to_v(FILE* fd,vertex* s) {
	int len = 0;
	fread(&len, sizeof(int), 1, fd);
	s->name = (char*)calloc(len, sizeof(char));
	fread(s->name, sizeof(char), len, fd);
	fread(&s->point[0], sizeof(int), 1, fd);
	fread(&s->point[1], sizeof(int), 1, fd);
}
Graph* f_to_g(FILE* fd) {
	int N,i;
	fseek(fd, 0, SEEK_SET);
	fread(&N, sizeof(int), 1, fd);
	Graph* G = new_graph(N);
	vertex v = { NULL,{0,0}};
	for (i = 0; i < N; i++) {
		f_to_v(fd, &v);
		if (idx(v.name, G) == -1) {
			insert(v, G);
			//free(v.name);
		}
		free(v.name);
	}
	return G;
}

void construct_edges(Graph* G, int N) {
	int i;
	for (i = 1; i < N; i++) {
		adj(&G->ptr[0], G->ptr[i]);
		adj(&G->ptr[i], G->ptr[0]);
	}
}

int d_timing(Graph* G) {
	char* fname = NULL;
	int i, j;
	puts("Введите имя файла");
	fname = get_str();
	FILE* fd = NULL;
	fopen_s(&fd, fname, "rb");
	Graph* g = f_to_g(fd);
	construct_edges(g, g->n);
	int n = g->n;
	double T = 0.0;
	clock_t t;
	vertex** pred = NULL;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n;j++) {
			t = clock();
			pred = BFS(i, j, g);
			t = clock() - t;
			delete_pred(pred,n);
			T += (double)t / CLOCKS_PER_SEC;
		}
	}
	unsigned int C = n * (n - 1) / 2;
	double avg = T / C;
	printf("Среднее время поиска (сек.): %lf\n", avg);
	delete_graph(g);
	fclose(fd);
	free(fname);
	return 1;
}

int null(Graph* G) {
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Lab2_header.h"
#include <string.h>

Stack_list* new_list() {
	return (Stack_list*)calloc(1, sizeof(Stack_list));
}

double *new_vector(int size) {
	return (double*)calloc(size, sizeof(double));
}

void push(Stack_list* s,double x) {
	Stack_element* z = (Stack_element*)calloc(1,sizeof(Stack_element));
	z->x = x;
	z->next = s->top;
	s->top = z;
}

void pop(Stack_list* s) {
	if (s->top != NULL) {
		Stack_element* ptr = s->top;
		s->top = ptr->next;
		ptr->next = NULL;
		free(ptr);
	}
}

void delete_list(Stack_list* s) {
	while (s->top != NULL) {
		pop(s);
	}
	if (s->top == NULL) {
		free(s);
	}
}

int get_operand_list(Stack_list* s, double* v) {
	if (s->top != NULL) {
		*v = s->top->x;
		pop(s);
		return 1;
	}
	else {
		return 0;
	}
}

double count_operation(double x,double y, char op) {
	if (op == '+') {
		return x + y;
	}
	if (op == '-') {
		return y - x;
	}
	if (op == '*') {
		return x * y;
	}
	if (op == '/') {
		return y / x;
	}
}

int is_operation(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/') {
		return 1;
	}
	else {
		return 0;
	}
}

char* get_str() {
	char buf[81] = { 0 };
	char* res = NULL;
	int len = 0;
	int n = 0;
	do {
		n = scanf_s("%80[^\n]", buf,sizeof(buf));
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

double process_list(char *str) {
	int i;
	double u,x,y,result;
	char ch;
	Stack_list* s = new_list();
	for (i = 0; *(str + i) != '\0'; i++) {
		ch = *(str + i);
		if (isdigit(ch)) {
			push(s, (double)ch - (double)'0');
		}
		if (is_operation(ch)) {
			get_operand_list(s, &x);
			get_operand_list(s, &y);
			u = count_operation(x,y, ch);
			push(s, u);
		}
	}
	result = s->top->x;
	delete_list(s);
    return result;
}

double process_vector(char* str) {
	int N, top_s = 0,i;
	N = strlen(str);
	double* s = new_vector(N);
	char ch = ' ';
	double u, x, y,res;
	for (i = 0;i < N; i++) {
		ch = *(str + i);
		if (isdigit(ch)) {
			s[top_s] = (double)ch - (double)'0';
			top_s++;
		}
		if (is_operation(ch)) {
			top_s--;
			x = s[top_s];
			top_s--;
			y = s[top_s];
			u = count_operation(x, y, ch);
			s[top_s] = u;
			top_s++;
		}
	}
	res = s[top_s - 1];
	free(s);
	return res;
}

double stack_process(char* s) {
	double res;
	int k;
		printf("Work with stack: \n");
		printf("List: press 1\n");
		printf("Vector: press 2\n");
		scanf_s("%d", &k);
		scanf_s("%*c");
		if (k == 1) {
			res = process_list(s);
		}
		if (k == 2) {
			res = process_vector(s);
		}
		return res;
}


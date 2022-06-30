

#include <stdio.h>
#include <stdlib.h>

/*typedef struct Operand {
	int x;
	Operand  *next;
} Operand;

typedef struct Stack {
	Operand* top;
} Stack;
*/
typedef struct Stack_element {	
	double x;
	char c;
	Stack_element* next;
} Stack_element;

typedef struct Stack_list {
	Stack_element *top;
} Stack_list;

/*Result_list *new_vector(int size) {
	int i;
	Result_Stack* s = (Result_Stack*)calloc(size, sizeof(Result_Stack));
	for (i = 0; i < size; i++) {
		s[i].x = -1;
	}
	return s;
}
*/
//Result_Stack* read_vector(Result_Stack* s, int* top) {}

Stack_list *new_list() {
	return (Stack_list*)calloc(1, sizeof(Stack_list));
}
 /*
void add_element(Result_stack_list *s, Result_list_element *z) {
	if (s->top == NULL) {
		s->top = z;
		z->next = NULL;
		return;

	}
	z->next = s->top;
	s->top = z;
}

void remove_element(Result_stack_list* s) {
	if (s->top != NULL) {
		Result_list_element* ptr = s->top;
		s->top = s->top->next;
		free(ptr);
	}
}
*/
void push(Stack_list *s, Stack_element *z) {
		if (s->top == NULL) {
			s->top = z;
			z->next = NULL;
			return;

		}
		z->next = s->top;
		s->top = z;
}
void pop(Stack_list* s) {
	if (s->top != NULL) {
		Stack_element* ptr = s->top;
		s->top = s->top->next;
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

/*void remove_res_list(Result_stack_list* s) {
	while (s->top != NULL) {
		remove_element(s);
	}
	if (s->top == NULL) {
		free(s);
	}
}
*/
int get_operand_list(Stack_list* s,double *v) {
	if (s->top != NULL) {
		*v = s->top->x;
		pop(s);
		return 1;
	}
	else {
		return 0;
	}
}

double count_op(Stack_list* s, char op,int *res) {
	double x,y;
	int v,l;
	v = get_operand_list(s, &x);
	l = get_operand_list(s, &y);
	if (v && l) {
		*res = 1;
		if (op == '+') {
			return x + y;
		}
		if (op = '-') {
			return y - x;
		}
		if (op = '*') {
			return x * y;
		}
		if (op = '/') {
			return y / x;
		}
	} else {
		*res = 0;
		return 0.0;
	}
}

Stack_list* enter_stack_list(double *res) {
	int n,x,v;
	char ch;
	Stack_list* s = new_list();
	Stack_list* L = new_list();
	Stack_element z;
	printf("Enter your string:\n");
	n = scanf_s("%1d[0-9]",&x,sizeof(int));
	while (n > 0) {
		z.x = x;
		push(L, &z);
		push(s, &z);
		n = scanf_s("%1d[0-9]",&x,sizeof(int));
	}
	if (n == 0) {
		n = scanf_s("%1c[+-*/]",&ch,sizeof(char));
		while (n > 0) {
			z.c = ch;
			push(L, &z);
			z.x = count_op(s, ch, &v);
			if (v == 0) {
				printf("Error\n");
				delete_list(s);
				delete_list(L);
				return NULL;
			}
			push(s, &z);
			n = scanf_s("%1c[+-*/]",&ch,sizeof(char));
		}
		if (n == 0) {
			scanf_s("%*s[^\n]");
			scanf_s("%*c");
			delete_list(s);
			delete_list(L);
			printf("Error.Try again\n");
			return NULL;
		}
		*res = s->top->x;
		delete_list(s);
		return L;
	}
	if (n < 0) {
		delete_list(s);
		delete_list(L);
		return NULL;
	}
}

int main()
{
	double res;
	Stack_list *s = enter_stack_list(&res);
	printf("Result : %lf\n", res);
	delete_list(s);
	return 0;
}


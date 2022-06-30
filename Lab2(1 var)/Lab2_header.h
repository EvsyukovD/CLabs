#pragma once
typedef struct Stack_element {
	double x;
	struct Stack_element* next;
}Stack_element;

typedef struct Stack_list {
	Stack_element* top;
}Stack_list;

Stack_list* new_list();

double* new_vector(int size);

char* get_str();

void push(Stack_list* s, double x);

void pop(Stack_list* s);

void delete_list(Stack_list* s);

int get_operand_list(Stack_list* s, double* v);

double count_operation(double x, double y, char op);

int is_operation(char c);

double process_list(char *str);

double process_vector(char *str);

double stack_process(char* s);

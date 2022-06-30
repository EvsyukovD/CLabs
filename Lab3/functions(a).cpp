#include "Lab3_header.h"

Keyspace1* key1_table(int size) {
	return (Keyspace1*)calloc(size, sizeof(Keyspace1));
}

Keyspace2* key2_table(int size) {
	return (Keyspace2*)calloc(size, sizeof(Keyspace2));
}

int hash(int key, int size) {
	return key % size;
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

int get_float(float* x) {
	int n;
	char* msg = "Error input.Try again";
	do {
		n = scanf_s("%f", x, sizeof(float));
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

int get_int(unsigned int* x) {
	int n;
	char* msg = "Error input.Try again";
	do {
		n = scanf_s("%d", x, sizeof(unsigned int));
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

Item* search_key2(table* T, unsigned int key2) {
	Keyspace2* p = T->ks2;
	Keyspace2* ptr = &p[hash(key2, T->msize2)];
	while (ptr) {
		if (ptr->key == key2) {
			return ptr->info;
		}
		ptr = ptr->next;
	}
	return NULL;
}

Item* search_key1(table* T,const char* key1) {
	Keyspace1* table = T->ks1;
	int i, size = T->csize1;
	for (i = 0; i < size; i++) {
		if (!strcmp(table[i].key, key1)) {
			return table[i].info;
		}
	}
	return NULL;
}

void swap(void* a, void* b, size_t size) {
	char* s = (char*)calloc(size, sizeof(char));
	memcpy(s, a, size);
	memcpy(a, b, size);
	memcpy(b, s, size);
	free(s);
}

table* new_table(int size1, int size2) {
	table* T = (table*)calloc(1, sizeof(table));
	T->ks1 = key1_table(size1);
	T->ks2 = key2_table(size2);
	T->csize1 = 0;
	T->msize1 = size1;
	T->msize2 = size2;
	return T;
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

void push(Keyspace2* head, Item* I) {
	Keyspace2* ptr = (Keyspace2*)calloc(1, sizeof(Keyspace2));
	ptr->key = I->key2;
	ptr->info = I;
}

Item* search_item(table* T, const char* key1, unsigned int key2) {
	Item* I = NULL, * J = NULL;
	I = search_key1(T,key1);
	if (!I) {
		return NULL;
	}
	J = search_key2(T, key2);
	if (!J) {
		return NULL;
	}
	if (I == J) {
		return I;
	}
	else {
		return NULL;
	}
}

void insert_keys1(table* table, Item* I) {
	Keyspace1* ptr = table->ks1;
	ptr[table->csize1].key = I->key1;
	ptr[table->csize1].info = I;
	ptr[table->csize1].par = I->p1;
	table->csize1 = table->csize1 + 1;
}

void insert_keys2(table* table, Item* I) {
	Keyspace2* ptr = table->ks2;
	int j = hash(I->key2, table->msize2);
	if (!ptr[j].info) {
		ptr[j].info = I;
		ptr[j].key = I->key2;
		ptr[j].next = NULL;
	}
	else {
		Keyspace2* p = (Keyspace2*)calloc(1, sizeof(Keyspace2));
		p->next = ptr[j].next;
		ptr[j].next = p;
		p->info = I;
		p->key = I->key2;
	}

}

int insert(table* T, Item* I) {
	if (T->csize1 == T->msize1) {
		printf("Table is overflow\n");
		return 0;
	}
	if (!search_item(T, I->key1, I->key2)) {
		if ((I->p1 == NULL) || (I->p1 && search_key1(T, I->p1))) {
			insert_keys1(T, I);
			insert_keys2(T, I);
			return 1;
		}
		if (I->p1 && !search_key1(T, I->p1)) {
			printf("Parent key is not exist\n");
			return 0;
		}
	}
	else {
		printf("This key(s) have already exist\n");
		return 0;
	}
}

void delete_keys1(Keyspace1* table, int size) {
	int i;
	/*for (i = 0; i < size; i++) {
		if (table[i].info) {
			free(table[i].key);
			free(table[i].par);
		}
	}*/
	free(table);
}

void delete_list(Keyspace2* head) {
	Keyspace2* ptr1 = NULL, * ptr2 = NULL;
	ptr1 = head->next;
	while (ptr1) {
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
	}
}

void delete_keys2(Keyspace2* table, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (table[i].info) {
			delete_list(&table[i]);
		}
	}
	free(table);
}

void itemcpy(Item* i1,Item* i2) {
	int len_s = strlen(i2->info->s);
	int len_key1 = strlen(i2->key1);
	int len_p1 = strlen(i2->p1);
	i1->info->s = (char*)calloc(len_s + 1, sizeof(char));
	i1->key1 = (char*)calloc(len_key1 + 1, sizeof(char));
	i1->p1 = (char*)calloc(len_p1 + 1, sizeof(char));
	strcpy_s(i1->info->s, len_s, i2->info->s);
	strcpy_s(i1->key1, len_key1, i2->key1);
	strcpy_s(i1->p1, len_p1, i2->p1);
	i1->info->x = i2->info->x;
	i1->info->y = i2->info->y;
	i1->key2 = i2->key2;
}

void delete_item(Item* inf) {
	if (inf) {
		free(inf->info->s);
		free(inf->info);
		free(inf->key1);
		free(inf->p1);
		free(inf);
	}
}

void delete_table(table* T) {
	Keyspace1* ks1 = T->ks1;
	int i = 0, n = T->csize1;
	while (i < n) {
		delete_item(ks1[i].info);
		i++;
	}
	delete_keys1(T->ks1, T->msize1);
	delete_keys2(T->ks2, T->msize2);
	free(T);
}

int d_add(table* t) {
	char* msgs[] = { "Enter first float num", "Enter second float num","Enter string" };
	char* key_msgs[] = { "Enter key1:","Enter key2:","Enter parent key.If item haven't got parent key enter NULL:" };
	int r;
	unsigned int key2;
	char* key1 = NULL, * par = NULL;
	puts("Enter keys");
	puts(key_msgs[0]);
	key1 = get_str();
	puts(key_msgs[1]);
	r = get_int(&key2);
	puts(key_msgs[2]);
	par = get_str();
	if (!r || !key1 || !par) {
		free(key1);
		free(par);
		return 0;
	}
	if (!strcmp(par, "NULL")) {
		free(par);
		par = NULL;
	}
	Item* I = (Item*)calloc(1, sizeof(Item));
	Info* inf = (Info*)calloc(1, sizeof(Info));
	puts(msgs[0]);
	r = get_float(&inf->x);
	if (r == 0) {
		free(inf);
		delete_item(I);
		return 0;
	}
	puts(msgs[1]);
	r = get_float(&inf->y);
	if (r == 0) {
		free(inf);
		delete_item(I);
		return 0;
	}
	puts(msgs[2]);
	char* s = get_str();
	if (!s) {
		free(inf);
		delete_item(I);
		return 0;
	}
	inf->s = s;
	I->info = inf;
	I->key1 = key1;
	I->key2 = key2;
	I->p1 = par;
	r = insert(t, I);
	if (r == 0) {
		delete_item(I);
		return 0;
	}
	return 1;
}

int null(void* t) {
	return 0;
}

table* init_table() {
	int res, size;
	puts("Enter size of keyspace:");
	res = get_int(&size);
	if (res) {
		return new_table(size, size);
	}
	else {
		return NULL;
	}
}

void show_item(Item* I) {
	if (I) {
		printf("________________________\n");
		printf("First float: %lf\n", I->info->x);
		printf("Second float: %lf\n", I->info->y);
		printf("String: %s\n", I->info->s);
		printf("First key: %s\n", I->key1);
		printf("Second key: %u\n", I->key2);
		if (I->p1) {
			printf("Parent key: %s\n", I->p1);
		}
		else {
			printf("Parent key: 0\n");
		}
		}
}

int d_show(table* t) {
	int i;
	int N = t->csize1;
	Keyspace1* ks1 = t->ks1;
	printf("Your table:\n");
	for (i = 0; i < N; i++) {
		show_item(ks1[i].info);
	}
	return 1;
}

int d_search(table* t) {
	char* key1 = NULL;
	unsigned int key2;
	int res;
	Item* I;
	puts("Enter first key:");
	key1 = get_str();
	if (!key1) {
		return 0;
	}
	puts("Enter second key");
	res = get_int(&key2);
	if (!res) {
		free(key1);
		return 0;
	}
	I = search_item(t, key1, key2);
	free(key1);
	if (I) {
		show_item(I);
		return 1;
	}
	else {
		puts("Item not exist\n");
		return 0;
	}
}

void full_delete_item(table* t, Item* I) {
	char* par = NULL, * key1 = I->key1;
	int i, size;
	unsigned int key2 = I->key2;
	par = I->p1;
	Keyspace1* ks1 = t->ks1;
	size = t->csize1;
	for (i = 0; i < size; i++) {
		if (!strcmp(ks1[i].key, key1)) {
			swap(&ks1[i].info ,&ks1[size - 1].info,sizeof(Item*));
			swap(&ks1[i].key,&ks1[size - 1].key,sizeof(char*));
			swap(&ks1[i].par,&ks1[size - 1].par,sizeof(char*));
			ks1[size - 1].key = NULL;
			ks1[size - 1].info = NULL;
			ks1[size - 1].par = NULL;
			t->csize1--;
			i = size;
		}
	}
	delete_item(I);
	Keyspace2* p = t->ks2;
	Keyspace2* ptr = &p[hash(key2, t->msize2)], * l = ptr;
	while (ptr) {
		if (ptr->key == key2) {
			if (ptr != &p[hash(key2, t->msize2)]) {
				l->next = ptr->next;
				free(ptr);
				ptr = NULL;
			}
			else {
				if (ptr->next) {
					ptr = ptr->next;
					l->info = ptr->info;
					l->key = ptr->key;
					l->next = ptr->next;
					ptr->info = NULL;
					ptr->next = NULL;
					free(ptr);
					ptr = NULL;
				}
				else {
					l->info = NULL;
					l->key = 0;
				}
			}
		}
		if (ptr) {
			l = ptr;
			ptr = ptr->next;
		}
	}
}

int delete_with_par(table* t, char* par) {
	int i;
	int size = t->csize1;
	Keyspace1* ptr = t->ks1;
	for (i = 0; i < size; i++) {
		if (!strcmp(ptr[i].par, par)) {
			full_delete_item(t, ptr[i].info);
		}
	}
	return 1;
}

int d_delete(table* t) {
	const char* key1 = NULL, * par = NULL;
	unsigned int key2;
	int res, i, size = t->csize1;
	Keyspace1* ptr = t->ks1;
	Item* I;
	puts("Enter first key:");
	key1 = get_str();
	if (!key1) {
		return 0;
	}
	puts("Enter second key");
	res = get_int(&key2);
	if (!res) {
		free(key1);
		return 0;
	}
	I = search_item(t, key1, key2);
	if (I) {
		full_delete_item(t, I);
		for (i = 0; i < t->csize1; i++) {
			if (ptr[i].par && !strcmp(ptr[i].par, key1)) {
				free(ptr[i].info->p1);
				ptr[i].info->p1 = NULL;
				ptr[i].par = NULL;
			}
		}
		puts("Element was deleted");
		free(key1);
		return 1;
	}
	else {
		puts("Element not exist");
		free(key1);
		return 0;
	}
}

int d_search_with_par(table* t) {
	char* par = NULL;
	int N, i;
	int size = t->csize1;
	Item* I = NULL, * p = NULL;
	Info* inf = NULL, * ptr = NULL;
	Keyspace1* ks1 = t->ks1;
	table* res = new_table(size, size);
	Keyspace1* ks1_res = res->ks1;
	puts("Enter parent key");
	par = get_str();
	if (!par) {
		return  0;
	}
	if (!search_key1(t, par)) {
		printf("Parent key not exist\n");
		free(par);
		delete_table(res);
		return 0;
	}
	for (i = 0; i < size; i++) {
		if (ks1[i].par) {
			if (!strcmp(ks1[i].par, par)) {
				p = ks1[i].info;
				ptr = p->info;
				I = (Item*)calloc(1, sizeof(Item));
				inf = (Info*)calloc(1, sizeof(Info));
				inf->x = ptr->x;
				inf->y = ptr->y;
				N = strlen(ptr->s) + 1;
				inf->s = (char*)calloc(N, sizeof(char));
				strcpy_s(inf->s, N, ptr->s);
				I->info = inf;
				I->key1 = (char*)calloc(N, sizeof(char));
				strcpy_s(I->key1, N, p->key1);
				I->key2 = p->key2;
				I->p1 = (char*)calloc(N, sizeof(char));
				strcpy_s(I->p1, N, par);
				insert_keys1(res, I);
				insert_keys2(res, I);
			}
		}
	}
	size = res->csize1;
	for (i = 0; i < size; i++) {
		show_item(ks1_res[i].info);
	}
	free(par);
	delete_table(res);
	return 1;
}


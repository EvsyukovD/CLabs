#include "Lab3(b)_header.h"
#include <string.h>

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

Item* search_key1(table* T, const char* key1) {
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
	I = search_key1(T, key1);
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

int fix_insert(table* T, Item* I) {
	insert_keys1(T, I);
	insert_keys2(T, I);
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

void itemcpy(Item* i1, Item* i2) {
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
		if (inf->info) {
			free(inf->info->s);
		}
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
	//par = I->p1;
	Keyspace1* ks1 = t->ks1;
	size = t->csize1;
	for (i = 0; i < size; i++) {
		if (key1 && ks1[i].key && !strcmp(ks1[i].key, key1)) {
			swap(&ks1[i].info, &ks1[size - 1].info, sizeof(Item*));
			swap(&ks1[i].key, &ks1[size - 1].key, sizeof(char*));
			swap(&ks1[i].par, &ks1[size - 1].par, sizeof(char*));
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

int fget_int(FILE* fd, unsigned int* x) {}

int i_to_f(Item *I,char* fname) {
	FILE* fd = NULL; 
	int i,csize,msize;
	fopen_s(&fd, fname, "r+b");
    I->len_key1 = strlen(I->key1) + 1;
	if (I->p1) {
		I->len_p1 = strlen(I->p1) + 1;
	}
	else {
		I->len_p1 = 1;
	}
	I->lens = strlen(I->info->s) + 1;
	fread(&msize, sizeof(int),1,fd);
	fread(&csize, sizeof(int), 1, fd);
	table* t = new_table(msize, msize);
	Keyspace1* ks1 = t->ks1;
	Item* J = NULL;
	for (i = 0; i < csize; i++) {
		J = (Item*)calloc(1, sizeof(Item));
		J->info = (Info*)calloc(1, sizeof(Info));
		fread(&J->len_key1, sizeof(int), 1, fd);
		J->key1 = (char*)calloc(J->len_key1, sizeof(char));
		fread(J->key1, sizeof(char), J->len_key1, fd);
		fread(&J->key2, sizeof(unsigned int), 1, fd);
		fread(&J->len_p1, sizeof(int), 1, fd);
		J->p1 = (char*)calloc(J->len_p1, sizeof(char));
		fread(J->p1, sizeof(char), J->len_p1, fd);
		fread(&J->info->x, sizeof(float), 1, fd);
		fread(&J->info->y, sizeof(float), 1, fd);
		fread(&J->lens, sizeof(int), 1, fd);
		J->info->s = (char*)calloc(J->lens, sizeof(char));
		fread(J->info->s, sizeof(char), J->lens, fd);
		fread(&J->offset, sizeof(int), 1, fd);
		fix_insert(t, J);
	}
	fclose(fd);
	//t->csize1 = t->csize1 + 1;
	csize++;
	fopen_s(&fd, fname, "wb");
	fseek(fd, 0, SEEK_SET);
	fwrite(&msize, sizeof(int), 1, fd);
	fwrite(&csize, sizeof(int), 1, fd);
	//t->csize1--;
	for (i = 0; i < t->csize1; i++) {
		J = ks1[i].info;
		//fseek(fd, 0, SEEK_END);
		J->offset = ftell(fd);
		fwrite(&J->len_key1, sizeof(int), 1, fd);
		fwrite(J->key1, sizeof(char), J->len_key1, fd);
		fwrite(&J->key2, sizeof(unsigned int), 1, fd);
		fwrite(&J->len_p1, sizeof(int), 1, fd);
		fwrite(J->p1, sizeof(char), J->len_p1, fd);
		/*if (!strcmp(J->p1, "NULL")) {
			free(J->p1);
			J->len_p1 = 1;
			J->p1 = NULL;
		}*/
		fwrite(&J->info->x, sizeof(float), 1, fd);
		fwrite(&J->info->y, sizeof(float), 1, fd);
		fwrite(&J->lens, sizeof(int), 1, fd);
		fwrite(J->info->s, sizeof(char), J->lens, fd);
		fwrite(&J->offset, sizeof(int), 1, fd);
	}
	//fseek(fd, 0L, SEEK_END);
	//I->len_key1 = I->len_key1 - 1;
	//I->lens = I->lens - 1;
	//I->len_p1 = I->len_p1 - 1;
	//fseek(fd, 0, SEEK_END);
	I->offset = ftell(fd);
	fwrite(&I->len_key1, sizeof(int), 1, fd);
	fwrite(I->key1, sizeof(char), I->len_key1, fd);
	fwrite(&I->key2,sizeof(unsigned int),1,fd);
	if (I->p1) {
		fwrite(&I->len_p1, sizeof(int), 1, fd);
		fwrite(I->p1, sizeof(char), I->len_p1, fd);
	}
	else {
		int n = 5;
		fwrite(&n, sizeof(int), 1, fd);
		fwrite("NULL", sizeof(char), n, fd);
	}
	fwrite(&I->info->x, sizeof(float), 1,fd);
	fwrite(&I->info->y, sizeof(float), 1, fd);
	fwrite(&I->lens, sizeof(int), 1, fd);
	fwrite(I->info->s, sizeof(char), I->lens, fd);
	fwrite(&I->offset, sizeof(int), 1, fd);
	//I->len_key1 = I->len_key1 + 1;
	//I->lens = I->lens + 1;
	//I->len_p1 = I->len_p1 + 1;
	fclose(fd);
	delete_table(t);
	puts("Item has been download to file");
	return 1;
}

Item* f_to_i(int offset,FILE* fd) {
	/*FILE* fd = NULL; 
	fopen_s(&fd, fname, "r+b");*/
	//fseek(fd, offset, SEEK_SET);
	int i = 0;
	Item* K = (Item*)calloc(1, sizeof(Item));
	/*fread(&I->len_key1, sizeof(int), 1, fd);
	fread(&I->key1,sizeof(char),I->len_key1,fd);
	fread(&I->key2,sizeof(unsigned int),1,fd);
	fread(&I->len_p1, sizeof(int), 1, fd);
	fread(&I->p1,sizeof(char),I->len_p1,fd);
	fread(&I->info->x, sizeof(float),1,fd);
	fread(&I->info->y, sizeof(float),1,fd);
	fread(&I->lens, sizeof(int), 1, fd);
	fread(&I->info->s,sizeof(char),I->lens,fd);
	fread(&I->offset, sizeof(int), 1, fd);*/
	K->info = (Info*)calloc(1, sizeof(Info));
	fseek(fd, offset, SEEK_SET);
	fread(&K->len_key1, sizeof(int), 1, fd);
	K->key1 = (char*)calloc(K->len_key1, sizeof(char));
	fread(K->key1, sizeof(char), K->len_key1, fd);
	fread(&K->key2, sizeof(unsigned int), 1, fd);
	fread(&K->len_p1, sizeof(int), 1, fd);
	K->p1 = (char*)calloc(K->len_p1, sizeof(char));
	fread(K->p1, sizeof(char), K->len_p1, fd);
	if (!strcmp(K->p1, "NULL")) {
		K->len_p1 = 1;
		free(K->p1);
		K->p1 = NULL;
	}
	fread(&K->info->x, sizeof(float), 1, fd);
	fread(&K->info->y, sizeof(float), 1, fd);
	fread(&K->lens, sizeof(int), 1, fd);
	K->info->s = (char*)calloc(K->lens, sizeof(char));
	fread(K->info->s, sizeof(char), K->lens, fd);
	fread(&K->offset, sizeof(int), 1, fd);
	return K;
}

table* f_to_t(char* fname) {
	FILE* fd = NULL; 
	fopen_s(&fd, fname, "rb");
	int msize,i,csize,res;
	int offset;
	Item* I = NULL;
	if (fd) {
		/*fread(&msize, sizeof(int), 1, fd);
		*t = new_table(msize, msize);
		fread(&csize, sizeof(int), 1, fd);
		(*t)->csize1 = csize;*/
		fread(&msize, sizeof(int), 1, fd);
		fread(&csize, sizeof(int), 1, fd);
		table* r = new_table(msize,msize);
		for (i = 0; i < csize; i++) {
			/*I = (Item*)calloc(1, sizeof(Item));
			//I->info = (Info*)calloc(1, sizeof(Info));
			fread(&I->len_key1,sizeof(int),1,fd);
			fseek(fd,(I->len_key1) * sizeof(char),SEEK_CUR);
			fseek(fd, sizeof(unsigned int),SEEK_CUR);
			fread(&I->len_p1, sizeof(int), 1, fd);
			fseek(fd,(I->len_p1) * sizeof(char),SEEK_CUR);
			fseek(fd, sizeof(float),SEEK_CUR);
			fseek(fd, sizeof(float),SEEK_CUR);
			fread(&I->lens, sizeof(int), 1, fd);
			fseek(fd,(I->lens) * sizeof(char),SEEK_CUR);
			fread(&I->offset, sizeof(int), 1, fd);
			ks1[i].info = I;*/
			offset = ftell(fd);
			I = f_to_i(offset,fd);
			fix_insert(r, I);
		}
		fclose(fd);
		return r;
	}
	else {
		puts("File not exist.Enter size of table");
		res = get_int(&msize);
		if (res) {
			fopen_s(&fd,fname, "w+b");
			csize = 0;
			fwrite(&msize, sizeof(int), 1, fd);
			fwrite(&csize, sizeof(int), 1, fd);
			table* r = new_table(msize, msize);
			fclose(fd);
			return r;
		}
		else {
			return NULL;
		}
	}
}

int t_to_f(table* t, char* fname) {
	FILE* fd = NULL; 
	fopen_s(&fd, fname, "w+b");
	int i,size = t->csize1;
	Keyspace1* ks1 = t->ks1;
	fwrite(&t->msize1, sizeof(int), 1, fd);
	fwrite(&size, sizeof(int), 1, fd);
	fclose(fd);
	for (i = 0; i < size; i++) {
		i_to_f(ks1[i].info, fname);
	}
	//fclose(fd);
	return 1;
}

Item* fsearch_item(char* fname, table* t,char* key1,unsigned int key2,int *key1_ex,int *key2_ex) {
	//FILE* fd = fopen(fname, "r+b");
	int len,i;
	//char* key1 = NULL;
	//unsigned int key2;
	FILE* fd = NULL;
	fopen_s(&fd, fname, "r+b");
	Keyspace1* ks1 = t->ks1;
	Item* K = NULL;
	*key1_ex = 0;
	*key2_ex = 0;
	int csize = t->csize1;
	for (i = 0; i < csize; i++)
	{    
		K = f_to_i(ks1[i].info->offset, fd);
		/*K = (Item*)calloc(1, sizeof(Item));
		K->info = (Info*)calloc(1, sizeof(Info));
		fseek(fd, ks1[i].info->offset, SEEK_SET);
		fread(&K->len_key1, sizeof(int), 1, fd);
		//K->len_key1 = len;
		K->key1 = (char*)calloc(K->len_key1, sizeof(char));
		fread(&K->key1, sizeof(char), K->len_key1, fd);
		fread(&K->key2, sizeof(unsigned int), 1, fd);
		fread(&K->len_p1, sizeof(int), 1, fd);
		K->p1 = (char*)calloc(K->len_p1, sizeof(char));
		fread(&K->p1, sizeof(char), K->len_p1, fd);
		fread(&K->info->x, sizeof(float), 1, fd);
		fread(&K->info->y, sizeof(float), 1, fd);
		fread(&K->lens, sizeof(int), 1, fd);
		K->info->s = (char*)calloc(K->lens, sizeof(char));
		fread(&K->info->s, sizeof(char), K->lens, fd);
		fread(&K->offset, sizeof(int), 1, fd);*/
		if (!strcmp(K->key1, key1)) {
			*key1_ex = 1;
		}
		if (K->key2 == key2) {
			*key2_ex = 1;
		}
		if (!strcmp(K->key1, key1) && key2 == K->key2) {
			//fclose(fd);
			fclose(fd);
			return K;
		}
		delete_item(K);
	}
	//fseek(fd, sizeof(int), SEEK_SET);
	/*if (SEEK_CUR != SEEK_END) {
		fseek(fd, sizeof(int), SEEK_CUR);
	}
	else {
		return NULL;
	}
	Item* J = (Item*)calloc(1, sizeof(Item));
	J->info = (Info*)calloc(1, sizeof(Info));
	do {
		fread(&len, sizeof(int), 1, fd);
		J->len_key1 = len;
		fread(&key1, sizeof(char), len, fd);
		J->key1 = (char*) calloc(len, sizeof(char));
		J->key1 = key1;
		fread(&key2, sizeof(unsigned int), 1, fd);
		J->key2 = key2;
		fread(&len, sizeof(int), 1, fd);
		J->p1 = (char*)calloc(len, sizeof(char));
		J->len_p1 = len;
		fread(&J->p1,sizeof(char),len,fd);
		fread(&J->info->x, sizeof(float), 1,fd);
		fread(&J->info->y, sizeof(float), 1,fd);
		fread(&len, sizeof(int), 1, fd);
		J->lens = len;
		J->info->s = (char*)calloc(len, sizeof(char));
		fread(&J->info->s, sizeof(char),len,fd);
		fread(&J->offset,sizeof(int),1,fd);
	} while (SEEK_CUR != SEEK_END && (strcmp(key1, I->key1) || key2 != I->key2));*/
	/*if (!strcmp(key1, I->key1) && key2 == I->key2) {
		fclose(fd);
		return J;
	}
	else {
		delete_item(J);
		fclose(fd);
		return NULL;
	}*/
	fclose(fd);	
	return NULL;
}

int fsearch_par(table* t, char* fname,char* par) {
	Keyspace1* ks1 = t->ks1;
	int i;
	FILE* fd = NULL;
	fopen_s(&fd, fname, "r+b");
	for (i = 0; i < t->csize1; i++) {
		Item* I = f_to_i(ks1[i].info->offset,fd);
		if (I->p1 && !strcmp(I->p1, par)) {
			delete_item(I);
			return 1;
		}
	}
	fclose(fd);
	return 0;
}

int fd_add(table* t,char* fname) {
	char* msgs[] = { "Enter first float num", "Enter second float num","Enter string" };
	char* key_msgs[] = { "Enter key1:","Enter key2:","Enter parent key.If item haven't got parent key enter NULL:" };
	int r,key1_ex,key2_ex;
	unsigned int key2;
	char* key1 = NULL, * par = NULL;
	Item* G = NULL;
	if (t->csize1 == t->msize1) {
		puts("Table is overflow");
		return 0;
	}
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
	if (!(G = fsearch_item(fname,t,I->key1, I->key2, &key1_ex, &key2_ex)) && !key1_ex && !key2_ex) {
		i_to_f(I, fname);
		//t->csize1++;
		fix_insert(t, I);
		free(I->info->s);
		free(I->info);
		free(I->key1);
		free(I->p1);
		I->info = NULL;
		I->key1 = NULL;
		I->p1 = NULL;
		//delete_item(I);
		return 1;
	}
	else if (G) {
		puts("Item is exist");
	}
	if (key1_ex) {
		puts("First key is exist");
	}
	if (key2_ex) {
		puts("Second key is exist");
	}
	delete_item(G);
	//delete_item(I);
	return 0;
}

int fd_show(table* t,char *fname) {
	int i;
	int N = t->csize1;
	Keyspace1* ks1 = t->ks1;
	Item* I = NULL;
	FILE* fd = NULL;
	fopen_s(&fd, fname, "r+b");
	printf("Your table:\n");
	for (i = 0; i < N; i++) {
		I = f_to_i(ks1[i].info->offset, fd);
		show_item(I);
		delete_item(I);
	}
	fclose(fd);
	return 1;
}

int fd_search(table* t,char* fname) {
	char* key1 = NULL;
	unsigned int key2;
	int res,key1_ex,key2_ex;
	Item* I = NULL;
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
	I = fsearch_item(fname,t, key1, key2,&key1_ex,&key2_ex);
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

int fd_search_with_par(table* t, char* fname) {
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
	if (!fsearch_par(t,fname,par)) {
		printf("Parent key not exist\n");
		free(par);
		delete_table(res);
		return 0;
	}
	FILE* fd = NULL;
	fopen_s(&fd, fname, "r+b");
	for (i = 0; i < size; i++) {
		/*if (ks1[i].par) {
			if (!strcmp(ks1[i].par, par)) {
				p = f_to_i();
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
		}*/
		I = f_to_i(ks1[i].info->offset,fd);
		insert(res, I);
	}
	fclose(fd);
	size = res->csize1;
	for (i = 0; i < size; i++) {
		show_item(ks1_res[i].info);
	}
	free(par);
	delete_table(res);
	return 1;
}

int fd_delete(table* t, char* fname) {
	const char* key1 = NULL, * par = NULL;
	unsigned int key2;
	int res, i, size = t->csize1,key1_ex,key2_ex;
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
	I = fsearch_item(fname,t, key1, key2,&key1_ex,&key2_ex);
	if (I) {
		table* res = f_to_t(fname);
		Keyspace1* ptr = res->ks1;
		Keyspace1* p = t->ks1;
		for (i = 0; i < t->csize1; i++) {
			if (p[i].info->offset == I->offset) {
				p[i].info->lens = 0;
				p[i].info->len_key1 = 0;
				p[i].info->len_p1 = 0;
				p[i].info->offset = 0;
			    full_delete_item(t, I);
				//free(p[i].info);
				//p[i].info = NULL;
				//swap(&p[i].info, &p[(t->csize1) - 1].info, sizeof(Item*));
				i = t->csize1;
			}
		}
		Item* J = fsearch_item(fname, res, key1, key2, &key1_ex, &key2_ex);
		full_delete_item(res, J);
		for (i = 0; i < res->csize1; i++) {
			if (ptr[i].par && !strcmp(ptr[i].par, key1)) {
				free(ptr[i].info->p1);
				ptr[i].info->p1 = NULL;
				ptr[i].par = NULL;
			}
		}
		for (i = 0; i < t->csize1; i++) {
			if (p[i].par && !strcmp(p[i].par, key1)) {
				free(p[i].info->p1);
				p[i].info->p1 = NULL;
				p[i].par = NULL;
			}
		}

		t_to_f(res, fname);
		//t->csize1 = t->csize1 - 1;
		puts("Element was deleted");
		delete_table(res);
		free(key1);
		return 1;
	}
	else {
		puts("Element not exist");
		free(key1);
		return 0;
	}
}

/*int d_t_to_f(table* t,char* fname) {
	FILE* fd = fopen(fname, "w+b");
    t_to_f(t, fd);
	fclose(fd);
	puts("Table has been download to file");
	return 1;
}*/
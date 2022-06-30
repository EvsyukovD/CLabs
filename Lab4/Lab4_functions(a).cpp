#include "Lab4_header(a).h"

tree* new_tree() {
	return (tree*)calloc(1, sizeof(tree));
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

int get_key(unsigned int* x) {
	int n;
	char* msg = "Error input.Try again";
	do {
		n = scanf_s("%d", x, sizeof(unsigned int));
		if (n == 0) {
			//puts(msg);
			scanf_s("%*c");
			return 0;
		}

	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return 1;
}

Node* tree_search_one(unsigned int key, tree* t) {
	Node* ptr = t->root;
	int k = 0, n;
	while (ptr) {
		if (ptr->key > key) {
			ptr = ptr->left;
		}
		else if (ptr->key < key) {
			ptr = ptr->right;
		}
		else if (ptr->key == key) {
			return ptr;
		}
	}
	return NULL;
}

Node* tree_search_all(unsigned int key, tree* t) {
	Node* ptr = t->root;
	int k = 0,n;
	while (ptr) {
		if (ptr && (ptr->key > key)) {
			ptr = ptr->left;
		}
		if (ptr && (ptr->key < key)) {
			ptr = ptr->right;
		}
		if (ptr && (ptr->key == key)) {
			Node* p = ptr;
			while (ptr && (ptr->key == key)) {
				k++;
				ptr = ptr->next;
			}
			if (k == 1) {
				return p;
			}
			printf("Tree have %d equal keys.Choose one from 1 to %d:\n", k, k);
			get_int(&n);
			k = 1;
			ptr = p;
			while (k < n) {
				ptr = ptr->next;
				k++;
			}
			return ptr;
		}
	}
	puts("Key is not exist");
	return NULL;
}

Node* fix_tree_search_all(unsigned int key, tree* t) {
	Node* ptr = t->root;
	int k = 0,m = 0;
	static int n = 1;
	while (ptr) {
		if (ptr && (ptr->key > key)) {
			ptr = ptr->left;
		}
		if (ptr && (ptr->key < key)) {
			ptr = ptr->right;
		}
		if (ptr && (ptr->key == key)) {
			Node* p = ptr;
			while (ptr && (ptr->key == key)) {
				k++;
				ptr = successor(ptr);
			}
			if (k == 1) {
				n = 1;
				return p;
			}
			m = k;
			//printf("Tree have %d equal keys.Choose one from 1 to %d:\n", k, k);
			//get_int(&n);
			k = 1;
			ptr = p;
			while (k < n) {
				ptr = successor(ptr);
				k++;
			}
			n++;
			if (n > m) {
				n = 1;
			}
			return ptr;
		}
	}
	puts("Key is not exist");
	return NULL;
}

Node* tree_max(Node* p) {
	Node* ptr = p;
	if (ptr) {
		while (ptr->right) {
			ptr = ptr->right;
		}
	}
	return ptr;
}

Node* tree_min(Node* p) {
	Node* ptr = p;
	if (ptr) {
		while (ptr->left) {
			ptr = ptr->left;
		}
	}
	return ptr;
}

Node* successor(Node* p) {
	Node* ptr = NULL;
	if (p->right) {
		return tree_min(p->right);
	}
	ptr = p->parent;
	while (ptr && (p == ptr->right)) {
		p = ptr;
		ptr = ptr->parent;
	}
	return ptr;
}

Node* predecessor(Node* p) {
	Node* ptr = NULL;
	if (p->left) {
		return tree_max(p->left);
	}
	ptr = p->parent;
	while (ptr && (p == ptr->left)) {
		p = ptr;
		ptr = ptr->parent;
	}
	return ptr;
}

int tree_insert(Node* p, tree* t) {
	Node* par = NULL, *ptr = NULL;
	if (t->root == NULL) {
		t->root = p;
		return 1;
	}
	ptr = t->root;
	while (ptr) {
		par = ptr;
		if (p->key < ptr->key) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}
	if (par->key > p->key) {
		par->left = p;
		p->parent = par;
	}
	else {
		par->right = p;
		p->parent = par;
	}
	p->next = successor(p, t);
	p->prev = predecessor(p, t);
	Node* prev = p->prev;
	Node* succ = p->next;
	if (prev) {
		prev->next = p;
	}
	if (succ) {
		succ->prev = p;
	}
	return 1;
}

int fix_tree_delete(unsigned int key, tree* t) {
	int l = 0;
	Node* x = tree_search_one(key, t);
	if (!x) {
		return 0;
	}
	Node* y = NULL, * p = NULL, * par = NULL;
	if ((x->left == NULL) || (x->right == NULL)) {
		y = x;
	}
	else {
		y = x->next;
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
		x->key = y->key;
		free(x->info.s);
		x->info = y->info;
		x->next = y->next;
		if (y->next) {
			y->next->prev = x;
		}
	}
	else {
		Node* ps = y->next;
		Node* ppr = y->prev;
		if (ppr) {
			ppr->next = ps;
		}
		if (ps) {
			ps->prev = ppr;
		}
	}
	if (!l) {
		free(y->info.s);
	}
	free(y);
	return 1;
}

int tree_delete(unsigned int key, tree* t) {
	int l = 0;
	Node* x = tree_search_all(key, t);
	if (!x) {
		return 0;
	}
	Node* y = NULL,*p = NULL,*par = NULL;
	if ((x->left == NULL) || (x->right == NULL)) {
		y = x;
	}
	else {
		y = x->next;
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
		x->key = y->key;
		free(x->info.s);
		x->info = y->info;
		x->next = y->next;
		if (y->next) {
			y->next->prev = x;
		}
	}
	else {
		Node* ps = y->next;
		Node* ppr = y->prev;
		if (ppr) {
			ppr->next = ps;
		}
		if (ps) {
			ps->prev = ppr;
		}
	}
	if (!l) {
		free(y->info.s);
	}
	free(y);
	return 1;
}

int show(Node* p) {
	if (p) {
		puts("___________________");
		printf("Key: %u\n", p->key);
		printf("Info:\n");
		printf("Float num: %lf", p->info.x);
		printf("String: %s\n", p->info.s);
		return 1;
	}
	return 0;
}

int d_show_max(tree* t) {
 long int key;
	int res = 0;
	puts("Enter key:");
	res = scanf_s("%d",&key);
	Node* p = NULL;
	puts("Elements:");
	if (key >= 0) {
		p = tree_max(t->root);
		while (p) {
			if (p->key > key) {
				show(p);
			}
			p = p->prev;
		}
	}
	else {
		p = tree_max(t->root);
		while (p) {
		    show(p);
		    p = p->prev;
		}
	}
	return 1;
}

int d_delete(tree* t) {
	unsigned int key;
	int res;
	puts("Enter key:");
	res = get_int(&key);
	if (!res) {
		return 0;
	}
	res = tree_delete(key, t);
	return res;
}

int d_insert(tree* t) {
	unsigned int key;
	float x;
	char* s = NULL;
	int res;
	puts("Enter key:");
	res = get_int(&key);
	if (!res) {
		return 0;
	}
	puts("Enter float num:");
	res = get_float(&x);
	if (!res) {
		return 0;
	}
	puts("Enter string");
	s = get_str();
	if (!s) {
		return 0;
	}
	Node* p = (Node*)calloc(1, sizeof(Node));
	p->info.s = s;
	p->info.x = x;
	p->key = key;
	tree_insert(p, t);
	return 1;
}

int d_search(tree* t) {
	unsigned int key;
	int res;
	puts("Enter key:");
	res = get_int(&key);
	if (!res) {
		return 0;
	}
	Node* p = tree_search_all(key, t);
	if (p) {
		puts("Element:");
		show(p);
		return 1;
	}
	else {
		return 0;
	}
}

int d_search_max(tree* t) {
	unsigned int key;
	int res;
	puts("Enter key:");
	res = get_int(&key);
	if (!res) {
		return 0;
	}
	Node* ptr = tree_max(t->root);
	while (ptr) {
		if (ptr->key < key) {
			ptr = tree_search_all(ptr->key, t);
			puts("Max element:");
			show(ptr);
			return 1;
		}
		ptr = ptr->prev;
	}
	puts("Maximum doesn't exist");
	return 0;
}

void delete_tree(tree* t) {
	if (t && t->root) {
		Node* p = tree_min(t->root);
		//Node* ptr = successor(p,t), *ptr2 = NULL;
		while (p) {
		    //ptr2 = successor(ptr,t);///
			//tree_delete(ptr->key, t);///проблемы здесь
			//ptr = ptr2;///
			fix_tree_delete(p->key, t);
			p = tree_min(t->root);
		}
		/*if (p) {
			tree_delete(p->key, t);
		}*/
	}
	free(t);
	}

int null(tree* t) {
	return 0;
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

Node* f_to_e(FILE* fd) {
	Node* p = (Node*)calloc(1, sizeof(Node));
	int size;
	fread(&p->key, sizeof(unsigned int), 1, fd);
	fread(&p->info.x, sizeof(float), 1, fd);
	fread(&size, sizeof(int), 1, fd);
	p->info.s = (char*)calloc(size, sizeof(char));
	fread(p->info.s, sizeof(char), size, fd);
	return p;
}

tree* f_to_tr(char* fname) {
	FILE* fd = NULL;
	tree* t = NULL;
	int N;
	fopen_s(&fd, fname, "rb");
	fseek(fd, 0, SEEK_SET);
	if (fd) {
		t = new_tree();
		fread(&N, sizeof(int), 1, fd);
		while (N) {
			Node* p = f_to_e(fd);
			tree_insert(p, t);
			N = N - 1;
		}
		fclose(fd);
	}
	return t;
}

int list_parents(Node* end,Node* p) {
	int h = 0;
	Node* ptr = end;
	while (ptr != p) {
		h++;
		ptr = ptr->parent;
	}
	return h;
}

void show_keys(unsigned int key) {
	printf("(%u)", key);
}

void round_for_show(Node* ptr, int level) {
	int i;
	if (ptr) {
		round_for_show(ptr->right, level + 1);
	}
	if (ptr == NULL) {
		printf("\n");
		//printf("       ");
		return;
	}
	//show_keys(ptr->p.key);
	for (i = 0; i < level; i++) {
		printf("        ");
	}
	show_keys(ptr->key);
	level++;
	//round_for_show(ptr->right,level + 1);
	round_for_show(ptr->left, level);
}

int d_show_tree(tree* t) {
	puts("Your tree:");
	round_for_show(t->root, 0);
	return 1;
}

int maximum(int x, int y) {
	return (x > y) ? x : y;
}

int height(Node* p) {
	Node* ptr = tree_min(p);
	int h1 = 0,h = 0;
	while (ptr) {
		h1 = list_parents(ptr, p);
		ptr = successor(ptr);
		h = maximum(h1, h);
	}
	return h;
}

int d_time(void* s) {
	puts("Enter file name:");
	char* fname = get_str();
	tree* t = f_to_tr(fname);
	double T = 0.0;
	clock_t time;
	Node* p = tree_min(t->root);
	int N = 0;
	int h = height(t->root);
	printf("Height: %d\n", h);
	while (p) {
		time = clock();
		fix_tree_search_all(p->key, t);
		time = clock() - time;
		T += (double)time / CLOCKS_PER_SEC;
		p = successor(p);
		N++;
	}
	double avg_time = T / N;
	printf("Average time(millsec): %.8lf\n", avg_time * 1000.0);
	delete_tree(t);
	free(fname);
	return 1;
}
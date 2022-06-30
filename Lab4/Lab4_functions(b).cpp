#include "Lab4_header(b).h"
#include <limits.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <time.h>

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

void lend_left(Point* l, int size,int idx) {
    int i;
    for (i = idx - 1; i < size; i++) {
        l[i] = l[i + 1];
    }
}

void delete_in_array(Point* s, int key[],int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (s[i].key[0] == key[0] && s[i].key[1] == key[1]) {
            s[i].info = NULL;
            s[i].key[0] = 0;
            s[i].key[1] = 0;
            if (i != size - 1) {
                lend_left(s, size, i + 1);
                return;
            }
        }
    }
}

unsigned int maximum( unsigned int x, unsigned int y) {
    return (x > y) ? x : y;
}

unsigned int minimum(unsigned int x, unsigned int y) {
    return (x > y) ? y : x;
}

void swap(Point* x, Point* y) {
    Point t;
    t = *x;
    *x = *y;
    *y = t;
}

void lend_right(Point* l, int size) {
    int i;
    for (i = size - 1; i >= 0; i--) {
        l[i + 1] = l[i];
    }
}

void insert_p(Point* l,int size,Point p,int axis) {
    int i,j = size;
    //lend_right(l, size);
    l[size] = p;
    for (i = size - 1; i >= 0; i--) {
        if (l[i].key[axis] > l[j].key[axis]) {
            swap(&l[i], &l[j]);
            j = i;
        }
    }
}

void deep_search(Node* root, int depth,Node** res,int h) {
    if (root == NULL) {
        return;
    }
    if (h == depth) {
        if (root) {
            *res = root;
        }
    }
    if (h + 1 > depth) {
        return;
    }
    deep_search(root->left, depth, res, h + 1);
    deep_search(root->right, depth, res, h + 1);
}

int search_in_array(Point* s,int size, int key[]) {
    int i;
    for (i = 0; i < size; i++) {
        if (s[i].key[0] == key[0] && s[i].key[1] == key[1]) {
            return 1;
        }
    }
    return 0;
}

void round_level(Node* ptr,Node* p,int depth,int h) {
    //static int h = 0;
    if (ptr == NULL) {
        return;
    }
    if (h == depth) {
        if (!search_in_array(p->level, p->n, ptr->p.key)) {
            insert_p(p->level, p->n, ptr->p, depth % 2);
            p->n++;
            if (!search_in_array(ptr->level, ptr->n, p->p.key)) {
                insert_p(ptr->level, ptr->n, p->p, depth % 2);
                ptr->n++;
            }
        }
    }
    if (h + 1 > depth) {
        return;
    }
    round_level(ptr->left,p,depth,h + 1);
    round_level(ptr->right,p,depth,h + 1);
}

Node* search(int key[], tree* t) {
    int axis = 0;
    Node* ptr = t->root;
    while (ptr) {
        axis = axis % 2;
        if (ptr->p.key[0] == key[0] && ptr->p.key[1] == key[1]) {
            return ptr;
        }
        if (ptr->p.key[axis] > key[axis]) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
        axis++;
    }
    return NULL;
}

unsigned int search_deep(int key[], tree* t) {
    if (t->root == NULL) {
        return 0;
    }
    unsigned int depth = 0;
    int plane;
    Node* ptr = t->root;
    while (ptr) {
        plane = depth % 2;
        if (ptr->p.key[plane] > key[plane]) {
            ptr = ptr->left;
            depth++;
        }
        else {
            ptr = ptr->right;
            depth++;
        }
        if (ptr == NULL) {
            return depth;
        }
    }
}

void round_max_dist(int x,int y,Node* v,unsigned int *d2) {
    unsigned int r2 = 0;
    if (v == NULL) {
        return;
    }
    if (v) {
        r2 = (x - v->p.key[0]) * (x - v->p.key[0]) + (y - v->p.key[1]) * (y - v->p.key[1]);
        *d2 = maximum(r2, *d2);
        round_max_dist(x,y,v->left,d2);
        round_max_dist(x,y,v->right,d2);
    }

}

void round_min_dist(int x, int y, Node* v, unsigned int* d2) {
    unsigned int r2 = 0;
    if (v == NULL) {
        return;
    }
    if (v) {
        r2 = (x - v->p.key[0]) * (x - v->p.key[0]) + (y - v->p.key[1]) * (y - v->p.key[1]);
        *d2 = minimum(r2, d2);
        round_min_dist(x, y, v->left, d2);
        round_min_dist(x, y, v->right, d2);
    }

}

void show(Node* v) {
    puts("_____________");
    printf("First key : %d\n", v->p.key[0]);
    printf("Second key : %d\n", v->p.key[1]);
    printf("First float number: %lf\n", v->p.info->x);
    printf("Second float number: %lf\n", v->p.info->y);
    printf("String: %s\n", v->p.info->s);
}

void round_equal_dist(int x,int y,Node* v, unsigned int d2) {
    unsigned int r2 = 0;
    if (v == NULL) {
        return;
    }
    if (v) {
        r2 = (x - v->p.key[0]) * (x - v->p.key[0]) + (y - v->p.key[1]) * (y - v->p.key[1]);
        if (r2 == d2) {
            show(v);
        }
        round_equal_dist(x,y,v->left, d2);
        round_equal_dist(x,y,v->right, d2);
    }
}

void region_max(int x,int y,tree* t) {
    unsigned int d2 = 0;
    round_max_dist(x,y,t->root, &d2);
    round_equal_dist(x,y,t->root, d2);
}

void round_less_this_keys(int key[],Node* v,int h) {
    if (v == NULL) {
        return;
    }
    int cd = h % 2;
    if (v->p.key[cd] <= key[cd]) {
        show(v);
    }
    round_less_this_keys(key, v->left, h + 1);
    round_less_this_keys(key, v->right, h + 1);
}

void round_less_this_key(int key, int axis, Node* v,int h) {
    if (v == NULL) {
        return;
    }
    if (axis == h % 2 && v->p.key[axis] <= key) {
        show(v);
    }
    round_less_this_key(key, axis, v->left,h + 1);
    round_less_this_key(key, axis, v->right,h + 1);
}

void first_equal_min_dist(int x, int y, Node* v, unsigned int d2,Node** ptr) {
    unsigned int r2 = 0;
    if (v == NULL) {
        return NULL;
    }
    if (v) {
        r2 = (x - v->p.key[0]) * (x - v->p.key[0]) + (y - v->p.key[1]) * (y - v->p.key[1]);
        if (r2 == d2) {
            *ptr = v;
            return ;
        }
        first_equal_min_dist(x, y, v->left, d2,ptr);
        first_equal_min_dist(x, y, v->right, d2,ptr);
    }
}

void search_fixup(Point* s,int key[],int size,tree* t) {
    int i;
    Node* p = NULL;
    for (i = 0; i < size; i++) {
        p = search(s[i].key, t);
        if (p) {
            delete_in_array(p->level, key, p->n);
            p->n--;
        }
        else {
            delete_in_array(s,s[i].key, size);
        }
    }
}

Node* successor(Node* p,tree* t) {
    unsigned int d2 = UINT_MAX;
    round_min_dist(p->p.key[0], p->p.key[1], t->root, &d2);
    Node* res = NULL; 
    first_equal_min_dist(p->p.key[0], p->p.key[1], t->root, d2,&res);
    return res;
}

/*Node* tree_delete(int key[],tree* t) {
    int l = 0;
    Node* x = search(key, t);
    if (!x) {
        return 0;
    }
    Node* y = NULL, * p = NULL, * par = NULL;
    if ((x->left == NULL) || (x->right == NULL)) {
        y = x;
    }
    else {
        y = successor(x,t);
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
        x->p.key[0] = y->p.key[0];
        x->p.key[1] = y->p.key[1];
        free(x->p.info->s);
        x->p.info = y->p.info;
        delete_in_array(x->level, x->p.key, x->n);
        --(x->n);
        int axis = (x->depth) % 2;
        insert_p(x->level, x->n, x->p, axis);
    }
   
    if (!l) {
        free(y->p.info->s);
    }

    free(y);
    return 1;
}
*/
int insert(Node* p, tree* t) {
    if (t->root == NULL) {
        t->root = p;
        //p->level = (Point*)calloc(t->N, sizeof(Point));
        p->level[0] = p->p;
        p->n++;
        return 1;
    }
    unsigned int depth = 0;
    int plane;
    Node* ptr = t->root,*prev = NULL;
    while (ptr) {
        plane = depth % 2;
        prev = ptr;
            if (ptr->p.key[plane] > p->p.key[plane]) {
                ptr = ptr->left;
                depth++;
            }
            else {
                ptr = ptr->right;
                depth++;
            }
        if (ptr == NULL) {
            if (prev->p.key[plane] > p->p.key[plane]) {
                prev->left = p;
            }
            else {
                    prev->right = p;
            }
            p->parent = prev;
            round_level(t->root,p,depth,0);
            /*int i;
            Node* p2 = NULL;
            for (i = 0; i < p->n; i++) {
                if (p->level[i].key[0] != p->p.key[0] || p->level[i].key[1] != p->p.key[1]) {
                    p2 = search(p->level[i].key[0], p->level[i].key[1], t);
                    insert_p(p2->level, p2->n, p->p, plane);
                    p2->n++;
                }
            }*/
            return 1;
        }
    }
}

Node* minNode(Node* x, Node* y, Node* z, int d) {
    Node* res = x;
    if (y != NULL && y->p.key[d] < res->p.key[d]) {
        res = y;
    }
    if (z != NULL && z->p.key[d] < res->p.key[d]){
        res = z;
    }
    return res;
}

Node* maxNode(Node* x, Node* y, Node* z, int d) {
    Node* res = x;
    if (y != NULL && y->p.key[d] > res->p.key[d]) {
        res = y;
    }
    if (z != NULL && z->p.key[d] > res->p.key[d]) {
        res = z;
    }
    return res;
}

Node* findMaxRec(Node* root, int d, unsigned depth) {
    if (root == NULL) {
        return NULL;
    }
    unsigned cd = depth % 2;

    if (cd == d) {

        if (root->right == NULL) {

            return root;
        }
        return findMaxRec(root->right, d, depth + 1);
    }
    return maxNode(root,
        findMaxRec(root->left, d, depth + 1),
        findMaxRec(root->right, d, depth + 1), d);
}

Node* findMax(Node* root, int d) {
    return findMaxRec(root, d, 0);
}


Node* findMinRec(Node* root, int d, unsigned depth) {
    if (root == NULL) {
        return NULL;
    }
    unsigned cd = depth % 2;

    if (cd == d) {

        if (root->left == NULL) {

            return root;
        }
        return findMinRec(root->left, d, depth + 1);
    }
    return minNode(root,
        findMinRec(root->left, d, depth + 1),
        findMinRec(root->right, d, depth + 1), d);
}

Node* findMin(Node* root, int d) {
    return findMinRec(root, d, 0);
}

Node* deleteNodeRec(Node* root, int point[], int depth,tree* t){
    int h,len = 0;
    if (root == NULL) {
        return NULL;
    }
    int cd = depth % 2;
    if (root->p.key[0] == point[0] && root->p.key[1] == point[1]){
       if (root->right != NULL){
             Node* min = findMin(root->right, cd);
             delete_in_array(root->level, root->p.key, root->n);
             root->n--;
             search_fixup(root->level, root->p.key, root->n, t);
             root->p.key[0] = min->p.key[0];
             root->p.key[1] = min->p.key[1];
             free(root->p.info->s);
             //free(root->p.info);
             root->p.info->x = min->p.info->x;
             root->p.info->y = min->p.info->y;
             len = strlen(min->p.info->s) + 1;
             root->p.info->s = (char*)calloc(len, sizeof(char));
             strcpy_s(root->p.info->s, len, min->p.info->s);
             //root->p.info = min->p.info;
             round_level(t->root, root, depth, 0);
             root->right = deleteNodeRec(root->right, min->p.key, depth + 1,t);
        }
        else if (root->left != NULL){
            Node* max = findMax(root->left, cd);
            delete_in_array(root->level, root->p.key, root->n);
            root->n--;
            search_fixup(root->level, root->p.key, root->n, t);
            root->p.key[0] = max->p.key[0];
            root->p.key[1] = max->p.key[1];
            free(root->p.info->s);
            //free(root->p.info);
            root->p.info->x = max->p.info->x;
            root->p.info->y = max->p.info->y;
            len = strlen(max->p.info->s) + 1;
            root->p.info->s = (char*)calloc(len, sizeof(char));
            strcpy_s(root->p.info->s, len, max->p.info->s);
            //root->p.info = min->p.info;
            round_level(t->root, root, depth, 0);
            root->left = deleteNodeRec(root->left, max->p.key, depth + 1,t);
        }
        else{
           Node* par = root->parent;
           delete_in_array(root->level, root->p.key, root->n);
           root->n--;
           search_fixup(root->level, root->p.key,root->n,t);
           //if ((par && !(par->p.key[0] == root->p.key[0] && par->p.key[1] == root->p.key[1])) || !par) {
               free(root->p.info->s);
               free(root->p.info);
          // }
            /*delete_in_array(root->level, root->p.key, root->n); 
            root->n--;
            search_fixup(root->level, root->p.key, root->n, t);*/
            free(root->level);
            free(root);
            return NULL;
        }

        return root;
    }
    if (point[cd] < root->p.key[cd]) {
        root->left = deleteNodeRec(root->left, point, depth + 1,t);
    }
    else {
        root->right = deleteNodeRec(root->right, point, depth + 1,t);
    }
    return root;
}

void show_keys(int key[]) {
    printf("(%d ; %d)", key[0], key[1]);
}

void round_for_show(Node* ptr,int level) {
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
    show_keys(ptr->p.key);
    level++;
    //round_for_show(ptr->right,level + 1);
    round_for_show(ptr->left,level);
}

Node* deleteNode(int point[],tree* t){
    return deleteNodeRec(t->root, point, 0,t);
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->p.key[1] > r->p.key[1]) {
        l->right = merge(l->right, r);
        return l;
    }
    else {
        r->left = merge(l, r->left);
        return r;
    }
}

Pair split(Node* p, int x) {
    Pair q = { NULL,NULL };
    Pair res = { NULL,NULL };
    if (!p) return q;
    if (p->p.key[0] <= x) {
        q = split(p->right, x);
        p->right = q.x;
        res.x = p;
        res.y = q.y;
        return res;
    }
    else {
        Pair q = split(p->left, x);
        p->left = q.y;
        res.x = q.x;
        res.y = p;
        return res;
    }
}

Node* tree_search_one(unsigned int key, tree* t) {
    Node* ptr = t->root;
    int k = 0, n;
    while (ptr) {
        if (ptr->p.key[0] > key) {
            ptr = ptr->left;
        }
        else if (ptr->p.key[0] < key) {
            ptr = ptr->right;
        }
        else if (ptr->p.key[0] == key) {
            return ptr;
        }
    }
    return NULL;
}

int d_show_tree(tree* t) {
    puts("Your tree");
    if (t->root != NULL) {
        round_for_show(t->root,0);
    }
    return 1;
}

int d_search(tree* t) {
    int key[2],res;
    Node* p = NULL;
    puts("Enter first key:");
    res = get_int(&key[0]);
    if (!res) {
        return 0;
    }
    puts("Enter second key:");
    res = get_int(&key[1]);
    if (!res) {
        return 0;
    }
    p = search(key, t);
    if (p) {
        show(p);
        return 1;
    }
    else {
        puts("Element is not exist");
        return 0;
    }
}

int d_insert(tree* t) {
    int key[2];
    float x,y;
    char* s = NULL;
    int res;
    unsigned int depth;
    Node* p = NULL,*r = NULL;
    puts("Enter first key:");
    res = get_int(&key[0]);
    if (!res) {
        return 0;
    }
    puts("Enter second key:");
    res = get_int(&key[1]);
    if (!res) {
        return 0;
    }
    r = search(key, t);
    if (r) {
        puts("Element with equal keys is exist");
        return 0;
    }
    depth = search_deep(key, t);
    deep_search(t->root, depth, &r,0);
    if (r && r->n == t->N) {
        puts("Level is full");
        return 0;
    }
    puts("Enter first float num:");
    res = get_float(&x);
    if (!res) {
        return 0;
    }
    puts("Enter second float num:");
    res = get_float(&y);
    if (!res) {
        return 0;
    }
    puts("Enter string");
    s = get_str();
    if (!s) {
        return 0;
    }
    p = (Node*)calloc(1, sizeof(Node));
    p->p.info = (Info*)calloc(1, sizeof(Info));
    p->level = (Point*)calloc(t->N, sizeof(Point));
    p->p.info->s = s;
    p->p.info->x = x;
    p->p.info->y = y;
    p->p.key[0] = key[0];
    p->p.key[1] = key[1];
    insert(p, t);
    return 1;
}

int d_delete(tree* t) {
    int key[2];
    int res;
    puts("Enter first key:");
    res = get_int(&key[0]);
    if (!res) {
        return 0;
    }
    puts("Enter second key:");
    res = get_int(&key[1]);
    if (!res) {
        return 0;
    }
    Node* p = search(key, t);
    if (!p) {
        puts("Element is not exist");
        return 0;
    }
    t->root = deleteNode(key, t);
    return 1;
}

int d_show(tree* t) {
    int key[2];
    int res,rc;
    char* msgs[] = { "1.Show tree","2.Enter first and second keys and show corresponding keys","3.Enter first key and show corresponding keys","4.Enter second key and show corresponding keys" };
    int size = sizeof(msgs) / sizeof(char*);
    rc = dialog(msgs, size);
    if (!rc) {
        return 0;
    }
    if (rc == 1) {
        key[0] = INT_MAX;
        key[1] = INT_MAX;
        round_less_this_keys(key, t->root, 0);
    }
    if (rc == 2) {
        puts("Enter first key:");
        res = get_int(&key[0]);
        if (!res) {
            return 0;
        }
        puts("Enter second key:");
        res = get_int(&key[1]);
        if (!res) {
            return 0;
        }
        round_less_this_keys(key, t->root, 0);
    }
    if (rc > 2) {
        printf("Enter key number %d\n", rc - 2);
        int axis = (rc - 3) % 2;
        res = get_int(&key[axis]);
        if (!res) {
            return 0;
        }
        round_less_this_key(key[axis], axis, t->root, 0);
    }
    return 1;
}

int d_search_max(tree* t) {
    puts("The farthest points:");
    region_max(0, 0, t);
    return 1;
}

int delete_tree(tree* t) {
    Node* ptr = t->root;
    while (ptr) {
        t->root = deleteNode(ptr->p.key, t);
        ptr = t->root;
    }
    free(t);
    return 1;
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

Node* f_to_i(FILE* fd) {
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int len = 0;
    Node* K = NULL;
    K = (Node*)calloc(1, sizeof(Node));//“очка останова возникает в этом месте
    K->p.info = (Info*)calloc(1, sizeof(Info));
    fread(&K->p.key[0], sizeof(int), 1, fd);
    fread(&K->p.key[1], sizeof(int), 1, fd);
    fread(&K->p.info->x, sizeof(float), 1, fd);
    fread(&K->p.info->y, sizeof(float), 1, fd);
    fread(&len, sizeof(int), 1, fd);
    K->p.info->s = (char*)calloc(len, sizeof(char));
    fread(K->p.info->s, sizeof(char), len, fd);
    return K;
}

void fix_insert(tree* t, Node* I) {
    Node* r = NULL;
    Node* p = NULL;
    unsigned int depth = 0;
    r = search(I->p.key, t);
    if (r) {
        free(I->p.info->s);
        free(I->p.info);
        free(I->level);
        free(I);
        return;
    }
    depth = search_deep(I->p.key, t);
    deep_search(t->root, depth, &r, 0);
    if (r && r->n == t->N) {
        free(I->p.info->s);
        free(I->p.info);
        free(I->level);
        free(I);
        return;
    }
    insert(I, t);
    return;
}

tree* f_to_t(char* fname,tree* r) {
    FILE* fd = NULL;
    fopen_s(&fd, fname, "rb");
    int msize, i;
    int offset;
    Node* I = NULL;
    if (fd) {
        fseek(fd, 0, SEEK_SET);
        fread(&msize, sizeof(int), 1, fd);
        //fread(&csize, sizeof(int), 1, fd);
        for (i = 0; i < msize; i++) {
            I = f_to_i(fd);
            I->level = (Point*)calloc(r->N, sizeof(Point));
            fix_insert(r, I);
        }
        fclose(fd);
        return r;
    }
    else {
        puts("File do not exist");
        return NULL;
        }
}

void round_for_timing(Node* ptr,int *count,double *T,tree* t) {
   int i = 0;
    if (ptr == NULL) {
        return;
    }
    clock_t time = 0,dt;
    for (i = 0; i < 20; i++) {
        dt = clock();
        search(ptr->p.key, t);
        time += clock() - dt;
        //*T += time / CLOCKS_PER_SEC;
    }
    *T += (double)time / (20.0 * (double)CLOCKS_PER_SEC);
    *count = *count + 1;
    round_for_timing(ptr->left, count, T, t);
    round_for_timing(ptr->right, count, T, t);
}

int d_timing(tree* t) {
    char* fname = NULL;
    tree* result = NULL;
    double T = 0.0;
    int count = 0;
    puts("Enter file name");
    fname = get_str();
    if (!fname) {
        return 0;
    }
    tree* res = new_tree();
    res->N = t->N;
    result = f_to_t(fname, res);
    if (!result) {
        delete_tree(res);
        return 0;
    }
    round_for_timing(res->root, &count, &T, res);
    T = T / count;
    printf("Average time(millsec) : %lf\n", 1000.0 * T);
    delete_tree(res);
    return 1;
}

int null(tree* t) {
    return 0;
}

/*Node* insertRec(Node* root, int point[], unsigned depth){
  if (root == NULL)
        return newNode(point);
    unsigned cd = depth % k;
    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);
    return root;
}*/
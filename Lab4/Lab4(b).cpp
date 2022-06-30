#include <stdlib.h>
#include <stdio.h>
#include "Lab4_header(b).h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int (*fptrs[])(tree*) = { null,d_insert,d_search,d_delete,d_show,d_search_max,d_show_tree,d_timing};
	char* msgs[] = { "0.Quit","1.Insert new element","2.Search element","3.Delete element","4.Search elements,which keys less than this key","5.Search the fartherst elements from (0,0)","6.Show tree","7.Timing"};
	int size = sizeof(msgs) / sizeof(char*);
	int rc;
	int N,res;
	/*Point* l = (Point*)calloc(3, sizeof(Point));
	l[0].key[0] = 0;
	l[0].key[1] = 1;
	free(l);*/
	tree* t = new_tree();
	puts("Enter N:");
	res = get_int(&N);
	t->N = N;
	do {
		while (fptrs[rc = dialog(msgs, size)](t));
	} while (rc);
	delete_tree(t);
	return 0;
}
#include "Lab4_header(a).h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int (*fptrs[])(tree*) = { null,d_insert,d_search,d_search_max,d_show_max,d_delete,d_time,d_show_tree};
	char* msgs[] = { "0.Quit","1.Insert new element","2.Search element","3.Search max element,which key less than this key","4.Show elements, which keys bigger than this key","5.Delete element","6.Timing","7.Show tree" };
	int size = sizeof(msgs) / sizeof(char*);
	int rc;
	tree* t = new_tree();
	do {
		while (fptrs[rc = dialog(msgs, size)](t));
	} while (rc);
		delete_tree(t);
	return 0;
}
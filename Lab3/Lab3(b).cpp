#include "Lab3(b)_header.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char* msgs[] = { "0.Quit","1.Insert new element","2.Show table","3.Search element","4.Delete element","5.Search with parent key" };
	int size = sizeof(msgs) / sizeof(char*);
	int (*fptrs[])(table*) = { null,fd_add,fd_show,fd_search,fd_delete,fd_search_with_par };
	int rc;
	puts("Enter file name:");
	char* fname = get_str();
	if (!fname) {
		return 0;
	}
	table* t = f_to_t(fname);
	if (!t) {
		return 0;
	}
	do {
		while (fptrs[rc = dialog(msgs, size)](t,fname));
	} while (rc != 0);
	puts("End of programm");
	delete_table(t);
	free(fname);
	return 0;
}
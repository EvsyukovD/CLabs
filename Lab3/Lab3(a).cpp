#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lab3_header.h"
int main(){
	char* msgs[] = { "0.Quit","1.Insert new element","2.Show table","3.Search element","4.Delete element","5.Search with parent key" };
	int size = sizeof(msgs) / sizeof(char*);
	int (*fptrs[])(table*) = { null,d_add,d_show,d_search,d_delete,d_search_with_par};
	int rc;
	table* t = init_table();
	if (!t) {
		return 0;
	}
	do {
		while (fptrs[rc = dialog(msgs,size)](t));
	} while (rc != 0);
	puts("End of programm");
	delete_table(t);
	return 0;
}


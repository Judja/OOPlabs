/***********************************************************************
*file: test.c
* These functions are declared in the include file "scanner.h".
*related files: none
*author: Denys Fedorchenko
*created: 19/11/2017
*last modified: 20/11/2017
************************************************************************/

#include "scanner.h"

int main() {
	RECORD_SET *rs;

	if (create_db("Scanners.csv", "Scanners.db") == -1) {
		printf("ERROR");
		return 1;
	}
	print_db("Scanners.db");
	reindex("Scanners.db");
	del_scanner("Scanners.db", 1);

	add_scanner("Scanners.db", "Asus;AS1055;2009;99.99;210;297");
	rs = get_recs_by_index("Scanners.db", "id");
	if (rs = select("Scanners.db", "manufacturer", "HP"))
		print_rec_set(rs);
	del_scanner("Scanners.db", 5);
	print_db("Scanners.db");
	
	if (rs = get_recs_by_index("Scanners.db", "manufacturer"))
		print_rec_set(rs);

	system("pause");

	return 0;
}

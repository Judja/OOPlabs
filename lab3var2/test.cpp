#include "String.h"
#include <stdlib.h>

int main() {
	cString str("TEST");
	cString *str2 = new cString(str);

	str.Empty();

	str2->SetAt(0, 'F');
	str2->SetAt(-2, '2');

	if(!str2->Isempty())
		printf("str2 length: %d\n", str2->Getlength());

	delete str2;
	system("pause");

	return 0;
}
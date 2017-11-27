#include "String.h"
#include <stdlib.h>

int main() {
	cString str("TEST");
	cString *str2 = new cString(str);

	if (str.Compare(*str2) == 0) printf("EQUAL\n");

	str2->SetAt(0, 'F');
	str2->SetAt(-2, '2');
	printf("Str2: ");
	str2->Print();
	printf("\n");
	*str2 += str;
	printf("Str2: ");
	str2->Print();
	printf("\n");
	if (str2->Find("2T") >= 0) printf("2T FOUND\n");

	if (str.Compare(*str2) > 0) printf("T > F\n");

	str.Empty();

	if(!str2->Isempty())
		printf("str2 length: %d\n", str2->Getlength());

	delete str2;
	system("pause");

	return 0;
}
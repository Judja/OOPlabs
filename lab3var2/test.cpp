#include "String.h"
#include <stdlib.h>

int main() {
	cString str("TEST");
	cString *str2 = new cString(str);
	cString str3;

	printf("Str2: ");
	str2->Print();
	printf(" Str: ");
	str.Print();
	printf(" Are They equal?\n");
	if (str.Compare(*str2) == 0) printf("Yes, EQUAL\n");

	str2->SetAt(0, 'F');
	str2->SetAt(-2, '2');
	printf("Str2: ");
	str2->Print();
	printf("\n");

	*str2 += str;
	printf("Str2: ");
	str2->Print();
	printf("\n");

	str3 = str2->Right(3);
	printf("Str3: ");
	str3.Print();
	printf("\n");

	str3 = "NEW LINE";
	printf("Str3: ");
	str3.Print();
	printf("\n");

	str3 = (*str2) + str3;
	printf("Str3: ");
	str3.Print();
	printf("\n");

	printf("2T found at position %d\n", str2->Find("2T"));
	printf("STR2 char at pos 2 is %c, at pos 5 is %c\n", (*str2)[2], (*str2)[6]);

	if (str.Compare(*str2) > 0) printf("T > F\n");

	str2->Empty();

	if(str2->Isempty())
		printf("str2 length: %d\n", str2->Getlength());

	delete str2;
	system("pause");

	return 0;
}
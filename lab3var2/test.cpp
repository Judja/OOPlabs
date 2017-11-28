#include "String.h"
#include <stdlib.h>

int main() {
	cString str("TEST");
	cString *str2 = new cString(str);
	char *strc = NULL;
	*str2 = strc;
	str2->Print();

	cString str3;

	*str2 = "HELLO";
	printf("Str2: ");
	str2->Print();
	printf(" Str: ");
	str.Print();
	printf(" Are They equal?\n");
	if (str.Compare(*str2) != 0) printf("no\n");


	try {
		str2->SetAt(0, 'F');
		printf("\nLooking for 'E', index = %d\n", str2->Find("E"));

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

		str3 = (*str2) + str3;
		printf("Str3: ");
		str3.Print();
		printf("\n");

		printf("STR3 char at pos 2 is %c, at pos 6 is %c\n", str3[2], str3[6]);
	}
	catch (std::runtime_error e)
	{
		printf("Runtime error: %s\n", e.what());
	}
	str2->Empty();

	if(str2->Isempty())
		printf("str2 length: %d\n", str2->Getlength());

	delete str2;

	system("pause");

	return 0;
}
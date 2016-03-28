#include <stdio.h>

int main(int argc, char* argv[])
{
	if(argc <= 2)
		return 0;

	printf("Mounting %s to %s\n", argv[1], argv[2]);

	return 0;
}

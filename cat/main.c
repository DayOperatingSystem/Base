#include <stdio.h>

int main(int argc, char* argv[])
{
	if(argc <= 1)
		return 0;

	FILE* file = fopen(argv[1], "r");
	if(!file)
	{
		perror("Could not open file");
		return 1;
	}

	while(!feof(file))
	{
		putch(fgetc(file));
	}

	fflush(stdout);
	fclose(file);
	return 0;
}

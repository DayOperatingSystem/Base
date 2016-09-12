#include <stdio.h>

void print_file(const char* path)
{
	FILE* file = fopen(path, "r");
	if(!file)
	{
		perror("Could not open file");
		return;
	}

	while(!feof(file))
	{
		putch(fgetc(file));
	}

	fflush(stdout);
	fclose(file);
}

int main(int argc, char* argv[])
{
	if(argc <= 1)
		return 0;

	for(int i = 1; i < argc; i++)
		print_file(argv[i]);
	
	return 0;
}

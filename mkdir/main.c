#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc <= 1)
		return 0;
	
	
	if(mkdir(argv[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
	{
		perror("Could not create directory");
		return 1;
	}
	return 0;
}

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

void print_directory(const char* src)
{
	DIR* dir;
	struct dirent* entry;
	
	if((dir = opendir(src)) == NULL)
	{
		perror("Could not open directory");
		return;
	}
	
	
	do
	{
		errno = 0;
		if((entry = readdir(dir)) != NULL)
		{
			printf("%s\n", entry->d_name);
		}
		else
		{
			closedir(dir);
			return;
		}

        } while(entry != NULL);


	if (errno != 0)
		perror("Error reading directory");
	
	closedir(dir);
}

void print_directory_dayos(const char* src)
{
	struct vfs_file* dir = vfs_opendir(src);
	struct vfs_file entry;
	
	if(dir == NULL)
	{
		perror("Could not open directory");
		return;
	}
	
	entry.child_nid = dir->child_nid;
	
	while(vfs_readdir(dir, &entry, entry.child_nid) == SIGNAL_OK)
	{
		printf("%s\n", entry.path);
	}

	if (errno != 0)
		perror("Error reading directory");

	free(dir);
}


int main(int argc, char* argv[])
{
	if(argc <= 1)
		print_directory(getenv("PWD"));
	else
		print_directory(argv[1]);
		
	return 0;
}

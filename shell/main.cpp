#include <cstdio>

#ifdef __dayos__
#include <dayos.h>
#else
int execute_program(const char* cmd, size_t sz, char* argv[])
{
        return 0;
}

#define debug_printf printf
#endif

#include <vector>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <cstdlib>
#include <cstring>
#include <errno.h>

void handle_command(char* cmd, std::vector<char*>* args)
{
	std::cout << "HANDLING COMMAND!" << std::endl;
	char program[512];
	snprintf(program, sizeof(program), "%s/%s", "/drives/roramdisk", cmd);
	pid_t pid = 0;

	if(args->size() > 0)
	{
		pid = execute_program(program, args->size(), &(*args)[0]);
	}	
	else
	{
		pid = execute_program(program, 0, NULL);
	}

	if(pid)
		waitpid(pid, NULL, 0);
	else
		std::cerr << "Could not execute command '" << cmd << "': " << strerror(errno) << std::endl;

	for(int i = 0; i < args->size(); i++)
		free((*args)[i]);

	free(cmd);
	delete args;
}

using namespace std;

size_t handleLine(char* line, char*** arglist)
{
	size_t num = 0;
	char* iter = strtok(line, " ");
	while(iter)
	{
		*arglist = (char**) realloc(*arglist, ++num * sizeof(char**));
		(*arglist)[num-1] = iter;

		iter = strtok(NULL, " ");
	}
	return num;
}

void execute_command(size_t argc, char** argv)
{
	if(argc == 0)
		return;

	char program[512];
	snprintf(program, sizeof(program), "%s/%s", "/drives/roramdisk", argv[0]);
	pid_t pid = 0;

	//if(argc > 1)
		pid = execute_program(program, argc - 1, &argv[1]);
	//else
		//pid = execute_program(program, 0, NULL);

	if(pid)
		waitpid(pid, NULL, 0);
	else
		std::cerr << "Could not execute command '" << argv[0] << "': " << strerror(errno) << std::endl;
}

int main(int argc, char* argv[])
{
	bool running = true;
	char* line = new char[256];
	char** args = NULL;

	cout << "DayOS Shell v0.2" << endl;
	while(running)
	{
		cout << "DayOS > ";
		fgets(line, 256, stdin);
		line[strlen(line) - 1] = 0;

		if(!strcmp(line, "exit"))
		{
			delete line;
			return 0;
		}
		else if(!strcmp(line, "floppy"))
		{
			FILE* f = fopen("/dayos/dev/fdc0", "r");

			if(!f)
			{
				printf("Could not access floppy: file == NULL\n");
				continue;
			}

			unsigned char buf[512];
			size_t sz = fread(buf, 511, 1, f);

			if(sz == 0)
			{
				printf("Could not access floppy!\n");
				continue;
			}

			for(int i = 0; i < 511; i++)
				printf(" %x ", (unsigned int) buf[i]);

			printf("\n");
			fclose(f);
			continue;
		}

		/*char program[512];
		snprintf(program, sizeof(program), "%s/%s", "/drives/roramdisk", line);
		pid_t pid = 0;

		//cout << program << ":" << line << endl;

		pid = execute_program(program, 0, NULL);

		if(pid)
			waitpid(pid, NULL, 0);
		else
			cout << "Could not execute command '" << line << "': " << strerror(errno) << endl;*/

		size_t num = handleLine(line, &args);

		//cout << "Got num " << num << endl;
		//for(int i = 0; i < num; i++)
			//cout << args[i] << endl;
		execute_command(num, args);
	}
}

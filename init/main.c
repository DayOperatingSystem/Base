#include <stdio.h>
#include <string.h>
#include <dayos.h>
#include <stdlib.h>
#include <syscall.h>

#define LOG(msg) debug_printf("[ INIT ] %s\n", msg)
#define LOG_STRING(msg, str) debug_printf("[ INIT ] %s: %s\n", msg, str)

void execute_config(const char* path)
{
	FILE* config = fopen(path, "r");
	if(!config)
	{
		LOG("Could not open config file!");
		while(1) sleep(1000);
	}
	
	char* content;
	fseek(config, 0, SEEK_END);
	size_t sz = ftell(config);
	fseek(config, 0, SEEK_SET);

	content = (char*) malloc(sz+1);
	fread(content, sz, 1, config);
	
	char* p = strtok(content, "\n");
	while(p != NULL)
	{
		
		if(!strcmp(p, "delay"))
		{
			sleep(250);
		}
		else if(strcmp(p, ""))
		{
			LOG(p);
			if(!execute_program(p, 0, NULL))
				LOG_STRING("Could not execute program", p);
		}
		
		p = strtok(NULL, "\n");
	}
	
	fclose(config);
	free(content);
}

int main()
{
	LOG("Starting INIT system.");
	
	// Wait for VFS to crop up
	pid_t pid = 0;
	while((pid = get_service_pid("vfs")) == 0) sleep(50);
	
	//FILE* config = fopen(");

	// Setup some necessary environment variables
	putenv(strdup("PWD=/drives/roramdisk"));

	sleep(150);
	execute_config("/drives/roramdisk/init.cfg");
	
	
	message_t msg;
	while(1)
	{
		while(receive_message(&msg, MESSAGE_ANY) != MESSAGE_RECEIVED) sleep(10);
		
		switch(msg.signal)
		{
		
		default:
			debug_printf("[ INIT ] Unknown signal 0x%x!", msg.signal);
		}
	}

	for(;;);
}


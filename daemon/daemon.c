#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

// if kill parent process before chile process exit, 
// which get control permission? That is init controlling 
// parent process. 

int main()
{
	pid_t pid;

	if(( pid = fork()) < 0)
		exit(0);
	else if ( pid != 0 )
		exit(0); // exit parent process

	chdir("/");

	// link new seesion id
	setsid();

	while(1)
	{
		sleep(1);
	}
}
#include <stdio.h>
#include <string.h>
#include "predef.h"


int main(int argc, char ** argv)
{

	printf("%s %s\n",errstr(JACK), valuestr(JACK));

	inlinefunc();

	return 0;
}

inline void inlinefunc()
{
	printf("inline function\n");
}
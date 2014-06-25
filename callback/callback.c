#include <stdio.h>
#include <string.h>


typedef void (*callback) ();

static void output_2nd();
static void output_1st(callback fn);

static void output_1st(callback fn)
{
	printf("%s called\n", __FUNCTION__);
	fn();
}

static void output_2nd()
{
	printf("%s called\n", __FUNCTION__);
}

void main(int argc, char * argv[])
{

	printf("callback test start\n");
	output_1st(output_2nd);

}

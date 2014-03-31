#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "jpack.h"

int main(void)
{
	FILE * fd;

	char buffer[256];
	char rdbuffer[256];
	const char * message = "Hello Jack";
	jpack_struct_type jp;
	int length;
	size_t rwlen;

	fd = fopen("test.dat", "w+r");

	jpack * packet = new jpack(JPACK_BIG_ENDIAN);

	jp.cmd = 0xF1F2F3F4;
	jp.idx = 0xE1E2E3E4;
	jp.data = (char *) message;
	jp.length = strlen((const char *) message);

	length = packet->enpack(&jp, buffer, sizeof(buffer));

	rwlen = fwrite(buffer, sizeof(char), length, fd);

	memset(buffer, 0, sizeof(buffer));
	memset(&jp, 0, sizeof(jpack_struct_type));

	//fseek(fd, 0, SEEK_SET);
	rewind(fd);

	rwlen = fread(rdbuffer, sizeof(char), sizeof(rdbuffer), fd);

	jp.data = buffer;
	jp.length = sizeof(buffer);

	length = packet->depack(rdbuffer, sizeof(rdbuffer), &jp);
	if(length < 0)
		printf("Error on depack %d\n", length);

	printf("%s \n", jp.data);

	fclose(fd);

	delete packet;


}

/*
* browser.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, char **argv)
{
	inquiry_info *ii = NULL;
	int dev_id, sock;

	dev_id = hci_get_route(NULL);
	
	sock = hci_open_dev(dev_id);
	
	if (dev_id < 0 || sock < 0) {
		//error
		exit(1);
	}

	return 0;
}

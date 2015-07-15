/*
* browser.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <dirent.h>
#include <errno.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define SYS_HCI_DIR "/sys/class/bluetooth"

static int hci_count()
{
	int count = 0;
	DIR * dirp;
	struct dirent * entry;

	dirp = opendir(SYS_HCI_DIR);

	if(dirp == NULL) {
		perror("Cannot open dir");
		return -1;
	}

	while((entry = readdir(dirp)) != NULL)
	{
		if (entry->d_type == DT_LNK) { /* directory type is not unknown */
//		if (entry->d_type != DT_UNKNOWN) { /* directory type is not unknown */
			printf("%s type is %d\n", entry->d_name, entry->d_type);
			count++;
		}
	}

	closedir(dirp);

	return count;
}

static void hci_info(int devid)
{
	int ret;
	struct hci_dev_info info;

	ret = hci_dev_info (devid, &info);

/*	struct hci_dev_info {
		uint16_t dev_id;
		char     name[8];

		bdaddr_t bdaddr;

		uint32_t flags;
		uint8_t  type;

		uint8_t  features[8];

		uint32_t pkt_type;
		uint32_t link_policy;
		uint32_t link_mode;

		uint16_t acl_mtu;
		uint16_t acl_pkts;
		uint16_t sco_mtu;
		uint16_t sco_pkts;

		struct   hci_dev_stats stat;
	};	
*/
}

static void cmd_scan(int ctl, int hdev, char *opt)
{
	struct hci_dev_req dr;

	dr.dev_id  = hdev;
	dr.dev_opt = SCAN_DISABLED;
	if (!strcmp(opt, "iscan"))
		dr.dev_opt = SCAN_INQUIRY;
	else if (!strcmp(opt, "pscan"))
		dr.dev_opt = SCAN_PAGE;
	else if (!strcmp(opt, "piscan"))
		dr.dev_opt = SCAN_PAGE | SCAN_INQUIRY;

	if (ioctl(ctl, HCISETSCAN, (unsigned long) &dr) < 0) {
		fprintf(stderr, "Can't set scan mode on hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
		exit(1);
	}
}

int main(int argc, char **argv)
{
	inquiry_info *ii = NULL;
	int dev_id, sock;
	int len, i;
	int num_rsp, max_rsp, flags;
	int num_hci;
	int   devs[16];

	char addr[19] = { 0 };
	char name[248] = { 0 };
	bdaddr_t leadd_0 = {{0x00, 0x19, 0x0e, 0x15, 0x57, 0x23}};
	bdaddr_t leadd_1 = {{0xe0, 0x2a, 0x82, 0xc7, 0xa1, 0xd9}};

	char * hci_0 = "00:19:0e:15:57:23";
	char * hci_1 = "e0:2a:82:c7:a1:d9";

	num_hci = hci_count();

//	dev_id = hci_get_route(NULL);
	dev_id = hci_get_route(&leadd_1);

	printf("device id : %d\n", dev_id);

	dev_id = hci_devid(hci_0);	

	printf("device id : %d\n", dev_id);

	dev_id = hci_devid(hci_1);	

	printf("device id : %d\n", dev_id);

	ba2str(&leadd_0, name);

	printf("hci_0 address : %s\n", name);

	printf("Adaptor number : %d\n", num_hci);

	if (num_hci <= 0) {
		perror("No hci device");
		exit(1);
	}

	for (dev_id = 0 ; dev_id < num_hci; dev_id++)
	{
		sock = hci_open_dev(dev_id);

		cmd_scan(sock, dev_id, "pscan");

	    len  = 8;
	    max_rsp = 255;
	    flags = IREQ_CACHE_FLUSH;
	    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
	    
	    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
	    if( num_rsp < 0 ) perror("hci_inquiry");

	    printf ("num_rsp : %d\n", num_rsp);

	    for (i = 0; i < num_rsp; i++) {
	        ba2str(&(ii+i)->bdaddr, addr);
	        memset(name, 0, sizeof(name));
	        /* Display scanned device list */
	        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
	            name, 0) < 0)
	        strcpy(name, "[unknown]");
	        printf("%s  %s\n", addr, name);
	    }

	    free( ii );
	    close( sock );
	    hci_close_dev(dev_id);
	}

	return 0;
}

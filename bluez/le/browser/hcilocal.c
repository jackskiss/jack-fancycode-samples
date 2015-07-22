#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <bluetooth/hci.h>
#include <bludeooth/hci_lib.h>

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

#ifndef HCISETSCAN
#error "No define HCISETSCAN"
#endif

	if (ioctl(ctl, HCISETSCAN, (unsigned long) &dr) < 0) {
		fprintf(stderr, "Can't set scan mode on hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
		exit(1);
	}
}

static void cmd_name(int ctl, int hdev, char *opt)
{
	int dd;

	dd = hci_open_dev(hdev);
	if (dd < 0) {
		fprintf(stderr, "Can't open device hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
		exit(1);
	}

	if (opt) {
		if (hci_write_local_name(dd, opt, 2000) < 0) {
			fprintf(stderr, "Can't change local name on hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
			exit(1);
		}
	} else {
		char name[249];
		int i;

		if (hci_read_local_name(dd, sizeof(name), name, 1000) < 0) {
			fprintf(stderr, "Can't read local name on hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
			exit(1);
		}

		for (i = 0; i < 248 && name[i]; i++) {
			if ((unsigned char) name[i] < 32 || name[i] == 127)
				name[i] = '.';
		}

		name[248] = '\0';

		print_dev_hdr(&di);
		printf("\tName: '%s'\n", name);
	}

	hci_close_dev(dd);
}

/**
 * @brief Set hci device scan mode
 * @details Set hci device scan mode
 * 
 * @param ctl socket handle of hci device
 * @param hdev index of hci device
 * @param opt command string
 */
void set_scan_mode(int ctl, int hdev, char *opt)
{
	cmd_scan(int ctl, int hdev, char *opt);
}

void set_name(int ctrl, int hdev, char *opt)
{
	cmd_name(ctrl, hdev, opt);
}

void get_name(int ctrl, int hdev, char *opt);
{
	cmd_name(ctrl, hdev, opt);
}

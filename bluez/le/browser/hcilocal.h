#ifndef _HCILOCAL_H
#define _HCILOCAL_H

/**
 * @brief Set HCI local device name
 * @details Set HCI local device name
 * 
 * @param ctrl socket control handle
 * @param hdev hci device index
 * @param opt name string
 */
void set_name(int ctrl, int hdev, char *opt);

/**
 * @brief Get HCI local device name
 * @details Get HCI local device name
 * 
 * @param ctrl handle of hci socket
 * @param hdev hci device index
 * @param opt buffer to return hci device name
 */
void get_name(int ctrl, int hdev, char *opt);


#endif

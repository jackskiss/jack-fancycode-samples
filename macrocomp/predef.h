/**
 * @file predef.h
 * @brief define string value
 */

#ifndef __PREDEF_H
#define __PREDEF_H

#include <string.h>


#define prinfd(XX) printf("Error happend %s", ##XX##);

#define JACK	hero

#define errstr(XX) #XX

#define valuestr(XX) errstr(XX)

#endif /* __PREDEF_H */
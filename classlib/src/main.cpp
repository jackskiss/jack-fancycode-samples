/**
 * 
 */


#include <dlfcn.h>
#include "iface.h"

int main (int argc , char ** argv)
{
 	void *handle = dlopen("lib/libif.so", RTLD_NOW);

 	void *pface = dlsym(handle, "iface");

 	iface *lib = static_cast<iface *()>(pface)();

 	lib->printhi();

 	dlclose(handle);
}
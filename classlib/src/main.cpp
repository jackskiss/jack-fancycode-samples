/**
 * 
 */


#include <iostream>
#include <dlfcn.h>
#include "iface.h"

using namespace std;

int main (int argc , char ** argv)
{
 	void *handle = dlopen("../lib/libif.so", RTLD_NOW);
	
	if (handle == NULL) {
		cout << "Error to load" << dlerror() << endl;
	}
 	void *pface = dlsym(handle, "getinstance");

	if (pface == NULL) {
		cout << "Error to load. " << dlerror() << endl;
	}

	void *dface = dlsym(handle, "deleteinstance");
	if (dface == NULL) {
		cout << "Error to load. " << dlerror() << endl;
	}
	
//	typedef iface * (getface)();
	
 	iface *lib = reinterpret_cast<iface *(*)()>(pface)();

 	lib->printhi();

//	reinterpret_cast<void ()>(dface)(lib);	

 	dlclose(handle);
}

/**
 * 
 */

#include <iostream>
#include "iface.h"

using namespace std;

/**
 * @brief Class iflib
 * @details [long description]
 * 
 */

class iflib : public iface {
public:
	void printhi() { cout <<"Say Hi"<< endl;};
	void printbye() { cout <<"Good byte" << endl;};
};

#ifdef __cplusplus
extern "C" {
#endif

iface * getinstance()
{
	return new iflib();
}

void deleteinstance(iface * obj)
{
	if(obj) {
		delete obj;
	}
}

#ifdef __cplusplus
}
#endif

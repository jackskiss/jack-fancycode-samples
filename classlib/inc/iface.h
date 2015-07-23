/**
 * @brief sample interface
 * @details [long description]
 * 
 */

class iface {
public:
	virtual void printhi()=0;
	virtual void printbye()=0;
};

#ifdef __cplusplus
extern "C" {
#endif

extern iface * getinstance();

extern void deleteinstance(iface * obj);

#ifdef __cplusplus
}
#endif

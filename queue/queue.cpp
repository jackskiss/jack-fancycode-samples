#include <iostream>       // std::cin, std::cout
#include <queue>          // std::queue

#define TEST_CLASS_TYPE

#ifdef TEST_CLASS_TYPE
class data_item {
public:
	data_item(int val):mInt(val) {std::cout<<"Construction"<<val<<"\n";};
	virtual ~data_item() { std::cout<<"Destory data_item"<<mInt<<"\n";};
private:
        int mInt;
};

#endif

int main ()
{
#ifdef TEST_CLASS_TYPE
  std::queue<data_item * > myqueue;

  data_item * item = new data_item(3);

  myqueue.push (item);

  item = new data_item(4);

  myqueue.push (item);

  data_item * pitem = myqueue.front();
   
  myqueue.pop ();

  delete pitem;

  pitem = myqueue.front();

  myqueue.pop();

  delete pitem;
 
#else
  std::queue<int> myqueue;
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    myqueue.push (myint);
  } while (myint);

  std::cout << "myqueue contains: ";
  while (!myqueue.empty())
  {
    std::cout << ' ' << myqueue.front();
    myqueue.pop();
  }
  std::cout << '\n';
#endif
	
  return 0;
}

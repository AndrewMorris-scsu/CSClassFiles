//KeyPos.h
#include <fstream>
#ifndef KEYPOS
#define KEYPOS
#include <iostream>
using namespace std;
template<class obj>
class KeyPos{
	public: 
	obj key;
	int pos; 
	void operator=(const KeyPos<obj> &kp )
      { 
         key = kp.key;
         pos = kp.pos;
      }
    bool operator>=(const KeyPos<obj> &kp )
      { 
        return key>=kp.key;
      }
    bool operator>(const KeyPos<obj> &kp )
      { 
        return key>kp.key;
      }
    bool operator<=(const KeyPos<obj> &kp )
      { 
        return key<=kp.key;
      }
    bool operator<(const KeyPos<obj> &kp )
      { 
        return key<kp.key;
      }
    friend ostream &operator<<( ostream &output, const KeyPos<obj> &kp ){ 
         output << "key : " << kp.key<< " pos : " <<kp.pos;
         return output;            
      }

      friend istream &operator>>( istream  &input, KeyPos<obj> &kp )
      { 
         input >> kp.pos >> kp.key;
         return input;            
      }
      private:
};
#endif
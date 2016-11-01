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

	obj getKey() const{
		return key;
	}
	int getPos() const{
		return pos;
	}
	void operator=(const KeyPos<obj> &kp )
      { 
         key = kp.getKey();
         pos = kp.getPos();
      }
    bool operator>=(const KeyPos<obj> &kp ) const
      { 
        return getKey()>=kp.getKey();
      }
    bool operator>(const KeyPos<obj> &kp ) const 
      { 
        return getKey()>kp.getKey();
      }
    bool operator<=(const KeyPos<obj> &kp )const 
      { 
        return getKey()<=kp.getKey();
      }
    bool operator<(const KeyPos<obj> &kp ) const
      { 
        return getKey()<kp.getKey();
      }
    friend ostream &operator<<( ostream &output, const KeyPos<obj> &kp ){ 
         output << kp.getPos()<<" "<< kp.getKey();
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
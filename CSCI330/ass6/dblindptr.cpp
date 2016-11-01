#include <iostream> 
#include <cstring> 

using namespace std;

struct example {
	int x = 0; 
	int y = 0;
};

int main() {
// int to float
	int x = 1; 
	float y = x;
// float to int
	float z = 2; 
	int a = z;
// int to char
	int b = 100;
	char c = b;
// char to int
	char d = 'a';
	int e = d;
// int to string
	int f = 10;
	string g = f;
// string to int
	string h = "S";
	int i = h;
// enumerated to int
	enum days {mon, tue, wed, thur, fri, sat, sun};
	int j = 5;
	mon = j;
// int to enumerated
	int k = thur; 
// struct to another struct of diff type
	struct st1 {
		int x = 0; 
		int y = 1;
	};
	struct st2 {
		int x = 2;
		int y = 4;
	};
	st1 = st2;
// float ptr to int number
	int m = 5;
	float * flptr = &m;
// int ptr to float number
	float n = 5.54;
	int * o = &n;

}
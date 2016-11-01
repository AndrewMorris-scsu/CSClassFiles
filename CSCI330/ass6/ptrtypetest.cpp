#include <iostream> 
#include <cstring> 

using namespace std;

int main() {

// float ptr to int number -> cannot initialize float* with an rvalue of type int *
	int m = 5;
	float * flptr;
	flptr = &m; 
// int ptr to float number -> Cannot initialize a variable of type int * with and rvalue of type float *. 
	float n = 5.54;
	int * o;
	o = &n;
	cout << "flptr =" << *(flptr) << endl;
	cout << "o =" << *(o) << endl;

}
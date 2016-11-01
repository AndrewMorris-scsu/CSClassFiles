#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main () {
	srand(time(NULL));
	fstream IDs;

	IDs.open("id.txt", std::fstream::out);

	for (int i = 0; i < 6000; i++) {
			IDs << "Morris" << " Andrew " << abs(rand()%899999999 + 100000000) << " "
			<< abs(rand()%899999999 + 100000000) << " |" << endl;
	}

	return 0;
}
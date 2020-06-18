#include"Polynomial.h"

using namespace std;

int main(int argc, char**argv)
{
	if (argc != 3)
		cout << "Project cannot run!";
	else {
		docGhiFile(argv[1], argv[2]);
	}
	return 0;
}
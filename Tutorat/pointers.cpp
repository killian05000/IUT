#include <iostream>

using namespace std;


int main()
{
	int a = 20;
	int *adr = &a;
	int **adr2 = &adr;

	cout << "a = " << a << endl;
	cout << "&a = " << &a << endl;
	cout << "adr = " << adr << endl;
	cout << "&adr = " << &adr << endl;
	cout << "*adr = " << *adr << endl;
	cout << "**adr2 = " << **adr2 << endl;
	cout << "*adr2 = " << *adr2 << endl;

}
#include <iostream>
#include <random>

using namespace std;

random_device generator;

int main()
{
 for(int i=0; i<10; i++)
 {
   uniform_int_distribution<int> distribution(1,5);
   int dmg = distribution(generator);
   cout << dmg << endl;
 }
}

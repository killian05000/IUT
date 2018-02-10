#include <iostream>
#include <inttypes.h>
#include "GameCharacter.hpp"

using namespace std;

int main()
{
	GameCharacter Player(30,10, 5,"albert");
	cout << "vie de " << Player.getName() << " : " << Player.getLife() << endl;
	cout << "mana de "<< Player.getName() << " : " << Player.getMana() << endl;
	cout << "nom de " << Player.getName() << " : " << Player.getName() << endl;
}

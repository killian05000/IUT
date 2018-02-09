#include <iostream>
#include "GameCharacter.hpp"

using namespace std;

int main()
{
	GameCharacter Player(10,20,"albert");
	cout << "vie de " << Player.getName() << " : " << Player.getLife() << endl;
	cout << "mana de "<< Player.getName() << " : " << Player.getMana() << endl;
	cout << "nom de " << Player.getName() << " : " << Player.getName() << endl;
}

#include <iostream>
#include <inttypes.h>
#include "GameCharacter.hpp"

using namespace std;

int main()
{
	GameCharacter Player(30, 10, 3,"albert");
	GameCharacter Player2(30, 10, 3, "hugo");
	cout << "vie de " << Player.getName() << " : " << Player.getLife() << endl;
	cout << "mana de "<< Player.getName() << " : " << Player.getMana() << endl;
	cout << "nom de " << Player.getName() << " : " << Player.getName() << endl;

	while(Player2.getLife() > 0)
	{
		char c;
		cout << "Attaquez avec a : ";
		cin >> c;
		if (c == 'a')
			Player.attack(Player2);
		cout << "Vie de " << Player2.getName() << " : " << Player2.getLife() << endl;
	}
}

#include <iostream>
#include "GameCharacter.hpp"

using namespace std;

void winner(GameCharacter& p1, GameCharacter& p2)
{
	if ((p1.getLife() > 0) && (p2.getLife() == 0))
		cout << p1.getName() << " a gagne !!!" << endl;
	else
		cout << p2.getName() << " a gagne !!!" << endl;
}

int main()
{
	string pseudo1, pseudo2;
	cout << "Joueur 1 choisissez votre pseudo : ";
	cin >> pseudo1;
	cout << "Joueur 2 Choisissez un pseudo : ";
	cin >> pseudo2;

	GameCharacter Player1(30, 10, 3, pseudo1);
	GameCharacter Player2(30, 10, 3, pseudo2);

	bool tourP1=true;

	while((Player1.getLife() > 0) && (Player2.getLife() >0))
	{
		if(tourP1)
		{
			char c;
			cout << Player1.getName() << " doit chosir une action (a = attaquer ; s = se soigner) : ";
			cin >> c;
			if (c == 'a')
			{
				Player1.attack(Player2);
			}
			else if (c == 's')
			{
				Player1.heal();
			}
			tourP1=false;
		}
		else
		{
			char c;
			cout << Player2.getName() << " doit chosir une action (a = attaquer ; s = se soigner) : ";
			cin >> c;
			if (c == 'a')
			{
				Player2.attack(Player1);
			}
			else if (c == 's')
			{
				Player2.heal();
			}
			tourP1=true;
		}
		cout << "->" << Player1.getName() << " à " << Player1.getLife() << " pdv" << endl;
		cout << "->" << Player2.getName() << " à " << Player2.getLife() << " pdv" << endl;
	}
	winner(Player1, Player2);
}

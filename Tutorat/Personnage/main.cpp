#include <iostream>
#include "GameCharacter.hpp"

using namespace std;

void columnDisplay(GameCharacter& p1, GameCharacter& p2)
{
	cout << endl;
	cout << "----------------------------" << endl;
	cout << "   -" << p1.getName() << "-    -" << p2.getName() << "-" << endl;
	cout << "   vie :" << p1.getLife() << "      vie : " << p2.getLife() << endl;
	cout << "   mana :" << p1.getMana() << "     mana : " << p2.getMana() << endl;
	cout << "   degats :" << p1.getDegats() << "    degats:" << p2.getDegats() << endl;
	cout << "----------------------------" << endl << endl;
}

void lignDisplay(GameCharacter& p1, GameCharacter& p2)
{
	cout << "->" << p1.getName() << " à " << p1.getLife() << " pdv" << " et " << p1.getMana() << " pm" << endl;
	cout << "->" << p2.getName() << " à " << p2.getLife() << " pdv" <<" et " << p2.getMana() << " pm" << endl;
	cout << endl;
}

void uiChoice(int c, GameCharacter& p1, GameCharacter& p2)
{
	if (c ==1)
		columnDisplay(p1,p2);
	else
		lignDisplay(p1,p2);
}

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
	uint ui;
	cout << "Joueur 1 choisissez votre pseudo : ";
	cin >> pseudo1;
	cout << "Joueur 2 Choisissez un pseudo : ";
	cin >> pseudo2;
	do {cout << "Choix de l'interface 1 ou 2 : "; cin >> ui;} while ((ui != 1) && (ui != 2));
	cout << endl;

	GameCharacter Player1(30, 10, 3, pseudo1);
	GameCharacter Player2(30, 10, 3, pseudo2);

	bool tourP1=true;

	while((Player1.getLife() > 0) && (Player2.getLife() >0))
	{
		if(tourP1)
		{
			char c;
			do
			{
				cout << Player1.getName() << " doit chosir une action (a = attaquer ; s = se soigner) : ";
				cin >> c;
			} while((c != 'a') && (c != 's'));

			if (c == 'a')
				Player1.attack(Player2);
			else if (c == 's')
				Player1.heal();

			tourP1=false;
		}
		else
		{
			char c;
			do
			{
				cout << Player2.getName() << " doit chosir une action (a = attaquer ; s = se soigner) : ";
				cin >> c;
			} while((c!= 'a') && (c!= 's'));

			if (c == 'a')
				Player2.attack(Player1);
			else if (c == 's')
				Player2.heal();

			tourP1=true;

		}
		uiChoice(ui, Player1, Player2);
	}
	winner(Player1, Player2);
}

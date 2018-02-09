#include "GameCharacter.hpp"

GameCharacter::GameCharacter(uint _life, uint _mana, string _name)
							: life(_life), lifeMax(_life), mana(_mana), manaMax(_mana), name(_name)
{}

GameCharacter::GameCharacter()
							: life(2000), lifeMax(2000), mana(400), manaMax(400), name("")
{}

GameCharacter::~GameCharacter()
{}


void GameCharacter::receiveDammages(int _degats)
{
	if (_degats > life)
	{
		_degats = life;
		cout << name << " est mort." << endl;
	}

	life -= _degats;
}

void GameCharacter::heal()
{
	if (mana > 100)
	{
		uniform_int_distribution<int> distribution(100,200);
		int heal = distribution(generator);

		if (heal > lifeMax-life)
			heal = lifeMax-life;

		mana -= 100;
		life += heal;
	}
	else
		cout << "Plus de mana :/" << endl;
}

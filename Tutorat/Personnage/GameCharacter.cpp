#include "GameCharacter.hpp"

GameCharacter::GameCharacter(uint _life, uint _mana, uint _degats, string _name)
							: life(_life), lifeMax(_life), mana(_mana), manaMax(_mana), degats(_degats), name(_name)
{}

GameCharacter::GameCharacter()
							: life(20), lifeMax(20), mana(10), manaMax(10), degats(5), name("")
{}

GameCharacter::~GameCharacter()
{}

void GameCharacter::attack(GameCharacter& target)
{
	uniform_int_distribution<int> distribution(1,2);
	uint dmg = distribution(generator);
	target.receiveDammages(degats+dmg);
}

void GameCharacter::receiveDammages(uint _degats)
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
	if (mana > 2)
	{
		uniform_int_distribution<int> distribution(1,4);
		uint heal = distribution(generator);

		if (heal > lifeMax-life)
			heal = lifeMax-life;

		mana -= 2;
		life += heal;
	}
	else
		cout << "Plus de mana :/" << endl;
}

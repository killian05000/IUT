#include <iostream>
#include <random>

using namespace std;

class GameCharacter
{
	private:

		uint life;
		uint lifeMax;
		uint mana;
		uint manaMax;
		uint degats;
		string name;

	public:

		random_device generator;

		GameCharacter(uint _life, uint _mana, uint degats, string _name);
		GameCharacter();
		~GameCharacter();

		inline uint getLife() const {return life;}
		inline uint getMana() const {return mana;}
		inline uint getDegats() const {return degats;}
		inline string getName() const {return name;}

		void attack(GameCharacter& target);
		void receiveDammages(uint _degats);
		void heal();
};

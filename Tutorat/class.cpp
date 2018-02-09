# include <iostream>

using namespace std;

class Voiture
{
	private :
		int poids;
		int vitesse;

	public : 
		inline int getPoid() {return poids;}
		Voiture(int _poids, int _vitesse);
};

Voiture::Voiture(int _poids, int _vitesse)
		: poids(_poids), vitesse(_vitesse)
{}

int main ()
{
	Voiture voit(2000,30);
	cout << "Poids de la voiture : " << voit.getPoid() << endl;
}
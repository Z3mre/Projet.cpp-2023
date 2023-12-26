#include "Dimension.h"

#include <string.h>


	const Dimension Dimension::VGA(640,480);
	const Dimension Dimension::HD(1280,720);
	const Dimension Dimension::FULL_HD(1920,1080);





// CONSTRUCTEURS

	Dimension::Dimension()
	{
	#ifdef DEBUG

		cout << "Dimension: Constructeur par defaut"<< endl;

	#endif



		setLargeur(400);
		setHauteur(300);
	}


	Dimension::Dimension(int l, int h)
	{
	#ifdef DEBUG

		cout << "Dimension: Constructeur d'initialisation"<< endl;

	#endif

		setLargeur(l);
		setHauteur(h);
	}


	Dimension::Dimension(const Dimension& d2)
	{
	#ifdef DEBUG

		cout << "Dimension: Constructeur de copie "<< endl;

	#endif

		setLargeur(d2.getLargeur());
		setHauteur(d2.getHauteur());
	}

	// DESTRUCTEUR

	Dimension::~Dimension()
	{
	#ifdef DEBUG

		cout << "Destructeur de dimension"<< endl;

	#endif

	}


	// SETTERS


	void Dimension::setLargeur(int l)
	{
		if(l>0) largeur = l;
	}


	void Dimension::setHauteur(int h)
	{
		if(h>0) hauteur = h;
	}


	// GETTERS


	int Dimension::getLargeur() const
	{
		return largeur;
	}

	int Dimension::getHauteur() const
	{
		return hauteur;
	}



	void Dimension::Affiche() const
	{
		cout << "[Dimension : largeur=";
		 cout << getLargeur();
	
		cout << " hauteur=" << getHauteur() << "]" << endl;

	}





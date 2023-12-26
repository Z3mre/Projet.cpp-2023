#include "Dimension.h"


#include <string.h>


	const Dimension Dimension::VGA(640,480);
	const Dimension Dimension::HD(1280,720);
	const Dimension Dimension::FULL_HD(1920,1080);





// CONSTRUCTEURS

	Dimension::Dimension()
	{
	#ifdef DEBUG

			cout << ">>> Dimension: constructeur par defaut <<<" << endl;

	#endif

		setLargeur(400);
		setHauteur(300);
	}


	Dimension::Dimension(int l, int h)
	{
	#ifdef DEBUG

			cout << ">>> Dimension: constructeur d'initialisation <<<" << endl;

	#endif
		setLargeur(l);
		setHauteur(h);

		if(l<1 && h<1)
		{
			throw(XYException('d',"Dimension invalide"));
		}

		if(l<1)
	    {
	      throw(XYException('x',"Largeur invalide"));
	    }

	    if(h<1)
	    {
	      throw(XYException('y',"Hauteur invalide"));
	    }
		
	}


	Dimension::Dimension(const Dimension& d2)
	{
	#ifdef DEBUG

			cout << ">>> Dimension: constructeur de copie <<<" << endl;

	#endif

		setLargeur(d2.getLargeur());
		setHauteur(d2.getHauteur());
	}

	// DESTRUCTEUR

	Dimension::~Dimension()
	{
	#ifdef DEBUG

			cout << ">>> Dimension: Destructeur <<<" << endl;

	#endif

	}

	// OPERATEURS

	 ostream& operator<<(ostream& s,const Dimension& d)
	{
		s << "largeur : "<< d.largeur << endl << " | hauteur : " << d.hauteur << endl;

		return s;


	}


	istream& operator>> (istream& s, Dimension& d)
	{
		int l,h;

		cout << "largeur : ";
		s >> l;
		cout << endl;

		if(l<1)
	    {
	      throw(XYException('x',"Largeur invalide"));
	    }

		cout << "hauteur : ";
		s >> h;
		cout << endl;

		if(h<1)
	    {
	      throw(XYException('y',"Hauteur invalide"));
	    }

		d.largeur = l;
		d.hauteur = h;

		return s;

	}

	int Dimension::operator==(const Dimension& d)
	{
		return compD(d)==0;
	}

	int Dimension::operator!=(const Dimension& d)
	{
		return compD(d)==1;
	}

	int Dimension::compD(const Dimension& d)
	{
		if (largeur != d.largeur) return 1;
		if (hauteur != d.hauteur) return 1;
		
		return 0;


	}

	// SETTERS


	void Dimension::setLargeur(int l)
	{
		largeur = l;

	}


	void Dimension::setHauteur(int h)
	{
		 hauteur = h;

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

// AFFICHAGE

	void Dimension::Affiche() const
	{
		cout << "[Dimension : largeur=";
		 cout << getLargeur();
	
		cout << " hauteur=" << getHauteur() << "]" << endl;

	}





#include "ImageNG.h"
#include "Dimension.h"

#include <string.h>


//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------

	ImageNG::ImageNG(void)
	{
		#ifdef DEBUG

			cout << ">>> ImageNG : constructeur par defaut <<<" << endl;

		#endif

			setId (0);
			nom = NULL;
			setNom ("???");

			


	}

	ImageNG::ImageNG(int d, const char* s)
	{
		#ifdef DEBUG

			cout << ">>> ImageNG : constructeur d'initialisation <<<" << endl;

		#endif

		setId(d);
		nom = NULL;

		setNom(s);
		

	}

	ImageNG::ImageNG(int d,const char* s, Dimension dim)
	{
		#ifdef DEBUG

			cout << ">>> ImageNG : constructeur d'initialisation <<<" << endl;

		#endif
			
		setId(d);
		nom = NULL;

		setNom(s);
		

		setDimension(dim);

	}


	ImageNG::ImageNG(const ImageNG& p)
	{

		#ifdef DEBUG

			cout << ">>> ImageNG : constructeur de copie <<<" << endl;

		#endif

		setId(p.getId());
		nom = NULL;
		setNom(p.getNom());

		setDimension(p.dimension);
	}




	


//----------------------------------
//-------DESTRUCTEURS
//----------------------------------

	ImageNG::~ImageNG()
	{

		#ifdef DEBUG

			cout << ">>> ImageNG : destructeur  <<<" << endl;

		#endif

			if(nom) //si nom different de null
				delete nom;

			
			


	}
//----------------------------------
//-------SETTERS
//----------------------------------

	void ImageNG::setId (int i)
	{

		id = i;
	}

	void ImageNG::setNom (const char *n)
	{
		if (nom) delete nom;
		if (n == NULL)
		{
			nom = NULL;
			return;
		}

		nom = new char[strlen(n)+1];
		strcpy(nom,n);

	}

	
	void ImageNG::setDimension(const Dimension& dim)
	{
		dimension.setLargeur(dim.getLargeur());
		dimension.setHauteur(dim.getHauteur());
	}


	

	//----------------------------------
//-------GETTERS
//----------------------------------


	int ImageNG::getId() const
	{
		return id;


	}
	const char* ImageNG::getNom() const
	{
		return nom;

	}

	

	Dimension ImageNG::getDimension() const
	{
		return dimension;
	}


//----------------------------------
//-------METHODES D INSTANCES
//----------------------------------

	void ImageNG::Affiche() const
	{
		cout << "[ImageNG : nom=";
		if(nom) cout << getNom();
		else cout << "???";
		cout << " id=" << getId() << "]" << endl;

		cout << "[Dimension : largeur=";
		 cout << dimension.getLargeur();
	
		cout << " hauteur=" << dimension.getHauteur() << "]" << endl;

	}

	
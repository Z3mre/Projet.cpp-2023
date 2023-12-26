#include "ImageNG.h"

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

	ImageNG::ImageNG(int d, char* s)
	{
		setId(d);
		nom = NULL;

		if(s!=NULL) setNom(s);
		else
			setNom("???");

	}


	ImageNG::ImageNG(const ImageNG& p)
	{
		setId(p.getId());
		nom = NULL;
		setNom(p.getNom());
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
		}

		nom = new char[strlen(n)+1];
		strcpy(nom,n);

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


//----------------------------------
//-------METHODES D INSTANCES
//----------------------------------

	void ImageNG::Affiche() const
	{
		cout << "[ImageNG : nom=";
		if(nom) cout << getNom();
		else cout << "???";
		cout << " id=" << getId() << "]" << endl;

	}
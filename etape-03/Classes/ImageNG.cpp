#include "ImageNG.h"
#include "MyQT.h"

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

			matrice = new int*[dimension.getLargeur()];
		for (int x=0;x<dimension.getLargeur();x++)
		{
			matrice[x] = new int[dimension.getHauteur()];

		} 

		/*cout<< dimension.getLargeur() << endl;
		cout << dimension.getHauteur() << endl;*/


	}

	ImageNG::ImageNG(int d, const char* s)
	{
	#ifdef DEBUG

			cout << ">>> ImageNG : constructeur d'initialisation 1<<<" << endl;

	#endif
		setId(d);
		nom = NULL;

		setNom(s);
		

	}

	ImageNG::ImageNG(int d,const char* s, Dimension dim)
	{

	#ifdef DEBUG

			cout << ">>> ImageNG : constructeur d'initialisation 2 <<<" << endl;

	#endif

		setId(d);
		nom = NULL;

		setNom(s);

		matrice = new int*[dimension.getLargeur()];
		for (int x=0;x<dimension.getLargeur();x++)
		{
			matrice[x] = new int[dimension.getHauteur()];

		} 
		
		
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

		

		dimension.setLargeur(p.dimension.getLargeur());
		dimension.setHauteur(p.dimension.getHauteur());

		cout<< dimension.getLargeur() << endl;
		cout << dimension.getHauteur() << endl;


		matrice = new int*[dimension.getLargeur()];
		for (int x=0;x<dimension.getLargeur();x++)
		{
			matrice[x] = new int[dimension.getHauteur()];

		} 



		for (int i = 0; i < dimension.getLargeur(); ++i)
	    {
	        for (int j = 0; j < dimension.getHauteur(); ++j)
	        {
	            
	            matrice[i][j] = p.matrice[i][j];
	        }
	    }


		
		
		
		

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

			for (int x=0 ; x<dimension.getLargeur() ; x++) delete[] matrice[x];


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

	void ImageNG::setPixel(int x, int y, int val)
	{
		matrice[x][y] = val;


	}


	void ImageNG::setDimension(const Dimension& d)
	{

			/*dimension.setLargeur(d.getLargeur());
			dimension.setHauteur(d.getHauteur());


			matrice = new int*[dimension.getLargeur()];
			for (int x=0;x<dimension.getLargeur();x++)
			{
				matrice[x] = new int[dimension.getHauteur()];

			} */




	    int newLargeur = d.getLargeur();
	    int newHauteur = d.getHauteur();

	    int** newMatrice = new int*[newLargeur];
	    for (int i = 0; i < newLargeur; ++i) 
	    {
	        newMatrice[i] = new int[newHauteur];
	    }

	    for(int i=0;i< newLargeur;i++)
			{
				
				for(int j=0;j< newHauteur;j++)
				{
					newMatrice[i][j] = 0;
				}
			}


	    for (int i = 0; i < min(dimension.getLargeur(), newLargeur); ++i)
	    {
	        for (int j = 0; j < min(dimension.getHauteur(), newHauteur); ++j)
	        {
	            
	            newMatrice[i][j] = matrice[i][j];
	        }
	    }
	    for (int i = 0; i < dimension.getLargeur(); ++i)
	    {
	        delete[] matrice[i];
	    }
	    
	    delete[] matrice; 
	    /*le fait de supp les lignes de la matrice et puis le tableau principale permet une liberation complete de la memoire
	    et permet d'éviter les fuites de memoires*/

	    dimension = d;
	    matrice = newMatrice;

	}

	

	void ImageNG::setBackground(int val)
	{
		
		
		
		for(int i=0;i<dimension.getLargeur();i++)
		{
			
			for(int j=0;j<dimension.getHauteur();j++)
			{
				setPixel(i,j,val);
			}
		}
		cout << "sortie de boucle" << endl;
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

	int ImageNG::getPixel(int x, int y) const
	{
		return matrice[x][y];


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


	void ImageNG::Dessine() const
	{
		
		cout << "ca va" << endl;
		

		 MyQT::ViewImage(*this);
	}

	void ImageNG::importFromFile(const char* fichier)
	{
		
		 MyQT::ImportFromFile(*this, fichier);
		 cout << "nice" << endl;
	}

	void ImageNG::exportToFile(const char* fichier, const char* format)
	{
		

		 MyQT::ExportToFile(*this,fichier, format);
		 cout << "c'est nice" << endl;
	}
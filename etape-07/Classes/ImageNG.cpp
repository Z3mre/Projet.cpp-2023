#include "ImageNG.h"
#include "MyQT.h"


#include <string.h>


//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------

ImageNG::ImageNG() : Image()
{
	#ifdef DEBUG

		cout << ">>> ImageNG : constructeur par defaut <<<" << endl;

	#endif

		

		matrice = new int*[dimension.getLargeur()];
	for (int x=0;x<dimension.getLargeur();x++)
	{
		matrice[x] = new int[dimension.getHauteur()];

	} 


	for (int i = 0; i < dimension.getLargeur(); ++i)
    {
        for (int j = 0; j < dimension.getHauteur(); ++j)
        {
            
            matrice[i][j] = 0;
        }
    }
	


}

ImageNG::ImageNG(int d, const char *s) : Image(d,s)
{
#ifdef DEBUG
    cout << ">>> Image : constructeur d'initialisation 1<<<" << std::endl;
#endif
    
}


ImageNG::ImageNG(int d,const char* s, Dimension dim) : Image(d, s, dim)
{

#ifdef DEBUG

		cout << ">>> ImageNG : constructeur d'initialisation 2 <<<" << endl;

#endif


	matrice = new int*[dimension.getLargeur()];
	for (int x=0;x<dimension.getLargeur();x++)
	{
		matrice[x] = new int[dimension.getHauteur()];

	} 
	
	
	setDimension(dim);

	
}


ImageNG::ImageNG(const ImageNG& p) : Image(p)
{
#ifdef DEBUG

		cout << ">>> ImageNG : constructeur de copie <<<" << endl;

#endif
	

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

ImageNG::ImageNG(const char* f) : Image(f)
{

	#ifdef DEBUG

		cout << ">>> ImageNG : constructeur  <<<" << endl;

	#endif

	matrice = new int*[dimension.getLargeur()];
	for (int x=0;x<dimension.getLargeur();x++)
	{
		matrice[x] = new int[dimension.getHauteur()];

	} 

	MyQT::ImportFromFile(*this,f);

	

	

	
}







//----------------------------------
//-------DESTRUCTEURS
//----------------------------------

ImageNG::~ImageNG()
{

	#ifdef DEBUG

		cout << ">>> ImageNG : destructeur  <<<" << endl;

	#endif


		for (int x=0 ; x<dimension.getLargeur() ; x++) delete[] matrice[x];


}


//----------------------------------
//-------OPERATEURS
//----------------------------------

ImageNG& ImageNG::operator=(const ImageNG& m)
{
	// Éviter l'auto-affectation
    if (this != &m) {
        // Supprimer la mémoire allouée pour la matrice existante
        for (int i = 0; i < dimension.getLargeur(); i++) 
        {
            delete[] matrice[i];
        }
        delete[] matrice;

        // Copier les valeurs de l'autre objet
        setId(m.getId());
        setNom(m.getNom());
        
        // Allouer de la mémoire pour la nouvelle matrice
        
        matrice = new int*[m.dimension.getLargeur()];
        for (int i = 0; i < m.dimension.getLargeur(); i++) 
        {
            matrice[i] = new int[m.dimension.getHauteur()];
        }

         // Copier les valeurs de la matrice de l'autre objet
        for (int i = 0; i < m.dimension.getLargeur(); i++) 
        {
            for (int j = 0; j < m.dimension.getHauteur(); j++) 
            {
                matrice[i][j] = 0;
            }
        }


        for (int i = 0; i < m.dimension.getLargeur(); i++)
    	{
	        for (int j = 0; j < m.dimension.getHauteur(); j++)
	        {
	            
	            matrice[i][j] = m.matrice[i][j];
	        }
    	}
    	dimension = m.dimension;

    }

    return *this;
}

 ostream& operator<<(ostream& s,const ImageNG& m)
{

	s << "[id : "<< m.id << " | nom : " << m.nom << " | largeur : " << m.dimension.getLargeur() << " | hauteur : " << m.dimension.getHauteur() 
	<< " | luminance : " << m.getLuminance() << " | contraste : " << m.getContraste() << "]" << endl;



		return s;
}

 ImageNG ImageNG::operator+(int n)
 {

 	ImageNG m(*this);

 	for (int i = 0; i < m.dimension.getLargeur(); i++) 
        {
            for (int j = 0; j < m.dimension.getHauteur(); j++) 
            {
                m.matrice[i][j] += n;

                if(m.matrice[i][j]>255)
                {
                	m.matrice[i][j] = 255;

                }else if(m.matrice[i][j]<0)
                {
                	m.matrice[i][j] = 0;
                }
            }
        }

        return m;

 }


 ImageNG operator+(int n,ImageNG i1)
 {
 	return i1 + n;

 }

 ImageNG ImageNG::operator-(int n)
 {
 	ImageNG m(*this);

 	for (int i = 0; i < m.dimension.getLargeur(); i++) 
        {
            for (int j = 0; j < m.dimension.getHauteur(); j++) 
            {
                m.matrice[i][j] -= n;

        
           		if(m.matrice[i][j]<0)
                {
                	m.matrice[i][j] = 0;
                }
            }
        }

        return m;

 }

 ImageNG ImageNG::operator++()
 {
 	(*this) = (*this) + 20;

 	return *this; 
 }

 ImageNG ImageNG::operator++(int)
 {
 	 ImageNG tmp(*this);
	 (*this) = (*this) + 20;
	 return tmp;
 }

 ImageNG ImageNG::operator--()
 {
 	(*this) = (*this) - 20;

 	return *this; 
 }

 ImageNG ImageNG::operator--(int)
 {
 	ImageNG tmp(*this);
	 (*this) = (*this) - 20;
	 return tmp;
 }

 ImageNG operator-(ImageNG i1, ImageNG i2)
 {
 	ImageNG diff;

 	if((i1.dimension.getLargeur()!=i2.dimension.getLargeur()) && (i1.dimension.getHauteur()!=i2.dimension.getHauteur()))
	{
		throw(XYException('d',"les deux dimension sont differentes donc incomparables"));
	}
	if(i1.dimension.getLargeur()!=i2.dimension.getLargeur())
	{
		throw(XYException('x',"les deux largeurs sont differentes donc dimensions incomparables"));
	}
	if(i1.dimension.getHauteur()!=i2.dimension.getHauteur())
	{
		throw(XYException('y',"les deux hauteurs sont differentes donc dimensions incomparables"));
	}

 	diff.dimension.setLargeur(i1.dimension.getLargeur());
 	diff.dimension.setHauteur(i1.dimension.getHauteur());



 	for (int i = 0; i < i1.dimension.getLargeur(); i++) 
        {
            for (int j = 0; j < i1.dimension.getHauteur(); j++) 
            {
                diff.matrice[i][j] = i1.matrice[i][j] - i2.matrice[i][j];
            }
        }

        return diff;

 }


int ImageNG::operator==(const ImageNG& im)
{
	
	return compI(im)==0;

}

int ImageNG::operator<(const ImageNG& im)
{
	
	return compI(im)==-1;

}

int ImageNG::operator>(const ImageNG& im)
{
	

	return compI(im)==1;
}


int ImageNG::compI(const ImageNG& im)
{
	if((dimension.getLargeur()!=im.dimension.getLargeur()) && (dimension.getHauteur()!=im.dimension.getHauteur()))
	{
		throw(XYException('d',"les deux dimension sont differentes donc incomparables"));
	}
	if(dimension.getLargeur()!=im.dimension.getLargeur())
	{
		throw(XYException('x',"les deux largeurs sont differentes donc dimensions incomparables"));
	}
	if(dimension.getHauteur()!=im.dimension.getHauteur())
	{
		throw(XYException('y',"les deux hauteurs sont differentes donc dimensions incomparables"));
	}

	for (int i = 0; i < im.dimension.getLargeur(); i++) 
        {
            for (int j = 0; j < im.dimension.getHauteur(); j++) 
            {
                if(matrice[i][j] > im.matrice[i][j]) return 1;
                if(matrice[i][j] < im.matrice[i][j]) return -1;
            }
        }

        return 0;

}


//----------------------------------
//-------SETTERS
//----------------------------------


void ImageNG::setPixel(int x, int y, int val) 
{
	if(val<0 || val>255) throw(RGBException(val,"Valeur de gris non valide"));
	verifcoord(x,y);

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



    for (int i = 0; i < newLargeur; ++i)
    {
        for (int j = 0; j < newHauteur; ++j)
        {
            
            newMatrice[i][j] = matrice[i][j];
        }
    }


    for (int i = 0; i < newLargeur; ++i)
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




int ImageNG::getPixel(int x, int y) const
{
	verifcoord(x,y);
	return matrice[x][y];


}

Dimension ImageNG::getDimension() const
{
	return dimension;
}

int ImageNG::getLuminance() const
{
	int totalpixels = 0;

    // Parcours de tous les pixels pour obtenir la somme des niveaux de gris
    for (int i = 0; i < dimension.getLargeur(); i++) {
        for (int j = 0; j < dimension.getHauteur(); j++) {
            totalpixels += matrice[i][j];
        }
    }

    // Calcul de la luminance (moyenne des niveaux de gris)
    int luminance = totalpixels / (dimension.getLargeur() * dimension.getHauteur());
    
	return luminance;
}

int ImageNG::getMinimum() const
{
	int min;

	for(int i=0;i<dimension.getLargeur();i++)
	{
		
		for(int j=0;j<dimension.getHauteur();j++)
		{
			if (matrice[i][j] < min) 
			{
                min = matrice[i][j];
            }
		}
	}

	return min;
}

int ImageNG::getMaximum() const
{
	int max;

	for(int i=0;i<dimension.getLargeur();i++)
	{
		
		for(int j=0;j<dimension.getHauteur();j++)
		{
			if (matrice[i][j] > max) 
			{
                max = matrice[i][j];
            }
		}
	}

	return max;
}

float ImageNG::getContraste() const
{
	float contraste;

	contraste = static_cast<float>(getMaximum() - getMinimum()) / (getMaximum() + getMinimum());

	return contraste;
}



//----------------------------------
//-------METHODES D INSTANCES
//----------------------------------

void ImageNG::Affiche() const
{
    cout << "[Image : nom=";
    if (nom)
        cout << getNom();
    else
        cout << "???";
    cout << " id=" << getId() << "]" << endl;

    cout << "[Dimension : largeur=" << dimension.getLargeur()
              << " hauteur=" << dimension.getHauteur() << "]" << endl;
}


void ImageNG::Dessine() const
{
    MyQT::ViewImage(*this);
}

void ImageNG::exportToFile(const char *fichier, const char *format)
{
    MyQT::ExportToFile(*this, fichier, format);
}

void ImageNG::importFromFile(const char* fichier)
{
	
	 MyQT::ImportFromFile(*this, fichier);
	 
}

void ImageNG::verifcoord(int x, int y) const
{
	if((x>dimension.getLargeur()) && (y>dimension.getHauteur())) throw(XYException('d',"Dimension en dehors de la matrice"));
	if(x>dimension.getLargeur()) throw(XYException('x',"Largeur en dehors de la matrice"));
	if(y>dimension.getHauteur()) throw(XYException('y',"Hauteur en dehors de la matrice"));
}
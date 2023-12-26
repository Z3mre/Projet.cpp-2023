#include "ImageB.h"
#include "MyQT.h"



#include <string.h>


 Couleur ImageB::couleurTrue(255, 255, 255);  
 Couleur ImageB::couleurFalse(0, 0, 0);     

//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------

ImageB::ImageB() : Image()
{
#ifdef DEBUG
    cout << ">>> ImageB : constructeur par defaut <<<" << std::endl;  
#endif

    

    matrice = new bool*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new bool[dimension.getHauteur()];
    }
}

ImageB::ImageB(int d, const char* s)  : Image(d,s)
{
#ifdef DEBUG
    cout << ">>> ImageB : constructeur d'initialisation 1<<<" << std::endl;  
#endif
    
}

ImageB::ImageB(int d, const char* s, Dimension dim) : Image(d,s, dim)
{
#ifdef DEBUG
    cout << ">>> ImageB : constructeur d'initialisation 2 <<<" << std::endl;  
#endif

   

    matrice = new bool*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new bool[dimension.getHauteur()];
    }

    setDimension(dim);
}

ImageB::ImageB(const ImageB& p) : Image(p)
{
#ifdef DEBUG
    cout << ">>> ImageB : constructeur de copie <<<" << std::endl;  
#endif

    

    

    matrice = new bool*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new bool[dimension.getHauteur()];
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

ImageB::~ImageB()  
{
#ifdef DEBUG
    cout << ">>> ImageB : destructeur  <<<" << std::endl;  
#endif

    for (int x = 0; x < dimension.getLargeur(); x++)
        delete[] matrice[x];

    delete[] matrice;
}

//----------------------------------
//-------OPERATEURS
//----------------------------------

ImageB& ImageB::operator=(const ImageB& m)  
{
    // Éviter l'auto-affectation
    if (this != &m)
    {
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
        matrice = new bool*[m.dimension.getLargeur()];
        for (int i = 0; i < m.dimension.getLargeur(); i++)
        {
            matrice[i] = new bool[m.dimension.getHauteur()];
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

ostream& operator<<(ostream& s, const ImageB& m)  
{
    s << "[id : " << m.id << " | nom : " << m.nom << " | largeur : " << m.dimension.getLargeur() << " | hauteur : " << m.dimension.getHauteur()
      << "]" << endl;

    return s;
}

//----------------------------------
//-------SETTERS
//----------------------------------

void ImageB::setPixel(int x, int y, bool c)  
{
	
    matrice[x][y] = c;
    
}

void ImageB::setDimension(const Dimension& d)  
{

    int newLargeur = d.getLargeur();
    int newHauteur = d.getHauteur();

    for (int i = 0; i < dimension.getLargeur(); ++i)
    {
        delete[] matrice[i];
    }

    delete[] matrice;

    bool** newMatrice = new bool*[newLargeur];
    for (int i = 0; i < newLargeur; ++i)
    {
        newMatrice[i] = new bool[newHauteur];
    }

    for(int i=0;i< newLargeur;i++)
        {
            
            for(int j=0;j< newHauteur;j++)
            {
                newMatrice[i][j] = 0;
            }
        }


    dimension = d;
    matrice = newMatrice;
}

void ImageB::setBackground(bool c)  
{
	 

    for (int i = 0; i < dimension.getLargeur(); i++)
    {
        for (int j = 0; j < dimension.getHauteur(); j++)
        {
            setPixel(i, j, c);
        }
    }
    
    cout << "sortie de boucle" << endl;
}

//----------------------------------
//-------GETTERS
//----------------------------------

bool ImageB::getPixel(int x, int y) const  
{
    return matrice[x][y];
}

Dimension ImageB::getDimension() const  
{
    return dimension;
}

//----------------------------------
//-------METHODES D INSTANCES
//----------------------------------

void ImageB::Affiche() const 
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

void ImageB::Dessine() const  
{
    MyQT::ViewImage(*this);
}

void ImageB::exportToFile(const char* fichier, const char* format)  
{
    MyQT::ExportToFile(*this, fichier, format);
}

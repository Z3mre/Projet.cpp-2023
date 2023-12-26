#include "ImageRGB.h"
#include "MyQT.h"


#include <string.h>


//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------

ImageRGB::ImageRGB() : Image()
{
    #ifdef DEBUG
        cout << ">>> ImageRGB : constructeur par defaut <<<" << std::endl;
    #endif


    matrice = new Couleur*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new Couleur[dimension.getHauteur()];
    }
}

ImageRGB::ImageRGB(int d, const char *s) : Image(d,s)
{
    #ifdef DEBUG
    cout << ">>> ImageRGB : constructeur d'initialisation 1<<<" << std::endl;
    #endif
    
}

ImageRGB::ImageRGB(int d, const char* s, Dimension dim) : Image(d, s, dim)
{
    #ifdef DEBUG
    cout << ">>> ImageRGB : constructeur d'initialisation 2 <<<" << std::endl;
    #endif


    matrice = new Couleur*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new Couleur[dimension.getHauteur()];
    }

    setDimension(dim);
}

ImageRGB::ImageRGB(const ImageRGB& p) : Image(p)
{
    #ifdef DEBUG
    cout << ">>> ImageRGB : constructeur de copie <<<" << std::endl;
    #endif

    
    matrice = new Couleur*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new Couleur[dimension.getHauteur()];
    }

    for (int i = 0; i < dimension.getLargeur(); ++i)
    {
        for (int j = 0; j < dimension.getHauteur(); ++j)
        {
            matrice[i][j] = p.matrice[i][j];
        }
    }
}

ImageRGB::ImageRGB(const char* f) : Image(f)
{
    #ifdef DEBUG
    cout << ">>> ImageRGB : constructeur  <<<" << std::endl;
    #endif

    

    matrice = new Couleur*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new Couleur[dimension.getHauteur()];
    }

    MyQT::ImportFromFile(*this, f);
}

//----------------------------------
//-------DESTRUCTEURS
//----------------------------------

ImageRGB::~ImageRGB()
{
    #ifdef DEBUG
    cout << ">>> ImageRGB : destructeur  <<<" << std::endl;
    #endif

    for (int x = 0; x < dimension.getLargeur(); x++)
        delete[] matrice[x];

    delete[] matrice;
}

//----------------------------------
//-------OPERATEURS
//----------------------------------

ImageRGB& ImageRGB::operator=(const ImageRGB& m)
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
        id = m.id;
        strcpy(nom, m.nom);

        // Allouer de la mémoire pour la nouvelle matrice
        matrice = new Couleur*[m.dimension.getLargeur()];
        for (int i = 0; i < m.dimension.getLargeur(); i++)
        {
            matrice[i] = new Couleur[m.dimension.getHauteur()];
        }

        for (int i = 0; i < min(dimension.getLargeur(), m.dimension.getLargeur()); i++)
        {
            for (int j = 0; j < min(dimension.getHauteur(), m.dimension.getHauteur()); j++)
            {
                matrice[i][j] = m.matrice[i][j];
            }
        }
        dimension = m.dimension;
    }

    return *this;
}

ostream& operator<<(ostream& s, const ImageRGB& m)
{
    s << "[id : " << m.id << " | nom : " << m.nom << " | largeur : " << m.dimension.getLargeur() << " | hauteur : " << m.dimension.getHauteur()
     <<  "]" << endl;

    return s;
}

//----------------------------------
//-------SETTERS
//----------------------------------

void ImageRGB::setPixel(int x, int y, const Couleur& c)
{
    matrice[x][y] = c;
}

void ImageRGB::setDimension(const Dimension& d)
{

    dimension = d;
    /*int newLargeur = d.getLargeur();
    int newHauteur = d.getHauteur();

    Couleur** newMatrice = new Couleur*[newLargeur];
    for (int i = 0; i < newLargeur; ++i)
    {
        newMatrice[i] = new Couleur[newHauteur];
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

    dimension = d;
    matrice = newMatrice;*/

}

void ImageRGB::setBackground(const Couleur& c)
{

    for(int i=0;i<dimension.getLargeur();i++)
    {
        
        for(int j=0;j<dimension.getHauteur();j++)
        {
            setPixel(i,j,c);
        }
    }
    cout << "sortie de boucle" << endl;
}

//----------------------------------
//-------GETTERS
//----------------------------------

Couleur ImageRGB::getPixel(int x, int y) const
{
    return matrice[x][y];
}

Dimension ImageRGB::getDimension() const
{
    return dimension;
}

//----------------------------------
//-------METHODES D INSTANCES
//----------------------------------

void ImageRGB::Affiche() const
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


void ImageRGB::Dessine() const
{
    MyQT::ViewImage(*this);
}

void ImageRGB::exportToFile(const char* fichier, const char* format)
{
    MyQT::ExportToFile(*this, fichier, format);
}

void ImageRGB::importFromFile(const char* fichier)
{
    MyQT::ImportFromFile(*this, fichier);
}

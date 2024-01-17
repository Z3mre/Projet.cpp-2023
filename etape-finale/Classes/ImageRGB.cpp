#include "ImageRGB.h"
#include "MyQT.h"
#include "Traitements.h"

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
//-------GESTION FICHIER
//----------------------------------

void ImageRGB::Save(ofstream & fichier) const
{
    if (!fichier)
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        exit(1);
    }

    // Sauvegarde de l'ID
    fichier.write((char *) &id, sizeof(int));

    // Sauvegarde de la taille du nom
    int taille = strlen(nom);
    fichier.write((char *) &taille, sizeof(int));

    // Sauvegarde du nom
    fichier.write(nom, taille * sizeof(char));

    // Sauvegarde de la dimension
    dimension.Save(fichier);

    // Sauvegarde de la matrice
    for (int i = 0; i < dimension.getLargeur(); ++i)
    {
        fichier.write((char *) matrice[i], dimension.getHauteur() * sizeof(Couleur));
    }
}

void ImageRGB::Load(ifstream & fichier)
{
    if (!fichier.rdbuf()->is_open())
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        exit(1);
    }

    // Chargement de l'ID
    fichier.read((char *) &id, sizeof(int));

    // Chargement de la taille du nom
    int taille;
    fichier.read((char *) &taille, sizeof(int));

    // Allocation de l'espace pour le nom
    nom = new char[taille + 1];  // +1 pour le caractère nul
    // Chargement du nom
    fichier.read(nom, taille * sizeof(char));
    // Ajout du caractère nul à la fin du nom
    nom[taille] = '\0';

    // Chargement de la dimension
    dimension.Load(fichier);

    // Allocation de l'espace pour la matrice
    matrice = new Couleur*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new Couleur[dimension.getHauteur()];
    }

    // Chargement de la matrice
    for (int i = 0; i < dimension.getLargeur(); ++i)
    {
        fichier.read((char *) matrice[i], dimension.getHauteur() * sizeof(Couleur));
    }
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
    verifcoord(x,y);
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
    verifcoord(x,y);
    return matrice[x][y];
}

Dimension ImageRGB::getDimension() const
{
    return dimension;
}

string ImageRGB::getType() const
{
    return "RGB";
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

void ImageRGB::verifcoord(int x, int y) const
{
    if((x>dimension.getLargeur()) && (y>dimension.getHauteur())) throw(XYException('d',"Dimension en dehors de la matrice"));
    if(x>dimension.getLargeur()) throw(XYException('x',"Largeur en dehors de la matrice"));
    if(y>dimension.getHauteur()) throw(XYException('y',"Hauteur en dehors de la matrice"));
}

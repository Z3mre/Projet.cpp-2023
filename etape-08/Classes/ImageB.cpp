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
//-------GESTION FICHIER
//----------------------------------

void ImageB::Save(ofstream & fichier) const
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
        fichier.write((char *) matrice[i], dimension.getHauteur() * sizeof(bool));
    }
}

void ImageB::Load(ifstream & fichier)
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
    matrice = new bool*[dimension.getLargeur()];
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        matrice[x] = new bool[dimension.getHauteur()];
    }

    // Chargement de la matrice
    for (int i = 0; i < dimension.getLargeur(); ++i)
    {
        fichier.read((char *) matrice[i], dimension.getHauteur() * sizeof(bool));
    }
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
	verifcoord(x,y);
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
    verifcoord(x,y);
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

void ImageB::verifcoord(int x, int y) const
{
    if((x>dimension.getLargeur()) && (y>dimension.getHauteur())) throw(XYException('d',"Dimension en dehors de la matrice"));
    if(x>dimension.getLargeur()) throw(XYException('x',"Largeur en dehors de la matrice"));
    if(y>dimension.getHauteur()) throw(XYException('y',"Hauteur en dehors de la matrice"));
}

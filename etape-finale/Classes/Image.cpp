#include "Image.h"


//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------

Image::Image()
{
#ifdef DEBUG
    cout << ">>> Image : constructeur par defaut <<<" << endl;
#endif

    setId(0);
    nom = NULL;
    setNom("???");
}

Image::Image(int d, const char* s)
{
#ifdef DEBUG
    cout << ">>> Image : constructeur d'initialisation 1<<<" << endl;
#endif
    setId(d);  
    nom = NULL;
    setNom(s);
}

Image::Image(int d, const char* s, Dimension dim)
{
#ifdef DEBUG
    cout << ">>> Image : constructeur d'initialisation 2 <<<" << endl;
#endif

    setId(d);
    nom = NULL;
    setNom(s);
    
}

Image::Image(const Image& p)
{
#ifdef DEBUG
    cout << ">>> Image : constructeur de copie <<<" << endl;
#endif

    setId(p.getId());
    nom = NULL;
    setNom(p.getNom());

    dimension.setLargeur(p.dimension.getLargeur());
    dimension.setHauteur(p.dimension.getHauteur());

}

Image::Image(const char *f)
{
#ifdef DEBUG
    cout << ">>> Image : constructeur de copie <<<" << endl;
#endif

    setId(1);
    nom = NULL;
    setNom(f);

}

//----------------------------------
//-------DESTRUCTEURS
//----------------------------------

Image::~Image()
{
#ifdef DEBUG
    std::cout << ">>> Image : destructeur <<<" << std::endl;
#endif

    if (nom) 
        delete[] nom;
}

//----------------------------------
//-------GESTION FICHIER
//----------------------------------

void Image::Save(ofstream & fichier) const
{
    if(!fichier)
    {
        cout << "erreur d'ouverture !" << endl;
        exit(1);
    }
    
    fichier.write((char *) &id,sizeof(int));

    int taille = strlen(nom);
    fichier.write((char *) &taille,sizeof(int));
    fichier.write((char *) nom,taille * sizeof(char));
    dimension.Save(fichier);

    cout << "save image accomplish"<< endl;



    

}
void Image::Load(ifstream & fichier)
{
    if(!fichier.rdbuf()->is_open())
    {
        cout << "erreur d'ouverture !" << endl;
        exit(1);
    }
    

    fichier.read((char *) &id,sizeof(int));
    int taille = strlen(nom);
    fichier.read((char *) &taille,sizeof(int));
    
    fichier.read((char *) nom,taille * sizeof(char));
    dimension.Load(fichier);
}


//----------------------------------
//-------SETTERS
//----------------------------------

void Image::setId(int i)
{
    
    id = i;
}

void Image::setNom(const char* n)
{
    delete[] nom;
    if (n == NULL)
    {
        nom = NULL;
        return;
    }

    nom = new char[strlen(n) + 1];
    strcpy(nom, n);
}

void Image::setDimension(const Dimension& d)
{
    dimension = d;
}

//----------------------------------
//-------GETTERS
//----------------------------------

int Image::getId() const
{
    return id;
}

const char* Image::getNom() const
{
    return nom;
}

Dimension Image::getDimension() const
{
    return dimension;
}

//----------------------------------
//-------METHODES D'INSTANCES
//----------------------------------




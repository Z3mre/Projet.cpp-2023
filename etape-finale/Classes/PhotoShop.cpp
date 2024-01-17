#include "PhotoShop.h"

PhotoShop PhotoShop::instance;
int PhotoShop::numCourant=1;



// Constructeur par défaut

PhotoShop::PhotoShop() {}

// Destructeur

PhotoShop::~PhotoShop()
{
    reset();
}

// Méthode pour ajouter une image

void PhotoShop::ajouteImage(Image* pImage)
{
    pImage->setId(numCourant);
    numCourant++;

    images.insereElement(pImage);
}


// Méthodes pour supprimer une image par indice et par id

void PhotoShop::supprimeImageParIndice(int ind)
{
   // Vérification de l'indice

    if (ind < 0 || ind >= images.getNombreElements()) 
    {
        cout << "Indice hors limites" << endl;
        exit(0); 
    }

    Image *pImage = images.retireElement(ind);
    delete pImage; 
    cout << "image supprimée" << endl;
}

void PhotoShop::supprimeImageParId(int id)
{
    
   for (int i = 0; i < images.getNombreElements(); ++i)
    {
        Image *pImage = images.getElement(i);
        if (pImage->getId() == id)
        {
            images.retireElement(i);
            delete pImage; // Désallouer l'image
            break; // on sort de la boucle
        }
    }

    
}

// Méthodes pour récupérer une image par indice et par id
Image* PhotoShop::getImageParIndice(int indice)
{
    
    
        return images.getElement(indice);
    
    
}

Image* PhotoShop::getImageParId(int id)
{
    try
    {
        return images.getElement(id);
    }
    catch (const out_of_range& e)
    {
        cout << "Image introuvable" << endl;
        return nullptr;
    }
}

ArrayList<Image*>& PhotoShop::getImages() 
{
    return images; // Renvoie la liste d'images
}

// Méthodes pour afficher et dessiner les images
void PhotoShop::afficheImages() const
{
    Iterateur<Image*> it(images);
    for (it.reset() ; !it.end() ; it++)
    {
        Image* i = (Image*) it;
        i->Affiche();

    }
}

void PhotoShop::dessineImages() const
{
    Iterateur<Image*> it(images);
    for (it.reset() ; !it.end() ; it++)
    {
        Image* i = (Image*) it;
        i->Dessine();

    }
}

// Méthode pour réinitialiser la PhotoShop
void PhotoShop::reset()
{
    // Libérer la mémoire associée à la liste
    for (Iterateur<Image*> it(images); !it.end(); ++it)
    {
        delete it;
    }

    // Vider la liste (libère automatiquement la mémoire)
    images.estVide();

    // Réinitialiser numCourant à 1
    numCourant = 1;
}

//////////

const char* PhotoShop::verifierTypeImage(Image* imageTypeChoisi) 
{
    Image* imageSelectionnee = imageTypeChoisi;
    const char* type = nullptr;

    if (imageSelectionnee) 
    {
        // Comparaison des indicateurs pour déterminer le type d'image
        if (dynamic_cast<ImageNG*>(imageTypeChoisi)) 
        {
            type = "NG";
        }
        else if(dynamic_cast<ImageRGB*>(imageTypeChoisi))
        {
            type = "RGB";
        } 
        else if(dynamic_cast<ImageB*>(imageTypeChoisi))
        {
            type = "B";
        }
        else 
        {
            // Afficher un message d'erreur si les types ne correspondent pas
            perror("Erreur : Le type d'image sélectionné ne correspond pas à l'option choisie.");
            exit(0);
        }
    } 
    else
    {
        // Image non sélectionnée ou pointeur null
        perror("Erreur : Aucune image sélectionnée.");
        exit(0);
    }

    return type;
}

// METHODE STATIQUE

PhotoShop& PhotoShop::getInstance()
{
    return instance;
}

//***********************//

// Etape 12
Image *PhotoShop::operande1 = nullptr;
Image *PhotoShop::operande2 = nullptr;
Image *PhotoShop::resultat = nullptr;

// Etape 13
int PhotoShop::importeImages(const string &nomFichier)
{
    ifstream fichier(nomFichier);

    if (!fichier.is_open())
        return 0;

    int nombreImagesImportees = 0;

    string ligne;
    while (getline(fichier, ligne))
    {
        size_t posDebut = 0;
        size_t posFin = ligne.find(';');

        // Utiliser posFin pour détecter la fin de chaque champ
        string typeImage = ligne.substr(posDebut, posFin - posDebut);
        posDebut = posFin + 1;
        posFin = ligne.find(';', posDebut);
        string cheminImage = ligne.substr(posDebut, posFin - posDebut);
        posDebut = posFin + 1;
        string nomImage = ligne.substr(posDebut);

        // En fonction du type d'image, créer un objet du bon type
        if (typeImage == "NG")
        {
            ImageNG *pImageNG = new ImageNG();
            pImageNG->importFromFile(cheminImage.c_str());
            pImageNG->setNom(nomImage.c_str());
            ajouteImage(pImageNG);
        }
        else if (typeImage == "RGB")
        {
            ImageRGB *pImageRGB = new ImageRGB();
            pImageRGB->importFromFile(cheminImage.c_str());
            pImageRGB->setNom(nomImage.c_str());
            ajouteImage(pImageRGB);
        }
        nombreImagesImportees++;
    }

    return nombreImagesImportees;
}

// Etape 14
void PhotoShop::Save(const string &nomFichier) const
{
    ofstream fichier(nomFichier, ios::binary);

    if (!fichier.is_open() || fichier.fail())
    {
        cout << "Erreur lors de l'ouverture du fichier " << nomFichier << endl;
        return;
    }

    // Sauvegarde de numCourant
    fichier.write(reinterpret_cast<const char *>(&numCourant), sizeof(numCourant));
    cout << ">>> numCourant Save: " << numCourant << "<<<" << endl;

    // Sauvegarde de couleurs TRUE et FALSE
    fichier.write(reinterpret_cast<const char *>(&ImageB::couleurTrue), sizeof(ImageB::couleurTrue));
    fichier.write(reinterpret_cast<const char *>(&ImageB::couleurFalse), sizeof(ImageB::couleurFalse));

    // Sauvegarde le nombre d'images dans le conteneur
    int nbImages = images.getNombreElements();
    fichier.write(reinterpret_cast<const char *>(&nbImages), sizeof(nbImages));

    Image *pImage = nullptr;
    // Sauvegarde des images
    for (int i = 0; i < nbImages; ++i)
    {
        pImage = images.getElement(i);

        int typeImage = 0;

        if (dynamic_cast<ImageNG *>(pImage) != nullptr)
        {
            typeImage = 1;
        }
        else if (dynamic_cast<ImageRGB *>(pImage) != nullptr)
        {
            typeImage = 2;
        }
        else if (dynamic_cast<ImageB *>(pImage) != nullptr)
        {
            typeImage = 3;
        }

        // Écriture de l'identifiant du type d'image
        fichier.write(reinterpret_cast<const char *>(&typeImage), sizeof(typeImage));

        if (typeImage == 1)
        {
            dynamic_cast<ImageNG *>(pImage)->Save(fichier);
        }
        else if (typeImage == 2)
        {
            dynamic_cast<ImageRGB *>(pImage)->Save(fichier);
        }
        else if (typeImage == 3)
        {
            dynamic_cast<ImageB *>(pImage)->Save(fichier);
        }

        if (pImage != nullptr)
        {
            cout << "Type image : " << typeImage << endl;
            string typeIm = to_string(typeImage);
            cout << "Sauvegarde de l'image " << pImage->getNom() << " de type " << pImage->getType() << endl;
        }
    }
    fichier.close();
}

void PhotoShop::Load(const string &nomFichier)
{
    ifstream fichier(nomFichier, ios::binary);

    if (!fichier.is_open() || fichier.fail())
    {
        cout << "Erreur lors de l'ouverture du fichier " << nomFichier << endl;
        return;
    }

    // Réinitialisation de l'application
    reset();

    // Lecture de numCourant
    fichier.read(reinterpret_cast<char *>(&numCourant), sizeof(numCourant));
    cout << "numCourant: " << numCourant << endl;

    // Lecture de couleurs TRUE et FALSE
    fichier.read(reinterpret_cast<char *>(&ImageB::couleurTrue), sizeof(ImageB::couleurTrue));
    fichier.read(reinterpret_cast<char *>(&ImageB::couleurFalse), sizeof(ImageB::couleurFalse));
    cout << "couleurTrue: " << ImageB::couleurTrue << endl
         << "couleurFalse: " << ImageB::couleurFalse << endl;

    // Lecture du nombre d'images dans le conteneur
    int nbImages = 0;
    fichier.read(reinterpret_cast<char *>(&nbImages), sizeof(nbImages));
    cout << "Nombre Images: " << nbImages << endl;

    int typeImage;
    // Lecture des images
    for (int i = 0; i < nbImages; ++i)
    {
        typeImage = 0;
        fichier.read(reinterpret_cast<char *>(&typeImage), sizeof(typeImage));

        cout << i << ") Type de l'image : " << typeImage << endl;

        if (typeImage == 1)
        {
            ImageNG *pImageNG = new ImageNG();
            pImageNG->Load(fichier);
            images.insereElement(pImageNG);
            cout << ">>> ImageNG ajoutée" << endl;
        }
        else if (typeImage == 2)
        {
            ImageRGB *pImageRGB = new ImageRGB();
            pImageRGB->Load(fichier);
            images.insereElement(pImageRGB);
            cout << ">>> ImageRGB ajoutée" << endl;
        }
        else if (typeImage == 3)
        {
            ImageB *pImageB = new ImageB();
            pImageB->Load(fichier);
            images.insereElement(pImageB);
            cout << ">>> ImageB ajoutée" << endl;
        }
    }
    fichier.close();
}

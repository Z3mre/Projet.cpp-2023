#ifndef PHOTO_H
#define PHOTO_H

#include <iostream>
#include "ArrayList.h"
#include "Iterateur.h"
#include "Image.h"
#include "ImageNG.h"
#include "ImageB.h"
#include "ImageRGB.h"


class PhotoShop
{
     private:

         ArrayList<Image*> images;
         static int numCourant;
         static PhotoShop instance;

         PhotoShop(const PhotoShop& p);
         PhotoShop& operator=(const PhotoShop& p);

         PhotoShop();


     public:


         
         ~PhotoShop();
         void reset();
         void ajouteImage(Image* pImage);

         static PhotoShop& getInstance();

         void afficheImages() const;
         void dessineImages() const;
         Image* getImageParIndice(int indice);
         Image* getImageParId(int id);
         const char* verifierTypeImage(Image* imageTypeChoisi); 
         ArrayList<Image*>& getImages();
         void supprimeImageParIndice(int ind);
         void supprimeImageParId(int id);

        // Etape 12
        static Image *operande1;
        static Image *operande2;
        static Image *resultat;

        // Etape 13
        int importeImages(const string& nomFichier);

        // Etape 14
        void Save(const string& nomFichier) const;
        void Load(const string& nomFichier);

};

#endif
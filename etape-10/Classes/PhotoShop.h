#ifndef PHOTO_H
#define PHOTO_H

#include <iostream>
#include "ArrayList.h"
#include "Iterateur.h"
#include "Image.h"


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
         void supprimeImageParIndice(int ind);
         void supprimeImageParId(int id);

};

#endif
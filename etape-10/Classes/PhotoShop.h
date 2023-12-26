#ifndef PHOTO_H
#define PHOTO_H

#include <iostream>
#include "ArrayList.h"
#include "Image.h"


class PhotoShop
{
     private:

         ArrayList<Image*> images;
         static int numCourant;


     public:


         PhotoShop();
         ~PhotoShop();
         void reset();
         void ajouteImage(Image* pImage);

         void afficheImages() const;
         void dessineImages() const;
         Image* getImageParIndice(int indice);
         Image* getImageParId(int id);
         void supprimeImageParIndice(int ind);
         void supprimeImageParId(int id);

};

#endif
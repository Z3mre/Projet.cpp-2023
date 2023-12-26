#ifndef TRAIT_H
#define TRAIT_H

#include "ImageNG.h"

#include "ImageRGB.h"
#include "ImageB.h"

class Traitements
{
	public :

		static ImageB Seuillage(const ImageNG& imageIn, int seuil) ;

		static ImageNG FiltreMoyenneur(const ImageNG& imageIn, int taille) ;

		static ImageNG FiltreMedian(const ImageNG& imageIn, int taille) ;

		static ImageNG Erosion(const ImageNG& imageIn, int taille) ;

		static ImageNG Dilatation(const ImageNG& imageIn, int taille) ;

		static ImageNG Negatif(const ImageNG& imageIn);

};
#endif
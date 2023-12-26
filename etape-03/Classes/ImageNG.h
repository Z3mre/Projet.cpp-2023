#ifndef Image_NG_H
#define Image_NG_H

#include <iostream>
#include "Dimension.h"


using namespace std;


class ImageNG
{
	private :

		int id;
		char *nom;
		int** matrice;

		Dimension dimension;
		



	public : 

		ImageNG(void);
		ImageNG(int d, const char* s);
		ImageNG(int d,const char* s, Dimension dim);
		ImageNG(const ImageNG& p);
		

		~ImageNG();

		
		void setId (int i);
		void setNom (const char *n);
		void setPixel(int x,int y,int val);
		void setBackground(int val);

		void setDimension(const Dimension& d);


		int getId() const;
		const char * getNom() const;
		int getPixel(int x, int y) const;

		Dimension getDimension() const;
		


		void Affiche() const;
		void Dessine() const;
		void importFromFile(const char* fichier);
		void exportToFile(const char* fichier, const char* format);




};

#endif




#ifndef Image_NG_H
#define Image_NG_H

#include <iostream>
#include "Dimension.h"


using namespace std;


class ImageNG
{

	friend ostream& operator<<(ostream& s,const ImageNG& m);
 	friend ImageNG operator+(int n,ImageNG i1);
 	friend ImageNG operator-(ImageNG i1, ImageNG i2);

	private :

		int id;
		char *nom;
		int** matrice;

		Dimension dimension;

		int compI(const ImageNG& im);
		



	public : 

		ImageNG(void);
		ImageNG(int d, const char* s);
		ImageNG(int d,const char* s, Dimension dim);
		ImageNG(const ImageNG& p);
		ImageNG(const char* f);
		

		~ImageNG();

		ImageNG& operator=(const ImageNG& m);
		ImageNG  operator++(); // pré-incrémentation
		ImageNG operator++(int); // post-incrémentation
		ImageNG  operator--(); // pré-décrémentation
		ImageNG operator--(int); // post-décrémentation
		ImageNG operator+(int n);
		ImageNG operator-(int n);
		int operator==(const ImageNG& im);
		int operator<(const ImageNG& im);
		int operator>(const ImageNG& im);

		
		void setId (int i);
		void setNom (const char *n);
		void setPixel(int x,int y,int val);
		void setBackground(int val);

		void setDimension(const Dimension& d);


		int getId() const;
		const char * getNom() const;
		int getPixel(int x, int y) const;
		int getLuminance() const;
		int getMinimum() const;
		int getMaximum() const;
		float getContraste() const;

		Dimension getDimension() const;
		


		void Affiche() const;
		void Dessine() const;
		void importFromFile(const char* fichier);
		void exportToFile(const char* fichier, const char* format);




};

#endif




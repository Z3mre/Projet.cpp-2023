#ifndef Image_NG_H
#define Image_NG_H

#include <iostream>

#include "Image.h"

using namespace std;


class ImageNG : public  Image
{

	friend ostream& operator<<(ostream& s,const ImageNG& m);
 	friend ImageNG operator+(int n,ImageNG i1);
 	friend ImageNG operator-(ImageNG i1, ImageNG i2);

	private :

		
		int** matrice;


		int compI(const ImageNG& im);
		



	public : 

		ImageNG(void);
		ImageNG(int d, const char *s);
		ImageNG(int d,const char* s, Dimension dim);
		ImageNG(const ImageNG& p);
		ImageNG(const char* f);

		virtual ~ImageNG() override;
		

		

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

		
		
		void setPixel(int x,int y,int val);
		void setBackground(int val);

		void setDimension(const Dimension& d);


		
		int getPixel(int x, int y) const;
		int getLuminance() const;
		int getMinimum() const;
		int getMaximum() const;
		float getContraste() const;

		Dimension getDimension() const;

		void Affiche() const;
	    void Dessine() const;
		void exportToFile(const char *fichier, const char *format);
		void importFromFile(const char* fichier);
		




};

#endif




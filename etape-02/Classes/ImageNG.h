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
		

		Dimension dimension;


	public : 



		ImageNG(void);
		ImageNG(int d, const char* s);
		ImageNG(int d,const char* s, Dimension dim);
		ImageNG(const ImageNG& p);
		

		~ImageNG();

		
		void setId (int i);
		void setNom (const char *n);
		

		void setDimension(const Dimension& dim);


		int getId() const;
		const char * getNom() const;
		

		Dimension getDimension() const;
		


		void Affiche() const;
		




};

#endif




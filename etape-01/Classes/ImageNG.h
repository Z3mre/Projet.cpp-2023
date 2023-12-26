#ifndef Image_NG_H
#define Image_NG_H

#include <iostream>

using namespace std;


class ImageNG
{
	private :

		int id;
		char *nom;


	public : 

		ImageNG(void);
		ImageNG(int d, char* s=NULL);
		ImageNG(const ImageNG& p);
		~ImageNG();

		
		void setId (int i);
		void setNom (const char *n);

		int getId() const;
		const char * getNom() const;
		


		void Affiche() const;




};

#endif




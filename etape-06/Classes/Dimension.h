#ifndef DIM_H
#define DIM_H

#include <iostream>

#include "XYException.h"

using namespace std;


class Dimension
{
	friend ostream& operator<<(ostream& s,const Dimension& d);
	friend istream& operator>> (istream& s, Dimension& d);

	private : 

		int largeur;
		int hauteur;

		int compD(const Dimension& d);

	public : 

		static const Dimension VGA;
		static const Dimension HD;
		static const Dimension FULL_HD;

		Dimension();
		Dimension(int l, int h);
		Dimension(const Dimension& d2);

		~Dimension();

		int operator==(const Dimension& d);
		int operator!=(const Dimension& d);


		void setLargeur(int l);
		void setHauteur(int h);

		int getLargeur() const;
		int getHauteur() const;

		void Affiche() const;



};

#endif

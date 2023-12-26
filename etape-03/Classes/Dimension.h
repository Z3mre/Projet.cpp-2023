#ifndef DIM_H
#define DIM_H

#include <iostream>

using namespace std;


class Dimension
{
	private : 

		int largeur;
		int hauteur;

	public : 

		static const Dimension VGA;
		static const Dimension HD;
		static const Dimension FULL_HD;

		Dimension();
		Dimension(int l, int h);
		Dimension(const Dimension& d2);

		~Dimension();

		void setLargeur(int l);
		void setHauteur(int h);

		int getLargeur() const;
		int getHauteur() const;

		void Affiche() const;



};

#endif

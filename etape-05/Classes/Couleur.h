#ifndef COUL_H
#define COUL_H

#include <iostream>

using namespace std;


class Couleur
{
	friend ostream& operator<<(ostream& s,const Couleur& c);

	private : 

		int rouge;
		int vert;
		int bleu;


		
	public : 

		static const Couleur ROUGE;
		static const Couleur VERT;
		static const Couleur BLEU;
		static const Couleur BLANC;
		static const Couleur NOIR;

		Couleur();
		Couleur(int r, int v, int b);
		Couleur(const Couleur& c);

		~Couleur();

		void setRouge(int r);
		void setVert(int v);
		void setBleu(int b);


		int getRouge() const;
		int getVert() const;
		int getBleu() const;

		void Affiche() const;


		


};

#endif

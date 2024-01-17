#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string.h>

using namespace std;

template <class T> struct Cellule
{
	T valeur ;
	Cellule<T> *suivant ;

	Cellule(T val, Cellule<T> *suiv) : valeur(val), suivant(suiv) {};
};

template <class T> class Iterateur;

template <class T> class ArrayList
{
	private :

		Cellule<T> *ptete;

	public :

		ArrayList();
		ArrayList(const ArrayList<T>& a);
		~ArrayList();

		ArrayList<T>& operator=(const ArrayList<T>& a);

		

		int  getNombreElements() const;
		T& getElement(int ind) const;

		bool estVide();
		void insereElement(const T& val);
		T retireElement(int ind);


		void Affiche();

		friend class Iterateur<T>;

		


};

#endif

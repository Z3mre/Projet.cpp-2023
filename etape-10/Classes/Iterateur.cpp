#include "Iterateur.h"




template<class T>

Iterateur<T>::Iterateur(ArrayList<T>& list) : a(list), pcur(list.ptete) {}


template<class T>

int Iterateur<T>::end()
{
	return pcur == 0;
}

template<class T>

void Iterateur<T>::reset()
{
	pcur = a.ptete;
}


//----------------------------------
//-------OPERATEURS
//----------------------------------
template<class T>

char Iterateur<T>::operator++()
{
	if(pcur)
	{
		pcur = pcur->suivant;
		return 1;
	}

	return 0;

}

template<class T>

char Iterateur<T>::operator++(int)
{
	return operator++();


}


template<class T>

Iterateur<T>::operator T() const
{
	return pcur->valeur;
}

template<class T>

T& Iterateur<T>::operator&()
{
	return pcur->valeur;
}

//-----------------------------------------
//-------INSTANCIATION DES TEMPLATES-------
//-----------------------------------------

template class Iterateur<int>;

#include "Couleur.h"
template class Iterateur<Couleur>;

#include "ImageB.h"
template class Iterateur<ImageB>;

#include "ImageNG.h"
template class Iterateur<ImageNG>;

#include "ImageRGB.h"
template class Iterateur<ImageRGB>;


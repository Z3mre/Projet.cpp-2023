#include "Iterateur.h"
#include "Image.h"


template<class T>

Iterateur<T>::Iterateur(const ArrayList<T>& list) : a(list), pcur(list.ptete) {}


template<class T>

int Iterateur<T>::end() const
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

template class Iterateur<Image*>;




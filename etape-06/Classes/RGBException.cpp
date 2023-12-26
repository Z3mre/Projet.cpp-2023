#include "RGBException.h"

#include <math.h>
#include <string.h>



//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------

RGBException::RGBException() : Exception()
{
	#ifdef DEBUG
		cout << ">>> RGBException : constructeur par defaut <<<" << endl;  
	#endif
}

RGBException::RGBException(int code,const char* msg) : Exception(msg)
{
	#ifdef DEBUG
		cout << ">>> RGBException : constructeur  <<<" << endl;  
	#endif

		setvaleur(code);

		

}

RGBException::RGBException(const RGBException& e) : Exception(e)
{
	#ifdef DEBUG
		cout << ">>> RGBException : constructeur de copie <<<" << endl;  
	#endif

	valeur = e.valeur;

}



//----------------------------------
//-------DESTRUCTEURS
//----------------------------------


RGBException::~RGBException()
{
	#ifdef DEBUG
		cout << ">>> RGBException : destructeur <<<" << endl;  
	#endif
}


//----------------------------------
//-------SETTERS
//----------------------------------

void RGBException::setvaleur(int v)
{
	valeur = v;
}



//----------------------------------
//-------GETTERS
//----------------------------------

int RGBException::getvaleur() const
{
	return valeur;
}



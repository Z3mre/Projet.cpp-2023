#include "XYException.h"


#include <math.h>
#include <string.h>



//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------


XYException::XYException() : Exception()
{
	#ifdef DEBUG
		cout << ">>> XYException : constructeur par defaut <<<" << endl;  
	#endif
}

XYException::XYException(const char val, const char* msg) : Exception(msg)
{
	#ifdef DEBUG
		cout << ">>> XYException : constructeur  <<<" << endl;  
	#endif

		setVal(val);

}

XYException::XYException(const XYException& e) : Exception(e)
{
	#ifdef DEBUG
		cout << ">>> XYException : constructeur de copie <<<" << endl;  
	#endif

}

//----------------------------------
//-------DESTRUCTEURS
//----------------------------------

XYException::~XYException()
{
	#ifdef DEBUG
		cout << ">>> XYException : destructeur <<<" << endl;  
	#endif

		

}

//----------------------------------
//-------SETTERS
//----------------------------------

void XYException::setVal(const char v)
{
	
    val = v;
   
}

//----------------------------------
//-------GETTERS
//----------------------------------

char XYException::getVal() const
{
	return val;
}


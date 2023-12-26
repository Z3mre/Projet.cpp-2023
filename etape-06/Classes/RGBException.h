#ifndef RGBEXCEPTION_C
#define RGBEXCEPTION_C

#include <iostream>

#include "Exception.h"

using namespace std;


class RGBException : public Exception
{
	private :

		int valeur;



	public : 

		RGBException();
		RGBException(const RGBException& e);
		RGBException(int code,const char* msg);

		void setvaleur(int v);

		int getvaleur()const;

		virtual ~RGBException() override;
		

};
#endif

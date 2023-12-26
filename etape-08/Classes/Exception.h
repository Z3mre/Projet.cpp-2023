#ifndef EXCEPTION_C
#define EXCEPTION_C



#include <iostream>
#include <string.h>

using namespace std;

class Exception 
{
	protected :

		char message[80];

	public :

		Exception();
		Exception(const char* msg);
		Exception(const Exception& e);

		virtual ~Exception();
		
		virtual const char* getMessage() const;
		void setmsg(const char* m);
		
};

#endif
#ifndef XYEXCEPTION_C
#define XYEXCEPTION_C


#include <iostream>

#include "Exception.h"

using namespace std;

class XYException : public Exception 
{

	private :

		char val;

	public : 

		XYException();
		XYException(const XYException& e);
		XYException(const char val, const char* msg);
		virtual ~XYException() override;

		void setVal(const char v);

		char getVal() const;
	
};
#endif

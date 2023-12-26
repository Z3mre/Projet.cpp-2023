#include "Exception.h"

#include <iostream>



//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------

Exception::Exception() 
{
#ifdef DEBUG
    cout << ">>> Exception : constructeur par defaut <<<" << endl;
#endif
    
}


Exception::Exception(const char* msg) 
{
#ifdef DEBUG
    cout << ">>> Exception : constructeur d'initialisation <<<" << endl;
#endif
    setmsg(msg);
}

Exception::Exception(const Exception& e)
{
#ifdef DEBUG
    cout << ">>> Exception : constructeur copie <<<" << endl;
#endif

    setmsg(e.getMessage());
}

//----------------------------------
//-------DESTRUCTEUR
//----------------------------------

Exception::~Exception()
{
#ifdef DEBUG
	cout << ">>> Exception : destructeur <<<" << endl;
#endif
	
}

//----------------------------------
//-------GETTERS
//----------------------------------

const char* Exception::getMessage() const
{
    return message;
}

//----------------------------------
//-------SETTERS
//----------------------------------

void Exception::setmsg(const char* m)
{
    if (m == nullptr)
    {
        message[0] = '\0'; 
        return;
    }

    strcpy(message, m);
    message[sizeof(message) - 1] = '\0';
}

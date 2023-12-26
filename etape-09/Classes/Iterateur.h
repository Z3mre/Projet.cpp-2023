#ifndef ITER_H
#define ITER_H

#include "ArrayList.h"

template<class T>
class Iterateur
{
private:
    ArrayList<T>& a;
    Cellule<T>* pcur;

public:
    Iterateur(ArrayList<T>& list);
    int end();
    void reset();

    char operator++();
    char operator++(int);

    operator T() const;
    T& operator&();
};

#endif

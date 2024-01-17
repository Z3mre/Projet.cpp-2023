#ifndef ITER_H
#define ITER_H

#include "ArrayList.h"

template<class T>
class Iterateur
{
private:
    const ArrayList<T>& a;
    Cellule<T>* pcur;

public:
    Iterateur(const ArrayList<T>& list);
    int end() const;
    void reset();

    char operator++();
    char operator++(int);

    operator T() const;
    T& operator&();
};

#endif

#ifndef Image_H
#define Image_H

#include <iostream>
#include <string.h>
#include <fstream>
#include "Dimension.h"

using namespace std;

class Image
{
protected:
    int id;
    char *nom;
    Dimension dimension;

public:
    
    Image();
    Image(int d, const char* s);
    Image(int d, const char* s, Dimension dim);
    Image(const Image& p);
    Image(const char* f);

    virtual ~Image();

    virtual void Save(ofstream & fichier) const = 0;
    virtual void Load(ifstream & fichier) = 0;

    void setId(int i);
    void setNom(const char *n);
    void setDimension(const Dimension &d);

    int getId() const;
    const char *getNom() const;
    Dimension getDimension() const;

    virtual void Affiche() const = 0;
    virtual void Dessine() const = 0;
    virtual void exportToFile(const char *fichier, const char *format) = 0;
};

#endif

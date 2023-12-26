#ifndef Image_RGB_H
#define Image_RGB_H

#include <iostream>
#include "Image.h"
#include "Couleur.h"
#include "XYException.h"


using namespace std;

class ImageRGB : public  Image
{
    friend ostream& operator<<(ostream& s, const ImageRGB& m);

private:
    Couleur** matrice;

public:
    ImageRGB();
    ImageRGB(int d, const char* s);
    ImageRGB(int d, const char* s, Dimension dim);
    ImageRGB(const ImageRGB& p);
    ImageRGB(const char* f);
    virtual ~ImageRGB() override;

    void Save(ofstream & fichier) const;
    void Load(ifstream & fichier);

    ImageRGB& operator=(const ImageRGB& m);

    void setPixel(int x, int y, const Couleur& c);
    void setBackground(const Couleur& c);
    void setDimension(const Dimension& d);

    Couleur getPixel(int x, int y) const;

    Dimension getDimension() const;

    void Affiche() const;
    void Dessine() const;
    void exportToFile(const char* fichier, const char* format);
    void importFromFile(const char* fichier);
    void verifcoord(int x, int y) const ;
};

#endif

#ifndef Image_B_H
#define Image_B_H

#include <iostream>
#include "Image.h"
#include "Couleur.h"  

using namespace std;


class ImageB : public  Image
{
    friend std::ostream& operator<<(std::ostream& s, const ImageB& m);

private:
    bool** matrice;

public:
    static  Couleur couleurTrue;
    static  Couleur couleurFalse;

    ImageB();
    ImageB(int d, const char* s);
    ImageB(int d, const char* s, Dimension dim);
    ImageB(const ImageB& p);

    virtual ~ImageB() override;

    ImageB& operator=(const ImageB& m);

    void setPixel(int x, int y,  bool c);
    void setBackground( bool c);
    void setDimension(const Dimension& d);

    bool getPixel(int x, int y) const;

    Dimension getDimension() const;

    void Affiche() const;
    void Dessine() const;
    void exportToFile(const char* fichier, const char* format);
};

#endif

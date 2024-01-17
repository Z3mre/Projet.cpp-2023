#ifndef Image_B_H
#define Image_B_H

#include <iostream>
#include "Image.h"
#include "Couleur.h"  
#include "XYException.h"


using namespace std;


class ImageB : public  Image
{
    friend ostream& operator<<(ostream& s, const ImageB& m);

private:
    bool** matrice;

public:
    static  Couleur couleurTrue;
    static  Couleur couleurFalse;

    ImageB();
    ImageB(int d, const char* s);
    ImageB(int d, const char* s, Dimension dim);
    ImageB(const ImageB& p);
    ImageB(const char* f);

    virtual ~ImageB() override;

    void Save(ofstream & fichier) const;
    void Load(ifstream & fichier);

    ImageB& operator=(const ImageB& m);

    void setPixel(int x, int y,  bool c);
    void setBackground( bool c);
    void setDimension(const Dimension& d);

    bool getPixel(int x, int y) const;

    Dimension getDimension() const;

    string getType() const override;

    void Affiche() const;
    void Dessine() const;
    void exportToFile(const char* fichier, const char* format);
    void verifcoord(int x, int y) const ;
};

#endif

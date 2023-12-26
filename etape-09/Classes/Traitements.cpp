#include "Traitements.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;


ImageB Traitements::Seuillage(const ImageNG& imageIn, int seuil)
{

    // Obtention des dimensions de l'image d'entrée
    int largeur = imageIn.getDimension().getLargeur();
    int hauteur = imageIn.getDimension().getHauteur();

    // Convertir la valeur du seuil en chaîne de caractères
	ostringstream oss;
	oss << seuil;
	string seuilString = oss.str();

	// Concaténer la chaîne avec le nom de l'image
	string nomImage = "lena";
	string nomImageSeuil = nomImage + "-seuil" + seuilString;

	const char * name = nomImageSeuil.c_str();

	// Création d'une image binaire de même dimension
    ImageB imageOut(0,name,imageIn.getDimension());

    // Parcours de chaque pixel de l'image d'entrée
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < hauteur; ++j) {
            // Récupération du niveau de gris du pixel
            int niveauGris = imageIn.getPixel(i, j);

            // Seuillage : true si le niveau de gris est supérieur au seuil, false sinon
            bool pixelSeuil = (niveauGris > seuil);

            // Affectation de la valeur au pixel correspondant de l'image de sortie
            imageOut.setPixel(i, j, pixelSeuil);
        }
    }

    return imageOut;


}

// ********************************************************************************************

ImageNG Traitements::FiltreMoyenneur(const ImageNG& imageIn, int taille)
{
	// Créer une nouvelle image résultante avec la même dimension que l'image d'entrée
    ImageNG imageOut(imageIn);
   

    // Boucle sur chaque pixel de l'imageIn
    for (int x = 0; x < imageIn.getDimension().getLargeur(); ++x)
     {
        for (int y = 0; y < imageIn.getDimension().getHauteur(); ++y) 
        {
            int somme = 0;
            int count = 0;

            // Boucle sur les pixels environnants (taille x taille)
            for (int i = -taille / 2; i <= taille / 2; ++i) {
                for (int j = -taille / 2; j <= taille / 2; ++j) {
                    int newX = x + i;
                    int newY = y + j;

                    // Vérifier que le pixel environnant est à l'intérieur de l'image
                    if (newX >= 0 && newX < imageIn.getDimension().getLargeur() &&
                        newY >= 0 && newY < imageIn.getDimension().getHauteur()) 
                    {
                    	somme += imageIn.getPixel(newX,newY);
                    	count++;
                        
                    }
                }
            }

            // Calculer la moyenne et assigner la nouvelle valeur au pixel dans l'image résultante
            if (count > 0) {
                int moyenne = somme / count;
                imageOut.setPixel(x, y, moyenne);
            } else {
                // Dans le cas improbable où count est égal à zéro, conserver la valeur d'origine
                imageOut.setPixel(x, y, imageIn.getPixel(x, y));
            }
        }
    }

	    // Convertir la valeur de la taille en chaîne de caractères
	ostringstream oss;
	oss << taille;
	string tailleString = oss.str();

	// Utiliser strncpy pour copier la chaîne dans un tableau de caractères
	char tstr[10]; // Assurez-vous que la taille est suffisante
	strncpy(tstr, tailleString.c_str(), sizeof(tstr));
	tstr[sizeof(tstr) - 1] = '\0'; // Assurer la null-termination

	// Concaténer la chaîne avec le nom de l'image
	char nomImagetaille[100]; // Assurez-vous que la taille est suffisante
	snprintf(nomImagetaille, sizeof(nomImagetaille), "%s-taille%s", imageOut.getNom(), tstr);

	imageOut.setNom(nomImagetaille);


	

    return imageOut;

}

// ********************************************************************************************


ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int taille)
{

	ImageNG imageOut(imageIn);

	int m = imageIn.getDimension().getLargeur();
    int n = imageIn.getDimension().getHauteur();

    // for (int i = 0; i < m; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         // Créer la fenêtre
    //         vector<int> fenetre;

    //         // Parcourir la fenêtre autour du pixel (i, j)
    //         for (int x = max(0, i - taille / 2); x <= min(m - 1, i + taille / 2); ++x) {
    //             for (int y = max(0, j - taille / 2); y <= min(n - 1, j + taille / 2); ++y) {
    //                 fenetre.push_back(imageIn.getPixel(x, y));
    //             }
    //         }

    //         // Trier les valeurs de la fenêtre
    //         sort(fenetre.begin(), fenetre.end());

    //         // Remplacer la valeur du pixel par la médiane
    //         int indiceMedian = fenetre.size() / 2;
    //         imageOut.setPixel(i, j, fenetre[indiceMedian]);
    //     }
    // }

     for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Créer le tableau fenetre
            int fenetre[20];
            int indice = 0; // Indice pour suivre la position actuelle dans le tableau

            // Parcourir la fenêtre autour du pixel (i, j)
            for (int x = max(0, i - taille / 2); x <= min(m - 1, i + taille / 2); x++) {
                for (int y = max(0, j - taille / 2); y <= min(n - 1, j + taille / 2); y++) {
                    fenetre[indice] = imageIn.getPixel(x, y);
                    indice++;
                }
            }

            // Trier les valeurs de la fenêtre
            sort(fenetre, fenetre + indice);

            // Remplacer la valeur du pixel par la médiane
            int indiceMedian = indice / 2;
            imageOut.setPixel(i, j, fenetre[indiceMedian]);
        }
    }

    

	    // Convertir la valeur de la taille en chaîne de caractères
	ostringstream oss;
	oss << taille;
	string tailleString = oss.str();

	// Utiliser strncpy pour copier la chaîne dans un tableau de caractères
	char tstr[10]; // Assurez-vous que la taille est suffisante
	strncpy(tstr, tailleString.c_str(), sizeof(tstr));
	tstr[sizeof(tstr) - 1] = '\0'; // Assurer la null-termination

	// Concaténer la chaîne avec le nom de l'image
	char nomImagetaille[100]; // Assurez-vous que la taille est suffisante
	snprintf(nomImagetaille, sizeof(nomImagetaille), "%s-taille%s", imageOut.getNom(), tstr);

	imageOut.setNom(nomImagetaille);

	return imageOut;

}

// ********************************************************************************************
ImageNG Traitements::Erosion(const ImageNG& imageIn, int taille)
{
	ImageNG imageOut(imageIn);

	int m = imageIn.getDimension().getLargeur();
    int n = imageIn.getDimension().getHauteur();


	 for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            int fenetre[20];
            int indice = 0; 

            for (int x = max(0, i - taille / 2); x <= min(m - 1, i + taille / 2); x++) {
                for (int y = max(0, j - taille / 2); y <= min(n - 1, j + taille / 2); y++) {
                    fenetre[indice] = imageIn.getPixel(x, y);
                    indice++;
                }
            }

            int min = 255;
            for(int a = 0;a < indice; a++)
            {
            	if(fenetre[a]<min)
            	{
            		min = fenetre[a];
            	}
            }

            
            imageOut.setPixel(i, j, min);
        }
    }

    

	    // Convertir la valeur de la taille en chaîne de caractères
	ostringstream oss;
	oss << taille;
	string tailleString = oss.str();

	// Utiliser strncpy pour copier la chaîne dans un tableau de caractères
	char tstr[10]; // Assurez-vous que la taille est suffisante
	strncpy(tstr, tailleString.c_str(), sizeof(tstr));
	tstr[sizeof(tstr) - 1] = '\0'; // Assurer la null-termination

	// Concaténer la chaîne avec le nom de l'image
	char nomImagetaille[100]; // Assurez-vous que la taille est suffisante
	snprintf(nomImagetaille, sizeof(nomImagetaille), "%s-eros%s", imageOut.getNom(), tstr);

	imageOut.setNom(nomImagetaille);

	return imageOut;

}


// ********************************************************************************************
ImageNG Traitements::Dilatation(const ImageNG& imageIn, int taille)
{
	ImageNG imageOut(imageIn);

	int m = imageIn.getDimension().getLargeur();
    int n = imageIn.getDimension().getHauteur();

	 for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int fenetre[20];
            int indice = 0;

            for (int x = max(0, i - taille / 2); x <= min(m - 1, i + taille / 2); x++) {
                for (int y = max(0, j - taille / 2); y <= min(n - 1, j + taille / 2); y++) {
                    fenetre[indice] = imageIn.getPixel(x, y);
                    indice++;
                }
            }

            int max = 0;
            for(int a = 0;a < indice; a++)
            {
            	if(fenetre[a]>max)
            	{
            		max = fenetre[a];
            	}
            }

           
            imageOut.setPixel(i, j, max);
        }
    }

    

	    // Convertir la valeur de la taille en chaîne de caractères
	ostringstream oss;
	oss << taille;
	string tailleString = oss.str();

	// Utiliser strncpy pour copier la chaîne dans un tableau de caractères
	char tstr[10]; // Assurez-vous que la taille est suffisante
	strncpy(tstr, tailleString.c_str(), sizeof(tstr));
	tstr[sizeof(tstr) - 1] = '\0'; // Assurer la null-termination

	// Concaténer la chaîne avec le nom de l'image
	char nomImagetaille[100]; // Assurez-vous que la taille est suffisante
	snprintf(nomImagetaille, sizeof(nomImagetaille), "%s-dilate%s", imageOut.getNom(), tstr);

	imageOut.setNom(nomImagetaille);

	return imageOut;


}

// ********************************************************************************************


ImageNG Traitements::Negatif(const ImageNG& imageIn)
{
	ImageNG imageOut(imageIn);

	int m = imageIn.getDimension().getLargeur();
    int n = imageIn.getDimension().getHauteur();


	for(int x = 0; x<m; x++)
	{
		for(int y = 0; y<n; y++)
		{
			imageOut.setPixel(x,y,(255-imageOut.getPixel(x,y)));
		}
	}

	string nom = imageOut.getNom();
	nom += "-negatif";
	imageOut.setNom(nom.c_str());



	



	return imageOut;
}


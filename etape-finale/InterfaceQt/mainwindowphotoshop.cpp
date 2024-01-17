#include "mainwindowphotoshop.h"
#include "ui_mainwindowphotoshop.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QScreen>
#include <QRect>
#include <QPixmap>
#include <QColorDialog>


#include "Classes/ImageNG.h"
#include "Classes/ImageRGB.h"
#include "Classes/ImageB.h"
#include "Classes/PhotoShop.h"
#include "Classes/Iterateur.h"
#include "Classes/Traitements.h"
#include "Classes/XYException.h"


MainWindowPhotoShop::MainWindowPhotoShop(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindowPhotoShop)
{
    ui->setupUi(this);
    setTitre("Mini-PhotoShop  en C++");

    // Centrage de la fenetre
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
    setFixedSize(1021,845);

    // Configuration de la table des images
    ui->tableWidgetImages->setColumnCount(4);
    ui->tableWidgetImages->setRowCount(0);
    QStringList labelsTableOptions;
    labelsTableOptions << "Id" << "Type" << "Dimension" << "Nom";
    ui->tableWidgetImages->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetImages->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetImages->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetImages->horizontalHeader()->setVisible(true);
    ui->tableWidgetImages->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetImages->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetImages->verticalHeader()->setVisible(false);
    ui->tableWidgetImages->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Intialisation des scrollArea
    
    setImageNG("selection");
    setImageNG("operande1");
    setImageNG("operande2");
    setImageNG("resultat");
    

    // ComboBox des traitements disponibles
    ajouteTraitementDisponible("Eclaircir (+ val)");
    ajouteTraitementDisponible("Eclaircir (++)");
    ajouteTraitementDisponible("Assombrir (- val)");
    ajouteTraitementDisponible("Assombrir (--)");
    ajouteTraitementDisponible("Différence");
    ajouteTraitementDisponible("Comparaison (==)");
    ajouteTraitementDisponible("Comparaison (<)");
    ajouteTraitementDisponible("Comparaison (>)");
    ajouteTraitementDisponible("Seuillage");
    ajouteTraitementDisponible("Filtre moyenneur");
    ajouteTraitementDisponible("Filtre médian");
    ajouteTraitementDisponible("Erosion");
    ajouteTraitementDisponible("Dilatation");
    ajouteTraitementDisponible("Négatif");

    // Etape 14 (TO DO)
    // Restauration bibliothèque via fichier de sauvegarde
    PhotoShop::getInstance().Load("sauvegarde.dat"); // Si le fichier de sauvegarde existe

    // vider table images et la mettre à jour

    videTableImages();

    PhotoShop& pI = PhotoShop::getInstance();
    ArrayList<Image*>& image = pI.getImages();

    Iterateur<Image*> it(image);

    for(it.reset();!it.end();it++)
    {

      Image* imageAjoutee = (Image*)it;
        
      string type = imageAjoutee->getType();
      string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
      string nomImage = imageAjoutee->getNom();
      ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
    }


    
}

MainWindowPhotoShop::~MainWindowPhotoShop()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Méthodes de la fenêtre (ne pas modifier) ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setTitre(string titre)
{
  this->setWindowTitle(titre.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setNomImage(string nom)
{
  ui->lineEditNom->setText(QString::fromStdString(nom));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getNomImage() const
{
  return ui->lineEditNom->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setParametresImageNG(int max,int min,int luminance,float contraste)
{
  if (max == -1)
  {
    ui->lineEditMax->setText("");
    ui->lineEditMin->setText("");
    ui->lineEditLuminance->setText("");
    ui->lineEditContraste->setText("");
    return;
  }
  char tmp[20];
  sprintf(tmp,"%d",max);
  ui->lineEditMax->setText(tmp);
  sprintf(tmp,"%d",min);
  ui->lineEditMin->setText(tmp);
  sprintf(tmp,"%d",luminance);
  ui->lineEditLuminance->setText(tmp);
  sprintf(tmp,"%f",contraste);
  ui->lineEditContraste->setText(tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageNG(string destination,const ImageNG* imageng)
{
    QPixmap * pixmap = NULL;
    if (imageng != NULL)
    {
      // Creation du QPixmap
      int largeur = imageng->getDimension().getLargeur();
      int hauteur = imageng->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          int valeur = imageng->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur,valeur,valeur));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageRGB(string destination,const ImageRGB* imagergb)
{
    QPixmap * pixmap = NULL;
    if (imagergb != NULL)
    {
      // Creation du QPixmap
      int largeur = imagergb->getDimension().getLargeur();
      int hauteur = imagergb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          Couleur valeur = imagergb->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur.getRouge(),valeur.getVert(),valeur.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageB(string destination,const ImageB* imageb)
{
    QPixmap * pixmap = NULL;
    if (imageb != NULL)
    {
      // Creation du QPixmap
      int largeur = imageb->getDimension().getLargeur();
      int hauteur = imageb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          bool valeur = imageb->getPixel(x,y);
          if (valeur) im1.setPixel(x,y,qRgb(ImageB::couleurTrue.getRouge(),ImageB::couleurTrue.getVert(),ImageB::couleurTrue.getBleu()));
          else im1.setPixel(x,y,qRgb(ImageB::couleurFalse.getRouge(),ImageB::couleurFalse.getVert(),ImageB::couleurFalse.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setResultatBoolean(int val)
{
  if (val == 1) // vrai
  {
    ui->checkBoxResultat->setChecked(true);
    ui->checkBoxResultat->setText("VRAI");
    ui->checkBoxResultat->setStyleSheet("background-color: lightgreen;border: 1px solid black;");
    return;
  }
  if (val == 0) // faux
  {
    ui->checkBoxResultat->setChecked(false);
    ui->checkBoxResultat->setText("FAUX");
    ui->checkBoxResultat->setStyleSheet("background-color: red;border: 1px solid black;");
    return;
  }
  // ni vrai, ni faux
  ui->checkBoxResultat->setChecked(false);
  ui->checkBoxResultat->setText("Résultat");
  ui->checkBoxResultat->setStyleSheet("background-color: lightyellow;border: 1px solid black;");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Images (ne pas modifier) ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTupleTableImages(int id,string type,string dimension,string nom)
{
    char Id[20];
    sprintf(Id,"%d",id);

    char Type[20];
    strcpy(Type,type.c_str());

    char Dimension[20];
    strcpy(Dimension,dimension.c_str());

    char Nom[80];
    strcpy(Nom,nom.c_str());

    // Ajout possible
    int nbLignes = ui->tableWidgetImages->rowCount();
    nbLignes++;
    ui->tableWidgetImages->setRowCount(nbLignes);
    ui->tableWidgetImages->setRowHeight(nbLignes-1,20);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Id);
    ui->tableWidgetImages->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Type);
    ui->tableWidgetImages->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Dimension);
    ui->tableWidgetImages->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(Nom);
    ui->tableWidgetImages->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTableImages()
{
    ui->tableWidgetImages->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::getIndiceImageSelectionnee()
{
    QModelIndexList liste = ui->tableWidgetImages->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des traitements disponibles (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTraitementDisponible(string operation)
{
    ui->comboBoxTraitements->addItem(operation.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTraitementsDisponibles()
{
    ui->comboBoxTraitements->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getTraitementSelectionne() const
{
    return ui->comboBoxTraitements->currentText().toStdString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue (ne pas modifier) ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MainWindowPhotoShop::dialogueDemandeFloat(const char* titre,const char* question)
{
    return QInputDialog::getDouble(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierOuvrir(const char* question)
{
  QString fileName = QFileDialog::getOpenFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierEnregistrer(const char* question)
{
  QString fileName = QFileDialog::getSaveFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueDemandeCouleur(const char* message,int* pRouge,int* pVert,int* pBleu)
{
  QColor color = QColorDialog::getColor(Qt::red,this,message);
  *pRouge = color.red();
  *pVert = color.green();
  *pBleu = color.blue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Clic sur la croix de la fenêtre ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::closeEvent(QCloseEvent *event)
{
  if (event == NULL) {} // pour éviter le warning à la compilation
  // Etape 14 (TO DO)

   // Vérifier si la bibliothèque contient des images
  // Demander à l'utilisateur s'il veut enregistrer l'état de l'application
  // Si oui, enregistrer l'état dans un fichier de sauvegarde

  if (!PhotoShop::getInstance().getImages().estVide())
  {
    string enregistrer;
    enregistrer = dialogueDemandeTexte("Quitter", "Voulez-vous enregistrer l'état de l'application o/n? ");

    if (enregistrer == "o" || enregistrer == "O")
    {
      PhotoShop::getInstance().Save("sauvegarde.dat");
    }
  }

  QApplication::exit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionQuitter_triggered()
{
  // Etape 14 (TO DO)

  if (!PhotoShop::getInstance().getImages().estVide())
  {
    string enregistrer;
    enregistrer = dialogueDemandeTexte("Quitter", "Voulez-vous enregistrer l'état de l'application o/n? ");

    if (enregistrer == "o" || enregistrer == "O")
    {
      PhotoShop::getInstance().Save("sauvegarde.dat");
    }
  }

  QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageNB_triggered()
{
  // Etape 11 (TO DO)
 
  string nom = dialogueDemandeFichierOuvrir("Entrez le nom de l'image à charger : ");

  if (nom == "")
  {
    // dialogueErreur("Erreur", "Impossible de charger le fichier image.");
    return;
  }
  const char *nomf = nom.c_str();

  ImageNG* newIm = new ImageNG(nomf);

  

  PhotoShop& pI = PhotoShop::getInstance();

  pI.ajouteImage(newIm);

  videTableImages();

 
  ArrayList<Image*>& image = pI.getImages();
    Iterateur<Image*> it(image);

    for(it.reset();!it.end();it++){

        Image* imageAjoutee = (Image*)it;
        
            
            string type = imageAjoutee->getType();
            string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
            string nomImage = imageAjoutee->getNom();
            ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
        
        
    }

  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageRGB_triggered()
{
  // Etape 11 (TO DO)

  string nom = dialogueDemandeFichierOuvrir("Entrez le nom de l'image à charger : ");
   if (nom == "")
  {
    // dialogueErreur("Erreur", "Impossible de charger le fichier image.");
    return;
  }
  const char *nomf = nom.c_str();

  ImageRGB* newIm = new ImageRGB(nomf);

  

  PhotoShop& pI = PhotoShop::getInstance();

  pI.ajouteImage(newIm);

  videTableImages();

  

  // ImageRGB *ImageAjoutee;
  //  for (int i = 0; i < image.getNombreElements(); ++i) {
  //       ImageAjoutee = dynamic_cast<ImageRGB*>(image.getElement(i));

  //       if (ImageAjoutee) 
  //       {
  //           string type = "RGB";
  //           string dimension = to_string(ImageAjoutee->getDimension().getLargeur()) + "x" + to_string(ImageAjoutee->getDimension().getHauteur());
  //           string nomImage = ImageAjoutee->getNom();
  //           ajouteTupleTableImages(ImageAjoutee->getId(), type, dimension, nomImage);
  //       }
  //   }

  ArrayList<Image*>& image = pI.getImages();
    Iterateur<Image*> it(image);

    for(it.reset();!it.end();it++) {
        Image* imageAjoutee = (Image*)it;
        
            string type = imageAjoutee->getType();
            string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
            string nomImage = imageAjoutee->getNom();
            ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
        
        
    }


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageNB_triggered()
{
  // Etape 11 (TO DO)

   // Étape 1 : Récupérer l'indice de l'image sélectionnée
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  // Vérifier si une image est sélectionnée
  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  // Étape 2 : Vérifier le type d'image
  Image *image = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  image = dynamic_cast<ImageNG *>(image);
  // Vérifier le type d'image (NB)
  if (image == NULL)
  {
    dialogueErreur("Erreur", "Erreur de type image");
    return;
  }

  // Étape 3 : Demander le nom du fichier
  string nomFichier = dialogueDemandeFichierEnregistrer("Enregistrer l'image NB");

  if (nomFichier == "")
  {
    dialogueErreur("Erreur", "Pas de fichier");
    return;
  }

  // Étape 4 : Demander le format du fichier
  string formatFichier = dialogueDemandeTexte("Format du fichier", "Entrez le format du fichier (JPG, BMP, PNG)");

  if(strcmp(formatFichier.c_str(),"JPG")==0 || strcmp(formatFichier.c_str(),"BMP")==0 || strcmp(formatFichier.c_str(),"PNG")==0)
  {
    // Étape 5 : Enregistrer l'image sur disque
    dynamic_cast<ImageNG *>(image)->exportToFile(nomFichier.c_str(), formatFichier.c_str());

  }else
  {
    dialogueErreur("Erreur", "Format incorrect");
    return;
  }
  
  // Afficher un message de confirmation
  dialogueMessage("Enregistrement d'image", "L'image a été enregistrée avec succès.");

  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageRGB_triggered()
{
  // Etape 11 (TO DO)
 
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  Image *image = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  image = dynamic_cast<ImageRGB *>(image);
  if (image == NULL)
  {
    dialogueErreur("Erreur", "Erreur de type image");
    return;
  }

  string nomFichier = dialogueDemandeFichierEnregistrer("Enregistrer l'image RGB");

  if (nomFichier == "")
  {
    return;
  }

  string formatFichier = dialogueDemandeTexte("Format du fichier", "Entrez le format du fichier (JPG, BMP, PNG)");

  if(strcmp(formatFichier.c_str(),"JPG")==0 || strcmp(formatFichier.c_str(),"BMP")==0 || strcmp(formatFichier.c_str(),"PNG")==0)
  {
    // Étape 5 : Enregistrer l'image sur disque
    dynamic_cast<ImageRGB *>(image)->exportToFile(nomFichier.c_str(), formatFichier.c_str());

  }else
  {
    dialogueErreur("Erreur", "Format incorrect");
    return;
  }

  dialogueMessage("Enregistrement d'image", "L'image a été enregistrée avec succès.");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageB_triggered()
{
  // Etape 11 (TO DO)

   // Étape 1 : Récupérer l'indice de l'image sélectionnée
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  // Vérifier si une image est sélectionnée
  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  // Étape 2 : Vérifier le type d'image
  Image *image = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  // Vérifier le type d'image (B)
  image = dynamic_cast<ImageB *>(image);
  if (image == NULL)
  {
    dialogueErreur("Erreur", "Erreur de type image");
    return;
  }

  // Étape 3 : Demander le nom du fichier
  string nomFichier = dialogueDemandeFichierEnregistrer("Enregistrer l'image B");

  if (nomFichier == "")
  {
    dialogueErreur("Erreur", "Pas de fichier");
    return;
  }
  // Étape 4 : Demander le format du fichier
  string formatFichier = dialogueDemandeTexte("Format du fichier", "Entrez le format du fichier (JPG, BMP, PNG)");

  if(strcmp(formatFichier.c_str(),"JPG")==0 || strcmp(formatFichier.c_str(),"BMP")==0 || strcmp(formatFichier.c_str(),"PNG")==0)
  {
    // Étape 5 : Enregistrer l'image sur disque
    dynamic_cast<ImageB *>(image)->exportToFile(nomFichier.c_str(), formatFichier.c_str());

  }else
  {
    dialogueErreur("Erreur", "Format incorrect");
    return;
  }
  // Afficher un message de confirmation
  dialogueMessage("Enregistrement d'image", "L'image a été enregistrée avec succès.");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_selectionn_e_triggered()
{
  // Etape 11 (TO DO)

  int indice = getIndiceImageSelectionnee();

  if (indice == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée !");
  }
  else
  {
    // Utilisation de l'instance de PhotoShop dans une seule ligne
    PhotoShop& pI = PhotoShop::getInstance();

    // Suppression de l'image par l'indice
    pI.supprimeImageParIndice(indice);

    // Vidange de la table des images
    videTableImages();

    // Obtention de la liste d'images
   ArrayList<Image*>& image = pI.getImages();
    Iterateur<Image*> it(image);

    for(it.reset();!it.end();it++){

        Image* imageAjoutee = (Image*)it;
        
            
            string type = imageAjoutee->getType();
            string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
            string nomImage = imageAjoutee->getNom();
            ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
        
        
    }
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_par_id_triggered()
{
  // Etape 11 (TO DO)

  int identifiant=0;
  
  identifiant=dialogueDemandeInt("Identifiant","Veuillez entré l'identifiant de l'image à supprimer");

if(!identifiant)
{

}else if(identifiant<0)
  {
    dialogueErreur("Erreur","L'identifiant entré en invalide !");
  }
  else
  {

    // Utilisation de l'instance de PhotoShop dans une seule ligne
    PhotoShop& pI = PhotoShop::getInstance();

    // Suppression de l'image par l'indice
    pI.supprimeImageParId(identifiant);


    // Vidange de la table des images
    videTableImages();

    // Obtention de la liste d'images
     // Obtention de la liste d'images
   ArrayList<Image*>& image = pI.getImages();
    Iterateur<Image*> it(image);

    for(it.reset();!it.end();it++){

        Image* imageAjoutee = (Image*)it;
        
            
            string type = imageAjoutee->getType();
            string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
            string nomImage = imageAjoutee->getNom();
            ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
        
        
    }
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_TRUE_pour_ImageB_triggered()
{
  // Etape 12 (TO DO)
  int rouge, vert, bleu;
  dialogueDemandeCouleur("Couleur TRUE", &rouge, &vert, &bleu);
  ImageB::couleurTrue.setRouge(rouge);
  ImageB::couleurTrue.setVert(vert);
  ImageB::couleurTrue.setBleu(bleu);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_FALSE_pour_imageB_triggered()
{
  // Etape 12 (TO DO)
  int rouge, vert, bleu;
  dialogueDemandeCouleur("Couleur FALSE", &rouge, &vert, &bleu);
  ImageB::couleurFalse.setRouge(rouge);
  ImageB::couleurFalse.setVert(vert);
  ImageB::couleurFalse.setBleu(bleu);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImporterCSV_triggered()
{
  // Etape 13 (TO DO)

  string nomFichier = dialogueDemandeFichierOuvrir("Sélectionner un fichier CSV");

  if (nomFichier.empty())
  {
    dialogueErreur("Erreur", "Nom de fichier invalide.");
    return;
  }

  PhotoShop& pI = PhotoShop::getInstance();

  // Appeler la méthode importeImages de l'objet PhotoShop
  int nombreImagesImportees = pI.importeImages(nomFichier);

  // Mettre à jour la table des images
  videTableImages();
  ArrayList<Image*>& image = pI.getImages();
  Iterateur<Image*> it(image);

    for(it.reset();!it.end();it++) 
    {
      Image* imageAjoutee = (Image*)it;
        
      string type = imageAjoutee->getType();
      string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
      string nomImage = imageAjoutee->getNom();
      ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
    }

  // Afficher le nombre d'images importées dans une boîte de dialogue
  string message = "Nombre d'images importées : " + to_string(nombreImagesImportees);
  dialogueMessage("Importation d'images", message.c_str());

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionReset_triggered()
{
  // Etape 14 (TO DO)

  // Appeler la méthode reset de l'objet PhotoShop et mettre numéro courant à 1
  PhotoShop::getInstance().reset();

  // Mettre à jour la table des images
  videTableImages();

  // Mettre couleurTrue à Blanc
  ImageB::couleurTrue.setRouge(255);
  ImageB::couleurTrue.setVert(255);
  ImageB::couleurTrue.setBleu(255);

  // Mettre couleurFalse à Noir
  ImageB::couleurFalse.setRouge(0);
  ImageB::couleurFalse.setVert(0);
  ImageB::couleurFalse.setBleu(0);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions selection sur la table des images ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_tableWidgetImages_itemSelectionChanged()
{
  // Etape 11 (TO DO)

  int indice = getIndiceImageSelectionnee();
  PhotoShop& pI = PhotoShop::getInstance();
  ArrayList<Image*>& images = pI.getImages();

  // Vérifier que l'indice est valide
  if (indice >= 0 && indice < images.getNombreElements())
  {
    Image* imageSelec = images.getElement(indice);

    // Utiliser '== 0' pour comparer les chaînes avec strcmp
    if (strcmp(pI.verifierTypeImage(imageSelec), "NG") == 0)
    {
      ImageNG* ng = dynamic_cast<ImageNG*>(imageSelec);
      // 1. Si le type est "NG", setParametresImageNG
      setParametresImageNG(ng->getMaximum(), ng->getMinimum(), ng->getLuminance(), ng->getContraste());

      // 2. Dessiner l'image NG
      
      setImageNG("selection", ng);
    }
    else if (strcmp(pI.verifierTypeImage(imageSelec), "RGB") == 0)
    {
      setParametresImageNG();
      // 3. Dessiner l'image RGB
      ImageRGB* rgb = dynamic_cast<ImageRGB*>(imageSelec);
      setImageRGB("selection", rgb);
    }
    else if (strcmp(pI.verifierTypeImage(imageSelec), "B") == 0)
    {
      setParametresImageNG();
      // 4. Dessiner l'image B (ajoutez setImageB si nécessaire)
      ImageB* b = dynamic_cast<ImageB*>(imageSelec);
      setImageB("selection", b);
    }
  }
  else
  {
    // Gérer le cas où l'indice n'est pas valide
    //dialogueErreur("Erreur", "Indice d'image sélectionné non valide !");
  }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonModifierNom_clicked()
{
  // Etape 11 (TO DO)

  int indice = getIndiceImageSelectionnee();
  PhotoShop& pI = PhotoShop::getInstance();
  ArrayList<Image*>& images = pI.getImages();

  // Étape 2 : Récupérer le nom modifié par l'utilisateur
  string newNom = getNomImage();

  // Vérifier si une image est sélectionnée
  if (indice == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }
  // Étape 3 : Récupérer l'image correspondante du singleton
  Image *imageSelec = images.getElement(indice);

  // Étape 4 : Appeler la méthode setNom() de l'image
  imageSelec->setNom(newNom.c_str());

  // Étape 5 : Mettre à jour la table des images
  videTableImages();

  
    Iterateur<Image*> it(images);

    for(it.reset();!it.end();it++) 
    {
      Image* imageAjoutee = (Image*)it;
        
      string type = imageAjoutee->getType();
      string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
      string nomImage = imageAjoutee->getNom();
      ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande1_clicked()
{
    // Etape 12 (TO DO)

  // Récupérer l'indice de l'image sélectionnée
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  // Vérifier si une image est sélectionnée
  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  // Récupérer le pointeur vers l'image sélectionnée
  Image *selectedImage = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  // Affecter le pointeur à la variable operande1 de PhotoShop
  PhotoShop::getInstance().operande1 = selectedImage;

  // Appeler la bonne méthode setImageXXX en fonction du type de l'image
  if (dynamic_cast<ImageNG *>(selectedImage) != nullptr)
  {
    setImageNG("operande1", dynamic_cast<ImageNG *>(selectedImage));
  }
  else if (dynamic_cast<ImageRGB *>(selectedImage) != nullptr)
  {
    setImageRGB("operande1", dynamic_cast<ImageRGB *>(selectedImage));
  }
  else if (dynamic_cast<ImageB *>(selectedImage) != nullptr)
  {
    setImageB("operande1", dynamic_cast<ImageB *>(selectedImage));
  }
  else
  {
    dialogueErreur("Erreur", "Type d'image non pris en charge.");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimeOperande1_clicked()
{
    // Etape 12 (TO DO)
   // Remettre la variable operande1 de PhotoShop à NULL
  PhotoShop::getInstance().operande1 = nullptr;

  // Appeler la bonne méthode setImageXXX() pour faire disparaître l'image "operande1"
  setImageNG("operande1", nullptr);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande2_clicked()
{
    // Etape 12 (TO DO)
  // Récupérer l'indice de l'image sélectionnée
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  // Vérifier si une image est sélectionnée
  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  // Récupérer le pointeur vers l'image sélectionnée
  Image *selectedImage = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  // Affecter le pointeur à la variable operande2 de PhotoShop
  PhotoShop::getInstance().operande2 = selectedImage;

  // Appeler la bonne méthode setImageXXX en fonction du type de l'image
  if (dynamic_cast<ImageNG *>(selectedImage) != nullptr)
  {
    setImageNG("operande2", dynamic_cast<ImageNG *>(selectedImage));
  }
  else if (dynamic_cast<ImageRGB *>(selectedImage) != nullptr)
  {
    setImageRGB("operande2", dynamic_cast<ImageRGB *>(selectedImage));
  }
  else if (dynamic_cast<ImageB *>(selectedImage) != nullptr)
  {
    setImageB("operande2", dynamic_cast<ImageB *>(selectedImage));
  }
  else
  {
    dialogueErreur("Erreur", "Type d'image non pris en charge.");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerOperande2_clicked()
{
    // Etape 12 (TO DO)
  // Remettre la variable operande2 de PhotoShop à NULL
  PhotoShop::getInstance().operande2 = nullptr;

  // Appeler la bonne méthode setImageXXX() pour faire disparaître l'image "operande2"
  setImageNG("operande2", nullptr);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonResultat_clicked()
{
    // Etape 12 (TO DO)

  if (PhotoShop::getInstance().resultat != nullptr)
  {
    // Ajouter l'image "résultat" à la bibliothèque (PhotoShop)
    PhotoShop& pI = PhotoShop::getInstance();
    pI.ajouteImage(PhotoShop::getInstance().resultat);

    // Mettre à jour la table des images
    videTableImages();
    ArrayList<Image*>& image = pI.getImages();

    Iterateur<Image*> it(image);

    for(it.reset();!it.end();it++) 
    {
      Image* imageAjoutee = (Image*)it;
        
      string type = imageAjoutee->getType();
      string dimension = to_string(imageAjoutee->getDimension().getLargeur()) + "x" + to_string(imageAjoutee->getDimension().getHauteur());
      string nomImage = imageAjoutee->getNom();
      ajouteTupleTableImages(imageAjoutee->getId(), type, dimension, nomImage);
    }

    // Remettre le pointeur resultat de PhotoShop à NULL

    PhotoShop::getInstance().resultat = nullptr;

    // Effacer l'image "résultat" en appelant la méthode setImageXXX()
    setImageNG("resultat", nullptr); // Remplacez ceci par la méthode appropriée si nécessaire
  }
  else
  {
    dialogueErreur("Erreur", "Pas d'image résultat à ajouter.");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerResultat_clicked()
{
    // Etape 12 (TO DO)

  if (PhotoShop::getInstance().resultat != nullptr)
  {
    // Récupérer le type de l'image résultat
    string typeResultat = PhotoShop::getInstance().resultat->getType();

    // Supprimer l'image résultat par un delete
    delete PhotoShop::getInstance().resultat;

    // Remettre le pointeur resultat de PhotoShop à NULL
    PhotoShop::getInstance().resultat = nullptr;

    // Effacer l'image "résultat" en appelant la méthode setImageXXX()
    if (typeResultat == "NG")
    {
      setImageNG("resultat", nullptr);
      return;
    }
    if (typeResultat == "RGB")
    {
      setImageRGB("resultat", nullptr);
      return;
    }
    if (typeResultat == "B")
    {
      setImageB("resultat", nullptr);
      return;
    }
    else
    {
      dialogueErreur("Erreur", "Type d'image non pris en charge.");
    }
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonTraitement_clicked()
{
    // Etape 12 (TO DO)
  // Récupérer le nom du traitement sélectionné
  string traitement = getTraitementSelectionne();
  int parametre = 0;

  // libérer la mémoire de l'image précédente si elle existe
  if (PhotoShop::getInstance().resultat != nullptr)
  {
    delete PhotoShop::getInstance().resultat;
    PhotoShop::getInstance().resultat = nullptr;
  }
  // Réinitialiser le booléen
  setResultatBoolean(-1);

  if (PhotoShop::getInstance().operande1 != nullptr)
  {
    try
    {
      if (traitement == "Eclaircir (+ val)")
      {
        // Code pour le traitement "Eclaircir (+ val)"
        parametre = dialogueDemandeInt("Eclaircir (+ val)", "Veuillez saisir la valeur à ajouter : ");

        ImageNG *operande1NG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);

        if (operande1NG != nullptr && parametre != 0)
        {
          // Créer une copie de l'image
          PhotoShop::getInstance().resultat = new ImageNG(*operande1NG + parametre);

          // Modifier le nom de la nouvelle image
          string nouveauNom = string(PhotoShop::getInstance().operande1->getNom()) + "+" + to_string(parametre);
          PhotoShop::getInstance().resultat->setNom(nouveauNom.c_str());

          // Mettre à jour l'interface
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }

        return;
      }

      if (traitement == "Eclaircir (++)")
      {
        // Code pour le traitement "Eclaircir (++)"
        ImageNG *imageNG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
        if (imageNG)
        {
          ImageNG result = (*imageNG)++;
          PhotoShop::getInstance().resultat = new ImageNG(result);
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }
        return;
      }

      if (traitement == "Assombrir (- val)")
      {
        // Code pour le traitement "Assombrir (- val)"
        parametre = dialogueDemandeInt("Assombrir (- val)", "Veuillez saisir la valeur à soustraire : ");

        ImageNG *operande1NG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);

        if (operande1NG != nullptr && parametre != 0)
        {
          // Créer une copie de l'image
          PhotoShop::getInstance().resultat = new ImageNG(*operande1NG - parametre);

          // Modifier le nom de la nouvelle image
          string nouveauNom = string(PhotoShop::getInstance().operande1->getNom()) + "-" + to_string(parametre);
          PhotoShop::getInstance().resultat->setNom(nouveauNom.c_str());

          // Mettre à jour l'interface
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }

        return;
      }

      if (traitement == "Assombrir (--)")
      {
        // Code pour le traitement "Assombrir (--)"
        ImageNG *imageNG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
        if (imageNG)
        {
          ImageNG result = (*imageNG)--;
          PhotoShop::getInstance().resultat = new ImageNG(result);
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }
        return;
      }

      /*********************************************************************************************************************/

      if (traitement == "Différence")
      {
        // Code pour le traitement "Différence"
        // Vérifier si operande2 est bien défini
        if (PhotoShop::getInstance().operande2 != nullptr)
        {
          ImageNG *operande1NG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
          ImageNG *operande2NG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2);

          if (operande1NG != nullptr && operande2NG != nullptr)
          {

            ImageNG resultatDifference = *operande1NG - *operande2NG;
            PhotoShop::getInstance().resultat = new ImageNG(resultatDifference);
            setImageNG("resultat", &resultatDifference);
          }
        }
        else
          dialogueErreur("Erreur", "Pas d'opérande 2");

        return;
      }

      if (traitement == "Comparaison (==)")
      {
        if (PhotoShop::getInstance().operande2 != nullptr)
        {

          // Code pour le traitement "Comparaison (==)"
          if (PhotoShop::getInstance().operande1 == PhotoShop::getInstance().operande2)
            setResultatBoolean(1);

          else
            setResultatBoolean(0);
        }
        else
          dialogueErreur("Erreur", "Pas d'opérande 2");

        return;
      }

      if (traitement == "Comparaison (<)")
      {
        // Code pour le traitement "Comparaison (<)"
        // Vérifier si operande2 est bien défini
        if (PhotoShop::getInstance().operande2 != nullptr)
        {
          if (PhotoShop::getInstance().operande1 < PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 1 est plus petit que l'opérande 2");
          }
          else if (PhotoShop::getInstance().operande1 > PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 2 est plus petit que l'opérande 1");
          }
          /*else
          {
            dialogueErreur("Comparaison", "Les deux images sont égales !");
          }*/
        }
        else
          dialogueErreur("Erreur", "Pas d'opérande 2");

        return;
      }
      if (traitement == "Comparaison (>)")
      {
        // Code pour le traitement "Comparaison (>)"

        // Vérifier si operande2 est bien défini
        if (PhotoShop::getInstance().operande2 != nullptr)
        {
          if (PhotoShop::getInstance().operande1 > PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 1 est plus grand que l'opérande 2");
          }
          else if (PhotoShop::getInstance().operande1 < PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 2 est plus grand que l'opérande 1");
          }
          /*else
          {
            dialogueErreur("Comparaison", "Les deux images sont égales !");
          }*/
        }
        else
          dialogueErreur("Erreur", "Pas d'opérande 2");

        return;
      }

      /*********************************************************************************************************************/

      if (traitement == "Seuillage")
      {
        // Code pour le traitement "Seuillage"
        parametre = dialogueDemandeInt("Seuillage", "Veuillez saisir la valeur du seuil : ");
        ImageB resultatSeuillage = Traitements::Seuillage(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1), parametre);

        PhotoShop::getInstance().resultat = new ImageB(resultatSeuillage);
        setImageB("resultat", &resultatSeuillage);
        return;
      }

      if (traitement == "Filtre moyenneur")
      {
        // Code pour le traitement "Filtre moyenneur"
        parametre = dialogueDemandeInt("Filtre moyenneur", "Veuillez saisir la taille du filtre : ");
        ImageNG resultatFiltreMoyenneur = Traitements::FiltreMoyenneur(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1), parametre);

        PhotoShop::getInstance().resultat = new ImageNG(resultatFiltreMoyenneur);
        setImageNG("resultat", &resultatFiltreMoyenneur);
        return;
      }

      if (traitement == "Filtre médian")
      {
        // Code pour le traitement "Filtre médian"
        parametre = dialogueDemandeInt("Filtre médian", "Veuillez saisir la taille du filtre : ");
        ImageNG resultatFiltreMedian = Traitements::FiltreMedian(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1), parametre);

        PhotoShop::getInstance().resultat = new ImageNG(resultatFiltreMedian);
        setImageNG("resultat", &resultatFiltreMedian);
        return;
      }

      if (traitement == "Erosion")
      {
        // Code pour le traitement "Erosion"
        parametre = dialogueDemandeInt("Erosion", "Veuillez saisir la taille du filtre : ");
        ImageNG resultatErosion = Traitements::Erosion(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1), parametre);

        PhotoShop::getInstance().resultat = new ImageNG(resultatErosion);
        setImageNG("resultat", &resultatErosion);
        return;
      }

      if (traitement == "Dilatation")
      {
        // Code pour le traitement "Dilatation"
        parametre = dialogueDemandeInt("Dilatation", "Veuillez saisir la taille du filtre : ");
        ImageNG resultatDilatation = Traitements::Dilatation(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1), parametre);

        PhotoShop::getInstance().resultat = new ImageNG(resultatDilatation);
        setImageNG("resultat", &resultatDilatation);
        return;
      }

      if (traitement == "Négatif")
      {
        // Code pour le traitement "Negatif"
        ImageNG negatif;
        negatif = Traitements::Negatif(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1));

        PhotoShop::getInstance().resultat = new ImageNG(negatif);
        setImageNG("resultat", &negatif);
        return;
      }
    }
    catch (const XYException &exception)
    {
      dialogueErreur("Erreur XYException", QString::fromUtf8(exception.getMessage()).toStdString().c_str());

    }
  }
  else
    dialogueErreur("Erreur", "Pas d'opérande 1");
}



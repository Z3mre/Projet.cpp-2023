.SILENT:
# 	n'afiche plus rien à l'écran, sauf les erreurs
COMP=g++ -I Classes/ -Wall -D DEBUG



# Test11:	Test11.cpp objets/Exception.o objets/RGBException.o objets/XYException.o objets/Image.o objets/ImageNG.o objets/ImageRGB.o objets/ImageB.o objets/Dimension.o objets/Couleur.o objets/MyQT.o objets/Traitements.o objets/ArrayList.o objets/Iterateur.o objets/PhotoShop.o
# 	echo "Creation de Test11"
# 	$(COMP) Test11.cpp -o Test11 objets/Exception.o objets/RGBException.o objets/XYException.o objets/Image.o objets/MyQT.o objets/Traitements.o objets/ImageNG.o objets/ImageRGB.o objets/ImageB.o objets/Dimension.o objets/Couleur.o objets/ArrayList.o objets/Iterateur.o objets/PhotoShop.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

ApplicPhotoShop:	objets/Exception.o objets/RGBException.o objets/XYException.o objets/Image.o objets/ImageRGB.o objets/ImageB.o objets/ImageNG.o   objets/Dimension.o objets/Couleur.o objets/MyQT.o objets/Traitements.o objets/ArrayList.o objets/Iterateur.o objets/PhotoShop.o objets/moc_mainwindowphotoshop.o objets/mainwindowphotoshop.o objets/main.o
	echo Creation de ApplicPhotoShop...
	g++ -o ApplicPhotoShop objets/Exception.o objets/RGBException.o objets/XYException.o objets/Image.o objets/ImageRGB.o objets/ImageB.o objets/ImageNG.o  objets/Dimension.o objets/Couleur.o objets/MyQT.o objets/Traitements.o objets/ArrayList.o objets/Iterateur.o objets/PhotoShop.o objets/moc_mainwindowphotoshop.o objets/mainwindowphotoshop.o objets/main.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread


objets/Exception.o:	Classes/Exception.cpp Classes/Exception.h
	echo "Creation de Exception.o"
	$(COMP) Classes/Exception.cpp -c -o objets/Exception.o

objets/RGBException.o:	Classes/RGBException.cpp Classes/RGBException.h
	echo "Creation de RGBException.o"
	$(COMP) Classes/RGBException.cpp -c -o objets/RGBException.o

objets/XYException.o:	Classes/XYException.cpp Classes/XYException.h
	echo "Creation de XYException.o"
	$(COMP) Classes/XYException.cpp -c -o objets/XYException.o

objets/Image.o:	Classes/Image.cpp Classes/Image.h
	echo "Creation de Image.o"
	$(COMP) Classes/Image.cpp -c -o objets/Image.o

objets/ImageNG.o:	Classes/ImageNG.cpp Classes/ImageNG.h
	echo "Creation de ImageNG.o"
	$(COMP) Classes/ImageNG.cpp -c -o objets/ImageNG.o

objets/ImageRGB.o:	Classes/ImageRGB.cpp Classes/ImageRGB.h
	echo "Creation de ImageRGB.o"
	$(COMP) Classes/ImageRGB.cpp -c -o objets/ImageRGB.o

objets/ImageB.o:	Classes/ImageB.cpp Classes/ImageB.h
	echo "Creation de ImageB.o"
	$(COMP) Classes/ImageB.cpp -c -o objets/ImageB.o

objets/Couleur.o:	Classes/Couleur.cpp Classes/Couleur.h
	echo "Creation de Couleur.o"
	$(COMP) Classes/Couleur.cpp -c -o objets/Couleur.o

objets/Dimension.o:	Classes/Dimension.cpp Classes/Dimension.h
	echo "Creation de Dimension.o"
	$(COMP) Classes/Dimension.cpp -c -o objets/Dimension.o

objets/MyQT.o:	Classes/MyQT.cpp Classes/MyQT.h
	echo "Creation de MyQT.o"
	$(COMP) Classes/MyQT.cpp -c -o objets/MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

objets/Traitements.o:	Classes/Traitements.cpp Classes/Traitements.h
	echo "Creation de Traitements.o"
	$(COMP) Classes/Traitements.cpp -c -o objets/Traitements.o
	
objets/PhotoShop.o:	Classes/PhotoShop.cpp Classes/PhotoShop.h
	echo "Creation de PhotoShop.o"
	$(COMP) Classes/PhotoShop.cpp -c -o objets/PhotoShop.o

objets/ArrayList.o:	Classes/ArrayList.cpp Classes/ArrayList.h
	echo "Creation de ArrayList.o"
	$(COMP) Classes/ArrayList.cpp -c -o objets/ArrayList.o

objets/Iterateur.o:	Classes/Iterateur.cpp Classes/Iterateur.h
	echo "Creation de Iterateur.o"
	$(COMP) Classes/Iterateur.cpp -c -o objets/Iterateur.o


objets/moc_mainwindowphotoshop.o:	InterfaceQt/moc_mainwindowphotoshop.cpp InterfaceQt/mainwindowphotoshop.h
	echo Creation de moc_mainwindowphotoshop.o...
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o objets/moc_mainwindowphotoshop.o InterfaceQt/moc_mainwindowphotoshop.cpp

objets/mainwindowphotoshop.o:	InterfaceQt/mainwindowphotoshop.cpp InterfaceQt/mainwindowphotoshop.h InterfaceQt/ui_mainwindowphotoshop.h 	
	echo Creation de mainwindowphotoshop.o...
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o objets/mainwindowphotoshop.o InterfaceQt/mainwindowphotoshop.cpp

objets/main.o:	InterfaceQt/main.cpp
	echo Creation de main.o...
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o objets/main.o InterfaceQt/main.cpp





clean:
	rm objets/*.o
#make clean

clobber:	clean
	rm -f ApplicPhotoShop
	ipcrm -Q 0x4d2





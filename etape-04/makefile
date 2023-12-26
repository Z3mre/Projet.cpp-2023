.SILENT:
	#n'afiche plus rien à l'écran, sauf les erreurs
COMP=g++ -I Classes/ -Wall -D DEBUG

Test4:	Test4.cpp objets/ImageNG.o objets/Dimension.o objets/MyQT.o
	echo "Creation de Test4"
	$(COMP) Test4.cpp -o Test4 objets/MyQT.o objets/ImageNG.o objets/Dimension.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

objets/ImageNG.o:	Classes/ImageNG.cpp Classes/ImageNG.h
	echo "Creation de ImageNG.o"
	$(COMP) Classes/ImageNG.cpp -c -o objets/ImageNG.o

objets/Dimension.o:	Classes/Dimension.cpp Classes/Dimension.h
	echo "Creation de Dimension.o"
	$(COMP) Classes/Dimension.cpp -c -o objets/Dimension.o

objets/MyQT.o:	Classes/MyQT.cpp Classes/MyQT.h
	echo "Creation de MyQT.o"
	$(COMP) Classes/MyQT.cpp -c -o objets/MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

clean:
	rm objets/*.o
#make clean





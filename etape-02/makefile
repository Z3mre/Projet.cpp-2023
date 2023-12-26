.SILENT:

COMP=g++ -I Classes/ -Wall -D DEBUG


Test2:	Test2.cpp objets/ImageNG.o objets/Dimension.o 
	echo Creation Test2
	$(COMP) -o Test2 Test2.cpp objets/ImageNG.o objets/Dimension.o 

objets/ImageNG.o:	Classes/ImageNG.cpp Classes/ImageNG.h
	echo Creation ImageNG 
	$(COMP) Classes/ImageNG.cpp -c -o objets/ImageNG.o 

objets/Dimension.o:	Classes/Dimension.cpp Classes/Dimension.h
	echo Creation Dimension 
	$(COMP) Classes/Dimension.cpp -c -o objets/Dimension.o 


clean:	
	rm -f objets/*.o core 


clobber:	clean
	rm -f Test2
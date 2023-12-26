.SILENT:

COMP=g++ -I Classes/ -Wall -D DEBUG


Test1:	Test1.cpp objets/ImageNG.o
	echo Creation Test1
	$(COMP) -o Test1 Test1.cpp objets/ImageNG.o 

objets/ImageNG.o:	Classes/ImageNG.cpp Classes/ImageNG.h
	echo Creation ImageNG 
	$(COMP) Classes/ImageNG.cpp -c -o objets/ImageNG.o 


clean:	
	rm -f objets/*.o core 


clobber:	clean
	rm -f Test1
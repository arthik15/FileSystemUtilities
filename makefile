objfiles = mytail	myls	mystat	mytree
cpp = gcc

all: mytail	myls	mystat	mytree

myls:
	$(cpp) myls.c -o myls

mystat:
	$(cpp) mystat.c -o mystat

mytail:
	$(cpp) mytail.c -o mytail

mytree:
	$(cpp) mytree.c -o mytree
	
clean:
	rm $(objfiles)


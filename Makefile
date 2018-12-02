all:
	gcc GrahamScan/graham_scan.c 
	gcc GrahamScan/graham_scan_main.c 
	gcc graham_scan.o graham_scan_main.o -o gs
	rm -f graham_scan.o graham_scan_main.o

debug:
	gcc -g GrahamScan/graham_scan.c 
	gcc -g GrahamScan/graham_scan_main.c 
	gcc -g graham_scan.o graham_scan_main.o -o gs
	rm -f graham_scan.o graham_scan_main.o

test:
	gcc -c GrahamScan/graham_scan.c
	gcc -c tests/graham_scan_tests.c
	gcc graham_scan_tests.o graham_scan.o -o gstest -lcriterion --coverage
	rm -f graham_scan.o
	rm -f graham_scan_tests.o

jtest:
	gcc tests/graham_scan_tests.c --coverage -o gstest -lcriterion 

clean:
	rm -f gs
	rm -f gstest
	

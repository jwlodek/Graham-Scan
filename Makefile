gs:
	gcc -c GrahamScan/graham_scan_main.c
	gcc -c GrahamScan/graham_scan.c
	gcc graham_scan_main.o graham_scan.o -o gs
	rm -f graham_scan.o graham_scan_main.o

debug:
	gcc -g -c GrahamScan/graham_scan_main.c
	gcc -g -c GrahamScan/graham_scan.c
	gcc -g graham_scan_main.o graham_scan.o -o gs
	rm -f graham_scan.o graham_scan_main.o

test:
	gcc -c GrahamScan/graham_scan.c
	gcc -c tests/graham_scan_tests.c
	gcc graham_scan_tests.o graham_scan.o -o gstest -lcriterion --coverage
	rm -f graham_scan.o
	rm -f graham_scan_tests.o

clean:
	rm -f gs
	rm -f gstest
	

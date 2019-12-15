#Name - Shubhkarman Sohi
#Student Number - 11219687
#NISD - sss669

CFLAGS = -Wall -Wextra -lnetpbm

.PHONY: cgr clean

CGR_OBJ = cgr.o cgr_plot.o cgr_aux.o 

cgr: $(CGR_OBJ)
	gcc -lnetpbm $(CGR_OBJ) -o cgr

cgr.o: cgr.c cgr.h cgr_plot.h cgr_aux.h
	gcc $(CFLAGS) -c cgr.c

cgr_plot.o: cgr_plot.c cgr_plot.h 
	gcc $(CFLAGS) -c cgr_plot.c

cgr_aux.o: cgr_aux.c cgr_aux.h
	gcc $(CFLAGS) -c cgr_aux.c
	
clean:
	rm -f cgr.o cgr_aux.o cgr_plot.o
	rm -f cgr

// Name - Shubhkarman Sohi
// Student Number - 11219687
// NISD - sss669

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <netpbm/pbm.h>

#include "cgr_aux.h"
#include "cgr_plot.h"
#include "cgr.h"
int Scale;

void initialize_plot( void ) {
    Plot =pbm_allocarray(Scale, Scale);
}

int main(int argc, char *argv[]){

    pm_init( "cgr", 0 );
    //Scale if to be given as argument while run
    //argv[1] is a pointer to char, atoi changes it to int
    Scale = atoi(argv[1]);
    //args should be exactly 2, the function call and the Scale input
    //if not print error message
    if (argc != 2){
        fputs("Correct input not provided.\n", stderr);
        exit(1);
    }
    //if input Scale is less than MIN_SCALE, error message
    if (Scale < MIN_SCALE ){
        fputs("Scale too small\n", stderr);
        exit(1);
    }
    //is Scale is greater thatn MAX_SCALE, error message
    if (Scale > MAX_SCALE ){
        fputs("Scale too large\n", stderr);
        exit(1);
    }
    //if Scale is not a power of 2, error message
    if (!(is_power_of_2(Scale))){
        fputs("Scale must be a power of 2\n", stderr);
        exit(1);
    }

    initialize_plot();

    //starting point to be the centre is the graph
    point_t on_point = {{1,2},{1,2}};

    char c;
    //get charter one at a time from stdin until EOF
    while((c = getchar()) != EOF){
        //input can be from multiple lines so if '\n'(newline) occurs
        //change it to '\0'(null char)
        if (c == '\n')
            c = '\0';
        //pass the input character to cgr function along with the initial
        //point which will get updated once the function has been run.
        on_point = cgr(on_point, c);
    }
    //print the plot with the boundaries and values from plot
    output_plot();
    // free(Plot);
    //free the allocated memory for Plot
    pbm_freearray(Plot, Scale);
    return (0);
}

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
#include "cgr.h"
#include "cgr_plot.h"

//global variable Plot as  pointer pointer to bit
bit** Plot;

/*
 * function to print the plot with values from Plot[i][j]
 * with bottom left most point to be (0,0) top left most
 * top left point(0,1), top right point(1,1) and bottom
 * left to be (1,0) as on an ideal graph.
 */
void output_plot( void ) {

    pbm_writepbminit(stdout, Scale ,Scale, false);
    for (int i =Scale-1; i >= 0; i--) {

        pbm_writepbmrow(stdout, Plot[i] , Scale, false);

    }
}

/*
 * function to compute the points at which the
 * value in Plot to be changed to *
 * takes argument one point x or y and returns an unsigned int
 * the return value has to be in between 0 and Scale
 */
unsigned scale_coord ( coord_t coord ){
    //if Scale < the denominator, then Scale/Denominator
    //return 0 because the return value becomes a float.
    //thus is computed the following way
    if ((uint64_t )Scale < coord.q){
        //if the above is true the opposite of Scale/Denominator
        //is stored in a temp
        uint64_t temp = coord.q/Scale;
        //and the numerator is then divided by temp
        //which gives the value same as Scale*N/D
        uint64_t temp2 = coord.n/temp;
        return temp2;
    }
    else{
        //if Scale > D (Scale/D)*N is returned
        return ((Scale/coord.q))*coord.n;
    }
}

/*
 * function to change the value Plot to *
 * at the points computed by scale_coord
 */
void plot_point( point_t point ){
    //x coordinate
    uint64_t colm = scale_coord(point.x);
    //y coordinate
    uint64_t row = scale_coord(point.y);
    //change in Plot from PBM_WHITE to PBM_BLACK at the above values
    Plot[row][colm] = PBM_BLACK;
}

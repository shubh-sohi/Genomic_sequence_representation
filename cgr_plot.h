// Name - Shubhkarman Sohi
// Student Number - 11219687
// NISD - sss669

#ifndef CGR_PLOT_H
#define CGR_PLOT_H

#include "cgr_aux.h"

//global variable Plot as  pointer pointer to char
extern bit** Plot;

/*
 * function to print the plot with values from Plot[i][j]
 * with bottom left most point to be (0,0) top left most
 * top left point(0,1), top right point(1,1) and bottom
 * left to be (1,0) as on an ideal graph.
 */
void output_plot(void);

/*
 * function to compute the points at which the
 * value in Plot to be changed to *
 * takes argument one point x or y and returns an unsigned int
 * the return value has to be in between 0 and Scale
 */
unsigned scale_coord(coord_t);

/*
 * function to change the value Plot to *
 * at the points computed by scale_coord
 */
void plot_point(point_t);

#endif

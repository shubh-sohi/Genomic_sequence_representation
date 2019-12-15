// Name - Shubhkarman Sohi
// Student Number - 11219687
// NISD - sss669

#ifndef CGR_AUX_H
#define CGR_AUX_H



//data type to keep the numerator and denominator each
//of type uint64_t to store a rather large value for
// a point of any coordinate(x,y)
//n = numerator
//q = denominator
typedef struct {
    uint64_t n;
    uint64_t q;
}coord_t;

//data type to store the coordinates(x,y) of a
//point further represented as numerator and
// denominator in coord_t
typedef struct {
    coord_t x;
    coord_t y;
}point_t;

//data type to store the the coordinated of
//valid input strings namely {A,G,C,T}
//thus of type point_t
typedef struct {
    point_t A;
    point_t C;
    point_t G;
    point_t T;
}ntide_t;

#define NUM_NTIDES 4

/*
 * function to check if the given argument is
 * a power of 2.
 * returns true if it is and false otherwise
 * code used from :
 * https://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
 * using the shift right method
 */
_Bool is_power_of_2(unsigned);

/*
 * function to reduce the computed point
 * by division with 2 if the denominator of
 * the point become larger that 1<<63
 */
coord_t reduce_coord(coord_t);

/*
 * function simply passes the x and y coordinates
 * of a point to reduce_cord and reduce_cord does rest of
 * the work
 */
point_t reduce_point(point_t);

/*
 * function to determine the mid point from the current point
 * to the char point. Char point can only (0,0),(1,0),(0,1) or (1,1)
 * because the char points can only be {A,G,C,T}
 * function return a point that is the midpoint
 * takes argument as a pnt1 that is possible previous point
 * and pnt2 is always coordinates of {A,G,C,T}
 * formula to compute is (pnt1.(x or y) + pnt2.(x or y))\2
 */
point_t determine_midpoint(point_t, point_t);

/*
 *function takes 2 arguments, one point and one character and computes the midpoint between the
 * point and the points of the corresponding character provided it is {A,G,C,T}
 *after computing the midpoint using the determine_midpoint function,
 * it passes the returned value to plot_point that changers the corresponding value
 * in plot from ' ' to *.
 * finally the computed new point is returned
 */
point_t cgr(point_t, char);

#endif

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

#include "cgr_plot.h"
#include "cgr_aux.h"
/*
 * function to check if the given argument is
 * a power of 2.
 * returns true if it is and false otherwise
 * code used from :
 * https://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
 * using the shift right method
 */
_Bool is_power_of_2( unsigned val ){
    {
        while (((val & 1) == 0) && val > 1) /* While x is even and > 1 */
            val >>= 1;
        return (val == 1);
    }
}
/*
 * function simply passes the x and y coordinates
 * of a point to reduce_cord and reduce_cord does rest of
 * the work
 */
point_t reduce_point( point_t old_point ){
    //passing the x coordinate
    old_point.x = reduce_coord(old_point.x);
    //passing the y coordinate
    old_point.y = reduce_coord(old_point.y);
    //returning the point with the changes coordinates if any
    return old_point;
}

/*
 * function to reduce the computed point
 * by division with 2 if the denominator of
 * the point become larger that 1<<63
 */
coord_t reduce_coord( coord_t old_coord){
    //1<<63 same as 2^63 and
    if (old_coord.q >= (uint64_t)1<<63){    //type casted to be (uint64_t)to avoid warnings
        //division of denominator by 2
        old_coord.q = (uint64_t )old_coord.q>>1;
        //division of the numerator by 2
        old_coord.n = (uint64_t )old_coord.n>>1;
        return old_coord;
    }
    else{
        return old_coord;
    }
}

/*
 * function to determine the mid point from the current point
 * to the char point. Char point can only (0,0),(1,0),(0,1) or (1,1)
 * because the char points can only be {A,G,C,T}
 * function return a point that is the midpoint
 * takes argument as a pnt1 that is possible previous point
 * and pnt2 is always coordinates of {A,G,C,T}
 * formula to compute is (pnt1.(x or y) + pnt2.(x or y))\2
 */
point_t determine_midpoint(point_t pnt1, point_t pnt2) {
    //if pnt2 x N is 0 i.e x is 0
    if (pnt2.x.n == 0) {
        //in addition N will be the same as ptn1 N
        uint64_t xn = pnt1.x.n;
        //D is divided by 2 as formulated
        uint64_t xq = pnt1.x.q<<1;
        //put the N and D in a temp coordinate
        coord_t temp01 = {xn, xq};
        //if pnt2 y N is 0 i.e y is 0
        if (pnt2.y.n == 0) {
            //in addition N will be the same as ptn1 N
            uint64_t yn = pnt1.y.n;
            //D is divided by 2 as formulated
            uint64_t yq = pnt1.y.q<<1;
            //put the N and D in a temp coordinate
            coord_t temp02 = {yn, yq};
            //using both the temp coordinates make a point
            point_t midpoint = {temp01, temp02};
            return midpoint;
        }
        else {
            //think of this as x/y+1. it always sums up to be (x+y)/y
            uint64_t yn = (pnt1.y.n + pnt1.y.q);
            //D is divided by 2 as formulated
            uint64_t yq = pnt1.y.q<<1;
            //put the N and D in a temp coordinate
            coord_t temp02 = {yn, yq};
            //using both the temp coordinates make a point
            point_t midpoint = {temp01, temp02};
            return midpoint;
        }
    }
    else  {
        //think of this as x/y+1. it always sums up to be (x+y)/y
        uint64_t xn = (pnt1.x.n + pnt1.x.q);
        //D is divided by 2 as formulated
        uint64_t xq = pnt1.x.q<<1;
        //put the N and D in a temp coordinate
        coord_t temp01 = {xn, xq};
        if (pnt2.y.n == 0) {
            //in addition N will be the same as ptn1 N
            uint64_t yn = pnt1.y.n;
            //D is divided by 2 as formulated
            uint64_t yq = pnt1.y.q<<1;
            //put the N and D in a temp coordinate
            coord_t temp02 = {yn, yq};
            //using both the temp coordinates make a point
            point_t midpoint = {temp01, temp02};
            return midpoint;
        }
        else {
            //think of this as x/y+1. it always sums up to be (x+y)/y
            uint64_t yn = (pnt1.y.n + pnt1.y.q);
            //D is divided by 2 as formulated
            uint64_t yq = pnt1.y.q<<1;
            //put the N and D in a temp coordinate
            coord_t temp02 = {yn, yq};
            //using both the temp coordinates make a point
            point_t midpoint = {temp01, temp02};
            return midpoint;
        }
    }
}

/*
 *function takes 2 arguments, one point and one character and computes the midpoint between the
 * point and the points of the corresponding character provided it is {A,G,C,T}
 *after computing the midpoint using the determine_midpoint function,
 * it passes the returned value to plot_point that changers the corresponding value
 * in plot from ' ' to *.
 * finally the computed new point is returned
 */
point_t cgr( point_t in_point, char in_char){
    //converts the char (in_point) to upper case
    in_char = toupper(in_char);
    //if the point while compilation becomes greater than max value if uint64_t
    //it is reduced using reduce_point() function
    point_t again_in_point = reduce_point(in_point);
    //coordinates values for {A,C,G,T}
    ntide_t corres_point = {{{0,1},{0,1}},
                            {{0,1},{1,1}},
                            {{1,1},{1,1}},
                            {{1,1},{0,1}}};
    //if input char matched A
    if (in_char == 'A'){
        //midpoint determination
        point_t newPoint = determine_midpoint(again_in_point, corres_point.A);
        //plotting of the mid point
        plot_point(newPoint);
        //return the new point returned be determine_midpoint
        return newPoint;
    }
    //if input char matched C
    if (in_char == 'C'){
        //midpoint determination
        point_t newPoint = determine_midpoint(again_in_point, corres_point.C);
        //plotting of the mid point
        plot_point(newPoint);
        //return the new point returned be determine_midpoint
        return newPoint;
    }
    //if input char matched G
    if (in_char == 'G'){
        //midpoint determination
        point_t newPoint = determine_midpoint(again_in_point, corres_point.G);
        //plotting of the mid point
        plot_point(newPoint);
        //return the new point returned be determine_midpoint
        return newPoint;
    }
    //if input char matched T
    if (in_char == 'T'){
        //midpoint determination
        point_t newPoint = determine_midpoint(again_in_point, corres_point.T);
        //plotting of the mid point
        plot_point(newPoint);
        //return the new point returned be determine_midpoint
        return newPoint;
    }
    //if the input char does not match {A,C,G,T}
    //the initial point is returned
    else{
        return in_point;
    }

}

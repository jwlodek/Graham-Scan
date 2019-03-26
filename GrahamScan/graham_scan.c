/**
 * This file contains functions for solving the convex hull problem with the graham scan approach
 * 
 * Author: Jakub Wlodek
 * Created on: Nov 30, 2018
 */


// standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// custom header include
#include "graham_scan.h"


/**
 * Simple function for printing all points in a set
 * 
 * @params: ps -> point set to print
 * @return: void
 */
void print_points(PointSet* ps){
    int i;
    printf("%d\n", ps->num_points);
    for(i = 0; i < ps->num_points; i++){
        printf("[%d,%d] -> %lf\n", (ps->points+i)->xCoord, (ps->points+i)->yCoord, (ps->points+i)->angle);
    }
}


/**
 * Simple function for printing points in a stack
 *
 * @params: p -> array of points in stack
 * @params: stack_size -> current size of the stack
 * @return: void
 */
void print_stack(Point* p, int stack_size){
    int i;
    for(i = 0; i < stack_size; i++){
        printf("[%d,%d] -> %lf\n", (p+i)->xCoord, (p+i)->yCoord, (p+i)->angle);
    }
}


/**
 * Simple function for printing all points in a set to an output file
 * 
 * @params: ps -> point set to print
 * @return: void
 */
void print_points_to_file(PointSet* ps, char* file_name){
    FILE* fp = fopen(file_name, "w");
    int i;
    fprintf(fp, "%d\n", ps->num_points);
    for(i = 0; i < ps->num_points; i++){
        fprintf(fp, "[%d,%d]\n", (ps->points+i)->xCoord, (ps->points+i)->yCoord);
    }
    fclose(fp);
}


/**
 * Function that parses a user input file and populates a point set with the contents
 * File format:
 * 
 * n
 * [p1x,p1y]
 * [p2x,p2y]
 * 
 * where n is the number of points, and pNx and pNy are the coordinates of points in the set
 * 
 * @params: filename    -> name of input file
 * @return: ps          -> point set created from points taken from file
 */
PointSet* parse_input_file(char* file_name){
    //printf("Parsing input file\n");
    FILE* fp = fopen(file_name, "r");
    if(fp == NULL){
        printf("ERROR Opening file\n");
        return NULL;
    }
    PointSet* ps = (PointSet*) calloc(1, sizeof(PointSet));
    char* line = NULL;
    size_t len = 0;
    size_t read;
    read = getline(&line, &len, fp);
    int n = atoi(line);
    ps->num_points = n;
    ps->points = malloc(ps->num_points*sizeof(Point));
    int counter = 0;
    while(read = getline(&line, &len, fp) != -1){
        Point* p = ps->points+counter;
        char* token = strtok(line, ",");
        token = token+1;
        char* second_token  = strtok(NULL, "]");
        p->xCoord = atoi(token);
        p->yCoord = atoi(second_token);
        counter++;
    }
    //print_points(ps);
    fclose(fp);
    if(line) free(line);
    return ps;
}


/**
 * Function that decides if three points result in a right or left turn 
 * Uses Slopes computed using the three points to do this
 * 
 * @params: p1 - p3     -> The three points
 * @return GS_Turn      -> enum type for turn inline, left, or right
 */
GS_Turn find_turn_type(Point* p1, Point* p2, Point* p3){
    //printf("checking points [%d,%d] [%d,%d] [%d,%d]\n", p1->xCoord, p1->yCoord, p2->xCoord, p2->yCoord, p3->xCoord, p3->yCoord);
    int value = (p2->yCoord - p1->yCoord)*(p3->xCoord - p2->xCoord) -
                (p2->xCoord - p1->xCoord)*(p3->yCoord - p2->yCoord);
    if(value == 0) return GS_Inline;
    return (value > 0) ? GS_RightTurn : GS_LeftTurn;
}


/**
 * Function that finds the minimum point by y-coordinate
 * If there is a tie, it finds the min x-coordinate as well
 * 
 * @params: ps -> input point set
 * @return: lowest point by y-coord
 */
Point* find_lowest_point(PointSet* ps){
    Point* p = ps->points;
    int i;
    for(i = 0; i < ps->num_points; i++){
        if((ps->points+i)->yCoord < p->yCoord){
            p = ps->points+i;
        }
        else if((ps->points+i)->yCoord == p->yCoord){
            if((ps->points+i)->xCoord < p->xCoord){
                p = ps->points+i;
            }
        }
    }
    return p;
}


/**
 * Merge Sort implementation for sorting points by their angles
 * 
 * @params: points  -> point array to sort by angle
 * @params: left    -> starting point for left subArray
 * @params: right   -> starting point for right subArray
 * @return: void
 */
void sort_by_angle(Point* points, int left, int right){
    if (left < right) { 
        int center = left+((right-left)/2); 
        sort_by_angle(points, left, center); 
        sort_by_angle(points, center+1, right); 
  
        merge_halves(points, left, center, right); 
    } 
}


/**
 * Function for merging the two sub arrays in the point set. 
 * Used by merge sort
 * 
 * @params: points  -> array of points in the point set
 * @params: left    -> Left start point of the sub array
 * @params: center  -> Center start point of the sub array
 * @params: right   -> Right start point of the sub array
 * @return: void
 */
void merge_halves(Point* points, int left, int center, int right){
    int i, j, k;
    int n1 = center - left + 1;
    int n2 = right - center;

    Point tempP1[n1];
    Point tempP2[n2];
    for(i = 0; i< n1; i++){
        tempP1[i] = points[left + i];
    }
    for(j = 0; j< n2; j++){
        tempP2[j] = points[center + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while(i < n1 && j< n2){
        if(tempP1[i].angle <= tempP2[j].angle){
            points[k] = tempP1[i];
            i++;
        }
        else{
            points[k] = tempP2[j];
            j++;
        }
        k++;
    }

    while (i < n1) { 
        points[k] = tempP1[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) { 
        points[k] = tempP2[j]; 
        j++; 
        k++; 
    }
}


/**
 * Function for finding the convex hull of a set of points using the graham scan approach
 * First, we find the lowest point.
 * Then we sort the points based on the angles using a separate function (mergesort).
 * Next we use a stack to go through all of the points following the Graham scan approach.
 * Starting with the first set of 3 points, we decide if they make a right or a left turn.
 * If they make a right turn, then the center point cannot be in the convex hull. As a result, we
 * shift the stack back one point, so now the first and third points and the previous first point make
 * up the new 3-point set. We again compute if it is a right or left turn, and repeat until we find a 
 * left or inline turn. If a left turn is found, the last point is added to the top of the stack, and the
 * next point in order becomes the new third point. We continue this until all points have been visited at
 * least one time.
 * 
 * @params: ps          -> original point set read from a file
 * @return: convexHull  -> Point set created by copying the final stack (Convex hull)
 */
PointSet* compute_convex_hull(PointSet* ps){
    //printf("Computing Convex hull using Graham scan...\n");
    //printf("Finding the lowest point by y-coordinate...\n");
    Point* p = find_lowest_point(ps);
    //printf("Lowest point found.\n");
    //printf("Computing angles with lowest point...\n");
    compute_angles(ps, p);
    //printf("Angles computed. Sorting using merge-sort\n");
    sort_by_angle(ps->points, 0, ps->num_points - 1);
    //printf("Finished sorting points by angle\n");
    //print_points(ps);
    PointSet* stackSet = (PointSet*) calloc(1, sizeof(PointSet));
    stackSet->num_points = ps->num_points;
    stackSet->points = malloc(stackSet->num_points * sizeof(Point));
    Point* stack = stackSet->points;
    int stack_top = 2;
    stack[0] = ps->points[0];
    stack[1] = ps->points[1];
    stack[2] = ps->points[2];
    //printf("Initialized the stack.\n");
    int i;
    for(i = 3; i < ps->num_points; i++){
        while(find_turn_type(stack+stack_top-1, stack+stack_top, ps->points+i) == GS_RightTurn){
            //printf("found right turn\n");
            stack_top = stack_top - 1;
        }
        stack_top++;
        stack[stack_top] = ps->points[i];
    }
    PointSet* convexHull = (PointSet*) calloc(1, sizeof(PointSet));
    convexHull->num_points = stack_top+1;
    convexHull->points = malloc(convexHull->num_points*sizeof(Point));
    int j;
    for(j = 0; j < convexHull->num_points; j++){
        convexHull->points[j] = stack[j];
    }
    free(stack);
    free(stackSet);
    printf("Finished computing Convex Hull using Graham Scan.\n");
    return convexHull;
}


/**
 * Function intended to remove 3-point colinear degenreacy from the convex hull.
 * 
 * Because the starting point is the lowest point in the set, we know that it cannto be the 
 * middle point in three colinear points, so we need not account for that
 * 
 * @params: convexHull -> pointset corresponding to the convex hull in clockwise order
 * @return: no_degenracy_hull -> convex hull with colinear points removed
 */
PointSet* remove_degeneracy(PointSet* convexHull){
    //printf("Handling degeneracies...\n");
    PointSet* no_degeneracy_hull = (PointSet*) malloc(sizeof(PointSet));
    int numPoints = 1;
    Point* tempPoints = (Point*) malloc(convexHull->num_points * sizeof(Point));
    int i = 0;
    int j = 1;
    int k = 2;
    tempPoints[0] = convexHull->points[0];
    while(k< convexHull->num_points){
        GS_Turn turnType = find_turn_type(convexHull->points+(i), convexHull->points+j, convexHull->points+k);
        if(turnType != GS_Inline){
            //printf("found non-colinear points\n");
            tempPoints[numPoints] = convexHull->points[j];
            numPoints++;
            i = j;
            j = k;
            k++;
            if(k == convexHull->num_points){
                GS_Turn wrap_around = find_turn_type(convexHull->points+i, convexHull->points+j, convexHull->points);
                if(wrap_around != GS_Inline){
                    tempPoints[numPoints] = convexHull->points[j];
                    numPoints++;
                }
            }
        }
        else{
            //printf("Found Colinear points\n");
            j = k;
            k++;
            if(k == convexHull->num_points){
                //case if CH wraps around and is  the three points are colinear at the end
                GS_Turn wrap_around = find_turn_type(convexHull->points+i, convexHull->points+j, convexHull->points);
                if(wrap_around != GS_Inline){
                    tempPoints[numPoints] = convexHull->points[j];
                    numPoints++;
                }
            }
        }
    }
    int c;
    no_degeneracy_hull->num_points = numPoints;
    no_degeneracy_hull->points = (Point*) malloc(numPoints*sizeof(Point));
    for(c = 0; c< numPoints; c++){
        no_degeneracy_hull->points[c] = tempPoints[c];
    }
    free(tempPoints);
    return no_degeneracy_hull;
}


/**
 * Function that computes the angle between the starting point and every other point
 * 
 * @params: ps -> set of points
 * @params: lowest -> lowest y-coord
 * @return: void
 */
void compute_angles(PointSet* ps, Point* lowest){
    int i;
    for(i = 0; i< ps->num_points; i++){
        Point* p = ps->points+i;
        if(p->xCoord == lowest->xCoord && p->yCoord == lowest->yCoord){
            p->angle = -1;
        }
        else{
            //printf("opp %f, hyp %f\n", (double)(p->xCoord-lowest->xCoord), distance_between(lowest, p));
            p->angle = acos((p->xCoord-lowest->xCoord)/distance_between(lowest, p));
        }
        //printf("%f\n", p->angle);
    }
}


/**
 * Distance formula for finding length of hypotenuse
 * 
 * @params: p1  -> starting point
 * @params: p2  -> ending point
 * @return distance between them
 */
double distance_between(Point* p1, Point*p2){
    double nx = p1->xCoord - p2->xCoord;
    double ny = p1->yCoord - p2->yCoord;
    double h2 = pow(nx,2)+pow(ny,2);
    return pow(h2, 0.5);
}


/**
 * Function that compares the contents of two point sets
 * Used primarily for testing
 * 
 * @params: ps1 -> first point set
 * @params: ps2 -> second point set
 * @return: -1 if not the same, 0 if the same
 */
int compare_point_sets(PointSet* ps1, PointSet* ps2){
    //print_points(ps1);
    //print_points(ps2);
    if(ps1->num_points != ps2->num_points) return -1;
    int i;
    for(i = 0; i< ps1->num_points; i++){
        if((ps1->points+i)->xCoord != (ps2->points+i)->xCoord) return -1;
        if((ps1->points+i)->yCoord != (ps2->points+i)->yCoord) return -1;
    }
    return 0;
}

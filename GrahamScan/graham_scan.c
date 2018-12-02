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
        printf("[%d,%d]\n", (ps->points+i)->xCoord, (ps->points+i)->yCoord);
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
        if((ps->points+i)->yCoord <= p->yCoord){
            if((ps->points+i)->xCoord < p->xCoord){
                p = ps->points+i;
            }
        }
    }
    return p;
}


// TODO
PointSet* sort_by_angle(PointSet* ps){
    printf("UNIMPLEMENTED\n");
}


//TODO
PointSet* compute_convex_hull(PointSet* ps){
    printf("UNIMPLEMENTED\n");
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
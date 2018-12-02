/**
 * Header file for Graham scan algorithm program
 * 
 * Author: Jakub Wlodek
 * Created on: Nov 30, 2018
 */


// include guard
#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H


/* Structures used to represent a point and a set of points */
typedef struct Point {
    int xCoord;
    int yCoord;
} Point;

typedef struct PointSet {
    int num_points;
    Point* points;
} PointSet;

/* function definitions */
PointSet* parse_input_file(char* file_name);

void print_points(PointSet* ps);

void print_points_to_file(PointSet* ps, char* file_name);

int compare_point_sets(PointSet* ps1, PointSet* ps2);


#endif
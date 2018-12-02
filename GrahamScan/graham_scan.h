


#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H


typedef struct Point {
    int xCoord;
    int yCoord;
} Point;

typedef struct PointSet {
    int num_points;
    Point* points;
} PointSet;

PointSet* parse_input_file(char* file_name);

void print_points(PointSet* ps);

void print_points_to_file(PointSet* ps, char* file_name);

int compare_point_sets(PointSet* ps1, PointSet* ps2);


#endif
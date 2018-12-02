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
    printf("Parsing input file\n");
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
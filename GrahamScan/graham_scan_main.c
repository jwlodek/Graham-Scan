/**
 * Main runner file for graham scan
 * 
 * Author: Jakub Wlodek
 * Created on: Dec 2, 2018
 */


#include <stdio.h>
#include <stdlib.h>

#include "graham_scan.h"


/* Main runner function */
int main(int argc, char** argv){
    printf("Starting graham scan algorithm\n");
    if(argc != 3){
        printf("Invalid Input, please only pass path to input file and path to output file.\n");
        return -1;
    }
    char* input_file_name = argv[1];
    char* output_file_name = argv[2];
    PointSet* inputPS = parse_input_file(input_file_name);
    if(inputPS == NULL){
        return -1;
    }
    print_points(inputPS);
}
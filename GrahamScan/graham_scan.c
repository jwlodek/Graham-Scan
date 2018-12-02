
#include <stdio.h>
#include <stdlib.h>


#include "graham_scan.h"

int main(int argc, char** argv){

}

void print_points(PointSet* ps){
    int i;
    printf("%d\n", ps->num_points);
    for(i = 0; i < ps->num_points; i++){
        printf("[%d,%d]\n", (ps->points+i)->xCoord, (ps->points+i)->yCoord);
    }
}

void print_points_to_file(PointSet* ps, char* file_name){
    FILE* fp = fopen(file_name, "w");
    int i;
    fprintf(fp, "%d\n", ps->num_points);
    for(i = 0; i < ps->num_points; i++){
        fprintf(fp, "[%d,%d]\n", (ps->points+i)->xCoord, (ps->points+i)->yCoord);
    }
    fclose(fp);
}

PointSet* parse_input_file(char* file_name){

}
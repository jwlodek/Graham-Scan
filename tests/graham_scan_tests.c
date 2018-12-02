#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <stdio.h>

#include "../GrahamScan/graham_scan.h"

PointSet* ps1;
PointSet* ps2;
PointSet* ps3;

void setup_parse(void){
    printf("Creating test point set\n");
    ps1 = (PointSet*) calloc(1, sizeof(PointSet));
    ps1->num_points = 3;
    ps1->points = malloc(ps1->num_points*sizeof(Point));
    ps1->points->xCoord = 5;
    ps1->points->yCoord = 26;
    (ps1->points+1)->xCoord = 76;
    (ps1->points+1)->yCoord = -23;
    (ps1->points+2)->xCoord = 20;
    (ps1->points+2)->yCoord = 221;
}

void teardown_parse(void){
    printf("Freeing test point set\n");
    free(ps1->points);
    free(ps1);
}

Test(asserts, parse_input_test, .init = setup_parse, .fini = teardown_parse){
    PointSet* ps = parse_input_file("../grahaminput1.txt");
    int eq = compare_point_sets(ps, ps1);
    cr_assert(eq == 0, "Parsed point set not equal");
}
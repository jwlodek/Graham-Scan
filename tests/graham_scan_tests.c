/**
 * File containing tests for graham scan
 *  
 * run tests with:
 * make test
 * ./gstest
 * 
 * Author: Jakub Wlodek
 * Created on: Dec 2, 2018
 */


#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <stdio.h>

#include "../GrahamScan/graham_scan.h"

PointSet* ps1;
PointSet* ps2;
PointSet* ps3;

/* Setup and teardown functions */
void setup_parse(void){
    //printf("Creating test point set\n");
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

void setup_general(void){
    //printf("Creating test point set\n");
    ps1 = parse_input_file("./inputs/graham_input2.txt");
}

void teardown_general(void){
    //printf("Freeing test point set\n");
    free(ps1->points);
    free(ps1);
}

/* ------------------------Unit Tests---------------------------------*/

/* File parsing test */
Test(asserts, parse_input_test, .init = setup_parse, .fini = teardown_general){
    PointSet* ps = parse_input_file("./inputs/graham_input1.txt");
    int eq = compare_point_sets(ps, ps1);
    cr_assert(eq == 0, "Parsed point set not equal");
}


/* Tests for turn type */
Test(asserts, turn_test_1, .init = setup_general, .fini = teardown_general){
    GS_Turn gst = find_turn_type(ps1->points, ps1->points+1, ps1->points+2);
    cr_assert(GS_LeftTurn == gst, "Left not computed correctly");
}

Test(asserts, turn_test_2, .init = setup_general, .fini = teardown_general){
    GS_Turn gst = find_turn_type(ps1->points+1, ps1->points+2, ps1->points+3);
    cr_assert(GS_RightTurn == gst, "Right not computed correctly");
}

Test(asserts, turn_test_3, .init = setup_general, .fini = teardown_general){
    GS_Turn gst = find_turn_type(ps1->points+2, ps1->points+3, ps1->points+4);
    cr_assert(GS_Inline == gst, "Inline not computed correctly");
}


/* Tests for finding lowest y-coord */
Test(asserts, lowest_test_1, .init = setup_general, .fini = teardown_general){
    Point* p = find_lowest_point(ps1);
    cr_assert(p->yCoord == -1 && p->xCoord == -1, "Inline not computed correctly");
}


/* Tests for computing angles */
Test(assert, angle_test_1, .init = setup_general, .fini = teardown_general){
    Point* p = find_lowest_point(ps1);
    compute_angles(ps1, p);
    double angles[8] = {0.785398, 0.58803, 0.876058, 0.851966, 0.844154 ,1.446441, 2.03444, -1.0};
    int i;
    for(i = 0; i< ps1->num_points; i++){
        cr_assert(abs((ps1->points+i)->angle-angles[i]) < 0.00001, "Angle not computed correctly for point %d", i);
    }
    free(ps2);
}


/* Tests for sorting by angles */
Test(assert, sort_test_1, .init = setup_general, .fini = teardown_general){
    Point* p = find_lowest_point(ps1);
    compute_angles(ps1, p);
    ps2 = sort_by_angle(ps1);
    double angles[8] = {-1.0, 0.58803, 0.785398, 0.844154, 0.851966, 0.876058, 1.446441, 2.03444};
    int i;
    for(i = 0; i< ps2->num_points; i++){
        cr_assert(abs((ps2->points+i)->angle-angles[i]) < 0.00001, "Angles not sorted correctly");
    }
}


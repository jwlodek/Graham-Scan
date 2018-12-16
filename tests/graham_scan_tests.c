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

void setup_convex_hull(void){
    ps1 = parse_input_file("./inputs/blackboard_input.txt");
    /* use the reordered output file, because my output always starts from the lowest y-coord point */
    ps2 = parse_input_file("./outputs/blackboard_output_reordered.txt");
}

void teardown_convex_hull(void){
    free(ps1->points);
    free(ps2->points);
    free(ps1);
    free(ps2);
}

void setup_colinear(void){
    ps1 = parse_input_file("./inputs/colinear_input.txt");
    ps2 = parse_input_file("./outputs/colinear_expected.txt");
    ps3 = parse_input_file("./outputs/colinear_handled_expected.txt");
}

void teardown_colinear(void){
    free(ps1->points);
    free(ps2->points);
    free(ps3->points);
    free(ps1);
    free(ps2);
    free(ps3);
}

void setup_colinear2(void){
    ps1 = parse_input_file("./inputs/graham_input3.txt");
    ps2 = parse_input_file("./outputs/graham_output3_expected.txt");
}

void setup_gs_input4(void){
    ps1 = parse_input_file("./inputs/graham_input4.txt");
    ps2 = parse_input_file("./outputs/graham_output4_expected.txt");
}

void setup_gs_input5(void){
    ps1 = parse_input_file("./inputs/graham_input5.txt");
    ps2 = parse_input_file("./outputs/graham_output5_expected.txt");
}

void teardown_2(void){
    free(ps1->points);
    free(ps2->points);
    free(ps1);
    free(ps2);
}

/* ------------------------Unit Tests---------------------------------*/

/* File parsing test */
Test(asserts, parse_input_test, .init = setup_parse, .fini = teardown_general){
    printf("---------------------------------------\n");
    printf("Testing input file parsing...\n");
    PointSet* ps = parse_input_file("./inputs/graham_input1.txt");
    int eq = compare_point_sets(ps, ps1);
    cr_assert(eq == 0, "Parsed point set not equal");
    printf("Input file parsing passed.\n");
}


/* Tests for turn type */
Test(asserts, turn_test_1, .init = setup_general, .fini = teardown_general){
    printf("---------------------------------------\n");
    printf("Testing calulating turn type...\n");
    GS_Turn gst = find_turn_type(ps1->points, ps1->points+1, ps1->points+2);
    cr_assert(GS_LeftTurn == gst, "Left not computed correctly");
    printf("Left turn type calculation passed.\n");
}

Test(asserts, turn_test_2, .init = setup_general, .fini = teardown_general){
    printf("---------------------------------------\n");
    printf("Testing calulating turn type...\n");
    GS_Turn gst = find_turn_type(ps1->points+1, ps1->points+2, ps1->points+3);
    cr_assert(GS_RightTurn == gst, "Right not computed correctly");
    printf("Right turn type calculation passed.\n");
}

Test(asserts, turn_test_3, .init = setup_general, .fini = teardown_general){
    printf("---------------------------------------\n");
    printf("Testing calulating turn type...\n");
    GS_Turn gst = find_turn_type(ps1->points+2, ps1->points+3, ps1->points+4);
    cr_assert(GS_Inline == gst, "Inline not computed correctly");
    printf("Inline turn type calculation passed.\n");
}


/* Tests for finding lowest y-coord */
Test(asserts, lowest_test_1, .init = setup_general, .fini = teardown_general){
    printf("---------------------------------------\n");
    printf("Testing calulating lowest point by y-coord...\n");
    Point* p = find_lowest_point(ps1);
    cr_assert(p->yCoord == -1 && p->xCoord == -1, "Lowest point not found correctly");
    printf("Lowest point found.\n");
}

Test(asserts, lowest_test_2, .init = setup_convex_hull, .fini = teardown_convex_hull){
    printf("---------------------------------------\n");
    printf("Testing calulating lowest point by y-coord...\n");
    Point* p = find_lowest_point(ps1);
    cr_assert(p->yCoord == -200 && p->xCoord == -25, "Lowest point not found correctly");
    printf("Lowest point found.\n");
}


/* Tests for computing angles */
Test(assert, angle_test_1, .init = setup_general, .fini = teardown_general){
    printf("---------------------------------------\n");
    printf("Testing calulating angles for each point...\n");
    Point* p = find_lowest_point(ps1);
    compute_angles(ps1, p);
    double angles[8] = {0.785398, 0.58803, 0.876058, 0.851966, 0.844154 ,1.446441, 2.03444, -1.0};
    int i;
    for(i = 0; i< ps1->num_points; i++){
        cr_assert(abs((ps1->points+i)->angle-angles[i]) < 0.00001, "Angle not computed correctly for point %d", i);
    }
    printf("Angles computed successfully.\n");
}


/* Tests for sorting by angles */
Test(assert, sort_test_1, .init = setup_general, .fini = teardown_general){
    printf("---------------------------------------\n");
    printf("Testing sorting points by angle...\n");
    Point* p = find_lowest_point(ps1);
    compute_angles(ps1, p);
    sort_by_angle(ps1->points, 0, ps1->num_points - 1);
    double angles[8] = {-1.0, 0.58803, 0.785398, 0.844154, 0.851966, 0.876058, 1.446441, 2.03444};
    //print_points(ps1);
    int i;
    for(i = 0; i< ps1->num_points; i++){
        //printf("%lf\n", (ps1->points+i)->angle);
        cr_assert(abs((ps1->points+i)->angle-angles[i]) < 0.00001, "Angles not sorted correctly");
    }
    printf("Points sorted correctly.\n");
}


/* Test against blackboard input/output */
Test(assert, convex_hull_test, .init = setup_convex_hull, .fini = teardown_convex_hull){
    printf("---------------------------------------\n");
    printf("Testing convex hull graham scan on blackboard input set...\n");
    PointSet* convex_hull = compute_convex_hull(ps1);
    int eq = compare_point_sets(convex_hull, ps2);
    free(convex_hull->points);
    free(convex_hull);
    cr_assert(eq == 0, "Convex Hull not computed correctly"); 
    printf("Convex hull computed successfully.\n");
}


/* Test if removinf colinear points causes errors for sets of points without colinearity */
Test(assert, no_colinear_test, .init = setup_convex_hull, .fini = teardown_convex_hull){
    printf("---------------------------------------\n");
    printf("Testing convex hull with on blackboard set w/ degeneracy handling...\n");
    PointSet* convex_hull = compute_convex_hull(ps1);
    PointSet* after_degeneracy = remove_degeneracy(convex_hull);
    free(convex_hull->points);
    free(convex_hull);
    int eq = compare_point_sets(after_degeneracy, ps2);
    free(after_degeneracy->points);
    free(after_degeneracy);
    cr_assert(eq == 0, "Non colinear CH affected by removing colinearity");
    printf("Convex hull computed successfully.\n");
}


/* Test for handling colinear degeneracy */
Test(assert, colinear_test, .init = setup_colinear, .fini = teardown_colinear){
    printf("---------------------------------------\n");
    printf("Testing convex hull on set with 3 colinear...\n");
    PointSet* convex_hull = compute_convex_hull(ps1);
    int eq1 = compare_point_sets(convex_hull, ps2);
    cr_assert(eq1 == 0, "Didn't get excpected convex hull before degeneracy");
    PointSet* after_degeneracy = remove_degeneracy(convex_hull);
    //print_points(after_degeneracy);
    free(convex_hull->points);
    free(convex_hull);
    int eq2 = compare_point_sets(after_degeneracy, ps3);
    free(after_degeneracy->points);
    free(after_degeneracy);
    cr_assert(eq2 == 0, "Did not handle degeneracy successfully");
    printf("Convex hull computed successfully.\n");
}

/* Test for colinear degenracy where last point is in colinear set */
Test(assert, colinear_test2, .init = setup_colinear2, .fini = teardown_2){
    printf("---------------------------------------\n");
    printf("Testing convex hull on set with colinear that include start point...\n");
    PointSet* convex_hull = compute_convex_hull(ps1);
    PointSet* after_degeneracy = remove_degeneracy(convex_hull);
    //print_points(after_degeneracy);
    free(convex_hull->points);
    free(convex_hull);
    int eq = compare_point_sets(after_degeneracy, ps2);
    free(after_degeneracy->points);
    free(after_degeneracy);
    cr_assert(eq == 0, "Did not handle degeneracy successfully");
    printf("Convex hull computed successfully.\n");
}


/* Test on medium size point set w/ degeneracy */
Test(assert, colinear_test3, .init = setup_gs_input4, .fini = teardown_2){
    printf("---------------------------------------\n");
    printf("Testing convex hull on large point set w/ degeneracy...\n");
    PointSet* convex_hull = compute_convex_hull(ps1);
    PointSet* after_degeneracy = remove_degeneracy(convex_hull);
    //print_points(after_degeneracy);
    free(convex_hull->points);
    free(convex_hull);
    int eq = compare_point_sets(after_degeneracy, ps2);
    free(after_degeneracy->points);
    free(after_degeneracy);
    cr_assert(eq == 0, "Did not handle degeneracy successfully");
    printf("Convex hull computed successfully.\n");
}



/* Test on large point set */
Test(assert, large_set_test, .init = setup_gs_input5, .fini = teardown_2){
    printf("---------------------------------------\n");
    printf("Testing large point set wo/ degeneracy...\n");
    PointSet* convex_hull = compute_convex_hull(ps1);
    PointSet* after_degeneracy = remove_degeneracy(convex_hull);
    //print_points(after_degeneracy);
    free(convex_hull->points);
    free(convex_hull);
    int eq = compare_point_sets(after_degeneracy, ps2);
    free(after_degeneracy->points);
    free(after_degeneracy);
    cr_assert(eq == 0, "Did not compute CH correctly");
    printf("Convex hull computed successfully.\n");
}

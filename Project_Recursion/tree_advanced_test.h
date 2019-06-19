//
//  testing.h
//  project2
//
//  Created by Ravir on 2019/6/13.
//  Copyright © 2019 新雨. All rights reserved.
//

#ifndef testing_h
#define testing_h


#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "p2.h"
#include "recursive.h"


const tree_t emptytree = tree_make();
const tree_t simple1 = tree_make(6,tree_make(7,tree_make(3,emptytree,emptytree),tree_make(2,emptytree,emptytree)),tree_make(4,tree_make(1,emptytree,emptytree),tree_make(0,emptytree,tree_make(-1,emptytree,emptytree))));
const tree_t simple2 = tree_make(-5,tree_make(-3,tree_make(-7,emptytree,emptytree),emptytree),tree_make(-7,emptytree,tree_make(-2,emptytree,emptytree)));
const tree_t simple3 = tree_make(6,tree_make(7,emptytree,emptytree),tree_make(4,emptytree,emptytree));
const tree_t simple4 = tree_make(6,emptytree,tree_make(4,emptytree,emptytree));
const tree_t simple5 = tree_make(4,tree_make(1,emptytree,emptytree),tree_make(0,emptytree,tree_make(-1,emptytree,emptytree)));
const tree_t simple6 = tree_make(4,emptytree,tree_make(0,emptytree,emptytree));
const tree_t simple7 = tree_make(4,tree_make(2,emptytree,emptytree),tree_make(0,emptytree,emptytree));
const tree_t monoMix = tree_make(-2,tree_make(-3,tree_make(-3,tree_make(-4,emptytree,emptytree),tree_make(-2,emptytree,emptytree)),emptytree),tree_make(-2,tree_make(3,emptytree,emptytree),tree_make(-7,emptytree,emptytree)));
const tree_t monoIn = tree_make(-2,tree_make(-2,tree_make(-1,tree_make(7,emptytree,emptytree),emptytree),emptytree),tree_make(-2,emptytree,tree_make(-5,emptytree,emptytree)));
const tree_t monoDe = tree_make(7,tree_make(7,tree_make(-2,emptytree,emptytree),emptytree),tree_make(6,tree_make(16,emptytree,emptytree),tree_make(0,emptytree,emptytree)));
const tree_t sort1 = tree_make(6, tree_make(-2,tree_make(-7,emptytree,emptytree),tree_make(5,emptytree,emptytree)), tree_make(7,emptytree,emptytree));
const tree_t sort2 = tree_make(6, tree_make(-2,tree_make(-7,emptytree,emptytree),tree_make(5,emptytree,emptytree)), tree_make(7,tree_make(6,emptytree,emptytree),emptytree));
const tree_t sort3 = tree_make(6, tree_make(-2,tree_make(-7,emptytree,emptytree),tree_make(5,emptytree,tree_make(5,emptytree,emptytree))), tree_make(7,emptytree,emptytree));

bool list_equal(list_t l1, list_t l2);
// EFFECTS: returns true iff l1 == l2.

bool tree_equal(tree_t t1, tree_t t2);
// EFFECTS: returns true iff t1 == t2


void test_tree_sum ();
void test_tree_search();
void test_depth();
void test_tree_max();
void test_traversal();
void test_tree_hasMonotonicPath();
void test_tree_allPathSumGreater();
void test_covered_by();
void test_contained_by();
void test_insert_tree();
void test_all();
#endif /* testing_h */

//
//  testing.cpp
//  project2
//
//  Created by Ravir on 2019/6/13.
//  Copyright © 2019 新雨. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "p2.h"
#include "tree_advanced_test.h"

using namespace std;

void test_tree_sum () {
    cout << endl <<"test_tree_sum:";
    bool re[2]={0};
    re[0] = (tree_sum(simple1)==22);
    re[1] = (tree_sum(emptytree)==0);
    if (re[0] && re[1]) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i =0; i<2; i++) {
            if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
        }
    }
}

void test_tree_search () {
    cout << endl <<"test_tree_search:";
    bool re[5] = {0};
    re[0] = (tree_search(simple1, 17) == 0);
    re[1] = (tree_search(simple1, 4) == 1);
    re[2] = (tree_search(simple1, -1) == 1);
    re[3] = (tree_search(simple1, -19) == 0);
    re[4] = (tree_search(emptytree, -19) == 0);
    if (re[0] && re[1] && re[2] && re[3] && re[4]) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i =0; i<5; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }
}

void test_depth(){
    cout << endl <<"test_depth:";
    bool re[3] = {0};
    re[0] = (depth(simple1)==4);
    re[1] = (depth(simple2)==3);
    re[2] = (depth(emptytree)==0);
    if (re[0] && re[1] && re[2] ) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i =0; i<3; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }
}

void test_tree_max(){
    cout << endl <<"test_tree_max:";
    bool re[2] = {0};
    re[0] = (tree_max(simple1)==7);
    re[1] = (tree_max(simple2)==-2);
    if (re[0] && re[1] ) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i = 0; i<2; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }
}

void test_traversal(){
    cout << endl <<"test_traversal:";
    int simple1_trare[] = {3,7,2,6,1,4,0,-1};
    list_t simple1_tra = list_make();
    for (int i = 0; i<8 ; i++) {
        simple1_tra = list_make(simple1_trare[i],simple1_tra);
    }
    simple1_tra = reverse(simple1_tra);
    bool re[2] = {0};
    re[0] = list_equal(traversal(simple1),simple1_tra);
    re[1] = list_equal(traversal(emptytree), list_make());
    if (re[0] && re[1] ) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i = 0; i<2; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }

}

void test_tree_hasMonotonicPath(){
    cout << endl <<"test_tree_hasMonotonicPath:";
    bool re[6] = {0};
    re[0] = (tree_hasMonotonicPath(simple1)==1);
    re[1] = (tree_hasMonotonicPath(simple2)==0);
    re[2] = (tree_hasMonotonicPath(monoMix)==1);
    re[3] = (tree_hasMonotonicPath(monoIn)==1);
    re[4] = (tree_hasMonotonicPath(monoDe)==1);
    re[5] = (tree_hasMonotonicPath(emptytree)==0);
    if (re[0] && re[1] && re[2] && re[3] && re[4] && re[5]) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i = 0; i<6; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }
}

void test_tree_allPathSumGreater(){
    cout << endl <<"test_tree_allPathSumGreater:";
    bool re[6] = {0};
    re[0] = (tree_allPathSumGreater(simple1,8)==1);
    re[1] = (tree_allPathSumGreater(simple1,10)==0);
    re[2] = (tree_allPathSumGreater(simple2,-10)==0);
    re[3] = (tree_allPathSumGreater(simple2,-16)==1);
    re[4] = (tree_allPathSumGreater(simple2,9)==0);
    re[5] = (tree_allPathSumGreater(simple2,-15)==0);
    if (re[0] && re[1] && re[2] && re[3] && re[4] && re[5]) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i = 0; i<6; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }
}



void test_covered_by(){
    cout << endl <<"test_covered_by:";
    bool re[7] = {0};
    re[0] = (covered_by(simple3, simple1)==1);
    re[1] = (covered_by(simple4, simple1)==1);
    re[2] = (covered_by(simple2, simple1)==0);
    re[3] = (covered_by(simple1, simple3)==0);
    re[4] = (covered_by(emptytree, simple1)==1);
    re[5] = (covered_by(simple1, emptytree)==0);
    re[6] = (covered_by(emptytree, emptytree)==1);
    if (re[0] && re[1] && re[2] && re[3] && re[4] && re[5] && re[6]) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i = 0; i<7; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }
}



void test_contained_by(){
    cout << endl <<"test_contained_by:";
    bool re[7] = {0};
    re[0] = (contained_by(simple3, simple1)==1);
    re[1] = (contained_by(simple5, simple1)==1);
    re[2] = (contained_by(simple6, simple1)==1);
    re[3] = (contained_by(simple7, simple3)==0);
    re[4] = (contained_by(emptytree, simple1)==1);
    re[5] = (contained_by(simple1, emptytree)==0);
    re[6] = (contained_by(emptytree, emptytree)==1);
    if (re[0] && re[1] && re[2] && re[3] && re[4] && re[5] && re[6]) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i = 0; i<7; i++) if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
    }
}

void test_insert_tree(){
    cout << endl <<"test_insert_tree:";
    bool re[3]={0};
    re[0] = (tree_equal(insert_tree(6, sort1), sort2));
    re[1] = (tree_equal(insert_tree(5, sort1), sort3));
    re[2] = (tree_equal(insert_tree(1, emptytree), tree_make(1,emptytree,emptytree)));
    if (re[0] && re[1] && re[2] ) cout << " pass" <<endl;
    else{
        cout << " fail" << endl;
        for (int i =0; i<3; i++) {
            if (re[i]==0) cout << "result " << i << " is wrong." <<endl;
        }
    }
}

void test_all(){
    test_tree_sum();
    test_tree_search();
    test_depth();
    test_tree_max();
    test_traversal();
    test_tree_hasMonotonicPath();
    test_tree_allPathSumGreater();
    test_covered_by();
    test_contained_by();
    test_insert_tree();
}

bool list_equal(list_t l1, list_t l2)
// EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }
}

bool tree_equal(tree_t t1, tree_t t2)
// EFFECTS: returns true iff t1 == t2
{
    if(tree_isEmpty(t1) && tree_isEmpty(t2))
    {
        return true;
    }
    else if(tree_isEmpty(t1) || tree_isEmpty(t2))
    {
        return false;
    }
    else
    {
        return ((tree_elt(t1) == tree_elt(t2))
                && tree_equal(tree_left(t1), tree_left(t2))
                && tree_equal(tree_right(t1), tree_right(t2)));
    }
}

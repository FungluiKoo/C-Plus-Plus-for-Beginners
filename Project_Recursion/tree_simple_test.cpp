#include <iostream>
#include "p2.h"

using namespace std;

static bool tree_equal(tree_t t1, tree_t t2)
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

int tree_simple_test()
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    if((tree_sum(end)==10)&&(tree_sum(start)==7)){cout<<"Success: Tree_Sum."<<endl;}
    else{cout<<"Failed: Tree_Sum."<<endl;}

    if((tree_search(end,3))&&(!tree_search(start,3))){cout<<"Success: tree search."<<endl;}
    else{cout<<"Failed: tree search."<<endl;}

    if((depth(end)==3)&&(depth(start)==2)){cout<<"Sucess: depth."<<endl;}
    else{cout<<"Failed: depth."<<endl;}

    if((tree_max(end)==4)&&(tree_max(start)==4)){cout<<"Sucess: tree max."<<endl;}
    else{cout<<"Failed: tree max."<<endl;}

    list_print(traversal(end));
    cout<<"should be (1 2 3 4)."<<endl;

    if(tree_hasMonotonicPath(start)&&tree_hasMonotonicPath(end)){cout<<"Sucess: hasMonoPath."<<endl;}
    else{cout<<"Failed: hasMonoPath."<<endl;}

    if((!tree_allPathSumGreater(start,3))&&(!tree_allPathSumGreater(end,3))&&tree_allPathSumGreater(start,2)){cout<<"Sucess: allPathSumGreater."<<endl;}
    else{cout<<"Failed: allPathSumGreater."<<endl;}

    if((covered_by(start,end))&&(!covered_by(end,start))){cout<<"Sucess: covered_by."<<endl;}
    else{cout<<"Failed: covered_by."<<endl;}

    tree_t small=tree_make(4,tree_make(3,tree_make(),tree_make()),tree_make());
    if((contained_by(small,end))&&(!contained_by(small,start))){cout<<"Sucess: contained_by."<<endl;}
    else{cout<<"Failed: contained_by."<<endl;}

    tree_t candidate = insert_tree(3, start);
    tree_print(end);
    cout << endl;
    cout << endl;

    tree_print(candidate);
    cout << endl;

    if(tree_equal(candidate, end))
    {
        cout << "Success: Insert."<<endl;
        return 0;
    }
    else
    {
        cout << "Failed: Insert."<<endl;
        return -1;
    }

}

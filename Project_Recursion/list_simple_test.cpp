#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

static bool isEven(int n){
    return (n%2==0);
}

static bool list_equal(list_t l1, list_t l2)
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

int list_simple_test()
{
    int i;
    list_t listA, listA_answer;
    list_t listB, listB_answer;

    listA = list_make();
    listB = list_make();
    listA_answer = list_make();
    listB_answer = list_make();

    for(i = 5; i>0; i--)
    {
        listA = list_make(i, listA);
        listA_answer = list_make(6-i, listA_answer);
        listB = list_make(i+10, listB);
        listB_answer = list_make(i+10, listB_answer);
    }

    list_t inserted_list=insert_list(listA,listA_answer,3);
    list_print(inserted_list);
    cout<<"should be (1 2 3 5 4 3 2 1 4 5)."<<endl;
    list_print(unique(inserted_list));
    cout<<"should be (1 2 3 5 4)."<<endl;
    list_print(chop(inserted_list,3));
    cout<<"should be (1 2 3 5 4 3 2)."<<endl;

    if(5==size(listB)){cout<<"Success: size"<<endl;}
    else{cout<<"Failed: size"<<endl;}

    if(memberOf(listB,15)){cout<<"Success: memberOf"<<endl;}
    else{cout<<"Failed: memberOf"<<endl;}

    if(205==dot(listB,listA) && 35==dot(listA_answer,listA)){cout<<"Success: dot"<<endl;}
    else{cout<<"Failed: dot"<<endl;}

    if(isIncreasing(listA) && !isIncreasing(listA_answer)){cout<<"Success: isIncreasing"<<endl;}
    else{cout<<"Failed: isIncreasing"<<endl;}

    if(isArithmeticSequence(listB) && isArithmeticSequence(listB_answer)){cout<<"Success: isArithmetic"<<endl;}
    else{cout<<"Failed: isArithmetic"<<endl;}

    for(i = 5; i>0; i--)
    {
        listB_answer = list_make(i, listB_answer);
    }

    list_print(listA);
    cout << endl;
    list_print(listB);
    cout << endl;

    listB = append(listA, listB);
    listA = reverse(listA);
    list_print(listA);
    cout << endl;
    list_print(listB);
    cout << endl;

    if(list_equal(listA, listA_answer) 
        && list_equal(listB, listB_answer))
    {
        cout << "Success: Append and Reverse"<<endl;
    }
    else
    {
        cout << "Failed: Append and Reverse"<<endl;
    }

    list_print(filter_odd(listA_answer));
    cout<<"should be (5 3 1)."<<endl;
    list_print(filter_odd(listB_answer));
    cout<<"should be (1 3 5 11 13 15)."<<endl;

    list_print(filter(listA_answer,isEven));
    cout<<"should be (4 2)."<<endl;
    list_print(filter(listB_answer,isEven));
    cout<<"should be (2 4 12 14)."<<endl;

    return 0;
}

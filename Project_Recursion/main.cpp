#include <iostream>
#include "p2.h"

using namespace std;

int list_simple_test();
int tree_simple_test();
void test_all();

int main(){
    cout<<"Enter: L (to test list), T (to test tree), A (advanced tree test), Q (to quit)."<<endl;
    bool flag=true;
    while(flag){
        char ch;
        cin>>ch;
        switch(ch){
            case 'L':
                list_simple_test();
                break;
            case 'T':
                tree_simple_test();
                break;
            case 'A':
                test_all();
                break;
            case 'Q':
                flag=false;
                break;
            default:
                continue;
        }
    }
    return 0;
}

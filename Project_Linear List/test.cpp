#include <iostream>
#include "dlist.h"
using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    int *ip2= new int(2);
    ilist.insertFront(ip);
    ilist.insertBack(ip2);

    if(ilist.isEmpty()){result = -1;}
    ip2 = ilist.removeFront();
    if(*ip2 != 1)
        result = -1;
    delete ip2;
    if(ilist.isEmpty()){result = -1;}
    ip =ilist.removeFront();
    if(*ip!=2){result = -1;}
    if(!ilist.isEmpty())
        result = -1;
    delete ip;
    return result;
}

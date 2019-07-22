#include "assignment.h"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    int ex;
    do {
        ex = getExerciseNumber(argc, argv);
        switch (ex){
        case 1 :
            ex1();
            break;
        case 2:
            ex2(argc, argv) ;
            break;
        case 0:
            //exit case
            return 0;
        default:
            cout<<"The exercise does not exist!"<<endl;
            cout<<"You specified exercise: "<<ex<<endl;
            return 0;
        }
    }
    while (argc == 1);
    return 0;
}

int getExerciseNumber(int argc, char* argv[]){
    if(argc <= 0 || argc > 2) {
        cout<<"Illegal Usage"<<endl;
        exit(-2);
    }
    if (argc == 2) {
        // Grader provided argument
        char *str = argv[1];
        int crit = 1;
        crit = crit && (str[0] == '-');
        crit = crit && (str[1] == 'e');
        crit = crit && (str[2] == 'x');
        if (crit)
            if ( str[3] > '0' && str[3] <= '9')
                return (str[3] - '0');
        cout<<"Illegal Usage"<<endl;
        exit(-3);
    }
    if (argc == 1){
        //Student running test repeatedly
        int exerciseNum = 0;
        for(;;) {
            cout<<"Please input your exercise number: ";
            std::cin>>exerciseNum;
            char c = 0;
            while ((c = getchar()) != '\n' && c != EOF) { }
            if(exerciseNum >= 0 && exerciseNum < 10)
                return exerciseNum;
            cout<<"Illegal input, try again"<<endl;
        }
    }
}

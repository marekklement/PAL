#include <iostream>
#include <cmath>

using namespace std;

inline void readNumber(int *x) {
    register char c = getchar_unlocked();
    *x = 0;
    for (; (c < 48) || (c > 57); c = getchar_unlocked());
    for (; (c > 47) && (c < 58); c = getchar_unlocked()) {
        *x = (int) ((((*x) << 1) + ((*x) << 3)) + c - 48);
    }
}

bool checkSame(double node1[], double node2[]){
    return node1[0] == node2[0] && node1[1] == node2[1];
}

double addLen(double node1[], double node2[]){
    double a = node1[0] - node2[0];
    double b = node1[1] - node2[1];
    double a2 = a*a;
    double b2 = b*b;
    return std::sqrt(a2 + b2);
}

void read(){
    int numberOfLines;
    readNumber(& numberOfLines);
    double previousLine[2], firstLine[2];
    int first, second;
    double len = 0;
    for (int i = 0; i < numberOfLines; i++){
        readNumber(& first);
        readNumber(& second);
        if(i == 0){
            previousLine[0] = first;
            previousLine[1] = second;
            firstLine[0] = first;
            firstLine[1] = second;
        } else {
            double nextLine[2];
            nextLine[0] = first;
            nextLine[1] = second;
            if(checkSame(previousLine, nextLine)) continue;
            len += addLen(previousLine, nextLine);
            previousLine[0] = first;
            previousLine[1] = second;
        }
    }
    if(numberOfLines!=0) {
        len += addLen(previousLine, firstLine);
    }
    //
    int res = (int) std::ceil(5*len);
    printf("%d", res);
}

int main() {
    read();
    return 0;
}

#include <iostream>
#include <string>

using namespace std;

inline void readNumber(int *x) {
    register char c = getchar_unlocked();
    *x = 0;
    for (; (c < 48) || (c > 57); c = getchar_unlocked());
    for (; (c > 47) && (c < 58); c = getchar_unlocked()) {
        *x = (int) ((((*x) << 1) + ((*x) << 3)) + c - 48);
    }
}

void getChar(string &str)
{
    char c = '0';
    while((c = getchar_unlocked()) && (c != -1 && c != '\n' && c != '\r'))
    {
        str += c;
    }
}

string word;
int abcLen;
int lenSubword;
int difference;

void read() {
    readNumber(& abcLen);
    readNumber(& lenSubword);
    readNumber(& difference);

    getChar(word);
}



int count(){
    int len = word.size();
    int global = 0;
    int lenDiff = lenSubword - difference;
    for (int i = 0; i < len - lenSubword + 1; ++i) {
        for (int j = i + lenSubword; j < len - lenSubword + 1; ++j) {
            int count = 0;
            for (int k = 0; k < lenSubword; ++k) {
                if(word.at(i+k) != word.at(j+k)){
                    count++;
                }
                if(count > difference){
                    break;
                }
            }
            if (count == difference) {
                global++;
            }
        }
        if(difference != 0) {
            // get lenSub - difference
            for (int j = i + lenSubword; j < len - lenDiff + 1; ++j) {
                bool ok = true;
                int more = 0;
                for (int l = 0; l < lenDiff;) {
                    if(word.at(j+l) != word.at(i + l + more)){
                        if(more != 0) {
                            ok = false;
                            break;
                        } else
                            more = difference;
                    } else l++;
                }
                if(ok){
                    global++;
                }
            }
        }
    }
    if(difference!=0) {
        for (int i = 0; i < len - lenDiff + 1; ++i) {
            for (int j = i + lenDiff; j < len - lenSubword + 1; ++j) {
                bool ok = true;
                int more = 0;
                for (int l = 0; l < lenDiff;) {
                    if(word.at(i+l) != word.at(j + l + more)){
                        if(more != 0) {
                            ok = false;
                            break;
                        } else
                            more = difference;
                    } else l++;
                }
                if(ok){
                    global++;
                }
            }
        }
    }
    return global;
}

int main() {
    read();
    printf("%d", count());
    return 0;
}

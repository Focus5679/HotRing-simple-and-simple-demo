#include "hotring-r.h"
#include <iostream>
#include <ctime>
#include <fstream>

#define inputfile "test5.data"

const int N = 10000000;                  //总访问数
const int M = 1000;                      //总项数

int main()
{
    time_t start, stop;
    string key;
    string val;
    ht h(M);
    hotring hr(M);



    fstream input(inputfile);

    

    for (int i = 0; i < M; ++i) {
        input >> key >> val;
        h.insert(key, val);
    }

    start = time(NULL);
    while(input >> key){
        h.search(key);
    }
    stop = time(NULL);

    cout << "HashTable:" << endl;
    cout << "findcnt:" << h.getfindcnt() << "次" << endl;
    cout << "maxFindcnt:" << h.getmaxFindcnt() << "次" << endl;
    cout << "minFindcnt:" << h.getminFindcnt() << "次" << endl;
    cout << "averageFindcnt:" << (double)h.getfindcnt() / N << "次" << endl;
    cout << "Use Time:" << (stop - start) << "s" << endl << endl;




    input.close();
    input.open(inputfile);



    for (int i = 0; i < M; ++i) {
        input >> key >> val;
        hr.insert(key, val);
    }

    start = time(NULL);
    while (input >> key) {
        hr.search(key);
    }
    stop = time(NULL);

    cout << "HotRing:" << endl;
    cout << "findcnt:" << hr.getfindcnt() << "次" << endl;
    cout << "maxFindcnt:" << hr.getmaxFindcnt() << "次" << endl;
    cout << "minFindcnt:" << hr.getminFindcnt() << "次" << endl;
    cout << "averageFindcnt:" << (double)hr.getfindcnt() / N << "次" << endl;
    cout << "Use Time:" << (stop - start) << "s" << endl;

    return 0;
}

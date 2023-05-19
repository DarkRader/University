#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>
using namespace std;

void thrFunc (int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d\n", i);
    }
}

int main (int argc, char * argv []) {
    vector<thread> threads;
    
    for(int i = 0; i < 4; ++i) {
        threads.emplace_back(thrFunc, 1000 + i);
    }
    
    thrFunc(1234);
    
    for(auto & t : threads) {
        t.join();
    }
    
    return 0;
}



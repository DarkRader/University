#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <condition_variable>
#include <pthread.h>
#include <semaphore.h>
#include "progtest_solver.h"
#include "sample_tester.h"
using namespace std;
#endif /* __PROGTEST__ */ 

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCompanyProblem {
public:
    CCompanyProblem(AProblemPack problemPack, size_t idProblemPack) : m_problemPack(problemPack), m_idProblemPack(idProblemPack) {
       
    }
    
//    for(size_t i = 0; i < m_problemPack->m_Problems.size(); ++i) {
//        m_problems.emplace_back(m_problemPack->m_Problems[i]);
//    }
//
//    printf("Control problem pack");
    
private:
    AProblemPack m_problemPack;
    size_t m_idProblemPack;
//    vector<AProblem> m_problems;
};


class COptimizer ;
class CThreadWork {
public:
    CThreadWork() {}
    ~CThreadWork() {}

    void createThread(int tid, COptimizer & opt) {
        printf("Thread %d: Start\n", tid);

        this_thread::sleep_for(chrono::seconds(5));

        printf("Thread %d: Stop\n", tid);
    }

private:
    mutex mtx1;
    mutex mtx2;
    condition_variable cv_full;
    condition_variable cv_empty;
};

class CCompanyProblemPack {
public:
    CCompanyProblemPack(ACompany company, size_t idCompany) : m_company(company), m_idCompany(idCompany) {
        thread(&CCompanyProblemPack::createCommunicationThread, this);
        thread(&CCompanyProblemPack::createDeliveredThread, this);
    }
    
//    size_t idProblemPack = 0;
//    while(m_problemsPack.empty() ||  m_problemsPack.back() != nullptr) {
//        AProblemPack newProblemPack = company->waitForPack();
//        m_problemsPack.emplace_back(newProblemPack);
//        idProblemPack++;
//    }
//
//    printf("Control!");
    
private:
    ACompany m_company;
    size_t m_idCompany;
    
    thread m_commThread;
    thread m_delivThread;
    vector<AProblemPack> m_problemsPack;
    
    void createCommunicationThread(void) {
        size_t idProblemPack = 0;
        while(true) {
            AProblemPack newProblemPack = m_company->waitForPack();
            
        }
    }
    
    void createDeliveredThread(void) {
        
    }
};

class COptimizer 
{
  public:
    COptimizer(void) {
        m_currentIdCompany = 0;
    }
    
    static bool usingProgtestSolver(void) {
      return true;
    }
    
    static void checkAlgorithm(AProblem problem) {
      // dummy implementation if usingProgtestSolver() returns true
    }
    
    void start(int threadCount) {
        CThreadWork some;
        for(int i = 0; i < threadCount; i++) {
            //printf("Start:     Creating thread %d\n", i);
            m_threads.push_back(thread(&CThreadWork::createThread, &some, i, ref(*this)));
        }
    }
    
    void stop(void) {
        for(auto &t: m_threads){
            t.join();
        }
    }
                    //std::shared_ptr<CProblem> - in file common.h
    void addCompany(ACompany company) {
        m_companies.emplace_back(CCompanyProblemPack(company, m_currentIdCompany));
        m_currentIdCompany++;
    }
    
  private:
    size_t m_currentIdCompany;
    vector<CCompanyProblemPack> m_companies;
    
    vector<thread> m_threads;
//    thread m_commThread;
//    thread m_delivThread;
    mutex mtx;
};

// TODO: COptimizer implementation goes here
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int main(void) {
  COptimizer optimizer;
  ACompanyTest company = std::make_shared<CCompanyTest> ();
  optimizer.addCompany(company);
  optimizer.start(4);
  optimizer.stop();
  if (!company->allProcessed())
    throw std::logic_error("(some) problems were not correctly processsed");
  return 0;  
}
#endif /* __PROGTEST__ */ 

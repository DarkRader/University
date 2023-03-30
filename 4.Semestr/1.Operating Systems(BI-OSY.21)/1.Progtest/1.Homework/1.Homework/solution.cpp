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

class COptimizer;
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
//    mutex mtx;
    condition_variable cv_full;
    condition_variable cv_empty;
};

class CListProblem {
public:
    CListProblem(size_t id, AProblem problem) : m_id(id), m_problem(problem) {}
    
    size_t getId(void) {
        return m_id;
    }

private:
    size_t m_id;
    AProblem m_problem;
};

class CListProblemPack {
public:
    CListProblemPack(size_t id, AProblemPack newProblemPack) : m_id(id), m_problemPack(newProblemPack)  {
        for(size_t i = 0; i < m_problemPack->m_Problems.size(); ++i) {
            m_problems.emplace_back(CListProblem(i, m_problemPack->m_Problems[i]));
        }
    }
    
    size_t getId(void) {
        return m_id;
    }
    
    AProblemPack getProblemPack(void) {
        return m_problemPack;
    }

private:
    size_t m_id;
    AProblemPack m_problemPack;
    vector<CListProblem> m_problems;
};

//class CCompanyProblems {
//public:
//    CCompanyProblems(size_t id, ACompany company, COptimizer * opt) : m_id(id), m_company(company), m_opt(opt) {
////        createCommunicationThread();
//        m_commThread = thread(&CCompanyProblems::createCommunicationThread, this);
//        m_delivThread = thread(&CCompanyProblems::createDeliveredThread, this);
//    }
//
//private:
//    size_t m_id;
//    ACompany m_company;
//    COptimizer * m_opt;
//
//    thread m_commThread;
//    thread m_delivThread;
//    vector<CListProblemPack> m_problemsPack;
//
//    void createCommunicationThread(void/*size_t id, ACompany company, COptimizer * opt*/) {
//
//        size_t idProblemPack = 0;
////        printf("id : %d\n", m_id);
//        while(true) {
//            AProblemPack newProblemPack = m_company->waitForPack();
//            if(newProblemPack == nullptr) {
//                break;
//            }
//            m_problemsPack.emplace_back(CListProblemPack(idProblemPack, newProblemPack));
//            idProblemPack++;
//        }
//
//    }
//
//    void createDeliveredThread(void) {
//
//    }
//};

class COptimizer 
{
  public:
    COptimizer(void) {
        m_id = 0;
    }
    
    static bool usingProgtestSolver(void) {
      return true;
    }
    
    static void checkAlgorithm(AProblem problem) {
      // dummy implementation if usingProgtestSolver() returns true
    }
    
    void start(int threadCount) {
//        CThreadWork some;
        for(int i = 0; i < threadCount; i++) {
            //printf("Start:     Creating thread %d\n", i);
            m_threads.emplace_back(thread(&CThreadWork::createThread, &m_worker, i, ref(*this)));
        }
    }
    
    void stop(void) {
        for(auto &t: m_threads){
            t.join();
        }
    }
    //std::shared_ptr<CProblem> - in file common.h
    void addCompany(ACompany company) {
        m_companies.emplace_back(CCompanyProblems(m_id, company, this));
        m_id++;
    }
    
  private:
    class CCompanyProblems;
    size_t m_id;
    mutex m_mtx;
    
    CThreadWork m_worker;
    vector<thread> m_threads;
    vector<CCompanyProblems> m_companies;
    
    class CCompanyProblems {
    public:
        CCompanyProblems(size_t id, ACompany company, COptimizer * opt) : m_id(id), m_company(company), m_opt(opt) {
    //        createCommunicationThread();
            m_commThread = thread(&CCompanyProblems::createCommunicationThread, this);
            m_delivThread = thread(&CCompanyProblems::createDeliveredThread, this);
        }
        
    private:
        size_t m_id;
        ACompany m_company;
        COptimizer * m_opt;
        
        thread m_commThread;
        thread m_delivThread;
        vector<CListProblemPack> m_problemsPack;
        
        void createCommunicationThread(void/*size_t id, ACompany company, COptimizer * opt*/) {
            
            size_t idProblemPack = 0;
            printf("id : %zu\n", m_id);
            while(true) {
                AProblemPack newProblemPack = m_company->waitForPack();
                if(newProblemPack == nullptr) {
                    break;
                }
                m_problemsPack.emplace_back(CListProblemPack(idProblemPack, newProblemPack));
                idProblemPack++;
            }
            
            
        }
        
        void createDeliveredThread(void) {

        }
    };
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

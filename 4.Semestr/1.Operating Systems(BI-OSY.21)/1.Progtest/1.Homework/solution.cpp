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
class CFirmProblemPack;
class CSolver {
public:
    CSolver() {
        m_solver = createProgtestSolver();
    }

    void addProblem(AProblem &problem) {
        m_solver->addProblem(problem);
        m_containSolver[m_containSolver.size() - 1].second++;
    }

    void solve() {
        m_solver->solve();
    }

    bool getCapacity() {
        return m_solver->hasFreeCapacity();
    }

    void newSolver() {
        m_solver = createProgtestSolver();
        m_containSolver.clear();
    }

    void addProblemPack(CFirmProblemPack & problemPack) {
        m_containSolver.push_back({problemPack, 0});
    }

    void deliverSolvingProblem() {
        for(size_t i = 0; i < m_containSolver.size(); ++i) {
            
        }
    }

private:
    AProgtestSolver m_solver;
    vector<pair<CFirmProblemPack&, size_t>> m_containSolver;

};

class CFirmProblem {
public:
    CFirmProblem(size_t id, size_t packId, size_t firmaId, AProblem problem) : m_id(id), m_packId(packId), m_firmaId(firmaId), m_problem(problem) {}

    size_t getId(void) {
        return m_id;
    }

private:
    size_t m_id;
    size_t m_packId;
    size_t m_firmaId;
    AProblem m_problem;
};

class CFirmProblemPack {
public:
    CFirmProblemPack(size_t id, size_t firmaId, AProblemPack &newProblemPack) : m_id(id), m_firmaId(firmaId), m_problemPack(newProblemPack) {
        m_size = newProblemPack->m_Problems.size();
        m_solved = false;
        m_loaded = false;
        m_curPos = 0;
        m_solvingProblem = 0;
    }

    void addProblem(CSolver &solver) {
        solver.addProblem(m_problemPack->m_Problems[m_curPos]);
        m_curPos++;
        if(m_curPos == m_size - 1) {
            m_loaded = true;
        }
    }

    void addProblemPack(CSolver &solver) {
        solver.addProblemPack(*this);
    }

    bool getLoaded() {
        return m_loaded;
    }

    bool getSolved(void) {
        return m_solved;
    }

    void deliveredSolvingProblem(size_t numSolProblem) {
        m_solvingProblem += numSolProblem;
        if(m_solvingProblem == m_size) {
            m_solved = true;
        }
    }

private:
    size_t m_id;
    size_t m_firmaId;
    size_t m_size;
    size_t m_curPos;
    size_t m_solvingProblem;
    bool m_solved;
    bool m_loaded;
    AProblemPack &m_problemPack;
};

class CFirm {
public:
    CFirm(size_t id, ACompany company, mutex & mtx, condition_variable & cv) : m_id(id), m_company(company), m_mtx(mtx), m_cv(cv) {}
    
    void createCommunicateTread(vector<thread> &threads, queue<CFirmProblemPack> &queueProblemPack) {
        m_instThread = thread(&CFirm::createInstalerThread, this, ref(threads), ref(queueProblemPack));
        m_delivThread = thread(&CFirm::createDeliveredThread, this);
    }
    
private:
    size_t m_id;
    mutex & m_mtx;
    condition_variable & m_cv;
    ACompany m_company;
    
    thread m_instThread;
    thread m_delivThread;

    
    void createInstalerThread(vector<thread> &threads, queue<CFirmProblemPack> &queueProblemPack) {
        size_t idProblemPack = 0;
        printf("id : %zu\n", m_id);
        while(true) {
            AProblemPack newProblemPack = m_company->waitForPack();
            if(newProblemPack == nullptr) {
                //TODO some flag
                break;
            }
            CFirmProblemPack firmaProblemPack(idProblemPack, m_id, newProblemPack);
            idProblemPack++;
            {
                lock_guard<mutex> ul (m_mtx);
                queueProblemPack.push(firmaProblemPack);
                m_cv.notify_one();
            }
        }
    }
    
    void createDeliveredThread(void) {

    }
};

class COptimizer 
{
  public:
    COptimizer(void) {
        m_numOfFirm = 0;
        m_solver = CSolver();
    }
    
    COptimizer(size_t numOfFirm) {
        m_numOfFirm = numOfFirm;
    }
    
    static bool usingProgtestSolver(void) {
      return true;
    }
    
    static void checkAlgorithm(AProblem problem) {
      // dummy implementation if usingProgtestSolver() returns true
    }
    
    void solvingSpecificProblem(/*CFirmProblemPack &problem,*/ unique_lock<mutex> &lock) {

        if(!m_solver.getCapacity()) {
            m_solver.newSolver();
            m_solver.addProblemPack(m_queueProblemPack.front());
        }

        while(m_solver.getCapacity()) {
            m_queueProblemPack.front().addProblem(m_solver);
            if(m_queueProblemPack.front().getLoaded()) {
                m_queueProblemPack.pop();
                if(m_solver.getCapacity()) {
                    m_solver.addProblemPack(m_queueProblemPack.front());
                }
            }
        }

        m_cv.notify_one();

        lock.unlock();
        m_solver.solve();
        lock.lock();

//        m_solver
    }
    
    void working(int threadNum) {
        printf("Thread %d: Start\n", threadNum);
        while(true) {
            unique_lock<mutex> lock(m_mtxInstaler);
            m_cv.wait(lock, [this] {return !m_queueProblemPack.empty(); });
            
            if(m_queueProblemPack.empty()) {
                break;
            }

            CFirmProblemPack &task = m_queueProblemPack.front();
            solvingSpecificProblem(lock);
        }

    }
    
    void start(int threadCount) {
        for(int i = 0; i < threadCount; i++) {
            printf("Start:     Creating thread %d\n", i);
            m_threads.emplace_back(&COptimizer::working, this, i);
        }

        printf("Threads is creating\n");

        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i].createCommunicateTread(m_threads, m_queueProblemPack);
        }
    }
    
    void stop(void) {
        for(auto &t: m_threads){
            t.join();
        }
    }
    
    //std::shared_ptr<CProblem> - in file common.h
    void addCompany(ACompany company) {
        m_companies.emplace_back(CFirm(m_numOfFirm, company, m_mtxInstaler, m_cv));
        m_numOfFirm++;
    }
    
  private:
    size_t m_numOfFirm;
    mutex m_mtxInstaler;
    mutex m_mtxWorker;
    condition_variable m_cv;
    CSolver m_solver;
    
    queue<CFirmProblemPack> m_queueProblemPack;
    
    vector<thread> m_threads;
    vector<CFirm> m_companies;
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

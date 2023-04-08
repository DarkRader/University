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
class CFirmProblemPack {
public:
    CFirmProblemPack(size_t id, size_t firmId, AProblemPack newProblemPack) : m_id(id), m_firmId(firmId), m_problemPack(newProblemPack) {
        m_size = newProblemPack->m_Problems.size();
        m_solved = false;
        m_loaded = false;
        m_curPos = 0;
        m_solvingProblem = 0;
    }

    AProblem addProblem() {
        m_curPos++;
        if(m_curPos == m_size) {
            printf("All problem of pack %zu: added!\n", m_id);
            m_loaded = true;
        }

        return m_problemPack->m_Problems[m_curPos - 1];
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
            printf("All problem of pack %zu: solved!\n", m_id);
            m_solved = true;
        }
    }

    AProblemPack getSolvedPack() {
        return m_problemPack;
    }

    size_t getPackProblemId() {
        return m_id;
    }

    size_t getFirmId() {
        return m_firmId;
    }

private:
    size_t m_id;
    size_t m_firmId;
    size_t m_size;
    size_t m_curPos;
    size_t m_solvingProblem;
    bool m_solved;
    bool m_loaded;
    AProblemPack m_problemPack;
};

class CFirm {
public:
    CFirm(size_t id, bool instalFinish, ACompany & company, mutex & mtx, condition_variable & cv) : m_id(id), m_instalFinish(instalFinish), m_company(company), m_mtxOpt(mtx), m_cvOpt(cv) {}

    void createCommunicateTread(queue<shared_ptr<CFirmProblemPack>> &queueProblemPack) {
        m_instThread = thread(&CFirm::createInstalerThread, this, ref(queueProblemPack));
        m_delivThread = thread(&CFirm::createDeliveredThread, this);
    }

    void push(shared_ptr<CFirmProblemPack> problemPack) {
        m_queueSolvedPack.push(problemPack);
    }

    thread &getInstaler() {
        return m_instThread;
    }

    thread &getDelivered() {
        return m_delivThread;
    }

    void notifyDeliver() {
        m_cv.notify_one();
    }


private:
    size_t m_id;
    bool &m_instalFinish;

    mutex & m_mtxOpt;
    mutex m_mtx;
    condition_variable & m_cvOpt;
    condition_variable m_cv;
    ACompany &m_company;

    queue<shared_ptr<CFirmProblemPack>> m_queueSolvedPack;

    thread m_instThread;
    thread m_delivThread;


    void createInstalerThread(queue<shared_ptr<CFirmProblemPack>> &queueProblemPack) {
        size_t idProblemPack = 0;
        printf("id : %zu\n", m_id);
        while(true) {
            AProblemPack newProblemPack = m_company->waitForPack();
            if (newProblemPack == nullptr) {
                break;
            }
            //push problemPack in queue and move work to worker
            {
                lock_guard<mutex> ul(m_mtxOpt);
                queueProblemPack.push(shared_ptr<CFirmProblemPack>(new CFirmProblemPack(idProblemPack, m_id, newProblemPack)));
                m_cvOpt.notify_one();
            }
            idProblemPack++;
        }
        printf("All problem of company %zu: solved!", m_id);
    }

    void createDeliveredThread(void) {
        while(true) {
            unique_lock<mutex> lock(m_mtx);
            m_cv.wait(lock, [this] {return !m_queueSolvedPack.empty() && m_queueSolvedPack.front()->getSolved(); });

//            if(m_queueSolvedPack.empty() && m_instalFinish) {
//                break;
//            }

            shared_ptr<CFirmProblemPack> solved = m_queueSolvedPack.front();

            while(true) {
                printf("\n");
                printf("Pack %zu: Delivered!\n\n", m_queueSolvedPack.front()->getPackProblemId());
                m_company->solvedPack(m_queueSolvedPack.front()->getSolvedPack());
                m_queueSolvedPack.pop();
                printf("Queue size is %zu", m_queueSolvedPack.size());
                if(m_queueSolvedPack.empty() || !(m_queueSolvedPack.front()->getSolved())) {
                    break;
                }
            }

        }
    }
};

class CSolver {
public:
    CSolver() {
        m_solver = createProgtestSolver();
    }

    void addProblem(shared_ptr<CFirmProblemPack> problemPack) {
        if(m_containSolver.size() == 0) {
            m_containSolver.push_back({problemPack, 0});
        }
        m_solver->addProblem(problemPack->addProblem());
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

    void clear() {
        m_containSolver.clear();
    }

    void addProblemPack(shared_ptr<CFirmProblemPack> problemPack) {
        m_containSolver.push_back({problemPack, 0});
    }

    vector<pair<shared_ptr<CFirmProblemPack>, size_t>> getContainSolver() {
        return m_containSolver;
    }

    void deliverSolvingProblem(vector<shared_ptr<CFirm>> &companies,
                               vector<pair<shared_ptr<CFirmProblemPack>, size_t>> containSolver) {
        for(size_t i = 0; i < containSolver.size(); ++i) {
            containSolver[i].first->deliveredSolvingProblem(containSolver[i].second);
            if(containSolver[i].first->getSolved()) {
                companies[containSolver[i].first->getFirmId()]->notifyDeliver();
            }
        }
    }

    vector<pair<shared_ptr<CFirmProblemPack>, size_t>> copyContainSolver() {
        vector<pair<shared_ptr<CFirmProblemPack>, size_t>> newContainSolver;
        for(size_t i = 0; i < m_containSolver.size(); ++i) {
            newContainSolver.push_back({m_containSolver[i].first, m_containSolver[i].second});
        }

        return newContainSolver;
    }

    AProgtestSolver getSolver() {
        return m_solver;
    }

private:
    AProgtestSolver m_solver;
    vector<pair<shared_ptr<CFirmProblemPack>, size_t>> m_containSolver;

};

class COptimizer
{
public:
    COptimizer(void) {
        m_numOfFirm = 0;
        m_instalFinish = false;
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

    void fillingPogtestSolver() {
        while(m_solver.getCapacity() && !(m_queueProblemPack.empty())) {
            m_solver.addProblem(m_queueProblemPack.front());
            if(m_queueProblemPack.front()->getLoaded()) {
                m_companies[m_queueProblemPack.front()->getFirmId()]->push(m_queueProblemPack.front());
                m_queueProblemPack.pop();
                if(m_solver.getCapacity() && !(m_queueProblemPack.empty())) {
                    m_solver.addProblemPack(m_queueProblemPack.front());
                    printf("Start or continue to solving %zu: pack problem\n", m_queueProblemPack.front()->getPackProblemId());
                }
            }
        }
    }


    void solvingSpecificProblem(unique_lock<mutex> &lock) {

        printf("Start or continue to solving %zu: pack problem\n", m_queueProblemPack.front()->getPackProblemId());
        fillingPogtestSolver();

        if(m_solver.getCapacity()) {
            return ;
        }

//        vector<pair<shared_ptr<CFirmProblemPack>, size_t>> containSolver = m_solver.getContainSolver();
        vector<pair<shared_ptr<CFirmProblemPack>, size_t>> containSolver = m_solver.copyContainSolver();
        AProgtestSolver solver = m_solver.getSolver();
        m_solver.newSolver();
        m_cv.notify_one();

        lock.unlock();
        solver->solve();
        lock.lock();

        printf("Some work solving!\n");
        m_solver.deliverSolvingProblem(m_companies, containSolver);
    }

    void working(int threadNum) {
        printf("Thread %d: Start\n", threadNum);
        while(true) {
            unique_lock<mutex> lock(m_mtxInstaler);
            m_cv.wait(lock, [this] {return !m_queueProblemPack.empty(); });

            if(m_queueProblemPack.empty() && m_instalFinish) {
                break;
            }

            printf("Worker %d: Take this work\n", threadNum);
            printf("Current queue size is %zu\n", m_queueProblemPack.size());
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
            m_companies[i]->createCommunicateTread(m_queueProblemPack);
        }
    }

    void stop(void) {
        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->getInstaler().join();
        }

        printf("\n");
        printf("ALL PROBLEMS ARE INSTALLING!\n\n");
        m_instalFinish = true;
        m_cv.notify_all();

        for(size_t i = 0; i < m_threads.size(); ++i) {
            m_threads[i].join();
        }

        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->getDelivered().join();
        }
    }

    void addCompany(ACompany company) {
        m_companies.emplace_back(shared_ptr<CFirm>(new CFirm(m_numOfFirm, m_instalFinish, company, m_mtxInstaler, m_cv)));
        m_numOfFirm++;
    }

private:
    size_t m_numOfFirm;
    bool m_instalFinish;

    mutex m_mtxInstaler;
    condition_variable m_cv;
    CSolver m_solver;

    queue<shared_ptr<CFirmProblemPack>> m_queueProblemPack;

    vector<thread> m_threads;
    vector<shared_ptr<CFirm>> m_companies;
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

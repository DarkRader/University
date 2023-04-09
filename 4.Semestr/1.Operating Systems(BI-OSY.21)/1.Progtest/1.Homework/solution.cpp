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
//            printf("All problem of pack %zu: added!\n", m_id.load());
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
//            printf("All problem of pack %zu: solved!\n", m_id.load());
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
    atomic<size_t> m_id;
    atomic<size_t> m_firmId;
    atomic<size_t> m_size;
    atomic<size_t> m_curPos;
    atomic<size_t> m_solvingProblem;
    atomic<bool> m_solved;
    atomic<bool> m_loaded;
    AProblemPack m_problemPack;
};

class CFirm {
public:
    CFirm(size_t id, atomic<bool> &workingFinish, ACompany & company, mutex & mtx, condition_variable & cv) : m_id(id), m_workingFinish(workingFinish), m_mtxOpt(mtx), m_cvOpt(cv) {
        m_company = move(company);
    }

    void createCommunicateTread(queue<shared_ptr<CFirmProblemPack>> &queueProblemPack) {
        m_instThread = thread(&CFirm::instalerThread, this, ref(queueProblemPack));
        m_delivThread = thread(&CFirm::deliveredThread, this);
    }

    void push(shared_ptr<CFirmProblemPack> problemPack) {
        lock_guard<mutex> lock(m_mtx);
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
    atomic<bool> &m_workingFinish;

    mutex & m_mtxOpt;
    mutex m_mtx;
    condition_variable & m_cvOpt;
    condition_variable m_cv;
    ACompany m_company;

    queue<shared_ptr<CFirmProblemPack>> m_queueSolvedPack;

    thread m_instThread;
    thread m_delivThread;


    void instalerThread(queue<shared_ptr<CFirmProblemPack>> &queueProblemPack) {
        size_t idProblemPack = 0;
//        printf("id : %zu\n", m_id);
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
//        printf("All problem of company %zu: solved!", m_id);
    }

    void deliveredThread(void) {
        while(true) {
            unique_lock<mutex> lock(m_mtx);
            m_cv.wait(lock, [this] {return (!m_queueSolvedPack.empty() && m_queueSolvedPack.front()->getSolved()) || m_workingFinish; });


            if(m_queueSolvedPack.empty() && m_workingFinish) {
                lock.unlock();
                break;
            }

            while(true) {
//                printf("\n");
//                printf("Pack %zu: of company %zu: Delivered!\n\n", m_queueSolvedPack.front()->getPackProblemId(), m_id);
                m_company->solvedPack(m_queueSolvedPack.front()->getSolvedPack());
                m_queueSolvedPack.pop();
//                printf("Queue size is %zu", m_queueSolvedPack.size());
                if(m_queueSolvedPack.empty() || !(m_queueSolvedPack.front()->getSolved())) {
                    lock.unlock();
                    break;
                }
            }

            if(m_queueSolvedPack.empty() && m_workingFinish) {
                break;
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
//        lock_guard<mutex> lock(m_mtx);
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
//        lock_guard<mutex> lock(m_mtx);
        return m_solver->hasFreeCapacity();
    }

//    bool getCapacity(vector<pair<shared_ptr<CFirmProblemPack>, size_t>> &containSolver, AProgtestSolver &solver) {
//        lock_guard<mutex> lock(m_mtx);
//        if(!m_solver->hasFreeCapacity()) {
//            containSolver = m_containSolver;
//            solver = m_solver;
//            newSolver();
//        }
//        return m_solver->hasFreeCapacity();
//    }

//    void initContainSolver(vector<pair<shared_ptr<CFirmProblemPack>, size_t>> &containSolver, AProgtestSolver &solver) {
//        lock_guard<mutex> lock(m_mtx);
//        if(!m_solver->hasFreeCapacity()) {
//            containSolver = m_containSolver;
//            solver = m_solver;
//            newSolver();
//        }
//    }

    AProgtestSolver newSolver(vector<pair<shared_ptr<CFirmProblemPack>, size_t>> &containSolver) {
//        lock_guard<mutex> lock(m_mtx);
        AProgtestSolver solver = m_solver;
        m_solver = createProgtestSolver();
//        if(!m_solver->hasFreeCapacity()) {
//            printf("\n");
//            printf("NO CAPACITY IN PROGTEST SOLVER!\n\n");
//        }
        containSolver = m_containSolver;
        m_containSolver.clear();

        return solver;
    }


    void addProblemPack(shared_ptr<CFirmProblemPack> problemPack) {
//        lock_guard<mutex> lock(m_mtx);
        m_containSolver.push_back({problemPack, 0});
    }

//    vector<pair<shared_ptr<CFirmProblemPack>, size_t>> getContainSolver() {
//        lock_guard<mutex> look(m_mtx);
//        return m_containSolver;
//    }

//    void deliverSolvingProblem(vector<shared_ptr<CFirm>> &companies,
//                               vector<pair<shared_ptr<CFirmProblemPack>, size_t>> containSolver) {
//        for(size_t i = 0; i < containSolver.size(); ++i) {
//            unique_lock<mutex> loop(m_mtx);
//            containSolver[i].first->deliveredSolvingProblem(containSolver[i].second);
//            if(containSolver[i].first->getSolved()) {
//                companies[containSolver[i].first->getFirmId()]->notifyDeliver();
//            }
//            loop.unlock();
//        }
//    }

//    AProgtestSolver getSolver() {
//        lock_guard<mutex> lock(m_mtx);
//        return m_solver;
//    }

private:
    AProgtestSolver m_solver;
    vector<pair<shared_ptr<CFirmProblemPack>, size_t>> m_containSolver;
//    mutex m_mtx;
};

class COptimizer
{
public:
    COptimizer(void) {
        m_numOfFirm = 0;
        m_instalFinish = false;
        m_workingFinish = false;
        m_solver = shared_ptr<CSolver> (new CSolver());
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
        while(m_solver->getCapacity() && !(m_queueProblemPack.empty())) {
            m_solver->addProblem(m_queueProblemPack.front());
            if(m_queueProblemPack.front()->getLoaded()) {
                m_companies[m_queueProblemPack.front()->getFirmId()]->push(m_queueProblemPack.front());
                m_queueProblemPack.pop();
//                if(m_solver->getCapacity(containSolver, solver)->hasFreeCapacity() && !(m_queueProblemPack.empty())) {
                if(m_solver->getCapacity() && !(m_queueProblemPack.empty())) {
                    m_solver->addProblemPack(m_queueProblemPack.front());
//                    printf("Start or continue to solving %zu: pack problem\n", m_queueProblemPack.front()->getPackProblemId());
                }
            }
        }
    }


    void solvingSpecificProblem(unique_lock<mutex> &lock) {

//        printf("Start or continue to solving %zu: pack problem\n", m_queueProblemPack.front()->getPackProblemId());
//        vector<pair<shared_ptr<CFirmProblemPack>, size_t>> containSolver;
//        AProgtestSolver solver;
        unique_lock<mutex> lk(m_mtx);
        fillingPogtestSolver();

        if(m_solver->getCapacity() && !(m_queueProblemPack.empty())) {
            lock.unlock();
            lk.unlock();
            return ;
        }

//        m_solver->initContainSolver(containSolver, solver);
        vector<pair<shared_ptr<CFirmProblemPack>, size_t>> containSolver; //= m_solver->getContainSolver();
//        AProgtestSolver solver = m_solver->getSolver();
        AProgtestSolver solver = m_solver->newSolver(containSolver);
        m_cv.notify_one();

        lock.unlock();
        lk.unlock();
        solver->solve();
        lock.lock();
        lk.lock();

//        printf("Some work solving!\n");
//        m_solver->deliverSolvingProblem(m_companies, containSolver);
        for(size_t i = 0; i < containSolver.size(); ++i) {
            containSolver[i].first->deliveredSolvingProblem(containSolver[i].second);
            if(containSolver[i].first->getSolved()) {
                m_companies[containSolver[i].first->getFirmId()]->notifyDeliver();
            }
        }
    }

    void working(int threadNum) {
//        printf("Thread %d: Start\n", threadNum);
        while(true) {
            unique_lock<mutex> lock(m_mtxInstaler);
            m_cv.wait(lock, [this] {return !m_queueProblemPack.empty() || m_instalFinish; });

            if(m_instalFinish) {
                while(!m_queueProblemPack.empty()) {
//                    printf("Worker %d: Take this work\n", threadNum);
//                    printf("Current queue size is %zu\n", m_queueProblemPack.size());
                    solvingSpecificProblem(lock);
                }
            }
            if (m_queueProblemPack.empty() && m_instalFinish) {
//                printf("Thread %d: Finish work\n", threadNum);
                break;
            }
//            printf("Worker %d: Take this work\n", threadNum);
//            printf("Current queue size is %zu\n", m_queueProblemPack.size());
            solvingSpecificProblem(lock);
        }
    }

    void start(int threadCount) {
        for(int i = 0; i < threadCount; i++) {
//            printf("Start:     Creating thread %d\n", i);
            m_threads.emplace_back(&COptimizer::working, this, i);
        }

//        printf("Threads is creating\n");
        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->createCommunicateTread(m_queueProblemPack);
        }
    }

    void stopInstallers(void) {
        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->getInstaler().join();
        }
//        printf("\n");
//        printf("ALL PROBLEMS ARE INSTALLING!\n\n");
        {
            std :: lock_guard<std :: mutex> lock(m_mtxInstaler);
            m_instalFinish = true;
            m_cv.notify_all();
        }
    }

    void stopWorkers(void) {
        for(size_t i = 0; i < m_threads.size(); ++i) {
            m_threads[i].join();
        }
//        printf("\n");
//        printf("ALL WORKERS FINISHED!\n\n");
        m_workingFinish = true;
    }

    void stopDelivers(void) {
        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->notifyDeliver();
            m_companies[i]->getDelivered().join();
        }
//        printf("\n");
//        printf("ALL JOB IS FINISHING!\n\n");
    }

    void stop(void) {
        stopInstallers();

        stopWorkers();

        stopDelivers();
    }

    void addCompany(ACompany company) {
        m_companies.emplace_back(shared_ptr<CFirm>(new CFirm(m_numOfFirm, m_workingFinish, company, m_mtxInstaler, m_cv)));
        m_numOfFirm++;
    }

private:
    size_t m_numOfFirm;
    bool m_instalFinish;
    atomic<bool> m_workingFinish;

    mutex m_mtxInstaler;
    mutex m_mtx;
    condition_variable m_cv;
    shared_ptr<CSolver> m_solver;

    queue<shared_ptr<CFirmProblemPack>> m_queueProblemPack;

    vector<thread> m_threads;
    vector<shared_ptr<CFirm>> m_companies;
};
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int main(void) {
    COptimizer optimizer;
    ACompanyTest company = std::make_shared<CCompanyTest> ();
//    ACompanyTest company2 = std::make_shared<CCompanyTest> ();
    optimizer.addCompany(company);
//    optimizer.addCompany(company2);
    optimizer.start(1);
    optimizer.stop();
    if (!company->allProcessed())
        throw std::logic_error("(some) problems were not correctly processsed");
    return 0;
}
#endif /* __PROGTEST__ */

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
    CFirmProblemPack(size_t firmId, AProblemPack newProblemPack) : m_firmId(firmId), m_problemPack(newProblemPack) {
        m_size = newProblemPack->m_Problems.size();
        m_solved = false;
        m_loaded = false;
        m_curPos = 0;
        m_solvingProblem = 0;
    }

    AProblem addProblem() {
        m_curPos++;
        {
            lock_guard<mutex> lock(m_mutLoaded);
            if (m_curPos == m_size) {
                m_loaded = true;
            }
        }

        return m_problemPack->m_Problems[m_curPos - 1];
    }

    bool getLoaded() {
        lock_guard<mutex> lock(m_mutLoaded);
        return m_loaded;
    }

    bool getSolved(void) {
        return m_solved;
    }
    bool getSolved2(void)
    {
        lock_guard<mutex> lock(m_mutSolved);
        return m_solved;
    }

    void deliveredSolvingProblem(size_t numSolProblem) {
        m_solvingProblem += numSolProblem;
        {
            lock_guard<mutex> lock(m_mutSolved);
            if (m_solvingProblem == m_size) {
                m_solved = true;
            }
        }
    }

    AProblemPack getSolvedPack() {
        return m_problemPack;
    }

    size_t getFirmId() {
        return m_firmId;
    }

private:
    atomic<size_t> m_firmId;
    atomic<size_t> m_size;
    atomic<size_t> m_curPos;
    atomic<size_t> m_solvingProblem;
    atomic<bool> m_solved;
    mutex m_mutSolved;
    bool m_loaded;
    mutex m_mutLoaded;
    AProblemPack m_problemPack;
};

class CFirm {
public:
    CFirm(size_t id, atomic<bool> &workingFinish, ACompany & company, mutex & mtx, condition_variable & cv) : m_id(id), m_workingFinish(workingFinish), m_mtxWorker(mtx), m_cvOpt(cv) {
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
        lock_guard<mutex> lock(m_mtx);
        m_cv.notify_one();
    }


private:
    size_t m_id;
    atomic<bool> &m_workingFinish;

    mutex & m_mtxWorker;
    mutex m_mtx;
    condition_variable & m_cvOpt;
    condition_variable m_cv;
    ACompany m_company;

    queue<shared_ptr<CFirmProblemPack>> m_queueSolvedPack;

    thread m_instThread;
    thread m_delivThread;


    void instalerThread(queue<shared_ptr<CFirmProblemPack>> &queueProblemPack) {
        size_t idProblemPack = 0;
        while(true) {
            AProblemPack newProblemPack = m_company->waitForPack();
            if (newProblemPack == nullptr) {
                break;
            }
            //push problemPack in queue and move work to worker
            {
                lock_guard<mutex> ul(m_mtxWorker);
                queueProblemPack.push(shared_ptr<CFirmProblemPack>(new CFirmProblemPack(m_id, newProblemPack)));
                m_cvOpt.notify_one();
            }
            idProblemPack++;
        }
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
                m_company->solvedPack(m_queueSolvedPack.front()->getSolvedPack());
                m_queueSolvedPack.pop();
                if(m_queueSolvedPack.empty() || !(m_queueSolvedPack.front()->getSolved())) {

                    break;
                }
            }

            if(m_queueSolvedPack.empty() && m_workingFinish) {
                lock.unlock();
                break;
            }
            lock.unlock();

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

    bool getCapacity() {
        return m_solver->hasFreeCapacity();
    }


    void newSolver() {
        m_solver = createProgtestSolver();
        m_containSolver.clear();
    }


    void addProblemPack(shared_ptr<CFirmProblemPack> problemPack) {        m_containSolver.push_back({problemPack, 0});
    }

    vector<pair<shared_ptr<CFirmProblemPack>, size_t>> getContainSolver() {
        return m_containSolver;
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
                if(m_solver->getCapacity() && !(m_queueProblemPack.empty())) {
                    m_solver->addProblemPack(m_queueProblemPack.front());
                }
            }
        }
    }


    void solvingSpecificProblem(unique_lock<mutex> &lock) {
        fillingPogtestSolver();

        if((m_solver->getCapacity()  && !(m_queueProblemPack.empty())) || (m_solver->getCapacity() && !m_instalFinish)) {
            lock.unlock();
            return ;
        }

        vector<pair<shared_ptr<CFirmProblemPack>, size_t>> containSolver = m_solver->getContainSolver();
        AProgtestSolver solver = m_solver->getSolver();
        m_solver->newSolver();
        m_cv.notify_one();

        lock.unlock();
        solver->solve();

        for(size_t i = 0; i < containSolver.size(); ++i) {
            containSolver[i].first->deliveredSolvingProblem(containSolver[i].second);
            if(containSolver[i].first->getSolved2()) {
                m_companies[containSolver[i].first->getFirmId()]->notifyDeliver();
            }
        }
    }

    void working() {
        while(true) {
            unique_lock<mutex> lock(m_mtxWorking);
            m_cv.wait(lock, [this] {return !m_queueProblemPack.empty() || m_instalFinish; });


            if (m_queueProblemPack.empty() && m_instalFinish) {
                lock.unlock();
                break;
            }
            solvingSpecificProblem(lock);
        }
    }

    void start(int threadCount) {
        for(int i = 0; i < threadCount; i++) {
            m_threads.emplace_back(&COptimizer::working, this);
        }

        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->createCommunicateTread(m_queueProblemPack);
        }
    }

    void stopInstallers(void) {
        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->getInstaler().join();
        }
    }

    void stopWorkers(void) {
        {
            lock_guard<mutex> lock(m_mtxWorking);
            m_instalFinish = true;
            m_cv.notify_all();
        }
        for(size_t i = 0; i < m_threads.size(); ++i) {
            m_threads[i].join();
        }
        m_workingFinish = true;
    }

    void stopDelivers(void) {
        for(size_t i = 0; i < m_companies.size(); ++i) {
            m_companies[i]->notifyDeliver();
            m_companies[i]->getDelivered().join();
        }
    }

    void stop(void) {
        stopInstallers();

        stopWorkers();

        stopDelivers();
    }

    void addCompany(ACompany company) {
        m_companies.emplace_back(shared_ptr<CFirm>(new CFirm(m_numOfFirm, m_workingFinish, company, m_mtxWorking, m_cv)));
        m_numOfFirm++;
    }

private:
    size_t m_numOfFirm;
    bool m_instalFinish;
    atomic<bool> m_workingFinish;

    mutex m_mtxWorking;
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
    optimizer.addCompany(company);
    optimizer.start(4);
    optimizer.stop();
    if (!company->allProcessed())
        throw std::logic_error("(some) problems were not correctly processsed");
    return 0;
}
#endif /* __PROGTEST__ */

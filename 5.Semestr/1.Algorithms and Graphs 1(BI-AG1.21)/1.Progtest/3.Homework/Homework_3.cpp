#ifndef __PROGTEST__

#include <iomanip>
#include <memory>
#include <limits>
#include <algorithm>
#include <bitset>
#include <list>
#include <vector>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
#include <queue>

using Price = unsigned long long;
using Employee = size_t;
inline constexpr Employee NO_EMPLOYEE = -1;
using Gift = size_t;

#endif

using namespace std;

void fillingGrafOfEmployee(vector<vector<Employee>> &grafOfEmployee,
                           vector<Employee> &rootEmployee,
                           const std::vector<Employee> &boss) {
    for (size_t i = 0; i < boss.size(); i++) {
        if (boss[i] == NO_EMPLOYEE) {
            rootEmployee.push_back(i);
            continue;
        }

        grafOfEmployee[boss[i]].push_back(i);
    }
}

void fillGiftInEmpl(const std::vector<Price> &gift_price,
                    vector<Price> &newGifted) {
    for (Price i = 0; i < gift_price.size(); i++) {
        newGifted[i] = gift_price[i];
    }
}

Employee returnSmallestIndex(const vector<Price> &gifts, Employee ignoredInd) {
    Employee smallestInd = numeric_limits<Price>::max();;
    Price smallestPrice = numeric_limits<Price>::max();;

    for (Employee i = 0; i < gifts.size(); i++) {
        if (i == ignoredInd) {
            continue;
        }
        if (smallestPrice > gifts[i]) {
            smallestPrice = gifts[i];
            smallestInd = i;
        }
    }

    return smallestInd;
}

Employee sumSubordinate(const vector<Employee> &curBoss, Employee ind,
                        const vector<vector<Price>> &prescribedGifts) {
    Employee sum = 0;
    for (Employee i = 0; i < curBoss.size(); i++) {
        sum += prescribedGifts[curBoss[i]][returnSmallestIndex(prescribedGifts[curBoss[i]], ind)];
    }

    return sum;
}

void fillGiftInEmplBoss(const std::vector<Price> &gift_price,
                        vector<Price> &newGifted,
                        const vector<Employee> &curBoss,
                        const vector<vector<Price>> &prescribedGifts) {
    for (Price i = 0; i < gift_price.size(); i++) {
        Price subordinateSumPrice = sumSubordinate(curBoss,
                                                   i,
                                                   prescribedGifts);

        newGifted[i] = subordinateSumPrice + gift_price[i];
    }
}

std::pair<Price, std::vector<Gift>> optimize_gifts(
        const std::vector<Employee> &boss,
        const std::vector<Price> &gift_price) {
    std::pair<Price, std::vector<Gift>> result(0, boss.size());

    vector<vector<Employee>> grafOfEmployee(boss.size());
    vector<vector<Price>> prescribedGifts(boss.size(), vector<Price>(gift_price.size()));
    vector<Employee> rootEmployee;
    vector<bool> visited(boss.size(), false);

    fillingGrafOfEmployee(grafOfEmployee, rootEmployee, boss);

    for (Employee i = 0; i < rootEmployee.size(); i++) {
        stack<Employee> stackQue;
        stackQue.push(rootEmployee[i]);

        while (!stackQue.empty()) {
            Employee curEmpl = stackQue.top();
            vector<Employee> curBoss = grafOfEmployee[curEmpl];

            if (!curBoss.empty() && !visited[curEmpl]) {
                for (const auto &employee: curBoss) {
                    stackQue.push(employee);
                }
            } else {
                if (curBoss.empty()) {
                    fillGiftInEmpl(gift_price, prescribedGifts[curEmpl]);
                } else {
                    fillGiftInEmplBoss(gift_price, prescribedGifts[curEmpl], curBoss, prescribedGifts);
                }

                stackQue.pop();
            }

            visited[curEmpl] = true;

        }
    }

    vector<vector<Employee>> ignIndEmpl(boss.size(), vector<Employee>(1));

    for (Employee i = 0; i < rootEmployee.size(); i++) {
        ignIndEmpl[rootEmployee[i]][0] = gift_price.size();
        result.first += prescribedGifts[rootEmployee[i]][returnSmallestIndex(prescribedGifts[rootEmployee[i]], gift_price.size())];
        queue<Employee> que;
        que.push(rootEmployee[i]);

        while (!que.empty()) {
            Employee curEmpl = que.front();
            que.pop();
            vector<Employee> curBoss = grafOfEmployee[curEmpl];

            Employee ignInd = returnSmallestIndex(prescribedGifts[curEmpl] ,ignIndEmpl[curEmpl][0]);
            result.second[curEmpl] = ignInd;

            for (Employee j = 0; j < curBoss.size(); j++) {
                que.push(curBoss[j]);
                ignIndEmpl[curBoss[j]][0] = ignInd;

            }

        }

    }

    return result;
}

#ifndef __PROGTEST__

const std::tuple<Price, std::vector<Employee>, std::vector<Price>> EXAMPLES[] = {
        { 17, {1,2,3,4,NO_EMPLOYEE}, {25,4,18,3} },
        { 16, {4,4,4,4,NO_EMPLOYEE}, {25,4,18,3} },
        { 17, {4,4,3,4,NO_EMPLOYEE}, {25,4,18,3} },
        {24, {4, 4, 3, 4, NO_EMPLOYEE, 3, 3}, {25, 4, 18, 3}},
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Test failed: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool test(Price p, const std::vector<Employee> &boss, const std::vector<Price> &gp) {
    auto &&[sol_p, sol_g] = optimize_gifts(boss, gp);
    CHECK(sol_g.size() == boss.size(),
          "Size of the solution: expected %zu but got %zu.", boss.size(), sol_g.size());

    Price real_p = 0;
    for (Gift g: sol_g) real_p += gp[g];
    CHECK(real_p == sol_p, "Sum of gift prices is %llu but reported price is %llu.", real_p, sol_p);

    if (0) {
        for (Employee e = 0; e < boss.size(); e++) printf(" (%zu)%zu", e, sol_g[e]);
        printf("\n");
    }

    for (Employee e = 0; e < boss.size(); e++)
        CHECK(boss[e] == NO_EMPLOYEE || sol_g[boss[e]] != sol_g[e],
              "Employee %zu and their boss %zu has same gift %zu.", e, boss[e], sol_g[e]);

    CHECK(p == sol_p, "Wrong price: expected %llu got %llu.", p, sol_p);

    return true;
}

#undef CHECK

int main() {
    int ok = 0, fail = 0;
    for (auto &&[p, b, gp]: EXAMPLES) (test(p, b, gp) ? ok : fail)++;

    if (!fail) printf("Passed all %d tests!\n", ok);
    else printf("Failed %d of %d tests.", fail, fail + ok);
}

#endif



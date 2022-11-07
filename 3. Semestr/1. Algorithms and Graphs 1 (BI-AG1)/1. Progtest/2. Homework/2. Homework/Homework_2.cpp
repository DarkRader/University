#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>

#endif

// TODO implement
template < typename Product >
struct Bestsellers {
  // The total number of tracked products
  size_t products() const;

  void sell(const Product& p, size_t amount)
  {
      
  }

  // The most sold product has rank 1
  size_t rank(const Product& p) const;
  const Product& product(size_t rank) const;

  // How many copies of product with given rank were sold
  size_t sold(size_t rank) const;
  // The same but sum over interval of products (including from and to)
  // It must hold: sold(x) == sold(x, x)
  size_t sold(size_t from, size_t to) const;

  // Bonus only, ignore if you are not interested in bonus
  // The smallest (resp. largest) rank with sold(rank) == sold(r)
  size_t first_same(size_t r) const { return 0; }
  size_t last_same(size_t r) const { return 0; }
};

#ifndef __PROGTEST__

void test1() {
  Bestsellers<std::string> T;
  T.sell("coke", 32);
  T.sell("bread", 1);
  assert(T.products() == 2);
  T.sell("ham", 2);
  T.sell("mushrooms", 12);

  assert(T.products() == 4);
  assert(T.rank("ham") == 3);
  assert(T.rank("coke") == 1);
  assert(T.sold(1, 3) == 46);
  assert(T.product(2) == "mushrooms");

  T.sell("ham", 11);
  assert(T.products() == 4);
  assert(T.product(2) == "ham");
  assert(T.sold(2) == 13);
  assert(T.sold(2, 2) == 13);
  assert(T.sold(1, 2) == 45);
}

void test2() {
# define CATCH(expr) \
  try { expr; assert(0); } catch (const std::out_of_range&) { assert(1); };

  Bestsellers<std::string> T;
  T.sell("coke", 32);
  T.sell("bread", 1);

  CATCH(T.rank("ham"));
  CATCH(T.product(3));
  CATCH(T.sold(0));
  CATCH(T.sold(9));
  CATCH(T.sold(0, 1));
  CATCH(T.sold(3, 2));
  CATCH(T.sold(1, 9));

#undef CATCH
}

int main() {
  test1();
  test2();
}

#endif



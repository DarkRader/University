#include "CEnvironment.h"
#include "CItem.h"
#include "CCommonExplosive.h"
#include "CDangerousExplosive.h"
#include "CWarehouse.h"
#include <cassert>
#include <sstream>
#include <string_view>

template<typename T>
static void testOpOut(const T & item, std::string_view ref) {
    std::stringstream ss;
    ss << item;
    assert(ss.str() == ref);
}

static void testCItem() {
    CItem i1 ("Golden globe");
    assert(!i1.canExplode({25, true}));
    assert(!i1.canExplode({250, true}));
    assert(!i1.canExplode({2500, true}));
    assert(!i1.canExplode({2500, false}));
    testOpOut(i1, "Golden globe");
    const CItem & ci1 = i1;
    assert(!ci1.canExplode({25, true}));
    assert(!ci1.canExplode({250, true}));
    assert(!ci1.canExplode({2500, true}));
    assert(!ci1.canExplode({2500, false}));
    testOpOut(ci1, "Golden globe");
}

static void testCDangerousExplosive() {
    CDangerousExplosive i4("Chicony keyboard");
    assert(i4.canExplode({25, true}));
    assert(i4.canExplode({250, true}));
    assert(i4.canExplode({2500, true}));
    assert(!i4.canExplode({2500, false}));
    testOpOut(i4, "Chicony keyboard [!]");
}

static void testCDangerousExplosivePolymorphism() {
    CDangerousExplosive i5("Chicony keyboard");
    CItem & i6 = i5;
    assert(i6.canExplode({25, true}));
    assert(i6.canExplode({250, true}));
    assert(i6.canExplode({2500, true}));
    assert(!i6.canExplode({2500, false}));
    testOpOut(i6, "Chicony keyboard [!]");
}

static void testCCommonExplosive() {
    CCommonExplosive i2("C4", 730);
    assert(!i2.canExplode({25, true}));
    assert(!i2.canExplode({250, true}));
    assert(i2.canExplode({2500, true}));
    assert(i2.canExplode({2500, false}));
    testOpOut(i2, "C4 [critical temp: 730]");
}

static void testCCommonExplosivePolymorphism() {
    CCommonExplosive i2("C4", 730);
    CItem & i3 = i2;
    assert(!i3.canExplode({25, true}));
    assert(!i3.canExplode({250, true}));
    assert(i3.canExplode({2500, true}));
    assert(i3.canExplode({2500, false}));
    testOpOut(i3, "C4 [critical temp: 730]");
}

static void testCWarehouse() {
    CWarehouse w("Top secret warehouse");
    testOpOut(w, "Top secret warehouse [0]");
    assert(!w.canExplode({25, true}));
    assert(!w.canExplode({250, true}));
    assert(!w.canExplode({2500, true}));
    assert(!w.canExplode({2500, false}));
    w.addItem(new CItem("Golden globe"));
    testOpOut(w, "Top secret warehouse [1]");
    assert(!w.canExplode({25, true}));
    assert(!w.canExplode({250, true}));
    assert(!w.canExplode({2500, true}));
    assert(!w.canExplode({2500, false}));
    w.addItem(new CCommonExplosive("Holy hand grenade", 50));
    testOpOut(w, "Top secret warehouse [2]");
    assert(!w.canExplode({25, true}));
    assert(w.canExplode({250, true}));
    assert(w.canExplode({2500, true}));
    assert(w.canExplode({2500, false}));
    w.addItem(new CDangerousExplosive("Hydrogen"));
    testOpOut(w, "Top secret warehouse [3]");
    assert(w.canExplode({25, true}));
    assert(w.canExplode({250, true}));
    assert(w.canExplode({2500, true}));
    assert(!w.canExplode({25, false}));
    assert(w.canExplode({2500, false}));
}

static void testCWarehousePolymorphism() {
    CWarehouse w("Top secret warehouse");
    CItem & i = w;
    testOpOut(i, "Top secret warehouse [0]");
    assert(!i.canExplode({25, true}));
    assert(!i.canExplode({250, true}));
    assert(!i.canExplode({2500, true}));
    assert(!i.canExplode({2500, false}));
    w.addItem(new CItem("Golden globe"));
    testOpOut(i, "Top secret warehouse [1]");
    assert(!i.canExplode({25, true}));
    assert(!i.canExplode({250, true}));
    assert(!i.canExplode({2500, true}));
    assert(!i.canExplode({2500, false}));
    w.addItem(new CCommonExplosive("Holy hand grenade", 50));
    testOpOut(i, "Top secret warehouse [2]");
    assert(!i.canExplode({25, true}));
    assert(i.canExplode({250, true}));
    assert(i.canExplode({2500, true}));
    assert(i.canExplode({2500, false}));
    w.addItem(new CDangerousExplosive("Hydrogen"));
    testOpOut(i, "Top secret warehouse [3]");
    assert(i.canExplode({25, true}));
    assert(i.canExplode({250, true}));
    assert(i.canExplode({2500, true}));
    assert(!i.canExplode({25, false}));
    assert(i.canExplode({2500, false}));
}

static void testCWarehousePolymorphismRecursion() {
    CWarehouse w("Top secret warehouse");
    CWarehouse * w2 = new CWarehouse("Bottom secret warehouse");
    w2->addItem(new CDangerousExplosive("Something that should not be leaked"));
    w.addItem(w2);
    testOpOut(w, "Top secret warehouse [1]");
    assert(w.canExplode({25, true}));
    assert(!w.canExplode({25, false}));
}

int main() {
    testCItem();
    testCDangerousExplosive();
    testCDangerousExplosivePolymorphism();
    testCCommonExplosive();
    testCCommonExplosivePolymorphism();
    testCWarehouse();
    testCWarehousePolymorphism();
    testCWarehousePolymorphismRecursion();
    return 0;
}

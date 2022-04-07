#include "CEnvironment.h"
#include "CSafeItem.h"
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

static void testCSafeItem() {
    CSafeItem i1("Golden globe");
    assert(!i1.canExplode({25, true}));
    assert(!i1.canExplode({250, true}));
    assert(!i1.canExplode({2500, true}));
    assert(!i1.canExplode({2500, false}));
    testOpOut(i1, "Golden globe");
    const CSafeItem & ci1 = i1;
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
    CSafeItem & i6 = i5;
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
    CSafeItem & i3 = i2;
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
    w.addItem(new CSafeItem("Golden globe"));
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
    CSafeItem & i = w;
    testOpOut(i, "Top secret warehouse [0]");
    assert(!i.canExplode({25, true}));
    assert(!i.canExplode({250, true}));
    assert(!i.canExplode({2500, true}));
    assert(!i.canExplode({2500, false}));
    w.addItem(new CSafeItem("Golden globe"));
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

/*static void testAbstractCItem() {
    static_assert(!std::is_base_of_v<CSafeItem, CCommonExplosive>, "CCommonExplosive should not descend from CSafeItem");
    static_assert(!std::is_base_of_v<CSafeItem, CDangerousExplosive>, "CDangerousExplosive should not descend from CSafeItem");
    static_assert(!std::is_base_of_v<CSafeItem, CWarehouse>, "CWarehouse should not descend from CSafeItem");
    //static_assert(std::has_virtual_destructor_v<CItem>, "CItem does not have virtual destructor!");
    //static_assert(std::is_abstract_v<CItem>, "CItem is not abstract!");
}*/

/*static void testCWarehousePolymorphismCopy() {
    CWarehouse w1("Top secret warehouse");
    w1.addItem(new CDangerousExplosive("I can crash your program if not copied properly!"));
    assert(w1.canExplode({25, true}));
    assert(!w1.canExplode({25, false}));
    CWarehouse w2 = w1;
    assert(w2.canExplode({25, true}));
    assert(!w2.canExplode({25, false}));
}*/

/*static void testEquals() {
    CWarehouse w1("Top secret warehouse");
    w1.addItem(new CDangerousExplosive("I can crash your program if not copied properly!"));
    CWarehouse w2 = w1;
    CWarehouse w3("Some empty warehouse");
    CWarehouse w4("Another secret warehouse");
    w4.addItem(new CDangerousExplosive("I can crash your program if not copied properly!"));
    CWarehouse w5("Top secret warehouse");
    w5.addItem(new CDangerousExplosive("I can crash your program if not copied properly!"));
    CWarehouse w6("Top secret warehouse");
    w6.addItem(new CSafeItem("Some different item."));
    assert(w1.equals(w2));
    assert(!w1.equals(w3));
    assert(!w1.equals(w4));
    assert(w1.equals(w5));
    assert(!w1.equals(w6));
    assert(w2.equals(w1));
    assert(!w3.equals(w1));
    assert(!w4.equals(w1));
    assert(w5.equals(w1));
    assert(!w6.equals(w1));
    const CItem & ci1 = w1;
    const CItem & ci2 = w2;
    const CItem & ci3 = w3;
    const CItem & ci4 = w4;
    const CItem & ci5 = w5;
    const CItem & ci6 = w6;
    assert(ci1.equals(ci2));
    assert(!ci1.equals(ci3));
    assert(!ci1.equals(ci4));
    assert(ci1.equals(ci5));
    assert(!ci1.equals(ci6));
    assert(ci2.equals(ci1));
    assert(!ci3.equals(ci1));
    assert(!ci4.equals(ci1));
    assert(ci5.equals(ci1));
    assert(!ci6.equals(ci1));
    w1.addItem(new CDangerousExplosive("Human shallow mind"));
    assert(!w1.equals(w2));
    assert(!ci1.equals(ci2));
    w2.addItem(new CDangerousExplosive("Human shallow mind"));
    assert(w1.equals(w2));
    assert(ci1.equals(ci2));
    w1.addItem(new CCommonExplosive("Do not heat!", 100));
    assert(!w1.equals(w2));
    assert(!ci1.equals(ci2));
    w2.addItem(new CCommonExplosive("Do not heat!", 100));
    assert(w1.equals(w2));
    assert(ci1.equals(ci2));
    w1.addItem(new CCommonExplosive("Do not heat!", 100));
    w2.addItem(new CCommonExplosive("Do not heat!", 150));
    assert(!w1.equals(w2));
    assert(!ci1.equals(ci2));
}*/

int main() {
    testCSafeItem();
    testCDangerousExplosive();
    testCDangerousExplosivePolymorphism();
    testCCommonExplosive();
    testCCommonExplosivePolymorphism();
    testCWarehouse();
    testCWarehousePolymorphism();
    testCWarehousePolymorphismRecursion();
    //testAbstractCItem();
    //testCWarehousePolymorphismCopy();
    //testEquals();
    return 0;
}

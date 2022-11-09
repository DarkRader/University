##Množina pomocí BST II

Třída CTree realizuje strukturu „set“, samotné prkvy jsou řetězce. Implementace využívá BST. Vaším úkolem je doplnit metody pro vkládání a odstranění prvků a destruktor. Vyvažování stromu není potřeba. Zároveň se ukládá obousměrný spoják vložených prvků, který si ukládá pořadí jejich vložení. Třída má rozhraní:

konstruktor

Nastaven na default, není třeba ho měnit.
destruktor

Musí správně uvolnit paměť. Implementace je Váš úkol.
kopírující konstruktor

=delete, zakázán.
operator=

=delete, zakázán.
bool insert(string key)

Přidá do množiny prvek key, musí ho ve stromu přidat na správné místo. Porovnání se provádí relačními operátory stringu, lexikograficky, menší řetězce se ukládají do levého podstromu, větší do pravého. Také musí správně zpracovat a pamatovat si pořadí vkládání (proměnné m_First a m_Last). Vrací true pro úspěch nebo false, pokud již daný prvek existuje. Implementace je Váš úkol.
bool erase(string key)

Odstraní z množiny prvek key. Vrací true pro úspěch, false pokud prvek nebyl nalezen. Musí prvek odstranit ze stromu a zároveň ze spojového seznamu, který si hlídá pořadí - aktualizovat správně m_NextOrder a m_PrevOrder. Je potřeba zachovat vlastnosti stromu a zároveň i vzájemné pořadí ve spojovém seznamu. Implementace je Váš úkol.
m_Root

Pointer na CNode pro kořen stromu.
m_First

Pointer na CNode ukazující na první vložený prvek. Pomocí m_First → m_NextOrder .. → m_NextOrder → nullptr by mělo jít projít všechny prvky dle pořadí vložení.
m_Last

Pointer na CNode ukazující na poslední vložený prvek.
CNode

Pomocná třída pro uzel ve stromu. Obsahuje proměnné:
m_Key = string daného prvku.
m_L = pointer na levý podstrom, pokud neexistuje tak nullptr.
m_R = pointer na pravý podstrom, pokud neexistuje tak nullptr.
m_NextOrder = pointer na další prvek dle pořadí vložení, případně nullptr pro poslední prvek.
m_PrevOrder = pointer na předchozí prvek dle pořadí vložení, případně nullptr pro první prvek.

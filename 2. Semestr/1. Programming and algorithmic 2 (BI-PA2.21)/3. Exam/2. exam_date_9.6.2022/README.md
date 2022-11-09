##Tabulka pomocí BST

Vytvořte tabulku (mapu) za použití binárních vyhledávacích stromů bez vyvažování, klíčem i hodnotou je string. Umístění prvku ve stromu se odvozuje z lexikografického řazení klíčů (operator `>`). Konstruktor implementovaný od Ládi, kopírující konstruktor ani operátor přiřazení není nutno implementovat. Tabulka umožňuje vkládat prvky (vaše implementace) a navíc uchovávat pořadí jejich vložení. K tomu slouží ukazatel m_nextOrder v instanci CNode (tvoří spojový seznam) a ukazatele m_first, m_last v CTree.

Ukládaná data ve třídách:

CNode(string m_key, string m_val, CNode* m_L, CNode* m_R, CNode* m_nextOrder);

CTree(CNode* m_first, CNode* m_last, CNode* m_root);

Potřeba implementovat:

destruktor
bool insert(key, val)… vloží prvek na správné místo ve stromu, vrátí true v případě úspěchu (klíč ještě není ve stromu obsažen)
bool isSet(key)… vrátí true pro obsažený klíč
operator «… výpis párů (klíč, hodnota) podle pořadí vložení do tabulky


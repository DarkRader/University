##Hash Table I

Třída CHash realizuje datový typ tabulka, kde klíčem i hodnotou jsou řetězce. Tabulka pracuje jako hashovací tabulka, kolize jsou řešeny pomocí zřetězení záznamů. Úkolem je doplnit do třídy CHash metodu pro vkládání prvků a destruktor.

Třída CHash implementuje rozptylovací tabulku standartním způsobem. Navíc si ukládá i informace o pořadí vkládání jednotlivých dvojic (klíč, hodnota). Bude poskytovat následující rozhraní:

konstruktor
inicializuje instanci. Parametrem je velikost rozptylovací tabulky. Implementace je hotová v dodaném zdrojovém kódu, není potřeba/vhodné jej měnit.
destruktor
uvolní prostředky alokované instancí. Jeho implementace je Váš úkol
kopírující konstruktor
není v této úloze testován, v dodané implementaci je zakázán (= delete)
operátor =
není v této úloze testován, v dodané implementaci je zakázán (= delete)
Ins(key, val)
metoda přidá do tabulky zadaný pár řetězců (key, val). Metoda musí respektovat hashovací algoritmus, tedy přidat prvek do takové řádky tabulky, která odpovídá hash hodnotě klíče modulo velikost tabulky. Dále, naše implementace si pamatuje pořadí vklánání prvků do tabulky (viz členské proměnné m_FirstOrder a m_LastOrder níže), metoda Ins musí správně zpracovat i toto pořadí. Tabulka je organizovná tak, že kolidující klíče ukládá do spojového seznamu (zřetězení záznamů, vnější zřetězení, separate chaining). Návratoou hodnotou je true pro úspěch nebo false pro chybu (daný klíč už v tabulce existuje). Implementace této metody je Váš úkol.
IsSet
metoda zjistí, zda v tabulce existuje daný klíč. Metoda je implementovaná v dodaném zdrojovém kódu, není ji potřeba upravovat. Dodaný kód můžete použít pro testování správnosti vašich metod, případně si studiem této metody můžete připomenout fungování hash tabulky.
ForEach
metoda projde celou hash tabulku, pro každý prvek zavolá dodanou funkci/funktor/lambdu. Metoda prochází prvky v pořadí vkládání do tabulky. Implementace je k dispozici v dodaném zdrojovém kódu, demonstruje použití spojového seznamu m_NextOrder/m_PrevOrder.
hashFn(str, mod)
metoda vypočte hash kód pro daný řetězec str a velikost hash tabulky mod. Metodu použijte pro určení pozice v hash tabulce, kam budete vkládat nový pár (klíč, hodnota).
TItem
je pomocná struktura, která ukládá vlastní hodnoty v hash tabulce. Obsahuje:
m_Key - ukládaný klíč
m_Val - ukládaná hodnota patřící ke klíči
m_NextHash - ukazatel na jednosměrně zřetězený spojový seznam dvojic (klíč, hodnota) se stejným hash kódem. Spojový seznam začíná vždy na odpovídajícím indexu hashovací tabulky (m_Table) a končí hodnotou NULL. Pořadí prvků v tomto seznamu není omezeno.
m_NextOrder - ukazatel na další prvek ve spojovém seznamu, který udává pořadí vkládání hodnot do hash tabulky. m_NextOrder ukazuje na další prvek (tedy prvek vložený později), případně má hodnotu NULL pro poslední vložený prvek.
m_PrevOrder - ukazatel na předchozí prvek ve spojovém seznamu, který udává pořadí vkládání hodnot do hash tabulky. m_PrevOrder ukazuje na předchozí prvek (tedy prvek vložený dříve), případně má hodnotu NULL pro první vložený prvek.
m_Table
vlastní hash tabulka, realizovaná jako ukazatel na dynamicky alokované pole ukazatelů. Každý prvek této tabulky ukazuje na počátek spojového seznamu pro odpovídající hodnotu hash kódu.
m_Size
velikost tabulky m_Table
m_FirstOrder
ukazatel na první vložený prvek, postupnou iterací m_FirstOrder - m_NextOrder - m_NextOrder … NULL lze projít prvky v tabulce v pořadí vkládání (od nejdříve vloženého po nejpozději vložený)
m_LastOrder
ukazatel na poslední vložený prvek, postupnou iterací m_LastOrder - m_PrevOrder - m_PrevOrder … NULL lze projít prvky v tabulce v opačném pořadí vkládání (od nejpozději vloženého po nejdříve vložený)

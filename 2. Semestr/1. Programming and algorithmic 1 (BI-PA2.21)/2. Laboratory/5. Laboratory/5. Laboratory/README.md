# Zkoušení studentů podruhé

Na třetím cviku jsme si napsali jednoduché nafukovací pole studentů, a napsali si pro ně konstruktor a destruktor.

Naše řešení mělo však nějaké vady, a slíbili jsme, že se k němu vrátíme později. Dnes tak činíme.

Tím problémem je, že není možné seznam studentů zkopírovat. Dojde k různým chybám (odkomentujte si kód; na cvičení si ukážeme),
které budeme muset opravit tak, že doplníme kopírující konstruktor a operátor přiřazení.

K testování můžete využít příkazy `make run` a `make valgrind`.

## Kopírující konstruktor

* Jde o konstruktor, kterým lze inicializovat instanci třídy pomocí dat jiné již existující instance. Jeho parametrem je tato kopírovaná instance (jak se předá?).
* Volá se, když potřebujeme vytvořit kopii objektu.
* Nemusí být definován, kompilátor jej může vygenerovat za nás;
  - pak má ale jednoduché chování - prostě zkopíruje členské proměnné pomoci jejich kopírujících konstruktorů; snažíme se využívat již stávající řešení (STL kontejnery, řetězce, chytré pointery apod.)
  - a nepotřebujeme ani vlastní destruktor; plně se spoléháme na fungování členských proměnných
* Ne vždy nám musí stačit (když nestačí kopírující konstruktory členských proměnných)
  - náš objekt drží nějaký zdroj, který musíme spravovat (např. vlastní alokovanou paměť); pak musíme definovat svůj kopírující konstruktor, operátor přiřazení a destruktor
  - náš objekt z nějakého důvodu nechceme kopírovat (držený zdroj je unikátní, kopie je silně problematická, např. I/O, vlákna a synchronizační primitivy, data na GPU apod.); kopírující konstruktor a operátor přiřazení zakážeme, nicméně destruktor potřebujeme pořád;
  - v obou výše zmíněných případech musíme definovat vlastní destruktor a musíme říct, zda a případně jak lze objekt kopírovat... to je tzv. pravidlo tří

## Operátor kopírujícího přiřazení

* Musí být deklarován společně s kopírujícím konstruktorem. Pokud je deklarován jen kopírující konstruktor, operátor přiřazení je vypnut. To nechceme, držíme pravidlo tří.
* Abychom neduplikovali logiku kopírujícího konstruktoru, místo toho ji využijeme - vytvoříme kopii, a pak si s ní prohodíme členské proměnné. Tomu se říká copy & swap. (Alternativou je destroy & placement new, ale to je pro pokročilé borce, nebudeme si ukazovat.)
* Který speciální případ při přiřazování si musíme pohlídat?

## Přesouvací konstruktor a operátor přesunu

Jedním z pokročilejších konceptů, které se hodí znát, je tzv. přesouvání. Ne vždy chceme vytvářet kopie. Příklad: mám pole studentů, chci ho zvětšit, provádím realokaci. Alokuji tedy nové pole, a jednotlivé studenty překopíruji ze starého do nového. Při tom dochází k alokaci jednotlivých řetězců se jmény studentů (což se děje při kopírování stringů), a později při dealokaci starého pole dochází k dealokaci původních řetězců se jmény studentů. Jde o zbytečnou práci navíc, proto C++ od verze 11 umí kromě kopií tzv. přesouvání.

Přesouvání funguje tak, že zdrojovou instanci můžeme při vytváření nové instance vykrást, ale musíme ji samozřejmě uvést do takového stavu, aby její pozdější destrukce nepoškodila nás.

Abychom v C++ věděli, že dostáváme objekt, který můžeme takto vykrást, zavádí se tzv. reference na pravou stranu. Značí se `&&`, a když ji dostaneme jako parametr funkce, můžeme ji chápat jako referenci na objekt, který po vykonání naší funkce už nebude potřeba (a můžeme jej tedy vykrást) a bude se na něm dále v programu už jen volat destruktor. C++ preferuje referenci na pravou stranu před referencí na konstantu, pokud námi předávaný objekt zabalíme do volání std::move, případně pokud jde o objekt vytvořený na místě.

Příklad:

```c++
#include <string>
#include <iostream>

int main()
{
    std::string a = "Toto je velmi dlouhý řetězec, který nechci kopírovat";
    std::cout << a.data() << std::endl;
    std::cout << a << std::endl;
    std::string b(std::move(a)); // přesouvám a do b
    std::cout << a.data() << std::endl;
    std::cout << b.data() << std::endl;
    std::cout << a << std::endl; // toto bych správně neměl dělat, od a se očekává, že už se na něm bude jen volat destruktor
    std::cout << b << std::endl; // v b mám to, co bylo původně v a
    return 0;
}
```

V praxi se potom pravidlo tří rozšiřuje na pravidlo pěti. Pokud máme definovanou pouze kopírující část (pravidlo tří), přesouvací část neexistuje a nebude se používat (zredukuje se na kopii). Pokud necháme kopírování a přesun kompletně na kompilátoru, vygeneruje si je všechny sám s pomocí kopií a přesunů členských proměnných.

Implementace operátoru přesouvacího přiřazení využívá potom nikoliv copy & swap, ale move & swap. A samotný swap (funkce std::swap) se snaží využívat přesouvací operátory.

Dále, aby bylo přesouvání prakticky využitelné v algoritmech standardní knihovny (např. při kopírování ze starého pole do nového při jeho realokaci), je potřeba kompilátoru říct, že přesun nevyhodí žádnou výjimku (a samozřejmě musíme i reálně zaručit, že nevyhodí výjimku). To se dělá klíčovým slovem `noexcept`, které se píše za seznam parametrů funkce (podobně jako `const`).

Ve standardní knihovně existuje řada tříd, které mají zakázané kopie, ale mají povolené přesuny, a je to žádoucí chování. Týká se to např. I/O proudů nebo chytrého pointeru unique_ptr. Obecně se takové nastavení hodí všude tam, kde instance třídy spravuje nějaký unikátní zdroj.

## Další kroky

Pokud nechceš teď řešit řetězec, možná by bylo fajn seznámit se s pár dalšími kamarády ze standardní knihovny.

`std::vector` a `std::string` už znáš. Ale bylo by fajn podívat se na nějaké algoritmy.

### Řazení studentů (std::sort, std::stable_sort)

Přidej výpis studentů a přidej použití `std::sort` k řazení pole (např. vymysli metodu `CList::sort`). Co potřebuje `std::sort` (a spousta dalších algoritmů)?

Potřebuje tzv. iterátory. Můžeme je chápat jako pointery. Všimni si, že třída CList v sobě definuje vlastní datové typy, `iterator` a `const_iterator`. Mohou to být třídy, my však nepotřebujeme žádné speciální schopnosti, takže se spokojíme se synonymy k pointerům. Reálně iterátor, aby fungoval pro sekvenční průchod, musí umět preinkrement, `==`, `!=` a dereferenci. Pro řazení musí umět trochu víc; hledej iterátor s náhodným přístupem (RandomAccessIterator). Proto nám zde v základu stačí ty pointery.

Všimni si také, že nabízíme hned dvojí iterátory - const a neconst verzi. Naprosto stejně to mají i kontejnery ve standardní knihovně.

Většina algoritmů dostává jako první dva parametry dva iterátory, které vymezují rozsah vstupních dat. První je počáteční (lze si jej představit jako pointer na začátek pole), druhý je koncový (pointer za konec pole).

Algoritmy mohou dostávat i další parametry, podle potřeby. Aby např. `std::sort` mohl řadit, musí vědět, jak má porovnávat prvky. Pokud nedodáme vlastní funkci, použije se `operator <` na procházených prvcích. Hodí se tedy buď vlastní funkce, nebo vlastní přetížení operátoru <.

A mimochodem, jak se od `std::sort` liší `std::stable_sort`?

### std::tie

K implementaci porovnání studentů operátorem < se může hodit třída `std::tie`, která představuje nějakou n-tici (složenou z referencí); n-tice stejných sestav typů lze jednoduše lexikograficky porovnat (tzn. po částech; std::tie má takto přetížené porovnávací operátory), což lze využít k jednoduché implementaci porovnání pro vlastní typy.

### Vkládání studentů do seřazeného pole (std::lower_bound)

Přidej metodu `CList::insert_student`, která vloží studenta do seřazeného pole studentů (předpokládej, že je seřazené). Jak nalézt pozici, kam vložit studenta? Hodilo by se binární vyhledávání. V C k tomu sloužila funkce `bsearch`, která ale sloužila čistě k hledání. V C++ máme krásnou funkci `std::lower_bound`, která umí krásně najít místo, kam vložit hledaný prvek, i když student neexistuje.

Co přesně `std::lower_bound` potřebuje? No... bude na tom velmi podobně jako `std::sort`.

A vzhledem k povaze parametrů... v jaké podobě bude `std::lower_bound` vracet výslednou pozici?

### Výpis studentů pozpátku (pro pokročilé!)

Přidej metody `CList::rbegin` a `CList::rend`, které budou vracet iterátor chodící pozpátku. Zde už nebude stačit pouhé synonymum k pointeru, ale je potřeba vlastní třída (tu je možné definovat uvnitř třídy CList) s vlastními overloady operátorů.

Metody pro průchod pozpátku není možné jednoduše využít (to je pro ještě pokročilejší!) v ranged for cyklu. Ale pořád je lze využít v klasickém cyklu `for(auto it = student_list.rbegin(); it != student_list.rend(); ++it)`

# Šablony

## Algoritmus bubble sort

Spousta algoritmů ve standardní knihovně je implementována jako šablona; nejčastěji se šablonují typy iterátorů

* Jak bude vypadat šablona funkce, která bude jako parametr brát dva iterátory stejného typu?
* Napište algoritmus bubble sort pomocí iterátorů. Předpokládejte, že máte u iterátorů k dispozici pouze operátory `++`, `*`, `==` a `!=`, dále, že výraz `*it` vrací objekt, který můžete prohodit s jiným pomocí `std::swap` a který můžete porovnat s jiným pomocí operátoru `<`

```
...
void bubbleSort(... begin, ... end) {
    ...
}
```

* Ověřte, že funkce řadí na vectoru i na obyčejném poli (pamatujete, že iterátory můžete chápat jako obyčejné pointery?), že umí řadit čísla i řetězce, a že umí i seřadit písmena v řetězci

## Rozšíření o komparátor

Přidejte funkci `bubbleSort` třetí parametr jiného typu, který budeme používat jako komparátor pro řazené prvky. Můžete se inspirovat hlavičkou některých algoritmů ze standardní knihovny, např. `std::sort`

* Jako výchozí hodnotu třetího parametru použijte `std::less`, podobným způsobem jako se to dělá ve standardní knihovně.
* Prozkoumejte `std::less`. Co to je, a co umí?
* Využijte tento komparátor při porovnávání v rámci bubble sortu.
* Ověřte, že volání funguje např. pro `std::greater` (bude řadit sestupně)

## Převod funkce na třídu

Z funkce `bubbleSort` vytvořte třídu `CBubbleSorter`. Komparátor bude uložen do členské proměnné při konstrukci.

* Předpokládejme, že komparátor nemá výchozí konstruktor (např. jde o lambda funkci, což ale teď nemusíte vědět, co je). Pořád ale má kopírující konstruktor. Jak musí vypadat konstruktor třídy `CBubbleSorter`?
* Jak nasimulujete typ, který nemá výchozí () konstruktor?
* K provádění bubble sortu přetěžte ve třídě operátor volání funkce.

## Zásady práce s šablonami

* Hlídejte si, co požadujete od typů, které využíváte ve svých šablonách.
* Velice snadno se zapomíná na to, že šablona využívá operátor přiřazení, implicitní konstruktor a kopírující konstruktor.
* K ověření toho, že šablona dodržuje stanovená omezení si připravte minimalistické typy, které umí jen úzce definované operace:
* Konstruktory, destruktory a operátory přiřazení lze zakazovat (v PA2 si destruktory nezakazujeme, i v praxi je to velmi vzácné) pomocí slůvka `delete`, případně lze využít toho, že při definici nekopírujícího konstruktoru zaniká výchozí () konstruktor.  
* Šablonu nedělte do h/cpp souborů; sice to nějakým velmi pracným způsobem lze, ale má to řadu omezení a celkově je to spíše kontraproduktivní.

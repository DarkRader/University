# Skladiště

Třídy skladiště z minulého cvičení trochu upravíme.

## Lepší hierarchie tříd

Ne vždy je vhodné předpokládat, že každá věc ve skladišti odvozuje své chování od nějaké konkrétní věci.

Přepišme hierarchii tříd na využití abstraktní třídy `CItem`. (Mezi týdny jsem původní `CItem` přejmenoval na `CSafeItem`.)

* Co je abstraktní třída?
* Co je `pure virtual` metoda?
* Kdy lze volat konstruktor abstraktní třídy?

## Kopírování předmětů

Chtěli bychom zařídit, abychom byli schopní zkopírovat skladiště tak, aby se správně zkopírovaly i předměty.

* Je řešením použít chytrý pointer `shared_ptr`?
* Může být definován virtuální kopírující konstruktor?
* Jak udělat něco podobného, a to využít?
  * Zkusíme nejprve otrocky se skladištěm obyčejných pointerů a správnou implementací pravidla tří.
  * Potom si zkusíme upravit `unique_ptr`, aby kopírování zařídil za nás.

## RTTI

Za normálních okolností se snažíme maximálně využívat virtuálních metod. Tak by se to mělo dělat _správně_. Ale omezení dynamické vazby pouze na případ, kdy se volá metoda na nějakém polymorfním objektu, způsobuje některé problémy s plným využitím polymorfismu v C++.

Můžeme např. chtít zařídit nějakou spolupráci dvou polymorfních tříd, a tato spolupráce může vypadat různě podle toho, o jaké třídy konkrétně jde. A moc rozumných možností nám jazyk C++ v aktuálním stavu nedává.

Možnosti:

* Vymyslet nějaké společné rozhraní, kterým by si dokázaly všechny implementace daných abstraktních tříd předat potřebné informace. Např.:
    * Když budu mít kružnici a přímku; a budu chtít řešit, zda se protínají, společným rozhraním mohou být nějaké algebraické rovnice
    * Když násobím matice v různých reprezentacích, společným rozhraním mohou být přístupy k prvkům
    * atd.
    * Tak by se to pokud možno dělat mělo; ne vždy je lehké takové společné rozhraní vymyslet, a ne vždy to lze a ne vždy to dává smysl;
* `match` - asi nejhezčí způsob, navrženo v [P1371R1](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1371r1.pdf), velmi vážně diskutováno, všichni se moc těšíme, bohužel zatím stále nebylo oficiálně zařazeno do žádné budoucí normy (ale existují knihovny, které tuto funkcionalitu emulují)
* Multiple dispatch. Ukázali jsme si už minule princip dispatchingu pro vypisovací operátor, kdy jsme polymorfní objekt dostali jako parametr funkce, a provedli jsme dynamickou vazbu (dispatching) pomocí volání virtuální metody `print` na dodaném objektu. Tento princip lze samozřejmě používat opakovaně a postupně dynamicky vázat jednotlivé parametry. Funguje to, je to čisté využití polymorfismu, dělá se to (někdy), ale zároveň je to trochu nepraktické pro rozšiřitelnost. Posuďte příklad s protínáním čtverců a kružnic:

```c++
class CShape {
    public:
    // toto ještě jde...
    virtual bool instersects(const CShape & other) const;
    // a zde to už bude ošklivé...
    virtual bool instersectsCircle(const class CCircle & other) const;
    virtual bool instersectsSquare(const class CSquare & other) const;
    // ^ tyto tři metody se mohly jmenovat stejně;
    // kompilátor by je od sebe rozlišil díky typům parametrů
};

class CCircle : public CShape {
    public:
    bool instersects(const CShape & other) const override {
        // dispatch...
        return other.instersectsCircle(*this);
    }
    bool instersectsCircle(const class CCircle & other) const override;
    bool instersectsSquare(const class CSquare & other) const override;
};

class CSquare : public CShape {
    public:
    bool instersects(const CShape & other) const override {
        // dispatch...
        return other.instersectsSquare(*this);
    }
    bool instersectsCircle(const class CCircle & other) const override;
    bool instersectsSquare(const class CSquare & other) const override;
};

// a teď přidáme class CLine : public CShape...
```

* Využití RTTI. Poslední zoufalá možnost, kterou byste měli šetřit. Vlastně tím přiznáváte, že si s polymorfismem nevíte moc rady. Pro některé případy je však efektivní a nejpřehlednější (a zrovna v našem dnešním cvičení se bude hodit dobře). Zkusíme si to v implementaci virtuální metody equals() pro porovnání nebezpečných předmětů.

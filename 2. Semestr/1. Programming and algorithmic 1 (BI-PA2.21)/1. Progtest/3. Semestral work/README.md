# Kalkulačka s neomezenou přesností

## Zadání

Můj úkol bude realizovat kalkulačlu s neomezenou přesností. Kalkulačka bude schopná pracovat s celými i desetinnými čísly a vypolňovat základní operace: sčítaní, odsčítaní, násobení a dělení, ale jen pro celé čísla (bude brát v úvahu zbytek). Navíc kalkulačka bude moct nejen provadět operace s čísly i zároveň zapsat výsledek do proměnné a pak využit proměnné ve výpočtu.

Uživatel může v době použítí kalkulačkou použít jakýkoli z navrhovaných operatoru pro operací popsané výše: `+`, `-`, `*`, `/`, `()`, přičemž závorky můžou být ve výrazu libovolně vnořené.

Aby kalkulačka byla více užitečná uživatel může uložit ji stav (například proměnné a historií) do souboru a v případě potřebe znovu načíst.

## Specifikace

Podle mé představy stahovaní bude fungovat tak, že užívatel může snadno stahnout všichni operaci, a tí zapíšou do odděleného souboru přesné tak, jak bylo zapsáno do kalkulačky(to bude zapsán do souboru současně při zápisu do kalkulačky, aby se všechny tyto údaje nebyli uloženy v paměti), pak přínačtení znovu program bude zpracovat stažený soubor stejně jak to dělal při zpracovaní s užívatelem. Přitom při načtení program zapíse promenné do svých objektu v třídech, aby dál mohl s nimi pracovat.

Program nebude použivat žadný grafické rozhraní a všichni operace budou zpracovány přímo v terminálu. Pokud uživatel bude chtít stahnout historku kalkulačky(pro to potřebuje jen propsát commandu stahnout), udělám program tak, aby všichni stažený soubory byli ukladány do "sourses" programy . Naopak, v případě, že uživatel bude chtít načíst soubor s historkou, bude stačít jen nápsat uložený soubor

Program potřebuje parsovat data, aby vědet s čím musí pracovat a s jaké třídy bude volat pro další práci. Protože uživatel může psát cokoliv v terminalu, program bude muset detekovat a výpisovat chybu, pokud syntaxe nebude správně nápsana. Na začatku programy bude nápsano co uživatel musí psát, aby kalsulačka fungovala spravně.

# Polimorfismus

V mém programu budu přepokladat použít jedmu hierarchie tříd, které budou splňovat podmínky na polimorfismus. Konkrétně některé třídy budou pracovat s cislami jsou poměrně velké a jiné pracovat s obrovskými čísly.

## Poměrně velké čísla

V této skupině tříd budu mít rodičovsku třídu (`CDataSize`) a dvě zdědiné třídy(`CInteger` a `CFloat`), které budou reprezentovat typ, s kterým program bude pracovat. Konkřetně budu mít v programu dva takzvaných typu: celé čísla(prezentovány pomocí long long int), desetinné čísla(prezentovány pomocí dva čísla long long int pro čelé čísla a také long long int pro čisla po čarce). To není typy dat doslova, ale spíše mé vlastní type dat, kterými budou jmenovat třídy. V každé zdědiné třídě budou výpočitat čísla svým způsobem, ale navíc výsledek po operacích bude ukladat svůj výsledek do promměnných rodičovské třídy(pro int a float respektive), aby možné bylo ji použít dál při výpočtu. Počty budou probíhat za pomoci operátorů `+`, `-`, `*`, `/`(jen pro celé čísla), které budou virtualní v rodičovské třídě a přepsany v zdědiných třídech. Všechna táto skupina může pracovat jen s omezenými číslami, pokud dovoluje typ long long int. Větší čísla budou vyžadovat vector long long int s vícema instacémi

## Obrovské čísla

Cíl této skupiny úplně stějná, jako u predchozí, ale bude pracovat s číslami větší než to dovoluje long long int. Pro čísla takovou velikostí potřebuju použít řetězec(to bude vector long long int), aby program byl shopen reprezentovat velmi velká čísla. Rozhraní u této skupiny tříd bude podobné, ale místo operací s číslami operací budou s řetězci(konkrétně ve vectoru long long int). Hierarchie tříd bude vypadat takto: rodičovska třída: `CDataSize` a zdědiné třídy: `CIntegerBig` a `CFloatBig`

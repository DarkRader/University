# Plánovač úloh

## Zadání
Vaším úkolem je udržovat si databázi úkolů a následně zpracovávat úkoly v rozumném pořadí.
Úkol je zadán unikátním ID (`size_t`, resp. `unsigned long int`), dale ma svuj popis (`std::string`) a svou prioritu (`size_t`). Tato třída je pro Vás již připravená, nemusíte a neměli byste ji nijak měnit.

Měli byste realizovat vhodně třídu CTaskScheduler tak, aby si byla schopna udržet všechny aktuální úkoly a následně je dokázala zpět vydávat nějakemu řešiteli. Pořadí vydávání úkolů podléhá prioritě úkolu, tedy čím větší priorita, tím dříve tento úkol musí někdo zpracovat.

Pokud bude dán požadavek na vydání nějakého úkolu řešiteli a vy byste měli na výber dva, nebo více úkolů se stejnou prioritou, vydejte ten úkol, který byl přidán dříve. Pozor, to že nějaký úkol má ID menší než jiný úkol, neznamená, že přišel nutně dříve, nevíte jak funguje system, který přidává úkoly, může si například alokovat nové ID již při vytvoření úkolu a tedy úkol může být nějakou dobu rozpracován a teprve později přidán do fronty.

Může se stát, že do plánovače přijde úkol se stejným ID 2x, pokud se tak stane a daný úkol JE již v databázi, tento úkol ignorujte. Může se ale stát, že se úkol do fronty vrátí, například v případě, že byl nejdříve vydán nějakému řešiteli a ten jej nevyřešil, tedy bude mít stejné ID, jelikož ho například nedokončil.

## Postup
Během řešení této úlohy se očekává, že budete používat kontejnery ze standardní knihovny. Rozmyslete si, které by se Vám hodily, abyste dosáhli nejhůře u každé metody logaritmických složitostí, nebo lepší. 

Podívejte se na následující kontejnery:
* std::map a std::set,
* std::queue a std::priority_queue.
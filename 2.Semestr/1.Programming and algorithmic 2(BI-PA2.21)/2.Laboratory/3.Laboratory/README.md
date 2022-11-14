# Zkoušení studentů

Na vysoké škole se vypisují zkoušky, abychom věděli, zda studenti pochopili danou látku. My si na to napíšeme program, kde budeme mít učitele, studenty a zkouškové termíny.

Vás čeká naimplementovat některé třídy, na kterých si vyzkoušíte konstruktory a destruktory.
V této úloze máte povoleny pouze knihovny `<iostream>` a `<string>`.

## Student

Jde o jednoduchou strukturu; student má jméno a připravenost. Po vyzkoušní bude mít nějakou známku, nás bude ale pouze zajímat, zdali zkouškou prošel. Třída je pro vás nachystaná.

## Učitel

Učitel má jméno a eviduje si počet úspěšně vyzkoušených studentů. Třída je pro vás nachystaná.

## Seznam studentů

Třída představuje seznam studentů. Realizujte jej dynamickým polem. Studenty je možné do seznamu vkládat, a seznam je možné procházet. Třída se musí starat o uvolnění paměti. Protože by se při kopírování některé věci rozbily a zatím to neumíme řešit, jsou v kostře třídy související funkce a operace potlačené.

## Zkouškový termín

Zkouškový termín má nastavenou obtížnost, která určuje minimální úroveň znalostí studenta k úspěchu, a je vázán na konkrétního učitele pomocí uložené reference. Zkouškový termín má metodu na vyzkoušení seznamu studentů. Během zkoušení jsou jednotliví studenti zkoušeni (simulováno porovnáním s obtížností) a počet úspěšně vyzkoušených studentů u učitele se aktualizuje.

# Hodnocení úloh

Dnes je pouze 1 úloha, kterou budeme společnými silami řešit. Na samostatnou práci máte na progtestu cvičnou úlohu, a od soboty řádnou domácí úlohu (která bude zaměřená na práci s binárními soubory). Pokud se však budete nudit, můžete se vrátit k oběma předchozím laborkám a zkusit si jejich řešení upravit tak, aby používala konstruktory a destruktory (tam, kde to má smysl).

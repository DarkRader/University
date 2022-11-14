# Skladiště

Ve skladu se nacházejí různé předměty. Některé bezpečné, některé nebezpečné. Ve skladu mohou být libovolné podmínky prostředí,
a předměty mohou a nemusí vybuchovat - každý ale může mít různé důvody k výbuchu. Naším úkolem bude tuto situaci namodelovat a poté naprogramovat.

## Třídy

### CEnvironment

`CEnvironment` je jednoduchá struktura obsahující informace o prostředí - teplotu, přítomnost kyslíku apod. Struktura je už připravená.

### CItem

`CItem` je běžný předmět ve skladu. Jako takový má jméno a umí se vypsat. Dále má metodu `canExplode`, která vrací, zda může předmět za uvedených podmínek vybuchnout - běžný předmět nevybuchne.

### CDangerousExplosive

`CDangerousExplosive` vybuchne v přítomnosti kyslíku.

### CCommonExplosive

`CCommonExplosive` je předmět, který vybuchne při překročení určité teploty (zadána při vytvoření instance).

### CWarehouse

`CWarehouse` má název a obsahuje seznam předmětů. I skladu se mohu zeptat, zda může vybuchnout.

## Rady

* Navrhněte dobrou hierarchii tříd a určete typy a viditelnost proměnných. Ke kreslení můžete využít DBS portál.
* Při výpisu chceme využít operátor <<. V C++ však neumíme dynamickou vazbu objektu, který dostaneme jako parametr funkce. Jak zařídím dynamickou vazbu pro potřeby výpisu?
* Při výpisu složitějšího druhu předmětu využijte výpis rodičovské třídy.
* K uložení předmětů ve skladu může skvěle posloužit šablona třídy `unique_ptr` z hlavičkového souboru `<memory>`. 

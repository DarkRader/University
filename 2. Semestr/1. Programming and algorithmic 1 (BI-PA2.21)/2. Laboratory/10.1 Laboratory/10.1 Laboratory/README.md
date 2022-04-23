# Šablony

## Nalezení unikátních prvků

Vaším úkolem je realizovat šablonovou funkci `unique_elements`, která dostává pouze instance `std::vector`, nebo `std::list`, které obsahují nějaké předem neznámé datové typy. Z těchto kontejnerů vybere pouze unikátní prvky. Všechny typy objektů, který můžete v těchto kontejnerech nalézt, mají zaručený pouze operátor `<`. Návratová hodnota této funkce bude `std::vector`.

* Jako výchozí komparátor vhodně použijte například `std::less` nebo `std::greater`.
* Prozkoumejte `std::less`. Co to je, a co umí?

## Rozšíření o komparátor

Implementujte další šablonovou funkci `unique_elements`, která bere další parametr jiného typu, který budeme používat jako komparátor pro porovnání unikátních prvků. Rozmyslete si, jak by šlo předchozí řešení znovupoužít i zde.

* Testovací program může a bude testovat další různé komparátory, než je pouze `std::less`.


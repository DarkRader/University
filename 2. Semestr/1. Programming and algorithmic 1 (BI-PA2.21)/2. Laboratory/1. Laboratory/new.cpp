#include <iostream>
#include <algorithm>

// mohu použít i svůj vlastní datový typ
struct DominoTile
{
    int dots[2];
};

// ale není to zadarmo
// níže jsem s intem/doublem dělal následující operace:

// čtení ze vstupu (>>)
// zápis na výstup (<<)
// řazení; zde se využívalo porovnání <

// a tyto operace budu muset nějak zajistit

// máme několik možností:
// 1) udělat to hnusně, načítat v existujících funkcích po složkách... :bonk:
// 2) napsat si vlastní funkce, které budou výše uvedené operace napodobovat
// 3) přímo dodefinovat operace (pro zájemce další commit, jinak náplň 4. týdne)

// čtení ze vstupu
// std::cout je ve skutečnosti typu std::istream
// nelze jej kopírovat, musíme si tedy předat referenci
// vracení std::istream & z funkce potom umožní s výsledkem něco dále dělat
std::istream & dominoRead(std::istream & in, DominoTile & tile)
{
    // nezapomeňme, že výsledkem >> je ten náš vstupní proud
    return in >> tile.dots[0] >> tile.dots[1];
}

// zápis na výstup
// std::cin je typu std::ostream
std::ostream & dominoWrite(std::ostream & out, DominoTile & tile)
{
    return out << "[" << tile.dots[0] << "|" << tile.dots[1] << "]";
}

// porovnání stylem <
// všimněte si, že na rozdíl od porovnávací funkce v qsort
// zde neberu pointery, ale reference
bool dominoLess(const DominoTile & a, const DominoTile & b)
{
    if(a.dots[0] < b.dots[0]) return true;
    if(a.dots[0] > b.dots[0]) return false;
    return a.dots[1] < b.dots[1];
}

struct MyArray
{
	unsigned int m_used;
	unsigned int m_cap;
	DominoTile * m_arr;
};


bool array_init ( MyArray & arr, unsigned int capacity )
{
	MyArray newArray = {0, capacity, new DominoTile[capacity]};

	if ( newArray.m_arr == nullptr )
		return false;
	
	arr = newArray;
	return true;
}

void array_destroy ( MyArray & arr )
{
	delete [] arr.m_arr;
	arr.m_arr = nullptr;
	arr.m_used = arr.m_cap = 0;
}

bool array_load ( MyArray & arr )
{
	for ( unsigned int i = 0; i < arr.m_cap; ++i )
		if ( ! dominoRead ( std::cin, arr.m_arr[i] ) )
			return false;
	return true;
}

void array_print ( const MyArray & arr )
{
	for ( unsigned int i = 0; i < arr.m_cap; ++i )
        // všimněte si, že díky vracení reference mohu do výsledku funkce šoupnout " "
		dominoWrite ( std::cout, arr.m_arr[i] ) << " ";
	std::cout << std::endl;
}

void array_sort ( MyArray & arr )
{
    // doplním porovnávací funkci
    // sort totiž existuje v 2parametrové i v 3parametrové variantě
    // všimněte si, že se zde nic nepřetypovává
    // ke konci semestru se naučíme, proč/jak to funguje
    std::sort ( arr.m_arr, arr.m_arr + arr.m_cap, dominoLess );
}

int main ( void )
{
	int N = 0;
	MyArray numbers;

	std::cout << "Zadej pozadovanou velikost:" << std::endl;
	if ( ! ( std::cin >> N ) || N <= 0 )
	{
        std::cout << "Chybny vstup!" << std::endl;
		return 0;
	}

	if ( ! array_init(numbers, N) )
	{
        std::cout << "Vytvoreni pole selhalo!" << std::endl;
		return 0;
	}

    std::cout << "Zadej sva cisla:" << std::endl;
	if ( ! array_load(numbers) )
	{
        std::cout << "Nacteni cisel selhalo!" << std::endl;
		array_destroy(numbers);
		return 0;
	}

    std::cout << "Nactena vsechna cisla!" << std::endl;
    array_sort(numbers);
	array_print(numbers);

	array_destroy(numbers);
	return 0;
}
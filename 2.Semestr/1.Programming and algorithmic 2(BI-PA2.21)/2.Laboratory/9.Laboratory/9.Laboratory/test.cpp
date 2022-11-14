#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstring>
#include <vector>
#include <list>

template <typename T, typename C = std::less<>>
void bubbleSort (T begin, T end, const C & cmp = C())
{
    size_t size = std::distance(begin, end);
    
    for(size_t i = 0; i < size; ++i)
        for(T it1 = begin, it2 = std::next(begin); it2 != end; ++it1, ++it2)
            if(cmp(*it2, *it1))
                std::swap(*it1, *it2);
}

struct CCompareInts
{
    bool operator() (int lhs, int rhs) const
    {
        return rhs < lhs;
    }
    
};

int main (void)
{
    int arr1[] = {5, 4, 3, 2, 1};
    bubbleSort(arr1, arr1 + sizeof(arr1)/sizeof(*arr1));
    for(const auto & el : arr1)
        std::cout << el << " ";
    std::cout << std::endl;
    
    std::string arr2[] = {"d", "c", "b", "a"};
    bubbleSort(arr2, arr2 + sizeof(arr2)/sizeof(*arr2));
    for(const auto & el : arr2)
        std::cout << el << " ";
    std::cout << std::endl;
    
    std::vector arr3 {5, 4, 3, 2, 1};
    bubbleSort(arr3.begin(), arr3.end());
    for(const auto & el : arr3)
        std::cout << el << " ";
    std::cout << std::endl;
    
    std::list l1 = {5, 4, 3, 2, 1};
    bubbleSort(l1.begin(), l1.end());
    for(const auto & el : l1)
        std::cout << el << " ";
    std::cout << std::endl;
    
    const char * arr4[] = {"d", "c", "b", "a"};
    bubbleSort(arr4, arr4 + sizeof(arr4)/sizeof(*arr4),
        [](const auto & lhs, const auto & rhs){
        return strcmp(lhs, rhs) < 0;
    });
    for(const auto & el : arr4)
        std::cout << el << " ";
    std::cout << std::endl;
    
    bubbleSort<int*, CCompareInts>(arr1, arr1 + sizeof(arr1)/sizeof(*arr1));
    for(const auto & el : arr1)
        std::cout << el << " ";
    std::cout << std::endl;
    
    return EXIT_SUCCESS;
}

#pragma once
#include <algorithm>
#include <vector>

template < typename Container, typename Comparator = std::less<typename Container::value_type>>
auto unique_elements ( const Container & elements, const Comparator & cmp = Comparator())
{
    std::vector<typename Container::value_type> unique(elements.begin(), elements.end());
    std::sort(unique.begin(), unique.end(), cmp);
    
    auto equal = [&cmp](const auto & lhs, const auto & rhs) {
        return !cmp(lhs, rhs) && ! cmp(rhs, lhs);
    };
    
    size_t i = 1, j = 0;
    for( ; i < unique.size(); ++i)
        if(!equal(unique[j], unique[i]))
            unique[++j] = unique[i];
    
    if(!unique.empty())
    unique.resize(j + 1, unique[0]);
    
    return unique;
}



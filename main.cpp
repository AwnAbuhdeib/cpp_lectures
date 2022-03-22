#include <array>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>

auto compute_addition() -> int

{
        int num1 {};
        int num2 {};
        std::cout << "enter two integers: ";
        std::scanf("%d %d", &num1, &num2);
        const auto res = num1 + num2;
        return res;
}

auto main() -> int
{
        const auto res  = compute_addition();
        // const auto res1 = compute_addition();
        // const auto res2 = compute_addition();
        // const auto res3 = compute_addition();
        std::cout<<"res= "<<res<< '\n';
}



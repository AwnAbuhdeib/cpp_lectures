#include <array>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

auto main() -> int
{
        /*auto compute_addition() -> int

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

         //std::cout<<"enter number of integers (o to terminate)";

               // int num = 0;

               // for (int i = 1; i <= num; i+=1)
                {
                      //  std::scanf("%d", &num);
                       // std::printf("%d%8d\n",i,i*i);

                        //if(num==0)
                      //  {
                      //          break;
                      //  }

             //   }*/
        std::vector<int> numbers {};
        while (true)
        {
                int number {};
                std::cin >> number;
                numbers.push_back(number);
                if (number == 0) { break; }
        }
        const auto n = std::count_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 != 0); });
        std::cout << "number of odd numbers: " << n << '\n';
}

#include <cstdio>
#include <ostream>
#include <string_view>
#include <string>
#include <iostream>
#include <array>
#include <iterator>

int main()
{
     /*   std::printf("%s\n", "Hello World");

        std::printf("test\n");
//option shift f to fix the format 
//command shift p for git commit and git push
std::string original = "message";
std::string copy1 = original;
std::string_view view1 {original};
original="adjusted message";
view1 = original;
 std::cout<<"orgi: "<<original<<std::endl;
 std::cout<<"copy1: "<<copy1<<std::endl;
 std::cout<<"view1: "<<view1<<std::endl;*/
 
 std::string basket = "apples, banana,peach,banana";
 // size_t is like int

 std::size_t found = basket.find("banana");
 int length_add = basket.length();
 std::cout <<"the value of found is: "<< found << std::endl;
 std::string second_fruit = basket.substr(found,7);
 std::cout<<"the substring value is: "<< second_fruit<<std::endl;


 std::string languages = "arabic,french,english,turkish";
 std::string language_of_intrest = "arabic";
 std::size_t position = languages.find(language_of_intrest);
 std::size_t lenght_of_languages = language_of_intrest.length();

 std::string msg {"where am I"};
 std::string*ptr{&msg};
 std::cout<<msg<<std::endl;
 std::cout<<&msg<<std::endl;
 std::cout<<ptr<<std::endl;

 

}



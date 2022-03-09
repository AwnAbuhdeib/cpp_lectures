#include <cstdio>
#include <string_view>
#include <string>
#include <iostream>

int main()
{
        std::printf("%s\n", "Hello World");

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
 std::cout<<"view1: "<<view1<<std::endl;

}



#include <iostream>
#include <string>


int main()
{
    const std::string red("\033[0;31m");
    const std::string green("\033[1;32m");
    const std::string yellow("\033[1;33m");
    const std::string cyan("\033[0;36m");
    const std::string magenta("\033[0;35m");
    const std::string reset("\033[0m");

    std::cout << yellow << " Hello color yellow " << reset << std::endl;
    std::cout << red << " Hello color red " << reset << std::endl;
    std::cout << green << " Hello color green " << reset << std::endl;
    std::cout << cyan <<" Hello color cyan " << reset << std::endl;
    std::cout << magenta << " Hello color magenta " << reset << std::endl;
     return 0;
}

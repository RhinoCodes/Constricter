#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

std::string space2underscore(std::string text)
{
    std::replace(0, 3, ' ', '_');
    return text;
}

int main(){
    cout << space2underscore("lo -");
}
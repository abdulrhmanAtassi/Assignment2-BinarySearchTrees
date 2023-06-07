#include "map.h"
#include <iostream>
using namespace std;

int main()
{
    Map<string, int> map;
    map.insert("F", 342);
    map.insert("B", 332);
    map.insert("A", 43);
    map.insert("C", 342);
    map.insert("K", 332);
    map.insert("M", 43);
    map.insert("N", 342);
    map.insert("L", 1000);
    // map.search(6);
    cout << map;

    // Map<string, int> Smap = map.cut("K");

    cout << "_______________________";
    map.trim("B", "M");
    cout << map;
    // cout << map.has_duplicate_values();
    // cout << map.max_value();
    return 0;
}
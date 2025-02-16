#include <iostream>
#include "hash_list.h"
#include "hash_map.h"

int main() {
    // Test hash_list
    hash_list<int, std::string> list;
    list.insert(1, "One");
    list.insert(2, "Two");
    list.insert(3, "Three");

    std::cout << "Value for key 2: " << list.get_value(2).value_or("Not found") << std::endl;

    list.remove(2);
    std::cout << "After removal, value for key 2: " << list.get_value(2).value_or("Not found") << std::endl;

    // Test hash_map
    hash_map<int, std::string> map(10, 0.75, 0.25);
    map.insert(1, "Apple");
    map.insert(2, "Banana");
    map.insert(3, "Cherry");

    std::cout << "Value for key 3 in hash_map: " << map.get_value(3).value_or("Not found") << std::endl;

    return 0;
}
#include <iostream>
#include "hash_list.h"
#include "hash_map.h"

void test_hash_list() {
    std::cout << "=== Testing hash_list ===" << std::endl;
    
    hash_list<int, std::string> list;
    list.insert(1, "One");
    list.insert(2, "Two");
    list.insert(3, "Three");

    // Retrieve values
    std::cout << "Value for key 2: " << list.get_value(2).value_or("Not found") << std::endl;

    // Test removal
    list.remove(2);
    std::cout << "After removal, value for key 2: " << list.get_value(2).value_or("Not found") << std::endl;

    // Test re-insertion
    list.insert(2, "Two Again");
    std::cout << "After reinsertion, value for key 2: " << list.get_value(2).value_or("Not found") << std::endl;

    // Test iterator
    std::cout << "Iterating through list:" << std::endl;
    list.reset_iter();
    while (!list.iter_at_end()) {
        auto iter_value = list.get_iter_value();
        if (iter_value) {
            std::cout << "Key: " << *iter_value->first << ", Value: " << *iter_value->second << std::endl;
        }
        list.increment_iter();
    }
}

void test_hash_map() {
    std::cout << "\n=== Testing hash_map ===" << std::endl;
    
    hash_map<int, std::string> map(3, 0.75, 0.25);

    std::cout << "capacity: " << map.get_capacity() << std::endl;

    // Insert elements
    map.insert(1, "Apple");
    map.insert(2, "Banana");
    map.insert(3, "Cherry");

    std::cout << "Value for key 3: " << map.get_value(3).value_or("Not found") << std::endl;

    // Remove key and check
    map.remove(2);
    std::cout << "After removal, value for key 2: " << map.get_value(2).value_or("Not found") << std::endl;

    // Insert more elements to trigger rehashing
    map.insert(4, "Date");
    map.insert(5, "Elderberry");
    map.insert(6, "Fig");  // Should trigger a rehash if upper_load_factor is exceeded
    map.insert(7, "Fig2");
    map.insert(8, "Fig3");
    map.insert(9, "Fig4");
    map.insert(10, "Fig50");
    map.insert(11, "Fig20");
    map.insert(12, "Fig30");
    map.insert(13, "Fig40");
    map.insert(14, "Fig57");

    std::cout << "After inserting 6 elements, new capacity: " << map.get_capacity() << std::endl;

    // Retrieve all keys
    int* keys = new int[map.get_size()];
    map.get_all_keys(keys);
    std::cout << "Keys in hash_map: ";
    for (size_t i = 0; i < map.get_size(); i++) {
        std::cout << keys[i] << " ";
    }
    std::cout << std::endl;
    delete[] keys;
}

int main() {
    test_hash_list();
    test_hash_map();
    return 0;
}
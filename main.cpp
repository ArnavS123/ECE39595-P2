#include <iostream>
#include "hash_map.h"


template <typename K, typename V>
void print_hash(hash_map<K,V> hash, int num_key){
    K* key_arr = new K[num_key];
    hash.get_all_keys(key_arr);
    std::optional<V> cur_value;
    for(int i = 0; i < num_key; i++){
        cur_value = hash.get_value(key_arr[i]);
        if(cur_value.has_value()) {
            std::cout << "Key #" << key_arr[i]<< ": " << cur_value.value() << std::endl;
        }
        else{
            std::cout <<"This is bad" << std::endl;
        }
    }
    std::cout << "Size of hash_map is " << hash.get_size() << std::endl;
    std::cout << "Capacity of hash_map is " << hash.get_capacity() << std::endl;
    delete [] key_arr;
}
template <typename K, typename V>
void bucket_printer(hash_map<K,V> hashmap){
    size_t* bucket = new size_t[hashmap.get_capacity()];
    hashmap.get_bucket_sizes(bucket);
    for(size_t i = 0; i < hashmap.get_capacity(); i++){
        std::cout << "list at index " << i << " has size " << bucket[i] << std::endl;
    }
    delete [] bucket;
}

void test_copy_and_assignment() {
    // Create a functional hashmap
    hash_map<int, float> original(2,1.2,0.8);
    original.insert(2, 1.0);
    original.insert(3, 2.0);
    std::cout << "Test Copy Constructor" << std::endl;


    hash_map<int, float> copy_constructed(original);
    // Create an empty hashmap
    hash_map<int, float> empty(1,1.2,0.8);
    std::cout << "Test Copying an Empty hash_map" << std::endl;
    // Test Copying an Empty hash_map
    hash_map<int, float> empty_copy(empty);
    bucket_printer(empty);
    bucket_printer(empty_copy);
    print_hash(empty,0);
    print_hash(empty_copy,0);
    // Test Assignment Operator
    std::cout << "Test Assignment Operator" << std::endl;
    hash_map<int, float> assigned(1,1.2,0.8);
    assigned = original;
    bucket_printer(original);
    bucket_printer(assigned);
    print_hash(original,2);
    print_hash(assigned,2);

    // Test Assigning an Empty hash_map
    std::cout << "Test Assigning an Empty hash_map" << std::endl;
    hash_map<int, float> assigned_empty(0,1.2,0.8);
    assigned_empty = empty;
    bucket_printer(empty);
    bucket_printer(assigned_empty);
    print_hash(empty,0);
    print_hash(assigned_empty,0);
}





int main(int argc, char *argv[]){
   // std::cout <<"Entering main" << std::endl;
    hash_map<int, float> test_type1 = hash_map<int,float>(500,1.2,0.8);

    std::cout << " pos -2" << std::endl;

    test_type1.insert(1, 2.0);

    //return 0;

    std::cout << " pos -2.1" << std::endl;

   // std::cout << "New cap should be 209: " << test_type1.get_capacity() << std::endl;

    hash_map<float,int> test_type2 = hash_map<float,int>(500,1.2,0.8);

    std::cout << " pos -1" << std::endl;

     for(int i = 0; i < 500; i++){
        size_t oldcap = test_type2.get_capacity();
        test_type2.insert(((float)i + 0.1),i);
        size_t newcap = test_type2.get_capacity();
       // if(oldcap != newcap) {//std::cout <<"old: " << oldcap << " | new: " << newcap << " | "<< (float)test_type2.get_size() / (float)test_type2.get_capacity() << std::endl;}
       // else{
        //    std::cout <<"For i = " << i << " no rehash, LF is at :" <<(float)test_type2.get_size() / (float)test_type2.get_capacity() << std::endl;
       // }
     } //expect an instant rehash, and then some flip flopping
     //now lets make sure we didnt lose any data

     std::cout << " pos 1" << std::endl;

     float* floatarr = new float[500];
     test_type2.get_all_keys(floatarr);

     for(int i = 0; i < 500; i++){
        std::optional<float> curval = test_type2.get_value((float)i + 0.1);
        //std::cout <<"key: " << i << " | val: " << curval.value() <<" | ";
    }
    std::cout << "pos 2" << std::endl;
     delete [] floatarr;
     //rehash down seem to work, values were still assigned correctly
     //test get all keys sorted

     hash_map<int,int> test_3 = hash_map<int,int>(209,0.8,1.2);

     test_3.insert(563,1);
     test_3.insert(123,1);
     test_3.insert(34634,1);
     test_3.insert(12398,1);
     test_3.insert(1237,1);
     test_3.insert(65398,1);
     test_3.insert(12371,1);
     test_3.insert(598043,1);
     test_3.insert(892371,1);
     test_3.insert(45071,1);
     test_3.insert(3,1);

     std::cout << "pos 2-1" << std::endl;

     size_t test3size = test_3.get_size();
     int* unsort_test = new int[test3size];
     int* sort_test = new int[test3size];

     std::cout << "pos 2-2-0" << std::endl;

     test_3.get_all_keys(unsort_test);
     test_3.get_all_sorted_keys(sort_test);

     std::cout << "pos 2-2" << std::endl;

    for(size_t j = 0; j < test3size; j++){
        //std::cout <<"index: " << j << "| key at index(US): " << unsort_test[j] <<" | key at index(S): " << sort_test[j] << std::endl;
    }
    delete [] unsort_test;
    delete [] sort_test;
    //validated template, get all sorted keys, hashing still works, does not really matter what the capacity is set to
    // test lower bound of 0 to make sure the capacity does not change until the upper bound is violated
    hash_map<int,int> test_4 =  hash_map<int,int>(50,1.3,0);
    for(size_t l = 1; l <= 100; l++){
        test_4.insert((int)l,(int)l);
        if(test_4.get_capacity() != 50){
       //     std::cout << "on insertion #" << l << " the capacity became " << test_4.get_capacity() << std::endl;
            break;
        }
    }

    std::cout << "pos 3" << std::endl;

    //test hashing based on capacity near 1021 to make sure hashing does not occur in a valid range
        //tested already
    //test remove validity
    hash_map<int,int> test5 = hash_map<int,int>(2500,1.2,0.8);
    for(int o = 1; o <= 2500; o++){
        test5.insert(o,o);
    }
    // 2500 element hashmap, cap should be max
    for(int o = 2500; o >= 0; o--){
        size_t oldcap = test5.get_capacity();
        std::optional<int> bingus = test5.remove(o);
        size_t newcap = test5.get_capacity();
        if(oldcap != newcap){
        //    std::cout << "Cap changed at :" << o << " elements from " << oldcap << " to " << newcap << std::endl;
        }
    }

    std::cout << "pos 4" << std::endl;

    //invalid hashmap test, no elements but cannot segfault or error on any method called on it
    hash_map<int,int> invalid = hash_map<int,int>(1,2,0.5);
        // get all bucket sizes, get all keys, get all keys sorted, remove, 
        std::optional<int> bingus2 = invalid.remove(2);
        if(bingus2 != std::nullopt){
          //  std::cout <<" bad" << std::endl;
        }
        int* bingus3 = new int[1];

        std::cout << "pos 5- -1" << std::endl;

        invalid.get_all_keys(bingus3);

        std::cout << "pos 5- -1 a" << std::endl;
    //    std::cout <<"Test: get all keys empty hashmap:" << bingus3[0] << std::endl;
        invalid.get_all_sorted_keys(bingus3);

        std::cout << "pos 5- -1 - 0" << std::endl;

       // std::cout <<"Test: get all sorted keys empty hashmap:" << bingus3[0] << std::endl;
        size_t* BScheck = new size_t[1];
        invalid.get_bucket_sizes(BScheck);
      //  std::cout <<"Test: get bucket sizes empty" << BScheck[0] << std::endl;        
        delete [] bingus3;
        delete [] BScheck;

        std::cout << "pos 5-0" << std::endl;


    //verify get bucket sizes, complete on a large array, delete most values, attempt again
    //hash_map<int,int> test6 = hash_map<int,int>(2,1.2,0.8);
   //     for(int b = 1; b <= 10000; b++){
   //     test6.insert(b,b);
  //  }
    // size_t* allkeyarr = new size_t[test6.get_capacity()];
    // test6.get_bucket_sizes(allkeyarr);
    // for(int g = 1; (size_t)g <= test6.get_capacity(); g++){
        // std::cout <<"Bucket " <<g <<" has " << allkeyarr[g-1] <<" keys." << std::endl;
    // }
    // std::cout << test6.get_size() << std::endl;
    //really specifically test the case in the pdf
    hash_map<int,int> test7 = hash_map<int,int>(209,1,0.95);
    //add 209 elements
    for(int u = 1; u <= 209; u++){
        test7.insert(u,u);
    }
  //  std::cout <<"Capacity is" << test7.get_capacity() << std::endl;
  //  std::cout <<"Load factor:" << (float)test7.get_size() / (float)test7.get_capacity() << std::endl;
    test7.insert(210,210);
    //std::cout <<"Capacity is" << test7.get_capacity() << std::endl;
   // std::cout <<"Load factor:" <<(float)test7.get_size() / (float)test7.get_capacity()<< std::endl;

   std::cout << "pos 5" << std::endl;

    //test copy/assign 
    //hash_map<int,int> test8 = test7;
    test_copy_and_assignment();
    return 0;
}
#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

// might need to remove this
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        int numerals[28] = {};
        int j = 0;
        for(int i=0; i < k.size(); i++) {
            HASH_INDEX_T new_int = letterDigitToNumber(k[i]);
            if(new_int != 40) {
                numerals[j++] = new_int;
            }
        }

        unsigned long long w[5] = {0};
        int index = 0;

        for(int i = j-1; (i >= 0 && index < 5); index++) {
            unsigned long long exponent = 1;
            unsigned long long total = 0;

            for(int k=0; (i >= 0 && k < 6); k++, i--) {
                total += numerals[i] * exponent;  
                exponent *= 36;
            }

            w[4-index] = total;
        }

        unsigned long long sum = 0; // reset to find total total

        for(int i=0; i < 5; i++) {
            sum += w[i] * rValues[i];
        }

        return sum;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        char new_letter = letter;

        if(new_letter <= 'Z' && new_letter >= 'A') { // if its capitol
            new_letter += 'a' - 'A'; // turn it lowercase
        }

        if(new_letter <= 'z' && new_letter >= 'a') { // if letter is alphabetic
            new_letter -= 'a';
            return new_letter; // converts it into proper v-tpye
        }

        else if(new_letter <= '9' && new_letter >= '0') { // it is numeric
            new_letter = 26 + (new_letter - '0');
            return new_letter;
        }
        return 40; // this number can only be hit if an error has occrued
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

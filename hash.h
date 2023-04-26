#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        // Add your code here
        HASH_INDEX_T sum = 0;
        std::string kk = k;
        for (int i = 0; i < 5; i++) {
            if (kk.length() == 0) {
                break;
            }
            else if (kk.length() >= 6) {
                std::string temp = kk.substr(kk.length() - 6, k.length());
                unsigned long long result = letterDigitToNumber(temp[0]);
                for (int j = 1; j < 6; j++) {
                    result = result * 36 + letterDigitToNumber(temp[j]);
                }
                sum += rValues[4 - i] * result;
                kk = kk.substr(0, kk.length() - 6);
            }
            else {
                std::string temp = kk.substr(0, kk.length());
                while (temp.length() < 6) {
                    temp = "a" + temp;
                }
                unsigned long long result = letterDigitToNumber(temp[0]);
                for (int j = 1; j < 6; j++) {
                    result = result * 36 + letterDigitToNumber(temp[j]);
                }
                sum += rValues[4 - i] * result;
                break;
            }
        }
        return sum;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        int temp = (int)letter;
        if (temp >= 48 && temp <= 57) {
            return temp -= 22;
        }
        else if (temp >= 65 && temp <= 90) {
            return temp - 65;
        }
        else if (temp >= 97 && temp <= 122) {
            return temp - 97;
        }
        else {
            return 0;
        }
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

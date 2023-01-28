#include "hw2-util.h"

// pre : 0 <= n < 256
// post: returns an 8-character string with the binary representation of n
string binary_8(int n) {
    string result = "";
    for (int i = 0; i < 8; i++) {
        result = static_cast<char>('0' + n % 2) + result;
        n /= 2;
    }
    return result;
}

// pre : bits contains a sequence of bits (the characters 0 and 1)
// post: returns the integer equivalent of the binary representation
int from_binary(const string & bits) {
    int result = 0;
    for (char ch : bits) {
        result = result * 2 + ch - '0';
    }
    return result;
}

// pre : bits contains a sequence of bits (the characters 0 and 1)
// post: the individual bits are appended to the end of the given vector
void to_vector(vector<int> & digits, const string & bits) {
    for (char ch : bits) {
        digits.push_back(ch - '0');
    }
}

// pre : digits contains a sequence of bits (the values 0 and 1)
// post: returns a string representation of the bits
string bits_to_string(const vector<int> & v) {
    string result = "";
    for (int n : v) {
        result += static_cast<char>(n + '0');
    }
    return result;
}

// pre : bit is 0 or 1
// post: returns the opposite bit
int flip(int bit) {
    return (bit + 1) % 2;
}

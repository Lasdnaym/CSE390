#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>  // for rand

using namespace std;

string binary_8(int n);
int from_binary(const string & bits);
void to_vector(vector<int> & digits, const string & bits);
string bits_to_string(const vector<int> & v);
int flip(int bit);

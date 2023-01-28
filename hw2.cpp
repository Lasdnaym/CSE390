// Copyright 2022 CSE 390C
// This program explores the error recovery scheme known as Hamming(7, 4).  The
// program uses a text file to create various other files for exploring this
// encoding scheme.  The 7-bit codes that are created are robust in the sense
// that they can have a single bit damaged and still recover the original code.

#include "hw2-util.h"

// post : introduced the program to the user
void intro(string & name, int & which) {
    cout << "This program performs various conversions of a text file" << endl;
    cout << "to explore Hamming codes.  The source file should have" << endl;
    cout << "the standard txt extension." << endl << endl;
    cout << "Available conversions are:" << endl;
    cout << "    1) txt to bit4 (initial expansion into 4-bit blocks)" << endl;
    cout << "    2) bit4 to bit7 (conversion to Hamming coded blocks)" << endl;
    cout<<  "    3) bit7 to bad (random damage to 7-bit blocks)" << endl;
    cout << "    4) bad to fix7 (error recovery)" << endl;
    cout << "    5) fix7 to new (new text file)" << endl;
    cout << "Base file name (without extension)? ";
    getline(cin, name);
    cout << "Which conversion do you want? ";
    cin >> which;
}

// pre : input is open for reading a text file of characters
// post: each character of the text file is converted into two 4-bit sequences
//       that represent the character value, one per line of output
void to_bit_4(ifstream & input, ofstream & output) {
    bool done = false;
    do {
        int ch = input.get();
        if (ch == EOF) {
            done = true;
        } else {
            string bits = binary_8(ch);
            output << bits.substr(0, 4) << endl << bits.substr(4, 4) << endl;
        }
    } while (!done);
}

// pre : input contains a sequence of 4-bit sequences, one per line
// post: 7-bit Hamming(7, 4) codes are written to output, one per line
void to_bit_7(ifstream & input, ofstream & output) {
    string data;
    while (input >> data) {
        int p1 = (data[0] + data[1] + data[3]) % 2;
        int p2 = (data[0] + data[2] + data[3]) % 2;
        int p4 = (data[1] + data[2] + data[3]) % 2;
        output << p1 << p2 << data[0] << p4 << data[1] << data[2] << data[3] << endl;
    }
}

// pre : input contains a sequence of 7-bit numbers, one per line
// post: approximately 25% of the sequences have a single bit damaged
void to_bad(ifstream & input, ofstream & output) {
    string data;
    while (input >> data) {
        // we pick a random number from 0 to 27, so 25% of the time we are
        // damaging one of the 7 bits
        unsigned int seed;
        int bad = rand_r(&seed) % 28;
        for (int i = 0; i < data.length(); i++) {
            if (i == bad) {
                output << flip(data[i] - '0');
            } else {
                output << data[i];
            }
        }
        output << endl;
    }
}

// pre : input contains a sequence of Hamming(7, 4) codes that contain up to
//       one bit error, one per line
// post: corrected Hamming(7, 4) codes are written to output, one per line
void to_fix_7(ifstream & input, ofstream & output) {
    string data;
    while (input >> data) {
        int p1 = (data[0] - '0') ^ (data[2] - '0') ^ (data[4] - '0') ^ (data[6] - '0');
        int p2 = (data[1] - '0') ^ (data[2] - '0') ^ (data[5] - '0') ^ (data[6] - '0');
        int p4 = (data[3] - '0') ^ (data[4] - '0') ^ (data[5] - '0') ^ (data[6] - '0');
        int error_bit = p4 * 4 + p2 * 2 + p1;
        if (error_bit != 0) {
            int index = error_bit - 1;
            data[index] = flip(data[index] - '0') + '0';
        }
        output << data << endl;
    }
}

// pre : input contains a sequence of 7-bit Hamming codes for a text file
// post: the original text is written to output
void to_new(ifstream & input, ofstream & output) {
    string data;
    while (input >> data) {
        string bits;
        bits = bits + data[2] + data[4] + data[5] + data[6];
        input >> data;
        bits = bits + data[2] + data[4] + data[5] + data[6];
        output << static_cast<char>(from_binary(bits));
    }
}

int main() {
    string name;
    int which;
    intro(name, which);
    vector<string> extensions = {"txt", "bit4", "bit7", "bad", "fix7", "new"};
    ifstream input((name + "." + extensions[which - 1]));

    if (!input.is_open()) {
        cerr << "Error: Couldn't open the provided input file." << endl;
        cerr << "Make sure that the path is correct and try again" << endl;
        return 1;
    }
    ofstream output((name + "." + extensions[which]));

    switch (which) {
    case 1:
        to_bit_4(input, output);
        break;
    case 2:
        to_bit_7(input, output);
        break;
    case 3:
        to_bad(input, output);
        break;
    case 4:
        to_fix_7(input, output);
        break;
    case 5:
        to_new(input, output);
        break;
    default:
        cout << "unknown conversion" << endl;
    }

    return 0;
}

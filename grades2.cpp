// This program reads student scores from a file and
// prints grading statistics to the console
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "student.h"

using namespace std;

void process_file(ifstream& input, vector<student> & students);
void report_results(vector<student> students);

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cout << "Error: unexpected number of arguments" << endl;
        cout << "Usage: ./<program> <filename>" << endl;
        return 1;
    }
    string file_name(argv[1]);  // converts the first argument to a string
    ifstream input(file_name);
    if (!input.is_open()) {
        cout << "Error: could not read the specified file" << endl;
        return 1;
    }
    vector<student> students;
    process_file(input, students);
    sort(students.begin(), students.end());
    report_results(students);
}

void process_file(ifstream& input, vector<student> & students) {
    string name;
    while (getline(input, name)) {
        student next(name);
        string line;
        getline(input, line);
        istringstream data(line);
        int midterm, final;
        data >> midterm >> final;
        next.set_midterm(midterm);
        next.set_final(final);
        int score, max;
        while (data >> score >> max) {
            next.add_score(score, max);
        }
        next.set_overall(0.2, 0.4, 0.4);
        students.push_back(next);
    }
}

void report_results(vector<student> students) {
    int count = students.size();
    int midterm_total = 0;
    int final_total = 0;
    int homework_total = 0;
    int total_homeworks = 0;
    double total_overall = 0.0;
    for (student & next : students) {
        midterm_total += next.get_midterm();
        final_total += next.get_final();
        homework_total += next.get_homework();
        total_homeworks += next.get_homework_scores().size();
        total_overall += next.get_overall();
    }
    cout << "Total of " << count << " students" << endl;
    cout << "averages:" << endl;
    cout << "    midterm     = " 
         << static_cast<double>(midterm_total) / count << endl;
    cout << "    final       = "
         << static_cast<double>(final_total) / count << endl;
    cout << "    homework    = " << 
        static_cast<double>(homework_total) / count << endl;
    cout << "    # homeworks = "
         << static_cast<double>(total_homeworks) / count << endl;
    cout << "    overall     = " << total_overall / count << endl;
    cout << endl;
    cout << "individual students:" << endl;
    for (student next : students) {
        cout << "    " << next << endl;
    }
}

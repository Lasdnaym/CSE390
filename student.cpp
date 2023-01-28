#include "student.h"

// Input: a string representing the name of the student
// Output: None
// Initializes the student object with a name and sets 
// the midterm, final, homework and total_overall scores to 0
student::student(const string& student_name) : name(student_name), 
midterm(0), final(0), homework(0), total_overall(0) {}

// Input: an integer representing the midterm score
// Output: None
// Sets the midterm score 
void student::set_midterm(int score) {
    midterm = score;
}

// Input: an integer representing the final score
// Output: None
// Sets the final score
void student::set_final(int score) {
    final = score;
}

// Input: an integer representing the score of a homework assignment, 
// and an integer representing the maximum possible score of the assignment
// Output: None
// Adds a homework score and its maximum possible score to the 
// homework_scores vector
void student::add_score(int score, int possible) {
    homework_scores.push_back({score, possible});
}

// Input: None
// Output: Reference to the string representing the student's name
// Returns the name of the student
const string& student::get_name() {
    return name;
}

// Input: None
// Output: integer representing the midterm score 
// Returns the midterm score
int student::get_midterm() {
    return midterm;
}

// Input: None
// Output: integer representing the final score
// Returns the final score 
int student::get_final() {
    return final;
}

// Input: None
// Output: reference to the vector of homework scores and maximum possible scores 
// Returns the homework scores and maximum possible scores
const vector<homework_score>& student::get_homework_scores() {
    return homework_scores;
}

// Input: None
// Output: double representing the homework score as a percentage
// Calculates and returns the homework score as a percentage
double student::get_homework() {
    double total_scores = 0;
    double total_possible = 0;
    for(auto hs : homework_scores){
        total_scores += hs.score;
        total_possible += hs.possible;
    }
    if(total_possible == 0){
        return 0;
    }
    homework = total_scores * 100/total_possible;
    homework = std::round(homework /0.0001) * 0.0001;
    return homework;
}

// Input: a double representing the weight of midterm score, 
// a double representing the weight of final score, 
// and a double representing the weight of homework score
// Output: None
// Calculates and sets the overall score of the student based on the given weights
void student::set_overall(double midterm_weight, double final_weight, double homework_weight) {
    total_overall = (midterm * midterm_weight) + (final * final_weight) + (get_homework() * homework_weight);
    total_overall = std::round(total_overall /0.0001) * 0.0001;
}

// Input: None
// Output: double representing the overall score 
// Returns the overall score 
double student::get_overall() const {
    return total_overall;
}

// Input: None
// Output: string representing a summary of a student
// Returns a summary of a student's performance
string student::to_string() const {
    string output;
    output += name + ": ";
    string overall_str = std::to_string(total_overall);
    int i = overall_str.size() - 1;
    while (i > 0 && overall_str[i] == '0') {
        overall_str.pop_back();
        i--;
    }
    if (overall_str[i] == '.') overall_str.pop_back();
    output += "overall " + overall_str + ", ";
    output += "midterm " + std::to_string(midterm) + ", ";
    output += "final " + std::to_string(final) + ", ";

    string homework_str = std::to_string(homework);
    i = homework_str.size() - 1;
    while (i > 0 && homework_str[i] == '0') {
        homework_str.pop_back();
        i--;
    }
    if (homework_str[i] == '.') homework_str.pop_back();
    output += "homework " + homework_str;
    return output;
}

// Input: an ostream object and a student object
// Output: an ostream object containing a string representation of the student
ostream & operator<<(ostream & out, const student & s) {
    out << s.to_string();
    return out;
}

// Input: two student objects
// Output: a boolean value indicating whether the 
// overall grade of the first student is less 
// than the overall grade of the second student
bool operator<(const student& lhs, const student& rhs) {
    return lhs.get_overall() < rhs.get_overall();
}

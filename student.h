#ifndef _HOME_SRC_STUDENT_H_
#define _HOME_SRC_STUDENT_H_

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// A homework_score is a helper struct that stores both
// the earned score and possible score for an assignment
struct homework_score {
    int score, possible;
};

// A class representing a student, including their name, midterm score, final score, 
// homework scores, and overall score
class student {
 public:
    // constructs a student with the given name
    student(const string& student_name);

    // sets the midterm score for this student
    void set_midterm(int score);

    // sets the final score for this student
    void set_final(int score);

    // adds a homework score for this student
    // accepting points earned and points possible args
    void add_score(int score, int possible);

    // returns the name for this student
    const string& get_name();

    // returns the midterm score for this student, 0 if not set yet
    int get_midterm();

    // returns the final exam score for this student, 0 if not set yet
    int get_final();

    // returns the homework scores for this student
    const vector<homework_score>& get_homework_scores();

    // returns the homework percentage total for this student
    // returns 0 if no homework scores reported
    double get_homework();

    // sets overall score given weights for midterm, final, and homework.
    // the overall score is the sum of the products of each of these scores
    // and their respective weights
    void set_overall(double midterm_weight, double final_weight, double homework_weight);

    // returns overall score or 0 if set_overall has not been called
    double get_overall() const;

    // returns a string consisting of this student's name and scores
    // lines 11-22 of the example output log show the expected format
    // There should be no trailing newline or leading tab in the returned string
    string to_string() const;

    // prints a string representing s to the given steam
    friend ostream & operator<<(ostream & out, const student & s);

    // Returns true if the overall score of the left student is less
    // than the overall score of the right student
    friend bool operator<(const student & lhs, const student & rhs);

    private:
        string name;
        int midterm;
        int final;
        vector<homework_score> homework_scores;
        double homework;
        double total_overall;
};

#endif  // _HOME_SRC_STUDENT_H_

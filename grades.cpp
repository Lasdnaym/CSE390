#include <iostream>
#include <cmath>
#include <vector>

using namespace std; 

void printIntro();
void printCourse(int);
void printStats();
int sumVectorInts(vector<int>);
double averageVectorDoubles(vector<double>);

vector<double> midtermScores, finalScores, avgHomeworkScores;
int numCourses;

int main() {
    // Intro
    printIntro();
    // How many courses will there be
    cout << "How many courses to record? ";
    cin >> numCourses;
    cout << endl;
    // Loop through all the courses
    for (int i = 1; i <= numCourses; i++) {
        printCourse(i);    
    }
    printStats();
    return 0;
}

// Prints the intro
void printIntro() {
    cout << "This program allows you to enter data for several courses and" << endl;
    cout << "reports average scores for midterms, finals, and homework." << endl << endl;
}

// Handles all inputs and outputs for a course
void printCourse(int currCourse) {
    // Course number message
    cout << "Course #" << currCourse << ":" << endl;
    // Get exam scores
    double midtermScore, finalScore;
    cout << "    midterm score? ";
    cin >> midtermScore;
    midtermScores.push_back(midtermScore);
    cout << "    final score? ";
    cin >> finalScore; 
    finalScores.push_back(finalScore);
    // How many homework assignments are there
    int numHomeworks;
    cout << "    number of homework assignments? ";
    cin >> numHomeworks;
    // Record and compute homework statistics
    vector<int> homeworkScores, maxHomeworkScores;
    for (int i = 1; i <= numHomeworks; i++) {
        int homeworkScore, maxHomeworkScore;
        cout << "        homework #" << i << " your score and max score? ";
        cin >> homeworkScore >> maxHomeworkScore;
        homeworkScores.push_back(homeworkScore);
        maxHomeworkScores.push_back(maxHomeworkScore);
    }
    // Sum true scores and max scores
    int trueScoreSum, maxScoreSum;
    trueScoreSum = sumVectorInts(homeworkScores);
    maxScoreSum = sumVectorInts(maxHomeworkScores);
    // Find percentage
    double homeworkPercentage;
    homeworkPercentage = ((double)trueScoreSum / maxScoreSum) * 100;
    cout << "    homework % = " << homeworkPercentage << endl << endl;
    avgHomeworkScores.push_back(homeworkPercentage);
}

// Print the ending statistics
void printStats() {
    double avgMidterm, avgFinal, avgHomework;
    avgMidterm = averageVectorDoubles(midtermScores);
    avgFinal = averageVectorDoubles(finalScores);
    avgHomework = averageVectorDoubles(avgHomeworkScores);
    cout << numCourses << " courses total" << endl;
    cout << "midterm average  = " << avgMidterm << endl;
    cout << "final average    = " << avgFinal << endl;
    cout << "homework average = " << avgHomework << endl; 
}

// Find the average of a vector of doubles, returns the average as a double
double averageVectorDoubles(vector<double> v) {
    double sum = 0;
    for (auto x : v) {
        sum += x;
    }
    return sum / v.size();
}

// Find the sum of a vector of ints, return the sum as an int
int sumVectorInts(vector<int> v) {
    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum;
}

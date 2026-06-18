#include <iostream>
using namespace std;

using Score = int;
using StudentID = unsigned int;
using GradeList = Score[100];

double averageScore(const GradeList& grades, int count) {
    if(count <= 0) { 
        return 0.0;
    } 

    Score sum = 0;

    for(Score i = 0; i < count; i++) {
        sum += grades[i];
    }

    return (double)sum / count;
}
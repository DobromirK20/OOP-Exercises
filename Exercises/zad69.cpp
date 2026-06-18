#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
using namespace std;

void proccessFile(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);

    if(!fin.is_open()){
        throw runtime_error("Ne moje da se otvori vhodniqt fail");
    }

    double sum = 0;
    int count = 0;
    string line;

    while (getline(fin,line))
    {
        try {
            double number = stod(line);
            sum += number;
            count++;
        }
        catch(const invalid_argument& e) {
            cerr << e.what() << '\n';
        }

        catch(const out_of_range& e) {
            cerr << e.what() << endl;
        }
    }

    fin.close();

    if(count == 0) {
        throw runtime_error("Nqma validni chisla vuv faila!");
    }

    double average = sum/count;

    ofstream fout(outputFile);

    if(!fout.is_open()) {
        throw runtime_error("Ne moje da se suzdade izhodniq fail");
    }

    fout << "Sum = " << sum << endl;
    fout << "Average = " << average << endl;

    fout.close();
}

int main() {
    try
    {
        proccessFile("input.txt", "output.txt");

        cout << "Dannite sa obraboteni uspeshno!" << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    return 0;
}
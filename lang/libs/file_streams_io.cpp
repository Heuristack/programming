#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream ifstream("/users/lancel/tmp/main.cpp");
    ofstream ofstream("/users/lancel/tmp/main.txt");

    vector<string> file;
    for (string line; getline(ifstream,line);) {
        file.emplace_back(move(line));
    }

    for (string const & line : file) {
        ofstream << line << endl;
    }
}


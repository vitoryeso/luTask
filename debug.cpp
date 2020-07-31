#include <iostream>
#include <fstream>
#include "luTask.h"

using namespace std;

int main(void) {
    Task T("terminar o i/o do task managger", "luTask");
    string file_path="history/tasks.txt";
    fstream myfile;

    myfile.open(file_path, fstream::in | fstream::out | fstream::app);
    myfile << T;
    myfile.close();

    return 0;
}

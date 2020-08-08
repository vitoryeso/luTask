#include <iostream>
#include <cctype>
#include <fstream>
#include "luTask.h"

using namespace std;

int main(void) {
    string file_path="history/tasks.txt";
    fstream myfile;
    bool save;
    cerr << "salvar(0) ou ler(1)? ";
    cin >> save;
    cin.ignore();
    if(!save) {
        TaskList TL;
        myfile.open(file_path, fstream::in | fstream::out);
        TL.typeList();
        TL.finishSomeTask();
        myfile << TL;
        myfile.close();
    }
    else {
        TaskList TL;
        myfile.open(file_path, fstream::in | fstream::out);
        myfile >> TL;
        TL.finishSomeTask();
        cout << TL << endl;
        myfile.close();
    }

    return 0;
}

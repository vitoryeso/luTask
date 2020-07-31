#include <iostream>
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
        Task T("terminar o i/o do task managger", "luTask");
        myfile.open(file_path, fstream::in | fstream::out | fstream::app);
        myfile << T;
        myfile.close();
    }
    else {
        Task T;
        myfile.open(file_path, fstream::in | fstream::out | fstream::app);
        T.read(myfile); 
        myfile.close();
    }

    return 0;
}

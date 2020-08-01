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
        Task T("terminar o i/o do task managger", "luTask");
        myfile.open(file_path, fstream::in | fstream::out | fstream::app);
        myfile << T;
        myfile.close();
    }
    else {
        Task T;
        myfile.open(file_path, fstream::in | fstream::out | fstream::app);
        if(!T.read(myfile)) cout << "deu errado" << endl;
        myfile.close();
    }
    fstream provfile;
    provfile.open("history/prov.txt", fstream::in);
    int num;
    int c;
    string numstr;
    c = provfile.peek();
    if(isdigit(c)) cout << " eh um digitooooo " << endl;
    else cout << "nao eh um digito" << endl;
    char cc = c;
    cout << "cc: " << cc << endl;
    provfile >> num;
    cout << "num: " << num << endl;

    provfile.close();
    return 0;
}

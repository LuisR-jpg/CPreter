#include <fstream>
#include <iostream>
using namespace std;
class Read
{
  public: 
    Read(){}
    string getCode(string name = "in.cpr"){
      //name = "test.cpr";
      //name = "lectura.cpr";
      //name = "if.cpr";
      //name = "si.cpr";
      //name = "for.cpr";
      //name = "while.cpr";
      //name = "error.cpr";
      ifstream file;
      string a, b;
      file.open(name, ios::in);
      if(file.fail()){
        cout << "\tERROR: There's been a problem while trying to read the CPR file."; 
        exit(0);
      }
      while(!file.eof()) getline(file, a), a += "\n", b += a;
      int esp = b.size() - 1;
      while(isspace(b[esp--]));
      return b.substr(0, 2 + esp) + '\n';
    }
};

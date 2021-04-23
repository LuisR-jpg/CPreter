#include <fstream>
#include <iostream>
using namespace std;
class Read
{
  public: 
    Read(){}
    string getCode(string name = "in.cpr"){
      ifstream file;
      string a, b;
      file.open(name, ios::in);
      if(file.fail()){
        cout << "\tERROR: There's been a problem while trying to read the CPR file."; 
        exit(0);
      }
      while(getline(file, a)) a += "\n", b += a;
      int esp = b.size() - 1;
      while(isspace(b[esp--]));
      return b.substr(0, 2 + esp) + '\n';
    }
};

#include <fstream>
#include <iostream>
using namespace std;
class Read
{
  public: 
    Read(){}
    string getCode(string name = "in.cpr"){
      //name = "test.cpr";
      name = "lectura.cpr";
      ifstream file;
      string a, b;
      file.open(name, ios::in);
      if(file.fail()){
	cout << "Agh, chale"; 
	return "";
      }
      while(!file.eof()) getline(file, a), a += "\n", b += a;
      return b;
    }
};

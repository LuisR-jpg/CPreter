#include <fstream>
#include <iostream>
using namespace std;
class Read
{
  public: 
    Read(){}
    string getCode(){
      ifstream file;
      string a, b;
      file.open("in.cpr", ios::in);
      if(file.fail()){
	cout << "Agh, chale"; 
	return "";
      }
      while(!file.eof()) getline(file, a), a += "\n", b += a;
      return b;
    }
};

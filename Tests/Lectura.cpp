#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int main(){
  ifstream jaja;
  string a;
  vector<string> v;
  jaja.open("in.cpr", ios::in);
  if(jaja.fail()){
    cout << "F" << endl;
    return 0;
  }
  while(!jaja.eof()){
    getline(jaja, a);
    v.push_back(a);
  }
  for(auto i: v) cout << i << endl;
  return 0;
}


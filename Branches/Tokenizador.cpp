#include <bits/stdc++.h>
using namespace std; 
int main(){
  cout << "{" << endl;
  vector<string> v;
  while(true){
    string a, b;
    cin >> a >> b;
    if(a == "F"){
      cout << "}";
      break;
    }
    string s = "make_pair(\"" + a + "\", " + b + "),\n";
    v.push_back(s);
  }
  for(auto i: v){
    cout << i;
  }
  return 0;
}

#include "ExpressionEvaluator.h"
using namespace std;
int main(){
  vector<pair<string, int>> v = 
  //------5*12 + (+-25 - +12/3 * -7)
    {
      make_pair("-", 32),
      make_pair("-", 32),
      make_pair("-", 32),
      make_pair("-", 32),
      make_pair("-", 32),
      make_pair("-", 32),
      make_pair("5", 50),
      make_pair("*", 32),
      make_pair("12", 50),
      make_pair("+", 32),
      make_pair("(", 31),
      make_pair("+", 32),
      make_pair("-", 32),
      make_pair("25", 50),
      make_pair("-", 32),
      make_pair("+", 32),
      make_pair("12", 50),
      make_pair("/", 32),
      make_pair("3", 50),
      make_pair(")", 31),
      make_pair("*", 32),
      make_pair("-", 32),
      make_pair("7", 50)
    };

  //5*12 + (25 - 12/3) * 7 = 207
  /*
    {
      make_pair("5", 50),
      make_pair("*", 32),
      make_pair("12", 50),
      make_pair("+", 32),
      make_pair("(", 31),
      make_pair("25", 50),
      make_pair("-", 32),
      make_pair("12", 50),
      make_pair("/", 32),
      make_pair("3", 50),
      make_pair(")", 31),
      make_pair("*", 32),
      make_pair("7", 50)
    };
  */
//10 >= (9/2 - 3*2)*2 && 5 + 9 <= 8 / 2 = 0
    /*
    {
      make_pair("(", 31),
      make_pair("10", 50),
      make_pair(">=", 33),
      make_pair("(", 31),
      make_pair("9", 50),
      make_pair("/", 32),
      make_pair("2", 50),
      make_pair("-", 32),
      make_pair("3", 50),
      make_pair("*", 32),
      make_pair("2", 50),
      make_pair(")", 31),
      make_pair("*", 32),
      make_pair("2", 50),
      make_pair(")", 31),
      make_pair("&&", 34),
      make_pair("(", 31),
      make_pair("5", 50),
      make_pair("+", 32),
      make_pair("9", 50),
      make_pair("<=", 33),
      make_pair("8", 50),
      make_pair("/", 32),
      make_pair("2", 50),
      make_pair(")", 31)
    };
    */
  queue<pair<string, int>> q;
  for(auto i: v) q.push(i);
  Evaluator a(q);
  cout << a.evaluate();
  return 0;
}

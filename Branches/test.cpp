#include "ExpressionEvaluator.h"
using namespace std;
int main(){
  //5*12 + (25 - 12/3) * 7 = 207
  Evaluator a(
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
    make_pair("7", 50),
    }
  );
  a.evaluate();
  return 0;
}

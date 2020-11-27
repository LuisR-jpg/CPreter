#include "ExpressionEvaluator.h"
using namespace std;
int main(){
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
  return 0;
}

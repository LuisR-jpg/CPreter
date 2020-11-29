#include "ExpressionEvaluator.h"
using namespace std;
int main(){
  /*
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
    make_pair("7", 50)
    }
  );
  */
  //10 >= (9/2 - 3*2)*2 && 5 + 9 <= 8 / 2
  /*
( 31
10 50
>= 33
( 31
9 50
/ 32
2 50
- 32
3 50
* 32
2 50
) 31
* 32
2 50
) 31
&& 34
( 31
5 50
+ 32
9 50
<= 33
8 50
/ 32
2 50
) 31
*/
  Evaluator a(
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
    }
  );
  a.evaluate();
  return 0;
}

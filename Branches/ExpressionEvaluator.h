#include <iostream>
//#include <vector>
using namespace std;
class Evaluator{
  public: 
    class Operator{
      public: 
        char symbol;
        Operator(char symbol): symbol(symbol){}
        ~Operator(){}
    };
    vector<pair<string, int>> expression;
    Evaluator(vector<pair<string, int>> expression): expression(expression){}
    double evaluate(){
      for(auto i: expression){
        if(i.second == 10)



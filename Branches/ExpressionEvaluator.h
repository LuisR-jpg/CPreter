#include <iostream>
//#include <vector>
using namespace std;
class Evaluator{
  public: 
    class Operator{
      public: 
        string symbol;
        Operator(string symbol): symbol(symbol){}
        ~Operator(){}
    };
    vector<pair<string, int>> expression;
    Evaluator(vector<pair<string, int>> expression): expression(expression){}
    double evaluate()
    {
      for(auto i: expression)
      {
        if(i.second == 10) out.push(i);
	else if(sta.size() && sta.front() != "(")
	{
	  while(sta.front().priority() >= i.priority())
	    out.push(sta.pop());
	  sta.push(i);
	}
	else if(i.first == "(") sta.push(i);
	else if(i.first == ")"){
	  while(sta.front().first != "(") out.push(sta.pop());
	  sta.pop();
	  //Lanza error si no hay parentestis (
	}
      }
      while(sta.size())
      {
	if(sta.front() == "(" || sta.front == ")") cout << "F"; //Need to be handled
	out.push(sta.pop());
      }
      while(out.size()) cout << out.pop().first << " ";
    }
};





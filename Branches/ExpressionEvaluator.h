#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Evaluator
{
  public: 
    class Operator
    {
      public: 
        string symbol;
        Operator(string symbol): symbol(symbol){}
        ~Operator(){}
	/*
	bool operator >= (const Operator &o){
	  return priority.find(
	}
	bool operator == (const Operator &o){
	  return symbol == o.symbol;
	}
	bool operator != (const Operator &o){
	  return symbol != o.symbol;
	}
	*/
    };
    vector<pair<string, int>> expression;
    map<Operator, int> priority;
    Evaluator(vector<pair<string, int>> expression): expression(expression)
    {
      vector<vector<string>> priorityTable =
      {
	{"&&"},	{"||"},	{"!"},
	{">=", "<=", ">", "<", "==", "!="},
	{"+","-"}, {"*","/"}, {"(",")"}
      };
      for(int i = 0; i < priorityTable.size(); i++)
      {
	cout << i << ":\t";
	for(int j = 0; j < priorityTable[i].size(); j++)
	{
	  cout << priorityTable[i][j] << " ";
	  priority.insert(make_pair(Operator(priorityTable[i][j]), i));
	}
	cout << endl;
      }
    }
    ~Evaluator(){}
    double evaluate()
    {
/*
      for(auto i: expression)
      {
	Operator op(i.first);
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
*/
      return 0;
    }
};





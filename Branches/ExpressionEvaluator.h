#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;
class Evaluator
{
  public: 
	/*
    class Operator
    {
      public: 
        string symbol;
	static unordered_map<string, int> priority;
	Operator(): symbol(""){}
        Operator(string symbol): symbol(symbol){}
        ~Operator(){}
	bool operator >= (const Operator &o){
	  return getPriority(this -> symbol) >= getPriority(o.symbol);
	}
	bool operator == (const Operator &o){
	  return symbol == o.symbol;
	}
	bool operator != (const Operator &o){
	  return symbol != o.symbol;
	}
    };
	*/
    vector<pair<string, int>> expression;
    unordered_map<string, int> priority;
    Evaluator(vector<pair<string, int>> expression): expression(expression)
    {
      vector<vector<string>> priorityTable =
      {
	{"&&"},	{"||"},	{"!"},
	{">=", "<=", ">", "<", "==", "!="},
	{"+","-"}, {"*","/"}, {"(",")"}
      };
      for(int i = 0; i < priorityTable.size(); i++)
	for(int j = 0; j < priorityTable[i].size(); j++)
	  priority.insert(make_pair(priorityTable[i][j], i));
    }
    ~Evaluator(){}
    double evaluate()
    {
      stack<pair<string, int>> sta;
      queue<pair<string, int>> out;
      for(auto i: expression)
      {
        if(i.second >= 50 && i.second <= 60) out.push(i);
	else if(sta.size() && sta.top().first != "(")
	{
	  while(priority[sta.top().first] >= priority[i.first])
	    out.push(sta.top()), sta.pop();
	  sta.push(i);
	}
	else if(i.first == "(") sta.push(i);
	else if(i.first == ")"){
	  while(sta.top().first != "(") out.push(sta.top()), sta.pop();
	  sta.pop();
	  //Lanza error si no hay parentestis (
	}
      }
      while(sta.size())
      {
	if(sta.top().first == "(" || sta.top().first == ")") cout << "F"; //Need to be handled
	out.push(sta.top()), sta.pop();
      }
      while(out.size()) cout << out.front().first << " ", out.pop();
      return 0;
    }
};





#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <string>
using namespace std;
class Evaluator
{
  public: 
    vector<pair<string, int>> expression;
    unordered_map<string, int> priority;
    Evaluator(vector<pair<string, int>> expression): expression(expression)
    {
      fillPriority();
    }
    void fillPriority()
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
    void prepare(){
      cout << "IMPLEMENTAMEEEEEEEEEEEEEEEEEE" << endl;
    }
    double evaluate()
    {
      prepare();
      stack<pair<string, int>> sta;
      queue<pair<string, int>> out;
      for(auto i: expression)
      {
        if(i.second >= 50 && i.second <= 60) out.push(i);
        else if(i.first == "(") sta.push(i);
        else if(i.first == ")")
        {
          while(sta.top().first != "(") out.push(sta.top()), sta.pop();
          sta.pop();
        }
        else
        {
          while(sta.size() && sta.top().first != "(" && priority[sta.top().first] >= priority[i.first])
            out.push(sta.top()), sta.pop();
          sta.push(i);
        }
      }
      while(sta.size())
      {
        if(sta.top().first == "(" || sta.top().first == ")") cout << "F"; //Need to be handled
        out.push(sta.top()), sta.pop();
      }
      stack<double> res;
      while(out.size())
      {
        auto a = out.front();
        out.pop();
        cout << a.first << " ";
        if(a.second >= 50 && a.second <= 60) res.push(stod(a.first));
        else
        {
          double nd = res.top(), ans;
          res.pop();
          if(a.first == "!") ans = !nd;
          else
          {
            double nu = res.top();
            res.pop();
            if(a.first == "&&") ans = nu && nd;
            if(a.first == "||") ans = nu || nd;
            if(a.first == ">=") ans = nu >= nd;
            if(a.first == "<=") ans = nu <= nd;
            if(a.first == ">") ans = nu > nd;
            if(a.first == "<") ans = nu < nd;
            if(a.first == "==") ans = nu == nd;
            if(a.first == "!=") ans = nu != nd;
            if(a.first == "+") ans = nu + nd;
            if(a.first == "-") ans = nu - nd;
            if(a.first == "*") ans = nu * nd;
            if(a.first == "/") ans = nu / nd;
          }
          res.push(ans);
        }
      }
      return res.top();
    }
};
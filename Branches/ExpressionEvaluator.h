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
    queue<pair<string, int>> expression;
    unordered_map<string, int> priority;
    Evaluator(queue<pair<string, int>> expression): expression(expression)
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
      int n = expression.size();
      string s = "";
      for(int i = 0; i < n; i++)
      {
        auto tok = expression.front();
        expression.pop();
        if(tok.first == "+" || tok.first == "-")
        {
          if(s == "") s = tok.first;
          else if(tok.first == "-") s = (s == "+"? "-": "+");
        }
        else
        {
          if(s != "") expression.push(make_pair(s, 32));
          s = "";
          expression.push(tok);
        }
      }
    }
    double evaluate()
    {
      prepare();
      stack<pair<string, int>> sta;
      queue<pair<string, int>> out;
      while(expression.size())
      {
        auto i = expression.front();
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
        expression.pop();
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
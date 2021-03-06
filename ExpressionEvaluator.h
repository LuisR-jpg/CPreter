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
    Evaluator()
    {
      fillPriority();
    }
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
      pair<string, int> tok, last;
      string s = "";
      for(int i = 0; i < n; i++)
      {
        tok = expression.front();
        if(tok.first == "+" || tok.first == "-")
        {
          if(s == "") s = tok.first;
          else if(tok.first == "-") s = (s == "+"? "-": "+");
        }
        else
        {
          if(s != "")
          {
            if(last.first == ")" || (last.second >= 50 && last.second <= 60)) expression.push(make_pair(s, 32));
            else tok.first = s + tok.first;
          }
          s = "", last = tok;
          expression.push(tok);
        }
        expression.pop();
      }
    }
    double evaluate(queue<pair<string, int>> e)
    {
      expression = e;
      return evaluate();
    }
    double evaluate()
    {
      prepare();
      /*
      cout << endl;
      for(int i = 0; i < expression.size(); i++)
      {
        auto a = expression.front();
        cout << a.first << ": " << a.second << " " << endl;
        expression.push(a);
        expression.pop();
      }
      cout << endl;
      */
      stack<pair<string, int>> sta;
      queue<pair<string, int>> out;
      while(expression.size())
      {
        auto i = expression.front();
        if(i.second >= 50 && i.second <= 60) out.push(i);
        else if(i.first == "(") sta.push(i);
        else if(i.first == ")")
        {
          while(sta.size() && sta.top().first != "(") out.push(sta.top()), sta.pop();
          if(sta.empty())
          {
            cout << "\tERROR: Expression Mismatch.";
            exit(0);
          }
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
        if(sta.top().first == "(" || sta.top().first == ")"){
          cout << "\tERROR: Expression Mismatch.";
          exit(0);
        }
        out.push(sta.top()), sta.pop();
      }
      stack<double> res;
      while(out.size())
      {
        auto a = out.front();
        if(a.second == 54) a.first = to_string((int)a.first[0]);
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
        out.pop();
      }
      return res.top();
    }
};
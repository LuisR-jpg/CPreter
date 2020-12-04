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
      ///DEBUG
      int n = expression.size();
      for(int i = 0; i < n; i++){
        auto a = expression.front();
        cout << a.first << " ";
        expression.pop();
        expression.push(a);
      }
      cout << endl;
      ///DEBUG
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
            if(last.second >= 50 && last.second <= 60) expression.push(make_pair(s, 32));
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
      /*
      ///DEBUG
      cout << "\t\t\tjola" << endl;
      ///DEBUG
      */
      prepare();
      /*
      ///DEBUG
      int n = expression.size();
      for(int i = 0; i < n; i++){
        auto a = expression.front();
        cout << a.first << " ";
        expression.pop();
        expression.push(a);
      }
      cout << endl;
      ///DEBUG
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
        /*
        ///DEBUG
        cout << a.first << " ";
        ///DEBUG
        */
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
      /*
      ///DEBUG
      cout << endl;
      ///DEBUG
      */
      return res.top();
    }
};
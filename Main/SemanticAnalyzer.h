#include "SyntacticAnalyzer.h"
//#include "ExpressionEvaluator.h"
#include <map>
#include <string>
map<string, pair<string, void*>> SymbolTable;
/*
double evaluate()
{
            else if(!tok.second)
        {
          auto var = SymbolTable[tok.first];
          if(var.first == "db") expression.push(make_pair(to_string((int)*((bool*)var.second)), 52));
          if(var.first == "dc") expression.push(make_pair(to_string((int)(*((char*)var.second))), 54));
          if(var.first == "di") expression.push(make_pair(to_string(*((int*)var.second)), 50));
          if(var.first == "dd") expression.push(make_pair(to_string(*((double*)var.second)), 51));
        }
}
*/
void Declaration::run()
{
    if(SymbolTable.find(name) != SymbolTable.end())
    {
        cout << "Variable Repetida..." << endl;
        exit(0);
    }
    void *pointer;
    /*
    cout << "\t\t\t\t";
    if(type == "db") cout << "bool", pointer = new bool;
    else if(type == "dc") cout << "char", pointer = new char;
    else if(type == "di") cout << "int", pointer = new int;
    else if(type == "dd") cout << "double", pointer = new double;
    else cout << "string", pointer = new string;
    cout << endl;
    */
    SymbolTable.insert(make_pair(name, make_pair(type, pointer)));
}
void Assignment::run()
{
    auto a = t_expresion.front();
    auto var = SymbolTable[name];
    cout << "\t\t\t\t\t" << name << ": ";
    if(var.first == "ds") var.second = new string(a.first), 
        cout << *((string*)var.second);
    else if(var.first == "dc") var.second = new char(a.first[0]),
        cout << *((char*)var.second);
    else
    {
        double c = evaluator.evaluate(t_expresion);
        if(var.first == "db") var.second = new bool(c),
            cout << *((bool*)var.second);
        if(var.first == "di") var.second = new int(c), 
            cout << *((int*)var.second);
        if(var.first == "dd") var.second = new double(c),
            cout << *((double*)var.second);
    }
    SymbolTable[name] = var;
    cout << endl;
}
void fp::run()
{
    cout << "\t\t\t\t\t...";
    auto a = t_expresion.front();
    if(a.second == 53) cout << a.first;
    else if(a.second == 54 && t_expresion.size() == 1) cout << a.first;
    else
    {
        auto var = SymbolTable[a.first];
        if(!a.second)
        {
            if(var.first == "ds") cout << *((string*)var.second);
            else if(t_expresion.size() == 1 && var.first == "dc") cout << *((char*)var.second);
        }
        else cout << evaluator.evaluate(t_expresion);
    }
    //else cout << evaluator.evaluate(t_expresion);
    cout << endl;
}
void fr::run()
{
    Assignment a;
    queue<pair<string, int>> q;
    string type = SymbolTable[name].first;
    if(type == "ds")
    {
        string s;
        cin >> s;
        q.push(make_pair(s, 53));
        //getchar();
    }
    if(type == "dc")
    {
        char c;
        cin >> c;
        string s = "";
        s += c;
        q.push(make_pair(s, 54));
    }
    a.insert(name, q);
    a.run();
    /*
    if(SymbolTable.find(name) == SymbolTable.end())
    {
        cout << "Trying to read in non-declarated variable.";
        exit(0);
    }
    auto var = SymbolTable[name];
    if(var.first == "ds") cin >> *((string*)var.second);
    */
}
void si::run()
{
    return;
}
void cf::run()
{
    return;
}
void cw::run()
{
    return;
}
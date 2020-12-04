#include "SyntacticAnalyzer.h"
#include <map>
map<string, pair<string, void*>> SymbolTable;
void Declaration::run()
{
    if(SymbolTable.find(name) != SymbolTable.end())
    {
        cout << "Variable Repetida..." << endl;
        exit(0);
    }
    void *pointer;
    cout << "\t\t\t\t";
    if(type == "db") cout << "bool", pointer = new bool;
    else if(type == "dc") cout << "char", pointer = new char;
    else if(type == "di") cout << "int", pointer = new int;
    else if(type == "dd") cout << "double", pointer = new double;
    else cout << "string", pointer = new string;
    cout << endl;
    SymbolTable.insert(make_pair(name, make_pair(type, pointer)));
}
void Assignment::run()
{
    return;
}
void fp::run()
{
    cout << "\t...";
    auto a = t_expresion.front();
    if(a.second == 53) cout << a.first;
    else cout << evaluator.evaluate(t_expresion);
    cout << endl;
}
void fr::run()
{
    return;
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
#include "SyntacticAnalyzer.h"
#include <map>
map<string, pair<string, void*>> SymbolTable;
void Declaration::run()
{
    if(type == "dv");
    if(type == "di");
    if(type == "dd");
}
void Assignment::run()
{
    return;
}
void fp::run()
{
    cout << "\tCorriendo...\n\t";
    auto a = t_expresion.front();
    if(a.second == 53) cout << a.first;
    else cout << evaluator.evaluate(t_expresion);
    cout << endl;
    /*
    while(t_expresion.size())
    {
        auto a = t_expresion.front();
        if(a.second == 53) cout << a.first << endl;
        else cout << evaluator.evaluate(t_expresion);
        t_expresion.pop();
    }
    */
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
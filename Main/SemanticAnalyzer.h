#include "SyntacticAnalyzer.h"
void Declaration::run()
{
    return;
}
void Assignment::run()
{
    return;
}
void fp::run()
{
    while(t_expresion.size())
    {
        auto a = t_expresion.front();
        if(a.second == 53) cout << "\tCorriendo...\n\t" << a.first << endl;
        t_expresion.pop();
    }
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
//#include "SyntacticAnalyzer.h"
#include "SemanticAnalyzer.h"
int main()
{
    SyntacticAnalyzer s;
    while(s.instruction.size())
    {
        auto a = s.instruction.front();
        a -> print("    ");
        cout << endl;
        a -> run();
        s.instruction.pop();
    }
    return 0;
}

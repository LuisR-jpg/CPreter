//#include "SyntacticAnalyzer.h"
#include "SemanticAnalyzer.h"
int main()
{
    SyntacticAnalyzer s;
    cout << "holos" << endl;
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

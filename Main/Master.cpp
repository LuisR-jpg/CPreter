//#include "SyntacticAnalyzer.h"
#include "SemanticAnalyzer.h"
int main()
{
    SyntacticAnalyzer s;
    while(!s.instruction.empty())
        s.instruction.front() -> print("    "),s.instruction.pop() , cout << endl;
    return 0;
}

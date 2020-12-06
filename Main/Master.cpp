//#include "SyntacticAnalyzer.h"
#include "SemanticAnalyzer.h"
bool debug;
void CPreter(string filename)
{
    SyntacticAnalyzer s(filename);
    while(s.instruction.size())
    {
        auto a = s.instruction.front();
        if(debug){
            a -> print("    ");
            cout << endl;
        }
        a -> run();
        s.instruction.pop();
    }
}
int main(int argc, char** argv)
{
    debug = argc > 2;
    if(argc < 2) cout << "Please enter file name.";
    else CPreter(argv[1]);
    return 0;
}

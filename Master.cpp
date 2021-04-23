#include "SemanticAnalyzer.h"
#include <fstream>
bool debug;
void CPreter(string filename)
{
    SyntacticAnalyzer s(filename);
    ofstream file;
    file.open("CPRtoCPP.cpp");
    file << "#include <bits/stdc++.h>\nusing namespace std;\nint main(){\n";
    while(s.instruction.size())
    {
        //cout << "Instrucciones: ";
        auto a = s.instruction.front();
        if(debug){
            a -> print("    ");
            cout << endl;
        }
        a -> run();
        file << a -> translate("    ");
        s.instruction.pop();

    }
    file << "return 0;\n}";
    file.close();
}
int main(int argc, char** argv)
{
    debug = argc > 2;
    if(argc < 2) cout << "\tERROR: Please enter file name.";
    else CPreter(argv[1]);
    return 0;
}
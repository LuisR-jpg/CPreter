#include "LexicalAnalyzer.h"
int main()
{
    AnalizadorLexico a;
    vector<pair<string, int>> aux = a.getToken();
    for(int i = 0; i < aux.size(); i++){
      cout << aux[i].first << " " << aux[i].second << endl;
    }
    return 0;
}

#include "LexicalAnalyzer.h"
int main()
{
  /*
    Read r;
    string s = r.getCode();
    AnalizadorLexico a(s);
    cout << endl;
    */
    AnalizadorLexico a;
    /*
    cout << a.token.size() << endl;
    for(int i = 0; i < a.token.size(); i++)
        cout << a.token[i].first << " " << a.token[i].second << endl;
	*/
    vector<pair<string, int>> aux = a.getToken();
    cout << aux.size();
    for(int i = 0; i < aux.size(); i++){
      cout << aux[i].first << " " << aux[i].second << endl;
    }
    return 0;
}

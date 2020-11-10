#include <iostream>
#include <vector>
#include <set>
using namespace std;
class AnalizadorLexicoV2
{
    public:
        string code;
        vector<pair<string,int>> token;
	set<string> s;
        AnalizadorLexicoV2()
        {
            this -> code = "";
        }
        AnalizadorLexicoV2(string code)
        {
            this -> code = code;
	    fillSet();
            tokens(code);
        }
	void fillSet(){
	  vector<string> tipo = {"db", "di", "dd", "ds"};
	  for(int i = 0; i < tipo.size(); i++) s.insert(tipo[i]);
	}
	void insert(string a){
	  if(s.find(a) != s.end()) insert(a, 10);
	  else insert(a, 0);
	}
	void insert(string a, int b){
	  token.push_back(make_pair(a, b));
	}
        void tokens(string code)
        {
            int esp = 0;
            string aux = "";
            for(int i = 0; i < code.size(); i++)
            {
                if(code[i] == ' ')
                {
                    if(++esp == 4)
		      insert("\\t", 50), esp = 0;
		      //token.push_back(make_pair("\\t",50)), esp = 0;
                    continue;
                }
                if(isalpha(code[i]))
                {
                    while(isalnum(code[i]) || code[i] == '_')
                        aux += code[i], i++;
		    insert(aux);
                    aux = "";
                }
                if(isdigit(code[i]))//En estos, checar casos como 15*9. Eliminar else? else if(isdigit(code[i]))
                {
                    while(isdigit(code[i]) || code[i]=='.')
                        aux += code[i], i++;
		    insert(aux, 60);
                    //token.push_back(make_pair(aux, 60));
                    aux = "";
                }
                if(code[i] == '"')
                {
		  /*
                    i++;
                    while(code[i] != '"')
                        aux += code[i], i++;
		  */
		    while(code[++i] != '"')
			aux += code[i];
		    insert(aux, 70);
                    //token.push_back(make_pair(aux, 70));
                    i++, aux = "";
                }
                if(ispunct(code[i]))
                {
                    if(code[i+1] == '=' || code[i+1] == '|' || code[i+1] == '&' || code[i+1] == '>')
		      aux += code[i], aux += code[i+1], i++;
                    else aux += code[i];
                    token.push_back(make_pair(aux, 30));
                    aux = "";
                }
                if(code[i] == '\n') token.push_back(make_pair("\\n",50));
                esp = 0;
            }

        }
};

int main()
{
    AnalizadorLexicoV2 a("    dd variable1=35.4\nds variable2\nvariable2=\"hola\"\nsi variable1<=variable2");//("    db\ndi")
    for(int i = 0; i < a.token.size(); i++)
        cout << a.token[i].first << " " << a.token[i].second << endl;
    return 0;
}

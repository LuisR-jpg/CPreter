#include <iostream>
#include <vector>
#include <map>
using namespace std;
class AnalizadorLexicoV2
{
    public:
        string code;
        vector<pair<string,int>> token;
	map<string, int> m;
        AnalizadorLexicoV2()
        {
            this -> code = "";
        }
        AnalizadorLexicoV2(string code)
        {
            this -> code = code;
	    mapear();
            tokens(code);
        }
	void mapear(){
	  vector<string> tipo, inst, espe, jera, arit, rela, logi, espa;
	  tipo = {"db", "di", "dd", "ds"};
	  inst = {"si", "se", "cf", "cw", "fp", "fr"};
	  espe = {"->", ",", "="};
	  jera = {"(", ")"};
	  arit = {"+", "-", "*", "/"};
	  rela = {"<", ">", "==", "!=", "<=", ">="};
	  logi = {"&&", "||", "!"};
	  espa = {"\\t", "\\n"};
	  for(int i = 0; i < tipo.size(); i++) m.insert(make_pair(tipo[i], 10));
	  for(int i = 0; i < inst.size(); i++) m.insert(make_pair(inst[i], 20));
	  for(int i = 0; i < espe.size(); i++) m.insert(make_pair(espe[i], 30));
	  for(int i = 0; i < jera.size(); i++) m.insert(make_pair(jera[i], 31));
	  for(int i = 0; i < arit.size(); i++) m.insert(make_pair(arit[i], 32));
	  for(int i = 0; i < rela.size(); i++) m.insert(make_pair(rela[i], 33));
	  for(int i = 0; i < logi.size(); i++) m.insert(make_pair(logi[i], 34));
	  for(int i = 0; i < espa.size(); i++) m.insert(make_pair(espa[i], 50));
	}
	int tokenize(string a){
	  if(m.find(a) != m.end()) return m[a];
	  return 0;
	}
	void insert(string a){
	  token.push_back(make_pair(a, tokenize(a)));
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
		      insert("\\t");
		      //token.push_back(make_pair("\\t",50)), esp = 0;
                    continue;
                }
                if(isalpha(code[i]))
                {
                    while(isalnum(code[i]) || code[i] == '_')
                        aux += code[i], i++;
		    /*
                    if(aux == "db") token.push_back(make_pair("db", 10));
                    else if(aux == "di") token.push_back(make_pair("di", 10));
                    else if(aux == "dd") token.push_back(make_pair("dd", 10));
                    else if(aux == "ds") token.push_back(make_pair("ds", 10));
                    else if(aux != "") token.push_back(make_pair(aux, 0));
		    */
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

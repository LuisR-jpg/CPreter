#include<iostream>
#include<vector>
using namespace std;

class AnalizadorLexicoV2
{
    public:
        string code;
        vector<pair<string,int>> token;
        AnalizadorLexicoV2()
        {
            this -> code = "";
        }
        AnalizadorLexicoV2(string code)
        {
            this -> code = code;
            tokens(code);
        }
        void tokens(string code)
        {
            int esp = 0;
            string aux = "";
            for(int i = 0; i < code.size(); i++)
            {
                //cout << i << " " << code[i] << endl;
                //cout << code[code.size()-1] << endl;
                if(code[i] == ' ')
                {
                    //esp++;
                    if(++esp == 4) token.push_back(make_pair("\\t",50)), esp = 0;
                    continue;
                }
                if(isalpha(code[i]))//else if(isalpha(code[i]))
                {
                    //while(code[i]!=' '&&code[i]!='\n'&&code[i]!='\t')
                    while(isalnum(code[i])||code[i]=='_')
                        aux+=code[i], i++;//cout << code[i] << endl,
                    if(aux=="db") token.push_back(make_pair("db",10));
                    else if(aux=="di") token.push_back(make_pair("di",10));
                    else if(aux=="dd") token.push_back(make_pair("dd",10));
                    else if(aux=="ds") token.push_back(make_pair("ds",10));
                    else if(aux!="") token.push_back(make_pair(aux,00));
                    aux = "";
                }
                if(isdigit(code[i]))//En estos, checar casos como 15*9. Eliminar else? else if(isdigit(code[i]))
                {
                    while(isdigit(code[i])||code[i]=='.')
                        aux+=code[i], i++;//cout << code[i] << endl,
                    token.push_back(make_pair(aux,60));
                    aux = "";
                }
                if(code[i]=='"')//else if(code[i]=='"')
                {
                    i++;
                    while(code[i]!='"')
                        aux+=code[i], i++;//cout << code[i] << endl,
                    token.push_back(make_pair(aux,70));
                    i++;
                    aux = "";
                }
                if(ispunct(code[i]))//else if(ispunct(code[i]))<
                {
                    //while(ispunct(code[i]))
                        //aux+=code[i], i++;//cout << code[i] << endl,
                    if(code[i+1]=='='||code[i+1]=='|'||code[i+1]=='&'||code[i+1]=='>') aux += code[i], aux += code[i+1], i++;
                    else aux += code[i];
                    token.push_back(make_pair(aux,30));
                    aux = "";
                }
                if(code[i]=='\n') token.push_back(make_pair("\\n",50));
                esp = 0;
                //aux = "";
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

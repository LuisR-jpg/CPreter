#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include "Read.h"
using namespace std;
class LexicalAnalyzer
{
    public:
        string code;
        vector<pair<string,int>> token;
        set<string> type;
        set<string> instruction;
        LexicalAnalyzer()
        {
            Read r;
            code = r.getCode();
        }
        vector<pair<string, int>> getToken()
        {
            fillSet();
            tokens(code);
            return token;
    	}
        void fillSet()
        {
            vector<string> tipo = {"dv", "db", "dll", "dl", "di", "df", "dd", "dc", "ds"};
            for(int i = 0; i < tipo.size(); i++) type.insert(tipo[i]);
            vector<string> instruccion = {"si", "sef", "se", "cf", "cw", "fp", "fr"};
            for(int i = 0; i < instruccion.size(); i++) instruction.insert(instruccion[i]);
        }
        void insert(string a)
        {
            if(a == "true" || a == "false") insert(a, 52);// 52 = palabra reservada (valor bool)
            else if(type.find(a) != type.end()) insert(a, 10);// 10 = palabra reservada (tipo de dato)
            else if(instruction.find(a) != instruction.end()) insert(a, 20);// 20 = palabra reservada (instruccion)
            else insert(a, 0);//00 = identificador
        }
        void insert(string a, int b)
        {
            token.push_back(make_pair(a, b));
        }
        void tokens(string code)
        {
            int esp = 0;
            string aux = "";
            for(int i = 0; i < code.size(); i++)
            {
                if(code[i] == ' ' || code[i] == '\t')
                {
                    if(++esp == 4 || code[i] == '\t') insert("\\t", 60), esp = 0;//60 = \t (identación)
                    continue;
                }
                if(isalpha(code[i]))
                {
                    while(isalnum(code[i]) || code[i] == '_')
                        aux += code[i], i++;
                    insert(aux);
                    aux = "";
                }
                if(isdigit(code[i]))
                {
                    bool intodouble = true;
                    int pun = 0;
                    while(isdigit(code[i]) || code[i]=='.')//Caso 10.5.2.1 = token inválido///////////////////
                    {
                        aux += code[i];
                        if(code[i] == '.') intodouble = false, pun++;
                        i++;
                    }
                    if(!intodouble && pun == 1) insert(aux, 51);//51 = valor decimal
                    else if(pun>1)
                    {
                        cout << "Error" << endl;
                        return;
                    }
                    else insert(aux, 50);//50 = valor entero
                    aux = "";
                }
                if(code[i] == '"')
                {
                    while(code[++i] != '"')
                        aux += code[i];
                    insert(aux, 53);//53 = valor string
                    i++, aux = "";
                }
                if(code[i] == '\'')
                {
                    aux += code[++i];
                    insert(aux, 54);//54 = valor char
                    i+=2, aux = "";
                }
                if(ispunct(code[i]))
                {
                    if(code[i+1] == '=' || code[i+1] == '|' || code[i+1] == '&' || code[i+1] == '>')
                        aux += code[i], aux += code[i+1], i++;
                    else aux += code[i];
                    if(aux == "->" || aux == "," || aux == "=" || aux == ":") insert(aux,30);//30 = Símbolos especiales
                    else if(aux == "(" || aux == ")") insert(aux,31);//31 = Símbolos de jerarquía
                    else if(aux == "+" || aux == "-" || aux == "*" || aux == "/") insert(aux,32);//32 = Símbolos de aritmética
                    else if(aux == "<" || aux == ">" || aux[1] == '=') insert(aux,33);//33 = Símbolos relacionales
                    else if(aux == "!" || aux == "&&" || aux == "||") insert(aux,34);//34 = Símbolos lógicos
                    aux = "";
                }
                if(code[i] == '\n') token.push_back(make_pair("\\n",61));//61 = \n (salto de línea)
                esp = 0;
            }
        }
};

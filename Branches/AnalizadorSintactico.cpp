#include "LexicalAnalyzer.h"
#include<iostream>
#include<vector>
using namespace std;

class Instruction
{
    public:
        Instruction()
        {

        }
        void run()
        {
            return;
        }
};

class Declaration:public Instruction
{
    public:
        string name;
        string type;
        Declaration()
        {
            this -> name = "";
            this -> type = "";
        }
        /*Declaration(string name, string type)
        {
            this -> name = name;
            this -> type = type;
        }*/
        void insert(string name, string type)
        {
            this -> name = name;
            this -> type = type;
        }
        void run()
        {
            return;
        }
        friend ostream& operator<<(ostream& output, Declaration& d)
        {
            output << d.name << " " << d.type;
            return output;
        }
};

class Assignment:public Instruction
{
    public:
        string name;
        vector<string> t_expresion;
        //Expresion expresion;
        Assignment()
        {
            this -> name = "";
        }
        void insert(string name,vector<string> t_expresion)
        {
            this -> name = name;
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void run()
        {
            return;
        }
        friend ostream& operator<<(ostream& output, Assignment& a)
        {
            output << a.name << " = ";
            for(int i = 0; i<a.t_expresion.size(); i++)
                output << a.t_expresion[i];
            return output;
        }
};

class fp:public Instruction
{
    public:
        vector<string> t_expresion;
        //Expresion expresion;
        fp()
        {

        }
        void insert(vector<string> t_expresion)
        {
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void run()
        {
            return;
        }
        friend ostream& operator<<(ostream& output, fp& p)
        {
            output << "fp ";
            for(int i = 0; i<p.t_expresion.size(); i++)
                output << p.t_expresion[i];
            return output;
        }
};

class fr:public Instruction
{
    public:
        string name;
        fr()
        {
            this -> name = "";
        }
        fr(string name)
        {
            this -> name = name;
        }
        void insert(string name)
        {
            this -> name = name;
        }
        void run()
        {
            return;
        }
        friend ostream& operator<<(ostream& output, fr& r)
        {
            output << "fr " << r.name;
            return output;
        }
};

class si:public Instruction
{
    public:
        //Expresion expresion;
        vector<string> t_expresion;
        vector<Instruction> instructions_si;
        vector<Instruction> instructions_se;
        si()
        {

        }
        void insert_expresion(vector<string> t_expresion)
        {
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void insert_instruction_si(vector<Instruction> instructions_si)
        {
            this -> instructions_si = instructions_si;
        }
        void insert_instruction_se(vector<Instruction> instructions_se)
        {
            this -> instructions_se = instructions_se;
        }
        void run()
        {
            return;
        }
        friend ostream& operator<<(ostream& output, si& s)
        {
            output << "si ";
            for(int i = 0; i<s.t_expresion.size(); i++)
                output << s.t_expresion[i];
            return output;
        }
};

class cf:public Instruction
{
    public:
        string name;
        int inital_value;
        int final_value;
        int increment;
        vector<Instruction> instruction;
        void run()
        {
            return;
        }
};

class cw:public Instruction
{
    public:
        //Expresion expresion;
        vector<string> instructions;
        void run()
        {
            return;
        }
};

class SyntacticAnalyzer
{
    public:
        AnalizadorLexico a;
        vector<pair<string,int>> tokens;
        vector<Instruction> instruction;
        SyntacticAnalyzer()
        {
            this -> tokens = a.getToken();
            this -> instruction = instructions(tokens, 0);
        }
        vector<Instruction> instructions(vector<pair<string,int>> tokens, int indentation)
        {
            vector<Instruction> instruction;
            pair<string, int> last;
            for(int i = 0; i < tokens.size(); i++)///En otra función, recursiva.
            {
                //cout << tokens[i].first << " " << tokens[i].second << endl;
                if((tokens[i].second == 10 && tokens[i+1].second == 0) || (tokens[i].first == "," && last.second == 10))///Declaration
                {
                    //cout << tokens[i].first << " " << tokens[i+1].first << endl;
                    Declaration d;
                    if(tokens[i].second == 10) last = tokens[i];
                    if(tokens[i].second == 10) d.insert(tokens[i].first,tokens[i+1].first);
                    else d.insert(last.first,tokens[i+1].first);
                    cout << d << endl;
                    instruction.push_back(d);
                    i++;
                }

                if(tokens[i].first == "=")///Assignment
                {
                    vector<string> t_expresion;
                    string name;
                    Assignment a;
                    if(tokens[i-1].second == 0) name = tokens[i-1].first;
                    else
                    {
                        cout << "Error" << endl;
                        return instruction;///Quitar/Cambiar
                    }
                    while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                        t_expresion.push_back(tokens[i+1].first),i++;
                    a.insert(name,t_expresion);
                    cout << a << endl;
                    instruction.push_back(a);
                }

                if((tokens[i].first == "fr" && tokens[i+1].second == 0) || (tokens[i].first == "," && last.first == "fr"))///Read
                {
                    //cout << tokens[i].first << " " << tokens[i+1].first << endl;
                    fr r;
                    if(tokens[i].second == 20) last = tokens[i];
                    r.insert(tokens[i+1].first);
                    cout << r << endl;
                    i++;
                    instruction.push_back(r);
                }

                if(tokens[i].first == "fp" || (tokens[i].first == "," && last.first == "fp"))///Print
                {
                    //cout << tokens[i].first << " " << tokens[i+1].first << endl;
                    vector<string> t_expresion;
                    fp p;
                    if(tokens[i].second == 20) last = tokens[i];
                    while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                        t_expresion.push_back(tokens[i+1].first),i++;
                    p.insert(t_expresion);
                    cout << p << endl;
                    instruction.push_back(p);
                }

                if(tokens[i].first == "si")
                {
                    si sif;
                    vector<string> t_expresion;
                    while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                        t_expresion.push_back(tokens[i+1].first),i++;
                    sif.insert_expresion(t_expresion);
                    cout << sif << endl;
                    //
                    vector<pair<string,int>> tokens_i;
                    tokens_i.assign(tokens.begin()+(i+1),tokens.end());

                    /*cout << endl;
                    for(int j = 0; j < tokens_i.size(); j++)
                        cout << tokens_i[j].first << " " << tokens_i[j].second << endl;
                    cout << endl;*/
                    //if(tokens[i].first == "se") cout << "hola";
                }
            }
            return instruction;
        }
};

int main()
{
    SyntacticAnalyzer s;
    cout << endl;
    for(int i = 0; i < s.tokens.size(); i++)
        cout << s.tokens[i].first << " " << s.tokens[i].second << endl;
    //for(int i = 0; i < s.instruction.size(); i++)
        //cout << s.instruction[i] << endl;
    return 0;
}

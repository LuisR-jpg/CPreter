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
        virtual void print() = 0;
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
        Declaration(string name, string type)
        {
            this -> name = name;
            this -> type = type;
        }
        void insert(string name, string type)
        {
            this -> name = name;
            this -> type = type;
        }
        void run()
        {
            return;
        }
        void print()
        {
            cout << name << " " << type;
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
        void print()
        {
            cout << name << " = ";
            for(int i = 0; i<t_expresion.size(); i++)
                cout << t_expresion[i];
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
        void print()
        {
            cout << "fp ";
            for(int i = 0; i<t_expresion.size(); i++)
                cout << t_expresion[i];
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
        void print()
        {
            cout << "fr " << name;
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
        vector<pair<Instruction*,int>> instructions_si;
        vector<pair<Instruction*,int>> instructions_se;
        si()
        {

        }
        ~si()
        {
            /*for(int i=0;i<instructions_si.size();i++)
                delete instructions_si[i];
            for(int i=0;i<instructions_se.size();i++)
                delete instructions_se[i];*/
        }
        void insert_expresion(vector<string> t_expresion)
        {
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void insert_instruction_si(vector<pair<Instruction*,int>> instructions_si)
        {
            this -> instructions_si = instructions_si;
        }
        void insert_instruction_se(vector<pair<Instruction*,int>> instructions_se)
        {
            this -> instructions_se = instructions_se;
        }
        void run()
        {
            return;
        }
        void print()
        {
            cout << "si ";
            for(int i = 0; i<t_expresion.size(); i++)
                cout << t_expresion[i];
            cout << endl;
            for(int i = 0; i < instructions_si.size(); i++)
            {
                for(int j = 0; j < instructions_si[i].second; j++)
                    cout << "    ";
                instructions_si[i].first -> print(), (i != instructions_si.size() - 1 ? cout << endl : cout << "");
            }
            if(!instructions_se.empty())
            {
                cout << endl;
                for(int j = 0; j < instructions_si[0].second - 1; j++)
                    cout << "    ";
                cout << "se" << endl;
                for(int i=0;i<instructions_se.size();i++)
                {
                    for(int j = 0; j < instructions_se[i].second; j++)
                        cout << "    ";
                    instructions_se[i].first -> print(), (i != instructions_se.size() - 1 ? cout << endl : cout << "");
                }
            }
        }
        friend ostream& operator<<(ostream& output, si& s)
        {
            output << "si [";
            for(int i = 0; i<s.t_expresion.size(); i++)
                output << s.t_expresion[i] << ",";
            output << "]";
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
        void print()
        {
            //cout << name << " " << type;
        }
};

class cw:public Instruction
{
    public:
        //Expresion expresion;
        vector<string> t_expresion;
        vector<pair<Instruction*,int>> instructions_cw;
        cw()
        {

        }
        void insert_expresion(vector<string> t_expresion)
        {
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void insert_instruction_cw(vector<pair<Instruction*,int>> instructions_cw)
        {
            this -> instructions_cw = instructions_cw;
        }
        void run()
        {
            return;
        }
        void print()
        {
            cout << "cw ";
            for(int i = 0; i<t_expresion.size(); i++)
                cout << t_expresion[i];
            cout << endl;
            for(int i = 0; i<instructions_cw.size(); i++)
            {
                for(int j = 0; j < instructions_cw[i].second; j++)
                    cout << "    ";
                instructions_cw[i].first -> print(), (i != instructions_cw.size() - 1 ? cout << endl : cout << "");
            }
        }
        friend ostream& operator<<(ostream& output, cw& w)
        {
            output << "cw ";
            for(int i = 0; i<w.t_expresion.size(); i++)
                output << w.t_expresion[i];
            return output;
        }
};

/*for(int j = 0; j < indentation; j++)
{
    cout << "    ";
}*/

class SyntacticAnalyzer
{
    public:
        AnalizadorLexico a;
        vector<pair<string,int>> tokens;
        vector<pair<Instruction*,int>> instruction;
        int con = 0;
        SyntacticAnalyzer()
        {
            this -> tokens = a.getToken();
            this -> instruction = instructions(tokens, 0);
        }
        ~SyntacticAnalyzer()
        {
            for(int i=0;i<instruction.size();i++)
                delete instruction[i].first;
        }
        vector<pair<Instruction*,int>> instructions(vector<pair<string,int>> tokens, int indentation)
        {
            vector<pair<Instruction*,int>> instruction;
            pair<string, int> last;
            string last_i;
            int indent = 0;
            for(int i = 0; i < tokens.size(); i++)
            {
                con = i;
                //cout << i << " " << tokens[i].first << " " << tokens[i].second << endl;
                if(tokens[i].second == 60 || tokens[i].second == 61)
                {
                    if(tokens[i].second == 61) indent = 0;
                    if(tokens[i].second == 60) indent++;
                    continue;
                }
                /*if(indentation != 0 && indent == 0)
                {
                    con--;
                    return instruction;
                }*/
                //else indent --;
                if(indent == indentation)
                {
                    //cout << indent << " " << indentation << endl;
                    if((tokens[i].second == 10 && tokens[i+1].second == 0) || (tokens[i].first == "," && last.second == 10))///Declaration
                    {
                        //cout << tokens[i].first << " " << tokens[i+1].first << endl;
                        Declaration* d = new Declaration;
                        if(tokens[i].second == 10) last = tokens[i];
                        if(tokens[i].second == 10) d -> insert(tokens[i].first,tokens[i+1].first);
                        else d -> insert(last.first,tokens[i+1].first);
                        //cout << d << endl;
                        instruction.push_back(make_pair(d,indent));
                        i++, con++;
                    }

                    if(tokens[i].first == "=")///Assignment
                    {
                        vector<string> t_expresion;
                        string name;
                        Assignment* a = new Assignment;
                        if(tokens[i-1].second == 0) name = tokens[i-1].first;
                        else
                        {
                            cout << "Error" << endl;
                            return instruction;///Quitar/Cambiar
                        }
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1].first),i++, con++;
                        a -> insert(name,t_expresion);
                        //cout << a << endl;
                        instruction.push_back(make_pair(a,indent));
                    }

                    if((tokens[i].first == "fr" && tokens[i+1].second == 0) || (tokens[i].first == "," && last.first == "fr"))///Read
                    {
                        //cout << tokens[i].first << " " << tokens[i+1].first << endl;
                        fr* r = new fr;
                        if(tokens[i].second == 20) last = tokens[i];
                        r -> insert(tokens[i+1].first);
                        //cout << r << endl;
                        i++, con++;
                        instruction.push_back(make_pair(r,indent));
                    }

                    if(tokens[i].first == "fp" || (tokens[i].first == "," && last.first == "fp"))///Print
                    {
                        //cout << tokens[i].first << " " << tokens[i+1].first << endl;
                        vector<string> t_expresion;
                        fp* p = new fp;
                        if(tokens[i].second == 20) last = tokens[i];
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1].first),i++, con++;
                        p -> insert(t_expresion);
                        //cout << p << endl;
                        instruction.push_back(make_pair(p,indent));
                    }








                    if(tokens[i].first == "si")///If
                    {
                        si* sif = new si;
                        vector<string> t_expresion;
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1].first), i++, con++;
                        sif -> insert_expresion(t_expresion);

                        vector<pair<string,int>> tokens_i;
                        tokens_i.assign(tokens.begin()+(i+1),tokens.end());
                        con = 0;
                        cout << endl << i+1 << " si i " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                        sif -> insert_instruction_si(instructions(tokens_i,indentation+1));
                        i += con;
                        con = 0;
                        cout << endl << i+1 << " si f " << tokens[i+1].first << " " << indent << " " << indentation << endl;

                        if(tokens[i+1].first == "se") i++, con++;//if(tokens[i].second == 61 || tokens[i].second == 60) i++, con++;
                        if(tokens[i].first == "se")
                        {
                            tokens_i.assign(tokens.begin()+(i+1),tokens.end());
                            con = 0;
                            cout << endl << i+1 << " se i " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                            sif -> insert_instruction_se(instructions(tokens_i,indentation+1));
                            i += con;
                            con = 0;
                            cout << endl << i+1 << " se f " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                        }

                        instruction.push_back(make_pair(sif,indent));
                        //if(indentation > 0 && tokens[i].second != 60) return instruction;
                        if(indentation > 0 && tokens[i].second != 60 && tokens[i+1].second != 60) return instruction;
                    }

                    if(tokens[i].first == "cf")
                    {

                    }

                    if(tokens[i].first == "cw")///While
                    {
                        cw* w = new cw;
                        vector<string> t_expresion;
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1].first),i++, con++;
                        w -> insert_expresion(t_expresion);

                        vector<pair<string,int>> tokens_i;
                        tokens_i.assign(tokens.begin()+(i+1),tokens.end());
                        con = 0;
                        cout << endl << i+1 << " cw i " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                        w -> insert_instruction_cw(instructions(tokens_i,indentation+1));
                        i += con;
                        cout << endl << i+1 << " cw f " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                        con = 0;

                        instruction.push_back(make_pair(w,indent));
                        //if(indentation > 0 && tokens[i].second != 60) return instruction;
                        if(indentation > 0 && tokens[i].second != 60 && tokens[i+1].second != 60) return instruction;
                    }
                    //indent = 0;







                }////////////////////////////Error con la separación en si, se, cw. Checar. Identación de las anidadas.
                else if(indent > indentation)
                {
                    cout << "Indentation error " << i << " " << tokens[i].first << " " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                    //exit(34404);
                    //return instruction;
                }
                else if(indent < indentation)
                {
                    cout << "Aber " << i << " " << indent << " " << tokens[i].first << " " << tokens[i+1].first << endl;
                    //if(indent == 0)
                    return instruction;
                }
            }
            return instruction;
        }
};

int main()
{
    SyntacticAnalyzer s;
    cout << "Instrucciones:" << endl;
    //for(int i = 0; i < s.tokens.size(); i++)
        //cout << i << " " << s.tokens[i].first << " " << s.tokens[i].second << endl;
    for(int i = 0; i < s.instruction.size(); i++)
        cout << endl << "Instruccion " << i << endl,s.instruction[i].first -> print(), cout << endl;
    return 0;
}

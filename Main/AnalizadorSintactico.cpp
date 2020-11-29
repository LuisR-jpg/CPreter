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
        Declaration(string type, string name)
        {
            this -> name = name;
            this -> type = type;
        }
        void insert(string type, string name)
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
            cout << type << " " << name;
        }
        friend ostream& operator<<(ostream& output, Declaration& d)
        {
            output << d.type << " " << d.name;
            return output;
        }
};

class Assignment:public Instruction
{
    public:
        string name;
        vector<pair<string,int>> t_expresion;
        //Expresion expresion;
        Assignment()
        {
            this -> name = "";
        }
        void insert(string name,vector<pair<string,int>> t_expresion)
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
                cout << t_expresion[i].first;
        }
        friend ostream& operator<<(ostream& output, Assignment& a)
        {
            output << a.name << " = ";
            for(int i = 0; i<a.t_expresion.size(); i++)
                output << a.t_expresion[i].first;
            return output;
        }
};

class fp:public Instruction
{
    public:
        vector<pair<string,int>> t_expresion;
        //Expresion expresion;
        fp()
        {

        }
        void insert(vector<pair<string,int>> t_expresion)
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
                cout << t_expresion[i].first;// << " " << t_expresion[i].second;
        }
        friend ostream& operator<<(ostream& output, fp& p)
        {
            output << "fp ";
            for(int i = 0; i<p.t_expresion.size(); i++)
                output << p.t_expresion[i].first;// << " " << p.t_expresion[i].second;
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
        vector<pair<string,int>> t_expresion;
        vector<pair<Instruction*,int>> instructions_si;
        vector<pair<Instruction*,int>> instructions_se;
        si()
        {

        }
        ~si()
        {
            for(int i=0;i<instructions_si.size();i++)
                delete instructions_si[i].first;
            for(int i=0;i<instructions_se.size();i++)
                delete instructions_se[i].first;
        }
        void insert_expresion(vector<pair<string,int>> t_expresion)
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
                cout << t_expresion[i].first;// << " " << t_expresion[i].second;
            cout << endl;
            for(int i = 0; i < instructions_si.size(); i++)
            {
                for(int j = 0; j < instructions_si[i].second; j++)
                    cout << "    ";
                cout << "instruccion " << i << " : ";
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
                    cout << "instruccion " << i << " : ";
                    instructions_se[i].first -> print(), (i != instructions_se.size() - 1 ? cout << endl : cout << "");
                }
            }
        }
        friend ostream& operator<<(ostream& output, si& s)
        {
            output << "si [";
            for(int i = 0; i<s.t_expresion.size(); i++)
                output << s.t_expresion[i].first;// << " " << s.t_expresion[i].second;
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
        vector<pair<Instruction*,int>> instructions_cf;
        void run()
        {
            return;
        }
        void insert(string name,int final_value,int inital_value = 0,int increment = 1)
        {
            this -> name = name;
            this -> inital_value = inital_value;
            this -> final_value = final_value;
            this -> increment = increment;
        }
        void insert_instruction_cf(vector<pair<Instruction*,int>> instructions_cf)
        {
            this -> instructions_cf = instructions_cf;
        }
        void print()
        {
            cout << "cf n = " << inital_value << ", n <= " << final_value << ", n+= " << increment;
            cout << endl;
            for(int i = 0; i<instructions_cf.size(); i++)
            {
                for(int j = 0; j < instructions_cf[i].second; j++)
                    cout << "    ";
                cout << "instruccion " << i << " : ";
                instructions_cf[i].first -> print(), (i != instructions_cf.size() - 1 ? cout << endl : cout << "");
            }
        }
};

class cw:public Instruction
{
    public:
        //Expresion expresion;
        vector<pair<string,int>> t_expresion;
        vector<pair<Instruction*,int>> instructions_cw;
        cw()
        {

        }
        ~cw()
        {
            for(int i=0;i<instructions_cw.size();i++)
                delete instructions_cw[i].first;
        }
        void insert_expresion(vector<pair<string,int>> t_expresion)
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
                cout << t_expresion[i].first;// << " " << t_expresion[i].second;
            cout << endl;
            for(int i = 0; i<instructions_cw.size(); i++)
            {
                for(int j = 0; j < instructions_cw[i].second; j++)
                    cout << "    ";
                cout << "instruccion " << i << " : ";
                instructions_cw[i].first -> print(), (i != instructions_cw.size() - 1 ? cout << endl : cout << "");
            }
        }
        friend ostream& operator<<(ostream& output, cw& w)
        {
            output << "cw ";
            for(int i = 0; i<w.t_expresion.size(); i++)
                output << w.t_expresion[i].first;// << " " << w.t_expresion[i].second;
            return output;
        }
};

class SyntacticAnalyzer
{
    public:
        LexicalAnalyzer a;
        vector<pair<string,int>> tokens;
        vector<pair<Instruction*,int>> instruction;
        int con = 0, g_indent = 0;
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
                if(indent == indentation)
                {
                    //cout << indent << " " << indentation << endl;
                    if((tokens[i].second == 10 && tokens[i+1].second == 0) || (tokens[i].first == "," && last.second == 10))///Declaration
                    {
                        Declaration* d = new Declaration;
                        if(tokens[i].second == 10) last = tokens[i];
                        if(tokens[i].second == 10) d -> insert(tokens[i].first,tokens[i+1].first);
                        else d -> insert(last.first,tokens[i+1].first);
                        instruction.push_back(make_pair(d,indentation));
                        i++, con++;
                    }

                    if(tokens[i].first == "=")///Assignment
                    {
                        vector<pair<string,int>> t_expresion;
                        string name;
                        Assignment* a = new Assignment;
                        if(tokens[i-1].second == 0) name = tokens[i-1].first;
                        else
                        {
                            cout << "Assignment Error" << endl;
                            exit(34404);
                        }
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1]),i++, con++;
                        a -> insert(name,t_expresion);
                        instruction.push_back(make_pair(a,indentation));
                    }

                    if((tokens[i].first == "fr" && tokens[i+1].second == 0) || (tokens[i].first == "," && last.first == "fr"))///Read
                    {
                        fr* r = new fr;
                        if(tokens[i].second == 20) last = tokens[i];
                        r -> insert(tokens[i+1].first);
                        i++, con++;
                        instruction.push_back(make_pair(r,indentation));
                    }

                    if(tokens[i].first == "fp" || (tokens[i].first == "," && last.first == "fp"))///Print
                    {
                        vector<pair<string,int>> t_expresion;
                        fp* p = new fp;
                        if(tokens[i].second == 20) last = tokens[i];
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1]),i++, con++;
                        p -> insert(t_expresion);
                        instruction.push_back(make_pair(p,indentation));
                    }








                    if(tokens[i].first == "si")///If
                    {
                        si* sif = new si;
                        vector<pair<string,int>> t_expresion;
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1]), i++, con++;
                        sif -> insert_expresion(t_expresion);

                        vector<pair<string,int>> tokens_i;
                        tokens_i.assign(tokens.begin()+(i+1),tokens.end());
                        con = 0;
                        //cout << endl << i+1 << " si i " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                        sif -> insert_instruction_si(instructions(tokens_i,indentation+1));
                        i += con;
                        con = 0;
                        //cout << endl << i << " si f " << tokens[i].first << " " << tokens[i+1].first  << " " << tokens[i+2].first  << endl;

                        if(tokens[i+1].first == "se") i++, con++;//if(tokens[i].second == 61 || tokens[i].second == 60) i++, con++;
                        if(tokens[i].first == "se")
                        {
                            tokens_i.assign(tokens.begin()+(i+1),tokens.end());
                            con = 0;
                            //cout << endl << i+1 << " se i " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                            sif -> insert_instruction_se(instructions(tokens_i,indentation+1));
                            i += con;
                            con = 0;
                            //cout << endl << i << " se f " << tokens[i].first << " " << tokens[i+1].first  << " " << tokens[i+2].first  << endl;
                        }

                        instruction.push_back(make_pair(sif,indentation));
                        if(indentation > 0 && indent == 0) return instruction;
                        //if(indentation > 0 && tokens[i].second != 60) return instruction;
                        //if(indentation > 0) return instruction;
                    }


                    //cout << tokens[i].first << " " << tokens[i+1].second  << " " <<  tokens[i+2].first  << " " << tokens[i+3].second  << " " <<  tokens[i+3].second  << endl;
                    if(tokens[i].first == "cf" && tokens[i+1].second == 00 && tokens[i+2].first == ":" && (tokens[i+3].second == 00 || tokens[i+3].second == 50 || tokens[i+3].second == 51))///For
                    {
                        if(tokens[i+3].second == 51) cout << "Value error" << endl, exit(34404);

                        int aux = 0, val;
                        int initial_value, final_value, increment;
                        string values[3] = {tokens[i+3].first,"0","1"};

                        Declaration* d = new Declaration;
                        d -> insert("di",tokens[i+1].first);
                        instruction.push_back(make_pair(d,indent));

                        if(tokens[i+4].first == ",")
                        {
                            while(tokens[i+4+aux+1].second != 61)
                            {
                                if(aux == 2) values[1] = tokens[i+4+aux].first;
                                if(aux == 4) values[2] = tokens[i+4+aux].first;
                                aux++;
                            }
                        }

                        for(int j = 0; j<3; j++)
                        {
                            //cout << values[j][0] << endl;
                            if(isdigit(values[j][0])) val = stoi(values[j]);
                            else val = 0;//Si es variable, obtener su valor de la tabla de símbolos
                            if(j == 0) initial_value = val;
                            if(j == 1) final_value = val;
                            if(j == 2) increment = val;
                        }

                        if(aux%2 == 1) cout << "Instruction error" << endl, exit(34404);

                        cf* f = new cf;
                        f -> insert(tokens[i+1].first,initial_value,final_value,increment);
                        i += 3 + aux;

                        vector<pair<string,int>> tokens_i;
                        tokens_i.assign(tokens.begin()+(i+1),tokens.end());
                        con = 0;
                        //cout << endl << i+1 << " cf i " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                        f -> insert_instruction_cf(instructions(tokens_i,indentation+1));
                        i += con;
                        //cout << endl << i << " cf f " << tokens[i].first << " " << tokens[i+1].first  << " " << tokens[i+2].first  << endl;
                        con = 0;

                        ///Si se intentan declarar dos variables con el mismo nombre = error
                        instruction.push_back(make_pair(f,indentation));
                        if(indentation > 0 && indent == 0) return instruction;
                        //if(indentation > 0 && tokens[i].second != 60) return instruction;
                        //if(indentation > 0) return instruction;
                    }
                    //else cout << tokens[i].first << " " << tokens[i+1].first  << " " <<  tokens[i+2].first  << " " << tokens[i+3].first  << " " <<  tokens[i+3].first  << endl, exit(34404);//cout << "Instruction error 2" << endl, exit(34404);



                    if(tokens[i].first == "cw")///While
                    {
                        cw* w = new cw;
                        vector<pair<string,int>> t_expresion;
                        while((tokens[i+1].second >= 31 && tokens[i+1].second <= 54) || tokens[i+1].second == 0)
                            t_expresion.push_back(tokens[i+1]),i++, con++;
                        w -> insert_expresion(t_expresion);

                        vector<pair<string,int>> tokens_i;
                        tokens_i.assign(tokens.begin()+(i+1),tokens.end());
                        con = 0;
                        //cout << endl << i+1 << " cw i " << tokens[i+1].first << " " << indent << " " << indentation << endl;
                        w -> insert_instruction_cw(instructions(tokens_i,indentation+1));
                        i += con;
                        //cout << endl << i << " cw f " << tokens[i].first << " " << tokens[i+1].first  << " " << tokens[i+2].first  << endl;
                        con = 0;

                        instruction.push_back(make_pair(w,indentation));
                        if(indentation > 0 && indent == 0) return instruction;
                        //if(indentation > 0 && tokens[i].second != 60) return instruction;
                        //if(indentation > 0) return instruction;
                    }







                }////////////////////////////Error con la separación en si, se, cw. Checar.
                else if(indent > indentation) cout << "Indentation error " << tokens[i].first << " " << tokens[i+1].first << endl;//, exit(34404);
                else if(indent < indentation) return instruction;
            }
            return instruction;
        }
};

int main()
{
    SyntacticAnalyzer s;
    cout << "Instrucciones:" << endl;
    for(int i = 0; i < s.tokens.size(); i++)
        cout << s.tokens[i].first << " " << s.tokens[i].second << endl;
    cout << endl << endl;
    for(int i = 0; i < s.instruction.size(); i++)
        cout << endl << "Instruccion " << i << endl,s.instruction[i].first -> print(), cout << endl;
        //s.instruction[i].first -> print(), cout << endl;
    return 0;
}

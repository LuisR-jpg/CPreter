#include <iostream>
#include <queue>
using namespace std;

class Instruction
{
    public:
        Instruction()
        {

        }
        virtual void run() = 0;
        virtual void print(string s) = 0;
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
        void print(string s)
        {
            cout << type << " " << name;
        }
};

class Assignment:public Instruction
{
    public:
        string name;
        queue<pair<string,int>> t_expresion;
        //Expresion expresion;
        Assignment()
        {
            this -> name = "";
        }
        void insert(string name,queue<pair<string,int>> t_expresion)
        {
            this -> name = name;
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void run()
        {
            return;
        }
        void print(string s)
        {
            cout << name << " = ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
        }
};

class fp: public Instruction
{
    public:
        queue<pair<string,int>> t_expresion;
        //Expresion expresion;
        fp()
        {

        }
        void insert(queue<pair<string,int>> t_expresion)
        {
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void run()
        {
            return;
        }
        void print(string s)
        {
            cout << "fp ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
        }
};

class fr: public Instruction
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
        void print(string s)
        {
            cout << "fr " << name;
        }
};

class si: public Instruction
{
    public:
        //Expresion expresion;
        queue<pair<string,int>> t_expresion;
        queue<Instruction*> instructions_si;
        queue<Instruction*> instructions_se;
        si()
        {

        }
        ~si()
        {
            while(!instructions_si.empty())
                delete instructions_si.front(),instructions_si.pop();
            while(!instructions_si.empty())
                delete instructions_se.front(),instructions_se.pop();
        }
        void insert_expresion(queue<pair<string,int>> t_expresion)
        {
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void insert_instruction_si(queue<Instruction*> instructions_si)
        {
            this -> instructions_si = instructions_si;
        }
        void insert_instruction_se(queue<Instruction*> instructions_se)
        {
            this -> instructions_se = instructions_se;
        }
        void run()
        {
            return;
        }
        void print(string s)
        {
            int nl = 0;
            cout << "si ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
            cout << endl;
            queue<Instruction*> aux2 = instructions_si;
            while(!aux2.empty())
                //cout << s << "Instruccion si: ", aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_si.size() ? cout << endl : cout << "");
                cout << s, aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_si.size() ? cout << endl : cout << "");
            if(!instructions_se.empty())
            {
                nl = 0;
                aux2 = instructions_se;
                cout << endl << "se" << endl;
                while(!aux2.empty())
                    //cout << s << "Instruccion se: ", aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_si.size() ? cout << endl : cout << "");
                    cout << s, aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_se.size() ? cout << endl : cout << "");
            }
        }
};

class cf:public Instruction
{
    public:
        string name;
        int inital_value;
        int final_value;
        int increment;
        queue<Instruction*> instructions_cf;
        cf ()
        {

        }
        ~cf()
        {
            while(!instructions_cf.empty())
                delete instructions_cf.front(),instructions_cf.pop();
        }
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
        void insert_instruction_cf(queue<Instruction*> instructions_cf)
        {
            this -> instructions_cf = instructions_cf;
        }
        void print(string s)
        {
            int nl = 0;
            cout << "cf n = " << inital_value << ", n <= " << final_value << ", n+= " << increment;
            cout << endl;
            queue<Instruction*> aux2 = instructions_cf;
            while(!aux2.empty())
                //cout << s << "Instruccion cf: ", aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_cf.size() ? cout << endl : cout << "");
                cout << s, aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_cf.size() ? cout << endl : cout << "");
        }
};

class cw: public Instruction
{
    public:
        //Expresion expresion;
        queue<pair<string,int>> t_expresion;
        queue<Instruction*> instructions_cw;
        cw()
        {

        }
        ~cw()
        {
            while(!instructions_cw.empty())
                delete instructions_cw.front(),instructions_cw.pop();
        }
        void insert_expresion(queue<pair<string,int>> t_expresion)
        {
            this -> t_expresion = t_expresion;
            //this -> expresion = Expresion(t_expresion);
        }
        void insert_instruction_cw(queue<Instruction*> instructions_cw)
        {
            this -> instructions_cw = instructions_cw;
        }
        void run()
        {
            return;
        }
        void print(string s)
        {
            int nl = 0;
            cout << "cw ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
            cout << endl;
            queue<Instruction*> aux2 = instructions_cw;
            while(!aux2.empty())
                //cout << s << "Instruccion cw: ", aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_cw.size() ? cout << endl : cout << "");
                cout << s, aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_cw.size() ? cout << endl : cout << "");
        }
};
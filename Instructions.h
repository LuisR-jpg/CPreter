#include <iostream>
#include <queue>
#include "ExpressionEvaluator.h"
using namespace std;

class Instruction
{
    public:
        Instruction(){}
        virtual void run() = 0;
        virtual void print(string s) = 0;
        virtual string translate(string s) = 0;
};

class Declaration: public Instruction
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
        void print(string s)
        {
            cout << type << " " << name;
        }
        string translate(string s){
            string r;
            if(type == "di") r = "int";
            if(type == "db") r = "bool";
            if(type == "dd") r = "double";
            if(type == "dc") r = "char";
            if(type == "ds") r = "string";
            r += " " + name + ";\n";
            return r;
        }
        void run();
};

class Assignment: public Instruction
{
    public:
        string name;
        queue<pair<string,int>> t_expresion;
        Evaluator evaluator;
        Assignment()
        {
            this -> name = "";
        }
        void insert(string name,queue<pair<string,int>> t_expresion)
        {
            this -> name = name;
            this -> t_expresion = t_expresion;
        }
        void print(string s)
        {
            cout << name << " = ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
        }
        string translate(string s){
            string r;
            r = name + " = ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                r += aux.front().first, aux.pop();
            r += ";\n";
            return r;
        }
        void run();
};

class fp: public Instruction
{
    public:
        queue<pair<string,int>> t_expresion;
        Evaluator evaluator;
        fp(){}
        void insert(queue<pair<string,int>> t_expresion)
        {
            this -> t_expresion = t_expresion;
        }
        void print(string s)
        {
            cout << "fp ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
        }
        string translate(string s){
            string r;
            r = "cout << ";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
            {
                if(aux.front().second == 53) r += "\"" + aux.front().first + "\"";
                else r += aux.front().first;
                aux.pop();
            }
            r += " << endl;\n";
            return r;
        }
        void run();
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
        void print(string s)
        {
            cout << "fr " << name;
        }
        string translate(string s){
            string r;
            r = "cin >> " + name + ";\n";
            return r;
        }
        void run();
};

class si: public Instruction
{
    public:
        Evaluator evaluator;
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
        }
        void insert_instruction_si(queue<Instruction*> instructions_si)
        {
            this -> instructions_si = instructions_si;
        }
        void insert_instruction_se(queue<Instruction*> instructions_se)
        {
            this -> instructions_se = instructions_se;
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
        string translate(string s){
            string r;
            int nl = 0;
            r = "if(";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                r += aux.front().first, aux.pop();
            r += ")\n{\n";
            queue<Instruction*> aux2 = instructions_si;
            while(!aux2.empty())
                //cout << s << "Instruccion si: ", aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_si.size() ? cout << endl : cout << "");
                r += s, r += aux2.front() -> translate(s+"    "), aux2.pop(), r += (++nl != instructions_si.size() ? "\n" : "");
            r += "\n}";
            if(!instructions_se.empty())
            {
                nl = 0;
                aux2 = instructions_se;
                r += "\nelse\n{\n";
                while(!aux2.empty())
                    //cout << s << "Instruccion se: ", aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_si.size() ? cout << endl : cout << "");
                    r += s, r += aux2.front() -> translate(s+"    "), aux2.pop(), r += (++nl != instructions_si.size() ? "\n" : "");
                r += "\n}";
            }
            r += "\n";
            return r;
        }
        void run();
};

class cf: public Instruction
{
    public:
        string name;
        queue<pair<string,int>> inital_value;
        queue<pair<string,int>> final_value;
        queue<pair<string,int>> increment;
        queue<Instruction*> instructions_cf;
        Evaluator evaluator;
        cf ()
        {

        }
        ~cf()
        {
            while(!instructions_cf.empty())
                delete instructions_cf.front(),instructions_cf.pop();
        }
        void insert(string name, queue<pair<string,int>> final_value)
        {
            this -> name = name;
            this -> inital_value.push(make_pair("0",50));
            this -> final_value = final_value;
            this -> increment.push(make_pair("1",50));
        }
        void insert(string name, queue<pair<string,int>> inital_value, queue<pair<string,int>> final_value)
        {
            this -> name = name;
            this -> inital_value = inital_value;
            this -> final_value = final_value;
            this -> increment.push(make_pair("1",50));
        }
        void insert(string name, queue<pair<string,int>> inital_value, queue<pair<string,int>> final_value, queue<pair<string,int>> increment)
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
            cout << "cf " << name << " = ";
            queue<pair<string,int>> aux = inital_value;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
            cout << ", " << name << " <= ";
            aux = final_value;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
            cout << ", " << name << " += ";
            aux = increment;
            while(!aux.empty())
                cout << aux.front().first, aux.pop();
            cout << endl;
            queue<Instruction*> aux2 = instructions_cf;
            while(!aux2.empty())
                //cout << s << "Instruccion cf: ", aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_cf.size() ? cout << endl : cout << "");
                cout << s, aux2.front() -> print(s+"    "), aux2.pop(), (++nl != instructions_cf.size() ? cout << endl : cout << "");
        }
        string translate(string s){
            string r;
            int nl = 0;
            r += "for(" + name + " = ";
            queue<pair<string,int>> aux = inital_value;
            while(!aux.empty())
                r += aux.front().first, aux.pop();
            r += "; " + name + " <= ";
            aux = final_value;
            while(!aux.empty())
                r += aux.front().first, aux.pop();
            r += "; " + name + " += ";
            aux = increment;
            while(!aux.empty())
                r += aux.front().first, aux.pop();
            r += ")\n{\n";
            queue<Instruction*> aux2 = instructions_cf;
            while(!aux2.empty())
                r += s, r += aux2.front() -> translate(s+"    "), aux2.pop(), r += (++nl != instructions_cf.size() ? "\n" : "");
            r += "\n}\n";
            return r;
        }
        void run();
};

class cw: public Instruction
{
    public:
        Evaluator evaluator;
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
        string translate(string s){
            string r;
            int nl = 0;
            r += "while(";
            queue<pair<string,int>> aux = t_expresion;
            while(!aux.empty())
                r += aux.front().first, aux.pop();
            r += ")\n{\n";
            queue<Instruction*> aux2 = instructions_cw;
            while(!aux2.empty())
                r += s, r += aux2.front() -> translate(s+"    "), aux2.pop(), r += (++nl != instructions_cw.size() ? "\n" : "");
            r += "\n}";
            return r;
        }
        void run();
};

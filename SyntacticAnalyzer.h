#include "LexicalAnalyzer.h"
#include "Instructions.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
extern bool debug;
class SyntacticAnalyzer
{
    public:
        queue<pair<string,int>> tokens;
        queue<Instruction*> instruction;
        vector<pair<string,int>> token;
        SyntacticAnalyzer(string file)
        {
            LexicalAnalyzer a(file);
            this -> token = a.getToken();
            if(debug)
            {
                ///DEBUG
                cout << "\t----------LEXICAL----------" << endl;
                for(int i = 0; i < token.size(); i++){
                    auto b = token[i];
                    cout << b.first << " " << b.second << endl;
                }
                cout << "\t----------LEXICAL----------" << endl << endl;
                ///DEBUG
            }
            for(int i = 0; i < token.size(); i++)
                tokens.push(token[i]);
            this -> instruction = instructions(tokens);
        }
        ~SyntacticAnalyzer()
        {
            while(!instruction.empty())
                delete instruction.front(),instruction.pop();
        }
        queue<Instruction*> instructions(queue<pair<string,int>> tokens)
        {
            queue<Instruction*> instruction;
            pair<string, int> last_type;
            pair<string, int> front_t;
            int indent = 0;
            while(!tokens.empty())
            {
                front_t = tokens.front();
                tokens.pop();
                if(tokens.front().second == 60){
                    cout << "\tSYNTACTIC ERROR: Indentation error" << endl;
                    exit(0);
                }
                if(front_t.second == 61) continue;
                if((front_t.second == 10 && tokens.front().second == 0) || (front_t.first == "," && last_type.second == 10))///Declaration ------ Listo
                {
                    Declaration* d = new Declaration;
                    if(front_t.second == 10) last_type = front_t, d -> insert(front_t.first,tokens.front().first);
                    else d -> insert(last_type.first,tokens.front().first);
                    front_t = tokens.front();
                    tokens.pop();
                    instruction.push(d);
                }
                if((tokens.front().first == "=" && tokens.front().second == 30) || (front_t.first == "=" && front_t.second == 30))///Assignment ------ Listo
                {
                    if(front_t.first == "="){
                        cout << "\tSYNTACTIC ERROR: Assignment Error";
                        exit(0);
                    }
                    queue<pair<string,int>> t_expresion;
                    string name;
                    Assignment* a = new Assignment;
                    if(front_t.second == 0) name = front_t.first;
                    else{
                        cout << "\tSYNTACTIC ERROR: Assignment Error";
                        exit(0);
                    }
                    front_t = tokens.front();
                    tokens.pop();
                    while((tokens.front().second >= 31 && tokens.front().second <= 54) || tokens.front().second == 0)
                        t_expresion.push(tokens.front()), front_t = tokens.front(), tokens.pop();
                    a -> insert(name,t_expresion);
                    instruction.push(a);
                    if(tokens.empty()) return instruction;
                }
                if(((front_t.first == "fr" && front_t.second == 20) && tokens.front().second == 0) || (front_t.first == "," && last_type.first == "fr"))///Read ------- Listo
                {
                    fr* r = new fr;
                    if(front_t.second == 20) last_type = front_t;
                    r -> insert(tokens.front().first);
                    front_t = tokens.front();
                    tokens.pop();
                    instruction.push(r);
                }
                if((front_t.first == "fp" && front_t.second == 20) || (front_t.first == "," && last_type.first == "fp"))///Print ------ Listo
                {
                    queue<pair<string,int>> t_expresion;
                    fp* p = new fp;
                    if(front_t.second == 20) last_type = front_t;
                    while((tokens.front().second >= 31 && tokens.front().second <= 54) || tokens.front().second == 0)
                        t_expresion.push(tokens.front()), front_t = tokens.front(), tokens.pop();
                    p -> insert(t_expresion);
                    instruction.push(p);
                    if(tokens.empty()) return instruction;
                }
                if(front_t.first == "si" && front_t.second == 20)///If ------ Listo?
                {
                    si* sif = new si;
                    queue<pair<string,int>> t_expresion;
                    while((tokens.front().second >= 31 && tokens.front().second <= 54) || tokens.front().second == 0)
                        t_expresion.push(tokens.front()), front_t = tokens.front(), tokens.pop();
                    sif -> insert_expresion(t_expresion);
                    front_t = tokens.front();
                    tokens.pop();
                    queue<pair<string,int>> tokens_i;
                    while(!tokens.empty() && (tokens.front().second == 60 || tokens.front().second == 61))
                    {
                        tokens.pop();
                        while(tokens.front().second != 61)
                        {
                            tokens_i.push(tokens.front());
                            tokens.pop();
                        }
                        if(tokens.front().second == 61) tokens_i.push(tokens.front()), tokens.pop();
                    }
                    front_t = tokens.front();
                    sif -> insert_instruction_si(instructions(tokens_i));
                    if(front_t.first == "se" && front_t.second == 20)
                    {
                        while(!tokens_i.empty())
                            tokens_i.pop();
                        tokens.pop();
                        while(!tokens.empty() && (tokens.front().second == 60 || tokens.front().second == 61))
                        {
                            tokens.pop();
                            while(tokens.front().second != 61)
                            {
                                tokens_i.push(tokens.front());
                                tokens.pop();
                            }
                            if(tokens.front().second == 61) tokens_i.push(tokens.front()), tokens.pop();
                        }
                        front_t = tokens.front();
                        sif -> insert_instruction_se(instructions(tokens_i));
                    }
                    instruction.push(sif);
                    if(tokens.empty()) return instruction;
                }
                if(front_t.first == "cf" && front_t.second == 20)///For ------ Listo?
                {
                    string name;
                    int aux;
                    queue<pair<string,int>> initial_value, final_value, increment;
                    for(int i = 0; i < 7; i++)
                    {
                        if((i == 3 || i == 5) && front_t.second == 61) break;
                        front_t = tokens.front();
                        tokens.pop();
                        if(i == 0 && front_t.second == 00)
                        {
                            name = front_t.first;
                            Declaration* d = new Declaration;
                            d -> insert("di",front_t.first);
                            instruction.push(d);
                            continue;
                        }
                        if(i == 1 && front_t.first == ":") continue;
                        if(i == 2 && (front_t.second == 0 || front_t.second == 50))
                        {
                            aux = 1;
                            while((front_t.second >= 31 && front_t.second <= 54) || front_t.second == 0)
                            {
                                initial_value.push(front_t);
                                if(tokens.front().first == "," || tokens.front().first == "\n") break;
                                front_t = tokens.front();
                                tokens.pop();
                            }
                            continue;
                        }
                        else if(i == 2 && !(front_t.second == 0 || front_t.second == 50))
                        {
                            cout << "\tSYNTACTIC ERROR: Value Error";
                            exit(0);
                        }
                        if(i == 3 && front_t.first == ",") continue;
                        else if(i == 3 && front_t.second == 61) break;
                        if(i == 4 && (front_t.second == 0 || front_t.second == 50))
                        {
                            aux = 2;
                            while((front_t.second >= 31 && front_t.second <= 54) || front_t.second == 0)
                            {
                                final_value.push(front_t);
                                if(tokens.front().first == "," || tokens.front().first == "\n") break;
                                front_t = tokens.front();
                                tokens.pop();
                            }
                            continue;
                        }
                        else if(i == 4 && !(front_t.second == 0 || front_t.second == 50))
                        {
                            cout << "\tSYNTACTIC ERROR: Value Error";
                            exit(0);
                        }
                        if(i == 5 && front_t.first == ",") continue;
                        else if(i == 5 && front_t.second == 61) break;
                        if(i == 6 && (front_t.second == 0 || front_t.second == 50))
                        {
                            aux = 3;

                            while((front_t.second >= 31 && front_t.second <= 54) || front_t.second == 0)
                            {
                                increment.push(front_t);
                                if(tokens.front().first == "," || tokens.front().first == "\n") break;
                                front_t = tokens.front();
                                tokens.pop();
                            }
                            continue;
                        }
                        else if(i == 6 && !(front_t.second == 0 || front_t.second == 50))
                        {
                            cout << "\tSYNTACTIC ERROR: Value Error";
                            exit(0);
                        }
                        else{
                            cout << "\tSYNTACTIC ERROR: Syntax Error";
                            exit(0);
                        }
                    }
                    cf* f = new cf;
                    if(aux == 1) f -> insert(name,initial_value);
                    if(aux == 2) f -> insert(name,initial_value,final_value);
                    if(aux == 3) f -> insert(name,initial_value,final_value,increment);
                    queue<pair<string,int>> tokens_i;
                    while(!tokens.empty() && (tokens.front().second == 60 || tokens.front().second == 61))
                    {
                        tokens.pop();
                        while(tokens.front().second != 61)
                        {
                            tokens_i.push(tokens.front());
                            tokens.pop();
                        }
                        if(tokens.front().second == 61) tokens_i.push(tokens.front()), tokens.pop();
                    }
                    front_t = tokens.front();
                    f -> insert_instruction_cf(instructions(tokens_i));
                    instruction.push(f);
                    if(tokens.empty()) return instruction;
                }
                if(front_t.first == "cw" && front_t.second == 20)///While ------ Listo?
                {
                    cw* w = new cw;
                    queue<pair<string,int>> t_expresion;
                    while((tokens.front().second >= 31 && tokens.front().second <= 54) || tokens.front().second == 0)
                        t_expresion.push(tokens.front()), front_t = tokens.front(), tokens.pop();
                    w -> insert_expresion(t_expresion);
                    front_t = tokens.front();
                    tokens.pop();
                    queue<pair<string,int>> tokens_i;
                    while(!tokens.empty() && (tokens.front().second == 60 || tokens.front().second == 61))
                    {
                        tokens.pop();
                        while(tokens.front().second != 61)
                        {
                            tokens_i.push(tokens.front());
                            tokens.pop();
                        }
                        if(tokens.front().second == 61) tokens_i.push(tokens.front()), tokens.pop();
                    }
                    front_t = tokens.front();
                    w -> insert_instruction_cw(instructions(tokens_i));
                    instruction.push(w);
                    if(tokens.empty()) return instruction;
                }
            }
            return instruction;
        }
};
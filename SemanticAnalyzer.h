#include "SyntacticAnalyzer.h"
#include <map>
#include <string>
map<string, pair<string, void*>> SymbolTable;
extern bool debug;
queue<pair<string, int>> replace(queue<pair<string, int>> q)
{
    int n = q.size();
    /*
    ///DEBUG
    cout << "\t----------REPLACE----------" << endl;
    for(int i = 0; i < q.size(); i++)
    {
        auto m = q.front();
        q.pop();
        cout << m.first << "\t" << m.second << endl;
        q.push(m);
    }
    ///DEBUG
    */
    for(int i = 0; i < n; i++)
    {
        auto tok = q.front();
        if(!tok.second)
        {
            if(SymbolTable.find(tok.first) == SymbolTable.end())
            {
                cout << "\tERROR. Trying to evaluate a non-declarated variable.";
                exit(0);
            }
            auto var = SymbolTable[tok.first];
            if(var.first == "di") tok = make_pair(to_string(*((int*)var.second)), 50);
            if(var.first == "dd") tok = make_pair(to_string(*((double*)var.second)), 51);
            if(var.first == "db") tok = make_pair(to_string((int)*((bool*)var.second)), 52);
            if(var.first == "dc") tok = make_pair(to_string((int)(*((char*)var.second))), 54);
        }
        q.push(tok);
        q.pop();
    }
    /*
    ///DEBUG
    cout << endl;
    for(int i = 0; i < q.size(); i++)
    {
        auto m = q.front();
        q.pop();
        cout << m.first << "\t" << m.second << endl;
        q.push(m);
    }
    cout << "\t----------REPLACE----------" << endl;
    ///DEBUG
    */
    return q;
}
void Declaration::run()
{
    if(SymbolTable.find(name) != SymbolTable.end())
    {
        cout << "\tSEMANTIC ERROR: Variable name already used." << endl;
        exit(0);
    }
    void *pointer;
    SymbolTable.insert(make_pair(name, make_pair(type, pointer)));
}
void Assignment::run()
{
    if(SymbolTable.find(name) == SymbolTable.end())
    {
        cout << "\tERROR. Trying to assing to non-declarated variable.";
        exit(0);
    }
    auto a = t_expresion.front();
    auto var = SymbolTable[name];
    if(debug) cout << "\t\t\t\t\t" << name << ": ";
    if(var.first == "ds"){
        var.second = new string(a.first);
        if(debug) cout << *((string*)var.second);
    }
    else if(var.first == "dc"){
        var.second = new char(a.first[0]);
        if(debug) cout << *((char*)var.second);
    }
    else
    {
        double c = evaluator.evaluate(replace(t_expresion));
        if(var.first == "db"){
            var.second = new bool(c);
            if(debug) cout << *((bool*)var.second);
        }
        if(var.first == "di"){
            var.second = new int(c);
            if(debug) cout << *((int*)var.second);
        }
        if(var.first == "dd"){
            var.second = new double(c);
            if(debug) cout << *((double*)var.second);
        }
    }
    SymbolTable[name] = var;
    if(debug) cout << endl;
}
//////////////////MEJORAAAAAAAAAAAAAAAAAAR
void fp::run()
{
    if(debug) cout << "\t\t\t\t\t...";
    auto a = t_expresion.front();
    if(t_expresion.size() == 1)
    {
        if(!a.second)
        {
            auto var = SymbolTable[a.first];
            if(var.first == "ds") cout << *((string*)var.second);
            else if(var.first == "dc") cout << *((char*)var.second);
            else cout << evaluator.evaluate(replace(t_expresion));
        }
        else if(a.second == 53 || a.second == 54) cout << a.first;
        else cout << evaluator.evaluate(replace(t_expresion));
    }
    else cout << evaluator.evaluate(replace(t_expresion));
    cout << endl;
}
void fr::run() 
{
    if(SymbolTable.find(name) == SymbolTable.end())
    {
        cout << "\tSEMANTIC ERROR: Trying to read in non-declarated variable.";
        exit(0);
    }
    Assignment a;
    queue<pair<string, int>> q;
    string type = SymbolTable[name].first, s;
    int t;
    /*
    double d, t;
    if(type == "ds" || type == "dc") 
    {
        cin >> s;
        t = 53 + (type == "dc");
    }
    else
    {
        cin >> d;
        t = (type == "di"? 50: (type == "dd"? 51: 52)), s = to_string(d);
    }
    */
    cin >> s;
    if(type == "ds") t = 53;
    if(type == "dc")
    {
        if(s.size() > 1)
        {
            cout << "\tSEMANTIC ERROR: Error while reading. DC was expected";
            exit(0);
        }
        t = 54;
    }
    if(type == "db")
    {
        if(s == "true") s = "1";
        if(s == "false") s = "0";
        if(s == "1" || s == "0") t = 52;
        else
        {
            cout << "\tSEMANTIC ERROR: Error while reading. DB was expected";
            exit(0);
        }
    }
    if(type == "di")
    {
        try
        {
            int i = stoi(s);
            t = 50;
        }
        catch(...)
        {
            cout << "\tSEMANTIC ERROR: Error while reading. DI was expected";
            exit(0);
        }
    }
    if(type == "dd")
    {
        try
        {
            double d = stod(s);
            t = 51;
        }
        catch(...)
        {
            cout << "\tSEMANTIC ERROR: Error while reading. DD was expected";
            exit(0);
        }
    }
    q.push(make_pair(s, t));
    a.insert(name, q);
    a.run();    
}
void si::run()
{
    auto condition = evaluator.evaluate(replace(t_expresion));
    auto toRun = (condition? instructions_si: instructions_se);
    while(toRun.size())
    {
        auto inst = toRun.front();
        inst -> run();
        toRun.pop();
    }
}
void cf::run()
{
    double end = evaluator.evaluate(replace(final_value));
    double inc = evaluator.evaluate(replace(increment));
    bool erase = false;
    Assignment a;
    a.insert(name, inital_value);
    a.run();
    int *var = (int*)SymbolTable[name].second, n = instructions_cf.size();
    for(; *var <= end; *var += inc)
    {
        for(int i = 0; i < n; i++)
        {
            auto inst = instructions_cf.front();
            inst -> run();
            instructions_cf.push(inst);
            instructions_cf.pop();
        }
    }
    SymbolTable.erase(name);
}
void cw::run()
{
    while(evaluator.evaluate(replace(t_expresion)))
    {
        for(int i = 0; i < instructions_cw.size(); i++)
        {
            auto inst = instructions_cw.front();
            inst -> run();
            instructions_cw.push(inst);
            instructions_cw.pop();
        }
    }
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <iomanip>

using namespace std;

bool isFunction(string s){
    bool beganWithAlph = !isdigit(s[0]);
    bool hasPranth = s.find('(') != string::npos;
    return beganWithAlph && hasPranth;
}


int main(int argc, char *argv[]) {
    //ifstream file("main.dpp");
    string line;
    unordered_map<string, double> variables;


    unordered_map<string, function<double(double, double)>> operations = {
        {"+", [](double a, double b) { return a + b; }},
        {"-", [](double a, double b) { return a - b; }},
        {"*", [](double a, double b) { return a * b; }},
        {"/", [](double a, double b) { return a / b; }},
        {"^", [](double a, double b) { return pow(a, b); }}
    };

    unordered_map<string, function<double(double)>> functions = {
        {"sin", [](double a) { return sin(a); }},
        {"cos", [](double a) { return cos(a); }},
        {"cot", [](double a) { return 1/tan(a); }},
        {"tan", [](double a) { return tan(a); }},
        {"print", [](double a) { cout << setprecision(3) << a << endl; return 0;}} //ADD setprecision(3)
    };

    while (getline(cin, line)) { //ADD CIN
        istringstream iss(line);
        string var, equal, lhs, op, rhs;
        iss >> var;
        if(iss >> equal >> lhs){

            if(isFunction(lhs)){

                int i = lhs.find("(");
                int j = lhs.find(")");

                string pram_str = lhs.substr(i+1,j-i-1);
                string name = lhs.substr(0,i);

                double pram;
                if(isdigit(pram_str[0])){
                    pram = stod(pram_str);
                }else{
                    pram = variables[pram_str];
                }
                variables[var] = functions[name](pram);

            }else if(isdigit(lhs[0])){
                variables[var] = stod(lhs);
            }else{

                variables[var] = variables[lhs];
            }
            if (iss >> op >> rhs) {

                if(isFunction(rhs)){

                    int i = rhs.find("(");
                    int j = rhs.find(")");

                    string pram_str = rhs.substr(i+1,j-i-1);
                    string name = rhs.substr(0,i);

                    double pram;
                    if(isdigit(pram_str[0])){
                        pram = stod(pram_str);
                    }else{
                        pram = variables[pram_str];
                    }
                    variables[var] = operations[op](variables[var],functions[name](pram));

                }else if(isdigit(rhs[0])){
                    variables[var] = operations[op](variables[var],stod(rhs));
                }else{

                    variables[var] = operations[op](variables[var],variables[rhs]);
                }

            }
        }else{
            int i = var.find("(");
            int j = var.find(")");

            string pram_str = var.substr(i+1,j-i-1);
            string name = var.substr(0,i);
            double pram;
            if(isdigit(pram_str[0])){
                pram = stod(pram_str);
            }else{
                pram = variables[pram_str];
            }
            functions[name](pram);
        }

    }


    return 0;
}
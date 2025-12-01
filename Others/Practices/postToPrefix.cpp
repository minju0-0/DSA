#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(){
    stack<string> strstack;
    string s1, s2, op, res = "";

    while(op != "x"){
        cout << "Op: ";
        cin >> op;

        if(op == "+" || op == "-" || op == "/" || op == "*"){
            s1 = strstack.top(); strstack.pop();
            s2 = strstack.top(); strstack.pop();
            res = op + " " + s2 + " " + s1;
            strstack.push(res);
        }else if(op == "x"){
            cout << "Prefix: " << res << endl;
        }else{
            strstack.push(op);
        }
    }


}
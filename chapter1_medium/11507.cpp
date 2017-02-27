#include <iostream>

using namespace std;

void fold(string f, string &c)
{
    if (c == "+x") {
        if (f != "No")
            c = f;
    } else if (c == "-x") {
        if (f == "+x") 
            c = "-x";
        else if (f == "-x")
            c = "+x";
        else if (f == "+y")
            c = "-y";
        else if (f == "-y")
            c = "+y";
        else if (f == "+z")
            c = "+z";
        else if (f == "-z")
            c = "-z";
    } else if (c == "+y") {
        if (f == "+x") 
            c = "+y";
        else if (f == "-x") 
            c = "-y";
        else if (f == "+y")
            c = "+x";
        else if (f == "-y")
            c = "-x";
        else if (f == "+z")
            c = "+z";
        else if (f == "-z")
            c = "-z";
    } else if (c == "-y") {
        if (f == "+x")
            c = "-y";
        else if (f == "-x")
            c = "+y";
        else if (f == "+y") 
            c = "-x";
        else if (f == "-y")
            c = "+x";
        else if (f == "+z")
            c = "+z";
        else if (f == "-z")
            c = "-z";
    } else if (c == "+z") {
        if (f == "+x")
            c = "+z";
        else if (f == "-x")
            c = "-z";
        else if (f == "+y")
            c = "+y";
        else if (f == "-y")
            c = "-y";
        else if (f == "+z")
            c = "-x";
        else if (f == "-z")
            c = "+x";
    } else if (c == "-z") {
        if (f == "+x")
            c = "-z";
        else if (f == "-x")
            c = "+z";
        else if (f == "+y")
            c = "+y";
        else if (f == "-y")
            c = "-y";
        else if (f == "+z")
            c = "+x";
        else if (f == "-z")
            c = "-x";
    }
    cout << c << endl;
}

int main()
{
    string c, f;
    int n;
    while (cin >> n && n) {
        c = "+x";
        while (--n) {
            cin >> f;
            fold(f, c);
        }
        //cout << c << endl;
        cout << endl << endl;
    }
}

#include <iostream>

using namespace std;

void fold(string f, string &c)
{
    if (f == "No") return;

    if (c == "+x") {
        c = f;
    } else if (c == "-x") {
        if (f == "+y")
            c = "-y";
        else if (f == "-y")
            c = "+y";
        else if (f == "+z")
            c = "-z";
        else if (f == "-z")
            c = "+z";
    } else if (c == "+y") {
        if (f == "+y")
            c = "-x";
        else if (f == "-y")
            c = "+x";
        else if (f == "+z")
            c = "+y";
        else if (f == "-z")
            c = "+y";
    } else if (c == "-y") {
        if (f == "+y")
            c = "+x";
        else if (f == "-y")
            c = "-x";
        else if (f == "+z")
            c = "-y";
        else if (f == "-z")
            c = "-y";
    } else if (c == "+z") {
        if (f == "+y")
            c = "+z";
        else if (f == "-y")
            c = "+z";
        else if (f == "+z")
            c = "-x";
        else if (f == "-z")
            c = "+x";
    } else if (c == "-z") {
        if (f == "+y")
            c = "-z";
        else if (f == "-y")
            c = "-z";
        else if (f == "+z")
            c = "+x";
        else if (f == "-z")
            c = "-x";
    }
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
        cout << c << endl;
    }
}

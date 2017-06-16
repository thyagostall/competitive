#include <cstdio>
#include <cstring>
#include <string>
#include <set>

using namespace std;

string format_set(set<string> s)
{
    if (s.size() == 1) {
        return *s.begin();
    }

    string result = "";
    for (auto x : s) {
        if (result.size()) {
            result += ", ";
        }
        result += x;
    }
    return "{" + result + "}";
}

set<string> abo_to_allele(const string abo)
{
    set<string> result;
    if (abo == "A") {
        result.insert("AA");
        result.insert("AO");
    } else if (abo == "B") {
        result.insert("BB");
        result.insert("BO");
    } else if (abo == "O") {
        result.insert("OO");
    } else {
        result.insert(abo);
    }
    return result;
}

set<string> abo_to_rh_factor(const string abo)
{
    set<string> result;
    if (abo == "+") {
        result.insert("++");
        result.insert("+-");
        result.insert("-+");
    } else {
        result.insert("--");
    }
    return result;
}

set<string> operator*(set<string> a, set<string> b)
{
    set<string> result;
    for (auto x : a) {
        for (auto y : b) {
            result.insert(x + y);
        }
    }
    return result;
}

set<string> abo_to_blood_type(const string abo)
{
    int len = abo.size();
    string allele = abo.substr(0, len - 1);
    string rh_factor { abo[len - 1] };
    
    set<string> alleles = abo_to_allele(allele);
    set<string> rh_factors = abo_to_rh_factor(rh_factor);

    return alleles * rh_factors;
}

set<string> possibilities_from_parents(string father, string mother)
{
    set<string> result;
    result.insert(string { father[0], mother[0], father[2], mother[2] });
    result.insert(string { father[0], mother[1], father[2], mother[3] });
    result.insert(string { father[1], mother[0], father[3], mother[2] });
    result.insert(string { father[1], mother[1], father[3], mother[3] });
    return result;
}

set<string> compute_possibilities_from_parents(set<string> father, set<string> mother)
{
    set<string> result;
    for (auto x : father) {
        for (auto y : mother) {
            set<string> p = possibilities_from_parents(x, y);
            result.insert(p.begin(), p.end());
        }
    }
    return result;
}

set<string> compute_from_parents(string father, string mother)
{
    set<string> father_bt = abo_to_blood_type(father);
    set<string> mother_bt = abo_to_blood_type(mother);

    return compute_possibilities_from_parents(father_bt, mother_bt);
}

set<string> get_all_possibilities()
{
    set<string> result;
    set<string> t;

    t = abo_to_blood_type("A+");
    result.insert(t.begin(), t.end());
    t = abo_to_blood_type("A-");
    result.insert(t.begin(), t.end());
    
    t = abo_to_blood_type("B+");
    result.insert(t.begin(), t.end());
    t = abo_to_blood_type("B-");
    result.insert(t.begin(), t.end());
    
    t = abo_to_blood_type("AB+");
    result.insert(t.begin(), t.end());
    t = abo_to_blood_type("AB-");
    result.insert(t.begin(), t.end());
    
    t = abo_to_blood_type("O+");
    result.insert(t.begin(), t.end());
    t = abo_to_blood_type("O-");
    result.insert(t.begin(), t.end());

    return result;
}

int main()
{
    char f[4], m[4], c[4];
    while (scanf("%s %s %s", f, m, c) != EOF && f[0] != 'E') {
        printf("%s %s %s\n", f, m, c);
        if (strcmp(c, "?") == 0) {
            string father { f };
            string mother { m };

            printf("%s\n", format_set(compute_from_parents(father, mother)).c_str());
        }
    }
}

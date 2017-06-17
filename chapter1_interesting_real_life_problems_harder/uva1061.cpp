#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

string format_set(set<string> s)
{
    if (s.size() == 0) {
        return "IMPOSSIBLE";
    } else if (s.size() == 1) {
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

string allele_and_rh_factor_to_abo(const string allele_rh_factor)
{
    string allele    = allele_rh_factor.substr(0, 2);
    string rh_factor = allele_rh_factor.substr(2, 2);

    if (allele == "AA" || allele == "AO" || allele == "OA") {
        allele = "A";
    } else if (allele == "BB" || allele == "BO" || allele == "OB") {
        allele = "B";
    } else if (allele == "OO") {
        allele = "O";
    } else {
        allele = "AB";
    }

    if (rh_factor == "--") {
        rh_factor = "-";
    } else {
        rh_factor = "+";
    }

    return allele + rh_factor;
}

set<string> abo_to_allele(const string abo)
{
    set<string> result;
    if (abo == "A") {
        result.insert("AA");
        result.insert("AO");
        result.insert("OA");
    } else if (abo == "B") {
        result.insert("BB");
        result.insert("BO");
        result.insert("OB");
    } else if (abo == "O") {
        result.insert("OO");
    } else {
        result.insert("AB");
        result.insert("BA");
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

set<string> compute_possibilities_from_parent_and_child(set<string> parent, set<string> child)
{
    set<string> result, another_parent = get_all_possibilities();
    for (auto x : parent) {
        for (auto y : another_parent) {
            set<string> p = possibilities_from_parents(x, y);
            set<string> i;
            
            set_intersection(child.begin(), child.end(), p.begin(), p.end(), inserter(i, i.end()));
            if (!i.empty()) {
                result.insert(y);
            }
            //printf("%s %s -- p=%s, i=%s, c=%s\n", x.c_str(), y.c_str(), format_set(p).c_str(), format_set(i).c_str(), format_set(child).c_str());
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

set<string> compute_from_parent_and_child(string parent, string child)
{
    set<string> parent_bt = abo_to_blood_type(parent);
    set<string> child_bt = abo_to_blood_type(child);

    return compute_possibilities_from_parent_and_child(parent_bt, child_bt);
}

set<string> to_abo(set<string> alleles)
{
    set<string> result;
    for (auto x : alleles) {
        result.insert(allele_and_rh_factor_to_abo(x));
    }
    return result;
}

int main()
{
    char f[4], m[4], c[4], i = 0;
    while (scanf("%s %s %s", f, m, c) != EOF && f[0] != 'E') {
        printf("Case %d: ", ++i);
        if (strcmp(c, "?") == 0) {
            string father { f };
            string mother { m };

            printf("%s %s %s\n", f, m, format_set(to_abo(compute_from_parents(father, mother))).c_str());
        } else {
            string parent { strcmp(f, "?") ? f : m };
            string child { c };

            string result = format_set(to_abo(compute_from_parent_and_child(parent, child))).c_str();
            if (strcmp(f, "?")) {
                printf("%s %s %s\n", f, result.c_str(), c);
            } else {
                printf("%s %s %s\n", result.c_str(), m, c);
            }
        }
    }
}

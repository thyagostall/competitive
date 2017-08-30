#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

#define CONTESTANT_QTY 115
#define PROBLEM_QTY 20

#define MAX_CONTESTANT CONTESTANT_QTY + 1
#define MAX_PROBLEM PROBLEM_QTY + 1

using namespace std;

typedef struct {
    int incorrect_qty;
    int correct_time;
    bool solved;
} Problem;

typedef struct {
    Problem problems[MAX_PROBLEM];
    bool participated;
} Contestant;

typedef struct {
    int team_num;
    int problems_solved;
    int penalty;
    bool participated;
} ContestantResult;

bool compare_team(ContestantResult a, ContestantResult b) {
    bool result = b.problems_solved < a.problems_solved;

    if (a.problems_solved == b.problems_solved) {
        result = a.penalty < b.penalty;

        if (a.penalty == b.penalty)
            result = a.team_num < b.team_num;
    }
    
    return result;
}

int main() {
    int test_case_qty;
    string line;
    
    cin >> test_case_qty;       
    getline(cin, line);
    getline(cin, line);

    while (test_case_qty-- > 0) {
        Contestant contestants[MAX_CONTESTANT];
        vector<ContestantResult> result(MAX_CONTESTANT);
        int contestant_num, problem_num, time;
        string veredict;
        
        for (int i = 0; i <= CONTESTANT_QTY; i++) {
            result[i].problems_solved = 0;
            result[i].penalty = 0;
            
            contestants[i].participated = false;
            
            for (int j = 0; j <= PROBLEM_QTY; j++) {
                contestants[i].problems[j].incorrect_qty = 0;
                contestants[i].problems[j].correct_time = 0;
                contestants[i].problems[j].solved = false;
            }
        }

        while (getline(cin, line) && !line.empty()) {
            istringstream in(line);

            in >> contestant_num;
            in >> problem_num;
            in >> time;
            in >> veredict;

//            cout << "Veredict: " << veredict << endl;

            if (!contestants[contestant_num].problems[problem_num].solved) {
                contestants[contestant_num].participated = true;

                if (veredict == "I")
                    contestants[contestant_num].problems[problem_num].incorrect_qty++;
                else if (veredict == "C") {
                    contestants[contestant_num].problems[problem_num].correct_time = time;
                    contestants[contestant_num].problems[problem_num].solved = true;
                }
            }
        }

        for (int i = 1; i <= CONTESTANT_QTY; i++) {
            result[i].team_num = i;
            result[i].participated = contestants[i].participated;

            for (int j = 1; j <= PROBLEM_QTY; j++) {
                if (contestants[i].problems[j].solved) {
                    result[i].penalty += contestants[i].problems[j].incorrect_qty * 20;
                    result[i].penalty += contestants[i].problems[j].correct_time;
                    result[i].problems_solved++;
                }
            }
        }

        sort(result.begin(), result.end(), compare_team);

        for (int i = 0; i <= CONTESTANT_QTY; i++) {
            if (result[i].participated) {
                cout << result[i].team_num << " " << result[i].problems_solved << " " << result[i].penalty << endl;
            }   
        }

        if (test_case_qty > 0)
            cout << endl;
    }

    return 0;
}

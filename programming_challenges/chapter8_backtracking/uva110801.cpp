#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int i, j;
} Piece;

inline int abs(int n)
{
    if (n > 0)
        return n;
    else
        return n * -1;
}

bool isLegalMove(vector<Piece> partialSolution, int currentColumn, int currentRow)
{
    for (int i = 0; i < partialSolution.size(); i++)
    {
        if (currentRow == partialSolution[i].i && currentColumn == partialSolution[i].j)
            return false;

        if (abs(partialSolution[i].j - currentRow) == abs(partialSolution[i].i - currentColumn))
            return false;
    }
    return true;
}

bool isSolution(vector<Piece> solutionCandidate, int solutionSize)
{
    return solutionCandidate.size() == solutionSize;
}

void generateCandidates(vector<Piece> partialSolution, vector<Piece> &candidates, int currentColumn, int currentRow, int boardSize)
{
    int lastPiecePos, currPos;

    lastPiecePos = currentColumn + currentRow * boardSize;
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
        {
            currPos = i * boardSize + j;

            if (lastPiecePos <= currPos)
                continue;

            if (isLegalMove(partialSolution, i, j))
            {
                Piece item;
                item.i = i, item.j = j;
                candidates.push_back(item);
            }
        }
}

int backtrack(vector<Piece> partialSolution, int pieceQty, int boardSize)
{
    int result = 0;
    vector<Piece> candidates;
    
    if (isSolution(partialSolution, pieceQty))
    {
        result++;
    }
    else
    {
        Piece last;
        candidates.clear();

        if (partialSolution.size())
        {
            last.i = (partialSolution.end() - 1)->i;
            last.j = (partialSolution.end() - 1)->j;
        }
        else
            last.i = 0, last.j = 0;

        generateCandidates(partialSolution, candidates, last.j, last.i, boardSize);
        for (int i = 0; i < candidates.size(); i++)
        {
            partialSolution.push_back(candidates[i]);
            result += backtrack(partialSolution, pieceQty, boardSize);
            partialSolution.erase(partialSolution.end() - 1);
        }
    }
    return result;
}

void generateFirstCandidates(int n, vector<Piece> &result)
{    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            Piece item;
            item.i = i, item.j = j;
            result.push_back(item);
        }
}

int processGame(int n, int k)
{
    if (k == 0 || n == 1)
        return 1;
    if (k == 1)
        return n;
    if (n == 2 && k > 2)
        return 0;
    if (n == 3 && k > 4)
        return 0;
    if (n == 4 && k > 5)
        return 0;
    if (n == 5 && k > 7)
        return 0;
    if (n == 6 && k > 9)
        return 0;
    if (n == 7 && k > 12)
        return 0;
    if (n == 8 && k > 14)
        return 0;

    int result = 0;
    vector<Piece> firstCandidates, partialSolution;

    generateFirstCandidates(n, firstCandidates);
    for (int i = 0; i < firstCandidates.size(); i++)
    {
        partialSolution.push_back(firstCandidates[i]);
        result += backtrack(partialSolution, k, n);
        partialSolution.erase(partialSolution.end() - 1);
    }
    return result;
}

int main()
{
    int i, j;
    while (cin >> i >> j && i)
        cout << processGame(i, j) << endl;
}

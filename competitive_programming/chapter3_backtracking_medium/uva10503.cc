#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> Piece;

Piece read_piece();
bool compute(int space_qty, Piece start_piece, Piece end_piece, vector<Piece> &pieces);
bool backtrack(int current_size, int max_size, int last_q, const Piece &end_piece, vector<Piece> &pieces, vector<bool> &available);

int main()
{
    int space_qty, piece_qty;
    while (cin >> space_qty && space_qty) {
        cin >> piece_qty;
        vector<Piece> pieces; 
        Piece start_piece = read_piece();
        Piece end_piece = read_piece();

        while (piece_qty--) {
            pieces.push_back(read_piece());
        }

        bool response = compute(space_qty, start_piece, end_piece, pieces);
        cout << (response ? "YES" : "NO") << endl;
    }
}

ostream& operator<<(ostream &out, const Piece &piece)
{
    out << "(" << piece.first << ", " << piece.second << ")";
    return out;
}

Piece read_piece()
{
    Piece piece;
    cin >> piece.first;
    cin >> piece.second;
    return piece;
}

bool compute(int space_qty, Piece start_piece, Piece end_piece, vector<Piece> &pieces)
{
    vector<bool> available(pieces.size(), true);
    return backtrack(0, space_qty, start_piece.second, end_piece, pieces, available);
}

bool compatible(int last_q, const Piece &piece)
{
    return last_q == piece.first || last_q == piece.second;
}

bool backtrack(int current_size, int space_qty, int last_q, const Piece &end_piece, vector<Piece> &pieces, vector<bool> &available)
{
    if (current_size == space_qty) 
        return last_q == end_piece.first;

    for (int i = 0; i < pieces.size(); i++) {
        if (!available[i]) 
            continue;
        if (!compatible(last_q, pieces[i])) 
            continue;

        available[i] = false;
        
        int q;
        if (last_q == pieces[i].first) {
            q = pieces[i].second;
        } else {
            q = pieces[i].first;
        } 

        if (backtrack(current_size + 1, space_qty, q, end_piece, pieces, available)) {
            return true;
        }
        
        available[i] = true;
    }
    return false;
}

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct Cell {
    int x;
    int y;
};

bool onBoard(const Cell& c) {
    return c.x >= 1 && c.x <= 8 && c.y >= 1 && c.y <= 8;
}

bool sameCell(const Cell& a, const Cell& b) {
    return a.x == b.x && a.y == b.y;
}

bool onDiagonal(const Cell& a, const Cell& b) {
    return abs(a.x - b.x) == abs(a.y - b.y) && a.x != b.x;
}

bool betweenStraight(const Cell& p, const Cell& a, const Cell& b) {
    if (a.x == b.x && p.x == a.x)
        return (a.y < p.y && p.y < b.y) || (b.y < p.y && p.y < a.y);
    if (a.y == b.y && p.y == a.y)
        return (a.x < p.x && p.x < b.x) || (b.x < p.x && p.x < a.x);
    return false;
}

bool betweenDiagonal(const Cell& p, const Cell& a, const Cell& b) {
    return onDiagonal(a, p) && onDiagonal(p, b) &&
           abs(a.x - p.x) < abs(a.x - b.x) &&
           abs(a.y - p.y) < abs(a.y - b.y);
}

bool rookThreat(const Cell& k, const Cell& r, const Cell& b) {
    if (k.x != r.x && k.y != r.y) return false;
    if (betweenStraight(b, k, r)) return false;
    return true;
}

bool bishopThreat(const Cell& k, const Cell& b, const Cell& r) {
    if (!onDiagonal(k, b))        return false;
    if (betweenDiagonal(r, k, b)) return false;
    return true;
}

Cell readCell(const string& who) {
    Cell c;
    cout << "Введите координаты " << who << " (x y, 1..8): ";
    cin >> c.x >> c.y;
    if (!cin || !onBoard(c)) {
        cerr << "Ошибка: клетка вне доски." << endl;
        exit(1);
    }
    return c;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Cell K = readCell("белого короля");
    Cell R = readCell("черной ладьи");
    Cell B = readCell("черного слона");

    if (sameCell(K, R) || sameCell(K, B) || sameCell(R, B)) {
        cerr << "Ошибка: фигуры не могут стоять на одной клетке." << endl;
        return 1;
    }

    bool rook   = rookThreat(K, R, B);
    bool bishop = bishopThreat(K, B, R);

    if (rook && bishop)  cout << "Угроза королю от ладьи и слона." << endl;
    else if (rook)       cout << "Угроза королю от ладьи." << endl;
    else if (bishop)     cout << "Угроза королю от слона." << endl;
    else                 cout << "Угрозы королю нет." << endl;

    return 0;
}

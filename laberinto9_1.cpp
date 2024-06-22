#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>

using namespace std;

struct Cell {
    int x, y;
    Cell(int _x, int _y) : x(_x), y(_y) {}
};

void reservar(char*** mat, int n, int m) {
    *mat = new char*[n];
    for (int i = 0; i < n; i++) {
        *(*mat + i) = new char[m];
    }
}

void llenar(char** mat, int n, int m) {
    // Initialize the maze with walls
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat[i][j] = '#';
        }
    }

    // Maze generation using recursive backtracking
    srand(time(0));
    stack<Cell> s;
    s.push(Cell(1, 1));
    mat[1][1] = ' '; // Starting point

    while (!s.empty()) {
        Cell current = s.top();
        vector<Cell> neighbors;

        // Check for valid neighbors
        if (current.x > 1 && mat[current.x - 2][current.y] == '#') {
            neighbors.push_back(Cell(current.x - 2, current.y));
        }
        if (current.x < n - 2 && mat[current.x + 2][current.y] == '#') {
            neighbors.push_back(Cell(current.x + 2, current.y));
        }
        if (current.y > 1 && mat[current.x][current.y - 2] == '#') {
            neighbors.push_back(Cell(current.x, current.y - 2));
        }
        if (current.y < m - 2 && mat[current.x][current.y + 2] == '#') {
            neighbors.push_back(Cell(current.x, current.y + 2));
        }

        if (!neighbors.empty()) {
            Cell next = neighbors[rand() % neighbors.size()];
            mat[(current.x + next.x) / 2][(current.y + next.y) / 2] = ' '; // Remove wall
            mat[next.x][next.y] = ' '; // Mark cell as visited
            s.push(next);
        } else {
            s.pop();
        }
    }

    // Ensure start and end points are open and marked with 'E' and 'S'
    mat[1][1] = 'E';
    mat[n - 2][m - 2] = 'S';
}

void mostrar(char** mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << mat[i][j];
        }
        cout << endl;
    }
}

bool seguro(char** mat, int N, int M, int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < M && (mat[x][y] == ' ' || mat[x][y] == 'S'));
}

bool camino(char ** mat, int N, int M, int x, int y, int finf, int finc) {
    if (x == finf && y == finc) {
        mat[x][y] = 'S'; // Ensure end remains 'S'
        return true;
    }
    if (seguro(mat, N, M, x, y)) {
        if (mat[x][y] != 'E' && mat[x][y] != 'S') { // Avoid overwriting 'E' and 'S'
            mat[x][y] = '.';
        }
        if (camino(mat, N, M, x + 1, y, finf, finc))
            return true;
        if (camino(mat, N, M, x - 1, y, finf, finc))
            return true;
        if (camino(mat, N, M, x, y - 1, finf, finc))
            return true;
        if (camino(mat, N, M, x, y + 1, finf, finc))
            return true;
        if (mat[x][y] != 'E' && mat[x][y] != 'S') { // Avoid overwriting 'E' and 'S'
            mat[x][y] = ' ';
        }
        return false;
    }
    return false;
}

void liberar(char** mat, int n) {
    for (int i = 0; i < n; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

int main() {
    int N = 13; // Include border walls
    int M = 21; // Include border walls
    char** matriz;

    reservar(&matriz, N, M);
    llenar(matriz, N, M);
    mostrar(matriz, N, M);
    cout << endl;

    if (camino(matriz, N, M, 1, 1, N - 2, M - 2)) {
        mostrar(matriz, N, M);
    } else {
        cout << "No solution found!" << endl;
    }

    liberar(matriz, N);
    return 0;
}
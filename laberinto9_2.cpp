#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>
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
            mat[i][j] = '|';
        }
    }

    // Maze generation using recursive backtracking (DFS)
    srand(time(0));
    stack<Cell> s;
    s.push(Cell(1, 1));
    mat[1][1] = ' '; // Starting point

    while (!s.empty()) {
        Cell current = s.top();
        vector<Cell> neighbors;

        // Check for valid neighbors
        if (current.x > 1 && mat[current.x - 2][current.y] == '|') {
            neighbors.push_back(Cell(current.x - 2, current.y));
        }
        if (current.x < n - 2 && mat[current.x + 2][current.y] == '|') {
            neighbors.push_back(Cell(current.x + 2, current.y));
        }
        if (current.y > 1 && mat[current.x][current.y - 2] == '|') {
            neighbors.push_back(Cell(current.x, current.y - 2));
        }
        if (current.y < m - 2 && mat[current.x][current.y + 2] == '|') {
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

bool bfs(char** mat, int N, int M, int startX, int startY, int endX, int endY) {
    queue<Cell> q;
    q.push(Cell(startX, startY));
    bool found = false;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<Cell>> parent(N, vector<Cell>(M, Cell(-1, -1)));

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    visited[startX][startY] = true;

    while (!q.empty() && !found) {
        Cell current = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (seguro(mat, N, M, newX, newY) && !visited[newX][newY]) {
                q.push(Cell(newX, newY));
                visited[newX][newY] = true;
                parent[newX][newY] = current;

                if (newX == endX && newY == endY) {
                    found = true;
                    break;
                }
            }
        }
    }

    if (found) {
        Cell step = parent[endX][endY];
        while (step.x != -1 && step.y != -1 && !(step.x == startX && step.y == startY)) {
            mat[step.x][step.y] = '.';
            step = parent[step.x][step.y];
        }
        return true;
    } else {
        return false;
    }
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

    if (bfs(matriz, N, M, 1, 1, N - 2, M - 2)) {
        mostrar(matriz, N, M);
    } else {
        cout << "No solution found!" << endl;
    }

    liberar(matriz, N);
    return 0;
}

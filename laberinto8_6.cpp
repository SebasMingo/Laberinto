#include <iostream>
using namespace std;

void reservar(char*** mat, int n, int m) {
    *mat = new char*[n];
    for (int i = 0; i < n; i++) {
        *(*mat + i) = new char[m];
    }
}

void llenar(char** mat, int n, int m) {
    // Initialize the maze with a fixed pattern
    const char* pattern[] = {
        "#####################",
        "E #    #     #    #",
        "# ### ### ### ### # #",
        "#   #   # #   #   # #",
        "### # # ### # # ### #",
        "#   # # #   # #     #",
        "# ### ### ##### #####",
        "#     #     #   #   #",
        "##### # ##### ### # #",
        "#   # #   #     # # #",
        "# ### ### ### ### ###",
        "#     #   #         S",
        "#####################"
    };
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat[i][j] = pattern[i][j];
        }
    }
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

#include <iostream>

using namespace std;



void reservar(char*** mat, int n, int m) {

 *mat = new char*[n];

 for (int i = 0; i < n; i++) {

  *(*mat + i) = new char[m];

 }

}

void llenar(char** mat, int n, int m, int i, int j) {

 if (i < n) {

  if (j < m) {

   *(*(mat + i) + j) = ' ';

   j++;

   llenar(mat, n, m, i, j);

  }

  else {

   j = 0;

   i++;

   llenar(mat, n, m, i, j);

  }

 }

 *(*(mat + 0) + 13) = 219; *(*(mat + 0) + 15) = 219;

 *(*(mat + 1) + 0) = 219; *(*(mat + 1) + 1) = 219;

 *(*(mat + 1) + 4) = 219; *(*(mat + 1) + 6) = 219; *(*(mat + 1) + 10) = 219; *(*(mat + 1) + 13) = 219; *(*(mat + 1) + 15) = 219; *(*(mat + 1) + 18) = 219;

 *(*(mat + 2) + 1) = 219; *(*(mat + 2) + 3) = 219; *(*(mat + 2) + 4) = 219; *(*(mat + 2) + 5) = 219; *(*(mat + 2) + 6) = 219; *(*(mat + 2) + 7) = 219;

 *(*(mat + 2) + 8) = 219; *(*(mat + 2) + 9) = 219; *(*(mat + 2) + 10) = 219; *(*(mat + 2) + 11) = 219; *(*(mat + 2) + 12) = 219; *(*(mat + 2) + 13) = 219; *(*(mat + 2) + 15) = 219; *(*(mat + 2) + 16) = 219; *(*(mat + 2) + 18) = 219;

 *(*(mat + 3) + 1) = 219; *(*(mat + 3) + 3) = 219; *(*(mat + 3) + 6) = 219; *(*(mat + 3) + 8) = 219; *(*(mat + 3) + 15) = 219; *(*(mat + 3) + 18) = 219;

 *(*(mat + 4) + 6) = 219; *(*(mat + 4) + 8) = 219; *(*(mat + 4) + 10) = 219; *(*(mat + 4) + 11) = 219; *(*(mat + 4) + 12) = 219; *(*(mat + 4) + 13) = 219; *(*(mat + 4) + 15) = 219; *(*(mat + 4) + 16) = 219; *(*(mat + 4) + 18) = 219;

 *(*(mat + 5) + 1) = 219; *(*(mat + 5) + 2) = 219; *(*(mat + 5) + 3) = 219; *(*(mat + 5) + 4) = 219; *(*(mat + 5) + 8) = 219; *(*(mat + 5) + 10) = 219; *(*(mat + 5) + 12) = 219; *(*(mat + 5) + 15) = 219; *(*(mat + 5) + 18) = 219;

 *(*(mat + 6) + 3) = 219; *(*(mat + 6) + 6) = 219; *(*(mat + 6) + 8) = 219; *(*(mat + 6) + 10) = 219; *(*(mat + 6) + 12) = 219; *(*(mat + 6) + 13) = 219; *(*(mat + 6) + 15) = 219; *(*(mat + 6) + 16) = 219; *(*(mat + 6) + 17) = 219; *(*(mat + 6) + 18) = 219;

 *(*(mat + 7) + 1) = 219; *(*(mat + 7) + 2) = 219; *(*(mat + 7) + 3) = 219; *(*(mat + 7) + 4) = 219; *(*(mat + 7) + 6) = 219; *(*(mat + 7) + 10) = 219; *(*(mat + 7) + 12) = 219; *(*(mat + 7) + 15) = 219; *(*(mat + 7) + 17) = 219;

 *(*(mat + 8) + 1) = 219; *(*(mat + 8) + 3) = 219; *(*(mat + 8) + 6) = 219; *(*(mat + 8) + 7) = 219; *(*(mat + 8) + 8) = 219; *(*(mat + 8) + 9) = 219; *(*(mat + 8) + 10) = 219; *(*(mat + 8) + 12) = 219; *(*(mat + 8) + 15) = 219; *(*(mat + 8) + 17) = 219; *(*(mat + 8) + 18) = 219;

 *(*(mat + 9) + 1) = 219; *(*(mat + 9) + 12) = 219; *(*(mat + 9) + 13) = 219; *(*(mat + 9) + 19) = 219;



}

void mostrar(char** mat, int n, int m, int i, int j) {

 if (i < n) {

  if (j < m) {

   cout << *(*(mat + i) + j);

   j++;

   mostrar(mat, n, m, i, j);

  }

  else {

   cout << endl;

   i++;

   j = 0;

   mostrar(mat, n, m, i, j);

  }

 }

}

bool seguro(char** mat, int N, int M, int x, int y) {



 if (x >= 0 && x < N && y >= 0 && y < M && *(*(mat + x) + y) == ' ') {

  return true;

 }

 return false;



}





bool camino(char ** mat, int N, int M, int x, int y, int finf, int finc) {

 if (x == finf && y == finc) {

  *(*(mat + x) + y) = 1;

  return true;

 }

 if (seguro(mat, N, M, x, y) == true) {

  *(*(mat + x) + y) = 1;

  if (camino(mat, N, M, x + 1, y, finf, finc) == true)

   return true;

  if (camino(mat, N, M, x - 1, y, finf, finc) == true)

   return true;

  if (camino(mat, N, M, x, y - 1, finf, finc) == true)

   return true;

  if (camino(mat, N, M, x, y + 1, finf, finc) == true)

   return true;

  *(*(mat + x) + y) = ' ';

  return false;

 }

 return false;

}



void liberar(char** mat, int n) {

 for (int i = 0; i < n; i++) {

  delete[] * (mat + i);

 }

 delete[]mat;

}



int main() {

 int N = 10;

 int M = 20;

 char** matriz;



 reservar(&matriz, N, M);

 llenar(matriz, N, M, 0, 0);

 mostrar(matriz, N, M, 0, 0);

 cout << endl;

 camino(matriz, N, M, 0, 0, 9, 0);

 mostrar(matriz, N, M, 0, 0);

 liberar(matriz, N);





 system("pause");

 return 0;
 
}
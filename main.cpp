#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<double>> Matrix;

bool choleskyDecomposition(const Matrix& A, Matrix& L) {
    int n = A.size();
    L = Matrix(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;

            if (j == i) { // Диагональный элемент
                for (int k = 0; k < j; k++)
                    sum += L[j][k] * L[j][k];
                double value = A[j][j] - sum;
                if (value <= 0.0)
                    return false; // Матрица не положительно определена
                L[j][j] = sqrt(value);
            } else {
                for (int k = 0; k < j; k++)
                    sum += L[i][k] * L[j][k];
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    return true;
}

void printMatrix(const Matrix& mat) {
    std::vector<double>::size_type n = mat.size();
    for (std::vector<double>::size_type i = 0; i < n; i++) {
        for (std::vector<double>::size_type j = 0; j < mat[i].size(); j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }
}

int main() {
    Matrix A = {
        {4, -1, 0, 0, -1},
        {-1, 5, -1, 0, -1},
        {0, -1, 6, 0, -1},
        {0, 0, 0, 7, 0},
        {-1, -1, -1, 0, 8}
    };

    Matrix L;
    if (choleskyDecomposition(A, L)) {
        cout << "Матрица L:" << endl;
        printMatrix(L);
    } else {
        cout << "Матрица не является положительно определенной." << endl;
    }

    return 0;
}


// 5
// 4 -1 0 0 -1 
// -1 5 -1 0 -1
// 0 -1 6 0 -1
// 0 0 0 7 0
// -1 -1 -1 0 8
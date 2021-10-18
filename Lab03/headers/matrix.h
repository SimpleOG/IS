#include <vector>

#ifndef IS_MATRIX_H
#define IS_MATRIX_H

using namespace std;

vector<vector<double>> operator+(const vector<vector<double>> &x, const vector<vector<double>> &y) {
    vector<vector<double>> res(x.size(), vector<double>(x.back().size()));
    for (int i = 0; i < x.size(); i++)
        for (int j = 0; j < x[i].size(); j++)
            res[i][j] = x[i][j] + y[i][j];
    return res;
}

vector<vector<double>> operator-(const vector<vector<double>> &x, const vector<vector<double>> &y) {
    vector<vector<double>> res(x.size(), vector<double>(x.back().size()));
    for (int i = 0; i < x.size(); i++)
        for (int j = 0; j < x[i].size(); j++)
            res[i][j] = x[i][j] - y[i][j];
    return res;
}

vector<vector<double>> operator*(const vector<vector<double>> &x, const vector<vector<double>> &y) {
    vector<vector<double>> res(x.size(), vector<double>(y.back().size()));
    for (int i = 0; i < x.size(); i++)
        for (int j = 0; j < y[i].size(); j++) {
            double sum = 0;
            for (int k = 0; k < y.size(); k++)
                sum += x[i][k] * y[k][j];
            res[i][j] = sum;
        }
    return res;
}

vector<vector<double>> getE(int rows, int cols) {
    vector<vector<double>> E(rows, vector<double>(cols, 0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (i == j)
                E[i][j] = 1;
    return E;
}

vector<vector<double>> transpose(const vector<vector<double>> &x) {
    vector<vector<double>> res(x.back().size(), vector<double>(x.size()));
    for (int i = 0; i < x.size(); i++)
        for (int j = 0; j < x[i].size(); j++)
            res[j][i] = x[i][j];
    return res;
}

vector<vector<double>> inverse(const vector<vector<double>> &a) {
    vector<vector<double>> triangular = a;
    unsigned int N = triangular.size();

    for (int i = 0; i < N; i++) {
        triangular[i].resize(N * 2);
        triangular[i][N + i] = 1;
    }

    double rate;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (i != j) {
                rate = triangular[j][i] / triangular[i][i];
                for (int k = 0; k < 2 * N; k++)
                    triangular[j][k] -= rate * triangular[i][k];
            }
    }

    for (int i = 0; i < N; i++) {
        for (int j = N; j < 2 * N; j++)
            triangular[i][j] /= triangular[i][i];
        triangular[i].erase(triangular[i].begin(), triangular[i].begin() + N);
    }

    return triangular;
}

#endif //IS_MATRIX_H

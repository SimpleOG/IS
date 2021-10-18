#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include "headers/matrix.h"

using namespace std;

struct number {
    vector<double> core;
    vector<vector<double>> covarianceMatrix;
    vector<vector<double>> samples;
};

map<double, number> &parseNumbers(string &fileName, int p, map<double, number> &numbers) {
    ifstream input;
    input.open(fileName);
    if (!input.is_open())
        throw invalid_argument("Error! Cannot load the file " + fileName + "\n");

    int num;
    char val;
    while (input >> num) {
        numbers[num].samples.push_back(vector<double>(100));
        for (int i = 0; i < p; i++) {
            input >> val;
            numbers[num].samples.back()[i] = val == '1' ? 1 : 0;
        }
    }

    return numbers;
}

void calcCovarianceMatrix(int p, int num, map<double, number> &numbers) {
    vector<vector<double>> covarianceMatrix(p, vector<double>(p, 0));
    vector<double> core(p, 0);

    for (int i = 0; i < core.size(); i++) {
        for (auto &c: numbers[num].samples)
            core[i] += c[i];
        core[i] /= numbers[num].samples.size();
    }
    numbers[num].core = core;

    for (int i = 0; i < p; i++)
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < numbers[num].samples.size(); k++)
                covarianceMatrix[i][j] +=
                        (numbers[num].samples[k][i] - core[i]) * (numbers[num].samples[k][j] - core[j]);
            covarianceMatrix[i][j] /= (numbers[num].samples.size() - 1);
        }
    numbers[num].covarianceMatrix = covarianceMatrix;
}

double getDistance(vector<vector<double>> x, vector<vector<double>> y, vector<vector<double>> &S) {
    return ((x - y) * inverse(S + getE(S.size(), S.back().size())) * transpose(x - y))[0][0];
}

double findClass(vector<double> &task, map<double, number> &numbers) {
    double min = 15;
    double curClass = -1;

    for (auto &num: numbers) {
        double d = getDistance({task}, {num.second.core}, num.second.covarianceMatrix);
        if (d < min) {
            min = d;
            curClass = num.first;
        }
    }

    return curClass;
}

int main() {
    int p = 100;
    string numbersFile = "../Lab03/Data/numbers.txt", taskFile = "../Lab03/Data/task.txt";
    map<double, number> numbers, tasks;
    numbers = parseNumbers(numbersFile, p, numbers);
    tasks = parseNumbers(taskFile, p, tasks);

    cout << "===========INFO============\n";
    for (auto &num: numbers) {
        cout << "CLASS " << num.first << "\n";
        calcCovarianceMatrix(p, num.first, numbers);
        cout << "Core: \n";
        for (auto &c: num.second.core)
            cout << c << ", ";
        cout << "\n";
        for (auto &sample: num.second.samples)
            for (int i = 0; i < sample.size(); i++) {
                cout << (sample[i] == 1 ? '*' : ' ') << ' ';
                if (i != 0 && i % int(sqrt(p)) == 0)
                    cout << endl;
            }
        cout << '\n';
    }

    cout << "===========TASK============\n";
    for (auto &task: tasks) {
        cout << "CLASS " << task.first << ":\n";
        for (auto &sample: task.second.samples) {
            double numClass = findClass(sample, numbers);
            cout << "I think its ";
            if (numClass == -1)
                cout << "something new";
            else
                cout << numClass;
            for (int i = 0; i < sample.size(); i++) {
                cout << (sample[i] == 1 ? '*' : ' ') << ' ';
                if (i != 0 && i % int(sqrt(p)) == 0)
                    cout << endl;
            }
        }
        cout << '\n';
    }

    return 0;
}
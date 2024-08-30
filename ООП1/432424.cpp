#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

// Функція для читання матриці з файлу
bool readMatrixFromFile(const string& filename, vector<vector<int>>& matrix) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    int rows, cols;
    if (!(file >> rows >> cols)) {
        cerr << "Error: Invalid file format. Expected rows and columns at the start." << endl;
        return false;
    }

    matrix.resize(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) {
                cerr << "Error: Invalid matrix data." << endl;
                return false;
            }
        }
    }

    file.close();
    return true;
}

// Функція для сортування матриці
void sortMatrix(vector<vector<int>>& matrix) {
    for (auto& row : matrix) {
        sort(row.begin(), row.end(), greater<int>());
    }
}

// Функція для аналізу матриці
void analyzeMatrix(const vector<vector<int>>& matrix, int& maxVal, int& minVal, int& maxRow, int& maxCol, int& minRow, int& minCol) {
    maxVal = INT_MIN;
    minVal = INT_MAX;
    maxRow = maxCol = minRow = minCol = 0;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxRow = i;
                maxCol = j;
            }
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }
}

// Функція для запису результатів у файл
bool writeResultsToFile(const string& outputFilename, int maxVal, int minVal, int maxRow, int maxCol, int minRow, int minCol) {
    ofstream outfile(outputFilename);
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open file for writing " << outputFilename << endl;
        return false;
    }

    outfile << "Maximum value: " << maxVal << " at (" << maxRow << ", " << maxCol << ")\n";
    outfile << "Minimum value: " << minVal << " at (" << minRow << ", " << minCol << ")\n";

    outfile.close();
    return true;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> matrix;
    int maxVal, minVal, maxRow, maxCol, minRow, minCol;

    // Перевірка наявності аргументів командного рядка
    string inputFilename, outputFilename = "output.txt";
    if (argc < 2) {
        cout << "Please enter the input file name: ";
        cin >> inputFilename;
    }
    else {
        inputFilename = argv[1];
        if (argc >= 3) {
            outputFilename = argv[2];
        }
    }

    // Читання матриці з файлу
    if (!readMatrixFromFile(inputFilename, matrix)) {
        return 1; // Повертаємо ненульовий код помилки
    }

    // Сортування матриці
    sortMatrix(matrix);

    // Аналіз матриці
    analyzeMatrix(matrix, maxVal, minVal, maxRow, maxCol, minRow, minCol);

    // Запис результатів у файл
    if (!writeResultsToFile(outputFilename, maxVal, minVal, maxRow, maxCol, minRow, minCol)) {
        return 1; // Повертаємо ненульовий код помилки
    }

    cout << "Results successfully written to " << outputFilename << endl;

    return 0;
}

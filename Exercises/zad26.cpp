#include <iostream>
#include <cstring>
#include <functional>
using namespace std;

template <typename T>
//int countIf(T* arr, int size, function<bool(const T&)> f) {
int countIf(T* arr, int size, bool (*f)(const T&)) {
    int counter = 0;

    for(int i = 0; i < size; i++) {
        if(f(arr[i])) counter++;
    }

    return counter;
}

class Matrix
{
private:
    int rows;
    int cols;
    double** data;

    void copyFrom(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;

        data = new double*[rows];
        for(int i = 0; i < rows; i++) {
            data[i] = new double[cols];

            for(int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    void free() {
        if(data == nullptr) return;

        for(int i = 0; i < rows; i++) {
            delete[] data[i];
        }

        delete[] data;
        data = nullptr;
        rows = 0;
        cols = 0;
    }
public:
    Matrix() : rows(0), cols(0), data(nullptr) {}

    Matrix(int r ,int c, const double** d) : rows(r), cols(c) {
        data = new double*[rows];

        for(int i = 0; i < rows; i++) {
            data[i] = new double[cols];

            for(int j = 0; j < cols; j++) {
                data[i][j] = d[i][j];
            }
        }
    }

    Matrix(const Matrix& other) {
        copyFrom(other);
    }

    Matrix& operator=(const Matrix& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~Matrix() {
        free();
    }

    double& operator()(int i, int j) {
        return data[i][j];
    }

    double operator()(int i, int j) const {
        return data[i][j];
    }

    Matrix operator+(const Matrix& other) const {
        if(rows != other.rows || cols != other.cols) return Matrix();

        Matrix result;
        result.rows = rows;
        result.cols = cols;

        result.data = new double*[rows];
        for(int i = 0; i < rows; i++) {
            result.data[i] = new double[cols];

            for(int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if(cols != other.rows) return Matrix();

        Matrix result;
        result.rows = rows;
        result.cols = other.cols;

        result.data = new double*[rows];
        for(int i = 0; i < rows; i++) {
            result.data[i] = new double[result.cols];

            for(int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;

                for(int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    friend ostream& operator<<(ostream& os, const Matrix& m);
};

ostream& operator<<(ostream& os, const Matrix& m) {
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j  < m.cols; j++) {
            os << m.data[i][j] << " ";
        }
        os << endl;
    }

    return os;
}

int main() {
    double** a = new double*[2];
    double** b = new double*[2];

    for(int i = 0; i < 2; i++) {
        a[i] = new double[2];
        b[i] = new double[2];
    }

    // Matrix A
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    // Matrix B
    b[0][0] = 5; b[0][1] = 6;
    b[1][0] = 7; b[1][1] = 8;

    Matrix m1(2, 2, (const double**)a);
    Matrix m2(2, 2, (const double**)b);

    cout << "Matrix A:" << endl;
    cout << m1 << endl;

    cout << "Matrix B:" << endl;
    cout << m2 << endl;

    // Събиране
    Matrix sum = m1 + m2;
    cout << "A + B:" << endl;
    cout << sum << endl;

    // Умножение
    Matrix product = m1 * m2;
    cout << "A * B:" << endl;
    cout << product << endl;

    // Тест на operator()
    cout << "Element m1(1,1): " << m1(1,1) << endl;

    // Освобождаване на входните масиви
    for(int i = 0; i < 2; i++) {
        delete[] a[i];
        delete[] b[i];
    }
    
    delete[] a;
    delete[] b;

    return 0;
}

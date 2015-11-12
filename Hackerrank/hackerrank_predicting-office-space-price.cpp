/*
*
* This code is copid from others ...
*
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

template<typename T> vector<vector<T> > submatrix(vector<vector<T> > X, int i1, int i2, int j1, int j2);
void readMatrix(vector<vector<double> > &X);
vector<vector<double> > transpose(vector<vector<double> > &X);
void printVector(vector<double> &x);
void printMatrix(vector<vector<double> > X);
template<typename T> vector<T> solve(vector<vector<T> > A, vector<T> b);
template<typename T> vector<T> solve(vector<vector<T> > A, vector<vector<T> > B);
template<typename T> vector<T> multiply(vector<vector<T> > A, vector<T> b);
template<typename T> vector<vector<T> > multiply(vector<vector<T> > A, vector<vector<T> > B);
template<typename T> vector<T> vec(vector<vector<T> > X);
template<typename T> vector<vector<T> > elementwise_multiply(vector<vector<T> > A, vector<vector<T> > B);
template<typename T> vector<vector<T> > elementwise_power(vector<vector<T> > &A, int exponent);
template<typename T> vector<vector<T> > column_concatenate(vector<vector<T> > A, vector<vector<T> > B);
template<typename T> vector<vector<T> > add(vector<vector<T> > A, vector<vector<T> > B);
template<typename T> vector<vector<T> > diag(vector<T> a);
template<typename T> vector<T> diag(vector<vector<T> > a);
template<typename T> vector<vector<T> > polynomialFeatures(vector<vector<T> > X);


int main() {

    int F, N, T;

    cin >> F >> N;

    vector<vector<double> > data(N, vector<double> (F+1, 0.0)); // N x (F+1) matrix.

    // Read training data.
    readMatrix(data);
    //printMatrix(data);

    vector<vector<double> > X    = submatrix(data, 0, N-1, 0, F-1);
    vector<vector<double> > Phi  = polynomialFeatures(X);
    // vector<vector<double> > ones( 1, vector<double> (N,1) );
    // vector<vector<double> > Phi  = column_concatenate(column_concatenate(transpose(ones), X), column_concatenate(elementwise_power(X,2), elementwise_power(X,3)));
    // vector<vector<double> > Phi  = column_concatenate(column_concatenate(transpose(ones), X), elementwise_power(X,2));
    // vector<vector<double> > Phi  = column_concatenate(column_concatenate(transpose(ones), X), elementwise_power(X,2));
    // vector<vector<double> > Phi  = column_concatenate(transpose(ones), X);
    vector<double> y = vec(submatrix(data, 0, N-1, F, F));
    //printMatrix(Phi);

    // Fit regression model.
    vector<vector<double> > Phi_t     = transpose(Phi);
    vector<vector<double> > Phi_t_Phi = multiply(Phi_t, Phi);
    vector<double> lambda(Phi_t_Phi.size(), 0);  Phi_t_Phi = add( Phi_t_Phi, diag(lambda)); // Regulatization parameter.
    vector<double>          Phi_t_y   = multiply(Phi_t, y);
    vector<double>          w         = solve(Phi_t_Phi , Phi_t_y);
    //printVector(w);

    // Read test data.
    cin >> T; //cout << T << endl;
    vector<vector<double> > test(T, vector<double> (F, 0.0)); // T x F matrix.
    readMatrix(test);
    vector<vector<double> > Phi_test  = polynomialFeatures(test);
    // vector<vector<double> > ones_F( 1, vector<double> (T,1) );
    // vector<vector<double> > Phi_test = column_concatenate(column_concatenate(transpose(ones_F), test), column_concatenate(elementwise_power(test,2), elementwise_power(test,3)));
    // vector<vector<double> > Phi_test = column_concatenate(column_concatenate(transpose(ones_F), test), elementwise_power(test,2));
    // vector<vector<double> > Phi_test = column_concatenate(transpose(ones_F), test);
    //printMatrix(Phi_test);
    vector<double> y_test = multiply(Phi_test, w);

    for (int i = 0; i < y_test.size(); ++i) {
        cout << y_test[i] << endl;
    }

    return 0;
}



// Returns the transpose of matrix X.
vector<vector<double> > transpose(vector<vector<double> > &X)
{
    int rows    = X.size();
    int columns = X[0].size();

    vector<double> _row(rows, 0); // This becomes as long as a column of the original matrix.
    vector<vector<double> > transposedMatrix(columns, _row);

    for (int j = 0; j < columns; j++) {
        // Fill in _row.
        for (int i=0; i<rows; i++) {
            _row[i] = X[i][j];
        }
        // Copy it into the transposed matrix.
        transposedMatrix[j] = _row;
    }

    return transposedMatrix;
}

void readMatrix(vector<vector<double> > &X)
{
    int rows    = X.size();
    int columns = X[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> X[i][j];
        }
    }
}

void printVector(vector<double> &x)
{
    for (int i=0; i < x.capacity(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void printMatrix(vector<vector<double> > X)
{
    for (int i=0; i < X.capacity(); i++) {
        printVector(X[i]);
    }
    cout << endl;
}

template<typename T> vector<vector<T> > submatrix(vector<vector<T> > X, int i1, int i2, int j1, int j2)
{
    int rows = i2 - i1 + 1;
    int cols = j2 - j1 + 1;
    vector<vector<T> > sub(rows, vector<T> (cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sub[i][j] = X[ i1 + i ][ j1 + j ];
        }
    }

    return sub;
}

template<typename T> vector<T> solve(vector<vector<T> > A, vector<T> b)
{
    int size = A.size();
    //vector<T> x = b;

    // Eliminate lower-triangular part.
    for (int p = 0; p < size; p++) { // Current pivot.
        // Normalise row.
        double coeff = A[p][p];
        for (int j = p; j < size; j++) {
            A[p][j] /= coeff;
        }
        b[p] /= coeff;
        //printMatrix(A); printVector(b); cout << endl;

        for (int i = p+1; i < size; ++i) {  // Variable to eliminate.
            double coeff = A[i][p] / A[p][p];
            //cout << coeff << endl;
            for (int k = p; k < size; k++) { //
                A[i][k] -= A[p][k] * coeff;
            }
            b[i] -= b[p] * coeff;
            //printMatrix(A); printVector(b); cout << endl;
        }
    }

    // Eliminate upper-triangular part.
    for (int p = size-1; p >= 0; p--) {
        for (int i = p-1; i >= 0; i--) {
            double coeff = A[i][p] / A[p][p];
            A[i][p] -= A[p][p] * coeff;
            b[i]    -= b[p] * coeff;
            //printMatrix(A); printVector(b); cout << endl;
        }
    }

    return b;
}

template<typename T> vector<T> solve(vector<vector<T> > A, vector<vector<T> > B)
{
    vector<T> x;
    if (B.size() == 1) {
        x = solve(A, B[0]);
    }
    return x;
}

template<typename T> vector<T> multiply(vector<vector<T> > A, vector<T> b)
{
    vector<T> product(A.size(), 0.0);

    for (int i = 0; i < A.size(); ++i) {
        product[i] = inner_product(A[i].begin(), A[i].end(), b.begin(), 0.0);
    }

    return product;
}

template<typename T> vector<vector<T> > multiply(vector<vector<T> > A, vector<vector<T> > B)
{
    vector<vector<T> > B_transpose = transpose(B);
    vector<vector<T> > product_transpose(B[0].size(), vector<T> (A.size(), 0.0));

    for (int j = 0; j < B[0].size(); ++j) {
        product_transpose[j] = multiply(A, B_transpose[j]);
    }
    return transpose( product_transpose );
}

template<typename T> vector<T> vec(vector<vector<T> > X)
{
    int rows = X.size();
    int cols = X[0].size();
    vector<T> v(rows*cols, 0.0);

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            v[j*rows + i] = X[i][j];
        }
    }

    return v;
}

template<typename T> vector<vector<T> > elementwise_multiply(vector<vector<T> > A, vector<vector<T> > B)
{
    vector<vector<T> > product = A;

    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j) {
            product[i][j] = A[i][j] * B[i][j];
        }
    }

    return product;
}

template<typename T> vector<vector<T> > elementwise_power(vector<vector<T> > &A, int exponent)
{
    vector<vector<T> > power = A;

    for (int i = 1; i < exponent; ++i) {
        power = elementwise_multiply(power, A);
    }

    return power;
}

template<typename T> vector<vector<T> > column_concatenate(vector<vector<T> > A, vector<vector<T> > B)
{
    vector<vector<T> > A_t = transpose(A);
    vector<vector<T> > B_t = transpose(B);
    vector<vector<T> > newMatrix(A_t.size()+B_t.size(), vector<T> (A.size(), 0.0));

    for (int i = 0; i < A_t.size(); ++i) {
        newMatrix[i] = A_t[i];
    }
    for (int i = 0; i < B_t.size(); ++i) {
        newMatrix[ i + A_t.size() ] = B_t[i];
    }

    return transpose(newMatrix);
}

template<typename T> vector<vector<T> > add(vector<vector<T> > A, vector<vector<T> > B)
{
    vector<vector<T> > sum = A;

    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j) {
            sum[i][j] += B[i][j];
        }
    }

    return sum;
}

template<typename T> vector<vector<T> > diag(vector<T> a)
{
    vector<vector<T> > diagonal(a.size(), vector<T> (a.size(), 0.0));

    for (int i = 0; i < a.size(); ++i) {
        diagonal[i][i] = a[i];
    }

    return diagonal;
}

template<typename T> vector<T> diag(vector<vector<T> > a)
{
    vector<T> diagonal(a.size(), 0.0);

    for (int i = 0; i < a.size(); ++i) {
        diagonal[i] = a[i][i];
    }

    return diagonal;
}

template<typename T> vector<vector<T> > polynomialFeatures(vector<vector<T> > X)
{
    int p = X[0].size();
    int N = X.size();
    vector<vector<double> > ones( 1, vector<double> (N,1) );
    vector<vector<T> > Phi = transpose(ones);

    Phi = column_concatenate(Phi, X);
    // printMatrix(Phi);
    Phi = column_concatenate(Phi, elementwise_power(X,2));
    // printMatrix(Phi);
    for (int i = 0; i < p; ++i) {
        for (int j = i+1; j < p; ++j) {
            Phi = column_concatenate(Phi, elementwise_multiply(submatrix(X,0,N-1,i,i), submatrix(X,0,N-1,j,j)) );
            // printMatrix(Phi);
        }
    }

    return Phi;
}

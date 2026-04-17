#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int rows;
    int cols;
    double* data;
} Matrix;

typedef struct {
    int size;
    double* data;
} Vector;

Vector FirstVec, SecondVec;
Matrix FirstMtx, SecondMtx;

void printMatrix(Matrix mat) {
    for (int i=0; i < mat.rows; i++) {
        for (int j=0; j < mat.cols; j++) {
            printf("%0.2lf ", mat.data[i * mat.cols + j]);
        }
        printf("\n");
    }
}

void printVector(Vector vec) {
    for (int i=0; i < vec.size; i++) {
        printf("%0.2lf ", vec.data[i]);
    }
    printf("\n");
}

Matrix allocMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double *)malloc(rows * cols * sizeof(double));
    return mat;
}

Matrix createMatrix(int rows, int cols) {
    Matrix mat = allocMatrix(rows, cols);
    for (int i=0; i < mat.rows; i++) {
        for (int j=0; j < mat.cols; j++) {
            printf("The value of row %d, col %d: ", i+1, j+1);
            double temp;
            scanf("%lf", &temp);
            mat.data[i * cols + j] = temp;
        }
    }
    printf("New Matrix of size %d*%d:\n", mat.rows, mat.cols);
    printMatrix(mat);
    return mat;
}

Vector allocVector(int VecSize) {
    Vector Vec;
    Vec.size = VecSize;
    Vec.data = (double*)malloc(VecSize * sizeof(double));

    return Vec;
}

Vector createVector(int VecSize) {
    Vector Vec = allocVector(VecSize);

    for (int i=0; i < VecSize; i++) {
        printf("Provide contents for term %d: ", i+1);
        scanf("%lf", &Vec.data[i]);
    }

    printf("New Vector:\n");
    printVector(Vec);
    return Vec;
}

Vector moveVec(Vector Src, Vector Counter){
    Vector TrueBase;
    if (Src.size < Counter.size) {
        TrueBase = allocVector(Counter.size);
    } else {
        TrueBase = allocVector(Src.size);
    }

    for (int i = 0; i < TrueBase.size; i++){
        if (!Src.data[i]) {
            TrueBase.data[i] = 0;
        }

        TrueBase.data[i] = Src.data[i];
    }

    return TrueBase;
}

void addVector(Vector base, Vector additive){
    Vector TrueBase = moveVec(base, additive);

    for (int i = 0; i < additive.size; i++){
        TrueBase.data[i] += additive.data[i];
    }

    printf("The resulting vector is:\n");
    printVector(TrueBase);
}

void subVector(Vector base, Vector subtractor){
    Vector TrueBase = moveVec(base, subtractor);

    for (int i = 0; i < subtractor.size; i++){
        TrueBase.data[i] -= subtractor.data[i];
    }

    printf("The resulting vector is:\n");
    printVector(TrueBase);
}

void dotVector(Vector AVec, Vector BVec){
    double Result = 0;
    if (AVec.size != BVec.size) {
        printf("Both vector must be the same dimension");
        exit(1);
    }

    for (int i = 0; i < AVec.size ; i++) {
        Result += (AVec.data[i]*BVec.data[i]);
    }

    printf("The Dot product is: %0.2lf", Result);
}

void crossVector(Vector AVec, Vector BVec){
    if (AVec.size != 3 && BVec.size != 3) {
        printf("Both vector must be three dimensional in order to find their cross product");
        exit(1);
    }

    Vector NewVec = allocVector(3);
    NewVec.data[0] = AVec.data[1] * BVec.data[2] - AVec.data[2] * BVec.data[1];
    NewVec.data[1] = -(AVec.data[0] * BVec.data[2] - AVec.data[2] * BVec.data[0]);
    NewVec.data[2] = AVec.data[0] * BVec.data[1] - AVec.data[1] * BVec.data[0];

    printf("\nThe Cross product is: ");
    printVector(NewVec);
}

void promptVector(){
        int Option;

        printf("Please input of what dimension the first vector should be: ");
        scanf("%d", &Option);

        if (Option <= 0) {
            printf("Invalid vector size. Exiting program.\n");
            exit(1);
        }

        FirstVec = createVector(Option);

        printf("\nPlease input of what dimension the second vector should be: ");
        scanf("%d", &Option);
        if (Option <= 0) {
            printf("Invalid vector size. Exiting program.\n");
            exit(1);
        }

        SecondVec = createVector(Option);
}

void addMatrix(Matrix base, Matrix Additive){
    if (base.rows != Additive.rows || base.cols != Additive.cols) {
        printf("Matrix is not the same size, tried addition with size: %d*%d and %d*%d", base.rows, base.cols, Additive.rows, Additive.cols);
        exit(1);
    }

    for (int i = 0; i < base.rows; i++) {
        for (int j = 0; j < base.cols; j++) {
            base.data[i * base.cols + j] = base.data[i * base.cols + j] + Additive.data[i * Additive.cols + j];
        }
    }

    printf("Result of addition is:\n");
    printMatrix(base);
}

void subMatrix(Matrix base, Matrix subtractor){
    if (base.rows != subtractor.rows || base.cols != subtractor.cols) {
        printf("Matrix is not the same size, tried subtraction with size: %d*%d and %d*%d", base.rows, base.cols, subtractor.rows, subtractor.cols);
        exit(1);
    }

    for (int i = 0; i < base.rows; i++) {
        for (int j = 0; j < base.cols; j++) {
            base.data[i * base.cols + j] = base.data[i * base.cols + j] - subtractor.data[i * subtractor.cols + j];
        }
    }

    printf("Result of subtraction is:\n");
    printMatrix(base);
}

void mulMatrix(Matrix base, Matrix multiplier) {
    if (base.cols != multiplier.rows) {
        printf("Collumn of first matrix must be the same as row of second matrix");
        exit(1);
    }

    Matrix Result = allocMatrix(base.rows, multiplier.cols);

    for (int i = 0; i < base.rows; i++) {
        for (int j = 0; j < base.cols; j++) {
            for (int k = 0; k < base.cols; k++) {
                Result.data[i * Result.cols + j] = Result.data[i * Result.cols + j] + base.data[i * base.cols + k] * multiplier.data[k * multiplier.cols + j];
            }
        }
    }

    printf("Result of multiplication is:\n");
    printMatrix(Result);
}

void transposeMatrix(Matrix mat){
    Matrix Result = allocMatrix(mat.cols, mat.rows);

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            Result.data[j * mat.rows + i] = mat.data[i * mat.cols + j];
        }
    }
    printf("Result of transpose is:\n");
    printMatrix(Result);
}

Matrix returnIdentityMatrix(int size){
    Matrix Identity = allocMatrix(size, size);
    for (int i = 0; i < Identity.rows; i++) {
        for (int j = 0; j < Identity.cols; j++) {
            if (i == j) {
            Identity.data[i * Identity.cols + j] = 1;
            } else {
                Identity.data[i * Identity.cols + j] = 0;
            }
        }
    }
    return Identity;
}

void InnerproductMatrix(Matrix FirstMat, Matrix SecondMat) {
    if (FirstMat.rows != SecondMat.rows || FirstMat.cols != SecondMat.cols) {
        printf("Matrix is not the same size, tried addition with size: %d*%d and %d*%d", FirstMat.rows, FirstMat.cols, SecondMat.rows, SecondMat.cols);
        exit(1);
    }
    double result = 0;
    for (int i = 0; i < FirstMat.rows; i++) {
        for (int j = 0; j < FirstMat.cols; j++) {
            result += FirstMat.data[i * FirstMat.cols + j] * SecondMat.data[i * SecondMat.cols + j];
        }
    }
    printf("Inner product is: %0.2lf", result);
}

void freeMatrix(Matrix *m) {
    free(m->data);
    m->data = NULL;
    m->rows = m->cols = 0;
}

// Helper: swap two rows in a matrix (given row indices)
void swapRows(Matrix *m, int row1, int row2) {
    if (row1 == row2) return;
    double *temp = (double*)malloc(m->cols * sizeof(double));
    if (!temp) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    // copy row1 to temp
    for (int j = 0; j < m->cols; j++) {
        temp[j] = m->data[row1 * m->cols + j];
    }
    // copy row2 to row1
    for (int j = 0; j < m->cols; j++) {
        m->data[row1 * m->cols + j] = m->data[row2 * m->cols + j];
    }
    // copy temp to row2
    for (int j = 0; j < m->cols; j++) {
        m->data[row2 * m->cols + j] = temp[j];
    }
    free(temp);
}

// Gauss-Jordan elimination to find inverse of a square matrix.
// Returns a new matrix (the inverse). The original matrix 'mat' is not modified.
void invMatrix(Matrix mat) {
    if (mat.rows != mat.cols) {
        printf("Error: cannot invert a non-square matrix (%d x %d)\n", mat.rows, mat.cols);
        exit(1);
    }
    int n = mat.rows;
    
    Matrix work = allocMatrix(n, n);
    Matrix inv = returnIdentityMatrix(n);
    
    for (int i = 0; i < n * n; i++) {
        work.data[i] = mat.data[i];
    }
    
    for (int col = 0; col < n; col++) {
        int pivotRow = -1;
        for (int row = col; row < n; row++) {
            if (fabs(work.data[row * n + col]) > 1e-12) {
                pivotRow = row;
                break;
            }
        }
        if (pivotRow == -1) {
            printf("Matrix is singular, cannot invert.\n");
            exit(1);
        }
        
        if (pivotRow != col) {
            swapRows(&work, col, pivotRow);
            swapRows(&inv, col, pivotRow);
        }
        
        double pivot = work.data[col * n + col];
        if (fabs(pivot) < 1e-12) {  // safety check
            printf("Numerical zero pivot, cannot invert.\n");
            exit(1);
        }
        for (int j = 0; j < n; j++) {
            work.data[col * n + j] /= pivot;
            inv.data[col * n + j] /= pivot;
        }
        
        for (int row = 0; row < n; row++) {
            if (row == col) continue;
            double factor = work.data[row * n + col];
            if (fabs(factor) < 1e-12) continue;  // already zero
            for (int j = 0; j < n; j++) {
                work.data[row * n + j] -= factor * work.data[col * n + j];
                inv.data[row * n + j] -= factor * inv.data[col * n + j];
            }
        }
    }
    printf("The inverse of the matrix is:\n");
    printMatrix(inv);
}

void promptMatrix(int numMtx){
        int row, col;
        printf("Please input size of row for the matrix: ");
        scanf("%d", &row);

        if (row <= 0) {
            printf("Invalid vector size. Exiting program.\n");
            exit(1);
        }

        printf("Please input size of col for the matrix: ");
        scanf("%d", &col);

        if (row <= 0) {
            printf("Invalid vector size. Exiting program.\n");
            exit(1);
        }

        FirstMtx = createMatrix(row, col);
        if (numMtx == 2) SecondMtx = createMatrix(row, col);
}

int main()
{
    printf("Select an option:\n0. Exit\n1. Matrix\n2. Vector\n");
    int Option;
    scanf("%d", &Option);

    switch (Option) 
    {
    case 1:
        printf("Select an Operation:\n0. Exit\n1. Addition\n2. Subtraction\n3. Transpose\n4. Multiply\n5. Inverse\n6. Inner Product\n");
        scanf("%d", &Option);

        switch (Option) {
        case 1:
            printf("\nAddition selected\n");
            promptMatrix(2);
            addMatrix(FirstMtx, SecondMtx);
            break;
        case 2:
            printf("\nSubtraction selected\n");
            promptMatrix(2);
            subMatrix(FirstMtx, SecondMtx);
            break;
        case 3:
            printf("\nTranspose selected\n");
            promptMatrix(1);
            transposeMatrix(FirstMtx);
            break;
        case 4:
            printf("\nMultiplication selected\n");
            promptMatrix(2);
            mulMatrix(FirstMtx, SecondMtx);
            break;
        case 5:
            printf("\nInverse selected\n");
            promptMatrix(1);
            invMatrix(FirstMtx);
            break;
        case 6:
            printf("\nInner product selected\n");
            promptMatrix(2);
            InnerproductMatrix(FirstMtx, SecondMtx);
            break;
        }
        break;
    case 2:
        promptVector();

        printf("Select an Operation:\n0. Exit\n1. Addition\n2. Subtraction\n3. Dot Product\n4. Cross Product\n");
        scanf("%d", &Option);

        switch (Option)
        {
        case 1:
            printf("\nAddition selected\n");
            addVector(FirstVec, SecondVec);
            break;
        case 2:
            printf("\nSubtraction selected\n");
            subVector(FirstVec, SecondVec);
            break;
        case 3:
            printf("\nDot product selected\n");
            dotVector(FirstVec, SecondVec);
            break;
        case 4:
            printf("\nCross product selected\n");
            crossVector(FirstVec, SecondVec);
        default:
            break;
        }

        break;
    default:
        printf("Invalid option selected.\n");
        printf("Exiting program.\n");
        return 1;
    }

    return 0;
}
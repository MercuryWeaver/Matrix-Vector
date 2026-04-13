#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    int rows;
    int cols;
    double* data;
} Matrix;

typedef struct {
    int size;
    double* data;
} Vector;

typedef struct {
    Matrix *items;
    size_t count;
    size_t capacity;
} MatrixList;

typedef struct {
    Vector *items;
    size_t count;
    size_t capacity;
} VectorList;

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

Matrix createMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double*)malloc(rows * cols * sizeof(double));
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            mat.data[i * cols + j] = 0.0; // Initialize to zero
        }
    }
    return mat;
}

void createVector(int VecSize, VectorList* Vectors) {
    Vector Vec;
    Vec.size = VecSize;
    Vec.data = (double*)malloc(VecSize * sizeof(double));
    for (int i=0; i < VecSize; i++) {
        printf("Provide contents for term %d: ", i+1);
        scanf("%lf", &Vec.data[i]);
    }

    printf("New Vector:\n");
    printVector(Vec);
    if (Vectors->count >= Vectors->capacity) {
        if (Vectors->capacity == 0) {
            Vectors->capacity = 1;
            Vectors->items = (Vector*)malloc(Vectors->capacity * sizeof(Vector));
        } else {
            Vectors->capacity += 1;
            Vectors->items = (Vector*)realloc(Vectors->items, Vectors->capacity * sizeof(Vector));
        }
        Vectors->items[Vectors->count] = Vec;
        Vectors->count++;
    }
}

int main()
{
    MatrixList Matrices = {0};
    VectorList Vectors = {0};

    while (true)
    {
        system("cls");
        printf("Select an option:\n0. Exit\n1. Create Matrix(WIP)\n2. Create Vector\n3. Printing\n4.Operations\n");
        int Option;
        scanf("%d", &Option);
        switch (Option) 
        {
        case 1:
            //unfinished
            createMatrix(3, 3);
            system("cls");
            break;
        case 2:
            system("cls");
            printf("Please input of what dimension the vector should be: ");
            scanf("%d", &Option); // Read user option using

            if (Option <= 0) {
                printf("Invalid vector size. Exiting program.\n");
                return 1;
            }

            system("cls");
            createVector(Option, &Vectors);
            printf("Press any key to continue...");
            getch();
            break;
        case 3:
            system("cls");
            printf("Select an option:\n1. Matrix(WIP)\n2. Vector\n");
            scanf("%d", &Option);
            switch (Option)
            {
            case 1:
                system("cls");
                if (Vectors.count < 1) {
                    printf("No Vectors Found");
                    printf("Press any key to continue...");
                    break;
                }
                for (int i=0; i < Vectors.count; i++) {
                    printVector(Vectors.items[i]);
                }

                printf("Press any key to continue...");
                break;
            default:
                break;
            }
            getch();
            break;
        default:
            printf("Invalid option selected.\n");
            printf("Exiting program.\n");
            return 1;
        }
    }
    
    
    
    return 0;
}
#include "iostream"
#define  N 8

void setQueen(int8_t** desk,int8_t i, int8_t j){
    for (int k = 0; k < N; ++k) {
        ++desk[k][j];
        ++desk[i][k];
        int foo = j - i + k;
        if (foo >= 0 && foo <8)
            ++desk[k][foo];
        foo = j + i - k;
        if (foo >= 0 && foo <8)
            ++desk[k][foo];
    }
    desk[i][j] = -1;
}

void resetQueen(int8_t** desk,int8_t i, int8_t j){

    for (int k = 0; k < N; ++k) {
        --desk[k][j];
        --desk[i][k];
        int foo = j - i + k;
        if (foo >= 0 && foo <8)
            --desk[k][foo];
        foo = j + i - k;
        if (foo >= 0 && foo <8)
            --desk[k][foo];
    }
    desk[i][j] = 0;
}

bool TryQueen(int8_t** desk,int8_t i)
{
    bool result = false;
    for (size_t j = 0; j < N; ++j) {
        if(desk[i][j] == 0){
            setQueen(desk,i,j);
            if (i == 7) result = true;
            else{
                if(!(result = TryQueen(desk,i+1)))
                    resetQueen(desk,i,j);
            }
        }
        if (result)
            break;
    }
    return result;
}

int main(int argv,char** argc)
{
    int8_t** desk = (int8_t**)malloc(N * sizeof(int8_t*));
    for (size_t i = 0; i < N; i++)
        desk[i] = (int8_t*)malloc(N * sizeof(int8_t));

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            desk[i][j] = 0;
        }
    }

    TryQueen(desk,0);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (desk[i][j] == -1)
                std::cout << " x ";
            else
                std::cout << " . ";
        }
        std::cout << std::endl;
    }


    for (size_t i = 0; i < N; i++)
        delete [] desk[i];
    delete [] desk;
    return 0;
}



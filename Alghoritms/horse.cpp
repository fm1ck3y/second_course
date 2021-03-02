#include <iostream>

#define COUNT_MOVE 8
constexpr int8_t horse_moves[8][2] = {
        {1,-2} , {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1},{-2,-1}, {-1,-2}
};

bool dfs(uint8_t** desk,uint8_t x, uint8_t y, uint8_t N, uint8_t it = 0)
{
    if(x<0 || x >= N || y < 0 || y >= N)
        return false;
    if (desk[x][y] != 0)
        return false;

    it++;
    desk[x][y] = it;

    if (it == N*N)
        return true;

    for (size_t i = 0; i < COUNT_MOVE; ++i){
        if(dfs(desk,x+horse_moves[i][0], y + horse_moves[i][1], N ,it))
            return true;
    }

    it--;
    desk[x][y] = 0;
    return false;
}

void print_desk(uint8_t** array, uint8_t N, uint8_t M)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            std::cout << (unsigned int)array[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*
int main(int argv,char** argc)
{
    unsigned int N, x, y;
    std:: cout << "Enter N: ";
    std:: cin >> N;

    std:: cout << "Enter x,y: ";
    std:: cin >> x >> y;
    uint8_t** desk = (uint8_t**)malloc(N * sizeof(uint8_t*));
    for (size_t i = 0; i < N; i++)
        desk[i] = (uint8_t*)malloc(N * sizeof(uint8_t));

    for (size_t i = 0; i <N; ++i)
        for (size_t j = 0; j < N; ++j)
            desk[i][j] = 0;

    dfs(desk,x,y, N );
    print_desk(desk,N,N);
    for (size_t i = 0; i < N; i++)
        delete [] desk[i];
    delete [] desk;
    return 0;
}*/
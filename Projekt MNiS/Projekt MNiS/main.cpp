#include <iostream>
#include <vector>

struct point
{
    int x, y;
    float g, h, f;
};

void print(std::vector<std::vector<int>> mapa)
{
    for (int i = 0; i < mapa.size() + 4; i++)
    {
        std::cout << (char)254u;
    }
    std::cout << std::endl;

    for (auto y : mapa)
    {
        std::cout << (char)254u;
        for (auto x : y)
        {
            if (x == 0)
            {
                std::cout << " ";
            }
            else if (x == 1)
            {
                std::cout << "\033[34m" << (char)254u << "\033[0m";
            }
            else if (x == 2)
            {
                std::cout << "\033[32m" << (char)254u << "\033[0m";
            }
            else if (x == 3)
            {
                std::cout << "\033[31m" << (char)254u << "\033[0m";
            }
        }
        std::cout << (char)254u;
        std::cout << "\n";
    }

    for (int i = 0; i < mapa.size() + 4; i++)
    {
        std::cout << (char)254u;
    }
}


void a_star (std::vector<std::vector<int>>& mapa, std::pair<int, int> start, std::pair<int, int> end)
{
    mapa[2][2] = 2;
    print(mapa);
}

int main()
{
    // 0 - puste, 1 - sciana, 2 - start, 3 - koniec
    std::vector<std::vector<int>> mapa = {
        {0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0},
        {0,2,0,1,0,3,0},
        {0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0},
    };

    print(mapa);
    a_star(mapa, { 1,2 }, { 5,2 });
}
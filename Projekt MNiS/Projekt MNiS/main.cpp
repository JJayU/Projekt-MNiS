#include <iostream>
#include <vector>
#include <set>
#include <Windows.h>

typedef std::vector<std::vector<int>> zmapa;

struct point
{
    int x, y;
    float g, h, f;
    std::pair<int, int> parent;
};

void print(zmapa mapa)
{
    //system("cls");

    for (size_t i = 0; i < mapa.size() + 4; i++)
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
            else if (x == 4)
            {
                std::cout << "\033[33m" << (char)254u << "\033[0m";
            }
        }
        std::cout << (char)254u;
        std::cout << "\n";
    }

    for (size_t i = 0; i < mapa.size() + 4; i++)
    {
        std::cout << (char)254u;
    }
}


void a_star (zmapa& mapa, std::pair<int, int> start, std::pair<int, int> end)
{
    size_t sizex = mapa[0].size();
    size_t sizey = mapa.size();

    std::vector<std::vector<point>> punkty;

    int a = 0;
    int b = 0;

    for (auto y : mapa)
    {
        std::vector<point> tvect;
        for (auto x : y)
        {
            point tpoint;
            tpoint.g = -1;
            tpoint.h = -1;
            tpoint.f = -1;
            tpoint.parent = { -1,-1 };
            tpoint.x = b;
            tpoint.y = a;

            tvect.push_back(tpoint);

            b++;
        }
        punkty.push_back(tvect);
        a++;
    }

    punkty[start.first][start.second].g = 0;
    punkty[start.first][start.second].h = 0;
    punkty[start.first][start.second].f = 0;

    std::set<std::pair<int, int>> openList;
    openList.insert({ start.first, start.second });

    bool routeFound = false;

    while (!routeFound || !openList.empty())
    {
        std::pair<int, int> tpunkty = *openList.begin();
        openList.erase(openList.begin());

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    int newy = tpunkty.first + i;
                    int newx = tpunkty.second + j;

                    if (newy == end.first && newx == end.second)
                    {
                        std::cout << "Znaleziono droge!\n";
                        return;
                    }

                    if (newy >= 0 && newx >= 0 && newy < sizey && newx < sizex && mapa[newy][newx] != 1 && mapa[newy][newx] != 2 && mapa[newy][newx] != 3)
                    {
                        mapa[newy][newx] = 4;
                        

                        //   ---odleglosc do punktu docelowego---

                        int x_difference_between_node_end = (end.first) - (newx);
                        //std::cout << x_difference_between_node_end << "\n";
                        int y_difference_between_node_end = (end.second) - (newy);
                        //std::cout << y_difference_between_node_end << "\n";
                        double path = (x_difference_between_node_end * x_difference_between_node_end) + (y_difference_between_node_end * y_difference_between_node_end);
                        double path2 = sqrt(path);
                        //std::cout << path2 << "\n";


                        //   ---odleglosc od punktu poczatkowego---
                        float g;
                        if (newy == tpunkty.first) {
                            g = abs(newx - tpunkty.second);
                            //std::cout << "p1 : " << p1;
                        }
                        else if (newx == tpunkty.second) {
                            g = abs(newy - tpunkty.first);
                            //std::cout << "p2 : " << p2;
                        }
                        else {
                            int x = (newx) - (tpunkty.second);
                            int y = (newy) - (tpunkty.first);
                            double path = (x * x) + (y * y);
                            g = sqrt(path);
                            //std::cout << "path_sqrt : " << path_sqrt << "\n";
                        }
                        g = g + punkty[tpunkty.first][tpunkty.second].g;

        

                        punkty[newy][newx].h = path2;
                        if (punkty[newy][newx].g != 1 || punkty[newy][newx].g < g)
                        {
                            punkty[newy][newx].g = g;
                        }  
                        if (punkty[newy][newx].f != 1 || path2 + g < punkty[newy][newx].f)
                        {
                            punkty[newy][newx].f = punkty[newy][newx].h + punkty[newy][newx].g;
                            openList.insert({ newy, newx });
                        }

                        std::cout << "\n---\n" << path2 << "\n" << g << "\n" << punkty[newy][newx].h + punkty[newy][newx].g << "\n";
                    }
                }
            }
        }

        
        print(mapa);
        //system("pause");
        //Sleep(10000);
        Sleep(100);
        system("cls");
    }
}

int main()
{
    // 0 - puste, 1 - sciana, 2 - start, 3 - koniec, 4 - pomaranczowy
    std::vector<std::vector<int>> mapa = {
        {0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0},
        {0,2,0,1,0,3,0},
        {0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0},
    };

    a_star(mapa, { 2,1 }, { 5,2 });
}
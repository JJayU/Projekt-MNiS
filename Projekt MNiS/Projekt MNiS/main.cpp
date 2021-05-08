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
            else if (x == 5)
            {
                std::cout << "\033[35m" << (char)254u << "\033[0m";
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
    const int sizex = mapa[0].size();
    const int sizey = mapa.size();

    std::vector<std::vector<point>> punkty;
    std::vector<std::vector<bool>> closedList;

    int a = 0;
    int b = 0;

    for (auto y : mapa)
    {
        std::vector<point> tvect;
        std::vector<bool> tbool;
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
            tbool.push_back(0);

            b++;
        }
        punkty.push_back(tvect);
        closedList.push_back(tbool);
        a++;
    }

    punkty[start.first][start.second].g = 0;
    punkty[start.first][start.second].h = -1;
    punkty[start.first][start.second].f = -1;

    std::set<std::pair<int, int>> openList;
    openList.insert({ start.first, start.second });

    bool routeFound = false;

    while (!routeFound || !openList.empty())
    {
        std::pair<int, int> tpunkty = *openList.begin();
        openList.erase(openList.begin());
        closedList[tpunkty.first][tpunkty.second] = 1;

        if (tpunkty != start)
        {
            mapa[tpunkty.first][tpunkty.second] = 4;
        }

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
                            int x = (newx)-(tpunkty.second);
                            int y = (newy)-(tpunkty.first);
                            double path = (x * x) + (y * y);
                            g = sqrt(path);
                            //std::cout << "path_sqrt : " << path_sqrt << "\n";
                        }
                        g = g + punkty[tpunkty.first][tpunkty.second].g;

                        punkty[newy][newx].parent = { tpunkty.first, tpunkty.second };

                        int akty = end.first;
                        int aktx = end.second;

                        while (akty != start.first || aktx != start.second)
                        {
                            if(akty !=  end.first || aktx != end.second)
                                mapa[akty][aktx] = 5;

                            int newnewy = punkty[akty][aktx].parent.first;
                            int newnewx = punkty[akty][aktx].parent.second;

                            aktx = newnewx;
                            akty = newnewy;
                        }

                        std::cout << g << "\n";

                        print(mapa);
                        system("pause");
                        return;
                    }


                    if (newy >= 0 && newx >= 0 && newy < sizey && newx < sizex && mapa[newy][newx] != 1 && mapa[newy][newx] != 2 && mapa[newy][newx] != 3)
                    {
                        mapa[newy][newx] = 4;
                        

                        //   ---odleglosc do punktu docelowego---

                        int x_difference_between_node_end = (end.second) - (newx);
                        //std::cout << x_difference_between_node_end << "\n";
                        int y_difference_between_node_end = (end.first) - (newy);
                        //std::cout << y_difference_between_node_end << "\n";
                        double path = (x_difference_between_node_end * x_difference_between_node_end) + (y_difference_between_node_end * y_difference_between_node_end);
                        double h = sqrt(path);
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
                        float s = h + g;
        

                        punkty[newy][newx].h = h;

                        if (punkty[newy][newx].g == -1 || g < punkty[newy][newx].g)
                        {
                            punkty[newy][newx].g = g;
                        }  
                        if (punkty[newy][newx].f == -1 || s < punkty[newy][newx].f)
                        {
                            punkty[newy][newx].f = punkty[newy][newx].h + punkty[newy][newx].g;
                            closedList[newy][newx] = 0;
                            punkty[newy][newx].parent = { tpunkty.first, tpunkty.second };
                        }

                        //std::cout << "\n---\n" << h << "\n" << g << "\n" << punkty[newy][newx].h + punkty[newy][newx].g << "\n";
                    }
                }
            }
        }

        float minf = 99999.0;
        int nowyx = -1;
        int nowyy = -1;
        for (int y = 0; y < sizey; y++)
        {
            for (int x = 0; x < sizex; x++)
            {
                if (punkty[y][x].f < minf && punkty[y][x].f != -1 && closedList[y][x] != 1)
                {
                    minf = punkty[y][x].f;
                    nowyx = x;
                    nowyy = y;
                }
            }
        }

        openList.insert({ nowyy, nowyx });
        
        print(mapa);
        //system("pause");
        //Sleep(10000);
        Sleep(200);
        system("cls");
    }
}

int main()
{
    // 0 - puste, 1 - sciana, 2 - start, 3 - koniec, 4 - pomaranczowy
    std::vector<std::vector<int>> mapa = {
        {2,1,0,1,0,0,0},
        {0,1,0,0,0,1,0},
        {0,1,0,1,0,1,0},
        {0,1,0,1,1,1,0},
        {0,0,0,1,3,0,0},
    };

    a_star(mapa, { 0,0 }, { 4,4 });
}
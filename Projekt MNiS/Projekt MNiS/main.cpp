#include <iostream>
#include <vector>
#include <set>
#include <Windows.h>

// Definicja typu, jakim reprezentowana jest mapa
typedef std::vector<std::vector<int>> zmapa;

// Struktura pojedynczego punktu na mapie
struct point
{
    int x, y;                       // koordynaty
    float g, h, f;                  // odleglosci g - od startu, h - do mety, f - suma g i h
    std::pair<int, int> parent;     // lokalizacja rodzica
};

// Funkcja wyswietlajaca mape na ekranie
void print(zmapa mapa)
{
    //system("cls");

    // Rysowanie gornej ramki
    for (size_t i = 0; i < mapa.size() + 2; i++)
    {
        std::cout << (char)254u;
    }
    std::cout << std::endl;

    for (auto y : mapa)
    {
        // Rysowanie lewej ramki

        std::cout << (char)254u;
        // Rysowanie zawartosci
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

        //Rysowanie prawej ramki
        std::cout << (char)254u;
        std::cout << "\n";
    }

    // Rysowanie dolnej ramki
    for (size_t i = 0; i < mapa.size() + 2; i++)
    {
        std::cout << (char)254u;
    }
}

void a_star (zmapa& mapa, std::pair<int, int> start, std::pair<int, int> end)
{
    // Pobranie wymiarow mapy
    const int sizex = mapa[0].size();
    const int sizey = mapa.size();

    // Utworzenie tablicy punktow na podstawie mapy i stworzenie tablicy
    std::vector<std::vector<point>> punkty;
    std::vector<std::vector<bool>> closedList;

    //
    // Wypelnienie tablicy "punkty" pustymi danymi oraz wprowadzenie danych punktu poczatkowego
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
    //
    
    // Utworzenie stosu punktow do zbadania
    std::set<std::pair<int, int>> openList;
    // Dodanie punktu startowego do ww. stosu
    openList.insert({ start.first, start.second });

    // Glowna petla algorytmu, wykonuje sie dopoki lista punktow do zbadania nie jest pusta
    while (!openList.empty())
    {
        //Pobranie lokalizacji aktualnie badanego punktu
        std::pair<int, int> tpunkty = *openList.begin();

        //Sprawdzenie czy ww. lokalizacja jest prawidlowa, jezeli nie - droga do punktu docelowego nie zostala znaleziona
        if (tpunkty.first < 0 || tpunkty.second < 0)
        {
            break;
        }

        // Usuniecie aktualnie badanego punktu z listy punktow do zbadania
        openList.erase(openList.begin());

        // Oznaczenie aktualnie badanego punktu jako punkt zbadany
        closedList[tpunkty.first][tpunkty.second] = 1;

        // Zaznaczenie aktualnie badanego punktu kolorem pomaranczowym, o ile nie jest on meta
        if (tpunkty != start)
        {
            mapa[tpunkty.first][tpunkty.second] = 4;
        }

        // Badanie wszystkich punktow przylegajacych do badanego punktu matki
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // Zabezpieczenie przed zbadaniem "samego siebie"
                if (i != 0 || j != 0)
                {
                    // Tymczasowe zmienne przechowujace lokalizacje aktualnie badanego punktu
                    int newy = tpunkty.first + i;
                    int newx = tpunkty.second + j;

                    // Jezeli nastepny punkt jest meta, zakoncz wykonywanie algorytmu i narysuj sciezke do startu
                    if (newy == end.first && newx == end.second)
                    {
                        // Wyznaczenie dlugosci sciezki od startu do mety
                        float g;
                        if (newy == tpunkty.first) 
                        {
                            g = abs(newx - tpunkty.second);
                        }
                        else if (newx == tpunkty.second) 
                        {
                            g = abs(newy - tpunkty.first);
                        }
                        else 
                        {
                            int x = (newx)-(tpunkty.second);
                            int y = (newy)-(tpunkty.first);
                            double path = (x * x) + (y * y);
                            g = sqrt(path);
                        }
                        g = g + punkty[tpunkty.first][tpunkty.second].g;

                        // Przypisanie mecie jej rodzica - punktu z ktorego "przychodzi" najkrotsza droga od startu
                        punkty[newy][newx].parent = { tpunkty.first, tpunkty.second };

                        // Rysowanie na mapie najkrotszej sciezki
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

                            print(mapa);
                            system("cls");
                        }

                        // Zakonczenie dzialania algorytmu
                        std::cout << "Znaleziono droge!\n";
                        std::cout << "Dlugosc: " << g << "\n";
                        print(mapa);
                        system("pause");
                        return;
                    }

                    // Jezeli nastepny punkt nie jest meta, kontynuuj dzialanie algorytmu
                    if (newy >= 0 && newx >= 0 && newy < sizey && newx < sizex && mapa[newy][newx] != 1 && mapa[newy][newx] != 2 && mapa[newy][newx] != 3)
                    {
                        // Zaznaczenie aktualnie badanego punktu kolorem pomaranczowym
                        mapa[newy][newx] = 4;
                        

                        // Wyznaczenie odleglosci od aktualnie badanego punktu do punktu koncowego w linii prostej
                        int x_difference_between_node_end = (end.second) - (newx);
                        int y_difference_between_node_end = (end.first) - (newy);
                        double path = (x_difference_between_node_end * x_difference_between_node_end) + (y_difference_between_node_end * y_difference_between_node_end);
                        double h = sqrt(path);

                        // Wyznaczenie odleglosci od aktualnie badanego punktu do punktu startowego
                        float g;
                        if (newy == tpunkty.first) 
                        {
                            g = abs(newx - tpunkty.second);
                        }
                        else if (newx == tpunkty.second) 
                        {
                            g = abs(newy - tpunkty.first);
                        }
                        else 
                        {
                            int x = (newx) - (tpunkty.second);
                            int y = (newy) - (tpunkty.first);
                            double path = (x * x) + (y * y);
                            g = sqrt(path);
                        }
                        g = g + punkty[tpunkty.first][tpunkty.second].g;

                        // Wyznaczenie sumy odleglosci
                        float s = h + g;
        
                        // Wpisanie powyzszych wartosci do tablicy punktow
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
                    }
                }
            }
        }

        // Przeszukiwanie tablicy w celu znalezienia punktu o najnizszej wartosci s, ktory nie zostal jeszcze zbadany
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

        // Dodanie powyzszego punktu do stosu punktow do zbadania
        openList.insert({ nowyy, nowyx });
        
        // Aktualizacja mapy z kazda iteracja petli
        //print(mapa);
        //system("cls");

        // Wstrzymanie dzialania programu po kazdej iteracji petli
        //system("pause");

        // Sztuczne spowolnienie dzialania programu dla poprawy widocznosci wykonywanych operacji
        //Sleep(200);
        
    }

    // Informacja o nieudanym poszukiwaniu drogi do celu
    std::cout << "Nie znaleziono drogi!\n";
    print(mapa);
}

int main()
{
    // Mapa labiryntu
    // Narysuj labirynt stosujac nastepujace liczby, oznaczajace poszczegolne jego elementy:
    // 0 - puste, 1 - sciana, 2 - start, 3 - koniec, 4 - pomaranczowy, 5 - fiolet
    zmapa mapa = {
        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1},
        {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,3,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
    };

    // Uruchomienie algorytmu szukajacego najkrotszej sciezki
    // Pierwszy argument - odwolanie do mapy
    // Drugi argument - punkt startowy {y,x}
    // Trzeci argument - punkt koncowy {y,x}
    a_star(mapa, { 1,1 }, { 21,21 });
}
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace std;

pair<vector<vector<char>>, vector<pair<int, int>>> gerar_tabuleiro_com_bloqueios_melhorado(
    int n,
    int num_bloqueios = -1,
    int seed = 0,
    double percentual_max = 0.2)
{
    if (seed != -1)
        srand(seed);
    else
        srand(time(nullptr));

    int total_casas = n * n;
    int max_bloqueios = min(total_casas - n, int(percentual_max * total_casas));

    if (num_bloqueios == -1)
        num_bloqueios = int(0.07 * total_casas);
    else if (num_bloqueios > max_bloqueios)
        throw invalid_argument("Número de bloqueios excede o máximo permitido para o valor de n.");

    vector<vector<char>> tabuleiro(n, vector<char>(n, '.'));
    set<pair<int, int>> bloqueios;

    while ((int)bloqueios.size() < num_bloqueios)
    {
        int i = rand() % n;
        int j = rand() % n;
        pair<int, int> pos = make_pair(i, j);
        if (bloqueios.find(pos) == bloqueios.end())
        {
            tabuleiro[i][j] = 'X';
            bloqueios.insert(pos);
        }
    }

    vector<pair<int, int>> bloqueios_lista(bloqueios.begin(), bloqueios.end());
    return make_pair(tabuleiro, bloqueios_lista);
}

void imprimir_tabuleiro(const vector<vector<char>> &tabuleiro, int limite = 32)
{
    int n = tabuleiro.size();
    for (int i = 0; i < min(n, limite); ++i)
    {
        for (int j = 0; j < min((int)tabuleiro[i].size(), limite); ++j)
        {
            cout << tabuleiro[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    int n = 8;
    pair<vector<vector<char>>, vector<pair<int, int>>> resultado = gerar_tabuleiro_com_bloqueios_melhorado(n, -1, 1);
    vector<vector<char>> tabuleiro = resultado.first;
    vector<pair<int, int>> bloqueios = resultado.second;

    imprimir_tabuleiro(tabuleiro);

    cout << "\nBloqueios:\n";
    for (size_t k = 0; k < bloqueios.size(); ++k)
    {
        cout << "(" << bloqueios[k].first << ", " << bloqueios[k].second << ") ";
    }
    cout << endl;

    return 0;
}

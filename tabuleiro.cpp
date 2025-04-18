#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <random>
#include <ctime>

using namespace std;

pair<vector<vector<char>>, vector<pair<int, int>>> gerar_tabuleiro_com_bloqueios_melhorado(
    int n,
    int num_bloqueios = -1,
    int seed = -1,
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

    while (bloqueios.size() < num_bloqueios)
    {
        int i = rand() % n;
        int j = rand() % n;
        pair<int, int> pos = {i, j};
        if (bloqueios.find(pos) == bloqueios.end())
        {
            tabuleiro[i][j] = 'X';
            bloqueios.insert(pos);
        }
    }

    vector<pair<int, int>> bloqueios_lista(bloqueios.begin(), bloqueios.end());
    return {tabuleiro, bloqueios_lista};
}

void imprimir_tabuleiro(const vector<vector<char>> &tabuleiro, int limite = 32)
{
    int n = tabuleiro.size();
    for (int i = 0; i < min(n, limite); ++i)
    {
        for (int j = 0; j < min(int(tabuleiro[i].size()), limite); ++j)
        {
            cout << tabuleiro[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    int n = 8;
    auto [tabuleiro, bloqueios] = gerar_tabuleiro_com_bloqueios_melhorado(n, -1, 10);
    imprimir_tabuleiro(tabuleiro);

    cout << "\nBloqueios:\n";
    for (const auto &[i, j] : bloqueios)
    {
        cout << "(" << i << ", " << j << ") ";
    }
    cout << endl;

    return 0;
}

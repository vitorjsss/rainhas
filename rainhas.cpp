#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

// Função para gerar o tabuleiro com bloqueios aleatórios
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

// Função para imprimir o tabuleiro
void printSolution(const vector<vector<char>> &board)
{
    int n = board.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << " " << board[i][j] << " ";
        cout << "\n";
    }
}

// Verifica se é seguro colocar a rainha
bool isSafe(const vector<vector<char>> &board, int row, int col)
{
    int n = board.size();

    // Mesma linha para a esquerda
    for (int i = 0; i < col; i++)
        if (board[row][i] == 'R')
            return false;

    // Diagonal superior esquerda
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'R')
            return false;

    // Diagonal inferior esquerda
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j] == 'R')
            return false;

    // Verifica se a posição está bloqueada
    if (board[row][col] == 'X')
        return false;

    return true;
}

// Algoritmo principal de backtracking
bool solveNQUtil(vector<vector<char>> &board, int col)
{
    int n = board.size();

    if (col >= n)
        return true;

    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col))
        {
            board[i][col] = 'R';

            if (solveNQUtil(board, col + 1))
                return true;

            board[i][col] = '.'; // backtrack
        }
    }

    return false;
}

// Função principal
int main()
{
    int n = 8;
    pair<vector<vector<char>>, vector<pair<int, int>>> resultado = gerar_tabuleiro_com_bloqueios_melhorado(n, -1, 1);
    vector<vector<char>> tabuleiro = resultado.first;
    vector<pair<int, int>> bloqueios = resultado.second;

    if (!solveNQUtil(tabuleiro, 0))
    {
        cout << "Nenhuma solução encontrada para N = " << n << "\n";
        printSolution(tabuleiro);
        return 0;
    }

    cout << "Solução encontrada para N = " << n << ":\n";
    printSolution(tabuleiro);
    return 0;
}


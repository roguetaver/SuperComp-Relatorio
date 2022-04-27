#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// função que devolve o score resultante entre duas sequencias
int get_score(string A, string B)
{
    int score = 0;
    for (int i = 0; i < int(A.size()); i++)
    {
        if (A[i] != B[i])
        {
            score += 1;
        }
        else if (A[i] == B[i])
        {
            score += 2;
        }
    }
    return score;
}

int main()
{
    // declarao e iniciação de variaveis

    int m;
    int n;
    int best_score = 0;
    int score = 0;
    int sizeA;
    int sizeB;
    string seqA;
    string seqB;
    string best_seqA;
    string best_seqB;
    vector<string> all_subseq_A;
    vector<string> all_subseq_B;

    // recebendo as sequencias A e B assim como seus tamanhos

    cin >> n;
    cin >> m;
    cin >> seqA;
    cin >> seqB;

    // print das sequencias A e B assim como seus respectivos tamanhos

    cout << "-------------------------------------" << endl;
    cout << "Tamanho de A (n) = " << n << endl;
    cout << "Sequencia A = " << seqA << endl;
    cout << "-------------------------------------" << endl;
    cout << "Tamanho de B (m) = " << m << endl;
    cout << "Sequencia B = " << seqB << endl;

    // geração de todas as subsequencias possíveis das sequencias A e B

    for (int i = 0; i <= int(seqA.size()); i++)
    {
        for (int j = 1; j <= int(seqA.size()); j++)
        {
            all_subseq_A.push_back(seqA.substr(i, j));
        }
    }

    for (int i = 0; i <= int(seqB.size()); i++)
    {
        for (int j = 1; j <= int(seqB.size()); j++)
        {
            all_subseq_B.push_back(seqB.substr(i, j));
        }
    }

    // comparação exaustiva entre todas as subsequencias geradas

    for (int i = 0; i < int(all_subseq_A.size()); i++)
    {
        for (int j = 0; j < int(all_subseq_B.size()); j++)
        {
            // tamanho da subsequencia A atual
            sizeA = int(all_subseq_A[i].size());

            // tamanho da subsequencia B atual
            sizeB = int(all_subseq_B[j].size());

            if (sizeA == sizeB)
            {
                score = get_score(all_subseq_A[i], all_subseq_B[j]);

                if (score >= best_score)
                {
                    best_score = score;
                    best_seqA = all_subseq_A[i];
                    best_seqB = all_subseq_B[j];
                }
            }

            else if (sizeA < sizeB)
            {
                string subseq_menor = all_subseq_A[i];
                string subseq_maior = all_subseq_B[j];

                for (int i = 0; i < (int(subseq_maior.size()) - int(subseq_menor.size())); i++)
                {
                    score = get_score(subseq_menor, subseq_maior.substr(i, int(subseq_menor.size())));

                    if (score >= best_score)
                    {
                        best_score = score;
                        best_seqA = subseq_menor;
                        best_seqB = subseq_maior.substr(i, int(subseq_menor.size()));
                    }
                }
            }

            else if (sizeA > sizeB)
            {
                string subseq_maior = all_subseq_A[i];
                string subseq_menor = all_subseq_B[j];

                for (int i = 0; i < (int(subseq_maior.size()) - int(subseq_menor.size())); i++)
                {
                    score = get_score(subseq_menor, subseq_maior.substr(i, int(subseq_menor.size())));

                    if (score >= best_score)
                    {
                        best_score = score;
                        best_seqA = subseq_maior.substr(i, int(subseq_menor.size()));
                        best_seqB = subseq_menor;
                    }
                }
            }
        }
    }

    // print das sequencias A e B alinhadas e seu score
    cout << "-------------------------------------" << endl;
    cout << "Melhor score: " << best_score << endl;
    cout << "Sequencia A alinhada: " << best_seqA << endl;
    cout << "Sequencia B alinhada: " << best_seqB << endl;
    cout << "-------------------------------------" << endl;

    return best_score;
}

// g++ -Wall -O3 main.cpp -o main
// ./main < dna.seq
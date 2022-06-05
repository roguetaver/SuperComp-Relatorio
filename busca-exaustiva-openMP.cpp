#include <iostream>
#include <algorithm>
#include <random>
#include <omp.h>

using namespace std;

// função que devolve o score resultante entre duas sequencias
int get_score(string A, string B)
{
    int score = 0;
    int size = int(A.size());
    
    for (int i = 0; i < size; i++)
    {
        if (A[i] != B[i])
        {
            score -= 1;
        }
        else if (A[i] == B[i])
        {
            score += 2;
        }
    }
    return score;
}

int main() {

    // declarao e iniciação de variaveis

    int n;
    int m;
    int score = 0;
    int best_score = 0;

    string seqA;
    string seqB;
    string best_seqA;
    string best_seqB;

    vector<string> all_subseq_A;
    vector<string> all_subseq_B;
    
    omp_set_num_threads(4);

    // recebendo as sequencias A e B assim como seus tamanhos

    cin >> n;
    cin >> m;
    cin >> seqA;
    cin >> seqB;

    // geração de todas as subsequencias possíveis das sequencias A e B

    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            all_subseq_A.push_back(seqA.substr(i, j));
        }
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            all_subseq_B.push_back(seqB.substr(i, j));
        }
    }

    // comparação exaustiva entre todas as subsequencias geradas

    int all_subseq_A_size = int(all_subseq_A.size());
    int all_subseq_B_size = int(all_subseq_B.size());

#pragma omp parallel for shared(best_seqA, best_seqB) reduction(max:best_score)

    for(int i = 0; i < all_subseq_A_size; i++){

        #pragma omp parallel for 
        for(int j = 0; j < all_subseq_B_size; j++){

            if (int(all_subseq_A[i].size()) == int(all_subseq_B[j].size())) {

                score = get_score(all_subseq_A[i], all_subseq_B[j]);

                if (score >= best_score) {
                    best_score = score;
                    best_seqA = all_subseq_A[i];
                    best_seqB = all_subseq_B[j];
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

    return 0;
}

// g++ -Wall -O3 -fopenmp busca-exaustiva-openMP.cpp -o busca-exaustiva-openMP
// ./busca-exaustiva-openMP < dna.seq
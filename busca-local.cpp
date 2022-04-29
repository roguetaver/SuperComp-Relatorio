#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

struct subsequencia_B
{
    string subseq;
    int score;
};

string generate_subsequence(string seq, int k, int size)
{
    string new_sequence;
    int random_index;

    random_device rd;
    unsigned seed = rd();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, size - k);

    random_index = distribution(generator);

    while (int(new_sequence.size()) < k)
    {
        new_sequence += seq[random_index];
        random_index++;
    }

    return new_sequence;
}

int seq_score(string a, string b)
{
    int score = 0;
    int len = int(a.size());

    for (int i = 0; i < len; i++)
    {
        if (a[i] == b[i])
        {
            score += 2;
        }
        else
        {
            score -= 1;
        }
    }

    return score;
}

int main()
{
    // declarao e iniciação de variaveis
    string subseqA;
    string subseqB;
    string seqA;
    string seqB;
    string tempseq;
    string bestSeqB;
    vector<subsequencia_B> subseqsB;
    int actual_score = 0;
    int best_score = -999;
    int m;
    int n;
    int k;
    int p;
    int tempint;

    // recebendo as sequencias A e B assim como seus tamanhos
    cin >> n;
    cin >> m;
    cin >> seqA;
    cin >> seqB;

    if (n > m)
    {
        tempseq = seqA;
        seqA = seqB;
        seqB = tempseq;
        tempint = m;
        m = n;
        n = tempint;
    }

    // print das sequencias A e B assim como seus respectivos tamanhos
    cout << "-------------------------------------" << endl;
    cout << "Tamanho de A (n) = " << n << endl;
    cout << "Sequencia A = " << seqA << endl;
    cout << "-------------------------------------" << endl;
    cout << "Tamanho de B (m) = " << m << endl;
    cout << "Sequencia B = " << seqB << endl;

    // criacao da subsequencia A
    random_device rd;
    unsigned seed = rd();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, n);

    k = distribution(generator);

    cout << "-------------------------------------" << endl;
    cout << "valor k (tamanho das subsequencias A e B): " << k << endl;

    subseqA = generate_subsequence(seqA, k, n);

    // criacao das subsequencias B
    p = distribution(generator);

    cout << "-------------------------------------" << endl;
    cout << "valor p (quantidade de subsequencias B criadas): " << p << endl;
    cout << "-------------------------------------" << endl;
    cout << "todas subsequencias B criadas: " << endl;
    cout << " " << endl;

    for (int i = 0; i < p; i++)
    {
        subsequencia_B subseqB;
        subseqB.subseq = generate_subsequence(seqB, k, m);

        if (i == 0)
        {
            bestSeqB = subseqB.subseq;
        }

        cout << subseqB.subseq << endl;

        actual_score = seq_score(subseqA, subseqB.subseq);
        subseqB.score = actual_score;

        cout << "score: " << subseqB.score << endl;
        cout << " " << endl;

        subseqsB.push_back(subseqB);

        if (actual_score >= best_score)
        {
            best_score = actual_score;
            bestSeqB = subseqB.subseq;
        }
    }

    cout << "-------------------------------------" << endl;
    cout << "Sequencia A: " << subseqA << endl;
    cout << "Sequencia B: " << bestSeqB << endl;
    cout << "Score: " << best_score << endl;
    cout << "-------------------------------------" << endl;

    return 0;
}

// g++ -Wall -O3 main.cpp -o main
// ./main < dna.seq
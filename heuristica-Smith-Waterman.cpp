#include <iostream>  // std::cout
#include <algorithm> // std::reverse
#include <vector>    // std::vector

using namespace std;

// struct de nós para matriz H
struct node
{
    string token; // movimentos disponiveis (diagonal,insercao e delecao)
    int linha;    // linha em que o nó se encontra
    int coluna;   // coluna em que o nó se encontra
    int valor;    // score do nó
};

// funcao que pega o maior valor entre o score da diagonal, delecao e insercao
// vale a pena notar que a insercao possui prioridade sobre a delecao

string maxVal(int diag, int del, int ins)
{
    if (diag >= del and diag >= ins and diag >= 0)
    {
        return "diagonal";
    }
    else if (ins >= del and ins >= 0)
    {
        return "insercao";
    }
    else if (del >= 0)
    {
        return "delecao";
    }
    else
    {
        return "zero";
    }
}

int main()
{
    // declarao e iniciação de variaveis

    vector<vector<node>> H;
    int m;
    int n;
    int diag = 0;
    int del = 0;
    int ins = 0;
    int valorMaximo = 0;
    int valorMaximoI = 0;
    int valorMaximoJ = 0;
    string seqA;
    string seqB;

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

    // inicializando matriz H com zeros

    H.resize(n + 1);
    for (int i = 0; i <= n; i++)
    {
        H[i].resize(m + 1);
    }

    // criando a matriz H
    // cada elemento da matriz H é de tipo node, struct declarada no inicio do codigo
    // desse modo, cada nó além de possuir seu valor e posição, também possui a direção de onde ele veio

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (seqA[i - 1] == seqB[j - 1])
            {
                diag = H[i - 1][j - 1].valor + 2;
            }
            else
            {
                diag = H[i - 1][j - 1].valor - 1;
            }

            ins = H[i][j - 1].valor - 1;

            del = H[i - 1][j].valor - 1;

            string tokenAtual = maxVal(diag, del, ins);

            if (tokenAtual == "diagonal")
            {
                H[i][j].valor = diag;
                H[i][j].linha = i;
                H[i][j].coluna = j;
                H[i][j].token = tokenAtual;
            }
            else if (tokenAtual == "delecao")
            {
                H[i][j].valor = del;
                H[i][j].linha = i;
                H[i][j].coluna = j;
                H[i][j].token = tokenAtual;
            }
            else if (tokenAtual == "insercao")
            {
                H[i][j].valor = ins;
                H[i][j].linha = i;
                H[i][j].coluna = j;
                H[i][j].token = tokenAtual;
            }
            else if (tokenAtual == "zero")
            {
                H[i][j].valor = 0;
                H[i][j].linha = i;
                H[i][j].coluna = j;
                H[i][j].token = "diagonal";
            }

            // calculando o score maximo da matriz H
            if (H[i][j].valor >= valorMaximo)
            {
                valorMaximo = H[i][j].valor;
                valorMaximoI = H[i][j].linha;
                valorMaximoJ = H[i][j].coluna;
            }
        }
    }

    // printando a matriz H assim como seu valor Maximo

    cout << "-------------------------------------" << endl;
    cout << "Matriz H" << endl;

    for (int i = 0; i <= n; i++)
    {
        cout << " " << endl;
        for (int j = 0; j <= m; j++)
        {
            cout << H[i][j].valor << " ";
        }
    }

    cout << "" << endl;
    cout << endl
         << "Valor Máximo da matriz H: " << valorMaximo << endl;
    cout << "Localizado em i = " << valorMaximoI << " e localizado em j = " << valorMaximoJ << endl;

    // Após criar a matriz H agora partindo do maior score nela
    // devemos traçar o caminho inverso para chegar no maior valor até atingir zero

    node termoAtual;
    termoAtual.linha = valorMaximoI;
    termoAtual.coluna = valorMaximoJ;

    string seqA_alinhada = "";
    string seqB_alinhada = "";

    // abaixo o caminho reverso é traçado a partir do maior score,
    // chegando assim na sequencia alinhada reversa

    while (termoAtual.valor != 0)
    {
        if (termoAtual.token == "diagonal")
        {
            seqA_alinhada += seqA[termoAtual.linha - 1];
            seqB_alinhada += seqB[termoAtual.coluna - 1];
            termoAtual.linha -= 1;
            termoAtual.coluna -= 1;
        }

        else if (termoAtual.token == "delecao")
        {
            seqA_alinhada += seqA[termoAtual.linha - 1];
            seqB_alinhada += "-";
            termoAtual.linha -= 1;
        }
        else if (termoAtual.token == "insercao")
        {
            seqA_alinhada += "-";
            seqB_alinhada += seqB[termoAtual.coluna - 1];
            termoAtual.coluna -= 1;
        }
        termoAtual.token = H[termoAtual.linha][termoAtual.coluna].token;
        termoAtual.valor = H[termoAtual.linha][termoAtual.coluna].valor;
    }

    // revertendo as sequencias
    reverse(seqA_alinhada.begin(), seqA_alinhada.end());
    reverse(seqB_alinhada.begin(), seqB_alinhada.end());

    // print das sequencias A e B alinhadas
    cout << "-------------------------------------" << endl;
    cout << "Sequencia A alinhada: " << seqA_alinhada << endl;
    cout << "Sequencia B alinhada: " << seqB_alinhada << endl;
    cout << "-------------------------------------" << endl;

    return valorMaximo;
}

// g++ -Wall -O3 main.cpp -o entrega1
// ./entrega1 < dna.seq
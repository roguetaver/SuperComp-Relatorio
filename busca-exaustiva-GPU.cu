#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/sequence.h>
#include <thrust/tuple.h>
#include <thrust/device_vector.h>

using namespace std;
struct cmp_horizontal
{
    __host__ __device__ 
    int operator()(const int &a, const int &b)
    {
        if (b > 0 && b > (a - 1))
        {
            return b;
        }
        else if ((a - 1) > 0 && (a - 1) > b)
        {
            return (a - 1);
        }
        else if ((a - 1) > 0 && b == (a - 1))
        {
            return (a - 1);
        }
        return 0;
    }
};
struct cmp_vertical
{
    int diag, ins;
    char element;

    cmp_vertical(int element_index) : element(element_index){};
    
    __host__ __device__ 
    int operator()(const thrust::tuple<char, int, int> &t)
    {
        ins = thrust::get<2>(t) - 1;

        if(element == thrust::get<0>(t)){
            diag = thrust::get<1>(t) + 2;
        }
        else{
            diag = thrust::get<1>(t) - 1;
        }

        if (diag > 0 && diag > ins)
        {
            return diag;
        }
        else if (ins > 0 && ins > diag)
        {
            return ins;
        }
        else if (diag > 0 && ins == diag)
        {
            return diag;
        }
        return 0;
    }
};

int main(int argc, char *argv[])
{
    string seq_A, seq_B, bigger_seq, smaller_seq;

    int n, m, score, bigger_size, smaller_size;
    int best_score = 0;

    cin >> n >> m;
    cin >> seq_A >> seq_B;

    if (n > m)
    {
        bigger_seq = seq_A;
        smaller_seq = seq_B;
    }
    else
    {
        bigger_seq = seq_B;
        smaller_seq = seq_A;
    }

    bigger_seq = 'X' + bigger_seq;

    bigger_size = int(bigger_seq.size());
    smaller_size = int(smaller_seq.size());

    thrust::device_vector<char> thrust_seq_A(bigger_size + 1);
    thrust::device_vector<char> thrust_seq_B(smaller_size + 1);
    thrust::device_vector<int> thrust_r(smaller_size + 1);
    thrust::device_vector<int> thrust_b(smaller_size + 1);

    for (int i = 0; i < int(bigger_seq.size()); i++)
    {
        thrust_seq_A[i] = bigger_seq[i];
    }

    for (int j = 0; j < int(smaller_seq.size()); j++)
    {
        thrust_seq_B[j] = smaller_seq[j];
    }

    for (int k = 0; k < int(bigger_seq.size()) - smaller_size; k++)
    {
        thrust::fill(thrust_r.begin(), thrust_r.end(), 0);

        for (int l = 0; l < smaller_size + 1; l++)
        {
            score = 0;

            thrust::transform(thrust::make_zip_iterator(thrust::make_tuple(thrust_seq_B.begin() + 1,
                            thrust_r.begin(), thrust_r.begin() + 1)),
                            thrust::make_zip_iterator(thrust::make_tuple(thrust_seq_B.begin() + smaller_size + 1,
                            thrust_r.begin() + smaller_size, thrust_r.begin() + smaller_size + 1)),
                            thrust_b.begin() + 1,
                            cmp_vertical(thrust_seq_A[l + k]));

            thrust::inclusive_scan(thrust_b.begin(),
                                   thrust_b.begin() + smaller_size,
                                   thrust_r.begin(),
                                   cmp_horizontal());

            score = thrust::reduce(thrust_r.begin(),
                                   thrust_r.begin() + smaller_size,
                                   (int)0,
                                   thrust::maximum<int>());

            if (score >= best_score)
            {
                best_score = score;
            }
        }
    }

    cout << "Score: " << best_score << endl;

    return 0;
}

// nvcc -o busca-exaustiva-GPU busca-exaustiva-GPU.cu
//  ./busca-exaustiva-GPU
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <vector>

#include <thrust/iterator/counting_iterator.h>
#include <thrust/transform_reduce.h>
#include <thrust/functional.h>
#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>

using namespace std;

struct seq_index
{
    int size;
    int start_a;
    int start_b;
};

using namespace std::chrono;

std::vector<seq_index> seq_gen(int max_size, int min_size)
{

    seq_index actual_index;
    vector<seq_index> all_indexes;

    for (int index = 0; index < min_size; index++)
    {
        for (int i = 0; i < max_size; i++)
        {
            for (int j = 0; j < min_size; j++)
            {
                actual_index.start_a = i;
                actual_index.start_b = j;
                actual_index.size = i + index;
                all_indexes.push_back(actual_index);
            }
        }
    }
    return all_indexes;
}

struct seq_score
{
    __host__ __device__ int operator()(const char &a, const char &b)
    {

        if (a != b)
        {
            return -1;
        }
        else if (a == b)
        {
            return 2;
        }
        return 0;
    }
};

int main()
{
    string seq_A, seq_B;
    int m, n;
    int max_size;
    int min_size;
    int size_a = 0;
    int size_b = 0;
    int best_score = 0;
    
    std::cin >> n >> m >> seq_A >> seq_B;

    size_a = int(seq_A.size());
    size_b = int(seq_B.size());

    if(size_a >= size_b){
        max_size = size_a;
        min_size = size_b;
    }
    else{
        max_size = size_a;
        min_size = size_b;
    }

    std::vector<seq_index> seq_indexes = seq_gen(max_size, min_size);

    thrust::device_vector<char> seq_A_GPU(n);
    thrust::device_vector<char> seq_B_GPU(m);
    thrust::device_vector<char> sequences(min_size);

    for (int i = 0; i < n; i++)
    {
        seq_A_GPU[i] = seq_A[i];
    }

    for (int j = 0; j < m; j++)
    {
        seq_B_GPU[j] = seq_B[j];
    }

    for (int k = 0; k < int(seq_indexes.size()); k++)
    {
        thrust::transform(seq_B_GPU.begin() + seq_indexes[k].start_b, 
                        seq_B_GPU.end() + seq_indexes[k].start_b + seq_indexes[k].size,
                        seq_A_GPU.begin() + seq_indexes[k].start_a, 
                        sequences.begin(),
                        seq_score());

        int actual_score = thrust::reduce(sequences.begin(), sequences.end(), (int)0, thrust::plus<int>());

        if (best_score <= actual_score)
        {
            best_score = actual_score;
        }
    }

    std::cout << "Score: " << best_score << endl;

    return 0;
}

//nvcc -o busca-exaustiva-GPU busca-exaustiva-GPU.cu
// ./busca-exaustiva-GPU
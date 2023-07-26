#include <iostream>
#include <cuda.h>
#include <vector>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <string>
using namespace std;

class Runner {
public:
    string name;
    int currentPosition;
    int speed;
};

// CUDA kernel fonksiyonu
__global__ void updateRunners(int numRunners, Runner* runners) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < numRunners) {
        // Hesaplama işlemleri burada yapılır.
        // Koşucunun hızı ve mevcut konumu güncellenir.
        runners[tid].currentPosition += runners[tid].speed;
    }
}

class Team {
public:
    string name;
    vector<Runner> runners;
    bool finished;
};

int main() {
    int numRunners = 4;
    vector<Runner> runners(numRunners);

    // Koşucu ve takım bilgilerini doldurun (kullanıcıdan alabilir veya sabit değerler atayabilirsiniz).
    for (int i = 0; i < numRunners; ++i) {
        runners[i].name = "Runner " + to_string(i + 1);
        runners[i].currentPosition = i * 100;
        runners[i].speed = (rand() % 5) + 1; // Rastgele 1 ile 5 arasında bir hız değeri atayın.
    }

    // CUDA bellek kopyalama işlemleri
    Runner* d_runners; // GPU üzerindeki koşucuların adresi
    size_t runnersSize = numRunners * sizeof(Runner);
    cudaMalloc((void**)&d_runners, runnersSize);
    cudaMemcpy(d_runners, runners.data(), runnersSize, cudaMemcpyHostToDevice);

    // CUDA Kernel fonksiyonunu çağırma
    int numBlocks = (numRunners + 255) / 256;
    int numThreadsPerBlock = 256;
    updateRunners<<<numBlocks, numThreadsPerBlock>>>(numRunners, d_runners);
    cudaDeviceSynchronize();

    // Koşucuların güncellenmiş verilerini geri alma
    cudaMemcpy(runners.data(), d_runners, runnersSize, cudaMemcpyDeviceToHost);

    // CUDA bellek serbest bırakma
    cudaFree(d_runners);

    // Yarış sonuçlarını yazdırma
    cout << "Updated Runner Information:" << endl;
    for (const auto& runner : runners) {
        cout << "Runner: " << runner.name << ", Position: " << runner.currentPosition << ", Speed: " << runner.speed << endl;
    }

    return 0;
}
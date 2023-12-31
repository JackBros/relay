cmake_minimum_required(VERSION 3.10)

# Projenin adını ve C++ sürümünü belirtin
project(MyCUDATestProject CXX)

# CUDA ayarlarını yapın
find_package(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11")

# C++ kaynak dosyasını ve CUDA kernel dosyasını belirtin
set(SOURCES
    ETE_Tec.cpp
)

# CUDA kernel dosyasını belirtin
set(CUDA_SOURCES
    updateRunners.cu
)

# CUDA ile derleme yapacağımızı belirtin
set(CUDA_SEPARABLE_COMPILATION ON)

# Yürütülebilir dosyayı oluşturun
add_executable(MyCUDAExecutable ${SOURCES} ${CUDA_SOURCES})

# CUDA kütüphanelerini ve bağımlılıklarını ekleyin
target_link_libraries(MyCUDAExecutable PRIVATE ${CUDA_LIBRARIES})

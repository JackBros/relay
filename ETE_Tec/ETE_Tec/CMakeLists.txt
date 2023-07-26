cmake_minimum_required(VERSION 3.10)

# Projenin adýný ve C++ sürümünü belirtin
project(MyCUDATestProject CXX)

# CUDA ayarlarýný yapýn
find_package(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11")

# C++ kaynak dosyasýný ve CUDA kernel dosyasýný belirtin
set(SOURCES
    ETE_Tec.cpp
)

# CUDA kernel dosyasýný belirtin
set(CUDA_SOURCES
    updateRunners.cu
)

# CUDA ile derleme yapacaðýmýzý belirtin
set(CUDA_SEPARABLE_COMPILATION ON)

# Yürütülebilir dosyayý oluþturun
add_executable(MyCUDAExecutable ${SOURCES} ${CUDA_SOURCES})

# CUDA kütüphanelerini ve baðýmlýlýklarýný ekleyin
target_link_libraries(MyCUDAExecutable PRIVATE ${CUDA_LIBRARIES})

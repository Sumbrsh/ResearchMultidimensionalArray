#include <iostream>
#include <vector>
#include <gtest/gtest.h>

template <typename T = char, typename ... Args>
void* CreateArrayAtMemory(size_t bs, Args ... args) {
    size_t R = bs * sizeof(T);
    size_t PS = sizeof(void*);
    char* P0 = nullptr;

    if constexpr (sizeof...(args) > 0) {
        P0 = new char[R];
        char* P = P0;

        for (size_t i = 0; i < bs; ++i) {
            void* subarray = CreateArrayAtMemory<T>(args...);
            *reinterpret_cast<void**>(P) = subarray;
            P += PS;
        }
    }
    else {
        P0 = new char[R];
    }

    return P0;
}

TEST(CreateArrayTest, OneDimensionalArray) {
    void* array = CreateArrayAtMemory<int>(5);
    int* intArray = static_cast<int*>(array);

    EXPECT_NE(intArray, nullptr);

    delete[] static_cast<char*>(array);
}

TEST(CreateArrayTest, TwoDimensionalArray) {
    void* array = CreateArrayAtMemory<double>(3, 4, 5);
    double*** doubleArray = static_cast<double***>(array);

    EXPECT_NE(doubleArray, nullptr);

    delete[] static_cast<char*>(array);
}


TEST(CreateArrayTest, OneDimensionalArrayValues) {
    int value = 0x21;
    void* array = CreateArrayAtMemory<int>(5);
    int* intArray = static_cast<int*>(array);

    for (int i = 0; i < 5; ++i) {
        intArray[i] = value++;
    }

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(intArray[i], 0x21 + i);
    }

    delete[] static_cast<char*>(array);
}


TEST(CreateArrayTest, TwoDimensionalArrayValues) {
    int value = 0x21;
    void* array = CreateArrayAtMemory<double>(3, 4, 5);
    double*** doubleArray = static_cast<double***>(array);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 5; ++k) {
                doubleArray[i][j][k] = value++;
            }
        }
    }

    value = 0x21;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 5; ++k) {
                EXPECT_EQ(doubleArray[i][j][k], static_cast<double>(value++));
            }
        }
    }

    delete[] static_cast<char*>(array);
}

int main(int argc, char** argv) {

    int value = 0x21;
    void* array1 = CreateArrayAtMemory<int>(5);
    std::cout << "Size of array 1: " << 5 * sizeof(int) << " bytes" << std::endl;
    int* intArray1 = static_cast<int*>(array1);

    std::cout << "Array 1: ";
    for (int i = 0; i < 5; i++) {
        intArray1[i] = value++;
        std::cout << intArray1[i] << " ";
    }
    std::cout << std::endl;

    void* array2 = CreateArrayAtMemory<double>(3, 4, 5);
    std::cout << "Size of array 2: " << 3 * 4 * 5 * sizeof(double) << " bytes" << std::endl;
    double*** doubleArray2 = static_cast<double***>(array2);
    int value2 = 0x21;
    std::cout << "Array 2:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 5; k++) {
                doubleArray2[i][j][k] = value2++;
                std::cout << doubleArray2[i][j][k] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}

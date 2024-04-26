#include <iostream>
#include <vector>
#include "TemplateArray.h"
using namespace std;

int main() {

    int j = 0x21;
    //1 ������� ������ �� � � ������, �� �����
    size_t n1 = CreateArrayAtMemory(nullptr, 2);
    vector<char> a1(n1);
    char* f1 = (char*)a1.data();
    CreateArrayAtMemory(f1, 2);
    for (int i1 = 0; i1 < 2; i1++)
    {
        f1[i1] = j++;
    }
    for (int i1 = 0; i1 < 2; i1++)
    {
        std::cout << (int)f1[i1] << " ";
    }
    std::cout << std::endl << n1 << " bytes used " << std::endl;
    //2 ������� �� ������� � �������, � �������� 34 �� 35 ���� ������ �������� ����������. 
    // �� �� ��������� ����� �� ������ �������� ������� � 1) �� 2). 
    // � ��������� ����� ��������� ��� ����� n2, �� �������� ������� ����� � �� ������� �������� �� �������, ���� � ���� 28 ����
    int k = 0x21;
    size_t n2 = CreateArrayAtMemory<short>(nullptr, 2, 3); //1)  <short>
    vector<char> a2(n2);
    short** f2 = (short**)a2.data();
    CreateArrayAtMemory<short>(f2, 2, 3); //2) <short>
    for (int i1 = 0; i1 < 2; i1++)
    {
        for (int i2 = 0; i2 < 3; i2++)
        {
            f2[i1][i2] = k++;
        }
    }

    for (int i1 = 0; i1 < 2; i1++)
    {
        for (int i2 = 0; i2 < 3; i2++)
        {
            std::cout << (int)f2[i1][i2] << " ";
        }
    }
    std::cout << std::endl << n2 << " bytes used " << std::endl;
    std::cout << std::endl;
    // 3 ������� ��� ����� ���� ������� �������� � 2 ���������, ��� ����� � ��� � ����� 50
    int l = 0x21;
    size_t n5 = CreateArrayAtMemory<int>(nullptr, 2, 3, 4, 5, 6); // ����� ��������� ������� vector a5 � 51 ����� � �������
    vector<char> a5(n5);
    int***** f5 = (int*****)a5.data();
    CreateArrayAtMemory<int>(f5, 2, 3, 4, 5, 6);
    for (int i1 = 0; i1 < 2; i1++)
    {
        for (int i2 = 0; i2 < 3; i2++)
        {
            for (int i3 = 0; i3 < 4; i3++)
            {
                for (int i4 = 0; i4 < 5; i4++)
                {
                    for (int i5 = 0; i5 < 6; i5++)
                    {
                        f5[i1][i2][i3][i4][i5] = l++;
                    }
                }
            }
        }
    }

    for (int i1 = 0; i1 < 2; i1++)
    {
        for (int i2 = 0; i2 < 3; i2++)
        {
            for (int i3 = 0; i3 < 4; i3++)
            {
                for (int i4 = 0; i4 < 5; i4++)
                {
                    for (int i5 = 0; i5 < 6; i5++)
                    {
                        std::cout << (int)f5[i1][i2][i3][i4][i5] << " ";
                    }
                }
            }
        }
    }
    std::cout << std::endl << n5 << " bytes used " << std::endl;
    std::cout << std::endl;

	return 0;
}
#pragma once


template <typename T = char> size_t CreateArrayAtMemory(void*, size_t bs) //������ ������� ��� ��������� ���������� ������ 
{
    return bs * sizeof(T); //������� ����� ������ � ������
}

template <typename T = char, typename ... Args>
size_t CreateArrayAtMemory(void* p, size_t bs, Args ... args) //������ ������������� �������� CreateArrayAtMemory(void*, size_t bs), 
//��� ��������� ������  ����-��� ������� Args ... args(���������), ��� ���������� ������� n-����� ������
{   
    //���������� ����
    size_t R = 0; // �������� ������� ����� ��� ��������� ������(����� ����� ������)
    size_t PS = sizeof(void*); //����� ���������
    char* P = (char*)p; //�������� ��� ��������� ����� ������� � �����
    char* P0 = (char*)p; //��������� ������ ������

    size_t BytesForAllPointers = bs * PS; //���������� �������� ������� ����  
    R = BytesForAllPointers; //���������� �������� �����

    char* pos = P0 + BytesForAllPointers; //�������� �� ��������� ���� ���'�� ��� ��������� ������ ��������
    //���� ��� ��������� ������, �� ����� ��������� ����� ����������� ����������
    for (size_t i = 0; i < bs; i++)
    {
        char** pp = (char**)P;
        if (p)
            *pp = pos;
        size_t RLD = CreateArrayAtMemory<T>(p ? pos : nullptr, args ...);
        P += PS;
        R += RLD;
        pos += RLD;
    }
    return R;
}
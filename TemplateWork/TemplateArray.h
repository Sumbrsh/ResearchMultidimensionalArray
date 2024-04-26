#pragma once


template <typename T = char> size_t CreateArrayAtMemory(void*, size_t bs) //шаблон функції для створення динамічного масиву 
{
    return bs * sizeof(T); //повертає розмір масиву в байтах
}

template <typename T = char, typename ... Args>
size_t CreateArrayAtMemory(void* p, size_t bs, Args ... args) //шаблон перевантаженої функціїї CreateArrayAtMemory(void*, size_t bs), 
//яка додатково приймає  будь-яку кількість Args ... args(аргументів), щоб створювати динамічні n-вимірні масиви
{   
    //ініціалізуємо змінні
    size_t R = 0; // загальна кількість байтів для створення масиву(тобто розмір масиву)
    size_t PS = sizeof(void*); //розмір вказівника
    char* P = (char*)p; //вказівник для розміщення нових елментів у масиві
    char* P0 = (char*)p; //початкова адреса масиву

    size_t BytesForAllPointers = bs * PS; //обчислення загальної кількості байт  
    R = BytesForAllPointers; //просвоюємо значення змінній

    char* pos = P0 + BytesForAllPointers; //вказівник на наступний блок пам'яті для створення нового підмасиву
    //цикл для створення масиву, де кожен вкладений масив створюється рекурсивно
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
#include "Big_Number.h"
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <random>

// Определения методов класса Big_Number здесь
using namespace std;
// Конструктор по умолчанию/параметрам
Big_Number::Big_Number(int ml, int p)
{
    if (ml < 1)
    {
        exit(1);
    }
    else
    {
        // Максимальное количество байт > 0
        this->maxlen = ml; // Инициализация количества байт для числа
        this->len = ml;
        coef = new BASE[ml]; // Выделение динамической памяти

        if (coef)
        { // Проверка выделения памяти
            if (p == 0)
            { // Если параметр 0, то заполняем все цифры 0
                for (int i = 0; i < ml; i++)
                    coef[i] = 0;
                this->len = 1; // Инициализация количества цифр числа
            }
            else
            { // Иначе заполняем рандомными цифрами
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<BASE> dis(0, std::numeric_limits<BASE>::max());

                for (int i = 0; i < ml; i++)
                    coef[i] = dis(gen); // Генерация случайного числа
				int i = this->len - 1;
				while (i > 0 && coef[i] == 0)
					this->len--;
            }

        }
    }
}
// Конструктор копирования
Big_Number::Big_Number(const Big_Number &bn)
{
	len = bn.len;			 // Копирование значений
	maxlen = bn.maxlen;		 // Копирование значений
	coef = new BASE[maxlen]; // Выделение динамической памяти для массива цифр
	if (coef)
	{ // Проверка выделения динамической памяти
		for (int i = 0; i < bn.maxlen; i++)
		{
			coef[i] = bn.coef[i]; // Копирование цифр
		}
	}
	else
	{
		exit(1);
	}
}

// Перегрузка оператора =
Big_Number Big_Number::operator=(const Big_Number &bn)
{
	if (&bn == this)  // Проверка самоприсвоения
		return *this; // Возвращение самого объекта

	len = bn.len;		// Копирование значений
	maxlen = bn.maxlen; // Копирование значений

	if (coef)				 // Проверка на NULL
		delete coef;		 // Освобождение динамической памяти
	coef = NULL;			 // Присвоение NULL
	coef = new BASE[maxlen]; // Выделение динамической памяти
	if (coef)
	{ // Проверка выделения памяти
		for (int i = 0; i < bn.maxlen; i++)
			coef[i] = bn.coef[i]; // Копирование значений
	}

	return *this; // Возвращение самого объекта
}

// Перегрузка оператора равенства
bool Big_Number::operator==(const Big_Number &bn)
{
	if (this == &bn)
	{ // Проверка на сравнение самим с собой
		return true;
	}

	if (len != bn.len) // Проверка на длину (если количество цифр не одно и
		// то же, то числа разные)
		return false;

	for (int i = len - 1; i >= 0;
		 i--)
	{ // Проход по всем цифрам числа, если хотя бы одно не сходится, то
		// они не равны
		if (this->coef[i] != bn.coef[i]){
			return false;
		}
	}
	return true;
}
// Перегрузка оператора неравенства
bool Big_Number::operator!=(const Big_Number &bn)
{
	if (this == &bn)
	{ // Проверка на сравнение самим с собой
		return false;
	}
	if (len != bn.len) // Проверка на длину (если количество цифр не одно и
		// то же, то числа разные)
		return true;
	for (int i = len - 1; i >= 0;
		 i--)
	{ // Проход по всем цифрам числа, если хотя бы одно не сходится, то
		// они не равны
		if (coef[i] != bn.coef[i])
			return true;
	}
	return false;
}

// Перегрузка оператора больше ИСПРАВИТЬ
bool Big_Number::operator>(const Big_Number &bn)
{
	if (this == &bn || this->len < bn.len) // Если сравнивается объект с самим
		// собой или длины разные, то ложь
		return false;
	if (this->len > bn.len) // Если длина текущего  больше, то истина
		return true;
	for (size_t i = len - 1; i >= 0;
		 i--)
	{ // Проход по всем цифрам числа, если хотя бы одно меньше, то ложь
	if (coef[i] > bn.coef[i]){
		return true;
	}
	if (coef[i] < bn.coef[i])
		return false;
	}
	return false;
}
// Перегрузка оператора больше или равно
bool Big_Number::operator>=(const Big_Number &bn)
{
	if (this == &bn || this->len > bn.len) // Если сравнивается объект с самим
		// собой или длины разные, то истина
		return true;
	if (this->len < bn.len) // Если длина текущего  больше, то ложь
		return false;
	for (size_t i = len - 1; i >= 0; i--)
	{
		if (coef[i] < bn.coef[i])
			return false;
	}
	return true;
}
// Перегрузка оператора <
bool Big_Number::operator<(const Big_Number &bn)
{
	if (this == &bn || this->len > bn.len) // Если длина текущего больше или сравнивается один и тот же объект
		return false;
	if (this->len < bn.len) // Если длина текущего меньше
		return true;
	for (int i = len - 1; i >= 0; i--) // Проходимся по всем цифрам с начала (в coef записывали наоборот)
	{
			if (coef[i] > bn.coef[i]){
			{
				return false;
			}
			if (coef[i] < bn.coef[i])
				return true;
	}
	}
	return false;
}
// Перегрузка оператора <=
bool Big_Number::operator<=(const Big_Number &bn)
{
	if (this == &bn || this->len < bn.len) // Если сравнивается объект с самим
		// собой или длины разные, то истина
		return true;
	if (this->len > bn.len) // Если длина текущего  больше, то ложь
		return false;
	for (size_t i = len - 1; i >= 0; i--) // Проходимся по всем цифрам с начала (в coef записывали наоборот)
	{
		if (coef[i] > bn.coef[i]) // Если одна из цифр больше, то ложь
			return false;
	}
	return true;
}



// Ввод большого числа в 16-ом виде
void Big_Number::input_hex()
{
	bool flag = false;
	do
	{
		flag = false;
		char buf[128]; // Буфер для строки - числа
		std::cin >> buf; // Ввод строки
		int buf_len = strlen(buf); // Длина введенной строки
		len =(buf_len - 1)/(BASE_SIZE / 4) + 1; // Подсчет длины числа
		delete[] coef; // Очистка памяти
		coef = new BASE[len]; // Выделение памяти под коэффициенты
		// Инициализация коэффициентов нулями
		for (int i = 0; i < len; ++i)
			coef[i] = 0;

		int coef_index = 0; // Индекс текущего коэффициента
		int shift = 0; // Смещение в текущем коэффициенте

		// Обработка символов в обратном порядке
		for (int i = buf_len - 1; i >= 0; --i)
		{
			char ch = buf[i];
			int value = 0;
			if ('0' <= ch && ch <= '9') // Преобразование цифры в число
				value = ch - '0';
			else if ('a' <= ch && ch <= 'f') // Преобразование шестнадцатеричной цифры в число
				value = ch - 'a' + 10;
			else if ('A' <= ch && ch <= 'F') // Преобразование шестнадцатеричной цифры в число
				value = ch - 'A' + 10;
			else // Некорректный символ
			{
				cout <<"Invalid error. Enter a number: ";
				flag = true;
				break;
			}

			// Запись значения в текущий коэффициент
			coef[coef_index] |= value << shift;

			// Переход к следующему коэффициенту или смещение
			shift += 4;
			if (shift >= BASE_SIZE) // Если достигнут конец текущего коэффициента
			{
				shift = 0;
				++coef_index;
			}
		}
	
	}while (flag);
	int i = len - 1;
	while (i > 0 && coef[i] == 0)
		len--;
}


// Вывод в 16-ой системе
void Big_Number::output_hex()
{
    bool non_zero_found = false; // Флаг, указывающий, была ли найдена ненулевая цифра

    int k = BASE_SIZE - 4; // для смещения коэффициента
    int j = len - 1;

    while (j >= 0)
    {
        unsigned char tmp = (coef[j] >> k) & 0xf;

        if (tmp != 0 || non_zero_found) {
            // Если текущая цифра не ноль или уже была найдена ненулевая цифра,
            // то выводим текущую цифру
            non_zero_found = true; // Устанавливаем флаг
            if (0 <= tmp && tmp <= 9)
                std::cout << (char)(tmp + '0');
            else if (10 <= tmp && tmp <= 15)
                std::cout << (char)(tmp - 10 + 'a');
        }

        k -= 4;

        if (k < 0) // Если смещение стало отрицательным, сбросить его и перейти к предыдущему коэффициенту
        {
            k = BASE_SIZE - 4;
            j--;
        }
    }
    if (!non_zero_found) // Если ненулевая цифра не была найдена, значит число ноль, вывести "0"
        std::cout << '0';

    std::cout << std::endl;
}


// Перегрузка оператора сложения +
Big_Number Big_Number::operator+(const Big_Number &bn) {
    // Определение длин чисел
    int n = this->len;
    int m = bn.len;
    int max_len = std::max(n, m) + 1; // учитываем дополнительный разряд для переноса

    // Создание объекта для результата
    Big_Number result(max_len);

    // Инициализация переменной для переноса
    DBASE carry = 0;

    // Сложение разрядов
    for (int j = 0; j < max_len; ++j) {
        // Получение текущих цифр из двух чисел и при необходимости переноса
        DBASE uj = (j < n ? this->coef[j] : 0);
        DBASE vj = (j < m ? bn.coef[j] : 0);

        // Сложение текущих цифр с учетом переноса
        DBASE tmp = uj + vj + carry;

        // Присваивание результату текущего разряда
        result.coef[j] = tmp & std::numeric_limits<BASE>::max();

        // Обновление значения переноса
        carry = tmp >> BASE_SIZE;
    }

    // Устанавливаем длину результата
    result.len = max_len;

    return result;
}

// Перегрузка оператора +=
Big_Number& Big_Number::operator+=(const Big_Number &bn) {
    // Определение длин чисел
    int n = this->len;
    int m = bn.len;
    int max_len = std::max(n, m) + 1; // учитываем дополнительный разряд для переноса

    // Инициализация переменной для переноса
    DBASE carry = 0;

    // Сложение разрядов
    for (int j = 0; j < max_len; ++j) {
        // Получение текущих цифр из двух чисел и при необходимости переноса
        DBASE uj = (j < n ? this->coef[j] : 0);
        DBASE vj = (j < m ? bn.coef[j] : 0);

        // Сложение текущих цифр с учетом переноса
        DBASE tmp = uj + vj + carry;

        // Присваивание текущему разряду суммы
        this->coef[j] = tmp & std::numeric_limits<BASE>::max();

        // Обновление значения переноса
        carry = tmp >> BASE_SIZE;
    }

    // Если был перенос за пределы максимальной длины, увеличиваем длину объекта
    if (carry > 0 && this->len < max_len)
        this->len = max_len;

    return *this;
}
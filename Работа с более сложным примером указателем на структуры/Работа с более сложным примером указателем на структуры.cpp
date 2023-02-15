#include <iostream>
#include <Windows.h>
using namespace std;
// объявим структуру
struct elem
{

	elem* next; // ссылка на следующий элемент (это адрес. возможно, пустой - NULL)
	char Zdanie[10];
	int count_of_etagey; // количество этажей в здании
	int count_of_audiense; // количество ауд. на здание 
	double srednee_na_etag;
};

int GetCount(elem* start)
{
	int result = 0;
	bool success = 0;
	if (start != NULL) {
		success = 1;
	}
	if (success)
	{
		result++;
	}
	return result;
}



void Menu() {

	cout << endl;

	cout << "ПУНКТЫ МЕНЮ" << endl;

	cout << "1. Ввести здания " << endl;
	cout << "2. Вывести здания " << endl;
	cout << "3. Добавление здания по номеру " << endl;
	cout << "4. Удаление здания по номеру " << endl;
	cout << "5. Удаление всех зданий " << endl;
	cout << "6. Вывод списка у кого есть имя и меньше сред знач " << endl;
	cout << "7. Длина списка " << endl;
	cout << "8. Выход" << endl;


	cout << "Введите номер пункта, который вам нужен" << endl;
}
int proverka_Menu(int x) {

	if ((x > 0) && (x <= 10)) {
		return x;
	}
	else {

		while ((x <= 0) || (x >= 10)) {
			cout << "Неверный пункт меню" << endl;
			cout << "Введите пункт меню" << endl;
			cin >> x;
		}

		return x;
	}

}


// Дано: ссылка на начало списка, номер желаемого элемента, адрес найденного элемента. Ответ: достали или нет (успех/неудача извлечения элемента)
bool GetLinkToElementNumber(elem* start, int index, elem*& result/*это ссылка на переменную, которую метод должен заполнить*/)
// main передаст в этот метод(функцию) ПО ССЫЛКЕ (&) переменную result типа "указатель на elem". Этот метод заполнит указатель, и main получит его по ссылке по окончании метода GetLinkToElementNumber
// Если передать elem* result, то создастся копия переданного значения, и функция изменит копию => main не увидит изменений в result
// Как раз start передаётся как копия: на бумажке записали адрес, по кот.нужно что-то проверить, и отдали записку в функцию (тут main не ожидает изменений значения start)
{
	result = NULL; // пока что элемент не найден => адрес пуст
	bool success = start != NULL; // если указатель на начало списка не пуст, то есть с чем работать
	if (success)
	{
		// Пусть текущая ссылка - current
		elem* current = start; // это текущая ссылка

		// она пока что совпадает со ссылкой start -- ссылка на структуру (4 Байта - адрес, а в 64-битной ОС - 8Б)

		for (int i = 0; i < index; i++)
		{
			if (current->next != NULL) // если в структуре, которая (вон там, по адресу, хранимому в current), в поле next
										 // лежит НЕ пустой адрес, то мы заменяем адрес в переменной current на найденный (то есть
										 // продвигаемся по ссылке вперёд на одно звено цепи => теперь у нас новый текущий элемент по адресу current)
			// второй вариант того же условия: if ((*current).next != NULL)
			{
				// Достаём следующую ссылку (след.звено нашей цепи):
				// 1) прошли по адресу, хранящемуся в current: (*current) , дошли до значения (самой структуры)"
				// 2) дошли до структуры, достали из неё поле next - это ссылка
				// 3) сохранили ссылку в поле типа ссылка (типы current и next совпадают)
				current = (*current).next;
				// типы current и next совпадают
			}
			else
			{
				// если же там лежит пустой адрес, то мы не дойдём до искомого элемента по номеру, их не хватает => неудача
				success = false;
				break;
			}
		}
		if (success) // всё ещё не было ошибки
		{
			// заполняем переменную result типа указатель: кладём туда указатель
			result = current; // ссылка, которую мы нашли
		}
	}
	return success; // если не удалось, то в result будет NULL, иначе в result будет ссылка на найденный элемент

	/* Пример:
	Элементы: start -> 10 -> 20 -> 30 -> 40
	Их номера: -- 0 -- 1 -- 2 -- 3

	start - это адрес начального элемента - структуры, где 10

	Хранение: (адрес элемента с 10) -> {10, (адрес элемента с 20)} -> {20, (адрес элемента с 30)} -> {30, (адрес элемента с 40)} -> {40, NULL(пустой адрес)}

	Если нужна ссылка на 3й элемент, нужно пройти 3 шага из точки старта:
	0) дойти (вон туда) до 0го элемента, взять из него ссылку на 1й
	1) дойти (вон туда) до 1го элемента, взять из него ссылку на 2й
	2) дойти (вон туда) до 2го элемента, взять из него ссылку на 3й
	это она

	В примере мы сделали три шага, номер шага от 0 до 2, 2 = 3-1
	=> for (int i = 0; i < index; i++)
	*/
}

void Del(elem*& start, int* IndexOfLastElement)
{
	int n;
	elem* buff;
	elem* current1;
	cout << "Номер удаляемого эл-та: ";
	cin >> n;
	bool res = false;
	if (n == 0) // не существует элемент номер (n-1)
	{
		if (start != NULL)
		{
			buff = (*start).next;
			delete start;
			start = buff;
			(*IndexOfLastElement)--;
			res = true;
		}
	}
	else
	{
		bool f = GetLinkToElementNumber(start, n, current1);
		bool f3 = GetLinkToElementNumber(start, n - 1, buff);


		if (f && f3)
		{
			buff->next = current1->next;
			delete current1;
			(*IndexOfLastElement)--;
			res = true;
		}
	}
}



int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int Punkt_menu;
	int N = 0; // количество зданий 
	int IndexOfLastElement = 0;
	double sum = 0;
	double count_of_all_etag = 0;
	double all_srednee = 0;
	int z = 0;
	int u = 0;
	// это указатель на начало списка элементов
	elem* start; // сейчас (start - мусор), а если записать start = NULL, то список указывает в пустоту

	elem* thisisastruct = new elem; // выделяем память в области динамической памяти (в куче) 1шт

	thisisastruct->next = NULL; //пустой адрес: за этим элементом нет следующего

	start /*значение в (переменной типа ссылка)*/ = thisisastruct /* (значение типа ссылка)*/; // итог: две перменные хранят один и тот же адрес (смотрят на одну и ту же запись)

	elem* current = NULL; // это ТЕКУЩИЙ элемент
	// Выделяем память для current, чтобы передать внутрь метода GetLinkToElementNumber адрес, ПО КОТОРОМУ нужно положить ответ
	elem* new_current = NULL;
	do {

		Menu();
		cout << "Введите пункт меню" << endl;
		cin >> Punkt_menu;
		Punkt_menu = proverka_Menu(Punkt_menu);
		switch (Punkt_menu)
		{
		case 1: {
			cout << "Введите количество зданий" << endl;
			cin >> N;

			for (int i = 1; i <= N; i++)
			{
				elem* MemoryWhichExistsOnlyInThisStepOfCycle = new elem;
				(*MemoryWhichExistsOnlyInThisStepOfCycle).next = NULL;
				cout << "Введите имя для здания" << endl;

				//cin.getline((*MemoryWhichExistsOnlyInThisStepOfCycle).Zdanie, 10,' '); // 
				cin >> (*MemoryWhichExistsOnlyInThisStepOfCycle).Zdanie;
				cout << "Введите количество аудиторий в здании" << endl;
				cin >> (*MemoryWhichExistsOnlyInThisStepOfCycle).count_of_audiense; // 


				cout << "Введите количество этажей в здании" << endl;
				cin >> (*MemoryWhichExistsOnlyInThisStepOfCycle).count_of_etagey;

				(*MemoryWhichExistsOnlyInThisStepOfCycle).srednee_na_etag = (*MemoryWhichExistsOnlyInThisStepOfCycle).count_of_audiense / (*MemoryWhichExistsOnlyInThisStepOfCycle).count_of_etagey;

				sum += (*MemoryWhichExistsOnlyInThisStepOfCycle).count_of_audiense;
				count_of_all_etag += (*MemoryWhichExistsOnlyInThisStepOfCycle).count_of_etagey;


				all_srednee = sum / count_of_all_etag;

				bool f = GetLinkToElementNumber(start, IndexOfLastElement, current);


				// на 1м шаге f == start
				if (!f)
				{
					// что-то произошло, элемент не найден, напишем об этом в cout
					cout << "Не удалось получить ссылку на элемент!\n";
					system("pause");
					break;
				}
				else
				{


					// в поле next от записи, которая (по адресу MemoryWhichExistsInCycleAndAfterCycle), записать адрес новой записи
					(*current).next = MemoryWhichExistsOnlyInThisStepOfCycle;
					IndexOfLastElement++;
				}


				// вызов функции, которая достанет адрес (i-1)го элемента списка: MemoryWhichExistsInCycleAndAfterCycle

			}


			break;
		}
		case 2: {
			if (IndexOfLastElement > 0) {
				for (int i = 1; i <= IndexOfLastElement; i++)
				{
					bool f = GetLinkToElementNumber(start, i, current);

					if (current == NULL || !f) {
						cout << "Не удалось получить ссылку на элемент!\n";
						system("pause");
						break;

					}
					else
					{
						cout << "Извлекаю элемент №\t" << i << " со значениями: кол-во аудиторий, кол-во этажей, Имя" << endl;
						cout << current->count_of_audiense << endl << current->count_of_etagey << endl << current->Zdanie << endl;
					}
					// на 1м шаге f == start


					// вызов функции, которая достанет адрес (i-1)го элемента списка: MemoryWhichExistsInCycleAndAfterCycle

				}
			}
			else
			{
				cout << "Не удалось получить ссылку на элемент!\n";
				system("pause");
				break;
			}
			break;
		}
		case 3: {
			int n;
			elem* buff = new elem;
			cout << "Номер добавленного эл-та: ";
			cin >> n;
			cout << "Добавленный эл-т: Введите кол-во аудиторий, кол-во этажей, Имя";
			cin >> buff->count_of_audiense;
			sum += buff->count_of_audiense;

			cin >> buff->count_of_etagey;

			cin.getline(buff->Zdanie, 10, ' ');
			if (n <= 0) // не существует элемент номер (n-1)
			{
				cout << "Неверное значение" << endl;
			}
			else
			{
				bool f = GetLinkToElementNumber(start, n - 1, current);
				//bool f3 = GetLinkToElementNumber(start, n - 1 , buff1);


				if (f)//&& f3)
				{
					buff->next = current->next;
					IndexOfLastElement++;
					current->next = buff;
					cout << "Элемент добавлен!\n";
				}

				for (int i = IndexOfLastElement; i >= 1; i--) {
					bool f = GetLinkToElementNumber(start, i, current);
					if (!f)
					{
						// что-то произошло, элемент не найден, напишем об этом в cout
						cout << "Не удалось получить ссылку на элемент!\n";
						system("pause");
						break;
					}
					else
					{

						if ((*current).count_of_etagey != NULL && (*current).count_of_audiense != NULL && (*current).Zdanie != NULL)
						{
							cout << ", элемент № " << i << "  " <<
								(*current).count_of_audiense << "	 " << (*current).count_of_etagey << "	" << (*current).Zdanie << "\n\n";

						}
						else
						{
							cout << ", элемент № " << i << " Не существует (NULL)\n\n";
						}
					}

				}
			}break;
		}
		case 4: {
			Del(start, &IndexOfLastElement);
			break;
		}
		case 5: {

			bool f2;
			for (int j = IndexOfLastElement; j > 0; j--)
			{
				// чистить память нужно от каждого адреса
				f2 = GetLinkToElementNumber(start, j, current); // повторно используем переменную current
				if (!f2)
				{
					// что-то произошло, элемент не найден, напишем об этом в cout
					cout << "Не удалось получить ссылку на элемент!\n";
					system("pause");
					break;
				}
				else
				{
					delete current;
					cout << "очищена запись\n";
				}
			}
			IndexOfLastElement = 0;
			break;
		}
		case 6: {

			if (IndexOfLastElement > 0) {
				for (int i = 1; i <= IndexOfLastElement; i++)
				{
					bool f = GetLinkToElementNumber(start, i, current);
					/*cout << sum << endl;
					cout << count_of_all_etag << endl;
					cout << all_srednee << endl;*/


					if (strcmp(current->Zdanie, "\n")) {

						if (all_srednee > current->srednee_na_etag) {




							if (current == NULL || !f) {
								cout << "Не удалось получить ссылку на элемент!\n";
								system("pause");
								break;

							}
							else
							{
								u++;
								new_current = current;

								cout << "Извлекаю элемент №\t" << u << " со значениями: кол-во аудиторий, кол-во этажей, Имя" << endl;
								cout << new_current->count_of_audiense << endl << new_current->count_of_etagey << endl << new_current->Zdanie << endl;
							}
							// на 1м шаге f == start
						}
					}


				}
			}
			else
			{
				cout << "КОНЕЦ!\n";
				system("pause");
				break;
			}
			break;
		}
		case 7: {
			int z1 = 0;
			for (int i = 1; i <= IndexOfLastElement; i++)
			{
				if (IndexOfLastElement > 0) {
					bool f = GetLinkToElementNumber(start, i, current);
					z += GetCount(current);
				}
			}
			for (int i = 1; i <= u; i++)
			{
				if (u > 0) {
					bool f = GetLinkToElementNumber(start, i, new_current);
					z1 += GetCount(new_current);
				}
			}

			cout << "Количество всех элементов -> " << z << endl;
			cout << "Количество всех элементов доп условия -> " << z1 << endl;
			break;
		}
		}


		cout << " Готово!\n";
	} while (Punkt_menu != 8);
	system("pause");
	return 0;

}


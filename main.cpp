#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>


using namespace std;

struct CW
{
	char a;
	int b;
};
char Upp_1(char a) {
	if(a >= 'а' && a <= 'я')
		return a - 32;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);

	vector <string> text;
	vector <CW> Letters;
	vector <string> outtext;


	ifstream txt("input.txt");
	ofstream bb("output.txt");
	char WORD[25];

	while (!txt.eof())
	{
		txt >> WORD;
		text.push_back(WORD);
		
	}

	int count = 0;
	int x = 0;
	int y = 0;
	string a;
	string b;

	for (int x = 0; x < text.size(); x++) //Тут считаются для вектора Letters буквы,т.е. какие именно пристутствуют и в каком количестве, связываю их с помощью struct CW
	{
		a = text[x];
		count = 0;
		for (int i = 0; i < a.size(); i++)
		{
			for (int y = 0; y < text.size(); y++)
			{
				b = text[y];
				for (int j = 0; j < b.size(); j++)
				{
					if (a[i] == b[j])
					{
						count++;
					}
				}
			}
			CW z;
			z.a = a[i];
			z.b = count;
			Letters.push_back(z);
			count = 0;
		}
	}
	
	for (int z = 0; z < Letters.size(); z++) {  //Удаляю повторы букв, делаю их уникальными
		for (int x = 0; x < Letters.size() - 1; x++) {
			for (int y = x + 1; y < Letters.size(); y++)
			{
				if (Letters[x].a == Letters[y].a)
				{
					auto i = Letters.cbegin();
					Letters.erase(i + y);
				}
			}
		}
	}
	
	for (int x = 0; x < Letters.size() - 1; x++) { //Отсортировываю по убыванию 
		for (int y = x + 1; y < Letters.size(); y++)
		{
			if (Letters[x].b < Letters[y].b) {
				swap(Letters[x], Letters[y]);
			}
		}
	}
	auto i = Letters.cbegin();//Удаляю лишние значения, по условию должно быть 8 самых часто встречабщихся букв
	Letters.erase(i + 8, Letters.cend());

	for (int x = 0; x < text.size(); x++)
	{
		string a = text[x];
		string b;
		int count = 0;
		for (int y = 0; y < a.size(); y++)
		{
			for (int z = 0; z < 8; z++)
			{
				if (char(a[y]) == char(Letters[z].a))//Проверяю букву из слова на наличие её в Letters
				{
					count++;
				}
			}
		}
		if ((y == a.size()) - 1 and (count >= 5))//По условию проверяю на наличие этих букв в слове
		{
			string b = to_string(count);
			string c = '(' + b + ')';
			for (int x1 = 0; x1 < a.size(); x1++) {
				for (int z1 = 0; z1 < 8; z1++) {
					if (char(a[x1]) == char(Letters[z1].a)) {
						a[x1] = char(a[x1] - 32);
					}
				}
			}
			a.append(c);
			outtext.push_back(a);
		}
		else
		{
			outtext.push_back(text[x]);
		}
		count = 0;
	}

	for (int x = 0; x < outtext.size(); x++)
		bb << outtext[x] << " ";

	std::cout << "Слова в файле" << endl;
}


#include<iostream>
using namespace std;

int main()
{
	int yukseklik;
	bool a = true;
	while(a==true)
	{
		cout << "yukseklik: "; cin >> yukseklik;
		if (yukseklik <= 8 && yukseklik >= 1)
		{
			a = false;
			for (int i = 0; i < yukseklik; i++)
			{
				for (int j = 0; j < yukseklik - (i + 1); j++)
				{
					cout << " ";
				}
				for (int j = 0; j < i + 1; j++)
				{
					cout << "#";
				}
				cout << "  ";

				for (int j = 0; j < i + 1; j++)
				{
					cout << "#";
			     }
				cout << endl;
			}
		}
		
	}
}
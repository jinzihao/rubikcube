#include <iostream>
#include <fstream>
using namespace std;
void output(int x);
void newline();

int main()
{
	int i;
	int x;
	char c[55];
	//initialize output file
	ofstream fout("cube.txt");  
	fout.close();
	cout<<"�밴˳���������ҡ��ϡ��¡�ǰ���������ɫ"<<endl; 
	cout<<"..����..|..����..|..����..|..����..|..ǰ��..|..����..|"<<endl;
	cin>>c;
	for (i=0;i<54;i++)
	{
		if (c[i]=='r')
		{
			 x=1;
		}
		else if (c[i]=='g')
		{
			 x=2;
		}
		else if (c[i]=='w')
		{
			 x=3;
		}
		else if (c[i]=='y')
		{
			 x=4;
		}
		else if (c[i]=='b')
		{
			 x=5;
		}
		else if (c[i]=='o')
		{
			 x=6;
		}
		output(x);
		if (i%9==8)
		{
			newline();
		}
	}
}

void output(int x)
{
	ofstream fout("cube.txt", ios::out | ios::app);  
	fout<<x<<" ";
	fout.close();
}

void newline()
{
	ofstream fout("cube.txt", ios::out | ios::app);  
	fout<<endl;
	fout.close();
}

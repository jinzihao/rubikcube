#include <iostream>
#include <fstream>
using namespace std;
void output(int x);
void newline();

int main()
{
	int i;
	int x;
	char c;
	//initialize output file
	ofstream fout("cube.txt");  
	fout.close();
	for (i=1;i<55;i++)
	{
		if (i==1)
		{
			cout<<"����������"<<endl;
		}
		else if (i==10)
		{
			cout<<"����������"<<endl;
		}
		else if (i==19)
		{
			cout<<"����������"<<endl;
		}
		else if (i==28)
		{
			cout<<"����������"<<endl;
		}
		else if (i==37)
		{
			cout<<"������ǰ��"<<endl;
		}
		else if (i==46)
		{
			cout<<"���������"<<endl;
		}
		cin>>c; 
		if (c=='r')
		{
			 x=1;
		}
		else if (c=='g')
		{
			 x=2;
		}
		else if (c=='w')
		{
			 x=3;
		}
		else if (c=='y')
		{
			 x=4;
		}
		else if (c=='b')
		{
			 x=5;
		}
		else if (c=='o')
		{
			 x=6;
		}
		output(x);
		if (i%9==0)
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

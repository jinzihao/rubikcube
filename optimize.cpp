#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
	if (argc==2||1)
	{
		int i=0,j;
		char lines[4][5]={"","","",""};
		ifstream fin("solution.txt");
		ofstream fout("solution_optimized.txt");
		while(!fin.eof())
		{
			if (strcmp(lines[3],"")!=0)
			{
				fout<<lines[3]<<endl;
			}
			for (j=3;j>0;j--)
			{
				strncpy(lines[j],lines[j-1],4);
			}
			fin>>lines[0];
			if( ( strcmp(lines[0],lines[1])||strcmp(lines[1],lines[2])||strcmp(lines[2],lines[3]) ) == false)
			{
				for (j=0;j<4;j++)
				{
					strncpy(lines[j],"",4);
				}
			}
			else if( ((strcmp(lines[1],lines[2])||strcmp(lines[2],lines[3])) == false) && (strcmp(lines[1],"")||strcmp(lines[2],"")||strcmp(lines[3],""))==true )
			{
				for (j=2;j<4;j++)
				{
					strncpy(lines[j],"",4);
				}
				strcat(lines[1],"i");
			}
		}
		//在eof之后再处理一次 
		if( ( strcmp(lines[0],lines[1])||strcmp(lines[1],lines[2])||strcmp(lines[2],lines[3]) ) == false)
		{
			for (j=0;j<4;j++)
			{
				strncpy(lines[j],"",4);
			}
		}
		else if( ((strcmp(lines[1],lines[2])||strcmp(lines[2],lines[3])) == false) && (strcmp(lines[1],"")||strcmp(lines[2],"")||strcmp(lines[3],""))==true )
		{
			for (j=2;j<4;j++)
			{
				strncpy(lines[j],"",4);
			}
			strcat(lines[1],"i");
		}
		for (i=3;i>0;i--)
		{
			if (strcmp(lines[i],"")!=0)
			{
				fout<<lines[i]<<endl;
			}
		}
	}
	else
	{
		cout<<"Usage: optimize.exe <filename>"<<endl;
	}
}

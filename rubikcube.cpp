#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
int cube[7][4][4]; //Store colors: 6 faces，3 lines，3 columns; red=1, orange=6, green=2, blue=5, white=3, yellow=4
void L(); //Left - clockwise 90° 
void R(); //Right - clockwise 90° 
void U(); //Up - clockwise 90° 
void D(); //Down - clockwise 90° 
void F(); //Front - clockwise 90° 
void B(); //Back - clockwise 90° 
void chainswap(int &a, int &b, int &c, int &d); //a,b,c,d -> d,a,b,c
void chainswapi(int &a, int &b, int &c, int &d); //a,b,c,d -> b,c,d,a
int validatecube(); 
int min(int a, int b);
int max(int a, int b);
int validateside(); 
int validatecorner(); 
void swap (int &a, int &b);
void rotatexy();
void rotatexz();
void rotateyz();

int main(int argc, char *argv[])
{
	int i,j,k,r;
	if (argc==2)
	{
		ifstream fin(argv[1]);
		for (i=1;i<7;i++)
		{
			for (j=1;j<4;j++)
			{
				for (k=1;k<4;k++)
				{
					fin>>cube[i][j][k];
				} 
			}
		} 
		r=validatecube(); //Preprocess: validate
		if(r) 
		{ 
			printf("Invalid cube, error number:%d",r); 
		}
		else
		{
			
		}
	}
	else
	{
		cout<<"Usage: rubikcube <filename> "<<endl;
	}
	return 0;
}

void chainswap(int &a, int &b, int &c, int &d) //a,b,c,d -> d,a,b,c
{
	int s;
	s=d;
	d=c;
	c=b;
	b=a;
	a=s;	
}

void L() //20次变换，5组chainswap 
{
	//面内变换 
	chainswap(cube[1][1][1],cube[1][1][3],cube[1][3][3],cube[1][3][1]);
	chainswap(cube[1][1][2],cube[1][2][3],cube[1][3][2],cube[1][2][1]);
	//其他面的变换 
	chainswap(cube[3][1][1],cube[5][1][1],cube[4][1][1],cube[6][3][3]);
	chainswap(cube[3][2][1],cube[5][2][1],cube[4][2][1],cube[6][2][3]);
	chainswap(cube[3][3][1],cube[5][3][1],cube[4][3][1],cube[6][1][3]);
}

void R() //20次变换，5组chainswap 
{
	//面内变换 
	chainswap(cube[2][1][1],cube[2][1][3],cube[2][3][3],cube[2][3][1]);
	chainswap(cube[2][1][2],cube[2][2][3],cube[2][3][2],cube[2][2][1]);
	//其他面的变换 
	chainswap(cube[3][3][3],cube[6][1][1],cube[4][3][3],cube[5][3][3]);
	chainswap(cube[3][2][3],cube[6][2][1],cube[4][2][3],cube[5][2][3]);
	chainswap(cube[3][1][3],cube[6][3][1],cube[4][1][3],cube[5][1][3]);
}

void U() //20次变换，5组chainswap 
{
	//面内变换 
	chainswap(cube[3][1][1],cube[3][1][3],cube[3][3][3],cube[3][3][1]);
	chainswap(cube[3][1][2],cube[3][2][3],cube[3][3][2],cube[3][2][1]);
	//其他面的变换 
	chainswap(cube[1][1][1],cube[6][1][1],cube[2][1][1],cube[5][1][1]);
	chainswap(cube[1][1][2],cube[6][1][2],cube[2][1][2],cube[5][1][2]);
	chainswap(cube[1][1][3],cube[6][1][3],cube[2][1][3],cube[5][1][3]);
}

void D() //20次变换，5组chainswap 
{
	//面内变换 
	chainswap(cube[4][1][1],cube[4][1][3],cube[4][3][3],cube[4][3][1]);
	chainswap(cube[4][1][2],cube[4][2][3],cube[4][3][2],cube[4][2][1]);
	//其他面的变换 
	chainswap(cube[5][3][1],cube[2][3][1],cube[6][3][1],cube[1][3][1]);
	chainswap(cube[5][3][2],cube[2][3][2],cube[6][3][2],cube[1][3][2]);
	chainswap(cube[5][3][3],cube[2][3][3],cube[6][3][3],cube[1][3][3]);
}

void F() //20次变换，5组chainswap 
{
	//面内变换 
	chainswap(cube[5][1][1],cube[5][1][3],cube[5][3][3],cube[5][3][1]);
	chainswap(cube[5][1][2],cube[5][2][3],cube[5][3][2],cube[5][2][1]);
	//其他面的变换 
	chainswap(cube[3][3][1],cube[2][1][1],cube[4][1][3],cube[1][3][3]);
	chainswap(cube[3][3][2],cube[2][2][1],cube[4][1][2],cube[1][2][3]);
	chainswap(cube[3][3][3],cube[2][3][1],cube[4][1][1],cube[1][1][3]);
}

void B() //20次变换，5组chainswap 
{
	//面内变换 
	chainswap(cube[6][1][1],cube[6][1][3],cube[6][3][3],cube[6][3][1]);
	chainswap(cube[6][1][2],cube[6][2][3],cube[6][3][2],cube[6][2][1]);
	//其他面的变换 
	chainswap(cube[3][1][3],cube[1][1][1],cube[4][3][1],cube[2][3][3]);
	chainswap(cube[3][1][2],cube[1][2][1],cube[4][3][2],cube[2][2][3]);
	chainswap(cube[3][1][1],cube[1][3][1],cube[4][3][3],cube[2][1][3]);
}

int validatecube()
{
	int i,j,k;
	int status=0;
	int color[7]={0,0,0,0,0,0,0};
	for (i=1;i<7;i++)
	{
		for (j=1;j<4;j++)
		{
			for (k=1;k<4;k++)
			{
				if (cube[i][j][k]>6 || cube[i][j][k]<1)
				{
					status=1; //bit 0: invalid color
				}
				else
				{
					color[cube[i][j][k]]+=1; //color count
				}
			}
		}
	}
	for (i=1;i<7;i++)
	{
		if (color[i]!=9)
		{
			status+=2; //bit 1: color count incorrect
			break;
		}
	} 
	for (i=1;i<6;i+=2)
	{
		if (cube[i][2][2]+cube[i+1][2][2]!=7)
		{
			status+=4; //bit 2: invalid center piece
			break;
		}
	}	
	status+=validateside();
	status+=validatecorner();
	return status;
}

int min(int a, int b)
{
	return a<b?a:b; 
} 

int max(int a, int b)
{
	return a>b?a:b;
}

int geteigenvalue2(int a, int b)
{
	return min(a,b)+max(a,b)*7; 
} 

int geteigenvalue3(int a, int b, int c)
{
	int colors[3];
	int i,j;
	colors[0]=a;
	colors[1]=b;
	colors[2]=c;
	for (i=0;i<3;i++)
	{
		for (j=i;j<3;j++)
		{
			if (colors[i]>colors[j])
			{
				swap(colors[i],colors[j]);
			}
		}
	}
	return colors[0]+colors[1]*7+colors[2]*49;
} 

int validateside()
{
	int result[49];
	int i,j,e=0;
	for (i=0;i<50;i++)
	{
		result[i]=0;
	}
	result[geteigenvalue2(cube[3][1][2],cube[6][1][2])]+=1;
	result[geteigenvalue2(cube[3][2][1],cube[1][1][2])]+=1;
	result[geteigenvalue2(cube[3][2][3],cube[2][1][2])]+=1;
	result[geteigenvalue2(cube[3][3][2],cube[5][1][2])]+=1;
	result[geteigenvalue2(cube[1][2][1],cube[6][2][3])]+=1;
	result[geteigenvalue2(cube[1][2][3],cube[5][2][1])]+=1;
	result[geteigenvalue2(cube[5][2][3],cube[2][2][1])]+=1;
	result[geteigenvalue2(cube[2][2][3],cube[6][2][1])]+=1;
	result[geteigenvalue2(cube[4][3][2],cube[6][3][2])]+=1;
	result[geteigenvalue2(cube[4][2][1],cube[1][3][2])]+=1;
	result[geteigenvalue2(cube[4][2][3],cube[2][3][2])]+=1;
	result[geteigenvalue2(cube[5][3][2],cube[4][1][2])]+=1;
	for (i=1;i<7;i++)
	{
		for (j=i+1;j<7;j++)
		{
			e=i+j*7;
			if ( (e!=43) && (e!=37) && (e!=31) )
			{
				if (result[e]!=1)
				{
					return 8; //bit 3: invalid side piece 
				}
			}
			else
			{
				if (result[e]!=0)
				{
					return 8; //bit 3: invalid side piece 
				}
			}
		}
	}
	return 0;
}

int validatecorner()
{
	int result[343];
	int i,j,k,e=0;
	for (i=0;i<344;i++)
	{
		result[i]=0;	
	}
	result[geteigenvalue3(cube[5][1][1],cube[1][1][3],cube[3][3][1])]+=1;
	result[geteigenvalue3(cube[5][1][3],cube[2][1][1],cube[3][3][3])]+=1;
	result[geteigenvalue3(cube[5][3][1],cube[1][3][3],cube[4][1][1])]+=1;
	result[geteigenvalue3(cube[5][3][3],cube[4][1][3],cube[2][3][1])]+=1;
	result[geteigenvalue3(cube[1][1][1],cube[3][1][1],cube[6][1][3])]+=1;
	result[geteigenvalue3(cube[1][3][1],cube[4][3][1],cube[6][3][3])]+=1;
	result[geteigenvalue3(cube[3][1][3],cube[2][1][3],cube[6][1][1])]+=1;
	result[geteigenvalue3(cube[4][3][3],cube[2][3][3],cube[6][3][1])]+=1;
	for (i=1;i<7;i++)
	{
		for (j=i;j<7;j++)
		{
			for (k=j;k<7;k++)
			{
				e=i+j*7+k*49;
				if (e==317||e==324||e==205||e==156||e==267||e==274||e==333||e==332)
				{
					if (result[e]!=1)
					{
						return 16; //bit 4: invalid corner piece 
					}
				}
				else
				{
					if (result[e]!=0)
					{
						return 16; //bit 4: invalid corner piece 
					}
				}
			}
		}
	}
	return 0;
}

void swap (int &a, int &b)
{
	int c;
	c=a;
	a=b;
	b=c;
}

void rotatexy()
{
	chainswap(cube[5][2][1],cube[2][2][1],cube[6][2][1],cube[1][2][1]);
	chainswap(cube[5][2][2],cube[2][2][2],cube[6][2][2],cube[1][2][2]);
	chainswap(cube[5][2][3],cube[2][2][3],cube[6][2][3],cube[1][2][3]);
}

void rotatexz()
{
	chainswap(cube[3][2][1],cube[2][1][2],cube[4][2][3],cube[1][3][2]);
	chainswap(cube[3][2][2],cube[2][2][2],cube[4][2][2],cube[1][2][2]);
	chainswap(cube[3][2][3],cube[2][3][2],cube[4][2][1],cube[1][1][2]);
}

void rotateyz()
{
	chainswap(cube[5][1][2],cube[3][1][2],cube[6][3][2],cube[4][1][2]);
	chainswap(cube[5][2][2],cube[3][2][2],cube[6][2][2],cube[4][2][2]);
	chainswap(cube[5][3][2],cube[3][3][2],cube[6][1][2],cube[4][3][2]);
}

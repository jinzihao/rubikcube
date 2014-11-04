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
int validatecube(); 
int min(int a, int b);
int max(int a, int b);
int validateside(); 
int validatecorner(); 
void swap (int &a, int &b);
void rotatexy();
void rotatexz();
void rotateyz();
int stage2();
void output(char message[]);
void stage2_finalize();
int stage3();
void stage3_finalize();

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
			//initialize output file
			ofstream fout("solution.txt");  
			fout.close();
			r=1;
			while(r==1)
			{
				r=stage2();
			}
			stage2_finalize(); 
			r=1;
			while(r==1)
			{
				r=stage3();
			}
			stage3_finalize();
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
	output("L");
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
	output("R");
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
	output("U");
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
	output("D");
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
	output("F");
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
	output("B");
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
				if (e==317||e==324||e==211||e==162||e==267||e==274||e==333||e==332)
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
	output("rxy");
}

void rotatexz()
{
	chainswap(cube[3][2][1],cube[2][1][2],cube[4][2][3],cube[1][3][2]);
	chainswap(cube[3][2][2],cube[2][2][2],cube[4][2][2],cube[1][2][2]);
	chainswap(cube[3][2][3],cube[2][3][2],cube[4][2][1],cube[1][1][2]);
	output("rxz");
}

void rotateyz()
{
	chainswap(cube[5][1][2],cube[3][1][2],cube[6][3][2],cube[4][1][2]);
	chainswap(cube[5][2][2],cube[3][2][2],cube[6][2][2],cube[4][2][2]);
	chainswap(cube[5][3][2],cube[3][3][2],cube[6][1][2],cube[4][3][2]);
	output("ryz");
}

int stage2()
{
	int maincolor=cube[5][2][2];
	int status=0;
	//第一步，只转视角，不影响魔方状态 
	if (cube[3][3][2]!=maincolor)
	{
		if (cube[1][2][3]==maincolor)
		{
			//xz平面顺时针转90°，化为 cube[3][3][2]==maincolor的情况 
			F();
			rotatexz();
			B();
			B();
			B();
			status=1;
		}
		else if (cube[4][1][2]==maincolor)
		{
			//xz平面顺时针转180°，化为 cube[3][3][2]==maincolor的情况 
			/*	
			F();
			rotatexz();
			B();
			B();
			B();
			F();
			rotatexz();
			B();
			B();
			B();
			*/
			//optimized version:
			F();
			F();
			rotatexy();
			rotatexz();
			B();
			B(); 
			status=1;
		}
		else if (cube[2][2][1]==maincolor)
		{
			//xz平面顺时针转270°，化为 cube[3][3][2]==maincolor的情况 
			/* 
			F();
			rotatexz();
			B();
			B();
			B();
			F();
			rotatexz();
			B();
			B();
			B();
			F();
			rotatexz();
			B();
			B();
			B();
			*/
			//optimized version:
			F();
			F();
			F();
			rotatexy();
			rotatexz();
			rotatexz();
			B();
			B(); 
			B(); 
			status=1;
		}
	}
	else
	{
		status=1; // cube[3][3][2]==maincolor，无需操作，直接记为status=1，可以进行下一步操作 
	} 
	//第二步，改变魔方状态，不影响前面十字的其他部分 
	if (status==1)
	{
		U(); //上面顺时针转90°，准备翻转到前面
		//把前面左侧三格留出空位 
		if (cube[5][3][2]!=maincolor)
		{
			F();
		}
		else if (cube[5][2][3]!=maincolor) 
		{
			F();
			F();
		}
		else if (cube[5][1][2]!=maincolor)
		{
			F();
			F();
			F();
		}
		L(); //将上面的maincolor块翻转到前面 
	}
	else //没有2类情况，（1,2,3) (3,3,2) (2,2,1) (4,1,2) 均不为maincolor，以下讨论3类情况 
	{
		//第一步，将3类情况的4种子情况化为cube[3][2][1]==maincolor的标准情况，对前面十字无影响 
		 if (cube[3][2][1]!=maincolor)
		 {
			if (cube[1][3][2]==maincolor) //xz平面顺时针转90°，化为 cube[3][2][1]==maincolor的情况 
			{
				rotatexz();
				status=1;
			}
			else if (cube[4][2][3]==maincolor) //xz平面顺时针转180°，化为 cube[3][2][1]==maincolor的情况 
			{
				rotatexz();
				rotatexz();
				status=1;
			}
			else if (cube[2][1][2]==maincolor) //xz平面顺时针转270°，化为 cube[3][2][1]==maincolor的情况 
			{
				rotatexz();
				rotatexz();
				rotatexz();
				status=1;
			}
		}
		else
		{
			status=1;
		}
		if (status==1)
		{
			//把前面左侧三格留出空位 
			if(cube[5][2][1]==maincolor)
			{ 
				if (cube[5][3][2]!=maincolor)
				{
					F();
				}
				else if (cube[5][2][3]!=maincolor) 
				{
					F();
					F();
				}
				else if (cube[5][1][2]!=maincolor)
				{
					F();
					F();
					F();
				}
			}
			L(); //将上面的maincolor块翻转到前面 
		}
		else //没有3类情况，（3,2,1) (1,3,2) (4,2,3) (2,1,2) 均不为maincolor，以下讨论4类情况 
		{
			//第一步，将4类情况的4种子情况化为cube[3][2][3]==maincolor的标准情况，对前面十字无影响 
			if (cube[3][2][3]!=maincolor)
			{
				if (cube[1][1][2]==maincolor) //xz平面顺时针转90°，化为 cube[3][2][3]==maincolor的情况 
				{
					rotatexz();
					status=1;
				}
				else if (cube[4][2][1]==maincolor) //xz平面顺时针转180°，化为 cube[3][2][3]==maincolor的情况 
				{
					rotatexz();
					rotatexz();
					status=1;
				}
				else if (cube[2][3][2]==maincolor) //xz平面顺时针转270°，化为 cube[3][2][3]==maincolor的情况 
				{
					rotatexz();
					rotatexz();
					rotatexz();
					status=1;
				}
				else
				{
					if (cube[3][1][2]==maincolor||cube[2][2][3]==maincolor||cube[4][3][2]==maincolor||cube[1][2][1]==maincolor) //4.5类情况，可以化为在对前面无影响的情况下化为4类情况 
					{
						//将 (2,2,3) (4,3,2) (1,2,1)化为 (3,1,2)的标准情况 
						if (cube[2][2][3]==maincolor)
						{
							B();
						}
						else if (cube[4][3][2]==maincolor)
						{
							B();
							B();
						}
						else if (cube[1][2][1]==maincolor)
						{
							B();
							B();
							B();
						}
						//把前面上方三格留出空位 
						if (cube[5][1][2]==maincolor)
						{
							if (cube[5][2][1]!=maincolor)
							{
								F();
							}
							else if (cube[5][3][2]!=maincolor) 
							{
								F();
								F();
							}
							else if (cube[5][2][3]!=maincolor)
							{
								F();
								F();
								F();
							}
						}
						U(); //化为4类情况 	
						status=1; 
					}
				}
			}
			else
			{
				status=1;
			}
			if (status==1)
			{
				//把前面右侧三格留出空位
				if (cube[5][2][3]==maincolor)
				{
					if (cube[5][1][2]!=maincolor)
					{
						F();
					}
					else if (cube[5][2][1]!=maincolor) 
					{
						F();
						F();
					}
					else if (cube[5][3][2]!=maincolor)
					{
						F();
						F();
						F();
					}
				}
				R(); //将上面的maincolor块翻转到前面 
				R(); 
				R(); 
			}
			else //没有4类和4.5类情况，(3,2,3) (1,1,2) (4,2,1) (2,3,2) (3,1,2) (1,2,1) (4,3,2) (2,2,3) 均不为maincolor，以下讨论5类情况 
			{
				//第一步，将5类情况的4种子情况化为cube[6][2][3]==maincolor的标准情况，对前面十字无影响 
				if (cube[6][1][2]==maincolor)
				{
					B();
					status=1;
				}
				else if (cube[6][2][1]==maincolor)
				{
					B();
					B();
					status=1;
				}
				else if (cube[6][3][2]==maincolor)
				{
					B();
					B();
					B();
					status=1;
				}
				if (status==1)
				{
					//把前面左侧三格留出空位 
					if(cube[5][2][1]==maincolor)
					{
						if (cube[5][3][2]!=maincolor)
						{
							F();
						}
						else if (cube[5][2][3]!=maincolor) 
						{
							F();
							F();
						}
						else if (cube[5][1][2]!=maincolor)
						{
							F();
							F();
							F();
						}
					}
					L(); //将上面的maincolor块翻转到前面 
					L();
				}
			}
		}
	}
	return status;
}

void stage2_finalize() //finalize to match goal 2 
{
	if (cube[3][3][2]==cube[1][2][2])
	{
		rotatexz();
	}
	else if (cube[3][3][2]==cube[4][2][2])
	{
		rotatexz();
		rotatexz();
	}
	else if (cube[3][3][2]==cube[2][2][2])
	{
		rotatexz();
		rotatexz();
		rotatexz();
	}
}

void output(char message[])
{
	ofstream fout("solution.txt", ios::out | ios::app);  
	fout<<message<<endl;
	fout.close();
}

int stage3()
{
	int maincolor=cube[5][2][2];
	int status=0;
	if(cube[3][1][1]!=maincolor) //4类情况，将213,433,131,231化为311范式 
	{
		if(cube[2][1][3]==maincolor)
		{
			B();
			status=1;
		}
		else if(cube[4][3][3]==maincolor)
		{
			B();
			B();
			status=1;
		}
		else if(cube[1][3][1]==maincolor)
		{
			B();
			B();
			B();
			status=1;
		}
	}
	else
	{
		status=1;
	}
	if(status==1) 
	{
		rotatexy(); //保护前面中间行 
		if (cube[5][3][1]==maincolor)
		{
			D(); //保护前面左下角已经到位的块
		}
		L(); //将311翻转到前面 
		rotatexy(); //恢复前面中间行 
		rotatexy();
		rotatexy();
		if (cube[2][3][1]==maincolor)
		{
			D(); //恢复前面左下角已经到位的块
			D();
			D();
		}
	}
	else //如果不是4类情况 
	{
		if(cube[3][1][3]!=maincolor) //5类情况，将313,233,431,111化为313范式 
		{
			if(cube[2][3][3]==maincolor)
			{
				B();
				status=1;
			}
			else if(cube[4][3][1]==maincolor)
			{
				B();
				B();
				status=1;
			}
			else if(cube[1][1][1]==maincolor)
			{
				B();
				B();
				B();
				status=1;
			}
		}
		else
		{
			status=1;
		}
		if(status==1) 
		{
			rotatexy(); //保护前面中间行 
			rotatexy();
			rotatexy();
			if (cube[5][3][3]==maincolor)
			{
				D(); //保护前面右下角已经到位的块
				D();
				D();
			}
			R(); //将313翻转到前面
			R();
			R(); 
			rotatexy(); //恢复前面中间行 
			if (cube[1][3][3]==maincolor)
			{
				D(); //恢复前面右下角已经到位的块
			}
		}
		else //如果不是5类情况 
		{
			if(cube[3][3][1]!=maincolor) //2类情况，将331,133,413,211化为331范式 
			{
				if(cube[1][3][3]==maincolor)
				{
					F();
					status=1;
				}
				else if(cube[4][1][3]==maincolor)
				{
					F();
					F();
					status=1;
				}
				else if(cube[2][1][1]==maincolor)
				{
					F();
					F();
					F();
					status=1;
				}
			}
			else
			{
				status=1;
			}
			if(status==1) //开始将331范式化为311范式 
			{
				rotatexy(); 
				D();
				L();
				rotatexy(); 
				rotatexy(); 
				rotatexy(); 
				D();
				D();
				D();
				B();
				B();
				B(); //至此将331范式化为311范式 
			}
			else //如果不是2类情况 
			{
				if(cube[3][3][3]!=maincolor) //3类情况，将333,113,411,231化为333范式 
				{
					if(cube[1][1][3]==maincolor)
					{
						F();
						status=1;
					}
					else if(cube[4][1][1]==maincolor)
					{
						F();
						F();
						status=1;
					}
					else if(cube[2][3][1]==maincolor)
					{
						F();
						F();
						F();
						status=1;
					}
				}
				else
				{
					status=1;
				}
				if(status==1) //开始将333范式化为313范式 
				{
					rotatexy(); 
					rotatexy(); 
					rotatexy(); 
					D();
					D();
					D();
					R();
					R();
					R(); 
					rotatexy(); 
					D();
					B(); //至此将331范式化为313范式 
				}
				else //如果不是2类情况 
				{
					if(cube[6][1][3]!=maincolor) //6类情况，将613,633,631,611化为613范式 
					{
						if(cube[6][3][3]==maincolor)
						{
							B();
						}
						else if(cube[6][3][1]==maincolor)
						{
							B();
							B();
						}
						else if(cube[6][1][1]==maincolor)
						{
							B();
							B();
							B();
						}
					}
					else
					{
						status=1;
					}
					if (status==1) //开始将613范式化为331范式 
					{
						if (cube[5][1][1]==maincolor) //将511腾空 
						{
							if (cube[5][3][1]!=maincolor)
							{
								F();
							}
							else if (cube[5][3][3]!=maincolor)
							{
								F();
								F();
							}
							else if (cube[5][1][3]!=maincolor)
							{
								F();
								F();
								F();
							}
						}
						rotatexy();
						D();	
						L();
						rotatexy();
						rotatexy();
						rotatexy();
						D();
						D();
						D(); //至此将613范式化为331范式 
					}
				}
			}
		}
	}
	return status;
}

void stage3_finalize()
{
	if (cube[3][3][2]==cube[1][2][2])
	{
		rotatexz();
	}
	else if (cube[3][3][2]==cube[4][2][2])
	{
		rotatexz();
		rotatexz();
	}
	else if (cube[3][3][2]==cube[2][2][2])
	{
		rotatexz();
		rotatexz();
		rotatexz();
	}
}


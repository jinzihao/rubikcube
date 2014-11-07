#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
int cube[7][4][4]; //Store colors: 6 faces��3 lines��3 columns; red=1, orange=6, green=2, blue=5, white=3, yellow=4
void L(); //Left - clockwise 90�� 
void R(); //Right - clockwise 90�� 
void U(); //Up - clockwise 90�� 
void D(); //Down - clockwise 90�� 
void F(); //Front - clockwise 90�� 
void B(); //Back - clockwise 90�� 
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
void output(char message[]);
int testcenter(int color, int face);
int testside(int color1, int color2, int face1, int face2);
int testcorner(int color1, int color2, int color3, int face1, int face2, int face3);
int cequal2(int a, int b, int x, int y);
int cexist2(int a, int x, int y, int z);
int cequal3(int a, int b, int c, int x, int y, int z);
int cexist3(int a, int x, int y, int z);
int sideexist(int color, int face1, int face2);
void output_c(char message);
void dump();
void screendump();
 
int main(int argc, char *argv[])
{
	int i,j,k,r;
	bool a,b,c,d,e,f,g,h;
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
		{ //%START% 
			//initialize output file
			ofstream fout("solution.txt");  
			fout.close();
			//�ҵ���ɫ���Ŀ鲢��ת������ 
			if (testcenter(5,3))
			{
				rotateyz();
			}
			else if (testcenter(1,3))
			{
				rotatexz();
			}
			else if (testcenter(2,3))
			{
				rotatexz();
				rotatexz();
				rotatexz();
			}
			else if (testcenter(4,3))
			{
				rotateyz();
				rotateyz();
			}
			else if (testcenter(6,3))
			{
				rotateyz();
				rotateyz();
				rotateyz();
			}
			//������ɫ����ת������
			if(testside(5,1,3,5))  
			{
				L();
			}
			else if(testside(5,2,3,5))
			{
				R();
				R();
				R();
			}
			else if(testside(5,3,3,5))
			{
				F();
				F();
			}
			else if(testside(6,1,3,5))
			{
				L();
				L();
				L();
			}
			else if(testside(6,2,3,5))
			{
				R();
			}
			else if(testside(6,3,3,5))
			{
				B();
				B();
			}
			else if(testside(1,3,3,5))
			{
				L();
				L(); 
			}
			else if(testside(2,3,3,5))
			{
				R();
				R();
			}
			//�����������ɫ����ת���Ҳ�
			if (testside(5,4,3,5))
			{
				D();
			}
			else if (testside(1,4,3,5))
			{
				D();
				D();
			}
			else if (testside(6,4,3,5))
			{
				D();
				D();
				D();
			}
			//���м����ɫ����ת���Ҳ�
			if (testcenter(5,5))
			{
				rotatexy();
			}
			else if (testcenter(1,5))
			{
				rotatexy();
				rotatexy();
			}
			else if (testcenter(6,5))
			{
				rotatexy();
				rotatexy();
				rotatexy();
			}
			//���Ҳ��������ɫ�鷭ת������
			R();
			R();
			//�������ɫ�鷴�˵Ļ�...
			if (testside(3,2,3,5)==2)
			{
				R();
				R();
				R();
				U();
				F();
				F();
				F();
				U();
				U();
				U();
			}
			//����ɫ���Ŀ������ת��ǰ�� 
			U();
			rotatexy();
			rotatexy();
			rotatexy();
			//���Ȱ�ɫ����ת������
			if(testside(5,1,3,6))  
			{
				L();
			}
			else if(testside(5,2,3,6))
			{
				R();
				R();
				R();
			}
			else if(testside(6,1,3,6))
			{
				L();
				L();
				L();
			}
			else if(testside(6,2,3,6))
			{
				R();
			}
			else if(testside(6,3,3,6))
			{
				B();
				B();
			}
			else if(testside(1,3,3,6))
			{
				L();
				L(); 
			}
			else if(testside(2,3,3,6))
			{
				R();
				R();
			}
			//������ĳȰ�ɫ����ת���Ҳ�
			if (testside(5,4,3,6))
			{
				D();
			}
			else if (testside(1,4,3,6))
			{
				D();
				D();
			}
			else if (testside(6,4,3,6))
			{
				D();
				D();
				D();
			}
			//���м�ĳ�ɫ����ת���Ҳ�
			if (testcenter(5,6))
			{
				rotatexy();
			}
			else if (testcenter(1,6))
			{
				rotatexy();
				rotatexy();
			}
			else if (testcenter(6,6))
			{
				rotatexy();
				rotatexy();
				rotatexy();
			}
			//���Ҳ���ĳȰ�ɫ�鷭ת������
			R();
			R();
			//����Ȱ�ɫ�鷴�˵Ļ�... 
			if (testside(3,2,3,6)==2)
			{
				R();
				R();
				R();
				U();
				F();
				F();
				F();
				U();
				U();
				U();
			}
			//����ɫ���Ŀ������ת��ǰ�� 
			U();
			rotatexy();
			rotatexy();
			rotatexy();
			//���̰�ɫ����ת������
			if(testside(5,2,3,2))
			{
				R();
				R();
				R();
			}
			else if(testside(6,1,3,2))
			{
				B();
			}
			else if(testside(6,2,3,2))
			{
				R();
			}
			else if(testside(6,3,3,2))
			{
				B();
				B();
			}
			else if(testside(2,3,3,2))
			{
				R();
				R();
			}
			else if(testside(5,1,3,2))
			{
				F();
				F();
				F();
				D();
				F();
			} 
			//��������̰�ɫ����ת���Ҳ�
			if (testside(5,4,3,2))
			{
				D();
			}
			else if (testside(1,4,3,2))
			{
				D();
				D();
			}
			else if (testside(6,4,3,2))
			{
				D();
				D();
				D();
			}
			//���м����ɫ����ת���Ҳ�
			if (testcenter(5,2))
			{
				rotatexy();
			}
			else if (testcenter(1,2))
			{
				rotatexy();
				rotatexy();
			}
			else if (testcenter(6,2))
			{
				rotatexy();
				rotatexy();
				rotatexy();
			}
			//���Ҳ�����̰�ɫ�鷭ת������
			R();
			R();
			//����̰�ɫ�鷴�˵Ļ�... 
			if (testside(3,2,3,2)==2)
			{
				R();
				R();
				R();
				U();
				F();
				F();
				F();
				U();
				U();
				U();
			}
			//����ɫ���Ŀ������ת��ǰ�� 
			U();
			rotatexy();
			rotatexy();
			rotatexy();
			//�����ɫ����ת������
			if(testside(5,2,3,1))
			{
				R();
				R();
				R();
			}
			else if(testside(3,2,3,1))
			{
				R();
				R();
			}
			else if(testside(6,2,3,1))
			{
				R();
			}
			else if(testside(5,1,3,1))
			{
				F();
				F();
				F();
				D();
				F();
			} 
			else if(testside(6,1,3,1))
			{
				B(); 
				D();
				B(); 
				B(); 
				B(); 
			} 
			//������ĺ��ɫ����ת���Ҳ�
			if (testside(5,4,3,1))
			{
				D();
			}
			else if (testside(1,4,3,1))
			{
				D();
				D();
			}
			else if (testside(6,4,3,1))
			{
				D();
				D();
				D();
			}
			//���м�ĺ�ɫ����ת���Ҳ�
			if (testcenter(5,1))
			{
				rotatexy();
			}
			else if (testcenter(1,1))
			{
				rotatexy();
				rotatexy();
			}
			else if (testcenter(6,1))
			{
				rotatexy();
				rotatexy();
				rotatexy();
			}
			//���Ҳ���ĺ��ɫ�鷭ת������
			R();
			R();
			//������ɫ�鷴�˵Ļ�... 
			if (testside(3,2,3,1)==2)
			{
				R();
				R();
				R();
				U();
				F();
				F();
				F();
				U();
				U();
				U();
			}
			//����ɫ���Ŀ������ת��ǰ�� 
			U();
			rotatexy();
			rotatexy();
			rotatexy();
			//����Stage2��ɣ���ʱǰ��Ϊ�죬����Ϊ��
			//�ҵ������׽ǿ飬������������ 
			if (testcorner(3,1,6,1,5,3))
			{
				L();
				L();
				L();
				D();
				D();
				D();
				L();
				D();
			}
			else if (testcorner(3,6,2,1,5,3))
			{
				R();
				D();
				R();
				R();
				R();
				D();
				D();
				D();
			}
			else if (testcorner(3,2,5,1,5,3))
			{
				R();
				R();
				R();
				D();
				D();
				D();
				R();
				D();
			}
			else if (testcorner(3,5,1,1,5,3))
			{
				L();
				D();
				L();
				L();
				L();
				D();
				D();
				D();
			}
			//������ĺ����׽ǿ��������½�
			if (testcorner(4,5,1,1,5,3))
			{
				D();
			}
			else if (testcorner(4,1,6,1,5,3))
			{
				D();
				D();
			}
			else if (testcorner(4,6,2,1,5,3))
			{
				D();
				D();
				D();
			}
			//������Ͻǿ���ɫ��λ�Ļ�... 
			while (testcorner(3,5,2,3,1,5)!=1)
			{
				R();
				R();
				R();
				D();
				D();
				D(); 
				R();
				D();
			}
			//����ɫ���Ŀ��ǰ��ת�����棬����ɫ���Ŀ�������ת��ǰ�� 
			U();
			rotatexy();
			rotatexy();
			rotatexy();
			//�ҵ����Ȱ׽ǿ飬������������ 
			if (testcorner(3,1,6,5,6,3))
			{
				L();
				L();
				L();
				D();
				D();
				D();
				L();
				D();
			}
			else if (testcorner(3,6,2,5,6,3))
			{
				R();
				D();
				R();
				R();
				R();
				D();
				D();
				D();
			}
			else if (testcorner(3,2,5,5,6,3))
			{
				R();
				R();
				R();
				D();
				D();
				D();
				R();
				D();
			}
			//����������Ȱ׽ǿ��������½�
			if (testcorner(4,5,1,5,6,3))
			{
				D();
			}
			else if (testcorner(4,1,6,5,6,3))
			{
				D();
				D();
			}
			else if (testcorner(4,6,2,5,6,3))
			{
				D();
				D();
				D();
			}
			//������Ͻǿ���ɫ��λ�Ļ�... 
			while (testcorner(3,5,2,3,5,6)!=1)
			{
				R();
				R();
				R();
				D();
				D();
				D(); 
				R();
				D();
			}
			//����ɫ���Ŀ��ǰ��ת�����棬����ɫ���Ŀ�������ת��ǰ�� 
			U();
			rotatexy();
			rotatexy();
			rotatexy();
			//�ҵ����̰׽ǿ飬������������ 
			if (testcorner(3,6,2,6,2,3))
			{
				R();
				D();
				R();
				R();
				R();
				D();
				D();
				D();
			}
			else if (testcorner(3,2,5,6,2,3))
			{
				R();
				R();
				R();
				D();
				D();
				D();
				R();
				D();
			}
			//������ĳ��̰׽ǿ��������½�
			if (testcorner(4,5,1,6,2,3))
			{
				D();
			}
			else if (testcorner(4,1,6,6,2,3))
			{
				D();
				D();
			}
			else if (testcorner(4,6,2,6,2,3))
			{
				D();
				D();
				D();
			}
			//������Ͻǿ���ɫ��λ�Ļ�... 
			while (testcorner(3,5,2,3,6,2)!=1)
			{
				R();
				R();
				R();
				D();
				D();
				D(); 
				R();
				D();
			}
			//����ɫ���Ŀ��ǰ��ת�����棬����ɫ���Ŀ�������ת��ǰ�� 
			U();
			rotatexy();
			rotatexy();
			rotatexy();
			//��������̺�׽ǿ��������½�
			if (testcorner(4,5,1,2,1,3))
			{
				D();
			}
			else if (testcorner(4,1,6,2,1,3))
			{
				D();
				D();
			}
			else if (testcorner(4,6,2,2,1,3))
			{
				D();
				D();
				D();
			}
			//������Ͻǿ���ɫ��λ�Ļ�... 
			while (testcorner(3,5,2,3,2,1)!=1)
			{
				R();
				R();
				R();
				D();
				D();
				D(); 
				R();
				D();
			}
			//����Stage3��ɣ���ʱǰ��Ϊ�̣�����Ϊ�� 
			//����ɫ�����淭ת������
			L();
			L();
			rotateyz();
			rotateyz();
			R();
			R(); 
			//��ʱǰ��Ϊ��������Ϊ��
			//ֻҪ��������������δ��λ�ķ��飬�ظ����²�����һ��ʹһ���߿鵽λ���������²�����ֱ�����Stage4 
			//�˴�������������������ѭ��������ѭ���� 
			while(( (cube[5][2][1]==cube[5][2][2])&&(cube[5][2][3]==cube[5][2][2])&&(cube[1][2][1]==cube[1][2][2])&&(cube[1][2][3]==cube[1][2][2])&&(cube[6][2][1]==cube[6][2][2])&&(cube[6][2][3]==cube[6][2][2])&&(cube[2][2][1]==cube[2][2][2])&&(cube[2][2][3]==cube[2][2][2]) )==false)
			{
				//�������ܣ�ֱ��ǰ���д�λ���м��б߿�Ϊֹ�����ִ��3����ת���� 
				i=0; 
				while ( ( ( (cube[1][2][3]==cube[5][2][2])&&(cube[1][2][2]==cube[5][2][1]) ) || ( (cube[2][2][1]==cube[5][2][2])&&(cube[2][2][2]==cube[5][2][3]) ) ) == false)
				{
					if (i==3)
					{
						break;
					}
					U();
					rotatexy();
					rotatexy();
					rotatexy();
					D();
					D();
					D();
					i++;
				}
				//����λ���м��б߿��ƶ�����ȷλ�� 
				if ( ( (cube[1][2][3]==cube[5][2][2])&&(cube[1][2][2]==cube[5][2][1]) ) || ( (cube[2][2][1]==cube[5][2][2])&&(cube[2][2][2]==cube[5][2][3]) ) )
				{
					U();
					R();
					U();
					U();
					U();
					R();
					R();
					R();
					U();
					U();
					U();
					F();
					F();
					F();
					U();
					F();
				}
				//��ת���棬ֱ�����ܵ�һ�б߿������������Ŀ��Ӧ���Ҹ�����ߺ��ұ�δ�����Ҹñ߿����������ɫ���ǻ�ɫΪֹ 
				i=0;
				while( ( ((cube[3][3][2]!=4)&&(cube[5][1][2]==cube[5][2][2])&&(cube[5][2][1]!=cube[5][2][2]||cube[5][2][3]!=cube[5][2][2])) || ((cube[3][2][1]!=4)&&(cube[1][1][2]==cube[1][2][2])&&(cube[1][2][1]!=cube[1][2][2]||cube[1][2][3]!=cube[1][2][2])) || ((cube[3][1][2]!=4)&&(cube[6][1][2]==cube[6][2][2])&&(cube[6][2][1]!=cube[6][2][2]||cube[6][2][3]!=cube[6][2][2])) || ((cube[3][2][3]!=4)&&(cube[2][1][2]==cube[2][2][2])&&(cube[2][2][1]!=cube[2][2][2]||cube[2][2][3]!=cube[2][2][2])) )==false)
				{
					if (i==3)
					{
						break;
					}	
					U();
					i++;
				}
				//���ǻơ���Ӧ��δ����һ��������ת��ǰ�� 
				if (((cube[3][3][2]!=4)&&(cube[5][1][2]==cube[5][2][2])&&((cube[5][2][1]!=cube[5][2][2])||(cube[5][2][3]!=cube[5][2][2])))==false)
				{
					if ((cube[3][2][3]!=4)&&(cube[2][1][2]==cube[2][2][2])&&(cube[2][2][1]!=cube[2][2][2]||cube[2][2][3]!=cube[2][2][2]))
					{
						U();
						rotatexy();
						rotatexy();
						rotatexy();
						D();
						D();
						D();
					}
					else if ((cube[3][1][2]!=4)&&(cube[6][1][2]==cube[6][2][2])&&(cube[6][2][1]!=cube[6][2][2]||cube[6][2][3]!=cube[6][2][2]))
					{
						U();
						U();
						rotatexy();
						rotatexy();
						D();
						D();
					}
					else if ((cube[3][2][1]!=4)&&(cube[1][1][2]==cube[1][2][2])&&(cube[1][2][1]!=cube[1][2][2]||cube[1][2][3]!=cube[1][2][2]))
					{
						U();
						U();
						U();
						rotatexy();
						D();
					}
				}
				//���332����������ͬɫ����332˳ʱ���ƶ�һ�� 
				if (cube[3][3][2]==cube[2][2][2])
				{
					U();
					R();
					U();
					U();
					U();
					R();
					R();
					R();
					U();
					U();
					U();
					F();
					F();
					F();
					U();
					F();
				}
				//���332����������ͬɫ����332��ʱ���ƶ�һ�� 
				else if (cube[3][3][2]==cube[1][2][2])
				{
					U();
					U();
					U();
					L();
					L();
					L();
					U();
					L();
					U();
					F();
					U();
					U();
					U();
					F();
					F();
					F(); 
				}
			}
			//����Stage5�������State2��ͨ�����²��軯ΪState3��State4 
			if ( ( (cube[3][1][2]==4)+(cube[3][2][1]==4)+(cube[3][2][3]==4)+(cube[3][3][2]==4) ) <2)
			{
				F();
				U();
				R();
				U();
				U();
				U();
				R();
				R();
				R();
				F();
				F();
				F();
			}
			//�������State3��State4
			if ((cube[3][1][2]==4)+(cube[3][2][1]==4)+(cube[3][2][3]==4)+(cube[3][3][2]==4)==2)
			{
				//�������State3�����ֱ���֮һ 
				if ( ((cube[3][2][1]==4) && (cube[3][1][2]==4)) || ((cube[3][1][2]==4) && (cube[3][2][3]==4)) || ((cube[3][2][3]==4) && (cube[3][3][2]==4)) || ((cube[3][3][2]==4) && (cube[3][2][1]==4)) )
				{
					//�����廯ΪState3 
					if ((cube[3][3][2]==4) && (cube[3][2][1]==4))
					{
						U();
						rotatexy();
						rotatexy();
						rotatexy();
						D();
						D();
						D();
					}
					else if ((cube[3][2][3]==4) && (cube[3][3][2]==4))
					{
						U();
						U();
						rotatexy();
						rotatexy();
						D();
						D();
					}
					else if ((cube[3][1][2]==4) && (cube[3][2][3]==4))
					{
						U();
						U();
						U();
						rotatexy();
						D();
					}
					//��State3��ΪState1
					F();
					U();
					R();
					U();
					U();
					U();
					R();
					R(); 
					R(); 
					F();
					F();
					F();
				}
				//�������State4�����ֱ���֮һ 
				else if ( ((cube[3][2][1]==4) && (cube[3][2][3]==4)) || ((cube[3][1][2]==4) && (cube[3][3][2]==4)) ) 
				{
					//�����廯ΪState4 
					if ((cube[3][1][2]==4) && (cube[3][3][2]==4))
					{
						U();
						rotatexy();
						rotatexy();
						rotatexy();
						D();
						D();
						D();
					}
					//��State4��ΪState1
					F();
					R();
					U();
					R();
					R();
					R();
					U();
					U();
					U();
					F();
					F();
					F();
				}
			}
			//����Stage5��2nd Step
			//ÿ��ִ������ǰ��������State 1/2/3�е�һ�ַ�ʽ 
			while( (cube[3][1][1]!=4) || (cube[3][1][3]!=4) || (cube[3][3][1]!=4) || (cube[3][3][3]!=4) )
			{
				//�����State1�Ļ�...
				if ( ((cube[3][1][1]==4) || (cube[3][1][3]==4) || (cube[3][3][1]==4) || (cube[3][3][3]==4)) == false)
				{
					//������ת�����������Ͻ�תΪ��ɫ�� 
					while (cube[1][1][3]!=4)
					{
						U();
						rotatexy();
						rotatexy();
						rotatexy();
						D();
						D();
						D();
					}
				}
				//�����State2�Ļ�... 
				else if ( (cube[3][1][1]==4) + (cube[3][1][3]==4) + (cube[3][3][1]==4) + (cube[3][3][3]==4) == 1)
				{
					//���������½�תΪ��ɫ�� 
					while (cube[3][3][1]!=4)
					{
						U();
						rotatexy();
						rotatexy();
						rotatexy();
						D();
						D();
						D();
					}
				}
				//�����State3�Ļ�... 
				else if ( (cube[3][1][1]==4) + (cube[3][1][3]==4) + (cube[3][3][1]==4) + (cube[3][3][3]==4) == 2)
				{
					//��ǰ�����Ͻ�תΪ��ɫ�� 
					while (cube[5][1][1]!=4)
					{
						U();
						rotatexy();
						rotatexy();
						rotatexy();
						D();
						D();
						D();
					}
				}
				R();
				U();
				R();
				R();
				R();
				U();
				R();
				U();
				U();
				R();
				R();
				R();
			}
			//����Stage5���
			a=( (cube[6][1][3]==cube[6][2][2])&&(cube[1][1][1]==cube[1][2][2]) );
			b=( (cube[2][1][3]==cube[2][2][2])&&(cube[6][1][1]==cube[6][2][2]) );
			c=( (cube[1][1][3]==cube[1][2][2])&&(cube[5][1][1]==cube[5][2][2]) );
			d=( (cube[5][1][3]==cube[5][2][2])&&(cube[2][1][1]==cube[2][2][2]) );
			//�������Ͻǿ�4��������2����λ 
			while ((a&&b&&c&&d)==false)
			{
				while((a+b+c+d)<2) 
				{
					U();
					a=( (cube[6][1][3]==cube[6][2][2])&&(cube[1][1][1]==cube[1][2][2]) );
					b=( (cube[2][1][3]==cube[2][2][2])&&(cube[6][1][1]==cube[6][2][2]) );
					c=( (cube[1][1][3]==cube[1][2][2])&&(cube[5][1][1]==cube[5][2][2]) );
					d=( (cube[5][1][3]==cube[5][2][2])&&(cube[2][1][1]==cube[2][2][2]) );
				}
				//������תֱ���ﵽAB��AD��BC��ʽ 
				while ( (a&&b || a&&d || b&&c) == false)
				{
					U();
					U();
					U();
					rotatexy();
					D();
					a=( (cube[6][1][3]==cube[6][2][2])&&(cube[1][1][1]==cube[1][2][2]) );
					b=( (cube[2][1][3]==cube[2][2][2])&&(cube[6][1][1]==cube[6][2][2]) );
					c=( (cube[1][1][3]==cube[1][2][2])&&(cube[5][1][1]==cube[5][2][2]) );
					d=( (cube[5][1][3]==cube[5][2][2])&&(cube[2][1][1]==cube[2][2][2]) );	
				}
				//��BC/AD��ʽ��ΪAB��ʽ����AB��ʽ��ΪABCD��ʽ 
				R();
				R();
				R();
				F();
				R();
				R();
				R();
				B();
				B();
				R();
				F();
				F();
				F();
				R();
				R();
				R();
				B();
				B();
				R();
				R();
				U();
				U();
				U();
				a=( (cube[6][1][3]==cube[6][2][2])&&(cube[1][1][1]==cube[1][2][2]) );
				b=( (cube[2][1][3]==cube[2][2][2])&&(cube[6][1][1]==cube[6][2][2]) );
				c=( (cube[1][1][3]==cube[1][2][2])&&(cube[5][1][1]==cube[5][2][2]) );
				d=( (cube[5][1][3]==cube[5][2][2])&&(cube[2][1][1]==cube[2][2][2]) );
			}
			//����Stage6, 2nd Step
			e=(cube[1][1][2]==cube[1][2][2]);
			f=(cube[6][1][2]==cube[6][2][2]);
			g=(cube[2][1][2]==cube[2][2][2]);
			h=(cube[5][1][2]==cube[5][2][2]);
			//��EFGH��ʽ��ΪEFG��ʽ��ĳ������ 
			if ((e||f||g||h)==false)
			{
				F();
				F();
				U();
				L();
				R();
				R();
				R();
				F();
				F();
				L();
				L();
				L();
				R();
				U();
				F();
				F();
			}
			//��EFG��ʽ��ĳ�����廯ΪEFG��ʽ 
			e=(cube[1][1][2]==cube[1][2][2]);
			f=(cube[6][1][2]==cube[6][2][2]);
			g=(cube[2][1][2]==cube[2][2][2]);
			h=(cube[5][1][2]==cube[5][2][2]);
			if (e+f+g+h==1)
			{
				if (e==1)
				{
					U();
					rotatexy();
					rotatexy();
					rotatexy();
					D();
					D();
					D();
				}
				else if (h==1)
				{
					U();
					U();
					rotatexy();
					rotatexy();
					D();
					D();
				}
				else if (g==1)
				{
					U();
					U();
					U();
					rotatexy();
					D();
				}
			}
			//��Ҫ˳ʱ����תһ�ε�EFG��ʽ 
			if (cube[1][2][2]==cube[5][1][2])
			{
				F();
				F();
				U();
				L();
				R();
				R();
				R();
				F();
				F();
				L();
				L();
				L();
				R();
				U();
				F();
				F();
			}
			//��Ҫ��ʱ����תһ�ε�EFG��ʽ 
			else if (cube[1][2][2]==cube[2][1][2])
			{
				F();
				F();
				U();
				U();
				U();
				L();
				R();
				R();
				R();
				F();
				F();
				L();
				L();
				L();
				R();
				U();
				U();
				U();
				F();
				F();
			}
			//�������Stage6
			//����ȫ�����
		} //%END%
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

void L() //20�α任��5��chainswap 
{
	//���ڱ任 
	chainswap(cube[1][1][1],cube[1][1][3],cube[1][3][3],cube[1][3][1]);
	chainswap(cube[1][1][2],cube[1][2][3],cube[1][3][2],cube[1][2][1]);
	//������ı任 
	chainswap(cube[3][1][1],cube[5][1][1],cube[4][1][1],cube[6][3][3]);
	chainswap(cube[3][2][1],cube[5][2][1],cube[4][2][1],cube[6][2][3]);
	chainswap(cube[3][3][1],cube[5][3][1],cube[4][3][1],cube[6][1][3]);
	output("L");
}

void R() //20�α任��5��chainswap 
{
	//���ڱ任 
	chainswap(cube[2][1][1],cube[2][1][3],cube[2][3][3],cube[2][3][1]);
	chainswap(cube[2][1][2],cube[2][2][3],cube[2][3][2],cube[2][2][1]);
	//������ı任 
	chainswap(cube[3][3][3],cube[6][1][1],cube[4][3][3],cube[5][3][3]);
	chainswap(cube[3][2][3],cube[6][2][1],cube[4][2][3],cube[5][2][3]);
	chainswap(cube[3][1][3],cube[6][3][1],cube[4][1][3],cube[5][1][3]);
	output("R");
}

void U() //20�α任��5��chainswap 
{
	//���ڱ任 
	chainswap(cube[3][1][1],cube[3][1][3],cube[3][3][3],cube[3][3][1]);
	chainswap(cube[3][1][2],cube[3][2][3],cube[3][3][2],cube[3][2][1]);
	//������ı任 
	chainswap(cube[1][1][1],cube[6][1][1],cube[2][1][1],cube[5][1][1]);
	chainswap(cube[1][1][2],cube[6][1][2],cube[2][1][2],cube[5][1][2]);
	chainswap(cube[1][1][3],cube[6][1][3],cube[2][1][3],cube[5][1][3]);
	output("U");
}

void D() //20�α任��5��chainswap 
{
	//���ڱ任 
	chainswap(cube[4][1][1],cube[4][1][3],cube[4][3][3],cube[4][3][1]);
	chainswap(cube[4][1][2],cube[4][2][3],cube[4][3][2],cube[4][2][1]);
	//������ı任 
	chainswap(cube[5][3][1],cube[2][3][1],cube[6][3][1],cube[1][3][1]);
	chainswap(cube[5][3][2],cube[2][3][2],cube[6][3][2],cube[1][3][2]);
	chainswap(cube[5][3][3],cube[2][3][3],cube[6][3][3],cube[1][3][3]);
	output("D");
}

void F() //20�α任��5��chainswap 
{
	//���ڱ任 
	chainswap(cube[5][1][1],cube[5][1][3],cube[5][3][3],cube[5][3][1]);
	chainswap(cube[5][1][2],cube[5][2][3],cube[5][3][2],cube[5][2][1]);
	//������ı任 
	chainswap(cube[3][3][1],cube[2][1][1],cube[4][1][3],cube[1][3][3]);
	chainswap(cube[3][3][2],cube[2][2][1],cube[4][1][2],cube[1][2][3]);
	chainswap(cube[3][3][3],cube[2][3][1],cube[4][1][1],cube[1][1][3]);
	output("F");
}

void B() //20�α任��5��chainswap 
{
	//���ڱ任 
	chainswap(cube[6][1][1],cube[6][1][3],cube[6][3][3],cube[6][3][1]);
	chainswap(cube[6][1][2],cube[6][2][3],cube[6][3][2],cube[6][2][1]);
	//������ı任 
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

void output(char message[]) 
{ 
	ofstream fout("solution.txt", ios::out | ios::app);   
	fout<<message<<endl; 
	fout.close(); 
}

int testcenter(int face, int color)
{
	if (cube[face][2][2]==color)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int testside(int face1, int face2, int color1, int color2)
{
	int s,t;
	if (s=cequal2(5,1,face1,face2))
	{
		t=cequal2(cube[5][2][1],cube[1][2][3],color1,color2);
	}
	else if (s=cequal2(5,2,face1,face2))
	{
		t=cequal2(cube[5][2][3],cube[2][2][1],color1,color2);
	}
	else if (s=cequal2(5,3,face1,face2))
	{
		t=cequal2(cube[5][1][2],cube[3][3][2],color1,color2);
	}
	else if (s=cequal2(5,4,face1,face2))
	{
		t=cequal2(cube[5][3][2],cube[4][1][2],color1,color2);
	}
	else if (s=cequal2(6,1,face1,face2))
	{
		t=cequal2(cube[6][2][3],cube[1][2][1],color1,color2);
	}
	else if (s=cequal2(6,2,face1,face2))
	{
		t=cequal2(cube[6][2][1],cube[2][2][3],color1,color2);
	}
	else if (s=cequal2(6,3,face1,face2))
	{
		t=cequal2(cube[6][1][2],cube[3][1][2],color1,color2);
	}
	else if (s=cequal2(6,4,face1,face2))
	{
		t=cequal2(cube[6][3][2],cube[4][3][2],color1,color2);
	}
	else if (s=cequal2(3,1,face1,face2))
	{
		t=cequal2(cube[3][2][1],cube[1][1][2],color1,color2);
	}
	else if (s=cequal2(3,2,face1,face2))
	{
		t=cequal2(cube[3][2][3],cube[2][1][2],color1,color2);
	}
	else if (s=cequal2(4,1,face1,face2))
	{
		t=cequal2(cube[4][2][1],cube[1][3][2],color1,color2);
	}
	else if (s=cequal2(4,2,face1,face2))
	{
		t=cequal2(cube[4][2][3],cube[2][3][2],color1,color2);
	}
	else
	{
		return 0;
	}
	return (t!=0)?((s==1)?t:3-t):0;
}

int testcorner(int face1, int face2, int face3, int color1, int color2, int color3)
{
	int s,t;
	if (s=cequal3(5,1,3,face1,face2,face3))
	{
		t=cequal3(cube[5][1][1],cube[1][1][3],cube[3][3][1],color1,color2,color3);
	}
	else if (s=cequal3(5,3,2,face1,face2,face3))
	{
		t=cequal3(cube[5][1][3],cube[3][3][3],cube[2][1][1],color1,color2,color3);
	}
	else if (s=cequal3(5,2,4,face1,face2,face3))
	{
		t=cequal3(cube[5][3][3],cube[2][3][1],cube[4][1][3],color1,color2,color3);
	}
	else if (s=cequal3(5,4,1,face1,face2,face3))
	{
		t=cequal3(cube[5][3][1],cube[4][1][1],cube[1][3][3],color1,color2,color3);
	}
	else if (s=cequal3(6,3,1,face1,face2,face3))
	{
		t=cequal3(cube[6][1][3],cube[3][1][1],cube[1][1][1],color1,color2,color3);
	}
	else if (s=cequal3(6,1,4,face1,face2,face3))
	{
		t=cequal3(cube[6][3][3],cube[1][3][1],cube[4][3][1],color1,color2,color3);
	}
	else if (s=cequal3(6,4,2,face1,face2,face3))
	{
		t=cequal3(cube[6][3][1],cube[4][3][3],cube[2][3][3],color1,color2,color3);
	}
	else if (s=cequal3(6,2,3,face1,face2,face3))
	{
		t=cequal3(cube[6][1][1],cube[2][1][3],cube[3][1][3],color1,color2,color3);
	}
	else
	{
		return 0;
	}
	if (s==1 && t==1 || s==2 && t==2 || s==3 && t==3 || s==4 && t==5 || s==5 && t==4 || s==6 && t==6)
	{
		return 1;
	}
	else if (t==0)
	{
		return 0;
	}
	else
	{
		return 2;
	}
}

int cequal2(int a, int b, int x, int y)
{
	if (a==x && b==y)
	{
		return 1;
	}
	else if(a==y && b==x)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

int cexist2(int a, int x, int y)
{
	if (a==x)
	{
		return 1;
	}
	else if (a==y)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

int cequal3(int a, int b, int c, int x, int y, int z)
{
	if (a==x && b==y && c==z)
	{
		return 1;
	}
	else if (a==x && b==z && c==y)
	{
		return 2;
	}
	else if (a==y && b==x && c==z)
	{
		return 3;
	}
	else if (a==y && b==z && c==x)
	{
		return 4;
	}
	else if (a==z && b==x && c==y)
	{
		return 5;
	}
	else if (a==z && b==y && c==x)
	{
		return 6;
	}
	else
	{
		return 0;
	}
}

int cexist3(int a, int x, int y, int z)
{
	if (a==x)
	{
		return 1;
	}
	else if (a==y)
	{
		return 2;
	}
	else if (a==z)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

int sideexist(int color, int face1, int face2)
{
	if (face1==5 && face2==1)
	{
		return cexist2(color,cube[5][2][1],cube[1][2][3]);
	}
	else if (face1==5 && face2==3)
	{
		return cexist2(color,cube[5][1][2],cube[3][3][2]);
	}
	else if (face1==5 && face2==2)
	{
		return cexist2(color,cube[5][2][3],cube[2][2][1]);
	}
	else if (face1==5 && face2==4)
	{
		return cexist2(color,cube[5][3][2],cube[4][1][2]);
	}
	else if (face1==6 && face2==1)
	{
		return cexist2(color,cube[6][2][3],cube[1][2][1]);
	}
	else if (face1==6 && face2==3)
	{
		return cexist2(color,cube[6][1][2],cube[3][1][2]);
	}
	else if (face1==6 && face2==2)
	{
		return cexist2(color,cube[6][2][1],cube[2][2][3]);
	}
	else if (face1==6 && face2==4)
	{
		return cexist2(color,cube[6][3][2],cube[4][3][2]);
	}
	else
	{
		return 0;
	}
}

void output_c(char message)
{ 
	ofstream fout("solution.txt", ios::out | ios::app);   
	fout<<message<<endl; 
	fout.close(); 
}

void dump()
{
	int i,j,k;
	output("~~~~~~~~~~~~~~~~");
	for (i=1;i<7;i++)
	{
		for (j=1;j<4;j++)
		{
			for (k=1;k<4;k++)
			{
				output_c(cube[i][j][k]+48);
			}
		}
	}
	output("~~~~~~~~~~~~~~~~"); 
}

void screendump()
{
	int i,j,k;
	cout<<"~~~~~~~~~~~~~~~~"<<endl;
	for (j=1;j<4;j++)
	{
		cout<<"       ";
		for (k=1;k<4;k++)
		{
			cout<<cube[3][j][k]<<" ";
		}
		cout<<endl;
	}
	for (j=1;j<4;j++)
	{
		for (k=1;k<4;k++)
		{
			cout<<cube[1][j][k]<<" ";
		}
		cout<<" ";
		for (k=1;k<4;k++)
		{
			cout<<cube[5][j][k]<<" ";
		}
		cout<<" ";
		for (k=1;k<4;k++)
		{
			cout<<cube[2][j][k]<<" ";
		}
		cout<<" ";
		for (k=1;k<4;k++)
		{
			cout<<cube[6][j][k]<<" ";
		}
		cout<<endl;
	}
	for (j=1;j<4;j++)
	{
		cout<<"       ";
		for (k=1;k<4;k++)
		{
			cout<<cube[4][j][k]<<" ";
		}
		cout<<endl;
	}
	cout<<"~~~~~~~~~~~~~~~~"<<endl;
}

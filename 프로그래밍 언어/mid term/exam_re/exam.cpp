/** exam.cpp */
/* 
* File Name: "exam.cpp"
* Description:
* - This program is Special Report
* Programmed by Jung-Ha Cho,
* Last updated: Version 2.0, Aprill 30, 2012 (by Jung-Ha Cho).
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/04/30) Version Remarks
* J.H Cho 2012/04/28 1.0 Project & Main function is created
* J.H Cho 2012/04/30 2.0 Project Last Function is done
* ========================================================
*/
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <stdlib.h>

#include "MyStructures.h"

using namespace std;

#define NUM_STUDENTS 10000
#define STUDENTS_TO_SEARCH 10
#define DISPLAYLINES 10

void initStudents(Student arrayOfStudent[], int size);
void printStudents(Student *pS, ofstream *pOf);
void printStudents2(Student *pS, ofstream *pOf,int i);
void genBigRandArray(int mA[], int size, int RANGE);
void printArrayOfStudents(Student arrayOfStudent[], int size, ofstream *pOf);
void quickSortStudentArrayByID(Student arrayOfStudent[], int right, int left);
void selectionSortStudentArrayByGPA_ID(Student arrayOfStudent[], int num);
void insertStudentInList(ListOfStudents *pLS, Student *pS);
void printListOfStudents(ListOfStudents *pLS, ofstream *pOf);
void insertStudentInTree(TreeNode **ppTN, Student *pS);
void printTreeInOrderOfStudents(TreeNode *pST, ofstream *pOf);
void printStudentID(Student *pS, ofstream *pOf);


int partition(Student mA[], int left, int right, int pivotIndex);

Student *searchStudentFromArray(Student arrayOfStudent[], int idToSearch[], int size);
Student *searchStudentFromList(ListOfStudents *pLS, int idToSearch[], int size);
Student *searchStudentFromTree(TreeNode *pTN, int idToSearch[], int size);

void main()
{
	Student *pSA, *pS;
	int *idToSearch;
	ofstream fout;

	LARGE_INTEGER freq, t_1, t_2;
	LONGLONG t_diff;
	double elapsed_time, accumulated_elapsedTime;

	QueryPerformanceFrequency(&freq);
	fout.open("output.txt");
	if(fout.fail()){
		cout<<"output file (output.txt) open failed !! \n";
		return;
	}

	/* Initialize Students */

	pSA = new Student[NUM_STUDENTS];
	initStudents(pSA, NUM_STUDENTS);

	idToSearch = new int[STUDENTS_TO_SEARCH];
	genBigRandArray(idToSearch, STUDENTS_TO_SEARCH, NUM_STUDENTS);
	cout<<"initialization of "<<NUM_STUDENTS<<" is completed..\n";

	//printStudents(pSA, &fout);

	/* Management of array of students */
	fout<<"Initialize Student array:\n";
	printArrayOfStudents(pSA, NUM_STUDENTS, &fout);

	fout<<"\n*** Management of structure array of students ***\n";
	fout<<"Students array sorted by ID :\n";

	QueryPerformanceCounter(&t_1);
	quickSortStudentArrayByID(pSA, NUM_STUDENTS, 0);
	QueryPerformanceCounter(&t_2);
	t_diff = t_2.QuadPart - t_1.QuadPart;
	elapsed_time = ((double) t_diff / freq.QuadPart) * 1000000;

	

	fout<<"Time for quickSorting of array of students: "<<elapsed_time<<"microseconds\n";
	printArrayOfStudents(pSA, NUM_STUDENTS, &fout);

	fout<<"\n"<<STUDENTS_TO_SEARCH<<" searched results from Array;\n";
	accumulated_elapsedTime = 0;

	for(int i=0; i<STUDENTS_TO_SEARCH; i++)
	{
		QueryPerformanceCounter(&t_1);
		pS = searchStudentFromArray(pSA, idToSearch, i);
		QueryPerformanceCounter(&t_2);
		t_diff = t_2.QuadPart - t_1.QuadPart;
		elapsed_time = ((double) t_diff / freq.QuadPart) * 1000000;
		accumulated_elapsedTime += elapsed_time;

		printStudents2(pS, &fout, i);
	}
	///////////////////////////////////////////////
	for(int i = 0; i < 10 ; i++)
	{
		fout<<idToSearch[i]<<" ";
	}
	fout<<endl;
	///////////////////////////////////////////////
	fout<<"Average time for seaching a studet from Array :";
	fout<< accumulated_elapsedTime / STUDENTS_TO_SEARCH<<" microseconds\n";

	fout<<"\nStudents Array sorted by GPA_ID : \n";
	selectionSortStudentArrayByGPA_ID(pSA, NUM_STUDENTS);
	printArrayOfStudents(pSA, NUM_STUDENTS, &fout);

	/* Management to linked list of students */

	fout<<"\n***Management of ;linked list of students ***\n";
	ListOfStudents *pLS;

	pLS = new ListOfStudents;
	pLS -> num_student = 0;
	pLS -> pFirst = pLS -> pLast = NULL;

	QueryPerformanceCounter(&t_1);
	for(int st = 0 ; st < NUM_STUDENTS ; st++)
	{
		insertStudentInList(pLS, &pSA[st]);
	}
	QueryPerformanceCounter(&t_2);
	t_diff = t_2.QuadPart - t_1.QuadPart;
	elapsed_time = ((double) t_diff / freq.QuadPart) * 1000000;
	cout<<"Insertion of students in linked list completed !!\n";

	fout<<"Average time to insert a student in sorted linked list : ";
	fout<< elapsed_time / NUM_STUDENTS <<" microseconds \n";

	fout<<"\nList of "<<pLS->num_student;
	fout<<"students in sorted order by ID (decreasing order):\n";
	printListOfStudents(pLS, &fout);

	fout<<"\n"<<STUDENTS_TO_SEARCH<<" searched results from Linked List:\n";

	accumulated_elapsedTime = 0;
	for(int i = 0 ; i < STUDENTS_TO_SEARCH; i++)
	{
		QueryPerformanceCounter(&t_1);
		pS = searchStudentFromList(pLS, idToSearch, i);
		QueryPerformanceCounter(&t_2);
		t_diff = t_2.QuadPart - t_1.QuadPart;
		elapsed_time = ((double) t_diff / freq.QuadPart) * 1000000;
		accumulated_elapsedTime += elapsed_time;

		printStudents2(pS, &fout, i);
	}
	///////////////////////////////////////////
	for(int i = 0; i < 10 ; i++)
	{
		fout<<idToSearch[i]<<" ";
	}
	fout<<endl;
	////////////////////////////////////////////
	fout<<"Average time for searching a student from Linked List:";
	fout<<accumulated_elapsedTime / STUDENTS_TO_SEARCH <<" microeconds\n";

	///* Management of Binary Tree of Students */

	fout<< "\n *** Management of Binary Tree of students *** \n";
	StudentTree *pST;
	pST = new StudentTree;
	pST->num_student = 0;
	pST->pTN = NULL;

	QueryPerformanceCounter(&t_1);
	for(int st=0; st < NUM_STUDENTS ; st++)
	{
		insertStudentInTree(&pST->pTN, &pSA[st]);
		pST->num_student++;
	}
	QueryPerformanceCounter(&t_2);
	t_diff = t_2.QuadPart - t_1.QuadPart;
	elapsed_time = ((double) t_diff / freq.QuadPart) * 1000000;
	fout<<"Average time to insert a student in binary tree :";
	fout<<elapsed_time / NUM_STUDENTS<<" microseconds\n";
	cout<<"Insertion of students in tree completed !!. \n";
	cout.flush();
	fout<<"\n Tree of " << pST->num_student<<" Students in sorted order by ID (in-order ): \n";
	fout.flush();

	printTreeInOrderOfStudents(pST->pTN, &fout);

	fout<<"\n" <<STUDENTS_TO_SEARCH <<" searched results from Binary Tree:..\n";
	accumulated_elapsedTime=0;
	for(int i = 0 ; i < STUDENTS_TO_SEARCH ; i ++)
	{
		QueryPerformanceCounter(&t_1);
		pS=searchStudentFromTree(pST->pTN, idToSearch, i);
		QueryPerformanceCounter(&t_2);
		t_diff = t_2.QuadPart - t_1.QuadPart;
		elapsed_time = ((double) t_diff / freq.QuadPart) * 1000000;
		accumulated_elapsedTime += elapsed_time;

		printStudents2(pS, &fout, i);
	}
	///////////////////////////////////////////////
	for(int i = 0; i < 10 ; i++)
	{
		fout<<idToSearch[i]<<" ";
	}
	fout<<endl;
	///////////////////////////////////////////////
	fout<<"Average time for searching a student from binary tree :";
	fout<<accumulated_elapsedTime / STUDENTS_TO_SEARCH<<" microseconds \n";
	cout<<"Searching students from Binary Tree completed."<<endl;

	fout<<endl;
	//delete pLS;
	//delete pST;
	//delete pSA;
	//delete pS;
	//free(pSA);
	fout.close();

	cout<<"Exit program....."<<endl;
}
void initStudents(Student arrayOfStudent[], int size)  
{
	srand(time(0));
	int name_fir, name_las, name_dep;    
	for(int i = 0 ; i < size+1; i++)
	{
		name_fir = rand()%12+3;  
		name_las = rand()%12+3;  
		name_dep = rand()%12+3;  
		(arrayOfStudent+i)->first_name[0] = rand()%26 + 'A' ; 
		for (int j=1; j<name_fir; j++)  
		{
			(arrayOfStudent+i)->first_name[j] = rand()%26 + 'a' ;
		}
		(arrayOfStudent+i)->first_name[name_fir] = NULL;

		/////////////////////////////////////////////////////////////////////////

		(arrayOfStudent+i)->last_name[0] = rand()%26 + 'A'; 
		for (int j=1; j<name_las; j++)  
		{
			(arrayOfStudent+i)->last_name[j] = rand()%26+ 'a'; 
		}
		(arrayOfStudent+i)->last_name[name_las] = NULL;

		/////////////////////////////////////////////////////////////////////////

		for (int j=0; j<name_dep; j++)  
		{
			(arrayOfStudent+i)->department[j] = rand()%26 + 'A';
		}
		(arrayOfStudent+i)->department[name_dep] = NULL;

		/////////////////////////////////////////////////////////////////////////

		(arrayOfStudent+i)->grade = (int)(rand()%8+1);
		(arrayOfStudent+i)->GPA = (double)(rand()%10000*0.01);
	}
	int name_len2;
	name_len2 = rand()%245+10; 

	for( int i = 0 ; i < size+1 ; i++ )
	{ 
		for (int j=0; j<name_len2; j++)  
		{
			(arrayOfStudent+i)->description[j] = rand()%26 +'a'; 
			(arrayOfStudent+i)->description[name_len2] = NULL;
		}
	}

	char *flag = new char[NUM_STUDENTS];
	unsigned int uint_32;
	unsigned int bigRand;
	//srand(time(0));
	for(int i = 0; i < NUM_STUDENTS; i++ )
	{
		flag[i] = 0;
	}
	int count = 0;
	while (count < NUM_STUDENTS) 
	{
		uint_32 = ( ( long ) rand() << 15) | rand(); 
		bigRand = uint_32 % NUM_STUDENTS;
		if (flag[bigRand] == 1)
		{ 
			continue;
		} else {
			flag[bigRand] = 1;
			(arrayOfStudent+count++)->st_id = bigRand; 
		} 
	}
}
void printStudents(Student *pS, ofstream *pOf)
{
	*pOf<<"First 10 of total "<<NUM_STUDENTS<<" students:"<<endl;
	for(int i =0; i < 10; i++)
	{
		*pOf<<"St_id ("<<setw(5)<<(pS+i)->st_id<<"): ";
		*pOf<<"Name ("<<(pS+i)->last_name<<", "<<(pS+i)->first_name<<"), ";
		*pOf<<"Dept ("<<(pS+i)->department<<"), ";
		*pOf<<"grade ("<<(pS+i)->grade<<"), ";
		cout.setf(ios::fixed); 
		cout.precision(2);
		*pOf<<"GPA ("<<(pS+i)->GPA<<")"<<endl;
	}

	*pOf<<"Last 10 of total "<<NUM_STUDENTS<<" students:"<<endl;
	for(int i = NUM_STUDENTS-10; i < NUM_STUDENTS; i++)
	{
		*pOf<<"St_id ("<<setw(5)<<(pS+i)->st_id<<"): ";
		*pOf<<"Name ("<<(pS+i)->last_name<<", "<<(pS+i)->first_name<<"), ";
		*pOf<<"Dept ("<<(pS+i)->department<<"), ";
		*pOf<<"grade ("<<(pS+i)->grade<<"), ";
		cout.setf(ios::fixed); 
		cout.precision(2);
		*pOf<<"GPA ("<<(pS+i)->GPA<<")"<<endl;
	}
}
void printStudents2(Student *pS, ofstream *pOf, int i)
{
	*pOf<<"St_id ("<<setw(5)<<pS->st_id<<"): ";
	*pOf<<"Name ("<<pS->last_name<<", "<<(pS+i)->first_name<<"), ";
	*pOf<<"Dept ("<<pS->department<<"), ";
	*pOf<<"grade ("<<pS->grade<<"), ";
	cout.setf(ios::fixed); 
	cout.precision(2);
	*pOf<<"GPA ("<<pS->GPA<<")"<<endl;
}
void genBigRandArray(int mA[], int RANGE, int size)//������ = 10 ������ 10000
{
	srand(time(0));
	char *flag = new char[size];
	unsigned int uint_32;
	unsigned int bigRand;
	for(int i = 0; i < RANGE; i++ )
	{
		flag[i] = 0;
	}
	int count = 0;
	while (count < RANGE) 
	{
		uint_32 = ( ( long ) rand() << 15) | rand(); 
		bigRand = uint_32 % size;
		if (flag[bigRand] == 1)
		{ 
			continue;
		} else {
			flag[bigRand] = 1;
			mA[count++] = bigRand; // �򷣵忡 +1���ָ� 1����100���� ����������
		} 
	} 
}

void printArrayOfStudents(Student arrayOfStudent[], int size, ofstream *pOf)
{
	printStudents(arrayOfStudent, pOf);
}
void quickSortStudentArrayByID(Student mA[], int right, int left)//, NUM_STUDENTS-1, 0);
{
	int pivotIndex, newPI; //�Ǻ��ε���,���Ǻ��ε��� ����
	pivotIndex = left + ( right - left ) / 2 ; //�Ǻ��ε��� ��ġ ���

	if (left >= right) //����Լ� ���� ���� 
		return;
	else if (left < right) //����Լ� ���� ���� //�ʱ� pdf���� ����Ʈ�� 0~"12"
	{
		newPI = partition(mA, left, right, pivotIndex); // ��Ƽ���� ��ȯ���� storeindex�� ��ȯ�ϸ� storeindex�� 0~12�� 6���迭�� ��� ������ ���� ���� 6���迭 ������(0~5) ��Ƽ��
		quickSortStudentArrayByID(mA, left, newPI - 1); // ����Լ� ����, newPI�� ���� ��Ƽ���� storeIndex�̸� �� ���� -1�� �Ѱ��� ���� ����Լ��� right�� �ȴ�.
		quickSortStudentArrayByID(mA, newPI + 1, right);// ����Լ� ����, 0~4������ �迭�� pivotIndex���� ������ �迭�� ��Ʈ�� ������ ������ �Ǹ� ������ �迭 ��Ʈ������ ����Լ� ����.
	} 
}
int partition(Student mA[], int left, int right, int pivotIndex) 
//mA[] ���������� �迭�� �ʱ� left = 0�� right 12�� �Ǻ��ε��� ���� ���� �޾ƿ�
{
	Student temp;

	int storeIndex;  //�����ε���, �� ��Ʈ �� �迭������ �迭��ȣ ����
	int pivotValue;  //�Ǻ����

	pivotValue = (mA+pivotIndex)->st_id; //�Ǻ������ mA[�Ǻ��ε���], �� 0~12������ �߰��� ġȯ
	//swap(*(mA+pivotIndex), *(mA+right)); // �Ǻ��ε���(0~12������ �߰���)�� �ǳ��� right=12 ���� ����.
	temp = *(mA+pivotIndex);
	*(mA+pivotIndex) =  *(mA+right);
	*(mA+right) = temp;
	storeIndex = left; //�ʱ� ����� �ε����� left(0)���� ġȯ

	for (int i = left; i <= right - 1; i++)// left���� right( �ǳ��� right �� ����) �ݺ���
	{
		if ((mA+i)->st_id < pivotValue) //mA[i]�� i�� 0~11���� Ȯ���ϸ鼭 pivotvalue ��, �ʱ� 0~12�� �߰����� �� 
		{						//pivotvalue ���� �������� ������ ���ǹ� ����
			//swap(*(mA+i), *(mA+storeIndex)); //mA[i]�� �Ǻ�������� ������, �׸��� mA[storeIndex] �� 0~12������ �迭�� �� ù��°�� ����
			temp = *(mA+i);
			*(mA+i) = *(mA+storeIndex);
			*(mA+storeIndex) = temp;
			storeIndex = storeIndex + 1; //mA[0]���� pivotvalue ���� �������� ������� ���� ������ ���� storeIndex + 1 �� ��
		}
	}

	//swap(*(mA+storeIndex), *(mA+right)); //�ݺ��� ������ ������ ���� �ʱ� pivotIndex�� ���� �񱳰� ���� storeIndex �ڸ��� ����
	temp = *(mA+storeIndex);
	*(mA+storeIndex) = *(mA+right);
	*(mA+right) = temp;
	return storeIndex; // ��Ƽ���� ���� �� ������ �迭��ȣ�� ��ȯ
}
void selectionSortStudentArrayByGPA_ID(Student arrayOfStudent[], int num)
{
	int iPos, jPos; //���� ����
	int iMin;       //���� ����

	Student *temp;
	temp = new Student[num];

	for (iPos = 0; iPos < num; iPos++)  //�ݺ���, num�� �� ����
	{
		iMin = iPos;                  //iMin�� iPos ġȯ
		for (jPos = iPos+1; jPos < num; jPos ++) // iPos +1�ؼ� iPos���� �˻��� ���ϰ� ��������
		{
			if ((arrayOfStudent+jPos)->GPA < (arrayOfStudent+iMin)->GPA) //������ 0��° �� ù��° ������ �ƽ�Ű�ڵ带 ��
			{
				iMin = jPos;  //ġȯ
			} 
		}
		if ( iMin != iPos ) //����
		{
			*(temp+iPos) = *(arrayOfStudent+iPos);
			*(arrayOfStudent+iPos) = *(arrayOfStudent+iMin);
			*(arrayOfStudent+iMin) = *(temp+iPos);
		}
	}
}

void insertStudentInList(ListOfStudents *pLS, Student *pS)
{
	ListNode *pLN;
	pLN = new ListNode;
	pLN->pST =  pS;

	if(pLS->num_student == 0 )  //��尡 ������. �ʱ�ȭ
	{
		pLS->pFirst = pLS->pLast = pLN;
		pLN->pNext = NULL;
		pLN->pPrev = NULL;
		pLS->num_student++;
	}else if(pLS->num_student < NUM_STUDENTS){ // ���л� 10000���� ������ 
		for(ListNode * pS = pLS->pFirst; pS != NULL;) //����Ʈ����� pS ������ pLS�� first�� �ּҰ� ����
		{
			if(pLN->pST->st_id < pS->pST->st_id ){ // id�� ��
				pLN->pNext = pS;                   //  pLN�� Next�� pS�� ġȯ
				pLN->pPrev = pS->pPrev;            // pLN�� �������� pS�� ���������� ġȯ
				if(pS != pLS->pFirst){             // pS�� pLS�� pFirst�� �ƴҶ�
					if(pS->pPrev != NULL)          // pS�� �������� ���� �ƴҶ�
						pS->pPrev->pNext= pLN;     
					pS->pPrev = pLN;
				} else {
					pLS->pFirst = pLN;
					pLN->pPrev = NULL;
					pS->pPrev = pLN;
				}
				pLS->num_student++;
				break;
			}
			else if((pS == pLS ->pLast) && (pLN->pST->st_id > pS->pST->st_id)) //
			{
				pLN->pPrev = pS;
				pS->pNext = pLN;
				pLS->pLast = pLN;
				pLN->pNext = NULL;
				pLS->num_student++;
				break;
			}else{
				if(pS != pLS->pLast)
					pS=pS->pNext;
				else
					break;
			}
		}
	}
}

void printListOfStudents(ListOfStudents *pLS, ofstream *pOf)
{
	ListNode *pST;   
	pST = pLS->pFirst->pNext;

	int count=1;
	while((pST != NULL) && (count < 51))
	{  
		*pOf<<setw(5)<<pST->pST->st_id<<", ";
		pST = pST->pNext;
		if(count % 10 == 0)
		{
			*pOf<<endl;
		}
		count++;
	}

	for(int i = 0 ; i < 9899; i++)
	{
		pST = pST ->pNext;
	}
	count = 1;
	while((pST != NULL) && (count < 51))
	{  
		*pOf<<setw(5)<<pST->pST->st_id<<", ";
		pST = pST->pNext;
		if(count % 10 == 0)
		{
			*pOf<<endl;
		}
		count++;
	}
}
void insertStudentInTree(TreeNode **ppTN, Student *pS)
{
	TreeNode *pN;   //Ʈ������� �����ͺ��� pN
	if(*ppTN == NULL) //ppT�� ���� 
	{
		pN = new TreeNode; //Ʈ����� ������ �����Ҵ�
		pN->pSTN = pS; // pN
		pN->pL = NULL;  //pN�� pL�ʱ�ȭ
		pN->pR = NULL;  //pN�� pL�ʱ�ȭ
		*ppTN = pN;
		//outstream <<" InsertTreeNode (Star id:" << pS->id;
		//outstream <<", name: " << pS->name << ")"<<endl;

	} else if (pS->st_id < (*ppTN)->pSTN->st_id)
	{
		insertStudentInTree(&(*ppTN)->pL, pS);//������ ����
	} else 
	{
		insertStudentInTree(&(*ppTN)->pR, pS);//ũ�� ������
	}
}
void printTreeInOrderOfStudents(TreeNode *pST, ofstream *pOf)
{
	if (pST != NULL) 
	{     
		printTreeInOrderOfStudents(pST->pL, pOf);
		printStudentID(pST->pSTN, pOf);
		printTreeInOrderOfStudents(pST->pR, pOf);
	}
}
void printStudentID(Student *pS, ofstream *pOf)
{
	if( (pS->st_id >= 0) && (pS->st_id < 50) || (pS->st_id >= 9950) && (pS->st_id <10000))
	{
		*pOf <<setw(5)<< pS->st_id << ", ";
		if( (pS->st_id + 1) % 10 == 0 )
		{
			*pOf << endl;
		}
	}
}
Student *searchStudentFromArray(Student arrayOfStudent[], int idToSearch[], int size)
{
	for(int j = 0 ; j < NUM_STUDENTS ; j++)//size=i 10��
	{
		if(idToSearch[size] == (arrayOfStudent+j)->st_id)
		{
			return arrayOfStudent+j;
			break;
		}
	}
}
Student *searchStudentFromTree(TreeNode *pTN, int idToSearch[], int size)
{
	if (pTN == NULL)
	{
		return NULL;
	} 
	else if(pTN->pSTN->st_id == idToSearch[size] )
	{
		return pTN->pSTN;
	} 
	else if (pTN->pSTN->st_id < idToSearch[size])
	{
		searchStudentFromTree(pTN->pR, idToSearch, size);
	}else{
		searchStudentFromTree(pTN->pL, idToSearch, size);
	}
}
Student *searchStudentFromList(ListOfStudents *pLS, int idToSeach[], int size)
{
	ListNode *pS;
	pS = pLS -> pFirst;
	int count = 0;
	while((pS != NULL) && (count < NUM_STUDENTS))
	{  
		if(pS->pST->st_id == idToSeach[size])
		{
			return pS -> pST;
			break;
		}
		pS = pS -> pNext;
		count++;
	}
}


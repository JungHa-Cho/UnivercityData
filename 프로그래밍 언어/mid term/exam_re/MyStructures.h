/*
*	My Students
*/
typedef struct MyStructures{
	int st_id;
	char last_name[15];
	char first_name[15];
	char department[15];
	int grade;
	double GPA;
	char description[255];;
}Student;
/*
*  Linked List
*/
typedef struct ListNode{
	Student *pST;
	ListNode *pNext;
	ListNode *pPrev;
}ListNode;
typedef struct ListOfStudents{
	int num_student;
	ListNode *pFirst;
	ListNode *pLast;
}ListOfStudents;
/*
*  Binary Tree
*/
typedef struct TreeNode{
	Student *pSTN;
	TreeNode *pL;
	TreeNode *pR;
}TreeNode;

typedef struct StudentTree{
	int num_student;
	TreeNode *pTN;
}StudentTree;

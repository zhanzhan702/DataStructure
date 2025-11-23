#include<iostream>
#include<string>
#include <iomanip>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;		//Status 是函数返回值类型，其值是函数结果状态代码。
typedef int ElemType;	 //ElemType 为可定义的数据类型，此设为int类型

#define MAXSIZE 100			//顺序表可能达到的最大长度

typedef struct {
	ElemType* elem;			//存储空间的基地址
	int length;				//当前长度
}SqList;

Status InitList_Sq(SqList& L);

Status GetElem(SqList L, int i, ElemType& e);

int LocateElem_Sq(SqList L, ElemType e);

Status ListInsert_Sq(SqList& L, int i, ElemType e);

Status ListDelete_Sq(SqList& L, int i, ElemType& e);

void Show(SqList& L);

Status InitList_Sq(SqList& L) {				//算法2.1 顺序表的初始化
	//构造一个空的顺序表L
	L.elem = new ElemType[MAXSIZE];		//为顺序表分配一个大小为MAXSIZE的数组空间
	if (!L.elem)  exit(OVERFLOW);		//存储分配失败
	L.length = 0;							//空表长度为0
	return OK;
}

Status GetElem(SqList L, int i, ElemType& e) {	//算法2.2 顺序表的取值
	//顺序表的取值
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	cout << e << endl;
	return OK;
}

int LocateElem_Sq(SqList L, ElemType e) {		//算法2.2 顺序表的查找
	//顺序表的查找
	for (int i = 0; i < L.length; i++)
		if (L.elem[i] == e) return i + 1;
	return 0;
}

Status ListInsert_Sq(SqList& L, int i, ElemType e) {		//算法2.3 顺序表的插入
	//在顺序表L中第i个位置之前插入新的元素e
	//i值的合法范围是1<=i<=L.length+1
	if (i<1 || i>L.length + 1)	return ERROR;		//i值不合法
	if (L.length == MAXSIZE)	return ERROR;		//当前存储空间已满
	for (int j = L.length - 1; j >= i - 1; j--)
		L.elem[j + 1] = L.elem[j];					//插入位置及之后的元素后移
	L.elem[i - 1] = e;								//将新元素e放入第i个位置
	++L.length;									//表长增1
	return OK;
}

Status ListDelete_Sq(SqList& L, int i, ElemType& e) {		//算法2.5 顺序表的删除
	//在顺序表L中删除第i个元素，并用e返回其值
	//i值的合法范围是1<=i<=L.length
	if (i<1 || i>L.length) {
		cout << "删除位置不合法！" << endl;
		return ERROR;		//i值不合法
	}
	e = L.elem[i - 1];								//将欲删除的元素保留在e中
	for (int j = i; j <= L.length; j++)
		L.elem[j - 1] = L.elem[j];					//被删除元素之后的元素前移
	--L.length;									//表长减1
	return OK;
}

void Show(SqList& L) {
	for (int i = 0; i < L.length; i++)
		cout << L.elem[i]<<" ";
	cout << endl;
}

int main() {
	SqList L;
	if (InitList_Sq(L))						//创建顺序表
		cout << "成功建立顺序表\n\n";
	else
		cout << "顺序表建立失败\n\n";

	ListInsert_Sq(L, 1, 87);
	ListInsert_Sq(L, 1, 78);
	ListInsert_Sq(L, 1, 34);
	ListInsert_Sq(L, 1, 27);
	ListInsert_Sq(L, 1, 88);
	ListInsert_Sq(L, 1, 65);
	ListInsert_Sq(L, 1, 50);
	ListInsert_Sq(L, 1, 43);
	ListInsert_Sq(L, 1, 29);

	Show(L);

	cout << "顺序表的获取" << endl;
	ElemType e;
	cout << "顺序表第五位为：" << endl;
	GetElem(L, 5, e);
	cout << endl;

	cout << "顺序表的查找" << endl;
	e = 78;
	int res = LocateElem_Sq(L, e);
	cout << e << "在顺序表第" << res << "位" << endl << endl;

	e = 99;
	res = LocateElem_Sq(L, e);
	cout << e << "在顺序表第" << res << "位" << endl << endl;

	cout << "顺序表的删除" << endl;
	cout << "删除顺序表的第几位：";
	int n;
	cin >> n;
	if(ListDelete_Sq(L, n, e))
		cout << "其值为：" << e << endl;
	cout << "删除顺序表的第几位：";
	cin >> n;
	if(ListDelete_Sq(L, n, e))
		cout << "其值为：" << e << endl;

	return 0;
}
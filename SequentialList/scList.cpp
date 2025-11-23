#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;		//Status 是函数返回值类型，其值是函数结果状态代码。
//typedef int ElemType;	 //ElemType 为可定义的数据类型，此设为int类型

#define MAXSIZE 100			//顺序表可能达到的最大长度

class ElemType {
private:
	string id, name, te;
	int score;
public:
	ElemType();
	ElemType(const string& id, const string& neme, const string& te, int score);
	ElemType(const ElemType& other);
	friend ostream& operator<<(ostream& os, const ElemType& person);
	bool operator==(const ElemType& other)const;
};

typedef struct {
	ElemType* elem;			//存储空间的基地址
	int length;				//当前长度
}SC;

Status InitList_Sq(SC& L);

Status GetElem(SC L, int i, ElemType& e);

int LocateElem_Sq(SC L, ElemType e);

Status ListInsert_Sq(SC& L, int i, ElemType e);

Status ListDelete_Sq(SC& L, int i, ElemType& e);

void Show(SC& L);

Status InitList_Sq(SC& L) {				//算法2.1 顺序表的初始化
	//构造一个空的顺序表L
	L.elem = new ElemType[MAXSIZE];		//为顺序表分配一个大小为MAXSIZE的数组空间
	if (!L.elem)  exit(OVERFLOW);		//存储分配失败
	L.length = 0;							//空表长度为0
	return OK;
}

Status GetElem(SC L, int i, ElemType& e) {	//算法2.2 顺序表的取值
	//顺序表的取值
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	cout << e << endl;
	return OK;
}

int LocateElem_Sq(SC L, ElemType e) {		//算法2.2 顺序表的查找
	//顺序表的查找
	for (int i = 0; i < L.length; i++)
		if (L.elem[i] == e) return i + 1;
	return 0;
}

Status ListInsert_Sq(SC& L, int i, ElemType e) {		//算法2.3 顺序表的插入
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

Status ListDelete_Sq(SC& L, int i, ElemType& e) {		//算法2.5 顺序表的删除
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

void Show(SC& L) {
	cout << "==================学生选课表==================" << endl;
	for (int i = 0; i < L.length; i++)
		cout << L.elem[i];
	cout << "==================学生选课表==================" << endl << endl;
}

ElemType::ElemType(){}

ElemType::ElemType(const string& id, const string& name, const string& te, int score) :id(id), name(name), te(te), score(score) {}

ElemType::ElemType(const ElemType& other) :id(other.id), name(other.name), te(other.te), score(other.score) {}

ostream& operator<<(ostream& os, const ElemType& person) {
	os << left;
	os << "学号:" << setw(3) << person.id << ",课程名:" << setw(8) << person.name << ",老师:" << setw(6) << person.te << ",成绩:" << setw(3) << person.score << endl;
	return os;
}

bool ElemType::ElemType::operator==(const ElemType& other)const {
	return this->id == other.id && this->name == other.name && this->score == other.score;
}

int main()
{
	SC L;
	if (InitList_Sq(L))						//创建学生选课表
		cout << "成功建立学生选课表\n\n";
	else
		cout << "学生选课表建立失败\n\n";

	ListInsert_Sq(L, 1, ElemType("101","操作系统","卢春燕",90));
	ListInsert_Sq(L, 1, ElemType("102", "数据结构", "卢春燕", 85));
	ListInsert_Sq(L, 1, ElemType("103", "数据库", "袁秋慧", 60));
	ListInsert_Sq(L, 3, ElemType("104", "C语言", "洪伟", 70));
	ListInsert_Sq(L, 3, ElemType("105", "高等数学", "刘仪伟", 88));
	ListInsert_Sq(L, 5, ElemType("106", "大学物理", "黄楷华", 99));

	Show(L);

	cout << "学生选课表的获取" << endl;
	ElemType e;
	cout << "学生选课表第五位为："<<endl;
	GetElem(L, 5, e);
	cout << endl;

	cout << "学生选课表的查找" << endl;
	int res = LocateElem_Sq(L, ElemType("105", "高等数学", "刘仪伟", 88));
	cout << e << "其在学生选课表第" << res << "位" << endl << endl;

	res = LocateElem_Sq(L, ElemType("103", "操作系统", "卢春燕", 90));
	cout << e<<"在学生选课表第" << res << "位" << endl << endl;

	cout << "学生选课表的删除" << endl;
	cout << "删除学生选课表的第几位：" ;
	int n;
	cin >> n;
	ListDelete_Sq(L, n, e);
	cout << "其值为：" << e << endl;
	cout << "删除学生选课表的第几位：";
	cin >> n;
	ListDelete_Sq(L, n, e);
	
	return 0;
}
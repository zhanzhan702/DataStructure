// 头文件
#include <iostream>
#include <vector>
using namespace std;

// 宏定义
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;     // Status 是函数返回值类型，其值是函数结果状态代码。
typedef char ElemType;  // ElemType 为可定义的数据类型，此设为char类型

//(1)单链表的定义
typedef struct LNode {
    ElemType data;       // 结点的数据域
    struct LNode* next;  // 结点的指针域
} LNode, *LinkList;      // LinkList为指向结构体LNode的指针类型

//==============函数声明======
Status InitList_L(LinkList& L);
void CreateList_F(LinkList& L, const vector<ElemType>& a);  // 使用vector容器保存elem，添加&减少拷贝数组的内存开销
void CreateList_L(LinkList& L, const vector<ElemType>& a);
void printList(const LinkList L);  // 对不改变链表数据的函数添加const
Status GetElem_L(const LinkList L, int i, ElemType& e);
LNode* LocateElem_L(LinkList L, ElemType e);
Status ListInsert_L(LinkList& L, int i, ElemType e);
int Length(const LinkList L);
//==============函数声明结束===

// 单链表的基本操作实现(并列关系)
//(2)初始化，空表
Status InitList_L(LinkList& L) {
    L = new LNode;   // 生成新结点作为头结点，用头指针L指向头结点
    L->next = NULL;  // 头结点的指针域置空
    return OK;
}

//(3)前插法创建单链表
void CreateList_F(LinkList& L, const vector<ElemType>& a) {
    L = new LNode;
    L->next = NULL;
    L->data = 0;           // 使用头节点的data数据域将表长度存在char里,要注意数据量大小，防止char溢出
    for (auto& ele : a) {  // 使用现代C++特性auto自动识别elem类型，并遍历容器
        L->data++;
        LinkList p = new LNode;
        p->data = ele;
        p->next = L->next;
        L->next = p;
    }
}

//(3)尾插法创建单链表
void CreateList_L(LinkList& L, const vector<ElemType>& a) {
    LNode *r, *p;
    L = new LNode;
    L->next = NULL;
    r = L;
    L->data = 0;  // 使用头节点的data数据域将表长度存在char里
    for (auto& ele : a) {
        L->data++;
        p = new LNode;
        p->data = ele;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

//(4)输出链表中所有元素
void printList(const LinkList L) {
    LNode* p;
    if (!L->next) cout << "The list is empty." << endl;
    for (p = L->next; p; p = p->next) cout << p->data << ' ';
    cout << endl << endl;
}

//(5)在带头结点的单链表L中查找第i个元素
Status GetElem_L(const LinkList L, int i, ElemType& e) {
    int j;
    LNode* p;
    p = L->next;
    j = 1;                // 初始化，p指向第一个结点，j为计数器
    while (j < i && p) {  // 顺链域向后扫描，直到p指向第i个元素或p为空
        p = p->next;
        ++j;
    }
    if (!p || j > i) return ERROR;  // 第i个元素不存在
    e = p->data;                    // 取第i个元素
    return OK;
}

//(6)在带头结点的单链表L中查找值为e的元素
LNode* LocateElem_L(LinkList L, ElemType e) {
    LNode* p;
    p = L->next;
    while (p && p->data != e) p = p->next;  // 寻找满足条件的结点
    return p;                               // 返回L中的值为e的数据元素的位置，查找失败返回NULL
}

//(7)在带头结点的单链表L中第i个位置之前插入元素e
Status ListInsert_L(LinkList& L, int i, ElemType e) {
    if (i < 1 || i > L->data + 1) return ERROR;  // 将检查i的范围前提
    int j;
    LNode *p, *s;
    p = L;
    j = 0;
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    }  // 寻找第i-1个结点
    s = new LNode;      // 生成新结点s
    s->data = e;        // 将结点s的数据域置为e
    s->next = p->next;  // 将结点s插入L中
    p->next = s;
    L->data++;  // 改变表长
    return OK;
}

//(8)在带头结点的单链表L中，删除第i个位置，并由e返回值
Status ListDelete_L(LinkList& L, int i, ElemType& e) {
    LNode *p, *q;
    int j;
    p = L;
    j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        ++j;
    }  // 寻找第i-1个结点
    if (!(p->next) || j > i - 1) return ERROR;  // i大于表长+1或者小于1
    q = p->next;                                // 临时保存被删结点的地址以备释放
    p->next = q->next;                          // 改变删除结点前驱结点的指针域
    e = q->data;                                // 保存删除结点的数据域
    delete q;                                   // 释放删除结点的空间
    L->data--;                                  // 改变表长
    return OK;
}

//(9)表长
int Length(const LinkList L) {
    if (L->data < 0) {//当char溢出时使用迭代求表长
        LNode* p;
        int len = 0;
        for (p = L->next; p; p = p->next) len++;
        return len;
    }
    return L->data;  // 将char转换为int记录表长，将O(n)级别的时间复杂度转换为O(1)
}

int main() {
    //(1)定义单链表
    LinkList L;

    //(2)初始化空表
    if (InitList_L(L))                                        // 建立一个单链表
        cout << "Successfully created the linked list!\n\n";  // 将输出改为全英文防止出现中文乱码

    //(3)前插法或尾插法创建单链表
    int n;
    cout << "Please input the length of link list:" << endl;
    cin >> n;
    vector<ElemType> a(n);
    for (auto& ele : a) cin >> ele;
    cout << endl << endl;
    // CreateList_F(L, a);
    CreateList_L(L, a);

    //(4)输出表中所有元素
    printList(L);

    //(5)取值
    int pos;
    ElemType e;
    cout << "Which element do you want to query:";
    cin >> pos;
    if (GetElem_L(L, pos, e))
        cout << "The " << pos << " element is:" << e << endl << endl;
    else
        cout << "The input position is unreasonable" << endl << endl;

    //(6)按值查找
    ElemType key;
    cout << "Enter the element you want to search for:";
    cin >> key;
    LNode* p = LocateElem_L(L, key);
    if (!p)  // 若元素在表中不存在
        cout << "The element is not in the list." << endl << endl;
    else
        cout << p->data << " is in the list." << endl << endl;

    //(7)插入
    cout << "Enter the element to insert:";
    cin >> e;
    cout << "Enter the position to insert:";
    cin >> pos;
    if (ListInsert_L(L, pos, e)) {
        cout << "The elements in the table after insertion are:" << endl;
        printList(L);
    } else
        cout << "The insertion position is unreasonable" << endl << endl;

    //(8)删除
    cout << "Enter the position to delete:";
    cin >> pos;
    if (ListDelete_L(L, pos, e)) {
        cout << "The deleted element is:" << e << endl;
        cout << "The elements in the table after deletion are:";
        printList(L);
    } else
        cout << "Delete position is unreasonable" << endl << endl;

    //(9)求当前的表长
    cout << "The current length of the linked list is:" << Length(L) << endl;

    return 0;
}

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 100
#include <stdio.h>
#include <string.h>
// 1. Định nghĩa struct TuDien, Node

// 3. Menu chính cho người dùng chọn thao tác
// 4. Hàm main
typedef struct tuLoai
{
	char tenDaydu[10];
	char kyhieu[6];
}tuLoai;

typedef struct tuDien
{
	char tu[50];
	char loaitu[30];
	char nghia[150];
	char vidu[100];
}tuDien;

typedef struct node
{
	tuDien data;
	node *pLeft, *pRight;
}node, *tree;

typedef struct Stacknode
{
	node* treenode;
	Stacknode* next;
}; 

typedef struct Stack
{
	Stacknode* top;
} Stack;
extern Stack S;
extern tree T;
// Ham thao tac tren Stack
int isEmpty(Stack *S);
int isFull(Stack *S);
void initStack(Stack *S);
void push(Stack *S, node* a);
node* pop(Stack* S);
// 2. Các hàm xử lý BST:
int kiemtrachu(char str[]);
void nhapChuoi(char str[], int size);
void switchType(char str[], tuLoai typelist[]);
//    - Tạo node mới
int InsertNode(tree* T, tuDien x);
//    - Thêm từ vào BST
void themTu(tree* T);
//    - Xóa từ khỏi BST
//  Cach 1
//node* timMinphai(node* a);
//node* xoaTu(tree* T, char tucanxoa[]);
//  Cach 2
void Remove(tree* T, char tucanxoa[]);
void SearchStandFor(tree* pHuy, tree* pTT);
//    - Tìm kiếm từ
node* timTuAV(tree T, char tucantim[]);
node* timTuVA(tree T, char tucantim[]);
//    - Sửa nghĩa của từ
int capNhattu(tree T, char tucapnhat[]);
//    - Duyệt BST để in danh sách từ
void LNRstdout(tree* T);
void xuat1(tuDien a);
void ghiChu();
//    - Đọc file
int docFile(tree* T, const char* filename);
//    - Ghi file
int ghiFile(tree* T, const char* filename);
void LNRghifile(tree* T, FILE* f);
//    - Bỏ khoảng cách dầu và cuối của chuỗi để đưa vào struct
void trim(char str[]);
// Xoa toan bo danh sach
void freeTree(tree* T);
//    - Xoa lich su tim kiem
void freeStack(Stack* S);

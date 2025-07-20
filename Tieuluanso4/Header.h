#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
// 1. Định nghĩa struct TuDien, Node

// 3. Menu chính cho người dùng chọn thao tác
// 4. Hàm main
typedef struct
{
	char tenDaydu[10];
	char kyhieu[6];
}tuLoai;
typedef struct 
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
extern tree T;
// 2. Các hàm xử lý BST:
int kiemtrachu(char str[]);
void nhapChuoi(char str[], int size);
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
node* timTu(tree T, char tucantim[]);
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
//    - Bỏ khoảng cách dầu và cuối của chuỗi để đưa vào struct
void trim(char str[]);
// Xoa toan bo danh sach
void freeTree(tree* T);

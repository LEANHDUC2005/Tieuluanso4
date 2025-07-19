#pragma execution_character_set("utf-8")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Header.h"
tree T = NULL;
int kiemtrachu(char str[])
{
	int dem = 0;
	while (str[dem] != '\0')  // Duyet ky tu den het chuoi
	{
		if (isdigit(str[dem])) return 0;
		dem++;
	}
	return 1;
}

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void nhapChuoi(char str[], int size)
{
	void clearInputBuffer();
	fgets(str, size, stdin);
	str[strcspn(str, "\n")] = '\0';
}
int kiemtraloaitu(char str[])
{
		tuLoai typelist[] = { {"danh tu","n"},
							{"dong tu","v"},
							{"tinh tu","adj"},
							{"trang tu","adv"},
							{"dai tu","pn"},
							{"gioi tu","pps"},
							{"lien tu","cont"} };
		for (int i = 0; i < sizeof(typelist)/sizeof(typelist[0]) ; i++)
		{
			if (_strcmpi(str, typelist[i].tenDaydu) == 0)
			{
				strcpy(str, typelist[i].kyhieu);
				return 1;
			}
		}
		return 0;
}
int InsertNode(tree* T, tuDien x)
{
	if (*T == NULL)
	{
		*T = (node*)malloc(sizeof(node));
		if (*T == NULL)
		{
			return -1; // Khong cap phat duoc bo nho
		}
		(*T)->data = x;
		(*T)->pLeft = (*T)->pRight =NULL;
		return 1;	
	}
	else
	{
		if (_strcmpi((*T)->data.tu, x.tu) == 0)
		{
			return 0;
		}
		else
		{
			if (_strcmpi((*T)->data.tu, x.tu) > 0)
			{
				return InsertNode(&(*T)->pLeft, x);
			}
			else
			{
				return InsertNode(&(*T)->pRight, x);
			}
		}
	}
}
//    - Thêm từ vào BST
void themTu(tree* T)
{
	tuDien a;
	while (true)
	{
		printf("| Nhập từ ( nhập 0 để kết thúc ): ");
		nhapChuoi(a.tu, sizeof(a.tu));
		if(strcmp(a.tu, "0") == 0) return;
		if (!kiemtrachu(a.tu))
		{
			printf("| LỖI ! Tên từ không được chứa ký tự số (1-8) hay kí tự đặc biệt.\n");
			continue;
		}
		do
		{
			printf("| Nhập loại của từ ( nhập 0 để kết thúc )\n");
			printf("| Vi du: Danh tu, danh tu , n\n");
			printf("| : ");
			nhapChuoi(a.loaitu, sizeof(a.loaitu));
			if (strcmp(a.loaitu, "0") == 0) return;
			if (!kiemtraloaitu(a.loaitu))
			{
				printf("| LỖI ! Vui lòng nhập đúng loại từ\n");
				continue;
			}
			break;
		} while (true);
		printf("| Nhập nghĩa của từ: ");
		nhapChuoi(a.nghia, sizeof(a.nghia));
		printf("| Nhập ví dụ sử dụng từ trong các câu cụ thể: ");
		nhapChuoi(a.vidu, sizeof(a.vidu));
		int res = InsertNode(T, a);
		if (res == 0)
		{
			printf("| Từ này đã tồn tại trong từ điển !\n");
		}
		else if (res == 1)
		{
			printf("| Thêm từ thành công !\n");
		}
		else
		{
			printf("| LỖI ! Không đủ bộ nhớ !\n");
		}
	}
}
//    - Tìm kiếm từ
node* timTu(tree* T, char tucantim[])
{
	if ((*T) == NULL) return NULL;
	else
	{
		if (strcmp((*T)->data.tu, tucantim) == 0) return *T;
		else
		{
			if (strcmp((*T)->data.tu, tucantim) > 0) return timTu(&(*T)->pLeft, tucantim);
			else return timTu(&(*T)->pRight, tucantim);
		}
	}	
}
//     - Xóa từ khỏi BST
/*
node* xoaTu(tree* T, char tucanxoa[])
{
	if ((*T)==NULL) return NULL;  
	else
	{
		// Nếu x < gốc -> xóa trên cây con trái của gốc
		if (strcmp((*T)->data.tu, tucanxoa) > 0) return xoaTu(&(*T)->pLeft, tucanxoa);   
		// Nếu x > gốc -> xóa trên cây con phải của gốc
		else if (strcmp((*T)->data.tu, tucanxoa) < 0) return xoaTu(&(*T)->pRight, tucanxoa);
		else
		{
			// Neu A ko co con trai va ko co con phai, TH1: a la node la
			if ((*T)->pLeft == NULL && (*T)->pRight == NULL )
			{
				free(*T);
				(*T) = NULL;
			}
			// Neu A chi co 1 con trai , TH 2a:
			else if ((*T)->pLeft != NULL && (*T)->pRight == NULL)
			{
				node* temp = (*T)->pLeft;
				free(*T);
				(*T) = temp;
			}
			// Neu A chi co 1 con phai , TH 2b:
			else if ((*T)->pLeft == NULL && (*T)->pRight != NULL)
			{
				node* temp = (*T)->pRight;
				free(*T);
				(*T) = temp;
			}
			// Neu A co ca 2 con , TH3:
			else     
			{
				// Tim node nho nhat cua cay con phai
				node* temp = timMinphai((*T)->pRight);
				(*T)->data = temp->data;
				(*T)->pRight = xoaTu(&(*T)->pRight, temp->data.tu);
			}
		}
	}
	return (*T);
}
// Tim gia tri trai nhat ben phai
node* timMinphai(node *a)
{
	while (a->pLeft != NULL)
	{
		a = a->pLeft;
	}
	return a;
} */
// Cách 2
void Remove(tree* T, char tucanxoa[])
{
	if ((*T) != NULL)
	{
		if (strcmp((*T)->data.tu, tucanxoa) > 0)
			Remove(&(*T)->pLeft, tucanxoa);
		else if (strcmp((*T)->data.tu, tucanxoa) < 0)
			Remove(&(*T)->pRight, tucanxoa);
		else // gia tri cua goc = gia tri can xoa
		{
			node* pHuy = (*T);     // Luu phan tu can xoa
			// phan tu co 1 cay con phai
			if ((*T)->pLeft == NULL)        
				(*T) = (*T)->pRight;        // cha->Right = cha->Right->Right = chau'
			// phan tu co 1 cay con trai
			else if ((*T)->pRight == NULL)  
				(*T) = (*T)->pLeft;         // cha->Left = cha->Left->Left = chau'
			else SearchStandFor(&pHuy, &(*T)->pRight);
			free(pHuy);
		}
		printf("| Xóa từ %s thành công !\n", tucanxoa);
	}
	else
	{
		printf("| Từ %s không tồn tại trong từ điển\n", tucanxoa);
	}
}
	
void SearchStandFor(tree* pHuy, tree* pTT)
{
	if ((*pTT)->pLeft != NULL)
	{
		SearchStandFor(&(*pHuy), &(*pTT)->pLeft);
	}
	else
	{
		(*pHuy)->data = (*pTT)->data;
		(*pHuy) = (*pTT);
		(*pTT) = (*pTT)->pRight;
	}
}
//    - Tìm kiếm từ
// Duyet LNR 
tree* Timtu(tree* T, char tucantim[])
{
	if ((*T) == NULL) return NULL;
	else
	{
		if (strcmp((*T)->data.tu, tucantim) > 0 ||
			strcmp((*T)->data.loaitu, tucantim) > 0)
			return Timtu(&(*T)->pLeft, tucantim);
		else if (strcmp((*T)->data.tu, tucantim) < 0 ||
			strcmp((*T)->data.loaitu, tucantim) < 0)
			return Timtu(&(*T)->pRight, tucantim);
		else return T;	
	}
}
//    - Sửa nghĩa của từ
int capNhattu(tree* T, char tucapnhat[])
{
		tree* a = Timtu(T, tucapnhat);
		if (a == NULL) return 0;
		else
		{
			printf("| Nhập nghĩa mới của từ: ");
			nhapChuoi((*a)->data.nghia, sizeof((*a)->data.nghia));
			printf("| Nhập ví dụ sử dụng từ trong các câu cụ thể: ");
			nhapChuoi((*a)->data.vidu, sizeof((*a)->data.vidu));
			printf("| Sửa thông tin của từ thành công !\n");
			return 1;
		}
}
//    - Duyệt BST để in danh sách từ
// Duyet LNR
void LNRstdout(tree* T)
{
	if ((*T) != NULL)
	{
		LNRstdout(&(*T)->pLeft);
		fprintf(stdout,"| %-15s | %-8s | %-36s | %-47s |\n",
			(*T)->data.tu,
			(*T)->data.loaitu,
			(*T)->data.nghia,
			(*T)->data.vidu);
		LNRstdout(&(*T)->pRight);
	}
}
void LNRghifile(tree* T, FILE *f)
{
	if ((*T) != NULL)
	{
		LNRghifile(&(*T)->pLeft,f);
		fprintf(f,"| %-15s | %-8s | %-36s | %-47s |\n",
			(*T)->data.tu,
			(*T)->data.loaitu,
			(*T)->data.nghia,
			(*T)->data.vidu);
		LNRghifile(&(*T)->pRight,f);
	}
}
//printf("| %-15s | %-12s | %-22s | %-25s |\n", "Tu", "Loai tu", "Nghia", "Vi du");
// In mot phan tu
void xuat1(tuDien a)
{
	printf("| %-15s | %-8s | %-36s | %-47s |\n", "Tu", "Loai tu", "Nghia", "Vi du");
	printf("| %-15s | %-8s | %-36s | %-47s |\n",
			a.tu,
			a.loaitu,
			a.nghia,
			a.vidu);

}
void ghiChu()
{
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
	printf("|   GHI CHU:                                                                                                          |\n");
	printf("|   n: danh tu   v: dong tu   adj: tinh tu   adv: trang tu   pn: dai tu   pps: gioi tu   cont: lien tu                |\n");
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
}
// Ham ghi du lieu ra tep 
int ghiFile(tree* T,const char* filename)
{
	FILE *f = fopen(filename, "w");
	if (f == NULL)
	{
		return 0;
	}
	else
		LNRghifile(T, f);
	fclose(f);
	return 1;
}
// Ham xoa khoang trang de dua vao cac truong cua struct td
void trim(char str[])
{
	int start = 0, end = strlen(str)-1;
	// Xoa khoang cach dau chuoi
	while (isspace(str[start]))
	{
		start++;
	}
	// Xoa khoang trang cuoi chuoi
	while (end >= start && isspace(str[end]))
	{
		end--;
	}
	int i = 0;
	// Dich chuoi ve dau
	while (start <= end)
	{
		str[i++] = str[start++];
	}
	str[i] = '\0';
}

// Ham doc du lieu tu tep
int docFile(tree* T, const char* filename)
{
	FILE* f = fopen(filename, "r");
	if (f == NULL)
	{
		return 0;
	}
	else
	{
		tuDien td;
		char line[300];
		int count = 0, error = 0, landem = 0;
		while (fgets(line, sizeof(line), f))
		{
			line[strcspn(line, "\n")] = '\0';        // loai bo dau \n cuoi cung
			int result = sscanf(line, "|%[^|]|%[^|]|%[^|]|%[^|]|\n",
				td.tu,
				td.loaitu,
				td.nghia,
				td.vidu);
			if (result == 4)
			{
							trim(td.tu);                  // loai khoang trang dau va cuoi de dua vao node
			trim(td.loaitu);
			trim(td.nghia);
			trim(td.vidu);
				InsertNode(T, td);
				count++;
			}
			else
			{
				error++;
				printf("Dong %d bi loi: \"%s\" (result = %d)\n", landem, line, result);
			}
			landem++;
		}
		fclose(f);
		printf("| So tu bi doc loi: %d\n", error);
		return count; 
	}
}
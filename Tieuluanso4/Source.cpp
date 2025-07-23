#pragma execution_character_set("utf-8")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Header.h"
Stack S;
tree T = NULL;
tuLoai typelist[] = { {"danh tu","n"},
					{"dong tu","v"},
					{"tinh tu","adj"},
					{"trang tu","adv"},
					{"dai tu","pn"},
					{"gioi tu","pps"},
					{"lien tu","cont"} };
// Cac ham xu ly chuoi, kiem tra du lieu dau vao
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
int kiemtraloaitu(char str[], tuLoai typelist[])
{
		for (int i = 0; i < sizeof(*typelist)/sizeof(typelist[0]) ; i++)
		{
			if (_strcmpi(str, typelist[i].tenDaydu) == 0)
			{
				return i;
			}
		}
		return -1;
}
// CHUYEN LOAI TU DAY DU THANH VIET TAT
void switchType(char str[], tuLoai typelist[])
{
	int vitri = kiemtraloaitu(str, typelist);
	if (vitri < 0)
	{
		printf("Loại từ không hợp lệ !\n");
		return;
	}
	else
	{
		strcpy(str, typelist[vitri].kyhieu);
	}
} 
// Khoi tao Stack
void initStack(Stack *S)
{
	S->top = NULL;
}
int isEmpty(Stack *S)
{
	return (S->top == NULL);
}
int isFull(Stack *S)
{
	return 0;
}
void push(Stack *S, node* a)
{
	if (!isFull(S))
	{
		Stacknode* p = (Stacknode*)malloc(sizeof(Stacknode));
		if (p == NULL)
		{
			printf("Không đủ dung lượng!\n");
		}
		else
		{
			p->treenode = a;
			p->next = S->top;
			S->top = p;
		}
	}
	else
	{
		printf("Danh sách đã đầy!\n");
		return;
	}
}
node* pop(Stack* S)
{
	if (isEmpty(S)) return NULL;
	else
	{
		node* x = S->top->treenode;
		Stacknode* temp = S->top;
		S->top = S->top->next;
		free(temp);
		return x;
	}
}
// Them node vao BST
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
		printf("| Nhập từ ( nhập 0 để kết thúc ): ");    // Nhap tu: nhap 0 de end
		nhapChuoi(a.tu, sizeof(a.tu));
		if(strcmp(a.tu, "0") == 0) return;
		if (!kiemtrachu(a.tu)) // neu tu chua ky tu so hoac ky tu dac biet
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
			if (kiemtraloaitu(a.loaitu, typelist) == -1)  // neu loai tu ko dung voi dinh dang
			{ 
				printf("| LỖI ! Vui lòng nhập đúng loại từ\n");
				continue;
			}
			break;
		} while (true);
		printf("| Nhập nghĩa của từ: "); // nhap nghia cua tu
		nhapChuoi(a.nghia, sizeof(a.nghia));
		printf("| Nhập ví dụ sử dụng từ trong các câu cụ thể: "); // nhap VD su dung
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
node* timTuAV(tree T, char tucantim[])
{
	if (T == NULL) return NULL;
	else
	{
		// x = T->data : tra ve con tro chua x
		if (_strcmpi(T->data.tu, tucantim) == 0) 
			return T;
		else
		{
			// x < T->data : tim tai cay con trai cua T
			if (_strcmpi(T->data.tu, tucantim) > 0) 
				return timTuAV(T->pLeft, tucantim);
			// x < T->data : tim tai cay con phai cua T
			else 
				return timTuAV(T->pRight, tucantim);
		}
	}	
}
// Tim tu Viet Anh - Duyen toan bo cay NLR
node* timTuVA(tree T, char tucantim[])
{
		if (T == NULL) return NULL;
		else
		{
			if (strstr(T->data.nghia, tucantim) != NULL) return T;
			else
			{
				node* ketquatrai = timTuVA(T->pLeft, tucantim);
				if (ketquatrai != NULL) return ketquatrai;
				else return timTuVA(T->pRight, tucantim);			
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
// Xóa từ khỏi từ điển
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
			// phan tu co 2 cay con
			else SearchStandFor(&pHuy, &(*T)->pRight);
			free(pHuy);
			printf("| Xóa từ %s thành công !\n", tucanxoa);
		}
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
//    - Sửa nghĩa của từ
int capNhattu(tree T, char tucapnhat[])
{
	tree a = timTuAV(T, tucapnhat);
	if (a == NULL) return 0; // ko tim duoc tu
	else
	{
		// Sua nghia va vi du cua tu
		printf("| Nhập nghĩa mới của từ: ");                     
		nhapChuoi(a->data.nghia, sizeof(a->data.nghia));
		printf("| Nhập ví dụ sử dụng từ trong các câu cụ thể: ");
		nhapChuoi(a->data.vidu, sizeof(a->data.vidu));
		printf("| Sửa thông tin của từ thành công !\n");
		return 1;
	}
}
//    - Duyệt BST để in danh sách từ ( Left - Node - Right )
// Duyet LNR
void LNRstdout(tree* T)                     // ghi ra man hinh
{
	if ((*T) != NULL)
	{
		LNRstdout(&(*T)->pLeft);		
		fprintf(stdout,"| %-15s | %-10s | %-36s |\n",
			(*T)->data.tu,
			(*T)->data.loaitu,
			(*T)->data.nghia);
		LNRstdout(&(*T)->pRight);
	}
}
void LNRghifile(tree* T, FILE *f)           // ghi ra file txt
{
	if ((*T) != NULL)
	{
		LNRghifile(&(*T)->pLeft,f);
		fprintf(f,"|%s|%s|%s|%s|\n",
			(*T)->data.tu,
			(*T)->data.loaitu,
			(*T)->data.nghia,
			(*T)->data.vidu);
		LNRghifile(&(*T)->pRight,f);
	}
}
// In mot phan tu
// ghi chu
void ghiChu()
{
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
	printf("|   GHI CHÚ                                                                                                           |\n");
	printf("|   n: danh từ   v: động từ   adj: tính từ   adv: trạng từ   pn: đại từ   pps: giới từ   cont: liên từ                |\n");
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
}
// In 1 phan tu
void xuat1(tuDien a)
{
	printf("| %-15s | %-10s | %-36s |\n",
			a.tu,
			a.loaitu,
			a.nghia);
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
		while (fgets(line, sizeof(line), f)) // ghi du lieu cua f vao chuoi line
		{
			line[strcspn(line, "\n")] = '\0';// loai bo dau \n cuoi cung
			int result = sscanf(line, "|%[^|]|%[^|]|%[^|]|%[^|]|",
				td.tu,       // chuan hoa chuoi line dua vao cac truong cua tuDien
				td.loaitu,
				td.nghia,
				td.vidu);
			if (result == 4) // nhan du 4 truong tuDien
			{
				trim(td.tu); // loai khoang trang dau va cuoi de dua vao node
				trim(td.loaitu);
				trim(td.nghia);
				trim(td.vidu);
				InsertNode(T, td);// dua vao cay nhi phan
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
void deletechar(char str[], char c)
{
	int i = 0, j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			str[j++] = str[i];
		}
		i++;
	}
	str[j] = '\0';
}
/*
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
		while (fgets(line, sizeof(line), f)) // ghi du lieu cua f vao chuoi line
		{
			// Tach thanh 4 truong
			// |you|dai tu|ban|you are my best friend|
			char* start = line;
			char* p1 = strchr(start+1, '|'); // tu
			char* p2 = strchr(p1+1, '|');    // loai tu
			char* p3 = strchr(p2+1, '|');    // nghia
			char* p4 = strchr(p3+1, '|');    // vidu
			char* token = strtok(p4 + 1, "\n"); // phan con lai
			if( p1 != NULL && p2 != NULL && p3 != NULL && p4 != NULL ) 
			{
				int len1 = p1 - (start+1); // '|' - 'y' 
				int len2 = p2 - (p1 + 1);  // '|' - 'd'
				int len3 = p3 - (p2 + 1);  // "|' - 'b'
				int len4 = p4 - (p3 + 1);  // '|' - 'y'
				deletechar(token, '|');
				strcpy(td.tu, start + 1); td.tu[len1] = '\0';
				strcpy(td.loaitu, p1 + 1); td.loaitu[len2] = '\0';
				strcpy(td.nghia, p2 + 1); td.nghia[len3] = '\0';
				strcpy(td.vidu, p3 + 1); td.vidu[len4] = '\0';

				InsertNode(T, td);// dua vao cay nhi phan
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
}*/
// Ham xoa toan bo danh sach
void freeTree(tree * T) // Giai phong theo thu tu LRN
{
	if ((*T) != NULL)
	{
		freeTree(&(*T)->pLeft);
		freeTree(&(*T)->pRight);
		free(*T);
	}
	*T = NULL;   // Dat lai con tro tree
}
// Ham xoa toan bo ket qua tim kiem Stack
void freeStack(Stack* S)
{
	Stacknode* temp = S->top;
	while (temp != NULL)
	{
		Stacknode* tempnext = temp->next; // Luu node tiep theo
		free(temp);         // Giai phong node hien tai
		temp = tempnext;    // Cap nhat lai node hien tai 
	}
	S->top = NULL;  // Dat lai con tro top
}

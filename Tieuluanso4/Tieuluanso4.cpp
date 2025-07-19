// Tieuluanso4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma execution_character_set("utf-8")
#include <windows.h>
#include <iostream>
#include "Header.h"
int main()
{
	SetConsoleOutputCP(65001);
	char username[20];
	printf("|=========================== TU DIEN ANH VIET ============================|\n");
	printf("| Nhap ten cua ban:");
	nhapChuoi(username, sizeof(username));
	printf("\n| CHAO MUNG ! %s\n", username);
	int choice;
	do
	{
		printf("\n|=========================================================================|\n");
		printf("|                                Cong cu                                  |\n");
		printf("|=========================================================================|\n");
		printf("|       [1].Them tu vao tu dien     |          [2].Tra cuu tu dien        |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("|                                   |                                     |\n");
		printf("|       [3].Xoa tu khoi tu dien     |          [4].Sua nghia cua tu       |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("|                                   |                                     |\n");
		printf("|       [5].Danh sach tu dien       |          [6].Doc tu dien tu file    |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("|                                   |                                     |\n");
		printf("|       [7].Ghi tu dien ra file     |          [8].Thoat tu dien          |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("| Nhap lua chon cua ban [1-9]:");
		scanf_s("%d", &choice);
		while (getchar() != '\n');
		switch (choice)
		{
			// Them tu vao tu dien
		case 1:
		{
			printf("| Da chon: [Them tu]\n");
			themTu(&T);
			break;
		}
		// Tim kiem tu
		case 2:
		{
			char tucantim[50];
			printf("| Da chon: [Tra cuu]\n");
			printf("| Nhap tu can tra cuu :");
			nhapChuoi(tucantim, sizeof(tucantim));
			node* result = timTu(&T, tucantim);
			if (result == NULL)
			{
				printf("| Khong ton tai tu %s trong tu dien !\n", tucantim);
			}
			else
			{
				printf("|=====================================================================================================================|\n");
				xuat1(result->data);
				ghiChu();
				printf("|_____________________________________________________________________________________________________________________|\n");
			}
			break;
		}
		// Xoa tu khoi tu dien
		case 3:
		{
			char tucanxoa[50];
			printf("| Da chon : [Xoa tu]\n");
			printf("| Nhap tu can xoa khoi tu dien:");
			nhapChuoi(tucanxoa, sizeof(tucanxoa));
			/* dungcho node* xoaTu(tree* T, char tucanxoa[])
			if (xoaTu(&T, tucanxoa) == NULL)
			{
				printf("| Tu %s khong ton tai trong tu dien!\n", tucanxoa);
			}
			else
			{
				printf("| Xoa thanh cong !\n"); 
			}*/
		    Remove(&T, tucanxoa);
			break;
		}
		// Sua nghia cua tu
		case 4:
		{
			printf("| Da chon: [Sua nghia cua tu]\n");
			char tucansua[50];
			printf("| Nhap tu can sua: ");
			nhapChuoi(tucansua, sizeof(tucansua));
			if (!capNhattu(&T, tucansua))
			{
				printf("| Tu %s khong ton tai trong tu dien!\n", tucansua);
			}
			else
			{
				printf("| Cap nhat thanh cong!\n");
			}
			break;
		}
		// Xuat danh sach tu dien
		case 5:
		{
			printf("| Da chon [Xuat danh sach]\n");
			printf("|================================================== DANH SACH TU DIEN ================================================|\n");
			ghiChu();
			printf("| %-15s | %-8s | %-36s | %-47s |\n", "Tu", "Loai tu", "Nghia", "Vi du");
			LNRstdout(&T);
			ghiChu();
			break;
		}
		// Doc tu dien tu tep
		case 6:
		{
			printf("| Da chon [Doc tu dien tu file]\n");
			char filename[50];
			printf("| Nhap file muon doc du lieu: ");
			nhapChuoi(filename, sizeof(filename));
			int result = docFile(&T, filename);
			if (!result)
			{
				printf("| File %s khong ton tai, vui long kiem tra ten file !\n", filename);
			}
			else
			{
				printf("| Doc file thanh cong !\n");
				printf("| So tu da doc : %d", result);
			}
			break;
		}
		// Ghi tu dien ra tep
		case 7:
		{
			printf("| Da chon [Ghi tu dien ra file]\n");
			char filename[50];
			printf("| Nhap file muon ghi du lieu: ");
			nhapChuoi(filename, sizeof(filename));
			if (!ghiFile(&T, filename))
			{
				printf("| File %s khong ton tai, vui long kiem tra ten file !\n", filename);
			}
			else
			{
				printf("| Ghi file thanh cong !\n");
			}
			break;
		}
		case 8: break;
		default: printf("| Lua chon khong hop le ! Vui long nhap lai lua chon cua ban.\n");
		}
	} while (choice != 8);
	printf("|========================================= TAM BIET =======================================|\n");
	return 0;
}


	

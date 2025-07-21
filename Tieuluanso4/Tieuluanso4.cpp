// Tieuluanso4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma execution_character_set("utf-8")
#include <windows.h>
#include <iostream>
#include "Header.h"
int main()
{
	initStack(&S);
	SetConsoleOutputCP(65001);
	char username[20];
	printf("|=========================== TỪ ĐIỂN ANH VIỆT ============================|\n");
	printf("| Nhập tên của bạn:");
	nhapChuoi(username, sizeof(username));
	printf("\n| CHÀO MỪNG ! %s\n", username);
	int choice;
	do
	{
		printf("\n|=========================================================================|\n");
		printf("|                                Công cụ                                  |\n");
		printf("|=========================================================================|\n");
		printf("|       [1].Thêm từ vào từ điển     |          [2].Tra cứu từ điển        |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("|                                   |                                     |\n");
		printf("|       [3].Xóa từ khỏi từ điển     |          [4].Sửa nghĩa của từ       |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("|                                   |                                     |\n");
		printf("|       [5].Danh sach tu dien       |          [6].Đọc từ điển từ file    |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("|                                   |                                     |\n");
		printf("|       [7].Ghi từ điển ra file     |          [8].Xem lai tu da tra      |\n");
		printf("|___________________________________|_____________________________________|\n");
		printf("| Nhập lựa chọn của bạn [1-9] ( nhap 9 de thoat ):");
		scanf_s("%d", &choice);
		while (getchar() != '\n');
		switch (choice)
		{
			// Them tu vao tu dien
		case 1:
		{
			printf("| Đã chọn: [Thêm từ]\n");
			themTu(&T);
			break;
		}
		// Tim kiem tu
		case 2:
		{
			char tucantim[50];
			printf("| Đã chọn: [Tra cứu]\n");
			printf("| Nhập từ cần tra cứu :");
			nhapChuoi(tucantim, sizeof(tucantim));
			node* result = timTu(T, tucantim);
			if (result == NULL)
			{
				printf("| Không tồn tại từ %s trong từ điển !\n", tucantim);
			}
			else
			{
				push(&S, result);
				printf("|=====================================================================================================================|\n");
				printf("| %-15s | %-8s | %-36s | %-47s |\n", "Tu", "Loai tu", "Nghia", "Vi du");
				xuat1(result->data);
				ghiChu();
			}
			break;
		}
		// Xoa tu khoi tu dien
		case 3:
		{
			char tucanxoa[50];
			printf("| Đã chọn : [Xóa từ]\n");
			printf("| Nhập từ cần xóa khỏi từ điển:");
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
			printf("| Đã chọn: [Sửa nghĩa của từ]\n");
			char tucansua[50];
			printf("| Nhập từ cần sửa: ");
			nhapChuoi(tucansua, sizeof(tucansua));
			if (!capNhattu(T, tucansua))
			{
				printf("| Từ %s không tồn tại trong từ điển !\n", tucansua);
			}
			else
			{
				printf("| Cập nhật thành công !\n");
			}
			break;
		}
		// Xuat danh sach tu dien
		case 5:
		{
			printf("| Đã chọn [Xuất danh sách]\n");
			printf("|================================================== DANH SÁCH TỪ ĐIỂN ================================================|\n");
			ghiChu();
			printf("| %-15s | %-8s | %-36s | %-47s |\n", "Tu", "Loai tu", "Nghia", "Vi du");
			LNRstdout(&T);
			ghiChu();
			break;
		}
		// Doc tu dien tu tep
		case 6:
		{
			printf("| Đã chọn [Đọc từ điển từ file]\n");
			char filename[50];
			printf("| Nhập file muốn đọc dữ liệu: ");
			nhapChuoi(filename, sizeof(filename));
			int result = docFile(&T, filename);
			if (!result)
			{
				printf("| File %s không tồn tại, vui lòng thực hiện với file khác !\n", filename);
			}
			else
			{
				printf("| Đọc file thành công !\n");
				printf("| Số từ đã đọc được : %d", result);
			}
			break;
		}
		// Ghi tu dien ra tep
		case 7:
		{
			printf("| Đã chọn [Ghi từ điển ra file]\n");
			char filename[50];
			printf("| Nhập tên file muốn ghi dữ liệu: ");
			nhapChuoi(filename, sizeof(filename));
			if (!ghiFile(&T, filename))
			{
				printf("| File %s không tồn tại, vui lòng thực hiện với file khác !\n", filename);
			}
			else
			{
				printf("| Ghi file thành công !\n");
			}
			break;
		}
		// Xem lich cac tu da luu
		case 8:
		{
			printf("| Da chon [Xem lai tu da tra]\n");
			printf("|=================================================== LICH SU TIM KIEM ================================================|\n");
			ghiChu();
			printf("| %-15s | %-8s | %-36s | %-47s |\n", "Tu", "Loai tu", "Nghia", "Vi du");
			while (!isEmpty(&S))
			{
				tuDien td = pop(&S);
				xuat1(td);
			}
			printf("|---------------------------------------------------------------------------------------------------------------------|\n");
		}break;
		default: printf("| Lựa chọn không hợp lệ ! Vui lòng nhập lại lựa chọn của bạn.\n"); break;
		}
	} while (choice != 9);
	printf("|========================================= TẠM BIỆT =======================================|\n");
	freeTree(&T);
	return 0;
}


	

#pragma once
#include <stdio.h> // để xài lệnh system("cls")
#include <conio.h> // để lấy cái hàm _getch trong hàm main
#include <windows.h> // để sử dụng cái cấu trúc COORD trong hàm gotoXY

// Di chuyển con trỏ console đến vị trí có tọa độ (x, y)
void gotoXY (int x, int y);

// Xóa con trỏ nháy
void noCursorType();

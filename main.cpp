//TUI CODE BẰNG VISUAL STUDIO 2019 VÀ CHẠY ĐƯỢC RỒI, MẤY ÔNG XÀI CÁI KHÁC THÌ CÓ 
//GÌ NÓ MÀ BÁO LỖI THÌ CÓ GÌ CHỈNH LẠI CHO NÓ PHÙ HỢP VỚI TRÌNH BIÊN DỊCH CỦA MẤY ÔNG 
#include <iostream>
#include <ctime>// thư viện để xài hàm random miếng mồi
#include "Snake.h"
using namespace std;
#define Dot_Ran 254 //254 là kí hiệu hình vuông trong mã ASCII
#define MAX 100 // con rắn dài tối đa 100 đơn vị
#define LEN 1 // hướng di chuyển
#define XUONG 2
#define TRAI 3
#define PHAI 4
#define TUONG_TREN 2 //khoảng cách để xây dựng tường
#define TUONG_DUOI 20
#define TUONG_TRAI 2
#define TUONG_PHAI 70
// toa độ vẽ rắn vẽ tường
struct toado { 
	int x;
	int y;
};

toado snake[MAX]; // tạo mảng chứa tọa độ các đốt rắn
int soDot = 3; //khởi tạo số đốt rắn

// khởi tạo vị trí rắn khi mới bắt đầu vào game
void taoSnake() { 
	snake[0].x = 16; 
	snake[1].x = 15; 
	snake[2].x = 14; 
	snake[0].y = snake[1].y = snake[2].y = 5;
}

// di chuyển con rắn
toado moveSnake(int huong) {
	toado duoirancu = snake[soDot - 1]; // lưu lại vi tri đuôi của con rắn để xóa nó khi con rắn di chuyển tại vì không xóa thì con rắn sẽ tự động dài ra theo vòng lặp
	for (int i = soDot - 1; i > 0; i--) // thân con rắn khi di chuyển
		snake[i] = snake[i - 1];
	switch (huong) { // đầu con rắn khi di chuyển lên xuống trái phải
	case LEN: snake[0].y--; break;
	case XUONG: snake[0].y++; break;
	case TRAI: snake[0].x--; break;
	case PHAI: snake[0].x++; break;
	}
	return duoirancu; // trả về tọa độ đuôi rắn cũ để xử lí(xem ham vẽ rắn ở dưới)
}

// ve ran
void veSnake(toado duoirancu) {
	for (int i = 0; i < soDot; i++) { // chạy vòng lặp tọa độ của rắn 
		gotoXY(snake[i].x, snake[i].y); // đi tới vị trí có tọa đồ (x,y) để vẽ đốt rắn
		cout << (char)Dot_Ran;
	}
	gotoXY(duoirancu.x, duoirancu.y);// đi tới tọa dộ đuôi rắn cũ để xóa đi khi rắn di chuyển
	cout << " ";
}

// ve tuong 
void veWall() {
	// cho vong lap chay tu tuong ben trai den tuong ben phai để vẽ tuong tren va tuong duoi
	for (int i = TUONG_TRAI; i <= TUONG_PHAI; i++){
		gotoXY(i, TUONG_TREN);
		cout << (char)223; // ki hieu de xay dung tuong trong bang ma ASCII
		gotoXY(i, TUONG_DUOI);
		cout << (char)220;// ki hieu de xay dung tuong trong bang ma ASCII
	}
	// cho vong lap chay tu tuong ben tren den tuong ben duoi để vẽ tuong trai va tuong phai
	for (int i = TUONG_TREN; i <= TUONG_DUOI; i++) {
		gotoXY(TUONG_TRAI, i);
		cout << (char)222;// ki hieu de xay dung tuong trong bang ma ASCII
		gotoXY(TUONG_PHAI, i);
		cout << (char)221;// ki hieu de xay dung tuong trong bang ma ASCII
	}
}

// kiem tra xem ran co dung tuong hay dung vao than cua ran hay khong
bool checkGameover() {
	// neu toa do đầu rắn trung voi cac vi tri tuong thi game over
	if (snake[0].x == TUONG_TRAI || snake[0].x == TUONG_PHAI || snake[0].y == TUONG_TREN || snake[0].y == TUONG_DUOI)
		return 1;
	// neu toa do đầu rắn trung voi cac vi tri tren than cua ran thi game over
	for (int i = 1; i < soDot; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			return 1;
			break;
		}
	}
}

// ve moi de an 
toado veMoi() {
reset: srand(time(NULL)); //ham random
	// hai cau lenh o duoi la random vi tri cua MỒI trong khoang gioi han cua tuong
	// tránh random xuat hien o ngoai tuong
	int x = TUONG_TRAI + 1 + rand() % ((TUONG_PHAI - 1) - (TUONG_TRAI + 1) + 1);
	int y = TUONG_TREN + 1 + rand() % ((TUONG_DUOI - 1) - (TUONG_TREN + 1) + 1);
	//chay vong lap xem vi tri cua MỒI vừa random co trung voi vi tri cua ran hay k
	// neu trung thi se di den cau lenh reset o tren de random lai
	for (int i = 0; i < soDot; i++)
		if (x == snake[i].x && y == snake[i].y)
			goto reset;
	gotoXY(x, y);
	cout << "*"; // ki hieu cua MỒI
	return toado{ x,y }; // tra ve toa do cua MỒI vừa mới random de tiện xử lí ben duoi
}

//kiem tra xem ran da an MỒI hay chua
//neu an roi thi mới vẽ MỒI khac
bool checkAnMoi(toado moi) {
	// neu dau ran trung voi toa do cua mồi thi tra ve true
	if (moi.x == snake[0].x && moi.y == snake[0].y)
		return 1;
	else return 0;
}

// ran se dài ra sau khi ăn mồi
void themDot() {
	snake[soDot] = snake[soDot - 1];
	soDot++;
}

int main()
{	
	taoSnake();
	int huong = PHAI; // mới vào game rắn sẽ di chuyển về phía bên phải
	char t; // biến này dùng để nhận dữ liệu nhập từ bàn phim để điều khiển rắn
	int diem = 0;// diem dat dc
	veWall();// ve tường
	toado moi = veMoi(); // ve mỗi
	while (1) {
		noCursorType(); // xóa con trỏ nhấp nháy khi chạy chương trình
		if (_kbhit()) { // nếu có tín hiệu nhập từ bàn phím
			t = _getch(); // thì gán biến t = tín hiệu đó 
			if (t == 72) huong = LEN; //72 là mã ASCII của dấu mũi tên đi lên
			else if (t == 80) huong = XUONG;//80 là mã ASCII của dấu mũi tên đi xuống
			else if (t == 75) huong = TRAI;//75 là mã ASCII của dấu mũi tên đi trái
			else if (t == 77) huong = PHAI;//77 là mã ASCII của dấu mũi tên đi phải
		}
		toado duoirancu = moveSnake(huong);// lấy vị trí đuôi rắn cũ khi rắn di chuyển đi
		veSnake(duoirancu); // vẽ rắn ở trạng thái kế tiếp + xóa đuôi rắn cũ 
		if (checkAnMoi(moi) == 1) { // kiem tra xem co ăn mồi chưa
			moi = veMoi(); // nếu có thì vẽ mồi mới
			themDot();// và làm rắn dài ra 1 đốt
			diem += 5; // +5 điểm 1 lượt ăn mồi
		}
		gotoXY(55, 23); // chọn vị trí để vẽ ô điểm, thích chọn chỗ nào cũng dc vừa mắt là được
		cout << "DIEM: " << diem; // xuất ra điểm 
		//câu lệnh sleep(200) là delay lại 0.2s để vòng lặp tiếp tục 
		//nếu không có thì vòng lặp chạy rất nhanh
		//đồng nghĩa với việc con rắn cũng nhanh, số trong () càng thấp thì tốc độ con rắn càng nhanh
		Sleep(200);
		if (checkGameover() == 1) {// kiểm tra coi thua chưa
			system("cls"); // thua thì xóa hết màn hình
			cout << "GAME OVER";// rồi in ra Game over
			break;// và kết thúc vòng lặp
		}
	}
	return 0;
}
// XONG NHA HEHE

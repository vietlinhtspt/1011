﻿#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

// Hàm nạp texture từ file ảnh, để vẽ lên renderer tương ứng
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

// Hàm đưa texture ra renderer (để hiển thị ra màn hình) tại toạ độ (x,y) và giữ nguyên kích cỡ ban đầu của ảnh
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

// Hàm (cùng trên nhưng khác tham số với hàm ngay trên)
// đưa texture ra renderer (để hiển thị ra màn hình) tại toạ độ (x,y) và
// với kích cỡ rộng (w) và cao (h) cho trước.
// Ảnh sẽ được co dãn (phóng to thu nhỏ) cho khớp kích cỡ này.
// Đây là hàm không có trong tutorial ban đầu, được sửa từ hàm trong tutorial.
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
//ham chay game
void playGame(SDL_Renderer* renderer);
//Ham ve nen game
void displayBackground(SDL_Renderer* renderer);
//Ham ve hinh trai
void displayLeft(SDL_Renderer* renderer, int left, int dentaX, int dentaY);
//Ham ve hinh giua
void displayMid(SDL_Renderer* renderer, int left, int dentaX, int dentaY);
//Ham ve hinh phai
void displayRight(SDL_Renderer* renderer, int left, int dentaX, int dentaY);
//Ham ve ban co tro choi
void displayMatrixColor(SDL_Renderer* renderer, int color[10][10]);
//Ham kiem tra trang thai cac o trong ma tran khi nguoi dung xep
bool checkObject(int seri, int color[10][10], int xObject, int yObject);
//Ham ve hinh vuong 4 o
void hinhVuong4(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh 4 o doc
void doc4(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh 4 o ngang
void ngang4(SDL_Renderer* renderer, int x, int y);

//**************************************************************
const int SCREEN_WIDTH = 360;
const int SCREEN_HEIGHT = 640;
const char WINDOW_TITLE[] = "Hello";

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	vector<SDL_Texture *> picture;
	// Load anh
	picture.push_back(loadTexture("picture/menu.bmp", renderer));
	//Kiem tra xem co load duoc anh hay khong	
	int imageNum = picture.size();
	for (int i = 0; i < imageNum; ++i) {
		if (picture[i] == nullptr) {
			for (int j = 0; j < imageNum; ++j) SDL_DestroyTexture(picture[j]);
			quitSDL(window, renderer);
			getchar();
			return 1;
		}
	}
	//Kich thuoc anh
	int iSizeX = 360;
	int iSizeY = 640;
	//Vi tri
	int x = 0;
	int y = 0;
	//Su kien chinh
	SDL_Event mainEven;
	//Bien kiem tra chuong trinh
	bool isRunning = true;
	//Vong lap chay chuong trinh
	while (isRunning)
	{
		SDL_RenderClear(renderer);
		//Ve man hinh chinh
		renderTexture(picture[0], renderer, x, y, iSizeX, iSizeY);
		//Dua hinh da ve ve man hinh chinh
		SDL_RenderPresent(renderer);
		while (SDL_WaitEvent(&mainEven)) {
			// Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
			switch (mainEven.type) {
				//Truong hop thoat
				case SDL_QUIT: {
					isRunning = false;
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					if (mainEven.button.button == SDL_BUTTON_LEFT)
					{
						if ((mainEven.motion.x >= 60) && (mainEven.motion.x <= 300) && (mainEven.motion.y >= 220) && (mainEven.motion.y <= 325)) {
							playGame(renderer);
						}
					}
					break;
				}
				case SDL_MOUSEMOTION: {
					cout << mainEven.motion.x << " , " << mainEven.motion.y << "\n";
					break;
				}
				//Truong hop khac
				default: {
					cout << "default";
					break;
				}
					
			}
		}
	}
	//Ham giai phong bo nho luu cac anh
	for (int i = 0; i < imageNum; i++) {
		SDL_DestroyTexture(picture[i]);
	}
	//Ham giai phong bo nho
	quitSDL(window, renderer);
	return 0;
}
//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL
void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
	os << msg << " Error: " << SDL_GetError() << std::endl;
	if (fatal) {
		SDL_Quit();
		exit(1);
	}
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logSDLError(std::cout, "SDL_Init", true);

	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	//window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
	//   SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

	//Khi thông thường chạy với môi trường bình thường ở nhà
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
// Ham doi 1 phim de thoat
void waitUntilKeyPressed()
{
	// Su kien e
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}

/**
* Nạp một ảnh bitmap (BMP) vào một texture trên thiết bị hiện thị (rendering device)
* @param file: đường dẫn và tên file ảnh BMP
* @param ren: renderer để nạp texture lên
* @return trả về texture đã nạp, hoặc nullptr nếu có lỗi.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr) {
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), trong khi
* giữ nguyên chiều rộng và cao của ảnh
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	//Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), với
* chiều rộng và cao mới
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
* @param w: chiều rộng (mới)
* @param h: độ cao (mới)
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	//Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	//(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void playGame(SDL_Renderer* renderer)
{
	//Matrix luu trang thai cac o 
	int color[10][10];
	//Duu trang thai cac o ve trong
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			color[i][j] = 0;
		}
	}
	//Hien thi nen game
	displayBackground(renderer);
	displayMatrixColor(renderer, color);
	//Su Kien
	SDL_Event playEvent;
	//Chay game
	bool isRunning = true;
	while (isRunning) {
		int numberObject = 3;
		//Random cac hinh
		srand(time(NULL));
		int left = rand() % 3 + 1;
		int mid = rand() % 3 + 1;
		int right = rand() % 3 + 1;
		//Hien thi hinh trai
		displayLeft(renderer, left, 0, 0);
		//Hien thi hinh giua
		displayMid(renderer, mid, 0, 0);
		//Hien thi hinh phai
		displayRight(renderer, right, 0, 0);
		//Nguoi choi chua di chuyen vat the
		int isObject = 0;
		//Toa do cu cua chuot
		int x;
		int y;
		while (SDL_WaitEvent(&playEvent)) {
			// Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
			switch (playEvent.type) {
				//Truong hop thoat
				case SDL_QUIT: {
					isRunning = false;
					break;
				}
				case SDL_MOUSEMOTION: {
					if (isObject == 1) {
						/*displayBackground(renderer);
						displayMatrixColor(renderer, color);
						//Hien thi hinh trai*/
						
						displayLeft(renderer, left, playEvent.motion.x - x, playEvent.motion.y - y);
						//Hien thi hinh giua
						displayMid(renderer, mid, 0, 0);
						//Hien thi hinh phai
						displayRight(renderer, right, 0, 0);
					}
					else if (isObject == 2) {
						displayBackground(renderer);
						displayMatrixColor(renderer, color);
						//Hien thi hinh trai
						displayLeft(renderer, left, 0, 0);
						//Hien thi hinh giua
						displayMid(renderer, mid, playEvent.motion.x - x, playEvent.motion.y - y);
						//Hien thi hinh phai
						displayRight(renderer, right, 0, 0);

					}
					else if (isObject == 3) {
						displayBackground(renderer);
						displayMatrixColor(renderer, color);
						//Hien thi hinh trai
						displayLeft(renderer, left, 0, 0);
						//Hien thi hinh giua
						displayMid(renderer, mid, 0, 0);
						//Hien thi hinh phai
						displayRight(renderer, right, playEvent.motion.x - x, playEvent.motion.y - y);
					}
					//cout << playEvent.motion.x << " , " << playEvent.motion.y << "\n";
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					if ((playEvent.button.button == SDL_BUTTON_LEFT) && (isObject == 0))
					{
						if ((playEvent.motion.x >= 35) && (playEvent.motion.x <= 95) && (playEvent.motion.y >= 530) && (playEvent.motion.y <= 590)) {
							//1 == object left
							isObject = 1;
							//Toa do cu cua chuot
							x = playEvent.motion.x;
							y = playEvent.motion.y;
						}
						else if ((playEvent.motion.x >= 145) && (playEvent.motion.x <= 215) && (playEvent.motion.y >= 530) && (playEvent.motion.y <= 590)) {
							//2 == object mid
							isObject = 2;
							//Toa do cu cua chuot
							x = playEvent.motion.x;
							y = playEvent.motion.y;
						}
						else if ((playEvent.motion.x >= 250) && (playEvent.motion.x <= 325) && (playEvent.motion.y >= 530) && (playEvent.motion.y <= 590)) {
							//3 == object right
							isObject = 3;
							//Toa do cu cua chuot
							x = playEvent.motion.x;
							y = playEvent.motion.y;
						}
					}
					else if ((playEvent.button.button == SDL_BUTTON_LEFT) && (isObject != 0)) {
						int xObject; 
						int yObject;
						switch (isObject) {
						case 1: {
							xObject = 30 + playEvent.motion.x - x;
							yObject = 500 + playEvent.motion.y - y;
							checkObject(left, color, xObject, yObject);
							break;
						}
						case 2: {
							xObject = 145 + playEvent.motion.x - x;
							yObject = 500 + playEvent.motion.y - y;
							checkObject(mid, color, xObject, yObject);
							break;
						}
						case 3: {
							xObject = 250 + playEvent.motion.x - x;
							yObject = 500 + playEvent.motion.y - y;
							checkObject(right, color, xObject, yObject);
							break;
						}
						
						}
					}
					break;
				}
			}
		}
	}
}
void displayBackground(SDL_Renderer* renderer) {
	//Load anh khi vao game
	SDL_Texture* picture;
	picture = loadTexture("picture/play.bmp", renderer);
	//Kich thuoc anh
	int iSizeX = 360;
	int iSizeY = 640;
	//Vi tri
	int x = 0;
	int y = 0;
	//Ve anh
	renderTexture(picture, renderer, x, y, iSizeX, iSizeY);
	SDL_RenderPresent(renderer);
}
void displayMatrixColor(SDL_Renderer* renderer, int color[10][10])  {
	//Kich thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Vi tri
	int x = 30;
	int y = 160;
	//Vong lap cac o vuong thanh hinh
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			//Load Picture
			SDL_Texture* picture;
			//Select the color accordingly
			switch (color[i][j]) {
				//Original cell
			case 0: {
				picture = loadTexture("picture/00.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Blue
			case 1: {
				picture = loadTexture("picture/01_Blue.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Emerald Green
			case 2: {
				picture = loadTexture("picture/02_EmeraldGreen.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Green
			case 3: {
				picture = loadTexture("picture/03_Green.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Orange
			case 4: {
				picture = loadTexture("picture/04_Orange.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Pink
			case 5: {
				picture = loadTexture("picture/05_Pink.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Purple
			case 6: {
				picture = loadTexture("picture/06_Purple.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Red
			case 7: {
				picture = loadTexture("picture/07_Red.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
					//Yellow
			case 8: {
				picture = loadTexture("picture/08_Yellow.bmp", renderer);
				//Display 
				renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				SDL_RenderPresent(renderer);
				break;
			}
			}
		}
	}
}
void displayLeft(SDL_Renderer* renderer, int left, int dentaX, int dentaY) {
	int x = 20;
	int y = 500;
	switch (left) {
	case 1:
		hinhVuong4(renderer, x + dentaX, y + dentaY);
		break;
	case 2:
		ngang4(renderer, x + dentaX, y + dentaY);
		break;
	case 3:
		doc4(renderer, x + dentaX, y + dentaY);
		break;
	}
}
void displayMid(SDL_Renderer* renderer, int left, int dentaX, int dentaY) {
	int x = 145;
	int y = 500;
	switch (left) {
	case 1:
		hinhVuong4(renderer, x + dentaX, y + dentaY);
		break;
	case 2:
		ngang4(renderer, x + dentaX, y + dentaY);
		break;
	case 3:
		doc4(renderer, x + dentaX, y + dentaY);
		break;
	}
}
void displayRight(SDL_Renderer* renderer, int left, int dentaX, int dentaY) {
	int x = 250;
	int y = 500;
	switch (left) {
	case 1:
		hinhVuong4(renderer, x + dentaX, y + dentaY);
		break;
	case 2:
		ngang4(renderer, x + dentaX, y + dentaY);
		break;
	case 3:
		doc4(renderer, x + dentaX, y + dentaY);
		break;
	}
}
bool checkObject(int seri, int color[10][10], int xObject, int yObject) {
	bool check = true;
	xObject = (xObject + 30) / 30;
	yObject = (yObject + 30) / 30;
	switch (seri) {
	case 1: {
		if (color[xObject][yObject] != 0) {
			check = false;
		}
		if (check == true) {
			color[xObject][yObject] = 1;
		}
		break;
	}
	case 2: {
		for (int i = 0; i <= 1; i ++) {
			for (int j = 0; j <= 1; j++) {
				if (color[i + xObject][j + yObject] != 0)
				{
					check = false;
				}
			}
		}
		if (check == true) {
			for (int i = 0; i <= 1; i++) {
				for (int j = 0; j <= 1; j++) {
					color[i + xObject][j + yObject] = 2;
				}
			}
		}
		break;
	}
	case 3: {
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				if (color[i + xObject][j + yObject] != 0)
				{
					check = false;
				}
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				for (int j = 0; j <= 2; j++) {
					color[i + xObject][j + yObject] = 3;
				}
			}
		}
		break;
	}
	case 4: {
		for (int i = 0; i <= 1; i++) {
			if (color[i + xObject][yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 1; i++) {
				color[i + xObject][yObject] == 4;
			}
		}
		break;
	}
	case 5: {
		for (int i = 0; i <= 2; i++) {
			if (color[i + xObject][yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[i + xObject][yObject] == 5;
			}
		}
		break;
	}
	case 6: {
		for (int i = 0; i <= 3; i++) {
			if (color[i + xObject][yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 3; i++) {
				color[i + xObject][yObject] == 6;
			}
		}
		break;
	}
	case 7: {
		for (int i = 0; i <= 1; i++) {
			if (color[xObject][i + yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 1; i++) {
				color[xObject][i + yObject] = 7;
			}
		}
		break;
	}
	case 8: {
		for (int i = 0; i <= 2; i++) {
			if (color[xObject][i + yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[xObject][i + yObject] = 8;
			}
		}
		break;
	}
	case 9: {
		for (int i = 0; i <= 3; i++) {
			if (color[xObject][i + yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 3; i++) {
				color[xObject][i + yObject] = 1;
			}
		}
		break;
	}
	case 10: {
		if (color[xObject + 1][yObject + 1] != 0) {
			check = false;
		}
		for (int i = 0; i <= 1; i ++) {
			if (color[xObject][yObject + i] != 0) {
				check = false;
			}
		}
		if (check == true) {
			color[xObject + 1][yObject + 1] = 2;
			for (int i = 0; i <= 1; i ++) {
				color[xObject][yObject + i] = 2;
			}
		}
		break;
	}
	case 11: {
		if (color[xObject + 1][yObject] != 0) {
			check = false;
		}
		for (int i = 0; i <= 1; i ++) {
			if (color[xObject][yObject + i] != 0) {
				check = false;
			}
		}
		if (check == true) {
			color[xObject + 1][yObject] = 3;
			for (int i = 0; i <= 1; i ++) {
				color[xObject][yObject + i] = 3;
			}
		}
		break;
	}
	case 12: {
		if (color[xObject][yObject] != 0) {
			check = false;
		}
		for (int i = 0; i <= 1; i++) {
			if (color[xObject + 1][yObject + i] != 0) {
				check = false;
			}
		}
		if (check == true) {
			color[xObject][yObject] = 4;
			for (int i = 0; i <= 1; i ++) {
				color[xObject + 1][yObject + i] = 4;
			}
		}
		break;
	}
	case 13: {
		if (color[xObject][yObject + 1] != 0) {
			check = false;
		}
		for (int i = 0; i <= 1; i++) {
			if (color[xObject + 1][yObject + i] != 0) {
				check = false;
			}
		}
		if (check == true) {
			color[xObject][yObject + 1] = 5;
			for (int i = 0; i <= 1; i++) {
				color[xObject + 1][yObject + i] = 5;
			}
		}
		break;
	}
	case 14: {
		for (int i = 0; i <= 2; i++) {
			if (color[xObject][yObject + i] != 0) {
				check = false;
			}
		}
		for (int i = 1; i <= 2; i++) {
			if (color[xObject + i][yObject + 2] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[xObject][yObject + i] = 6;
			}
			for (int i = 1; i <= 2; i++) {
				color[xObject + i][yObject + 2] = 6;
			}
		}
		break;
	}
	case 15: {
		for (int i = 0; i <= 2; i++) {
			if (color[xObject][yObject + i] != 0) {
				check = false;
			}
		}
		for (int i = 1; i <= 2; i++) {
			if (color[xObject + i][yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[xObject][yObject + i] = 7;
			}
			for (int i = 1; i <= 2; i++) {
				color[xObject + i][yObject] = 7;
			}
		}
		break;
	}
	case 16: {
		for (int i = 0; i <= 2; i++) {
			if (color[xObject + 2][yObject + i] != 0) {
				check = false;
			}
		}
		for (int i = 0; i <= 1; i++) {
			if (color[xObject + i][yObject + 2] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[xObject + 2][yObject + i] = 8;
			}
			for (int i = 0; i <= 1; i++) {
				color[xObject + i][yObject + 2] = 8;
			}
		}
		break;
	}
	case 17: {
		for (int i = 0; i <= 2; i++) {
			if (color[xObject + 2][yObject + i] != 0) {
				check = false;
			}
		}
		for (int i = 0; i <= 1; i++) {
			if (color[xObject + i][yObject] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[xObject + 2][yObject + i] = 1;
			}
			for (int i = 0; i <= 1; i++) {
				color[xObject + i][yObject] = 1;
			}
		}
		break;
	}
	}
	return check;
}
void hinhVuong4(SDL_Renderer* renderer, int x, int y)
{
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/03_Green.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 1; i ++) {
		for (int j = 0; j <= 1; j ++) {
			renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
			SDL_RenderPresent(renderer);
		}
	}
}
void ngang4(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/07_Red.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 3; i++) {
		renderTexture(picture, renderer, x + i * 30, y, iSizeX, iSizeY);
		SDL_RenderPresent(renderer);
	}
}
void doc4(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/04_Orange.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 3; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);
		SDL_RenderPresent(renderer);
	}
}



#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#pragma comment (lib, "winmm.lib")
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
//Ham ve menu
void displayMenuSetup(SDL_Renderer* renderer);
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
//Ham tinh diem
void countScore(int color[10][10]);
//Ham hien thi diem
void displayScore(SDL_Renderer* renderer);
//Ham hien thi diem so cao nhat
void displayHightScore(SDL_Renderer* renderer);
//Ham ve hinh vuong 1 o
void square1(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh vuong 4 o
void square4(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh vuong 9 o
void square9(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh ngang 2 o
void horizontalRectangle2(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh ngang 3 o
void horizontalRectangle3(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh ngang 4 o 
void horizontalRectangle4(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh doc 2 o
void verticalRectangle2(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh doc 3 o
void verticalRectangle3(SDL_Renderer* renderer, int x, int y);
//Ham ve thanh do 4 o
void verticalRectangle4(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh L be
void triangularSmall0(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh L be
void triangularSmall90(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh L be
void triangularSmall180(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh chu L be
void triangularSmall270(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh chu L lon
void triangularBig0(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh chu L lon
void triangularBig90(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh chu L lon
void triangularBig180(SDL_Renderer* renderer, int x, int y);
//Ham ve hinh chu L lon
void triangularBig270(SDL_Renderer* renderer, int x, int y);
//**************************************************************
const int SCREEN_WIDTH = 360;
const int SCREEN_HEIGHT = 640;
const char WINDOW_TITLE[] = "Hello";
int g_score = 0;
int g_hightScore;
const int g_xSize = 25;
const int g_ySize = 25;
int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	vector<SDL_Texture *> picture;
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
		picture.push_back(loadTexture("picture/menu.bmp", renderer));
		SDL_RenderClear(renderer);
		//Ve man hinh chinh
		renderTexture(picture[0], renderer, x, y, iSizeX, iSizeY);
		//Dua hinh da ve ve man hinh chinh
		SDL_RenderPresent(renderer);
		bool running = true;
		while (SDL_WaitEvent(&mainEven)) {
			if (running == false) break;
			if (isRunning == false) break;
			// Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
			switch (mainEven.type) {
				//Truong hop thoat
			case SDL_QUIT: {
				isRunning = false;
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{ 
				bool isPlay = PlaySound("sound/soundMenu.wav", NULL, SND_ASYNC);
				if (mainEven.button.button == SDL_BUTTON_LEFT)
				{
					if ((mainEven.motion.x >= 60) && (mainEven.motion.x <= 300) && (mainEven.motion.y >= 220) && (mainEven.motion.y <= 325)) {
						playGame(renderer);
						running = false;
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

	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
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
	//Su Kien
	SDL_Event playEvent;
	//Chay game
	bool isRunning = true;
	while (isRunning) {
		displayBackground(renderer);
		displayMatrixColor(renderer, color);
		displayScore(renderer);
		displayHightScore(renderer);
		int numberObject = 3;
		//Random cac hinh
		srand(time(NULL));
		int left = rand() % 17 + 1;
		int mid = rand() % 17 + 1;
		int right = rand() % 17 + 1;
		if (checkOver(left, mid, right, color) == false) {
			isRunning = false;
		}
		//Hien thi hinh trai
		displayLeft(renderer, left, 0, 0);
		//Hien thi hinh giua
		displayMid(renderer, mid, 0, 0);
		//Hien thi hinh phai
		displayRight(renderer, right, 0, 0);
		SDL_RenderPresent(renderer);
		//Nguoi choi chua di chuyen vat the
		int isObject = 0;
		//Toa do cu cua chuot
		int x;
		int y;
		while (SDL_WaitEvent(&playEvent)) {
			//Hien thi diem so cao nhat cua nguoi choi
			// Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
			if ((left == -1) && (mid == -1) && (right == -1)) {
				break;
			}
			if (isRunning == false) {
				break;
			}
			switch (playEvent.type) {
				//Truong hop thoat
			case SDL_QUIT: {     
				isRunning = false;
				break;
			}
			case SDL_MOUSEMOTION: {
				if (isObject == 1) {
					displayBackground(renderer);
					displayMatrixColor(renderer, color);
					//Hien thi hinh trai*/
					displayLeft(renderer, left, playEvent.motion.x - x, playEvent.motion.y - y);
					//Hien thi hinh giua
					displayMid(renderer, mid, 0, 0);
					//Hien thi hinh phai
					displayRight(renderer, right, 0, 0);
					displayScore(renderer);
					displayHightScore(renderer);
					SDL_RenderPresent(renderer);
					
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
					displayScore(renderer);
					displayHightScore(renderer);
					SDL_RenderPresent(renderer);
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
					displayScore(renderer);
					displayHightScore(renderer);
					SDL_RenderPresent(renderer);
				}
				cout << playEvent.motion.x << " , " << playEvent.motion.y << "\n";
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				if ((playEvent.button.button == SDL_BUTTON_LEFT) && (isObject == 0))
				{
					if ((playEvent.motion.x >= 15) && (playEvent.motion.x <= 110) && (playEvent.motion.y >= 450) && (left > 0)) {
						//1 == object left
						isObject = 1;
						//Toa do cu cua chuot
						x = playEvent.motion.x;
						y = playEvent.motion.y;
					}
					else if ((playEvent.motion.x >= 120) && (playEvent.motion.x <= 239) && (playEvent.motion.y >= 450) && (mid > 0)) {
						//2 == object mid
						isObject = 2;
						//Toa do cu cua chuot
						x = playEvent.motion.x;
						y = playEvent.motion.y;
					}
					else if ((playEvent.motion.x >= 240) && (playEvent.motion.x <= 350) && (playEvent.motion.y >= 450) && (right > 0)) {
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
						if (checkObject(left, color, xObject, yObject) == true) {
							left = -1;
							isObject = 0;
							countScore(color);
						}
						else {
							isObject = 0;
						}
						break;
					}
					case 2: {
						xObject = 120 + playEvent.motion.x - x;
						yObject = 500 + playEvent.motion.y - y;
						if (checkObject(mid, color, xObject, yObject) == true) {
							mid = -1;
							isObject = 0;
							countScore(color);
						}
						else {
							isObject = 0;
						}
						break;
					}
					case 3: {
						xObject = 240 + playEvent.motion.x - x;
						yObject = 500 + playEvent.motion.y - y;
						if (checkObject(right, color, xObject, yObject) == true) {
							right = -1;
							isObject = 0;
							countScore(color);
						}
						else {
							isObject = 0;
						}
						break;
					}
							continue;
					}
				bool isPlay = PlaySound("sound/soundPlay.wav", NULL, SND_ASYNC);
				}
				if (playEvent.button.button == SDL_BUTTON_LEFT) {
					if ((playEvent.motion.x >= 335) && (playEvent.motion.x <= 355) && (playEvent.motion.y >= 80) && (playEvent.motion.y <= 105)) {
						bool isPlay = PlaySound("sound/soundMenu.wav", NULL, SND_ASYNC);
						displayMenuSetup(renderer);
						bool runningMenuPlay = true;
						while (SDL_WaitEvent(&playEvent)) {
							if (runningMenuPlay == false) {
								break;
							}
							switch (playEvent.type) {
								//Truong hop thoat
							case SDL_QUIT: {
								runningMenuPlay = false;
								isRunning = false;
								break;
							}
							case SDL_MOUSEBUTTONUP: {
								if ((playEvent.motion.x >= 60) && (playEvent.motion.x <= 175) && (playEvent.motion.y >= 235) && (playEvent.motion.y <= 350)) {
									bool isPlay = PlaySound("sound/soundMenu.wav", NULL, SND_ASYNC);
									isRunning = false;
									runningMenuPlay = false;
								}
								else if ((playEvent.motion.x >= 185) && (playEvent.motion.x <= 300) && (playEvent.motion.y >= 240) && (playEvent.motion.y <= 355)) {
									bool isPlay = PlaySound("sound/soundMenu.wav", NULL, SND_ASYNC);
									mid = -1;
									right = -1;
									left = -1;
									for (int i = 0; i < 10; i++) {
										for (int j = 0; j < 10; j++) {
											color[i][j] = 0;
										}
									}
									runningMenuPlay = false;
								}
								else {
									bool isPlay = PlaySound("sound/soundMenu.wav", NULL, SND_ASYNC);
									runningMenuPlay = false;
								}
								break;
							}
							}
						}
					}
				}
				}
				break;
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
	SDL_DestroyTexture(picture);

}
void displayMenuSetup(SDL_Renderer* renderer) {
	//Load anh khi vao game
	SDL_Texture* picture;
	picture = loadTexture("picture/menuSetup.bmp", renderer);
	//Kich thuoc anh
	int iSizeX = 360;
	int iSizeY = 640;
	//Vi tri
	int x = 0;
	int y = 0;
	//Ve anh
	renderTexture(picture, renderer, x, y, iSizeX, iSizeY);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(picture);
}
void displayMatrixColor(SDL_Renderer* renderer, int color[10][10]) {
	//Kich thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Vi tri
	int x = 30;
	int y = 160;
	//load picture
	SDL_Texture* picture[9];
	picture[0] = loadTexture("picture/00.bmp", renderer);
	picture[1] = loadTexture("picture/01_Blue.bmp", renderer);
	picture[2] = loadTexture("picture/02_EmeraldGreen.bmp", renderer);
	picture[3] = loadTexture("picture/03_Green.bmp", renderer);
	picture[4] = loadTexture("picture/04_Orange.bmp", renderer);
	picture[5] = loadTexture("picture/05_Pink.bmp", renderer);
	picture[6] = loadTexture("picture/06_Purple.bmp", renderer);
	picture[7] = loadTexture("picture/07_Red.bmp", renderer);
	picture[8] = loadTexture("picture/08_Yellow.bmp", renderer);
	//Vong lap cac o vuong thanh hinh
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			//Load Picture
			//Select the color accordingly
			switch (color[j][i]) {
				//Original cell
			case 0: {
				//Display 
				renderTexture(picture[0], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Blue
			case 1: {
				//Display 
				renderTexture(picture[1], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Emerald Green
			case 2: {
				//Display 
				renderTexture(picture[2], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Green
			case 3: {
				//Display 
				renderTexture(picture[3], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Orange
			case 4: {
				//Display 
				renderTexture(picture[4], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Pink
			case 5: {
				//Display 
				renderTexture(picture[5], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Purple
			case 6: {
				//Display 
				renderTexture(picture[6], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Red
			case 7: {
				//Display 
				renderTexture(picture[7], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
					//Yellow
			case 8: {
				//Display 
				renderTexture(picture[8], renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
				break;
			}
			}
		}
	}
	SDL_RenderPresent(renderer);
	for (int i = 0; i < 9; i ++)
	SDL_DestroyTexture(picture[i]);
}
void displayLeft(SDL_Renderer* renderer, int left, int dentaX, int dentaY) {
	int x = 20;
	int y = 500;
	switch (left) {
	case 1:
		square1(renderer, x + dentaX, y + dentaY);
		break;
	case 2:
		square4(renderer, x + dentaX, y + dentaY);
		break;
	case 3:
		square9(renderer, x + dentaX, y + dentaY);
		break;
	case 4:
		horizontalRectangle2(renderer, x + dentaX, y + dentaY);
		break;
	case 5:
		horizontalRectangle3(renderer, x + dentaX, y + dentaY);
		break;
	case 6:
		horizontalRectangle4(renderer, x + dentaX, y + dentaY);
		break;
	case 7:
		verticalRectangle2(renderer, x + dentaX, y + dentaY);
		break;
	case 8:
		verticalRectangle3(renderer, x + dentaX, y + dentaY);
		break;
	case 9:
		verticalRectangle4(renderer, x + dentaX, y + dentaY);
		break;
	case 10:
		triangularSmall0(renderer, x + dentaX, y + dentaY);
		break;
	case 11:
		triangularSmall90(renderer, x + dentaX, y + dentaY);
		break;
	case 12:
		triangularSmall180(renderer, x + dentaX, y + dentaY);
		break;
	case 13:
		triangularSmall270(renderer, x + dentaX, y + dentaY);
		break;
	case 14:
		triangularBig0(renderer, x + dentaX, y + dentaY);
		break;
	case 15:
		triangularBig90(renderer, x + dentaX, y + dentaY);
		break;
	case 16:
		triangularBig180(renderer, x + dentaX, y + dentaY);
		break;
	case 17:
		triangularBig270(renderer, x + dentaX, y + dentaY);
		break;
	}
}
void displayMid(SDL_Renderer* renderer, int left, int dentaX, int dentaY) {
	int x = 120;
	int y = 500;
	switch (left) {
	case 1:
		square1(renderer, x + dentaX, y + dentaY);
		break;
	case 2:
		square4(renderer, x + dentaX, y + dentaY);
		break;
	case 3:
		square9(renderer, x + dentaX, y + dentaY);
		break;
	case 4:
		horizontalRectangle2(renderer, x + dentaX, y + dentaY);
		break;
	case 5:
		horizontalRectangle3(renderer, x + dentaX, y + dentaY);
		break;
	case 6:
		horizontalRectangle4(renderer, x + dentaX, y + dentaY);
		break;
	case 7:
		verticalRectangle2(renderer, x + dentaX, y + dentaY);
		break;
	case 8:
		verticalRectangle3(renderer, x + dentaX, y + dentaY);
		break;
	case 9:
		verticalRectangle4(renderer, x + dentaX, y + dentaY);
		break;
	case 10:
		triangularSmall0(renderer, x + dentaX, y + dentaY);
		break;
	case 11:
		triangularSmall90(renderer, x + dentaX, y + dentaY);
		break;
	case 12:
		triangularSmall180(renderer, x + dentaX, y + dentaY);
		break;
	case 13:
		triangularSmall270(renderer, x + dentaX, y + dentaY);
		break;
	case 14:
		triangularBig0(renderer, x + dentaX, y + dentaY);
		break;
	case 15:
		triangularBig90(renderer, x + dentaX, y + dentaY);
		break;
	case 16:
		triangularBig180(renderer, x + dentaX, y + dentaY);
		break;
	case 17:
		triangularBig270(renderer, x + dentaX, y + dentaY);
		break;
	}
}
void displayRight(SDL_Renderer* renderer, int left, int dentaX, int dentaY) {
	int x = 240;
	int y = 500;
	switch (left) {
	case 1:
		square1(renderer, x + dentaX, y + dentaY);
		break;
	case 2:
		square4(renderer, x + dentaX, y + dentaY);
		break;
	case 3:
		square9(renderer, x + dentaX, y + dentaY);
		break;
	case 4:
		horizontalRectangle2(renderer, x + dentaX, y + dentaY);
		break;
	case 5:
		horizontalRectangle3(renderer, x + dentaX, y + dentaY);
		break;
	case 6:
		horizontalRectangle4(renderer, x + dentaX, y + dentaY);
		break;
	case 7:
		verticalRectangle2(renderer, x + dentaX, y + dentaY);
		break;
	case 8:
		verticalRectangle3(renderer, x + dentaX, y + dentaY);
		break;
	case 9:
		verticalRectangle4(renderer, x + dentaX, y + dentaY);
		break;
	case 10:
		triangularSmall0(renderer, x + dentaX, y + dentaY);
		break;
	case 11:
		triangularSmall90(renderer, x + dentaX, y + dentaY);
		break;
	case 12:
		triangularSmall180(renderer, x + dentaX, y + dentaY);
		break;
	case 13:
		triangularSmall270(renderer, x + dentaX, y + dentaY);
		break;
	case 14:
		triangularBig0(renderer, x + dentaX, y + dentaY);
		break;
	case 15:
		triangularBig90(renderer, x + dentaX, y + dentaY);
		break;
	case 16:
		triangularBig180(renderer, x + dentaX, y + dentaY);
		break;
	case 17:
		triangularBig270(renderer, x + dentaX, y + dentaY);
		break;
	}
}
bool checkObject(int seri, int color[10][10], int xObject, int yObject) {
	bool check = true;
	xObject = (xObject - 30)/ 30;
	yObject = (yObject - 160) / 30;
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
		for (int i = 0; i <= 1; i++) {
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
				color[i + xObject][yObject] = 4;
			}
		}
		break;
	}
	case 5: {
		for (int i = 0; i <= 2; i++) {
			if (color[i + xObject][yObject + 1] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[i + xObject][yObject + 1] = 5;
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
				color[i + xObject][yObject] = 6;
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
			if (color[xObject][i + yObject + 1] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 3; i++) {
				color[xObject][i + yObject + 1] = 1;
			}
		}
		break;
	}
	case 10: {
		if (color[xObject + 1][yObject + 1] != 0) {
			check = false;
		}
		for (int i = 0; i <= 1; i++) {
			if (color[xObject][yObject + i] != 0) {
				check = false;
			}
		}
		if (check == true) {
			color[xObject + 1][yObject + 1] = 2;
			for (int i = 0; i <= 1; i++) {
				color[xObject][yObject + i] = 2;
			}
		}
		break;
	}
	case 11: {
		if (color[xObject + 1][yObject] != 0) {
			check = false;
		}
		for (int i = 0; i <= 1; i++) {
			if (color[xObject][yObject + i] != 0) {
				check = false;
			}
		}
		if (check == true) {
			color[xObject + 1][yObject] = 3;
			for (int i = 0; i <= 1; i++) {
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
			for (int i = 0; i <= 1; i++) {
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
			if (color[xObject][yObject + i + 1] != 0) {
				check = false;
			}
		}
		for (int i = 1; i <= 2; i++) {
			if (color[xObject + i][yObject + 1] != 0) {
				check = false;
			}
		}
		if (check == true) {
			for (int i = 0; i <= 2; i++) {
				color[xObject][yObject + i + 1] = 7;
			}
			for (int i = 1; i <= 2; i++) {
				color[xObject + i][yObject + 1] = 7;
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
void countScore(int color[10][10]) {
	for (int i = 0; i < 10; i++) {
		bool check = true;
		for (int j = 0; j < 10; j++) {
			if (color[i][j] == 0) {
				check = false;
				break;
			}
		}
		if (check == true) {
			for (int j = 0; j < 10; j++) {
				color[i][j] = 0;
			}
			g_score = g_score + 10;
		}
		check = true;
		for (int j = 0; j < 10; j++) {
			if (color[j][i] == 0) {
				check = false;
				break;
			}
		}
		if (check == true) {
			for (int j = 0; j < 10; j++) {
				color[j][i] = 0;
			}
			g_score = g_score + 10;
		}
	}
	cout << "Score: " << g_score << endl;
	}
void displayScore(SDL_Renderer* renderer) {
	SDL_Texture* picture[10];
	picture[0] = loadTexture("picture/0.bmp", renderer);
	picture[1] = loadTexture("picture/1.bmp", renderer);
	picture[2] = loadTexture("picture/2.bmp", renderer);
	picture[3] = loadTexture("picture/3.bmp", renderer);
	picture[4] = loadTexture("picture/4.bmp", renderer);
	picture[5] = loadTexture("picture/5.bmp", renderer);
	picture[6] = loadTexture("picture/6.bmp", renderer);
	picture[7] = loadTexture("picture/7.bmp", renderer);
	picture[8] = loadTexture("picture/8.bmp", renderer);
	picture[9] = loadTexture("picture/9.bmp", renderer);
	if (g_score == 0) {
		renderTexture(picture[0], renderer, 120, 78, 20, 35);
	}
	else {
		int count = 0;
		int temp = g_score;
		while (temp > 0) {
			int i = temp % 10;
			temp = temp / 10;
			renderTexture(picture[i], renderer, 120 - count * 20, 78, 20, 35);
			count++;
		}
	}
	
	for (int i = 0; i < 10; i++) {
		SDL_DestroyTexture(picture[i]);
	}
}
void displayHightScore(SDL_Renderer* renderer) {
	SDL_Texture* picture[10];
	picture[0] = loadTexture("picture/0.bmp", renderer);
	picture[1] = loadTexture("picture/1.bmp", renderer);
	picture[2] = loadTexture("picture/2.bmp", renderer);
	picture[3] = loadTexture("picture/3.bmp", renderer);
	picture[4] = loadTexture("picture/4.bmp", renderer);
	picture[5] = loadTexture("picture/5.bmp", renderer);
	picture[6] = loadTexture("picture/6.bmp", renderer);
	picture[7] = loadTexture("picture/7.bmp", renderer);
	picture[8] = loadTexture("picture/8.bmp", renderer);
	picture[9] = loadTexture("picture/9.bmp", renderer);
	fstream fileScore("hightScore.txt");
	if (!fileScore) {
		cout << endl << "Failed to open file ";
	}
	fileScore >> g_hightScore;
	if (g_score > g_hightScore) {
		g_hightScore = g_score;
		fileScore.close();
		fileScore.open("hightScore.txt", ios::trunc);
		fileScore << g_hightScore;
	}
	fileScore.close();
	if (g_hightScore == 0) {
		renderTexture(picture[0], renderer, 200, 78, 20, 35);
	}
	else {
		int count = 0;
		int temp = g_hightScore;
		while (temp > 0) {
			count++;
			temp = temp / 10;
		}
		temp = g_hightScore;
		while (temp > 0) {
			int i = temp % 10;
			temp = temp / 10;
			renderTexture(picture[i], renderer, 200 + count * 20, 78, 20, 35);
			count--;
		}
	}
	for (int i = 0; i < 10; i++) {
		SDL_DestroyTexture(picture[i]);
	}
}
void square1(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/01_Blue.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh ra man hinh
	renderTexture(picture, renderer, x, y, iSizeX, iSizeY);
	SDL_DestroyTexture(picture);
}
void square4(SDL_Renderer* renderer, int x, int y)
{
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/02_EmeraldGreen.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
		
		}
	}
	SDL_DestroyTexture(picture);
}
void square9(SDL_Renderer* renderer, int x, int y)
{
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/03_Green.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			renderTexture(picture, renderer, x + j * 30, y + i * 30, iSizeX, iSizeY);
			
		}
	}
	SDL_DestroyTexture(picture);
}
void horizontalRectangle2(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/04_Orange.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x + i * 30, y, iSizeX, iSizeY);
		
	}
	SDL_DestroyTexture(picture);
}
void horizontalRectangle3(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/05_Pink.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 2; i++) {
		renderTexture(picture, renderer, x + i * 30, y, iSizeX, iSizeY);
		
	}
	SDL_DestroyTexture(picture);
}
void horizontalRectangle4(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/06_Purple.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 3; i++) {
		renderTexture(picture, renderer, x + i * 30, y, iSizeX, iSizeY);
		
	}
	SDL_DestroyTexture(picture);
}
void verticalRectangle2(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/07_Red.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);
		
	}
	SDL_DestroyTexture(picture);
}
void verticalRectangle3(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/08_Yellow.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 2; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);
	
	}
	SDL_DestroyTexture(picture);
}
void verticalRectangle4(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/01_Blue.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//vong lap ve hinh
	for (int i = 0; i <= 3; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);
		
	}
	SDL_DestroyTexture(picture);
}
void triangularSmall0(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/02_EmeraldGreen.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);

	}
	renderTexture(picture, renderer, x + 30, y + 30, iSizeX, iSizeY);
	SDL_DestroyTexture(picture);
}
void triangularSmall90(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/03_Green.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);

	}
	renderTexture(picture, renderer, x + 30, y, iSizeX, iSizeY);
	SDL_DestroyTexture(picture);
}
void triangularSmall180(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/04_Orange.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x + 30, y + i * 30, iSizeX, iSizeY);
	
	}
	renderTexture(picture, renderer, x, y, iSizeX, iSizeY);
	SDL_DestroyTexture(picture);
}
void triangularSmall270(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/05_Pink.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x + 30, y + i * 30, iSizeX, iSizeY);
		SDL_RenderPresent(renderer);
	}
	renderTexture(picture, renderer, x, y + 30, iSizeX, iSizeY);
	SDL_DestroyTexture(picture);
}
void triangularBig0(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/06_Purple.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 2; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);
		
	}
	for (int i = 1; i <= 2; i++) {
		renderTexture(picture, renderer, x + i * 30, y + 60, iSizeX, iSizeY);
	}
	SDL_DestroyTexture(picture);
}
void triangularBig90(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/07_Red.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 2; i++) {
		renderTexture(picture, renderer, x, y + i * 30, iSizeX, iSizeY);
	
	}
	for (int i = 1; i <= 2; i++) {
		renderTexture(picture, renderer, x + i * 30, y, iSizeX, iSizeY);
	}
	SDL_DestroyTexture(picture);
}
void triangularBig180(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/08_Yellow.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 2; i++) {
		renderTexture(picture, renderer, x + 60, y + i * 30, iSizeX, iSizeY);
	
	}
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x + i * 30, y + 60, iSizeX, iSizeY);
	}
	SDL_DestroyTexture(picture);
}
void triangularBig270(SDL_Renderer* renderer, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/01_Blue.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 25;
	int iSizeY = 25;
	//Ve anh
	for (int i = 0; i <= 2; i++) {
		renderTexture(picture, renderer, x + 60, y + i * 30, iSizeX, iSizeY);
		
	}
	for (int i = 0; i <= 1; i++) {
		renderTexture(picture, renderer, x + i * 30, y, iSizeX, iSizeY);
	}
	SDL_DestroyTexture(picture);
}




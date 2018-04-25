﻿#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <string>
using namespace std;
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

// Hai hàm về texture, lấy nguyên về từ tutorial tại:
// http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-2-dont-put-everything-in-main

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

using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 450;
const int SCREEN_HEIGHT = 800;
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
	int iSizeX = 450;
	int iSizeY = 800;
	//Vi tri
	int x = 0; 
	int y = 0;
	//Su kien chinh
	SDL_Event mainEven;
	//Bien kiem tra chuong trinh
	bool isRunning = true;
	while (isRunning)
	{
		SDL_RenderClear(renderer);
		renderTexture(picture[0], renderer, x, y, iSizeX, iSizeY);
		SDL_RenderPresent(renderer);
		while (SDL_WaitEvent(&mainEven)) {
			// Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
			if (mainEven.type == SDL_QUIT) isRunning = false;

			// Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
			if (mainEven.type == SDL_KEYDOWN) {
				// Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
				if (mainEven.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
			}
		}

	}
	getchar();
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


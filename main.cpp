#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <string>
#include <ctime>
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
//Ham ve ban co tro choi
void displayMatrixColor(SDL_Renderer* renderer, int color[10][10]);
//Ham ve hinh vuong 4 o
void hinhVuong4(SDL_Renderer* renderer, int dentaX, int dentaY, int x, int y);
//Ham ve thanh 4 o doc
void doc4(SDL_Renderer* renderer, int dentaX, int dentaY, int x, int y);
//Ham ve thanh 4 o ngang
void ngang4(SDL_Renderer* renderer, int dentaX, int dentaY, int x, int y);

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
		/*srand(time(NULL));
		int a = rand() % 50 + 1;*/
		while (SDL_WaitEvent(&playEvent)) {
			// Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
			switch (playEvent.type) {
				//Truong hop thoat
				case SDL_QUIT: {
					isRunning = false;
					break;
				}
				case SDL_MOUSEMOTION: {
					cout << playEvent.motion.x << " , " << playEvent.motion.y << "\n";
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					if (playEvent.button.button == SDL_BUTTON_LEFT)
					{
						if ((playEvent.motion.x >= 35) && (playEvent.motion.x <= 95) && (playEvent.motion.y >= 530) && (playEvent.motion.y <= 590)) {
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
void displayMatrixColor(SDL_Renderer* renderer, int color[10][10]) {
	//Kich thuoc anh
	int iSizeX = 29;
	int iSizeY = 29;
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
void hinhVuong4(SDL_Renderer* renderer, int dentaX, int dentaY, int x, int y)
{
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/03_Green.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 29;
	int iSizeY = 29;
	//vong lap ve hinh
	for (int i = 0; i <= 1; i ++) {
		for (int j = 0; j <= 1; j ++) {
			renderTexture(picture, renderer, x + dentaX, y + dentaY, iSizeX + j * 30, iSizeY + i * 30);
			SDL_RenderPresent(renderer);
		}
	}
}
void ngang4(SDL_Renderer* renderer, int dentaX, int dentaY, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("07_picture/Red.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 29;
	int iSizeY = 29;
	//vong lap ve hinh
	for (int i = 0; i <= 3; i++) {
		renderTexture(picture, renderer, x + dentaX, y + dentaY, iSizeX + i * 30, iSizeY);
		SDL_RenderPresent(renderer);
	}
}
void doc4(SDL_Renderer* renderer, int dentaX, int dentaY, int x, int y) {
	//Load anh
	SDL_Texture* picture;
	picture = loadTexture("picture/04_Orange.bmp", renderer);
	//Kich Thuoc anh
	int iSizeX = 29;
	int iSizeY = 29;
	//vong lap ve hinh
	for (int i = 0; i <= 3; i++) {
		renderTexture(picture, renderer, x + dentaX, y + dentaY, iSizeX, iSizeY + i * 30);
		SDL_RenderPresent(renderer);
	}
}



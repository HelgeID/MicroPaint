#include <iostream> //to check the availability *ini
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "GdiPlus.lib")

#pragma warning(disable : 4996)

//constants for colours
#define COLOUR_PURPLE			RGB(163, 73, 164)
#define COLOUR_PURPLE_LITE		RGB(200, 191, 231)
#define COLOUR_BLUE				RGB(63, 72, 204)
#define COLOUR_BLUE_LITE		RGB(112, 146, 190)
#define COLOUR_CYAN				RGB(0, 162, 232)
#define COLOUR_CYAN_LITE		RGB(153, 217, 234)
#define COLOUR_GREEN			RGB(34, 177, 76)
#define COLOUR_GREEN_LITE		RGB(181, 230, 29)
#define COLOUR_YELLOW			RGB(255, 242, 0)
#define COLOUR_YELLOW_LITE		RGB(239, 228, 176)
#define COLOUR_ORANGE			RGB(255, 127, 39)
#define COLOUR_ORANGE_LITE		RGB(255, 201, 14)
#define COLOUR_RED				RGB(237, 28, 36)
#define COLOUR_RED_LITE			RGB(255, 174, 201)
#define COLOUR_BROWN			RGB(136, 0, 21)
#define COLOUR_BROWN_LITE		RGB(185, 122, 87)
#define COLOUR_GREY				RGB(127, 127, 127)
#define COLOUR_GREY_LITE		RGB(195, 195, 195)
#define COLOUR_BLACK			RGB(0, 0, 0)
#define COLOUR_WHITE			RGB(255, 255, 255)

#define COLOUR_BACKGROUND		RGB(200, 200, 200)
#define COLOUR_BTN_BLUE			RGB(60, 117, 188)
#define COLOUR_BTN_RED			RGB(242, 87, 95)

COLORREF ARR_COLOUR_BTN[20] = {
	COLOUR_PURPLE, COLOUR_PURPLE_LITE,
	COLOUR_BLUE, COLOUR_BLUE_LITE,
	COLOUR_CYAN, COLOUR_CYAN_LITE,
	COLOUR_GREEN, COLOUR_GREEN_LITE,
	COLOUR_YELLOW, COLOUR_YELLOW_LITE,
	COLOUR_ORANGE, COLOUR_ORANGE_LITE,
	COLOUR_RED, COLOUR_RED_LITE,
	COLOUR_BROWN, COLOUR_BROWN_LITE,
	COLOUR_GREY, COLOUR_GREY_LITE,
	COLOUR_BLACK, COLOUR_WHITE
};

RECT ARR_COLOUR_BTN_POS[20] = {
	{29, 71, 48, 90}, {57, 71, 76, 90},
	{29, 99, 48, 118}, {57, 99, 76, 118},
	{29, 127, 48, 146}, {57, 127, 76, 146},
	{29, 155, 48, 174}, {57, 155, 76, 174},
	{29, 183, 48, 202}, {57, 183, 76, 202},
	{29, 211, 48, 230}, {57, 211, 76, 230},
	{29, 239, 48, 258}, {57, 239, 76, 258},
	{29, 267, 48, 286}, {57, 267, 76, 286},
	{29, 295, 48, 314}, {57, 295, 76, 314},
	{29, 323, 48, 342}, {57, 323, 76, 342}
};

#define WIDTH_OF_WINDOW 960
#define HEIGHT_OF_WINDOW 550
#define HEIGHT_OF_OPTWINDOW 45

struct ColorRGB
{
	int r, g, b;
	COLORREF active_color;
}
rgb={0, 0, 0, COLOUR_BLACK};

namespace fDraw
{
	bool fDraw(false);
}

class MyHandles
{
	public:
		HWND hWndMain;
		HWND hWndOptions;
		HWND hWndFieldDrawing;
} ObjMyHandles;

//init functions
	/*test functions(print)*/
	VOID printVar(long);
	VOID printVar(char*);
	/*draw line*/
	BOOL Line(HDC, int, int, int, int);
	/*get Default Font*/
	HFONT GetDefaultFont(HDC);
	/*init font (used PrintText)*/
	VOID InitFont(HDC&, HFONT&, LONG, LONG, char*);
	/*print text*/
	VOID PrintText(HDC, char*, RECT*, char*, int, COLORREF);
	/*draw frame*/
	VOID DrawFrame(HDC, RECT*, bool, bool, bool, bool);

namespace MicroPaint
{
	struct PT {POINT pt;};
	class MyWindow
	{
		friend LRESULT CALLBACK WindowProcedure_main(HWND, UINT, WPARAM, LPARAM);
		friend LRESULT CALLBACK WindowProcedure_options(HWND, UINT, WPARAM, LPARAM);
		friend LRESULT CALLBACK WindowProcedure_fd(HWND, UINT, WPARAM, LPARAM);

		private:
			//names of the class (initialized, when the constructor is called)
			LPCSTR szClassMain;
			LPCSTR szClassOptions;
			LPCSTR szClassFieldDrawing;
			int optSize, optAlpha, optChoice;

		private:
			BOOL InitApplication(HINSTANCE);
			BOOL InitInstance(HINSTANCE, int);

			//used in MainWindow
			bool Buttonflag;
			bool Buttonflag2;

			//used in OptionsWindow
			bool OptWinflag;

			bool Sliderflag;
			bool Alphaflag;
			bool Choiceflag;

		public:
			MyWindow(HINSTANCE&, HINSTANCE&, LPSTR&, int&);
			~MyWindow();

			VOID CreateDestroyOptionsWindow();
			VOID DrawButton(HDC, RECT*, COLORREF);
			VOID DrawRoundButton(int, int, WCHAR*, bool);
			INT DrawSlider(int, int, int, int, bool);
			VOID DrawAlphaButton(int, int, bool);
			VOID DrawChoiceButton(int, int, bool);

			bool GetSliderflag() {return Sliderflag;}
			bool GetAlphaflag() {return Alphaflag;}
			bool GetChoiceflag() {return Choiceflag;}
			void SetSliderflag(bool Sliderflag) {this->Sliderflag = Sliderflag;}
			void SetAlphaflag(bool Alphaflag) {this->Alphaflag = Alphaflag;}
			void SetChoiceflag(bool Choiceflag) {this->Choiceflag = Choiceflag;}

			bool GetOptWinflag() {return OptWinflag;}
			void SetOptWinflag(bool OptWinflag) {this->OptWinflag = OptWinflag;}

			bool GetButtonflag() {return Buttonflag;}
			void SetButtonflag(bool Buttonflag) {this->Buttonflag = Buttonflag;}
			bool GetButtonflag2() {return Buttonflag2;}
			void SetButtonflag2(bool Buttonflag2) {this->Buttonflag2 = Buttonflag2;}

			int GetSize() {return optSize;}
			void SetSize(int Size) {this->optSize = Size;}
			int GetAlpha() {return optAlpha;}
			void SetAlpha(int Alpha) {this->optAlpha = Alpha;}
			int GetChoice() {return optChoice;}
			void SetChoice(int Choice) {this->optChoice = Choice;}

			//main painting tool
			VOID OnDrawLine(HDC&, int, int, int, int);

			//Bitmap
			HBITMAP hBitmap, hMemBitmap;
			VOID DrawBitmap(HDC, HBITMAP, int, int);

			void On_clear_function();
			void On_save_function();
			void On_load_function();
	};
}

//////////////////////////////////////////////////////////////////////////
//Start MicroPaint
//////////////////////////////////////////////////////////////////////////
MicroPaint::MyWindow *ObjMyWindow;
int WINAPI WinMain(
	HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	using MicroPaint::MyWindow;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);//initialize GdiPlus

	ObjMyWindow = new MyWindow(hThisInstance, hPrevInstance, lpszArgument, nCmdShow);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	delete ObjMyWindow;
	GdiplusShutdown(gdiplusToken);//cleaning
	return static_cast<int>(message.wParam);
}

MicroPaint::MyWindow::MyWindow(HINSTANCE& hThisInstance, HINSTANCE& hPrevInstance, LPSTR& lpszArgument, int& nCmdShow)
	:szClassMain("ClassMain"), szClassOptions("ClassOptions"), szClassFieldDrawing("ClassFieldDrawing"),
	Sliderflag(false), Alphaflag(false), Choiceflag(false),
	OptWinflag(false), Buttonflag(false), Buttonflag2(false)
{
	FILE *in = fopen(".\\config.ini", "r");
	if (!in) {
		MessageBox(NULL, (LPCTSTR)"Can not open config.ini", "Message: Error", MB_OK);
		fcloseall();
		exit(NULL);
	}
	else
		fcloseall();

	optSize = GetPrivateProfileIntW(L"Settings", L"size", 0, L".\\config.ini");
	optAlpha = GetPrivateProfileIntW(L"Settings", L"alpha", 0, L".\\config.ini");
	optChoice = GetPrivateProfileIntW(L"Settings", L"choice", 0, L".\\config.ini");

	if (!(optSize>=0&&optSize<=100)||
		!((optAlpha>=0&&optAlpha<=100)&&(optAlpha%5==0))||
		!(optChoice==1||optChoice==2)) {
		MessageBox(NULL, (LPCTSTR)"Еrror config.ini", "Message: Error", MB_OK);
		exit(NULL);
	}

	if (!hPrevInstance)
		if (!InitApplication(hThisInstance)) {
			MessageBox(NULL, (LPCTSTR)"Bad window profile (function: InitApplication)", "Message: Error", MB_OK);
			exit(NULL);
		}

	if (!InitInstance(hThisInstance, nCmdShow)) {
		MessageBox(NULL, (LPCTSTR)"Еrror creating window (function: InitInstance)", "Message: Error", MB_OK);
		exit(NULL);
	}
}

MicroPaint::MyWindow::~MyWindow()
{
}

BOOL MicroPaint::MyWindow::InitApplication(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.style			= CS_DBLCLKS;
	wc.lpfnWndProc		= static_cast<WNDPROC>(WindowProcedure_main);
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	wc.lpszClassName	= szClassMain;
	wc.lpszMenuName		= NULL;
	wc.cbSize			= sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
		return FALSE;

	wc.style			= CS_DBLCLKS;
	wc.lpfnWndProc		= static_cast<WNDPROC>(WindowProcedure_options);
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	wc.lpszClassName	= szClassOptions;
	wc.lpszMenuName		= NULL;
	wc.cbSize			= sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
		return FALSE;

	wc.style			= CS_DBLCLKS;
	wc.lpfnWndProc		= static_cast<WNDPROC>(WindowProcedure_fd);
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_CROSS);
	wc.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
	wc.lpszClassName	= szClassFieldDrawing;
	wc.lpszMenuName		= NULL;
	wc.cbSize			= sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
		return FALSE;

	return TRUE;
}

BOOL MicroPaint::MyWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int CW_WIDTH(WIDTH_OF_WINDOW);//window width
	int CW_HEIGHT(HEIGHT_OF_WINDOW);//window height
	int CW_X=rect.left+(rect.right-rect.left-CW_WIDTH)/2;//position X
	int CW_Y=rect.top+(rect.bottom-rect.top-CW_HEIGHT)/2;//position Y

	//create main window
	ObjMyHandles.hWndMain=CreateWindowEx(
		WS_EX_NOPARENTNOTIFY,
		szClassMain,
		NULL,
		WS_VISIBLE|WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		CW_X, CW_Y,
		CW_WIDTH, CW_HEIGHT,
		HWND_DESKTOP, NULL, hInstance, NULL
	);

	if (!ObjMyHandles.hWndMain)
		return FALSE;

	if (!ShowWindow(ObjMyHandles.hWndMain, nCmdShow))
		return FALSE;

	if (!UpdateWindow(ObjMyHandles.hWndMain))
		return FALSE;

	//create field for the drawing
	ObjMyHandles.hWndFieldDrawing=CreateWindowEx(
		WS_EX_NOPARENTNOTIFY,
		szClassFieldDrawing,
		NULL,
		WS_VISIBLE|WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		CW_X+100, CW_Y+40,
		CW_WIDTH-120, CW_HEIGHT-60,
		ObjMyHandles.hWndMain, NULL, hInstance, NULL
	);

	if (!ObjMyHandles.hWndFieldDrawing)
		return FALSE;

	if (!ShowWindow(ObjMyHandles.hWndFieldDrawing, nCmdShow))
		return FALSE;

	if (!UpdateWindow(ObjMyHandles.hWndFieldDrawing))
		return FALSE;

	return TRUE;
}

VOID MicroPaint::MyWindow::CreateDestroyOptionsWindow()
{
	if (OptWinflag) {
		SendMessage(ObjMyHandles.hWndOptions, WM_CLOSE, 0, 0);//send a signal to close the window
		OptWinflag=false;
		return;
	}
	else {
		RECT rect={0};
		GetWindowRect(ObjMyHandles.hWndMain, &rect);

		int CW_WIDTH(WIDTH_OF_WINDOW);
		int CW_HEIGHT(HEIGHT_OF_OPTWINDOW);
		int CW_X=rect.left;
		int CW_Y=rect.top+(HEIGHT_OF_WINDOW-1);

		ObjMyHandles.hWndOptions=CreateWindowEx(
			WS_EX_NOPARENTNOTIFY,
			szClassOptions,
			NULL,
			WS_VISIBLE|WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
			CW_X, CW_Y,
			CW_WIDTH, CW_HEIGHT,
			ObjMyHandles.hWndMain, NULL, NULL, NULL
		);
		OptWinflag=true;
	}
}

VOID MicroPaint::MyWindow::DrawButton(HDC hDC, RECT* rect, COLORREF rgb)
{
	//create a new brush and pen, default are saved
	HPEN hPen(CreatePen(PS_SOLID, 1, rgb));
	HPEN hOldPen(static_cast<HPEN>(SelectObject(hDC, hPen)));
	HBRUSH hBrush(CreateSolidBrush(rgb));
	HBRUSH hOldBrush(static_cast<HBRUSH>(SelectObject(hDC, hBrush)));
	//draw button
	FillRect(hDC, &(*rect), hBrush);
	DrawFrame(hDC, &(*rect), TRUE, TRUE, TRUE, TRUE);
	//set default
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);
	//removing objects from memory
	DeleteObject(hPen);
	DeleteObject(hBrush);
	return;
}

VOID MicroPaint::MyWindow::DrawRoundButton(int posX, int posY, WCHAR* text, bool move)
{
	HDC hDC=GetDC(ObjMyHandles.hWndMain);

	if (!move) {
		HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
		HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
		HPEN hPenBackground=CreatePen(PS_SOLID, 1, COLOUR_BACKGROUND);
		HBRUSH hBrushBackground(CreateSolidBrush(COLOUR_BACKGROUND));
		SelectObject(hDC, hPenBackground); SelectObject(hDC, hBrushBackground);
		Rectangle(hDC, posX-2, posY-2, posX+48, posY+48);
		//set default
		SelectObject(hDC, hOldPen); SelectObject(hDC, hOldBrush);
		//removing objects from memory
		DeleteObject(hPenBackground);
		DeleteObject(hBrushBackground);
	}
	Graphics gr(hDC);
	gr.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	Font t_font(&FontFamily(L"Lucida Handwriting"), 10);
	SolidBrush brush(Color(255, GetRValue(COLOUR_GREY), GetGValue(COLOUR_GREY), GetBValue(COLOUR_GREY)));
	SolidBrush t_brush(Color(255, 70, 70, 70));
	if (move)
		t_brush.SetColor(Color(255, 255, 255, 255));
	PointF *t_point = new PointF;
	t_point->X = posX+2;//for text
	t_point->Y = posY+14;//for text
	gr.FillEllipse(&brush, posX, posY, 45, 45);
	gr.DrawString(text, -1, &t_font, *t_point, &t_brush);
	delete t_point;
	ReleaseDC(ObjMyHandles.hWndMain, hDC);
	return;
}

MicroPaint::PT ptSLD = {150+(3*(GetPrivateProfileIntW(L"Settings", L"size", 0, L".\\config.ini"))), 5};//called directly, because ObjMyWindow->GetSize() - not initialized :(
MicroPaint::PT ptThis = {0};
MicroPaint::PT ptPrev = {0};
INT MicroPaint::MyWindow::DrawSlider(int posFromX, int posTop, int posToX, int posBottom, bool move)
{
	HDC hDC=GetDC(ObjMyHandles.hWndOptions);
	RECT rect;

	HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
	HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
	HPEN hPenGrey=CreatePen(PS_SOLID, 1, RGB(85, 85, 85));
	HBRUSH hBrushGrey(CreateSolidBrush(RGB(127, 127, 127)));
	HPEN hPenBackground=CreatePen(PS_SOLID, 1, COLOUR_BACKGROUND);
	HBRUSH hBrushBackground(CreateSolidBrush(COLOUR_BACKGROUND));

	if (ptSLD.pt.x<posFromX)
		ptSLD.pt.x=posFromX;
	
	if (ptSLD.pt.x>posToX)
		ptSLD.pt.x=posToX;

	if (move==true) {
		SelectObject(hDC, hPenBackground); SelectObject(hDC, hBrushBackground);
		RECT rect={posFromX, posTop, posToX-1, posBottom-1};
		DrawFrame(hDC, &rect, TRUE, TRUE, TRUE, TRUE);
		SelectObject(hDC, hPenGrey); SelectObject(hDC, hBrushGrey);
		Rectangle(hDC, posFromX+1, posTop+1, ptSLD.pt.x, posBottom-1);
		SelectObject(hDC, hBrushBackground);
		Rectangle(hDC, ptSLD.pt.x, posTop+1, posToX-1, posBottom-1);
		SelectObject(hDC, hPenBackground);
	}
	else {
		SelectObject(hDC, hPenGrey); SelectObject(hDC, hBrushGrey);
		Rectangle(hDC, posFromX, posTop, posToX, posBottom);
		SelectObject(hDC, hBrushBackground);
		Rectangle(hDC, ptSLD.pt.x, posTop, posToX, posBottom);
	}

	//draw text
	SelectObject(hDC, hPenBackground); SelectObject(hDC, hBrushBackground);
	char* text="point";
	rect.left=posFromX-45; rect.top=posTop;
	rect.right=posFromX-5; rect.bottom=posTop+20;
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	PrintText(hDC, text, &rect, "Lucida Handwriting", -12, RGB(0, 70, 70));

	//draw percent
	int percentage((ptSLD.pt.x-posFromX)/((posToX-posFromX)/100));
	char buff[16];
	char* pct;
	itoa(percentage, buff, 10);
	pct=strcat(buff, "%");
	SelectObject(hDC, hPenBackground);
	rect.left=posToX+5; rect.top=posTop;
	rect.right=posToX+45; rect.bottom=posBottom;
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	PrintText(hDC, pct, &rect, "Lucida Handwriting", -12, RGB(30, 30, 30));

	//set default
	SelectObject(hDC, hOldPen); SelectObject(hDC, hOldBrush);

	//removing objects from memory
	DeleteObject(hPenGrey);
	DeleteObject(hBrushGrey);
	DeleteObject(hPenBackground);
	DeleteObject(hBrushBackground);
	
	ReleaseDC(ObjMyHandles.hWndOptions, hDC);
	return percentage;
}

VOID MicroPaint::MyWindow::DrawAlphaButton(int posX, int posY, bool move)
{
	HDC hDC=GetDC(ObjMyHandles.hWndOptions);
	RECT rect;

	COLORREF rgb;
	switch (optAlpha) {
		case 0:		{int value(200); rgb = RGB(value, value, value);} break;
		case 5:		{int value(194); rgb = RGB(value, value, value);} break;
		case 10:	{int value(188); rgb = RGB(value, value, value);} break;
		case 15:	{int value(182); rgb = RGB(value, value, value);} break;
		case 20:	{int value(176); rgb = RGB(value, value, value);} break;
		case 25:	{int value(170); rgb = RGB(value, value, value);} break;
		case 30:	{int value(164); rgb = RGB(value, value, value);} break;
		case 35:	{int value(158); rgb = RGB(value, value, value);} break;
		case 40:	{int value(152); rgb = RGB(value, value, value);} break;
		case 45:	{int value(146); rgb = RGB(value, value, value);} break;
		case 50:	{int value(140); rgb = RGB(value, value, value);} break;
		case 55:	{int value(134); rgb = RGB(value, value, value);} break;
		case 60:	{int value(128); rgb = RGB(value, value, value);} break;
		case 65:	{int value(122); rgb = RGB(value, value, value);} break;
		case 70:	{int value(116); rgb = RGB(value, value, value);} break;
		case 75:	{int value(110); rgb = RGB(value, value, value);} break;
		case 80:	{int value(104); rgb = RGB(value, value, value);} break;
		case 85:	{int value(98);  rgb = RGB(value, value, value);} break;
		case 90:	{int value(92);  rgb = RGB(value, value, value);} break;
		case 95:	{int value(86);  rgb = RGB(value, value, value);} break;
		case 100:	{int value(80);  rgb = RGB(value, value, value);} break;
		default:	{int value(0);   rgb = RGB(value, value, value);} break;
	}

	if (optChoice==1) {
		int value(200); rgb = RGB(value, value, value);
	}

	HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
	HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
	HPEN hPenGrey=CreatePen(PS_SOLID, 1, RGB(85, 85, 85));
	HBRUSH hBrushGrey(CreateSolidBrush(rgb));
	HPEN hPenBackground=CreatePen(PS_SOLID, 1, COLOUR_BACKGROUND);
	HBRUSH hBrushBackground(CreateSolidBrush(COLOUR_BACKGROUND));

	//draw text
	SelectObject(hDC, hPenBackground); SelectObject(hDC, hBrushBackground);
	char* text="alpha";
	rect.left=posX-55; rect.top=posY;
	rect.right=posX-5; rect.bottom=posY+20;
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	PrintText(hDC, text, &rect, "Lucida Handwriting", -12, RGB(0, 70, 70));

	//draw button
	SelectObject(hDC, hPenGrey); SelectObject(hDC, hBrushGrey);
	if (move) {
		rect.left=(posX)+1; rect.top=(posY)+1;
		rect.right=(posX+45)-1; rect.bottom=(posY+20)-1;
	}
	else {
		rect.left=posX; rect.top=posY;
		rect.right=posX+45; rect.bottom=posY+20;
	}
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

	//draw percent
	int percentage(optAlpha);
	if (optChoice==2) {
		char buff[16];
		char* pct;
		itoa(percentage, buff, 10);
		pct=strcat(buff, "%");
		PrintText(hDC, pct, &rect, "Lucida Handwriting", -12, RGB(30, 30, 30));
	}
	else {
		if (optChoice==1)
			PrintText(hDC, "off", &rect, "Lucida Handwriting", -12, RGB(60, 0, 0));
	}

	//set frame
	if (move) {
		rect.left=posX; rect.top=posY;
		rect.right=(posX+45)-1; rect.bottom=(posY+20)-1;
		SelectObject(hDC, hPenBackground); SelectObject(hDC, hBrushBackground);
		DrawFrame(hDC, &rect, TRUE, TRUE, TRUE, TRUE);
	}

	//set default
	SelectObject(hDC, hOldPen); SelectObject(hDC, hOldBrush);

	//removing objects from memory
	DeleteObject(hPenGrey);
	DeleteObject(hBrushGrey);
	DeleteObject(hPenBackground);
	DeleteObject(hBrushBackground);

	ReleaseDC(ObjMyHandles.hWndOptions, hDC);
	return;
}

VOID MicroPaint::MyWindow::DrawChoiceButton(int posX, int posY, bool move)
{
	HDC hDC=GetDC(ObjMyHandles.hWndOptions);
	RECT rect;

	HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
	HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
	HPEN hPenGrey=CreatePen(PS_SOLID, 1, RGB(85, 85, 85));
	HBRUSH hBrushGrey(CreateSolidBrush(RGB(127, 127, 127)));
	HPEN hPenBackground=CreatePen(PS_SOLID, 1, COLOUR_BACKGROUND);
	HBRUSH hBrushBackground(CreateSolidBrush(COLOUR_BACKGROUND));

	//draw text
	SelectObject(hDC, hPenBackground); SelectObject(hDC, hBrushBackground);
	char* text;
	if (optChoice==1) 
		text="brush";
	if (optChoice==2)
		text="  pen";

	rect.left=posX-55; rect.top=posY;
	rect.right=posX-5; rect.bottom=posY+20;
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	PrintText(hDC, text, &rect, "Lucida Handwriting", -12, RGB(0, 70, 70));

	//draw button
	SelectObject(hDC, hPenGrey); SelectObject(hDC, hBrushBackground);
	rect.left=posX; rect.top=posY;
	rect.right=posX+40; rect.bottom=posY+20;
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(hDC, hPenGrey); SelectObject(hDC, hBrushGrey);
	if (optChoice==1) {
		rect.left=posX; rect.top=posY;
		rect.right=posX+20; rect.bottom=posY+20;
	}
	if (optChoice==2) {
		rect.left=posX+20; rect.top=posY;
		rect.right=posX+40; rect.bottom=posY+20;
	}
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

	//set frame
	if (move) {
		rect.left=posX; rect.top=posY;
		rect.right=(posX+40)-1; rect.bottom=(posY+20)-1;
		SelectObject(hDC, hPenBackground);
		DrawFrame(hDC, &rect, TRUE, TRUE, TRUE, TRUE);

		rect.left=posX+1; rect.top=posY+1;
		rect.right=(posX+40)-2; rect.bottom=(posY+20)-2;
		SelectObject(hDC, hPenGrey);
		DrawFrame(hDC, &rect, TRUE, TRUE, TRUE, TRUE);
	}

	//set default
	SelectObject(hDC, hOldPen); SelectObject(hDC, hOldBrush);

	//removing objects from memory
	DeleteObject(hPenGrey);
	DeleteObject(hBrushGrey);
	DeleteObject(hPenBackground);
	DeleteObject(hBrushBackground);
	
	ReleaseDC(ObjMyHandles.hWndOptions, hDC);
	return;
}

//test functions(print)
VOID printVar(long var) {
	char buf[10];
	ltoa(var, buf, 10);
	MessageBox(NULL, (LPCTSTR)buf, "Message", MB_OK);
	return;
}
VOID printVar(char* var) {
	MessageBox(NULL, (LPCTSTR)var, "Message", MB_OK);
	return;
}
//draw line
BOOL Line(HDC hDC, int x1, int y1, int x2, int y2) {
	MoveToEx(hDC, x1, y1, NULL);
	return LineTo(hDC, x2, y2);//set the current coordinates x1, y1
}
//get Default Font
HFONT GetDefaultFont(HDC hDC) {
	SetBkMode(hDC, BKMODE_LAST);
	return (HFONT)GetStockObject(DEVICE_DEFAULT_FONT);
}
//init font (used PrintText)
VOID InitFont(HDC& hDC, HFONT& hfont, LONG lfheight, LONG lfweight, char* namefont) {
	LOGFONT lf;
	memset(&lf, NULL, sizeof(lf));
	lf.lfHeight=lfheight;
	lf.lfWeight=lfweight;
	strcpy(lf.lfFaceName, namefont);
	hfont=CreateFontIndirect(&lf);
	SelectObject(hDC, hfont);
	return;
}
//print text
VOID PrintText(HDC hDC, char* text, RECT* rect, char* fontName, int size, COLORREF color) {
	COLORREF oldColor(SetTextColor(hDC, COLOUR_BLACK));
	COLORREF oldBkColor(SetBkColor(hDC, COLOUR_WHITE));
	SetTextColor(hDC, color);
	SetBkColor(hDC, COLOUR_BACKGROUND);

	HFONT hFont;//font for the text
	InitFont(hDC, hFont, size, FW_NORMAL, fontName);
	SetBkMode(hDC, TRANSPARENT);
	DrawText(hDC, text, strlen(text), &(*rect), DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	SelectObject(hDC, GetDefaultFont(hDC));//restore default font

	SetTextColor(hDC, oldColor);
	SetBkColor(hDC, oldBkColor);
	DeleteObject(hFont);//removing object from memory
	return;
}
//draw frame
VOID DrawFrame(HDC hDC, RECT* rect, bool left, bool top, bool right, bool bottom) {
	MoveToEx(hDC, (*rect).left, (*rect).top, NULL);
	if (top) {
		LineTo(hDC, (*rect).right+1, (*rect).top);
		MoveToEx(hDC, (*rect).right, (*rect).top, NULL);
	} else
		MoveToEx(hDC, (*rect).right, (*rect).top, NULL);
	if (right) {
		LineTo(hDC, (*rect).right, (*rect).bottom+1);
		MoveToEx(hDC, (*rect).right, (*rect).bottom, NULL);
	} else
		MoveToEx(hDC, (*rect).right, (*rect).bottom, NULL);
	if (bottom) {
		LineTo(hDC, (*rect).left-1, (*rect).bottom);
		MoveToEx(hDC, (*rect).left, (*rect).bottom, NULL);
	} else
		MoveToEx(hDC, (*rect).left, (*rect).bottom, NULL);
	if (left) {
		LineTo(hDC, (*rect).left, (*rect).top-1);
		MoveToEx(hDC, (*rect).left, (*rect).top, NULL);
	} else
		MoveToEx(hDC, (*rect).left, (*rect).top, NULL);

	MoveToEx(hDC, 0, 0, NULL);
	return;
}

HDC hDC, hMemDC;//device context for drawing and memory
VOID PaintMain();
VOID PaintOptions();

//////////////////////////////////////////////////////////////////////////
//Message handler of the main window
//////////////////////////////////////////////////////////////////////////
POINT MousePnt, CurrentMousePnt;
RECT wndrect, btnrect;
bool movestop(false);
namespace MicroPaint
{
	LRESULT CALLBACK WindowProcedure_main(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {
			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			case WM_CLOSE:
				if (ObjMyWindow->GetOptWinflag()) {
					SendMessage(ObjMyHandles.hWndFieldDrawing, WM_CLOSE, 0, 0);
					SendMessage(ObjMyHandles.hWndOptions, WM_CLOSE, 0, 0);
				} else
					SendMessage(ObjMyHandles.hWndFieldDrawing, WM_CLOSE, 0, 0);
				Sleep(450);
				AnimateWindow(hWnd, 300, AW_HIDE|AW_CENTER);
				SendMessage(ObjMyHandles.hWndMain, WM_DESTROY, 0, 0);
				break;

			case WM_SIZE:
				{
					switch (wParam) {
						case SIZE_MINIMIZED: //window is minimized
							ShowWindow(ObjMyHandles.hWndMain, SW_SHOWMINIMIZED);
							break;

						case SIZE_MAXIMIZED: //window is maximized
							ShowWindow(ObjMyHandles.hWndMain, SW_SHOWMAXIMIZED);
							break;

						default:
							break;
					}
				}
				break;

			case WM_LBUTTONDOWN: //when holding the left mouse button
				if ((LOWORD(lParam)>29&&LOWORD(lParam)<76)&&(HIWORD(lParam)>71&&HIWORD(lParam)<342))
					movestop=true;
				SetCapture(ObjMyHandles.hWndMain);
				GetCursorPos(&MousePnt);
				{
					//save bitmap in memory
					hDC=GetDC(ObjMyHandles.hWndFieldDrawing);
					hMemDC=CreateCompatibleDC(hDC);
					ObjMyWindow->hBitmap=CreateCompatibleBitmap(hDC, WIDTH_OF_WINDOW-120, HEIGHT_OF_WINDOW-60);
					SelectObject(hMemDC, ObjMyWindow->hBitmap);
					BitBlt(hMemDC, 0, 0, WIDTH_OF_WINDOW-120, HEIGHT_OF_WINDOW-60, hDC, 0, 0, 0xE20746L);
					DeleteDC(hMemDC);
					ReleaseDC(ObjMyHandles.hWndFieldDrawing, hDC);
				}
				break;

			case WM_LBUTTONUP: //when the left mouse button is released
				if (movestop)
					movestop=false;
				ReleaseCapture();
				{
					hDC=GetDC(ObjMyHandles.hWndFieldDrawing);
					ObjMyWindow->DrawBitmap(hDC, ObjMyWindow->hBitmap, 0, 0);
					ReleaseDC(ObjMyHandles.hWndFieldDrawing, hDC);
				}
				{
					if ((LOWORD(lParam)>810&&LOWORD(lParam)<955)&&(HIWORD(lParam)>5&&HIWORD(lParam)<25)) {
						(LOWORD(lParam)>810&&LOWORD(lParam)<855) ? ObjMyWindow->CreateDestroyOptionsWindow():							//show or close options
						(LOWORD(lParam)>860&&LOWORD(lParam)<905) ? SendMessage(ObjMyHandles.hWndMain, WM_SIZE, SIZE_MINIMIZED, 0):		//minimize the window
						(LOWORD(lParam)>910&&LOWORD(lParam)<955) ? SendMessage(ObjMyHandles.hWndMain, WM_CLOSE, 0, 0):					//close the window
						NULL;
					}
					if ((LOWORD(lParam)>27&&LOWORD(lParam)<79)&&(HIWORD(lParam)>357&&HIWORD(lParam)<529)) {
						(HIWORD(lParam)>357&&HIWORD(lParam)<409) ? ObjMyWindow->On_clear_function():
						(HIWORD(lParam)>417&&HIWORD(lParam)<469) ? ObjMyWindow->On_save_function():
						(HIWORD(lParam)>477&&HIWORD(lParam)<529) ? ObjMyWindow->On_load_function():
						NULL;
					}
					if ((LOWORD(lParam)>29&&LOWORD(lParam)<76)&&(HIWORD(lParam)>71&&HIWORD(lParam)<342)) {
						for (int i(0); i<20; ++i) {
							if (LOWORD(lParam)>ARR_COLOUR_BTN_POS[i].left&&LOWORD(lParam)<ARR_COLOUR_BTN_POS[i].right&&
								HIWORD(lParam)>ARR_COLOUR_BTN_POS[i].top&&HIWORD(lParam)<ARR_COLOUR_BTN_POS[i].bottom) {
									HDC hDC(GetDC(ObjMyHandles.hWndMain));
									HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
									HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
									HBRUSH hBrush;
									HPEN hPen=CreatePen(PS_SOLID, 1, COLOUR_WHITE);
									SelectObject(hDC, hPen);
									for (int k(0); k<20; ++k) {
										hBrush=CreateSolidBrush(ARR_COLOUR_BTN[k]); SelectObject(hDC, hBrush);
										Rectangle(hDC,
											ARR_COLOUR_BTN_POS[k].left,
											ARR_COLOUR_BTN_POS[k].top,
											ARR_COLOUR_BTN_POS[k].right,
											ARR_COLOUR_BTN_POS[k].bottom
										);
										DeleteObject(hBrush);	
									}

									//set active color
									rgb.active_color = ARR_COLOUR_BTN[i];
									rgb.r = GetRValue(ARR_COLOUR_BTN[i]);
									rgb.g = GetGValue(ARR_COLOUR_BTN[i]);
									rgb.b = GetBValue(ARR_COLOUR_BTN[i]);

									//draw active color
									RECT _rect = {ARR_COLOUR_BTN_POS[i].left, ARR_COLOUR_BTN_POS[i].top, ARR_COLOUR_BTN_POS[i].right, ARR_COLOUR_BTN_POS[i].bottom};
									if ((rgb.r==255)&&(rgb.g==255)&&(rgb.b==255))
										PrintText(hDC, "X", &_rect, "Lucida Handwriting", -16, COLOUR_BLACK);
									else
										PrintText(hDC, "X", &_rect, "Lucida Handwriting", -16, COLOUR_WHITE);

									//set default
									SelectObject(hDC, hOldPen);
									SelectObject(hDC, hOldBrush);

									//removing objects from memory
									DeleteObject(hPen);
									ReleaseDC(ObjMyHandles.hWndMain, hDC);//exempt DC

									break;
							}
						}
					}
				}
				break;

			case WM_MOUSEMOVE: //when the mouse cursor moves across the screen
				if (wParam & WM_LBUTTONDOWN && !fDraw::fDraw) {
					hDC=GetDC(ObjMyHandles.hWndFieldDrawing);
					HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
					HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
					HPEN hPenWhite=CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); SelectObject(hDC, hPenWhite);
					HBRUSH hBrushWhite=CreateSolidBrush(RGB(255, 255, 255)); SelectObject(hDC, hBrushWhite);
					Rectangle(hDC, 0, 0, WIDTH_OF_WINDOW-120, HEIGHT_OF_WINDOW-60);
					//set default
					SelectObject(hDC, hOldPen);
					SelectObject(hDC, hOldBrush);

					//removing objects from memory
					DeleteObject(hPenWhite);
					DeleteObject(hBrushWhite);
	
					ReleaseDC(ObjMyHandles.hWndFieldDrawing, hDC);
				}
				if ((LOWORD(lParam)>810&&LOWORD(lParam)<955)&&(HIWORD(lParam)>5&&HIWORD(lParam)<25)) {
					hDC=GetDC(ObjMyHandles.hWndMain);
					HPEN hPenBackground=CreatePen(PS_SOLID, 1, COLOUR_BACKGROUND);
					HPEN hOldPen=(HPEN)SelectObject(hDC, hPenBackground);
					if (LOWORD(lParam)>810&&LOWORD(lParam)<855&&!ObjMyWindow->GetButtonflag()&&!fDraw::fDraw) {
						btnrect.top=5; btnrect.left=810; btnrect.bottom=25; btnrect.right=855;
						DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
						ObjMyWindow->SetButtonflag(true);
					} else
					if (LOWORD(lParam)>860&&LOWORD(lParam)<905&&!ObjMyWindow->GetButtonflag()&&!fDraw::fDraw) {
						btnrect.top=5; btnrect.left=860; btnrect.bottom=25; btnrect.right=905;
						DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
						ObjMyWindow->SetButtonflag(true);
					} else
					if (LOWORD(lParam)>910&&LOWORD(lParam)<955&&!ObjMyWindow->GetButtonflag()&&!fDraw::fDraw) {
						btnrect.top=5; btnrect.left=910; btnrect.bottom=25; btnrect.right=955;
						DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
						ObjMyWindow->SetButtonflag(true);
					} else
					if (((LOWORD(lParam)>=855&&LOWORD(lParam)<=860)||(LOWORD(lParam)>=905&&LOWORD(lParam)<=910))&&ObjMyWindow->GetButtonflag()) {
						HPEN hPenBlue=CreatePen(PS_SOLID, 1, COLOUR_BTN_BLUE);
						HPEN hPenRed=CreatePen(PS_SOLID, 1, COLOUR_BTN_RED);
						SelectObject(hDC, hPenBlue);
						btnrect.top=5; btnrect.left=810; btnrect.bottom=25; btnrect.right=855;
						DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
						btnrect.top=5; btnrect.left=860; btnrect.bottom=25; btnrect.right=905;
						DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
						SelectObject(hDC, hPenRed);
						btnrect.top=5; btnrect.left=910; btnrect.bottom=25; btnrect.right=955;
						DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
						SelectObject(hDC, hOldPen);
						DeleteObject(hPenBlue);
						DeleteObject(hPenRed);
						ObjMyWindow->SetButtonflag(false);
					}
					DeleteObject(hPenBackground);
					ReleaseDC(ObjMyHandles.hWndMain, hDC);//exempt DC
				} else
				if (ObjMyWindow->GetButtonflag()==true) {
					hDC=GetDC(ObjMyHandles.hWndMain);
					HPEN hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
					HPEN hPenBlue=CreatePen(PS_SOLID, 1, COLOUR_BTN_BLUE);
					HPEN hPenRed=CreatePen(PS_SOLID, 1, COLOUR_BTN_RED);

					SelectObject(hDC, hPenBlue);
					btnrect.top=5; btnrect.left=810; btnrect.bottom=25; btnrect.right=855;
					DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
					btnrect.top=5; btnrect.left=860; btnrect.bottom=25; btnrect.right=905;
					DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
					SelectObject(hDC, hPenRed);
					btnrect.top=5; btnrect.left=910; btnrect.bottom=25; btnrect.right=955;
					DrawFrame(hDC, &btnrect, TRUE, TRUE, TRUE, TRUE);
				
					SelectObject(hDC, hOldPen);
					DeleteObject(hPenBlue);
					DeleteObject(hPenRed);
					ReleaseDC(ObjMyHandles.hWndMain, hDC);//exempt DC
					ObjMyWindow->SetButtonflag(false);
				}
				if (!((LOWORD(lParam)>29&&LOWORD(lParam)<76)&&(HIWORD(lParam)>71&&HIWORD(lParam)<342))&&!movestop) {
					if (wParam & WM_LBUTTONDOWN) {
						if (!fDraw::fDraw) {
							GetCursorPos(&CurrentMousePnt);//current position of the cursor
							GetWindowRect(hWnd, &wndrect);//current size of the window
							//edit the position of the window
							wndrect.left=wndrect.left+(CurrentMousePnt.x-MousePnt.x);
							wndrect.top=wndrect.top+(CurrentMousePnt.y-MousePnt.y);
							//new position of the windows
							SetWindowPos(hWnd, NULL, wndrect.left, wndrect.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
							SetWindowPos(ObjMyHandles.hWndFieldDrawing, NULL, wndrect.left+100, wndrect.top+40, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
							UpdateWindow(hWnd);//updates the window contents
							SetForegroundWindow(hWnd);//move focus to the window (make active)
							if (ObjMyWindow->GetOptWinflag()) {
								SendMessage(ObjMyHandles.hWndOptions, WM_CLOSE, 0, 0);//send a signal to close the window
								ObjMyWindow->SetOptWinflag(false);
							}
							MousePnt=CurrentMousePnt;//remember the current cursor position
						}
					}
				}
				if ((LOWORD(lParam)>27&&LOWORD(lParam)<79)&&(HIWORD(lParam)>357&&HIWORD(lParam)<529)) {
					if (HIWORD(lParam)>357&&HIWORD(lParam)<409&&!ObjMyWindow->GetButtonflag2()&&!fDraw::fDraw) {
						ObjMyWindow->DrawRoundButton(30, 360, L"clear", true);
						ObjMyWindow->SetButtonflag2(true);
					} else
					if (HIWORD(lParam)>417&&HIWORD(lParam)<469&&!ObjMyWindow->GetButtonflag2()&&!fDraw::fDraw) {
						ObjMyWindow->DrawRoundButton(30, 420, L"save", true);
						ObjMyWindow->SetButtonflag2(true);
					} else
					if (HIWORD(lParam)>477&&HIWORD(lParam)<529&&!ObjMyWindow->GetButtonflag2()&&!fDraw::fDraw) {
						ObjMyWindow->DrawRoundButton(30, 480, L"load", true);
						ObjMyWindow->SetButtonflag2(true);
					} else
					if ((HIWORD(lParam)>=409&&HIWORD(lParam)<=417)||(HIWORD(lParam)>=469&&HIWORD(lParam)<=477)&&ObjMyWindow->GetButtonflag2()) {
						ObjMyWindow->DrawRoundButton(30, 360, L"clear", false);
						ObjMyWindow->DrawRoundButton(30, 420, L"save", false);
						ObjMyWindow->DrawRoundButton(30, 480, L"load", false);
						ObjMyWindow->SetButtonflag2(false);
					}
				}
				else {
					if (ObjMyWindow->GetButtonflag2()==true) {
						ObjMyWindow->DrawRoundButton(30, 360, L"clear", false);
						ObjMyWindow->DrawRoundButton(30, 420, L"save", false);
						ObjMyWindow->DrawRoundButton(30, 480, L"load", false);
						ObjMyWindow->SetButtonflag2(false);
					}
				}
				break;

			case WM_RBUTTONDOWN:
				break;

			case WM_PAINT:
				PaintMain();

			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//Message handler of the options window
//////////////////////////////////////////////////////////////////////////
namespace MicroPaint
{
	LRESULT CALLBACK WindowProcedure_options(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {
			case WM_LBUTTONDOWN:
				SetCapture(ObjMyHandles.hWndOptions);
				break;
		
			case WM_LBUTTONUP:
				{
					ReleaseCapture();
					//control slider
					if (ObjMyWindow->GetSliderflag()) {
						ObjMyWindow->SetSliderflag(false);
						ObjMyWindow->SetSize(ObjMyWindow->DrawSlider(150, 5, 450, 25, false));//update slider
					}
					else {
						if (LOWORD(lParam)>=150&&LOWORD(lParam)<=450&&HIWORD(lParam)>=5&&HIWORD(lParam)<=25) {
							ptSLD.pt.x=LOWORD(lParam);
							ObjMyWindow->SetSize(ObjMyWindow->DrawSlider(150, 5, 450, 25, false));//update slider
						}
					}
					//control alpha
					if ((LOWORD(lParam)>680&&LOWORD(lParam)<720)&&(HIWORD(lParam)>5&&HIWORD(lParam)<25)&&ObjMyWindow->GetChoice()==2) {
						if (ObjMyWindow->GetAlpha()==100)
							ObjMyWindow->SetAlpha(0);
						else {
							int Alpha(ObjMyWindow->GetAlpha());
							Alpha+=5;
							ObjMyWindow->SetAlpha(Alpha);
						}
						ObjMyWindow->DrawAlphaButton(680, 5, true);//update button
					}
					//control choice
					if ((LOWORD(lParam)>560&&LOWORD(lParam)<610)&&(HIWORD(lParam)>5&&HIWORD(lParam)<25)) {
						(ObjMyWindow->GetChoice()==1)?ObjMyWindow->SetChoice(2):ObjMyWindow->SetChoice(1);
						ObjMyWindow->DrawChoiceButton(560, 5, true);//update button
						ObjMyWindow->DrawAlphaButton(680, 5, false);//update button
					}
				}
				break;
		
			case WM_MOUSEMOVE:
				//control slider
				if (wParam & WM_LBUTTONDOWN && (LOWORD(lParam)>=150&&LOWORD(lParam)<=450&&HIWORD(lParam)>=5&&HIWORD(lParam)<=25)) {
					GetCursorPos(&ptSLD.pt);
					ScreenToClient(hWnd, &ptSLD.pt);
					if ((ptSLD.pt.x>=150&&ptSLD.pt.x<=450&&ptSLD.pt.y>=5&&ptSLD.pt.y<=25)||ObjMyWindow->GetSliderflag()) {
						ObjMyWindow->SetSize(ObjMyWindow->DrawSlider(150, 5, 450, 25, true));//update button
						ObjMyWindow->SetSliderflag(true);
					}
				}
				//control alpha
				if ((LOWORD(lParam)>680&&LOWORD(lParam)<720)&&(HIWORD(lParam)>5&&HIWORD(lParam)<25)&&!ObjMyWindow->GetAlphaflag()) {
					ObjMyWindow->DrawAlphaButton(680, 5, true);//update button
					ObjMyWindow->SetAlphaflag(true);
				}
				else if (ObjMyWindow->GetAlphaflag()) {
					if (!(LOWORD(lParam)>680&&LOWORD(lParam)<720)||!(HIWORD(lParam)>5&&HIWORD(lParam)<25)) {
						ObjMyWindow->DrawAlphaButton(680, 5, false);//update button
						ObjMyWindow->SetAlphaflag(false);
					}
				}
				//control choice
				if ((LOWORD(lParam)>560&&LOWORD(lParam)<610)&&(HIWORD(lParam)>5&&HIWORD(lParam)<25)&&!ObjMyWindow->GetChoiceflag()) {
					ObjMyWindow->DrawChoiceButton(560, 5, true);//update button
					ObjMyWindow->SetChoiceflag(true);
				}
				else if (ObjMyWindow->GetChoiceflag()) {
					if (!(LOWORD(lParam)>560&&LOWORD(lParam)<610)||!(HIWORD(lParam)>5&&HIWORD(lParam)<25)) {
						ObjMyWindow->DrawChoiceButton(560, 5, false);//update button
						ObjMyWindow->SetChoiceflag(false);
					}
				}
				break;
			
			case WM_PAINT:
				PaintOptions();

			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//Message handler of the field drawing
//////////////////////////////////////////////////////////////////////////
UINT_PTR TIMER_MSEC = 1;
namespace MicroPaint
{
	LRESULT CALLBACK WindowProcedure_fd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	SetTimer(hWnd, TIMER_MSEC, 15, NULL);
	switch (message) {
		case WM_TIMER:
			GetCursorPos(&ptThis.pt);
			ScreenToClient(hWnd, &ptThis.pt);
			if (fDraw::fDraw) {
				if (DragDetect(hWnd, ptThis.pt)) {
					ptPrev.pt.x=ptThis.pt.x;
					ptPrev.pt.y=ptThis.pt.y;
				}
				else
					fDraw::fDraw=false;
			}
			break;
		case WM_LBUTTONDOWN:
			SetCapture(ObjMyHandles.hWndFieldDrawing);
			ptPrev.pt.x=LOWORD(lParam);
			ptPrev.pt.y=HIWORD(lParam);
			fDraw::fDraw=true;

			if (ObjMyWindow->GetOptWinflag()) {
				SendMessage(ObjMyHandles.hWndOptions, WM_CLOSE, 0, 0);//send a signal to close the window
				ObjMyWindow->SetOptWinflag(false);
			}
			break;
		case WM_LBUTTONUP:
			ReleaseCapture();
			if (fDraw::fDraw) {
				hDC=GetDC(hWnd);
				/*WinAPI
				MoveToEx(hDC, ptPrev.pt.x, ptPrev.pt.y, NULL);
				LineTo(hDC, LOWORD(lParam), HIWORD(lParam));
				*/
				ObjMyWindow->OnDrawLine(hDC, ptPrev.pt.x, ptPrev.pt.y, LOWORD(lParam), HIWORD(lParam));//used Gdi+
				ReleaseDC(hWnd, hDC);
				fDraw::fDraw=false;
			}
			break;
		case WM_MOUSEMOVE:
			if (fDraw::fDraw) {
				hDC=GetDC(hWnd);
				/*WinAPI
				MoveToEx(hDC, ptPrev.pt.x, ptPrev.pt.y, NULL);
				LineTo(hDC, ptPrev.pt.x=LOWORD(lParam), ptPrev.pt.y=HIWORD(lParam));
				*/
				ObjMyWindow->OnDrawLine(hDC, ptPrev.pt.x, ptPrev.pt.y, LOWORD(lParam), HIWORD(lParam));//used Gdi+
				ptPrev.pt.x=LOWORD(lParam);
				ptPrev.pt.y=HIWORD(lParam);
				ReleaseDC(hWnd, hDC);
			}
			break;
		case WM_PAINT:
			{
				static bool start_once=false;
				if (start_once) {
					hDC=GetDC(ObjMyHandles.hWndFieldDrawing);
					ObjMyWindow->DrawBitmap(hDC, ObjMyWindow->hBitmap, 0, 0);
					ReleaseDC(ObjMyHandles.hWndFieldDrawing, hDC);
				}
				else
					start_once=true;
			}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return NULL;
	}
}

VOID PaintMain()
{
	hDC=GetDC(ObjMyHandles.hWndMain);
	//TextOut(hDC, 20, 40, "MicroPaint", strlen("MicroPaint"));
	{
		//draw frame
		Line(hDC, 0, 0, WIDTH_OF_WINDOW-1, 0);
		Line(hDC, WIDTH_OF_WINDOW-1, 0, WIDTH_OF_WINDOW-1, HEIGHT_OF_WINDOW-1);
		Line(hDC, WIDTH_OF_WINDOW-1, HEIGHT_OF_WINDOW-1, 0, HEIGHT_OF_WINDOW-1);
		Line(hDC, 0, HEIGHT_OF_WINDOW-1, 0, 0);
		MoveToEx(hDC, 0, 0, NULL);
	}

	//draw button options
	{
		btnrect.top=5; btnrect.left=810; btnrect.bottom=25; btnrect.right=855;
		ObjMyWindow->DrawButton(hDC, &btnrect, COLOUR_BTN_BLUE);
		PrintText(hDC, "OPT", &btnrect, "Lucida Handwriting", -16, COLOUR_WHITE);
	}

	//draw button minimise
	{
		btnrect.top=5; btnrect.left=860; btnrect.bottom=25; btnrect.right=905;
		ObjMyWindow->DrawButton(hDC, &btnrect, COLOUR_BTN_BLUE);
		HGDIOBJ hPen=CreatePen(PS_SOLID, 1, COLOUR_WHITE);
		HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
		SelectObject(hDC, hPen);
		Line(hDC, btnrect.left+17, btnrect.top+14, btnrect.left+28, btnrect.top+14);
		Line(hDC, btnrect.right-28, btnrect.bottom-5, btnrect.right-17, btnrect.bottom-5);
		SelectObject(hDC, hOldPen);
		DeleteObject(hPen);
	}

	//draw button close
	{
		btnrect.top=5; btnrect.left=910; btnrect.bottom=25; btnrect.right=955;
		ObjMyWindow->DrawButton(hDC, &btnrect, COLOUR_BTN_RED);
		PrintText(hDC, "X", &btnrect, "Lucida Handwriting", -16, COLOUR_WHITE);
	}

	//draw button clear, save, load
	{
		ObjMyWindow->DrawRoundButton(30, 360, L"clear", false);
		ObjMyWindow->DrawRoundButton(30, 420, L"save", false);
		ObjMyWindow->DrawRoundButton(30, 480, L"load", false);
	}

	//print title
	{
		RECT titlerect;
		titlerect.top=10; titlerect.left=400; titlerect.bottom=25; titlerect.right=550;
		PrintText(hDC, "MicroPaint", &titlerect, "Lucida Handwriting", -20, COLOUR_BACKGROUND);//writing text, background color - bad variant fixing bug :)
		PrintText(hDC, "MicroPaint", &titlerect, "Lucida Handwriting", -20, COLOUR_WHITE);//write text, white color
	}

	HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
	HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
	HBRUSH hBrush;
	HPEN hPen=CreatePen(PS_SOLID, 1, COLOUR_WHITE);
	SelectObject(hDC, hPen);
	
	//draw buttons of the colors
	for (int i(0); i<20; ++i) {
		hBrush=CreateSolidBrush(ARR_COLOUR_BTN[i]); SelectObject(hDC, hBrush);
		Rectangle(hDC,
			ARR_COLOUR_BTN_POS[i].left,
			ARR_COLOUR_BTN_POS[i].top,
			ARR_COLOUR_BTN_POS[i].right,
			ARR_COLOUR_BTN_POS[i].bottom
		);

		//draw active color
		if (rgb.active_color==ARR_COLOUR_BTN[i]) {
			RECT _rect = {ARR_COLOUR_BTN_POS[i].left, ARR_COLOUR_BTN_POS[i].top, ARR_COLOUR_BTN_POS[i].right, ARR_COLOUR_BTN_POS[i].bottom};
			if ((rgb.r==255)&&(rgb.g==255)&&(rgb.b==255))
				PrintText(hDC, "X", &_rect, "Lucida Handwriting", -16, COLOUR_BLACK);
			else
				PrintText(hDC, "X", &_rect, "Lucida Handwriting", -16, COLOUR_WHITE);
		}

		DeleteObject(hBrush);
	}

	//set default
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	//removing objects from memory
	DeleteObject(hPen);

	ReleaseDC(ObjMyHandles.hWndMain, hDC);//exempt DC
	return;
}

VOID PaintOptions()
{
	hDC=GetDC(ObjMyHandles.hWndOptions);
	{
		//draw frame
		Line(hDC, 0, 0, 0, HEIGHT_OF_OPTWINDOW);
		Line(hDC, WIDTH_OF_WINDOW-1, 0, WIDTH_OF_WINDOW-1, HEIGHT_OF_OPTWINDOW-1);
		Line(hDC, WIDTH_OF_WINDOW-1, HEIGHT_OF_OPTWINDOW-1, 0, HEIGHT_OF_OPTWINDOW-1);
		MoveToEx(hDC, 0, 0, NULL);
	}
	ObjMyWindow->DrawSlider(150, 5, 450, 25, false);
	ObjMyWindow->DrawAlphaButton(680, 5, false);
	ObjMyWindow->DrawChoiceButton(560, 5, false);

	ReleaseDC(ObjMyHandles.hWndOptions, hDC);//exempt DC
	return;
}

VOID MicroPaint::MyWindow::OnDrawLine(HDC &hDC, int posX, int posY, int postoX, int postoY)
{
	Graphics graphics(hDC);
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	Pen pen(Color(255, rgb.r, rgb.g, rgb.b), optSize*1.5f);
	if (optChoice==1)
		;
	else {
		pen.SetColor(Color(2.55f*optAlpha, rgb.r, rgb.g, rgb.b));
		pen.SetWidth(1);
	}
	pen.SetStartCap(LineCap::LineCapRound);
	pen.SetEndCap(LineCap::LineCapRound);
	graphics.DrawLine(&pen, posX, posY, postoX, postoY);
}

VOID MicroPaint::MyWindow::DrawBitmap(HDC hDC, HBITMAP hBitmap, int x, int y)
{
	BITMAP bm;
	HDC hMemDC;
	DWORD dwSize;
	POINT ptSize, ptOrg;
	hMemDC=CreateCompatibleDC(hDC);
	SelectObject(hMemDC, hBitmap);
	SetMapMode(hMemDC, GetMapMode(hDC));
	GetObject(hBitmap, sizeof(BITMAP),(LPVOID) &bm);
	ptSize.x=bm.bmWidth;
	ptSize.y=bm.bmHeight;
	DPtoLP(hDC, &ptSize, 1);
	ptOrg.x=0;
	ptOrg.y=0;
	DPtoLP(hMemDC, &ptOrg, 1);
	BitBlt(hDC, x, y, ptSize.x, ptSize.y, hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);
	DeleteDC(hMemDC);
	return;
}

void MicroPaint::MyWindow::On_clear_function()
{
	hDC=GetDC(ObjMyHandles.hWndFieldDrawing);
	HGDIOBJ hOldPen=(HPEN)SelectObject(hDC, GetStockObject(DC_PEN));
	HGDIOBJ hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(DC_BRUSH));
	HPEN hPenBackground=CreatePen(PS_SOLID, 1, COLOUR_WHITE);
	HBRUSH hBrushBackground(CreateSolidBrush(COLOUR_WHITE));
	SelectObject(hDC, hPenBackground); SelectObject(hDC, hBrushBackground);
	Rectangle(hDC, 0, 0, WIDTH_OF_WINDOW-120, HEIGHT_OF_WINDOW-60);

	//set default
	SelectObject(hDC, hOldPen); SelectObject(hDC, hOldBrush);
	//removing objects from memory
	DeleteObject(hPenBackground);
	DeleteObject(hBrushBackground);
	ReleaseDC(ObjMyHandles.hWndFieldDrawing, hDC);
	return;
}

void MicroPaint::MyWindow::On_load_function()
{
	hDC=GetDC(ObjMyHandles.hWndFieldDrawing);
	ObjMyWindow->DrawBitmap(hDC, ObjMyWindow->hMemBitmap, 0, 0);
	ReleaseDC(ObjMyHandles.hWndFieldDrawing, hDC);
	return;
}

void MicroPaint::MyWindow::On_save_function()
{
	hDC=GetDC(ObjMyHandles.hWndFieldDrawing);
	hMemDC=CreateCompatibleDC(hDC);
	ObjMyWindow->hMemBitmap=CreateCompatibleBitmap(hDC, WIDTH_OF_WINDOW-120, HEIGHT_OF_WINDOW-60);
	SelectObject(hMemDC, ObjMyWindow->hMemBitmap);
	BitBlt(hMemDC, 0, 0, WIDTH_OF_WINDOW-120, HEIGHT_OF_WINDOW-60, hDC, 0, 0, 0xE20746L);
	DeleteDC(hMemDC);
	ReleaseDC(ObjMyHandles.hWndFieldDrawing, hDC);
	return;
}

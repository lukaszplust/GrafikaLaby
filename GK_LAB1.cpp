/******************************************************************
 Grafika komputerowa, �rodowisko MS Windows - program  przyk�adowy
 *****************************************************************/

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;


//litera B
void poligon1(HDC kontekst, int x, int y) {
	
	 COLORREF red(0x00000011);

    HBRUSH pioro1 = CreateSolidBrush(RGB(255, 0, 0)); 
    HBRUSH pioro2 = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH pioro3 = CreateSolidBrush(RGB(0, 0, 255));
    HBRUSH pioro4 = CreateSolidBrush(RGB(0, 255, 255));
    HBRUSH pioro5 = CreateSolidBrush(RGB(255, 255, 0));
	SelectObject(kontekst, pioro1);
	Pie(kontekst, -100 + x, -100 + y, 100 + x, 100 + y, 100 + x, -100 + y, -200 + x, 200 + y);
	DeleteObject(pioro1);

	SelectObject(kontekst, pioro2);
	Pie(kontekst, -100 + x, -100 + y, 100 + x, 100 + y, -200 + x, 100 + y, 100 + x, -120 + y);
	DeleteObject(pioro2);

	SelectObject(kontekst, pioro3);
	Pie(kontekst, -100 + x, -100 + y, 100 + x, 100 + y, -80 + x, 100 + y, 100 + x, -50 + y);
	DeleteObject(pioro3);

	SelectObject(kontekst, pioro5);
	Pie(kontekst, -100 + x, -100 + y, 100 + x, 100 + y, -240 + x, 120 + y, -200 + x, 270 + y);
	DeleteObject(pioro5);

    SelectObject(kontekst, pioro4);
	POINT rofl[6] = { {x - 50,y - 60 }, {40 + x - 50, y - 60},{60 + x - 50,20 + y - 60},{60 + x - 50,40 + y - 60},{40 + x - 50,60 + y - 60},{x - 50,60 + y - 60} };
	POINT rofl2[6] = { {x - 50,y }, {40 + x - 50, y },{60 + x - 50,20 + y},{60 + x - 50,40 + y },{40 + x - 50,60 + y},{x - 50,60 + y } };

	Polygon(kontekst, rofl, 6);

	SelectObject(kontekst, pioro3);
	Polygon(kontekst, rofl2, 6);
   



}


//deklaracja funkcji obslugi okna
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//funkcja Main - dla Windows
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG meldunek;		  //innymi slowy "komunikat"
	WNDCLASS nasza_klasa; //klasa g��wnego okna aplikacji
	HWND okno;
	static char nazwa_klasy[] = "Podstawowa";

	GdiplusStartupInput gdiplusParametry;// parametry GDI+; domy�lny konstruktor wype�nia struktur� odpowiednimi warto�ciami
	ULONG_PTR	gdiplusToken;			// tzw. token GDI+; warto�� uzyskiwana przy inicjowaniu i przekazywana do funkcji GdiplusShutdown

	// Inicjujemy GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusParametry, NULL);

	//Definiujemy klase g��wnego okna aplikacji
	//Okreslamy tu wlasciwosci okna, szczegoly wygladu oraz
	//adres funkcji przetwarzajacej komunikaty
	nasza_klasa.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	nasza_klasa.lpfnWndProc = WndProc; //adres funkcji realizuj�cej przetwarzanie meldunk�w 
	nasza_klasa.cbClsExtra = 0;
	nasza_klasa.cbWndExtra = 0;
	nasza_klasa.hInstance = hInstance; //identyfikator procesu przekazany przez MS Windows podczas uruchamiania programu
	nasza_klasa.hIcon = 0;
	nasza_klasa.hCursor = LoadCursor(0, IDC_ARROW);
	nasza_klasa.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	nasza_klasa.lpszMenuName = "Menu";
	nasza_klasa.lpszClassName = nazwa_klasy;

	//teraz rejestrujemy klas� okna g��wnego
	RegisterClass(&nasza_klasa);

	/*tworzymy okno g��wne
	okno b�dzie mia�o zmienne rozmiary, listw� z tytu�em, menu systemowym
	i przyciskami do zwijania do ikony i rozwijania na ca�y ekran, po utworzeniu
	b�dzie widoczne na ekranie */
	okno = CreateWindow(nazwa_klasy, "Grafika komputerowa", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);


	/* wyb�r rozmiaru i usytuowania okna pozostawiamy systemowi MS Windows */
	ShowWindow(okno, nCmdShow);

	//odswiezamy zawartosc okna
	UpdateWindow(okno);

	// G��WNA P�TLA PROGRAMU
	while (GetMessage(&meldunek, NULL, 0, 0))
		/* pobranie komunikatu z kolejki; funkcja GetMessage zwraca FALSE tylko dla
		komunikatu WM_QUIT; dla wszystkich pozosta�ych komunikat�w zwraca warto�� TRUE */
	{
		TranslateMessage(&meldunek); // wst�pna obr�bka komunikatu
		DispatchMessage(&meldunek);  // przekazanie komunikatu w�a�ciwemu adresatowi (czyli funkcji obslugujacej odpowiednie okno)
	}

	GdiplusShutdown(gdiplusToken);

	return (int)meldunek.wParam;
}

/********************************************************************
FUNKCJA OKNA realizujaca przetwarzanie meldunk�w kierowanych do okna aplikacji*/
LRESULT CALLBACK WndProc(HWND okno, UINT kod_meldunku, WPARAM wParam, LPARAM lParam)
{
	HMENU mPlik, mInfo, mGlowne;

	/* PONI�SZA INSTRUKCJA DEFINIUJE REAKCJE APLIKACJI NA POSZCZEG�LNE MELDUNKI */
	switch (kod_meldunku)
	{
	case WM_CREATE:  //meldunek wysy�any w momencie tworzenia okna
		mPlik = CreateMenu();
		AppendMenu(mPlik, MF_STRING, 100, "&Zapiszcz...");
		AppendMenu(mPlik, MF_SEPARATOR, 0, "");
		AppendMenu(mPlik, MF_STRING, 101, "&Koniec");
		mInfo = CreateMenu();
		AppendMenu(mInfo, MF_STRING, 200, "&Autor...");
		mGlowne = CreateMenu();
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR)mPlik, "&Plik");
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR)mInfo, "&Informacja");
		SetMenu(okno, mGlowne);
		DrawMenuBar(okno);

	case WM_COMMAND: //reakcje na wyb�r opcji z menu
		switch (wParam)
		{
		case 100: if (MessageBox(okno, "Zapiszcze�?", "Pisk", MB_YESNO) == IDYES)
			MessageBeep(0);
			break;
		case 101: DestroyWindow(okno); //wysylamy meldunek WM_DESTROY
			break;
		case 200: MessageBox(okno, "Imi� i nazwisko:\nNumer indeksu: ", "Autor", MB_OK);
		}
		return 0;

	case WM_LBUTTONDOWN: //reakcja na lewy przycisk myszki
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		return 0;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT paint;
		HDC kontekst;

		kontekst = BeginPaint(okno, &paint);

		// MIEJSCE NA KOD GDI




		//MoveToEx(kontekst, 100, 300, NULL);
		//LineTo(kontekst, 800, 300);
		poligon1(kontekst, 200, 200);



		// utworzenie obiektu umo�liwiaj�cego rysowanie przy u�yciu GDI+
		// (od tego momentu nie mo�na u�ywa� funkcji GDI
		Graphics grafika(kontekst);

		// MIEJSCE NA KOD GDI+


		// utworzenie czcionki i wypisanie tekstu na ekranie
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
		PointF      pointF(100.0f, 400.0f);
		SolidBrush  solidBrush(Color(255, 0, 0, 255));

		grafika.DrawString(L"To jest tekst napisany za pomoc� GDI+.", -1, &font, pointF, &solidBrush);

		EndPaint(okno, &paint);

		return 0;
	}

	case WM_DESTROY: //obowi�zkowa obs�uga meldunku o zamkni�ciu okna
		PostQuitMessage(0);
		return 0;

	default: //standardowa obs�uga pozosta�ych meldunk�w
		return DefWindowProc(okno, kod_meldunku, wParam, lParam);
	}
}

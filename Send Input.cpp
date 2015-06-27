
// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h> //needed to play a sound using windows also need to insert winmm.lib
					  //C:\Program Files\Microsoft Visual Studio\VC98\Lib
#include <Winuser.h> //needed to send keyboard input, also need user32.lib

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME "WINCLASS1"  // class name
#define WINDOW_WIDTH  320              // size of window
#define WINDOW_HEIGHT 200

// PROTOTYPES /////////////////////////////////////////////
void Test(int);
void TestKBPressed(int &);


// GLOBALS ////////////////////////////////////////////////

HWND main_window_handle = NULL; // save the window handle
HINSTANCE main_instance = NULL; // save the instance
char buffer[300]; 

// FUNCTIONS //////////////////////////////////////////////

//\\\\\\\\\\\\\\\\\\\\\\\\\ WinProc ///////////////////////////////

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT	ps;		   // used in WM_PAINT
	HDC			hdc;	   //creates a handle to the device context

	//find out what the message is
	switch(msg)
	{	
	
	case WM_CREATE: //called when window is created
		{// do initialization stuff here
			return(0);
		} break;

	case WM_PAINT: //called when window needs repainting
		{//simply validate the window
		    
			//ValidateRect(hwnd, NULL);
			hdc = BeginPaint(hwnd,&ps);
		    EndPaint(hwnd,&ps);
			
			return(0);
		} break;
	
	
	case WM_KEYDOWN:
		{
			int virtual_code= (int)wparam;
			int key_bits= (int)lparam;
			
			hdc=GetDC(hwnd);
			SetBkMode(hdc, TRANSPARENT); //set background color
			SetTextColor(hdc,RGB(0,0,255)); //set text color
			TextOut(hdc,100,100,"hi",strlen("hi")); //print text
			ReleaseDC(hwnd, hdc);

			return(0);
		}
	case WM_CHAR :
		{
			char ascii_code= (char)wparam;
			
			switch(ascii_code)
			{
			}
			
			return(0);
		}
	case WM_DESTROY: 
		{// kill the application			
			//close the program
			PostQuitMessage(0);
			return(0);
		} break;

	default:break;

    } // end main switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc


//\\\\\\\\\\\\\\\\\\\\\\\\ WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{

	WNDCLASS winclass;	// this will hold the class created
	HWND	 hwnd;		// generic window handle
	MSG		 msg;		// generic message
	MSG      msg2;
	HDC		 hdc;
	int count=0;

	//fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName	= WINDOW_CLASS_NAME;

	// register the window class
	if (!RegisterClass(&winclass))
		return(0);

	// create the window
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, // class
							  "Key stuff",	 // title
							  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						 	  0,0,	   // x,y
							  WINDOW_WIDTH,  // width
						      WINDOW_HEIGHT, // height
							  NULL,	   // handle to parent 
							  NULL,	   // handle to menu
							  hinstance,// instance
							  NULL)))	// creation parms
	{
		MessageBox(hwnd, "Window Could not be Created", NULL, MB_OK); //NULL is default for Error
		return(0);
	}

	// save the window handle and instance in a global
	main_window_handle = hwnd;
	main_instance      = hinstance;
	
	strcpy(buffer, " ");
	
	// enter main event loop
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit message
			if (msg.message == WM_QUIT)
				break;
	
			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		
				
		hdc=GetDC(hwnd);
		/*
		SetBkMode(hdc, TRANSPARENT); //set background color
		SetTextColor(hdc,RGB(0,0,0)); //set text color
		TextOut(hdc,100,100,buffer,strlen(buffer)); //print text
		
		sprintf(buffer,"return value= %d", GetAsyncKeyState(0x42) );
		SetTextColor(hdc,RGB(0,0,255)); //set text color
		TextOut(hdc,100,100,buffer,strlen(buffer)); //print text
		*/

		ReleaseDC(hwnd, hdc);
		
		//SetForegroundWindow(hwnd);
		//SetFocus(hwnd);

		//TestKBPressed(count);
		//IAmGay(count);
		
		if(count >= 8)
			count=0;

		
	} // end while

	

	// return to Windows like this
	return(msg.wParam);

} // end WinMain


void Test(int count)
{
	
	//keybd_event(0x08, 0x08, NULL, NULL);//back space
	
		
	
	return;
}

void TestKBPressed(int & count)
{
	//GetAsyncKeyState(0x41)
	
	
	return;
}
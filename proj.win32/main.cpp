#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed);

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	// create the application instance
	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(704, 469);
	//eglView->setWndProc(myWndProcHook); //增加这一句
	int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
	FreeConsole();
#endif

	return ret;
}

/* LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
	switch ( message )
	{
	case WM_LBUTTONDOWN:
		{
			CCEGLView* eglView = CCEGLView::sharedOpenGLView();
		
			CCSize originalDesignResolutionSize = CCSizeMake(480, 320);     //原始的设计分辨率大小
			CCSize obDesignResolutionSize = eglView->getDesignResolutionSize();
			int offsetWidth = obDesignResolutionSize.width - originalDesignResolutionSize.width;
			int offsetheight = obDesignResolutionSize.height - originalDesignResolutionSize.height;
			CCSize obScreenSize = eglView->getFrameSize();
			int offsetWidth2 = obScreenSize.width - originalDesignResolutionSize.width;
			int offsetheight2 = obScreenSize.height - originalDesignResolutionSize.height;

			CCPoint pt = CCPointZero;

			pt.x *= eglView->getScaleX();
			pt.y *= eglView->getScaleY();

			int id = wParam;

			eglView->handleTouchesBegin(1, &id, &pt.x, &pt.y);
			
			*pProcessed = TRUE;
		}
		break;
	case WM_LBUTTONUP:
		{
			CCEGLView* eglView = CCEGLView::sharedOpenGLView();

			CCSize originalDesignResolutionSize = CCSizeMake(480, 320);     //原始的设计分辨率大小
			CCSize obDesignResolutionSize = eglView->getDesignResolutionSize();
			int offsetWidth = obDesignResolutionSize.width - originalDesignResolutionSize.width;
			int offsetheight = obDesignResolutionSize.height - originalDesignResolutionSize.height;
			CCSize obScreenSize = eglView->getFrameSize();
			int offsetWidth2 = obScreenSize.width - originalDesignResolutionSize.width;
			int offsetheight2 = obScreenSize.height - originalDesignResolutionSize.height;

			CCPoint pt = CCPointZero;

			pt.x *= eglView->getScaleX();
			pt.y *= eglView->getScaleY();

			int id = wParam;

			eglView->handleTouchesEnd(1, &id, &pt.x, &pt.y);
			*pProcessed = TRUE;
		}
		break;
	}
	return 0;
}*/
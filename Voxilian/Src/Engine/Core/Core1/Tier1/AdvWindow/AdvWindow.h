#ifndef H_ADVWINDOW
#define H_ADVWINDOW
#include "..\..\..\Core0\Core0.h"

class CAdvWindow : public CWindow
{
public:
	//Is visible on screen.
	bool visible;
	//Has border inside frame.
	bool borderable;
	//Can close with X button. REQUIRES: BORDER.
	bool closeable;
	//Can move/resize with borders. REQUIRES: BORDER.
	bool modable;
	//Note on scrollbars: Left click to drag mover which moves scroll position by moved amount. Right click to drag bar which scrolls to bar position.
	//Can scroll horizontally. REQUIRES: BORDER.
	bool scrollxable;
	//Can scroll vertically. REQUIRES: BORDER.
	bool scrollyable;
	//Scrollbar are the same texture, size, etc...
	bool scrollsame;
	//The border width.
	float borderwidth;
	//The x/y scrollbar width, scrolling position, scrolling min, scrolling max, and mover speed multiplier.
	float scrollxbarwidth;
	float scrollxbarpos;
	float scrollxbarposmin;
	float scrollxbarposmax;
	float scrollxmoverspeedmult;
	float scrollybarwidth;
	float scrollybarpos;
	float scrollybarposmin;
	float scrollybarposmax;
	float scrollymoverspeedmult;
	//Textures for all of the intrawindows.
	int bordertexture;
	int closetexture;
	int scrollxbartexture;
	int scrollxmovertexture;
	int scrollybartexture;
	int scrollymovertexture;
	//The windows themselves. And a button.
	CWindow* borderleft;
	CWindow* borderup;
	CWindow* borderright;
	CWindow* borderdown;
	CButton* closebutton;
	CWindow* scrollxbarback;
	CWindow* scrollxbarbar;
	CWindow* scrollxbarmover;
	CWindow* scrollybarback;
	CWindow* scrollybarbar;
	CWindow* scrollybarmover;
	CAdvWindow();
	void Init(string bordertex);
	void Init(string bordertex,bool canmod);
	void Init(string bordertex,bool canclose,string closetex);
	void Init(string bordertex,bool canmod,bool canclose,string closetex);
	void Init(string bordertex,bool canmod,bool canclose,string closetex,bool hasscrolls,string scrollbartex,string scrollmovertex);
	virtual void Run();
	virtual void Draw();
};

#endif
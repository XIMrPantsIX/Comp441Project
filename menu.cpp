#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
}

Menu::Menu(vector<string> v, D3DXVECTOR2 loc)
{
	
	menuItems = v;
	menuHeading = menuItems[menuItems.size()-1];
	menuItems.pop_back();
	menuAnchor = loc;
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
}

void Menu::initialize(Graphics *g, Input *i)
{
	eggsOn = false;
	size = menuItems.size();
	highlightColor = graphicsNS::WHITE;
	normalColor = graphicsNS::RED;
	input = i;
	horizontalOffset = 250;
	verticalOffset = 100;
	linePtr = 0;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 50, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 50, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 80, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
	for(int i = 0; i < 255; i+=1)
	{
		keys_Pressed[i] = false;
	}
}

void Menu::update(int &gameState)
{
	if (input->isKeyDown(0x44) && !keys_Pressed[0x44])
	{
		linePtr++;
		keys_Pressed[0x44] = true;
	}
	if (input->isKeyDown(0x41) && !keys_Pressed[0x41])
	{
		linePtr--;
		keys_Pressed[0x41] = true;
	}
	if(!input->isKeyDown(0x44))
		keys_Pressed[0x44] = false;
	if(!input->isKeyDown(0x41))
		keys_Pressed[0x41] = false;
	if (linePtr > size-1) linePtr = 0;
	if (linePtr < 0) linePtr = size-1;

	if(input->isKeyDown(VK_RETURN) && !keys_Pressed[VK_RETURN])
	{
		keys_Pressed[VK_RETURN] = true;
		selectedItem = linePtr;
		if(selectedItem == 0) {
			if(menuItems[1] == "CHEATS ON") {
				eggsOn = true;
			}
			gameState = 1;
			return;
		}
		if(linePtr == 1) {
			if(menuItems[1]=="CHEATS ON") {
				menuItems[1] = "CHEATS OFF";
			}
			else {
				menuItems[1] = "CHEATS ON";
			}
			return;
		}
		if(selectedItem == size-1) {
			PostQuitMessage(0);
		}	
	}
	if(!input->isKeyDown(VK_RETURN))
	{
		keys_Pressed[VK_RETURN] = false;
	}
}

void Menu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x-100, menuAnchor.y);
	double vOff = verticalOffset;
	double hOff = horizontalOffset;
	for(int i=0;i<menuItems.size();i++) {
		
		if(linePtr==i)
			menuItemFontHighlight->print(menuItems[i], menuAnchor.x+hOff-600, menuAnchor.y+vOff);
		else
			menuItemFont->print(menuItems[i], menuAnchor.x+hOff-600, menuAnchor.y+vOff);
		hOff += horizontalOffset;
	}

}
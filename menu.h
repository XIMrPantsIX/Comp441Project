#define WIN32_LEAN_AND_MEAN
#ifndef MENU_H                 // Prevent multiple definitions if this 
#define MENU_H 

class Menu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include "input.h"
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::stringstream;
namespace menuNS
{
}

// inherits from Entity class
class Menu 
{
private:
   TextDX *menuItemFont;
   TextDX *menuItemFontHighlight;
   TextDX *menuHeadingFont;
   Input   *input;         // pointer to the input system
   Graphics *graphics;
   int selectedItem;
   int size;
   vector<string> menuItems;
   string menuHeading;
   D3DXVECTOR2 menuAnchor;
   int horizontalOffset;
   int verticalOffset;
   int linePtr;
   bool eggsOn;
   COLOR_ARGB highlightColor;
   COLOR_ARGB normalColor;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;

public:
    // constructor
    Menu();
	Menu(vector<string> v, D3DXVECTOR2 loc);
	void initialize(Graphics *g, Input *i);
	void update(int &gameState);
	int getSelectedItem() {return selectedItem;}
	void displayMenu();
	bool keys_Pressed[255];
	bool getKeysPressed(int i) {return keys_Pressed[i];}
	bool getEggsOn() {return eggsOn;}
};
#endif
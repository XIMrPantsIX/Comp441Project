#include "Anax.h"

void Anax::dialogChecker(){
	displayCoordinates();
	//switch(static_cast<int>(world_coordinates)){

	//case 400:
	//	turnDialogOn();
	//	dialogIn = "...congrats. You totally passed \n a cattail. \n Press Enter to Continue";
	//	break;
	//case 2111:
	//	turnDialogOn();
	//	dialogIn = "You stand on a Mountain.\n The peace is glorious. \n Now Let's go fight zombies. \n Press Enter to Continue";
	//	break;
	//}
}
void Anax::turnDialogOn(){
		isDialogOn = true;
		isRunningGame = false;
		moveScreen = false;
		dudeManBro.walk(middle);
		dudeManBro.setX(dudeManBro.getX()+1);
		world_coordinates+=1;

}
void Anax::setGameState(int i)
{
	gameState = i;
}


/*****************************************************************************************************
// Anax coordinate display
// output display to font.
*****************************************************************************************************/
void Anax::displayCoordinates(){
	std::stringstream s;
	s << world_coordinates;
	in.assign(s.str());

}

/*****************************************************************************************************
// Anax render helpers
// Simplifies render function by adding functions for draw sprite switches 
*****************************************************************************************************/
void Anax::drawHealth()
{
	switch(dudeManBro.getHealth())
	{
	case 0:
		emptyHeart.draw();
		emptyHeart2.draw();
		emptyHeart3.draw();
		break;
	case 1:
		halfHeart.draw();
		emptyHeart2.draw();
		emptyHeart3.draw();
		break;
	case 2:
		heart.draw();
		emptyHeart2.draw();
		emptyHeart3.draw();
		break;
	case 3:
		heart.draw();
		halfHeart2.draw();
		emptyHeart3.draw();
		break;
	case 4:
		heart.draw();
		heart2.draw();
		emptyHeart3.draw();
		break;
	case 5:
		heart.draw();
		heart2.draw();
		halfHeart3.draw();
		break;
	case 6:
		heart.draw();
		heart2.draw();
		heart3.draw();
		break;
	default:
		emptyHeart.draw();
		halfHeart2.draw();
		heart3.draw();
	}
}


/*****************************************************************************************************
// Anax tile position (x,y) placers
// Functions return values which coorespond to world coordinates
*****************************************************************************************************/
float Anax::tilePositionPlacerX(int i){
	switch(i){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4: 
		case 5:
		case 6: 
		case 7:
		case 8:
		case 9:
		default: return tile1[i].getScaledWidth() * i - world_coordinates;
	}
}
float Anax::tilePositionPlacerY(int i){
	switch(i){
	case 0:
		return GAME_HEIGHT - 100;
	case 1:
		return GAME_HEIGHT - 150;
	case 2:
		return GAME_HEIGHT - 200;
	case 3:
		return GAME_HEIGHT - 250;
	case 4:
		return GAME_HEIGHT - 300;
	case 5:
		return GAME_HEIGHT - 350;
	default: 
		return GAME_HEIGHT -600;
	}
}


#include "stdafx.h"

#include "Scroll.h"
#include <iostream>

using namespace std;

enum ScrollType : int { teleporation, improveArmor, raiseStrength, enhanceHealth, enhanceDexterity };
string scrollName[5] = { "scroll of teleportation", "scroll of improved armor", "scroll of raise strength", "scroll of enhance health", "scroll of enhance dexterity" };

Scroll::Scroll(Coord c, int sType) : GameObject(c, scrollName[sType]){
	type = sType;
}

//Corresponding action when used by actors
std::string Scroll::action(){
	switch (type){
	case teleporation:
		return "You feel your body wrenched in space and time.";
	case improveArmor:
		return "Your armor glows sliver.";
	case raiseStrength:
		return "Your muscles bulge.";
	case enhanceHealth:
		return "You fell your heart beating stronger.";
	case enhanceDexterity:
		return "You feel like less of a klutz.";
	default:
		return "";
	}
}
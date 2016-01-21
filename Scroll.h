#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "GameObject.h"

class Scroll : public GameObject{
public:
	Scroll(Coord c, int sType);
	virtual ~Scroll(){}
	std::string action();
	int getScrollType();

private:
	int type;
};

inline
int Scroll::getScrollType(){
	return type;
}

#endif
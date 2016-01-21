#ifndef _COORD_H_
#define _COORD_H_

class Coord{
public:
	Coord();
	Coord(int newX, int newY);
	Coord(const Coord &c);
	~Coord(){}
	bool operator==(const Coord& rhs);
	bool operator!=(const Coord& rhs);

	int x;
	int y;
};

inline
Coord::Coord():x(0),y(0){
}

inline
Coord::Coord(int newX, int newY) : x(newX), y(newY){
}

inline
Coord::Coord(const Coord &c) : x(c.x), y(c.y){
}

inline
bool Coord::operator==(const Coord& rhs){
	return (x == rhs.x && y == rhs.y);
}

inline
bool Coord::operator!=(const Coord& rhs){
	return (x != rhs.x || y != rhs.y);
}

#endif
#ifndef PLAYBOOKHANDLER_H
#define PLAYBOOKHANDLER_H

#include <vector>
#include "../../imgui/imgui.h"


// class definition for a strat.
// This will basically hold everything associated
// to a preplanned strat for any given round. This
// will include player positions, player paths that
// are drawn on the map, smoke, flashes, molotovs, 
// and HE grenades. Everything associated to the attack
// for the round - or defense - will be stored in this
// object

class Strat
{
public:

private:
	// There is going to be an array of points
	int size;
};



// This class is essentially the "book" of plays
// It will hold a vector of plays associated to
// each map.

class PlayBookHandler
{
public:
private:
	std::vector<Strat> stratLibrary;
};


#endif // PLAYBOOKHANDLER_H

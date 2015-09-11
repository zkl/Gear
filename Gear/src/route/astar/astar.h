#ifndef ASTAR_H
#define ASTAR_H

#include <map>
#include <vector>

class AStar
{
public:
	AStar(int w, int h);

	void setStart(int x, int y);
	void setStop (int x, int y);
	bool find(std::vector<int, int>& path);

private:
	struct AStarPoint
	{
		int position; // position = x*width +y;
	};

	int width;
	int height;
	std::map<int, AStarPoint> _opened;
	std::map<int, AStarPoint> _closeed;
};

#endif

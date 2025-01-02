// BoatPath.h
#ifndef BOAT_PATH_H
#define BOAT_PATH_H

#include "Path.h"
#include "TerrainMap.h"


class BoatPath : public Path {
public:
    BoatPath(TerrainMap& map, std::string name, Point start, Point finish);
    bool find() override;

private:
    struct Node {
        Point pos;
        double distance;
        bool operator>(const Node& other) const { 
            return distance > other.distance; 
        }
    };
    
    bool isValidWaterPoint(const Point& p) const;
    std::vector<Point> getNeighbors(const Point& p) const;
};

#endif
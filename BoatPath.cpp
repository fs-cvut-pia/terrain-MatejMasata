#include "BoatPath.h"
#include <algorithm>
#include <limits>
#include <queue>

BoatPath::BoatPath(TerrainMap& map, std::string name, Point start, Point finish) 
    : Path(map, name, start, finish) {}

bool BoatPath::isValidWaterPoint(const Point& p) const {
    if (p == start || p == finish) return true;
    return map.validCoords(p) && map.alt(p) < 0;
}

std::vector<Point> BoatPath::getNeighbors(const Point& p) const {
    std::vector<Point> neighbors;
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            if(dx == 0 && dy == 0) continue;
            Point newPoint = {p.x + dx, p.y + dy};
            if(map.validCoords(newPoint) && isValidWaterPoint(newPoint)) {
                neighbors.push_back(newPoint);
            }
        }
    }
    return neighbors;
}

bool BoatPath::find() {
    Matrix<double> distances(map.nx, map.ny);
    for(int i = 0; i < map.nx; i++) {
        for(int j = 0; j < map.ny; j++) {
            distances(i,j) = std::numeric_limits<double>::infinity();
        }
    }
    Matrix<Point> previous(map.nx, map.ny);
    
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    
    distances(start.x, start.y) = 0;
    pq.push({start, 0});
    
    while(!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        if(current.pos == finish) {
            path.clear();
            Point current_pos = finish;
            while(current_pos != start) {
                path.push_back(current_pos);
                current_pos = previous(current_pos.x, current_pos.y);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return true;
        }
        
        if(current.distance > distances(current.pos.x, current.pos.y)) {
            continue;
        }
        
        for(const Point& neighbor : getNeighbors(current.pos)) {
            double step_length = (current.pos - neighbor).length();
            double new_distance = current.distance + step_length;
            
            if(new_distance < distances(neighbor.x, neighbor.y)) {
                distances(neighbor.x, neighbor.y) = new_distance;
                previous(neighbor.x, neighbor.y) = current.pos;
                pq.push({neighbor, new_distance});
            }
        }
    }
    
    return false;
}
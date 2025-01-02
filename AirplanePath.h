#ifndef AIRPLANE_PATH_H
#define AIRPLANE_PATH_H

#include "Path.h"

class AirplanePath : public Path {
public:
    AirplanePath(TerrainMap& map, std::string name, Point start, Point finish) 
        : Path(map, name, start, finish) {}

    bool find() override;
};

#endif // AIRPLANE_PATH_H
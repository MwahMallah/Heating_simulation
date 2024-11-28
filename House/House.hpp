#ifndef __HOUSE_HPP
#define __HOUSE_HPP

#include "../Room/Room.hpp"
#include <vector>

class House {
    std::vector<Room> _rooms;
public:
    double GetHeatLoss(double outsideTemp);
    void SetDefaultRooms();
};

#endif

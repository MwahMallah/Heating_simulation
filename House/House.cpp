#include "House.hpp"
#include "../RoomFactory/RoomFactory.hpp"

#include <iostream>

void House::SetDefaultRooms() {
    _rooms.push_back(createDefaultHallway());
    _rooms.push_back(createDefaultBedroom());
    _rooms.push_back(createDefaultKitchen());
    _rooms.push_back(createDefaultBathroom());
    _rooms.push_back(createDefaultLivingRoom());
} 

double House::GetHeatLoss(double outTmp) {
    double totalLoss = 0;

    for (auto& room : _rooms) {
        totalLoss += room.GetHeatLoss(outTmp);
    }  

    return totalLoss;
}
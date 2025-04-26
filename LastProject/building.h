#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <vector>

//方向
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

//资源
class resource {
public:
    int value;
    bool isCuttable;
    bool isCut;
    resource();




};

//可切割资源
class CuttableResource : public resource {
public:
    CuttableResource();
};

//不可切割资源
class UncuttableResource : public resource {
public:
    UncuttableResource();
};

//设备
class Device {
protected:
    //功率，可供升级
    int rate;
    //方向    
    Direction orientation;
    //格子宽
    int width;
    //格子高
    int height;

public:
    Device(int r, Direction dir, int w, int h) : rate(r), orientation(dir), width(w), height(h) {}

    int getRate() const {
        return rate;
    }
    Direction getOrientation(){
        return orientation;
    }

    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }
};

class Miner : public Device {
public:
    Miner(int r, Direction dir) : Device(r, dir, 1, 1) {}

};

class Belt : public Device {
public:
    //定义传送带的传送方向
    Direction conveyorDirection;
    Belt(int r, Direction dir, Direction conveyDir) : Device(r, dir, 1, 1), conveyorDirection(conveyDir) {}

};

class Cutter : public Device {
public:
    Cutter(int r, Direction dir) : Device(r, dir, 1, 2) {}

};

class Trash : public Device {
public:
    Trash(int r, Direction dir) : Device(r, dir, 1, 1) {}

};

class DeliveryCenter {
public:
    std::vector<resource> deliveredResources;
    void deliver(resource& res) {
        std::cout << "Delivering resource with value " << res.value << " to the DeliveryCenter" << std::endl;
        deliveredResources.push_back(res);
    }
};

#endif // BUILDING_H

#include "phys_object.hpp"
#include <vector>
#include <iostream>
// calculates time to the collision of boxes with themselves
float predictBoxCollision(physObj::Box box_1,physObj::Box box_2 ){
    float deltaV;
    float deltaPos;
    deltaPos = box_2.position - box_1.position;
    deltaV = box_1.velocity - box_2.velocity;
    if(deltaV == 0 || deltaPos/deltaV <= 0){
        throw false;
    }
    return deltaPos/deltaV;
}
//calculates time to box1 collision with the wall(origin)
float predictWallCollision(physObj::Box box) {
    if(box.velocity == 0 || box.position/(-1 * box.velocity) <= 0){
        throw false;
    }
    return box.position/(-1 * box.velocity);
}
float moveBox(float velocity, float time){
    return velocity * time;
}
// calculates boxes velocity after collision
std::vector<float> calcVelCol(physObj::Box box1, physObj::Box box2){
    std::vector<float> velocity(2, 0);
    velocity[0] = (((box1.mass - box2.mass)/(box1.mass + box2.mass)) * box1.velocity) + (((2*box2.mass)/(box1.mass + box2.mass)) * box2.velocity);
    velocity[1] = ((2*box1.mass)/(box1.mass + box2.mass))*box1.velocity + (((box2.mass - box1.mass)/(box1.mass + box2.mass))*box2.velocity);
    return velocity;
};
int main(int argc, const char * argv[]) {
    physObj::Box box1;
    physObj::Box box2;
    box1.Create(1, 0, 100);
    float biggerBoxMass = 100000000;
    box2.Create(biggerBoxMass, -5, 200);
    int collisionNo = 0;
    float timeToWall = std::numeric_limits<float>::max();
    float timeToBoxC = std::numeric_limits<float>::max();
    bool wallC;
    bool boxC;
    std::vector<float> afterCollisionVelocity(2,0);
    while(true){
        try {
            wallC = true;
            timeToWall = predictWallCollision(box1);
        } catch (bool noCollision) {
            wallC = false;
            timeToWall = std::numeric_limits<float>::max();
        }
        try {
            boxC = true;
            timeToBoxC = predictBoxCollision(box1, box2);
        } catch (bool noCollision) {
            boxC = false;
            timeToBoxC = std::numeric_limits<float>::max();
        }
        if(!wallC && !boxC){break;}
        if(timeToWall < timeToBoxC){
            box1.position = 0;
            box1.velocity = -1 * box1.velocity;
            box2.position += moveBox(box2.velocity, timeToWall);
            collisionNo++;
        }
        else{
            afterCollisionVelocity = calcVelCol(box1, box2);
            box1.position += moveBox(box1.velocity, timeToBoxC) - 0.1; // adding a small buffer to prevent false positives on collision detection
            box2.position += moveBox(box2.velocity, timeToBoxC) + 0.1;
            box1.velocity = afterCollisionVelocity[0];
            box2.velocity = afterCollisionVelocity[1];
            collisionNo++;
        }
    };
    std::cout << "The second box has " << biggerBoxMass << " times more mass than the first box \n";
    std::cout << "Number of collision/pi: " << collisionNo << "\n";
    return 0;
}

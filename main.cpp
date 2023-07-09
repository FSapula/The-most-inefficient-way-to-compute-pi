#include "phys_object.hpp"
#include <vector>
#include <iostream>
// calculates time to the collision of boxes with themselves
float predictBoxCollision(float position1, float velocity1, float position2, float velocity2){
    float deltaV;
    float deltaPos;
    deltaPos = position2 - position1;
    deltaV =  velocity1 - velocity2;
    if(deltaV == 0 || deltaPos/deltaV <= 0 || deltaV < 0){
        throw false;
    }
    return deltaPos/deltaV;
}
//calculates time to box1 collision with the wall(origin)
float predictWallCollision(float velocity, float position) {
    if(position == 0 || velocity >= 0){
        throw false;
    }
    return position/(-1 * velocity);
}
float moveBox(float velocity, float time){
    return velocity * time;
}
// calculates boxes velocity after collision
std::vector<float> calcVelCol(float mass1, float velocity1, float mass2, float velocity2){
    std::vector<float> velocity(2, 0);
    velocity[0] = (((mass1 - mass2)/(mass1 + mass2)) * velocity1) + (((2*mass2)/(mass1 + mass2)) * velocity2);
    velocity[1] = ((2*mass1)/(mass1 + mass2))*velocity1 + (((mass2 - mass1)/(mass1 + mass2))*velocity2);
    return velocity;
};
int main(int argc, const char * argv[]) {
    physObj::Box box1 = physObj::Box(1, 0, 100);
    physObj::Box box2 = physObj::Box(10000000000, -10, 200);
    const float mass1 = box1.GetMass();
    const float mass2 = box2.GetMass();
    int collisionNo = 0;
    float timeToWall = std::numeric_limits<float>::max();
    float timeToBoxC = std::numeric_limits<float>::max();
    bool wallC;
    bool boxC;
    std::vector<float> afterCollisionVelocity(2,0);
    while(true){
        wallC = true;
        boxC = true;
        try {
            timeToWall = predictWallCollision(box1.GetVelocity(), box1.GetPosition());
        } catch (bool error) {
            wallC = false;
            timeToWall = std::numeric_limits<float>::max();
        }
        try {
            timeToBoxC = predictBoxCollision(box1.GetPosition(), box1.GetVelocity(), box2.GetPosition(), box2.GetVelocity());
        } catch (bool error) {
            boxC = false;
            timeToBoxC = std::numeric_limits<float>::max();
        }
        if(!wallC && !boxC){break;}
        if(timeToWall < timeToBoxC){
            box1.SetPosition(0);
            box1.SetVelocity(-1 * box1.GetVelocity());
            box2.Move(moveBox(box2.GetVelocity(), timeToWall));
            collisionNo++;
        }else{
            afterCollisionVelocity = calcVelCol(mass1, box1.GetVelocity(), mass2, box2.GetVelocity());
            box1.Move(moveBox(box1.GetVelocity(), timeToBoxC));
            box2.Move(moveBox(box2.GetVelocity(), timeToBoxC));
            box1.SetVelocity(afterCollisionVelocity[0]);
            box2.SetVelocity(afterCollisionVelocity[1]);
            collisionNo++;
        }
    };
    std::cout << collisionNo;
    return 0;
}

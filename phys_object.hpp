#ifndef phys_object_hpp
#define phys_object_hpp

#include <stdio.h>

#endif /* phys_object_hpp */
namespace physObj{
class Box{
    float mass;
    float velocity;
    float position;
public:
    Box(float inputMass, float inputVelocity, float inputPosition){
        mass = inputMass;
        velocity = inputVelocity;
        position = inputPosition;
    }
    void SetVelocity(float velocityIn){
        velocity = velocityIn;
    }
    void SetPosition(float positionIn){
        position = positionIn;
    }
    void Move(float move){
        position += move;
    }
    float GetVelocity(){
        return velocity;
    }
    float GetMass(){
        return mass;
    }
    float GetPosition(){
        return position;
    }
};
}

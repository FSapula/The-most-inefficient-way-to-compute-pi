#ifndef phys_object_hpp
#define phys_object_hpp

#include <stdio.h>

#endif /* phys_object_hpp */
namespace physObj{
class Box{
public:
    float mass;
    float velocity;
    float position;
    void Create(int inputMass, float inputVelocity, float inputPosition){
        mass = inputMass;
        velocity = inputVelocity;
        position = inputPosition;
    }
};
}

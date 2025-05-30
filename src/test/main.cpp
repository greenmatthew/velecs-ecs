#include <iostream>

#include "velecs/ecs/Common.hpp"

using namespace velecs::ecs;
using namespace velecs::math;

int main()
{
    Entity parent = Entity::Create()
        .WithName("Parent Entity")
        .WithPos(Vec3::FORWARD * 1)
        ;
    Transform& parentTransform = parent.GetTransform();
    Relationship& parentRelationship = parent.GetRelationship();
    std::cout << "Transform: " << parent.GetName() << std::endl;
    std::cout << "\tPosition: " << parentTransform.GetPos() << std::endl;
    std::cout << "\tScale: " << parentTransform.GetScale() << std::endl;
    std::cout << "\tRotation: " << parentTransform.GetEulerAnglesDeg() << std::endl;
    std::cout << "\tModel Matrix:\n" << parentTransform.GetModelMatrix() << std::endl;
    std::cout << "\tWorld Matrix:\n" << parentTransform.GetWorldMatrix() << std::endl;

    Entity child = Entity::Create()
        .WithName("Child Entity")
        .WithParent(parent)
        .WithPos(Vec3::FORWARD * 10)
        ;
    Transform& childTransform = child.GetTransform();
    Relationship& childRelationship = child.GetRelationship();
    std::cout << "Transform: " << child.GetName() << std::endl;
    std::cout << "\tParent:" << (childRelationship.GetParent() ? childRelationship.GetParent().GetName() : "(n/a)") << '\n' << std::endl;
    std::cout << "\tPosition: " << childTransform.GetPos() << std::endl;
    std::cout << "\tScale: " << childTransform.GetScale() << std::endl;
    std::cout << "\tRotation: " << childTransform.GetEulerAnglesDeg() << std::endl;
    std::cout << "\tModel Matrix:\n" << childTransform.GetModelMatrix() << std::endl;
    std::cout << "\tWorld Matrix:\n" << childTransform.GetWorldMatrix() << std::endl;

    Entity::RequestDestroy(parent);
    Entity::ProcessDestructionQueue();

    if (child) std::cout << child.GetName() << " is still alive!" << std::endl;
    else std::cout << "Entity is no longer alive." << std::endl;

    return EXIT_SUCCESS;
}

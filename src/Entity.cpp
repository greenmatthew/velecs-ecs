/// @file    Entity.cpp
/// @author  Matthew Green
/// @date    2025-05-12 16:24:39
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ecs/Entity.hpp"
#include "velecs/ecs/EntityBuilder.hpp"

#include "velecs/ecs/tags/DestroyTag.hpp"

#include "velecs/ecs/components/Name.hpp"
#include "velecs/ecs/components/Relationship.hpp"
#include "velecs/ecs/components/Transform.hpp"

#include <memory>
#include <string>

namespace velecs::ecs {

// Public Fields

const Entity Entity::INVALID;

// Constructors and Destructors

// Public Methods

EntityBuilder Entity::Create()
{
    return EntityBuilder();
}

std::string Entity::GetName() const
{
    return GetComponent<Name>().GetName();
}

void Entity::SetName(const std::string& newName)
{
    GetComponent<Name>().SetName(newName);
}

Relationship& Entity::GetRelationship() const
{
    return GetComponent<Relationship>();
}

Transform& Entity::GetTransform() const
{
    return GetComponent<Transform>();
}

void Entity::RequestDestroy(Entity entity)
{
    if (entity) entity.AddTag<DestroyTag>();
}

void Entity::ProcessDestructionQueue()
{
    // Create a view of all entities with the DestroyTag
    auto view = registry.view<DestroyTag>();
    
    // Store the entities in a temporary vector
    // This is necessary because we'll be modifying the registry during iteration
    std::vector<Entity> toDestroy;
    for (auto handle : view)
    {
        toDestroy.push_back(Entity(handle));
    }
    
    // Now process each entity for destruction
    for (auto entity : toDestroy)
    {
        // Ensure entity is still valid before destroying it
        if (entity) entity.Destroy(true);
    }
}

// Protected Fields

// Protected Methods

// Private Fields

entt::registry Entity::registry;

// Private Methods

void Entity::Destroy(bool removeParent) const
{
    auto& relationship = GetRelationship();
    const size_t childCount = relationship.GetChildCount();
    if (childCount > 0)
    {
        const auto childCountStr = std::to_string(childCount) + (childCount == 1 ? " child" : " children");
        std::cout << "Destroying the " << childCountStr << " of '" << GetName() << "':" << std::endl;
        for (const Entity& child : relationship.Reverse())
        {
            if (child) child.Destroy(false);
            else std::cout << "ERROR: child entity is not valid!" << std::endl;
        }
    }

    if (removeParent) relationship.SetParent(Entity::INVALID);

    std::cout << "Destroying '" << GetName() << "'!" << std::endl;
    registry.destroy(handle);
}

} // namespace velecs::ecs

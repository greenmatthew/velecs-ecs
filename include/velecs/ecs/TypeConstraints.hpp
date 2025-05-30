/// @file    TypeConstraints.hpp
/// @author  Matthew Green
/// @date    2025-05-12 17:32:24
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <type_traits>

namespace velecs::ecs {

class Entity;
class Tag;
class Component;

template <typename T>
using IsEntity = std::enable_if_t<std::is_base_of_v<Entity, T>>;

template <typename T>
using IsTag = std::enable_if_t<std::is_base_of_v<Tag, T>>;

template <typename T>
using IsComponent = std::enable_if_t<std::is_base_of_v<Component, T>>;

} // namespace velecs::ecs

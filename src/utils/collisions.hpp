#pragma once
#include <utils/utils.hpp>
#include <array>

bool is_colliding(const Rectanglei x, const Rectanglei y);

std::array<bool, 4> is_colliding_yes(const Rectanglei x, const Rectanglei y);


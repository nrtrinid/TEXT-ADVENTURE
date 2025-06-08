#pragma once

#include "ItemType.h"
#include <memory>
#include <string>
#include <optional>

struct Item {
	std::string id;
	std::string name;
	std::string description;
	ItemType type = ItemType::Consumable;
	std::string effectID;
	std::optional<int> magnitudeOverride;

	virtual ~Item() = default;

    Item(std::string id,
        std::string name,
        std::string desc,
        ItemType    type,
        std::string effectID,
        std::optional<int> magnitude = std::nullopt)
        : id(std::move(id)),
        name(std::move(name)),
        description(std::move(desc)),
        type(type),
        effectID(std::move(effectID)),
        magnitudeOverride(magnitude)
    {}

    virtual std::shared_ptr<Item> clone() const {
        return std::make_shared<Item>(*this);
    }
};

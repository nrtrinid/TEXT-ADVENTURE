#pragma once

#include "Character.h"
#include <vector>
#include <memory>
#include <string>

enum class PartyType {
    Player,
    Mercenary,
    Enemy,
    NPC
};

class Party {
public:
    using Ptr = std::shared_ptr<Party>;

    explicit Party(PartyType type = PartyType::Player);

    void addMember(std::shared_ptr<Character> character);
    void removeMemberByID(const std::string& id);

    std::shared_ptr<Character> getMemberByID(const std::string& id) const;
    std::shared_ptr<Character> getMemberByIndex(size_t index) const;
    int getIndexOf(const std::shared_ptr<Character>& character) const;

    const std::vector<std::shared_ptr<Character>>& getMembers() const;

    // party properties
    size_t size() const;
    bool isEmpty() const;
    bool isFull() const;

    // type info
    PartyType getType() const;
    void setType(PartyType newType);

private:
    std::vector<std::shared_ptr<Character>> members;
    PartyType type = PartyType::Player;
    static constexpr size_t maxSize = 4;
};

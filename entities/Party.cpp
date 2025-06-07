#include "Party.h"

Party::Party(PartyType type) : type(type) {}

void Party::addMember(std::shared_ptr<Character> character) {
	if (!isFull()) {
		members.push_back(character);
	}
}

void Party::removeMemberByID(const std::string& id) {
	for (auto it = members.begin(); it != members.end(); ++it) {
		if ((*it)->getID() == id) {
			members.erase(it);
			break;
		}
	}
}

std::shared_ptr<Character> Party::getMemberByID(const std::string& id) const {
	for (const auto& c : members) {
		if (c->getID() == id) {
			return c;
		}
	}
	return nullptr; // not found
}

std::shared_ptr<Character> Party::getMemberByIndex(size_t index) const {
	if (index >= members.size()) return nullptr;
	return members[index];
}

int Party::getIndexOf(const std::shared_ptr<Character>& character) const {
	for (size_t i = 0; i < members.size(); ++i) {
		if (members[i] == character) {
			return static_cast<int>(i);
		}
	}
	return -1; // not found
}


const std::vector<std::shared_ptr<Character>>& Party::getMembers() const {
	return members;
}

size_t Party::size() const {
	return members.size();
}

bool Party::isEmpty() const {
	return members.empty();
}

bool Party::isFull() const {
	return members.size() >= maxSize;
}

PartyType Party::getType() const {
	return type;
}

void Party::setType(PartyType newType) {
	type = newType;
}
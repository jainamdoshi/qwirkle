#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

LinkedList::~LinkedList() = default;

bool LinkedList::isEmpty() {
    return (this->size() == 0);
}

int LinkedList::size() {
    return this->length;
}

SharedTile LinkedList::getTile(int index) {
    SharedTile tile = nullptr;
    // Check for linkedlist and if index is within range or not.
    if (!this->isEmpty() && index >= 0 && index < this->size()) {
        std::shared_ptr<Node> curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->getNext();
        }
        tile = curr->getTile();
    }

    return tile;
}

SharedTile LinkedList::getTile(const Tile & searchTile) {
    // Check for linkedlist and if index is within range or not.
    SharedTile tile = nullptr;
    std::shared_ptr<Node> curr = head;
    while (tile == nullptr && curr != nullptr) {
        if (curr->getTile()->isEqual(searchTile)) {
            tile = curr->getTile();
        }
        curr = curr->getNext();
    }
    return tile;
}

// This method will always add Tile at the back of the LinkedList.
void LinkedList::addTile(const SharedTile & tile) {
    if (tile != nullptr) {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(tile, nullptr);
        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            this->tail->setNext(newNode);
            this->tail = newNode;
        }
        ++this->length;
    }
}

SharedTile LinkedList::deleteTile(const SharedTile & toRemove) {
    SharedTile tile = nullptr;
    // Check if the linked list is empty or not.
    if (!this->isEmpty()) {
        std::shared_ptr<Node> curr = head;
        std::shared_ptr<Node> prev = nullptr;

        //Loop till the tile is found or reached to end of linked list.
        while (curr != nullptr && tile == nullptr) {
            // same memory location
            if (toRemove == curr->getTile()) {
                // middle or end of the list
                if (prev != nullptr) {
                    prev->setNext(curr->getNext());
                }
                // beginning of list
                else {
                    head = curr->getNext();
                }
                if (curr == tail) {
                    this->tail = prev;
                }
                tile = curr->getTile();
                // For development only. Production will never enter this state
                if (tile == nullptr)
                    throw std::runtime_error(
                        "Reached illegal state Terminating...");
                length--;
            }

            prev = curr;
            curr = curr->getNext();
        }
    }
    return tile;
}

string LinkedList::toString(bool isColour, bool isSaving) {
    string result = "";

    // Get and converts each tile in the list to a string
    std::shared_ptr<Node> curr = head;
    while (curr != nullptr) {
        result += curr->getTile()->toString(isColour, isSaving);

        // Does not produce a comma after the last tile
        if (curr->getNext() != nullptr) {
            result += ",";
        }
        curr = curr->getNext();
    }

    return result + "\n";
}


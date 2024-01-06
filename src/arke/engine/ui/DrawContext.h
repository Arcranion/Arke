#pragma once

#include <vector>

#include "DrawCall.h"

namespace Arke::UI {
    class DrawContext {
    public:
        class Node;
    private:
        Node* rootNode = new Node(nullptr, nullptr); // Root node
        Node* lastAddedNode = nullptr; // Last added node
        Node* currentNode = rootNode; // Current tree node
    public:
        /**
         * Begin tree from last added draw call
         */
        void beginTree();
        /**
         * Add draw call to current tree
         */
        void drawCall(DrawCall* drawCall);
        /**
         * End tree and move to previous(parent of currentNode) node
         */
        void endTree();

        class Node {
        public:
            Node* parent;
            DrawCall* drawCall = nullptr;
            std::vector<Node*>* children = nullptr;

            void makeTree();

            Node(Node* parent, DrawCall* drawCall);
            ~Node();
        };
    };
}
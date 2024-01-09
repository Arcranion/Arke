#include "DrawContext.h"

namespace Arke::UI {
    void DrawContext::beginTree() {
        this->currentNode = lastAddedNode;
        this->currentNode->makeTree();
    }

    void DrawContext::drawCall(DrawCall* drawCall) {
        auto node = new Node(currentNode, drawCall);
        this->lastAddedNode = node;
        this->currentNode->children->push_back(node);
    }

    void DrawContext::endTree() {
        this->currentNode = this->currentNode->parent;
    }

    DrawContext::Node *DrawContext::getRootNode() {
        return this->rootNode;
    }

    DrawContext::Node *DrawContext::getLastAddedNode() {
        return this->lastAddedNode;
    }

    DrawContext::Node *DrawContext::getCurrentNode() {
        return this->currentNode;
    }

    void DrawContext::Node::makeTree() {
        if(!this->children) this->children = new std::vector<Node*>;
    }

    DrawContext::Node::Node(DrawContext::Node *parent, DrawCall* drawCall) {
        this->parent = parent;
        this->drawCall = drawCall;
    }

    DrawContext::Node::~Node() {
        delete children;
    }
}
#pragma once

#include<string>
#include<vector>

struct Node
{
    // next node holds vector of nodes to point to multiple children
    std::vector<Node*> next_node = {};
    Node* prev_node = nullptr;
    std::string key = std::string("");
    std::string val = std::string("");
    int length = 0;
};

class DoubleLinkNode
{
public:
    explicit DoubleLinkNode() :begin_node(nullptr), end_node(nullptr)
    {};

    explicit DoubleLinkNode(Node* begin_node_, Node* end_node_) :begin_node(begin_node_), end_node(end_node_)
    {};

    ~DoubleLinkNode() noexcept
    {
        begin_node = nullptr;
        end_node = nullptr;
        delete begin_node;
        delete end_node;
    }

    // Copy Constructor
    DoubleLinkNode(DoubleLinkNode const& other) :
        begin_node(other.begin_node ? other.begin_node : nullptr),
        end_node(other.end_node ? other.end_node : nullptr)
    {}

    DoubleLinkNode& operator=(DoubleLinkNode const& other)
    {
        DoubleLinkNode temp(other);
        std::swap(begin_node, temp.begin_node);
        std::swap(end_node, temp.end_node);
        return *this;
    }

    // Move constructor
    DoubleLinkNode(DoubleLinkNode&& other) noexcept
    {
        begin_node = other.begin_node;
        end_node = other.end_node;
        other.begin_node = nullptr;
        other.end_node = nullptr;
    }

    DoubleLinkNode& operator=(DoubleLinkNode&& other) noexcept
    {
        DoubleLinkNode temp(std::move(other));
        std::swap(begin_node, temp.begin_node);
        std::swap(end_node, temp.end_node);
        return *this;
    }



    Node* begin_node = new Node();
    Node* end_node = new Node();

    Node* insert_node(const std::string key, const std::string val, Node* prev_node = nullptr);
    void traverse(Node* node);
    void reset_nodes()
    {
        begin_node = nullptr;
        end_node = nullptr;
    }
    Node* get_begin_node()
    {
        return begin_node;
    }

    Node* get_end_node()
    {
        return end_node;
    }
};
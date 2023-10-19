#include "double_link_node.h"

#include<iostream>

Node* DoubleLinkNode::insert_node(const std::string key, const std::string val, Node* prev_node)
{
    Node* cur_node = new Node();
    cur_node->key = key;
    cur_node->val = val;

    // Point to parent node if present
    if (prev_node)
    {
        cur_node->prev_node = prev_node;
        prev_node->next_node.push_back(cur_node);
        cur_node->length = prev_node->length + 1;
    }

    // First node
    if (!begin_node)
    {
        begin_node = cur_node;
        end_node = cur_node;
    }

    // Keep track of node that's farthest from root
    if (cur_node->length >= end_node->length)
    {
        end_node = cur_node;
    }
    return cur_node;
}

void DoubleLinkNode::traverse(Node* begin)
{
    if (!begin)
    {
        std::cout << "No node found\n";
        return;
    }
    int indent = begin->length * 2;
    std::cout << std::string(indent, ' ');
    std::cout << begin->key;
    if (!begin->val.empty())
    {
        std::cout << " : " << begin->val;
    }
    std::cout << std::endl;
    for (Node* nd : begin->next_node)
    {
        traverse(nd);
    }
}
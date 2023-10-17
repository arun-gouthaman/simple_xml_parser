#pragma once
#include<iostream>
#include<string>
#include<map>
#include <vector>

struct Node
{
    Node* prev_node = nullptr;
    std::string key = std::string("");
    std::vector<Node*> next_node = {};
    std::string val = std::string("");
    int length = 0;
};

class DoubleLinkNode
{
    public:
    DoubleLinkNode():begin_node(nullptr), end_node(nullptr)
    {};
    ~DoubleLinkNode()
    {
        begin_node = nullptr;
        end_node = nullptr;
        delete begin_node;
        delete end_node;
    }
    Node* begin_node = new Node();
    Node* end_node = new Node();
    Node* insert_node(const std::string key, const std::string val, Node* prev_node = nullptr);
    void traverse(Node* node);
    void traverse_breadth(Node* node);

    Node* get_begin_node()
    {
        return begin_node;
    }

    Node* get_end_node()
    {
        return end_node;
    }
};

class XmlParser
{
    private:
    DoubleLinkNode double_link_node;
    public:
    std::string read_file(const std::string& file_path);
    Node* parse_to_node(const std::string& xml_content);
    bool is_close_tag(const std::string& cur_tag, const std::string& open_tag);
    void display_node_data();
};
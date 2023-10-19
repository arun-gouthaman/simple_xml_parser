#pragma once
#include "double_link_node.h"

class XmlParser
{
    private:
    DoubleLinkNode double_link_node;
    public:
    std::string read_file(const std::string& file_path);
    Node* parse_to_node(const std::string& xml_content);
    inline bool is_close_tag(const std::string& cur_tag, const std::string& open_tag);
    void display_node_data();
};
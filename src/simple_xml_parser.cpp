#include "simple_xml_parser.h"

#include<fstream>

Node* DoubleLinkNode::insert_node(const std::string key, const std::string val, Node* prev_node)
{
    Node* cur_node = new Node();
    cur_node->key = key;
    cur_node->val = val;
    if (prev_node)
    {
        cur_node->prev_node = prev_node;
        prev_node->next_node.push_back(cur_node);
        cur_node->length = prev_node->length + 1;
    }
    if(!begin_node)
    {
        begin_node = cur_node;
        end_node = cur_node;
    }
    if (cur_node->length >= end_node->length)
    {
        end_node = cur_node;
    }
    return cur_node;
}

void DoubleLinkNode::traverse(Node* begin)
{
    int indent = begin->length * 2;
    std::cout << std::string(indent, ' ');
    std::cout << begin->key;
    if (begin->val.size()>0)
    {
        std::cout << " : " << begin->val;
    }
    std::cout << std::endl;
    for(Node* nd : begin->next_node)
    {
        traverse(nd);
    }
}

void DoubleLinkNode::traverse_breadth(Node* begin)
{
    std::vector<Node*> nodes;
    std::vector<Node*> child_nodes;
    nodes.push_back(begin);
    Node* nd = begin;

}

std::string XmlParser::read_file(const std::string& file_path)
{
    std::fstream xml_file;
    xml_file.open(file_path, std::ios::in | std::ios::out);
    if(!xml_file)
    {
        std::cout << "Unable to open file\n";
        return "";
    }
    std::string file_contents;
    while(!xml_file.eof())
    {
        std::string line;
        std::getline(xml_file, line);
        file_contents += line;
    }
    xml_file.close();
    return file_contents;
}

bool XmlParser::is_close_tag(const std::string& cur_tag, const std::string& open_tag)
{
    if((cur_tag.length() != open_tag.length()+1) ||
       (cur_tag[0] != '/') ||
       (cur_tag != "/"+open_tag)
    )
    {
        return false;
    }
    return true;
}

Node* XmlParser::parse_to_node(const std::string& xml_content)
{
    bool bracket_open = false;
    std::string tag;
    std::string value;
    std::vector<std::string> tag_vec;
    Node* cur_node = new Node();
    cur_node = nullptr;
    bool tag_space = true;
    std::string tag_name;
    if (xml_content.size() < 1)
    {
        std::cout << "No xml content read\n";
        return nullptr;
    }
    for(char c : xml_content)
    {
        if(c == '<')
        {
            if(cur_node && !value.empty())
            {
                cur_node->val = value;
                value.clear();
            }
            bracket_open = true;
            continue;
        }

        if(c == '>')
        {
            bracket_open = false;

            if (tag[0] == '/' && tag_vec.empty())
            {
                std::cout << "Open close tag mismatch at " << tag << "\n";
                return nullptr;
            }

            if (tag[0] == '?' || tag[0] == '!')
            {
                tag.clear();
                tag_name.clear();
                continue;
            }
            if(!tag.empty() && tag[0] != '/')
            {
                cur_node = double_link_node.insert_node(tag, value, cur_node);
                if (tag_name.empty())
                {
                    tag_name = tag;
                }
                tag_vec.push_back(tag_name);
                tag.clear();
                value.clear();
                tag_name.clear();
                continue;
            }

            bool is_closed = is_close_tag(tag, tag_vec.back());
            if(is_closed)
            {
                tag_vec.pop_back();
                tag.clear();
                if (cur_node && cur_node->prev_node)
                {
                    cur_node = cur_node->prev_node;
                }
                continue;
            }
            else
            {
                std::cout << "TAG CHECK";
                for (std::string t : tag_vec)
                {
                    std::cout << t << "\n";
                }
                std::cout << "Open close tag mismatch at " << tag << "\n";
                return nullptr;
            }
        }

        if(bracket_open)
        {
            if (c == ' ' && tag_name.empty())
            {
                tag_name = tag;
            }
            tag.push_back(c);
            continue;
        }

        if(!bracket_open)
        {
            if (value.size() < 1 && c == ' ')
            {
                continue;
            }
            value.push_back(c);
        }
    }
    
    return double_link_node.begin_node ? double_link_node.begin_node : nullptr;
}

void XmlParser::display_node_data()
{
    double_link_node.traverse(double_link_node.begin_node);
}
#include "simple_xml_parser.h"

#include<fstream>

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
    if(!begin_node)
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

// Check if the tag read is close tag comparing with open tag at the end of vector
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

// Construct node graph structure from xml file content
Node* XmlParser::parse_to_node(const std::string& xml_content)
{
    bool bracket_open = false;
    std::string tag;
    std::string value;
    std::vector<std::string> tag_vec;
    Node* cur_node = new Node();
    cur_node = nullptr;
    std::string tag_name;
    if (xml_content.size() < 1)
    {
        std::cout << "No xml content read\n";
        return nullptr;
    }

    // Iterate through the string and parse to node
    for(char c : xml_content)
    {
        // check for tag beginning
        if(c == '<')
        {
            // If new tag starts and value has been accumulated, assign value to rpevious node value.
            if(cur_node && !value.empty())
            {
                cur_node->val = value;
                value.clear();
            }
            bracket_open = true;
            continue;
        }

        // Check for tag ending
        if(c == '>')
        {
            bracket_open = false;

            // if tag vector is empty and a close tag is encountered return with error message
            if (tag[0] == '/' && tag_vec.empty())
            {
                std::cout << "Open close tag mismatch at " << tag << "\n";
                double_link_node.reset_nodes();
                return nullptr;
            }

            // if tag begins with ? or ! discard tag and continue
            if (tag[0] == '?' || tag[0] == '!')
            {
                tag.clear();
                tag_name.clear();
                continue;
            }

            // if tag has value and first character is not '/', open tag is found
            if(!tag.empty() && tag[0] != '/')
            {
                // insert node to structure with tag and value strings
                cur_node = double_link_node.insert_node(tag, value, cur_node);

                // if tag has properties, the first part is extracted for tag name and added to tag vector.
                if (tag_name.empty())
                {
                    tag_name = tag;
                }
                tag_vec.push_back(tag_name);

                // clear tag and value strings after inserting
                tag.clear();
                value.clear();
                tag_name.clear();
                continue;
            }

            // check if the tag has been properly closed
            bool is_closed = is_close_tag(tag, tag_vec.back());
            if(is_closed)
            {
                // if proper close tag found, remove last item from tag vector
                tag_vec.pop_back();
                // clear tag string
                tag.clear();
                if (cur_node && cur_node->prev_node)
                {
                    // set current node to previous node as the end tag indicates no further children for the node
                    cur_node = cur_node->prev_node;
                }
                continue;
            }
            else
            {
                std::cout << "Open close tag mismatch at " << tag << "\n";
                double_link_node.reset_nodes();
                return nullptr;
            }
        }

        // bracket_open is true if the tag open bracket is found and close is not found yet
        if(bracket_open)
        {
            // when the first space is found, tag name is extracted from full name
            if (c == ' ' && tag_name.empty())
            {
                tag_name = tag;
            }
            tag.push_back(c);
            continue;
        }

        if(!bracket_open)
        {
            // skip whitespaces for tag names
            if (value.empty() && c == ' ')
            {
                continue;
            }
            value.push_back(c);
        }
    }
    // if begin node if valid, return begin_node else return nullptr
    return double_link_node.begin_node ? double_link_node.begin_node : nullptr;
}

void XmlParser::display_node_data()
{
    double_link_node.traverse(double_link_node.begin_node);
}
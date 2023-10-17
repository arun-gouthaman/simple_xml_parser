//#include <map>
//#include <string>
//#include <vector>
//#include<iostream>
//#include<fstream>
//
//struct Node
//{
//    Node* prev_node = nullptr;
//    std::string data = std::string("");
//    std::vector<Node*> next_node = {};
//    std::string val = std::string("");
//    int length = 0;
//};
//
//class DoubleLinkNode
//{
//public:
//    Node* head = new Node();;
//    
//    bool head_assigned = false;
//
//    Node* insert_node(const std::string& key, const std::string& val, Node* prev_node, bool end)
//    {
//        if (!head_assigned)
//        {
//            head->data = key;
//            head->val = val;
//            head_assigned = true;
//            return head;
//        }
//        Node* cur_node = new Node();
//        cur_node->data = key;
//        cur_node->val = val;
//        if (prev_node)
//        {
//            cur_node->prev_node = prev_node;
//            prev_node->next_node.push_back(cur_node);
//            cur_node->length = prev_node->length + 1;
//        }
//        return cur_node;
//    }
//
//};
//
//int main()
//{
//    std::fstream xml_file;
//    xml_file.open("sample.xml", std::ios::in| std::ios::out);
//    std::string file_contents;
//    while(!xml_file.eof())
//    {
//        std::string line;
//        std::getline(xml_file, line);
//        file_contents += line;
//    }
//    xml_file.close();
//    DoubleLinkNode double_link_node;
//    Node* head = new Node();
//    head = nullptr;
//    Node* cur_node = new Node();
//    cur_node = nullptr;
//    int bracket = 0;
//    std::vector<std::string> tag_vec;
//    std::vector<std::string> data_vec;
//    std::string cur_tag;
//    std::string data = "";
//    bool open_tag = false;
//    for(char c : file_contents)
//    {
//        if (c == '<')
//        {
//            if(data.length()>0)
//            {
//                data_vec.push_back(data);
//                data = "";
//            }
//            ++bracket;
//            continue;
//        }
//        else if(c == '>')
//        {
//            --bracket;
//
//            // Check for close tag
//            if(tag_vec.size()>0 && cur_tag == "/" + tag_vec.back())
//            {
//                tag_vec.pop_back();
//                cur_tag = "";
//                open_tag = false;
//                continue;
//            }
//            tag_vec.push_back(cur_tag);
//            cur_tag = "";
//            open_tag = true;
//            continue;
//        }
//
//        if(bracket > 0)
//        {
//            cur_tag.push_back(c);
//        }
//        else if(open_tag)
//        {
//            data.push_back(c);
//        }
//
//    }
//
//    for(std::string d : data_vec)
//    {
//        std::cout << d << "\n";
//    }
//
//}

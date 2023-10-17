#include "simple_xml_parser.h"

void process_xml_file(std::string file_path)
{
    XmlParser xml_parser;
    std::string file_content;
    file_content = xml_parser.read_file(file_path);
    Node* node = new Node();
    node = nullptr;
    node = xml_parser.parse_to_node(file_content);
    xml_parser.display_node_data();
    node = nullptr;
    delete node;
}

int main()
{
    std::string simple_xml = "C://my_files//CPP//xml_parser//src//sample.xml";
    std::string comp_xml = "C://my_files//CPP//xml_parser//src//complex_sample.xml";

    std::cout << "Simple\n";
    process_xml_file(simple_xml);
    std::cout << "\n\n\n";
    std::cout << "Complex\n";
    process_xml_file(comp_xml);
    return 0;
}
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
    std::string file_location = __FILE__;
    file_location = file_location.substr(0, file_location.rfind("\\"));

    std::string simple_xml = file_location + "//sample.xml";
    std::string comp_xml = file_location + "//complex_sample.xml";
    std::string nasa_xml = file_location + "//nasa.xml";


    //std::cout << simple_xml << "\n";
    //process_xml_file(simple_xml);

    //std::cout << std::string(2, '\n') << comp_xml << "\n";
    //process_xml_file(comp_xml);

    // Test xml file obtained online
    process_xml_file(nasa_xml);


    return 0;
}
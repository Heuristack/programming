#include "boost/program_options.hpp"
#include <iostream>

using namespace boost::program_options;
using namespace std;

int main(int argc, char const ** argv)
{
    options_description description("graph_search options");
    variables_map variables;

    description.add_options()
    ("help", "print available options")
    ("data-file", value<string>()->default_value(""), "graph data file to search")
    ("source-node", value<string>()->default_value("200"), "search starts from here")
    ("target-node", value<string>(), "target looking for")
    ("search-strategy", value<string>(), "algorithm used in the searching");

    store(parse_command_line(argc,argv,description),variables);
    if (variables.count("help")) {
        cout << description << endl;
        return 1;
    }

    string data_file = variables["data-file"].as<string>();
    if (data_file.empty()) {
        return 1;
    }
    string source_node = variables["source-node"].as<string>();

    cout << "data-file = " << data_file << endl;
    cout << "source-node = " << source_node << endl;
}


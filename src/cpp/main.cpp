#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

#include "generator/BAModel.h"
using namespace std;

void streamGraph(GraphImpOur* g, const std::string& filename) {
	std::ofstream of;
	of.open(filename, ios::out);
	of << *g;
	of.flush();
	of.close();
	std::cout << "Saved graph into " << filename;
}

void show_usage_and_exit() {
	std::cout << "-n - total number of vertices in the graph\nm0 - number of initial vertices fully connected\nm - number" 
			  << " of vertices added in each iteration\n-o - save file(graph.txt - default filename\n -h or --help - show help message "
			  << std::endl;
	exit(0);
}

bool validate_args(int n, int m, int m0) {
	return n > 0
		&& m > 0
		&& m0 > 0
		&& n > m0
		&& n > m0 + m;
}

std::tuple<int, int, int, std::string> parseCommandlineArgsOrExit(int argc, char** argv) throw(std::invalid_argument) {
	if (argc < 6)
		show_usage_and_exit();

	int n = 0, m0 = 0, m = 0;
	std::string filename = "graph.txt";
	for (int i = 0; i < argc; ++i) {
		const std::string&& arg = argv[i];
		if (arg == "-n")
			n = std::stoi(argv[i + 1]);
		else if (arg == "-m0")
			m0 = std::stoi(argv[i + 1]);
		else if (arg == "-m")
			m = std::stoi(argv[i + 1]);
		else if (arg == "-o")
			filename = argv[i + 1];
		else if (arg == "-h" || arg == "--help")
			show_usage_and_exit();
	}
	if (!validate_args(n, m, m0))
		throw std::invalid_argument("Invalid arguments!");
	return std::make_tuple(n, m, m0, filename);
}


// params N, m0, m, o
// 
int main(int argc, char** argv)
{
    BAModel m;
	bool isOutput = false;
	// parse input arguments
	try {
		auto arguments = parseCommandlineArgsOrExit(argc, argv);
		std::cout << "Generating graph..." << std::endl;
		std::cout << "Saving graph..." << std::endl;
		Graph* g = m.generateBAGraph(std::get<0>(arguments), std::get<1>(arguments), std::get<2>(arguments));
		streamGraph(dynamic_cast<GraphImpOur*>(g), std::get<3>(arguments));
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid arguments on input! See constraints!";
		return 1;
	}
	catch (const std::exception& e) {
		std::cerr << "An unknown error occured! " << e.what();
		return 1;
	}
	return 0;
}
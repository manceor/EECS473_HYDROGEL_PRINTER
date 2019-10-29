#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	ifstream in_file("CE3_3DBenchy.gcode");
	ofstream out_file("parsed_gcode.txt");

	string line;
	int num_layers = 0;
	int count_layers = 0;

	// find the number of layers
	while (getline(in_file, line)) {
		size_t find = line.find(";LAYER_COUNT:");

		if (find != string::npos) {
			num_layers = stoi(line.substr(13, string::npos));
			out_file << line << '\n';
			break;
		}

		out_file << line << '\n';
	}

	// change all extrusion values
	while (count_layers <= num_layers - 1 && getline(in_file, line)) {
		if (line.substr(0, 14) == ";TIME_ELAPSED:") {
			++count_layers;
			out_file << line << '\n';
			continue;
		}

		size_t find = line.find(" E");

		if (find != string::npos) {
			line = line.substr(0, find + 2);
			line += "69.6969";
		}

		out_file << line << '\n';
	}

	// output rest of gcode file
	while (getline(in_file, line)) {
		out_file << line << '\n';
	}
	
	in_file.close();
	out_file.close();

	return 0;
}

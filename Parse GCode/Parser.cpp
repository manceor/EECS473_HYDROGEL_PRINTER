#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	ifstream in_file("CE3_rectangular_prism_10mm_10mm_2mm.gcode");
	cout << "insert file name (include .gcode): ";
	string name_file;
	cin >> name_file;
	ofstream out_file(name_file);

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
			string line_value = line.substr(find + 2);
			float tmp = stof(line_value);
			tmp *= 100.0;
			line_value = to_string(tmp);
			line.replace(find + 2, line_value.length(), line_value);
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

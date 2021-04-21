/*==================================================
	This source file provided by Professor P
	Do not edit!
==================================================*/

//
#include "professor_lib.hpp"


//
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>


//
using std::cout, std::endl;
using std::vector;
using std::string;
using std::min, std::max;


//
const size_t BUFFER_WIDTH = 160;
const size_t BUFFER_HEIGHT = 40;
const size_t BUFFER_SIZE = BUFFER_WIDTH * BUFFER_HEIGHT;
const char GRAPH_CHAR_BORDER = '=';
const char GRAPH_CHAR_POINT = '*';
const char GRAPH_CHAR_EMPTY = ' ';


/*
	Load a converted file,
		translate and render datapoints to a cartesian plane suitable for printing to the terminal,
		and print it.
*/
void renderAndPrintConvertedFile(string file_name)
{
	//	Use a helper function to read and analyze the file at the same time
	std::vector<double> X, Y;
	double
		data_min_x, data_max_x, data_range_x,
		data_min_y, data_max_y, data_range_y
		;
	readAndAnalyzeConvertedFile(
		file_name,
		X, Y,
		data_min_x, data_max_x, data_range_x,
		data_min_y, data_max_y, data_range_y
	);
	
	//	Determine ratios to help translate between data and buffer dimensions
	double buffer_per_data_x = static_cast<double>(BUFFER_WIDTH) / data_range_x;
	double buffer_per_data_y = static_cast<double>(BUFFER_HEIGHT) / data_range_y;
	//cout << "Buffer dimensions: " << BUFFER_WIDTH << ":" << BUFFER_HEIGHT << endl;
	//cout << "Buffer per Data translations: " << buffer_per_data_x << ":" << buffer_per_data_y << endl;
	
	//	Create a buffer and fill it with empty characters (spaces)
	char * buffer = new char[BUFFER_SIZE];
	memset(buffer, GRAPH_CHAR_EMPTY, BUFFER_SIZE);
	
	//	Render data to the buffer
	for ( size_t i = 0; i < X.size(); i++ ) {
		
		//	Start with the raw data
		double x = X[i];
		double y = Y[i];
		//cout << "Initial point: " << x << ":" << y << endl;
		
		//	Translate the data to prevent negatives
		x -= data_min_x;
		y -= data_min_y;
		//cout << "Translated point: " << x << ":" << y << endl;
		
		//	Invert the Y so we have the origin at the bottom-left
		y = data_max_y - y;
		
		size_t buffer_x = round( x * buffer_per_data_x );
		size_t buffer_y = round( y * buffer_per_data_y );
		//cout << "Writing to " << buffer_x << ":" << buffer_y << endl;
		
		//
		size_t buffer_offset = calculateBufferOffset(buffer_x, buffer_y);
		buffer[buffer_offset] = GRAPH_CHAR_POINT;
	}
	
	//	Make a cute border around the buffer to hide my offset mistakes, lel
	drawBorderBuffer(buffer);
	
	//	Print the buffer to the terminal
	printBufferToTerminal(buffer);
}


/*
	Read the user's converted file into an X and Y vector of equal size
	While doing so, analyze statistics of the file for later use.
*/
void readAndAnalyzeConvertedFile(
	string file_name,
	std::vector<double>& X, std::vector<double>& Y,
	double& min_x, double& max_x, double& range_x,
	double& min_y, double& max_y, double& range_y
)
{
	//	Open the file
	std::ifstream f(file_name);
	if ( !f ) {
		throw std::runtime_error("Unable to read the file: " + file_name);
	}
	
	//	Track stuff
	bool initialized_min_max = false;
	
	//
	size_t loop_control = 0;
	loop_control--;	//	Yes, I'm hacking underflow to get the highest possible value
	while ( loop_control-- > 0 )
	{
		//	See if there's another point in the file
		double x, y;
		f >> x;
		f >> y;
		if ( f.eof() ) {
			break;
		}
		
		//	Initialize min/max values
		if ( !initialized_min_max ) {
			min_x = max_x = x;
			min_y = max_y = y;
			initialized_min_max = true;
		}
		else {
			
			//	Possibly adjust min/max values
			min_x = min(x, min_x);
			max_x = max(x, max_x);
			min_y = min(y, min_y);
			max_y = max(y, max_y);
		}
		
		//
		X.push_back(x);
		Y.push_back(y);
	}
	f.close();
	
	//	Calculate ranges
	range_x = max_x - min_x;
	range_y = max_y - min_y;
	
	//	Print min/max found in X and Y
	//cout << "Min/max X: " << min_x << ":" << max_x << endl;
	//cout << "Min/max Y: " << min_y << ":" << max_y << endl;
	//cout << "Ranges: " << range_x << ":" << range_y << endl;
}


/*
	Translate an x and y coordinate to a flat offset into the buffer array
*/
size_t calculateBufferOffset(size_t x, size_t y)
{
	//
	size_t buffer_offset = (y * BUFFER_WIDTH) + x;
	
	//	Keep in bounds just in case professor's code sucks
	buffer_offset = max(static_cast<size_t>(0), buffer_offset);
	buffer_offset = min(BUFFER_SIZE - 1, buffer_offset);
	
	return buffer_offset;
}

/*
	Draw a border around (in) the buffer.
*/
void drawBorderBuffer(char * buffer)
{
	//
	for ( size_t y = 0; y < BUFFER_HEIGHT; y++ ) {
		for ( size_t x = 0; x < BUFFER_WIDTH; x++ ) {
			
			//
			if ( x == 0 || x == BUFFER_WIDTH - 1 || y == 0 || y == BUFFER_HEIGHT - 1 ) {
				size_t buffer_offset = calculateBufferOffset(x, y);
				buffer[buffer_offset] = GRAPH_CHAR_BORDER;
			}
		}
	}
}


/*
	Print the contents of a buffer to the terminal
*/
void printBufferToTerminal(char * buffer)
{
	//
	for ( size_t buffer_y = 0; buffer_y < BUFFER_HEIGHT; buffer_y++ ) {
		for ( size_t buffer_x = 0; buffer_x < BUFFER_WIDTH; buffer_x++ ) {
			
			//
			size_t buffer_offset = calculateBufferOffset(buffer_x, buffer_y);
			cout << buffer[buffer_offset];
		}
		cout << endl;
	}
	cout << endl;
}









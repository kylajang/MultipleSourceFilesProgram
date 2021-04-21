/*==================================================
	This source file provided by Professor P
	Do not edit!
==================================================*/

#ifndef PROFESSOR_LIB_H
#define PROFESSOR_LIB_H


//
#include <string>
#include <vector>


//	Prototypes
void renderAndPrintConvertedFile(std::string file_name);
void readAndAnalyzeConvertedFile(
	std::string file_name,
	std::vector<double>& X, std::vector<double>& Y,
	double& min_x, double& max_x, double& range_x,
	double& min_y, double& max_y, double& range_y
);
size_t calculateBufferOffset(size_t x, size_t y);
void drawBorderBuffer(char * buffer);
void printBufferToTerminal(char * buffer);



#endif


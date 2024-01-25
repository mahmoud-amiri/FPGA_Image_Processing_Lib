#pragma once
#include "Mat.hpp"
#include "file_system.hpp"
#include <string.h> // memcpy
#include <stdlib.h> //realloc
#include "typedef.hpp"
#include "def.hpp"
#include "char_code.hpp"
#include <string>
#include "images_address.hpp"
using namespace std;
using std::string;

enum line_type {FILL, BORDERS};
class cv{
public:
	cv(file_system * fs);
	~cv();
	Mat imread(int name, mat_type type);
	void rectangle(Mat src, u32 x0, u32 y0, u32 x1, u32 y1, u32 color, line_type type, u8 transparency);
	void line(Mat src, u32 x0, u32 y0, u32 x1, u32 y1, u32 color, u32 thickness, u8 transparency);
	int putText(Mat src, string in, u32 x , u32 y, u32 color, u32 distance_between_char, u8 transparency);
	void putChar(Mat src,u32 name, u32 y0, u32 x0, u32 color, u8 transparency);
private:
	file_system * fs;

};

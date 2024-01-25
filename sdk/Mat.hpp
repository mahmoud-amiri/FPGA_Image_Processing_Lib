#pragma once
#include "xil_types.h"
#include <string.h> // memcpy
#include <stdlib.h> //realloc
enum mat_type{MONO, YCbCr};

class Mat{
public:
	Mat();
	Mat(mat_type type);
	~Mat();
	void set_address(u32 * address);
	u32 *get_address();
	void set_at(u32 xp,u32 yp,u32 value, u8 transparency);
	u32 get_at(u32 xp,u32 yp);
	void copyTo(Mat des);
	u32 rows;
	u32 cols;
private:

	u32 * address;
	mat_type type;
};

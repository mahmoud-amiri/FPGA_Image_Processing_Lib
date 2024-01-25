
#include "Mat.hpp"

Mat::Mat(){
	rows = 0;
	cols = 0;
	address = 0;
	this->type = YCbCr;
}
Mat::Mat(mat_type type){
	rows = 0;
	cols = 0;
	address = 0;
	this->type = type;
}

Mat::~Mat(){

}

void Mat::set_address(u32 * address){
	this->address = address;
}

void Mat::copyTo(Mat des){
	for (u32 i = 0; i < cols * rows; i++){
		*(des.get_address() + i) = *(address + i);
	}
 }
u32* Mat::get_address(){
	return address;
}

void Mat::set_at(u32 xp,u32 yp,u32 value, u8 transparency){
	if (type == MONO){
		*((u8*)address + (xp *cols) + yp) = (u8)(value & 0xFF);
	} else {
		*((u32*)address + (xp *cols) + yp) = (value & 0xFFFFFF) | ((transparency<<24)&0xFF000000);
	}
}
u32 Mat::get_at(u32 xp,u32 yp){
	u32 out;
	if (type == MONO){
		out =(u32) *((u8*)address + (yp *rows) + xp);
	} else {
		out = *((u32*)address + (yp *rows) + xp);
	}
	return out;
}

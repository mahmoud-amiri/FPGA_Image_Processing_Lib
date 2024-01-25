#include "cv.hpp"

cv::cv(file_system * fs){
	this->fs = fs;
}
cv::~cv(){

}
Mat cv::imread(int name, mat_type type){
	Mat out(type);
	u32 *entry_address = fs->get_file_address(name);
	u32 rows = fs->read(entry_address + 2);
	u32 cols = fs->read(entry_address + 3);
	out.set_address(entry_address + 4);
	out.rows = rows;
	out.cols = cols;
	return out;
}



void cv::rectangle(Mat src, u32 y0, u32 x0, u32 y1, u32 x1, u32 color, line_type type, u8 transparency){
	if (type == FILL){
		for (u32 x = x0; x < x1; x++){
			for (u32 y = y0; y < y1; y++){
				src.set_at(x, y, color, transparency);
			}
		}
	} else {
		line(src, y0, x0, y1, x0, color, 2, transparency);
		line(src, y0, x0, y0, x1, color, 2, transparency);
		line(src, y0, x1, y1, x1, color, 2, transparency);
		line(src, y1, x0, y1, x1, color, 2, transparency);

	}
}

void cv::line(Mat src, u32 y0, u32 x0, u32 y1, u32 x1, u32 color, u32 thickness, u8 transparency){
	u32 *x;
	u32 *y;
	u32 h;
	u32 sy = y1 - y0;
	u32 sx = x1 - x0;
	if ((x1 - x0)>(y1 - y0)){
		h = x1 - x0;
		x = new u32[h];
		y = new u32[h];
		for (u32 i = 0; i < h; i++){
			x[i] = x0 + i;
			y[i] = (sy * x[i]) / sx;
			y[i] += y0;
		}
	} else {
		h = y1 - y0;
		x = new u32[h];
		y = new u32[h];
		for (u32 i = 0; i < h; i++){
			y[i] = y0 + i;
			x[i] = (sx * y[i]) / sy;
			x[i] += x0;
		}
	}

	for (u32 k = 0; k < h; k++){
		for (int i = -(int)thickness; i < (int)thickness; i++){
			for (int j = -(int)thickness; j < (int)thickness; j++){
				src.set_at((u32)((int)x[k] + i), (u32)((int)y[k] + j), color, transparency);
			}
		}

	}
	delete x;
	delete y;
}

void cv::putChar(Mat src,u32 name, u32 y0, u32 x0, u32 color, u8 transparency){
	Mat text(MONO);
	text = imread(name, MONO);
	for (u32 x = 0; x < text.rows; x++){
		for (u32 y = 0; y < text.cols; y++){
			if (text.get_at(x, y) < 128){
				src.set_at(x0 + x - 22, y0 + y, color, transparency);
			}
		}
	}
}
int cv::putText(Mat src, string in, u32 x0 , u32 y0, u32 color, u32 distance_between_char, u8 transparency){

	char ch[256];
	strncpy(ch, in.c_str(), sizeof(ch));
	ch[sizeof(ch) - 1] = 0;
	int x_offset = 0;
	for (int i = 0; i < 256 ; i++){
		switch (ch[i]){
		case _CHAR_1_CODE:
			putChar(src, _CHAR_1 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_2_CODE:
			putChar(src, _CHAR_2 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_3_CODE:
			putChar(src, _CHAR_3 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_4_CODE:
			putChar(src, _CHAR_4 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_5_CODE:
			putChar(src, _CHAR_5 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_6_CODE:
			putChar(src, _CHAR_6 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_7_CODE:
			putChar(src, _CHAR_7 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_8_CODE:
			putChar(src, _CHAR_8 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_9_CODE:
			putChar(src, _CHAR_9 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_10_CODE:
			putChar(src, _CHAR_10 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_11_CODE:
			putChar(src, _CHAR_11 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_12_CODE:
			putChar(src, _CHAR_12 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_13_CODE:
			putChar(src, _CHAR_13 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_14_CODE:
			putChar(src, _CHAR_14 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_15_CODE:
			putChar(src, _CHAR_15 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_16_CODE:
			putChar(src, _CHAR_16 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_17_CODE:
			putChar(src, _CHAR_17 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_18_CODE:
			putChar(src, _CHAR_18 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_19_CODE:
			putChar(src, _CHAR_19 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_20_CODE:
			putChar(src, _CHAR_20 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_21_CODE:
			putChar(src, _CHAR_21 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_22_CODE:
			putChar(src, _CHAR_22 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_23_CODE:
			putChar(src, _CHAR_23 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_24_CODE:
			putChar(src, _CHAR_24 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_25_CODE:
			putChar(src, _CHAR_25 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_26_CODE:
			putChar(src, _CHAR_26 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_27_CODE:
			putChar(src, _CHAR_27 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_28_CODE:
			putChar(src, _CHAR_28 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_29_CODE:
			putChar(src, _CHAR_29 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_30_CODE:
			putChar(src, _CHAR_30 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_31_CODE:
			putChar(src, _CHAR_31 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_32_CODE:
			putChar(src, _CHAR_32 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_33_CODE:
			putChar(src, _CHAR_33 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_34_CODE:
			putChar(src, _CHAR_34 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_35_CODE:
			putChar(src, _CHAR_35 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_36_CODE:
			putChar(src, _CHAR_36 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_37_CODE:
			putChar(src, _CHAR_37 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_38_CODE:
			putChar(src, _CHAR_38 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_39_CODE:
			putChar(src, _CHAR_39 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_40_CODE:
			putChar(src, _CHAR_40 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_41_CODE:
			putChar(src, _CHAR_41 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_42_CODE:
			putChar(src, _CHAR_42 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_43_CODE:
			putChar(src, _CHAR_43 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_44_CODE:
			putChar(src, _CHAR_44 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_45_CODE:
			putChar(src, _CHAR_45 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_46_CODE:
			x_offset += 5;
			putChar(src, _CHAR_46 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_47_CODE:
			putChar(src, _CHAR_47 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_48_CODE:
			putChar(src, _CHAR_48 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_49_CODE:
			putChar(src, _CHAR_49 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_50_CODE:
			putChar(src, _CHAR_50 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_51_CODE:
			putChar(src, _CHAR_51 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_52_CODE:
			putChar(src, _CHAR_52 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_53_CODE:
			putChar(src, _CHAR_53 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_54_CODE:
			putChar(src, _CHAR_54 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_55_CODE:
			putChar(src, _CHAR_55 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_56_CODE:
			putChar(src, _CHAR_56 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_57_CODE:
			putChar(src, _CHAR_57 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_58_CODE:
			putChar(src, _CHAR_58 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_59_CODE:
			putChar(src, _CHAR_59 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_60_CODE:
			putChar(src, _CHAR_60 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_61_CODE:
			putChar(src, _CHAR_61 , x0 + x_offset, y0, color, transparency);
			x_offset += 8;
			break;
		case _CHAR_62_CODE:
			putChar(src, _CHAR_62 , x0 + x_offset, y0, color, transparency);
			x_offset += 3;
			break;
		case _CHAR_63_CODE:
			putChar(src, _CHAR_63 , x0 + x_offset, y0, color, transparency);
			x_offset += 3;
			break;
		case _CHAR_64_CODE:
			putChar(src, _CHAR_64 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_65_CODE:
			putChar(src, _CHAR_65 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_66_CODE:
			putChar(src, _CHAR_66 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_67_CODE:
			putChar(src, _CHAR_67 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_68_CODE:
			putChar(src, _CHAR_68 , x0 + x_offset, y0, color, transparency);
			x_offset += 4;
			break;
		case _CHAR_69_CODE:
			putChar(src, _CHAR_69 , x0 + x_offset, y0, color, transparency);
			x_offset += 3;
			break;
		case _CHAR_70_CODE:
			putChar(src, _CHAR_70 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_71_CODE:
			putChar(src, _CHAR_71 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_72_CODE:
			putChar(src, _CHAR_72 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_73_CODE:
			putChar(src, _CHAR_73 , x0 + x_offset, y0, color, transparency);
			x_offset += 6;
			break;
		case _CHAR_74_CODE:
			putChar(src, _CHAR_74 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_75_CODE:
			putChar(src, _CHAR_75 , x0 + x_offset, y0, color, transparency);
			x_offset += 6;
			break;
		case _CHAR_76_CODE:
			putChar(src, _CHAR_76 , x0 + x_offset, y0, color, transparency);
			x_offset += 2;
			break;
		case _CHAR_77_CODE:
			putChar(src, _CHAR_77 , x0 + x_offset, y0, color, transparency);
			x_offset += 7;
			break;
		case _CHAR_78_CODE:
			putChar(src, _CHAR_78 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_79_CODE:
			putChar(src, _CHAR_79 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_80_CODE:
			putChar(src, _CHAR_80 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_81_CODE:
			putChar(src, _CHAR_81 , x0 + x_offset, y0, color, transparency);
			x_offset += 3;
			break;
		case _CHAR_82_CODE:
			putChar(src, _CHAR_82 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_83_CODE:
			putChar(src, _CHAR_83 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_84_CODE:
			putChar(src, _CHAR_84 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_85_CODE:
			putChar(src, _CHAR_85 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_86_CODE:
			putChar(src, _CHAR_86 , x0 + x_offset, y0, color, transparency);
			x_offset += 4;
			break;
		case _CHAR_87_CODE:
			putChar(src, _CHAR_87 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_88_CODE:
			putChar(src, _CHAR_88 , x0 + x_offset, y0, color, transparency);
			x_offset += 4;
			break;
		case _CHAR_89_CODE:
			putChar(src, _CHAR_89 , x0 + x_offset, y0, color, transparency);
			x_offset += 4;
			break;
		case _CHAR_90_CODE:
			putChar(src, _CHAR_90 , x0 + x_offset, y0, color, transparency);
			x_offset += 8;
			break;
		case _CHAR_91_CODE:
			putChar(src, _CHAR_91 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_92_CODE:
			putChar(src, _CHAR_92 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_93_CODE:
			putChar(src, _CHAR_93 , x0 + x_offset, y0, color, transparency);
			break;
		case _CHAR_94_CODE:
			putChar(src, _CHAR_94 , x0 + x_offset, y0, color, transparency);
			break;
		case 0: //.
			return i;
			break;

		}
		x_offset += distance_between_char;
	}
	return 256;
}

#include "xil_io.h"
#include "xparameters.h"
#include "tpg.hpp"
#include "../share/def.hpp"

tpg::tpg(int address){
	 this->address = address;
	 control_register =  address + 0x00;
	 active_height_register =  address + 0x10;
	 active_width_register =  address + 0x18;
	 background_pattern_id_register =  address + 0x20;
	 foreground_pattern_id_register =  address + 0x28;
	 motion_speed_register =  address + 0x38;
	 color_format_register =  address + 0x40;
	 box_size_register =  address + 0x78;
	 box_color_red_y_register =  address + 0x80;
	 box_color_red_u_register =  address + 0x88;
	 box_color_red_v_register =  address + 0x90;
	 zplate_hor_cntl_start_register =  address + 0x58;
	 zplate_hor_cntl_delta_register =  address + 0x60;
	 zplate_ver_cntl_start_register =  address + 0x68;
	 zplate_ver_cntl_delta_register =  address + 0x70;
}


tpg::~tpg()
{

}

void tpg::ap_start(){
	int control_reg = Xil_In32(control_register);
	Xil_Out32(control_register , 0x81);//(control_reg | 0x1));

}

void tpg::ap_stop(){
	int control_reg = Xil_In32(control_register);
	Xil_Out32(control_register , (control_reg & 0xFFFFFFFE));
}
void tpg::set_zone_plat_default_params(){
	Xil_Out32(zplate_hor_cntl_start_register, 100);
	Xil_Out32(zplate_hor_cntl_delta_register, 100);
	Xil_Out32(zplate_ver_cntl_start_register, 100);
	Xil_Out32( zplate_ver_cntl_delta_register, 100);
}
void tpg::auto_restart(int status ){
	int control_reg = Xil_In32( control_register);
	if (status == ON_DEF){
		Xil_Out32( control_register , (control_reg | 0x80));
	}
	else if (status == OFF_DEF){
		Xil_Out32( control_register , (control_reg & 0xFFFFFF7F));
	}
}


void tpg::set_active_hight(int size ){
	Xil_Out32( active_height_register, size);
}


void tpg::set_active_width(int size ){
	Xil_Out32( active_width_register, size);
}


void tpg::set_background_pattern(TPG_BACKGROUND_PATTERN pattern ){
	Xil_Out32( background_pattern_id_register, (int)pattern);
}


void tpg::set_foreground_pattern(int pattern ){
	Xil_Out32( foreground_pattern_id_register, pattern);
}


void tpg::set_motion_speed(int speed ){
	Xil_Out32( motion_speed_register, speed);
}


void tpg::set_color_format(int format ){
	Xil_Out32( color_format_register, format);
}


void tpg::set_box_size(int size ){
	Xil_Out32( box_size_register, size);
}


void tpg::set_box_color(int* color ){
	Xil_Out32( box_color_red_y_register, color[0]);
	Xil_Out32( box_color_red_u_register, color[1]);
	Xil_Out32( box_color_red_v_register, color[2]);
}



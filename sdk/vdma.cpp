#include "vdma.hpp"
vdma::vdma(u32 address){
	this->address = address;
	AD_VDMASR_MM2S = 0x04;
	AD_VDMASR_S2MM = 0x34;
	AD_VDMACR_MM2S = 0x00;
	AD_VDMACR_S2MM = 0x30;
	AD_BADDR0_MM2S = 0x5C;
	AD_BADDR1_MM2S = 0x60;
	AD_BADDR2_MM2S = 0x64;
	AD_BADDR3_MM2S = 0x68;
	AD_BADDR4_MM2S = 0x6C;
	AD_BAADR0_S2MM = 0xAC;
	AD_BAADR1_S2MM = 0xB0;
	AD_BAADR2_S2MM = 0xB4;
	AD_BAADR3_S2MM = 0xB8;
	AD_BAADR4_S2MM = 0xBC;
	AD_FRMDLY_MM2S = 0x58;
	AD_FRMDLY_S2MM = 0xA8;
	AD_PARK_PTR_REG = 0x28;
	AD_HSIZE_MM2S = 0x54;
	AD_HSIZE_S2MM = 0xA4;
	AD_VSIZE_MM2S = 0X50;
	AD_VSIZE_S2MM = 0XA0;
	AD_VERTICAL_FLIP = 0xEC;
	mm2s_active = 0;
	s2mm_active = 0;
	offset_mm2s = 0;
	offset_s2mm = 0;
	control_reg = 0x0001408b;
	active_buffer_reg = 0;
	mm2s_active_buffer = 0;
	s2mm_active_buffer = 0;
	vertical_flip_en = 0;
}

void vdma::enable_verical_flip(){
	vertical_flip_en = 1;
}
void vdma::disable_verical_flip(){
	vertical_flip_en = 0;
}
void vdma::reset(){
	mm2s_active = 0;
	s2mm_active = 0;
	offset_mm2s = 0;
	offset_s2mm = 0;
	control_reg = 0x0001408b;
	active_buffer_reg = 0;
	mm2s_active_buffer = 0;
	s2mm_active_buffer = 0;
//	Xil_Out32(address+ AD_VDMACR_MM2S, 4);
//	Xil_Out32(address+ AD_VDMACR_S2MM, 4);
}
vdma::~vdma(){

}
void vdma::set_s2mm_frame_buffer(u32 addrress, u32 no){
	s2mm_frame_buffer_address[no] = addrress;
}
void vdma::set_mm2s_frame_buffer(u32 addrress, u32 no){
	mm2s_frame_buffer_address[no] = addrress;
}
void vdma::set_s2mm_resolution(u32 h, u32 v, u32 stride){
	s2mm_h = h;
	s2mm_stride = stride;
	s2mm_v = v;
}
void vdma::set_mm2s_resolution(u32 h, u32 v, u32 stride){
	mm2s_h = h;
	mm2s_stride = stride;
	mm2s_v = v;
}

void vdma::active_s2mm_frame_buffer(u32 no){
	s2mm_active_buffer = no & 0x1F;
	control_reg = 0x00014089;
}
void vdma::active_mm2s_frame_buffer(u32 no){
	mm2s_active_buffer = no & 0x1F;
	control_reg = 0x00014089;
}
void vdma::apply(){
	active_buffer_reg = active_buffer_reg & 0xFFFFE0E0;
	active_buffer_reg = active_buffer_reg | mm2s_active_buffer;
	active_buffer_reg = active_buffer_reg | (s2mm_active_buffer<<8);
	Xil_Out32(address+ AD_PARK_PTR_REG, active_buffer_reg);

	Xil_Out32(address+ AD_VERTICAL_FLIP, vertical_flip_en);

	if (mm2s_active == 1)
	{
		Xil_Out32(address+ AD_VDMACR_MM2S, control_reg);
		Xil_Out32(address+ AD_BADDR0_MM2S, mm2s_frame_buffer_address[0] + offset_mm2s);
		Xil_Out32(address+ AD_BADDR1_MM2S, mm2s_frame_buffer_address[1] + offset_mm2s);
		Xil_Out32(address+ AD_BADDR2_MM2S, mm2s_frame_buffer_address[2] + offset_mm2s);
		Xil_Out32(address+ AD_BADDR3_MM2S, mm2s_frame_buffer_address[3] + offset_mm2s);
		Xil_Out32(address+ AD_BADDR4_MM2S, mm2s_frame_buffer_address[4] + offset_mm2s);
		Xil_Out32(address+ AD_FRMDLY_MM2S, mm2s_stride*byte_per_pixel);
		Xil_Out32(address+ AD_HSIZE_MM2S, mm2s_h*byte_per_pixel);
		Xil_Out32(address+ AD_VSIZE_MM2S, mm2s_v);
	}

	if(s2mm_active == 1)
	{
		Xil_Out32(address+ AD_VDMACR_S2MM, control_reg);
		Xil_Out32(address+ AD_BAADR0_S2MM, s2mm_frame_buffer_address[0] + offset_s2mm);
		Xil_Out32(address+ AD_BAADR1_S2MM, s2mm_frame_buffer_address[1] + offset_s2mm);
		Xil_Out32(address+ AD_BAADR2_S2MM, s2mm_frame_buffer_address[2] + offset_s2mm);
		Xil_Out32(address+ AD_BAADR3_S2MM, s2mm_frame_buffer_address[3] + offset_s2mm);
		Xil_Out32(address+ AD_BAADR4_S2MM, s2mm_frame_buffer_address[4] + offset_s2mm);
		Xil_Out32(address+ AD_FRMDLY_S2MM, s2mm_stride*byte_per_pixel);
		Xil_Out32(address+ AD_HSIZE_S2MM, s2mm_h*byte_per_pixel);
		Xil_Out32(address+ AD_VSIZE_S2MM, s2mm_v);
	}
}
void vdma::set_byte_per_pixel(u32 byte_per_pixel){
	this->byte_per_pixel = byte_per_pixel;
}
void vdma::set_mm2s_frame_bufffer_offset_address(int h, int v){
	offset_mm2s  = (mm2s_stride * v  + h) * byte_per_pixel;
}
void vdma::set_s2mm_frame_bufffer_offset_address(int h, int v){
	offset_s2mm  = (s2mm_stride * v  + h) * byte_per_pixel;
}
void vdma::set_mm2s_active(){
	mm2s_active = 1;
}
void vdma::set_s2mm_active(){
	s2mm_active = 1;
}

u32 vdma::get_mm2s_frame_buffer(){
	u32 reg = Xil_In32(address + AD_PARK_PTR_REG);
	return ((reg>>16) & 0x1F);
}
u32 vdma::get_s2mm_frame_buffer(){
	u32 reg = Xil_In32(address + AD_PARK_PTR_REG);
	return ((reg>>24) & 0x1F);
}

VDMA_STATUS vdma::mm2s_check_status(){
	Xil_Out32(address + AD_VDMASR_MM2S, 0xFFFFFFFF);
	u32 reg = Xil_In32(address + AD_VDMASR_MM2S);
	if ((reg & 0x01) == 1){
		return HALTED;
	} else {
		return RUNNING;
	}
}
VDMA_STATUS vdma::s2mm_check_status(){
	Xil_Out32(address + AD_VDMASR_S2MM, 0xFFFFFFFF);
	u32 reg = Xil_In32(address + AD_VDMASR_S2MM);
	if ((reg & 0x01) == 1){
		return HALTED;
	} else {
		return RUNNING;
	}
}

u32 vdma::mm2s_get_status_reg(){
	Xil_Out32(address + AD_VDMASR_MM2S, 0xFFFFFFFF);
	return Xil_In32(address + AD_VDMASR_MM2S);;
}
u32 vdma::s2mm_get_status_reg(){
	Xil_Out32(address + AD_VDMASR_S2MM, 0xFFFFFFFF);
	return Xil_In32(address + AD_VDMASR_S2MM);
}

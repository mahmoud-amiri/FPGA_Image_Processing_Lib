
#pragma once
#include "xil_types.h"
#include "xil_io.h"
enum VDMA_STATUS {RUNNING, HALTED};
class vdma {
private:
	u32 address;
	u32 mm2s_active;
	u32 s2mm_active;
	u32 mm2s_frame_buffer_address[5];
	u32 s2mm_frame_buffer_address[5];
	u32 s2mm_h;
	u32 s2mm_v;
	u32 s2mm_stride;
	u32 mm2s_h;
	u32 mm2s_v;
	u32 mm2s_stride;
	u32 byte_per_pixel;
	int offset_mm2s ;
	int offset_s2mm ;
	u32 s2mm_active_buffer;
	u32 mm2s_active_buffer;
	u32 control_reg;
	u32 active_buffer_reg;
	u32 vertical_flip_en;

	u32 AD_VDMACR_MM2S;
	u32 AD_VDMACR_S2MM;
	u32 AD_BADDR0_MM2S;
	u32 AD_BADDR1_MM2S;
	u32 AD_BADDR2_MM2S;
	u32 AD_BADDR3_MM2S;
	u32 AD_BADDR4_MM2S;
	u32 AD_BAADR0_S2MM;
	u32 AD_BAADR1_S2MM;
	u32 AD_BAADR2_S2MM;
	u32 AD_BAADR3_S2MM;
	u32 AD_BAADR4_S2MM;
	u32 AD_FRMDLY_MM2S;
	u32 AD_FRMDLY_S2MM;
	u32 AD_PARK_PTR_REG;
	u32 AD_HSIZE_MM2S;
	u32 AD_HSIZE_S2MM;
	u32 AD_VSIZE_MM2S;
	u32 AD_VSIZE_S2MM;
	u32 AD_VDMASR_MM2S;
	u32 AD_VDMASR_S2MM;
	u32 AD_VERTICAL_FLIP;

public:
	vdma(u32 address);
	~vdma();
	void apply();
	void reset();
	void set_mm2s_active();
	void set_s2mm_active();
	void set_byte_per_pixel(u32 byte_per_pixel);
	void set_mm2s_frame_bufffer_offset_address(int h, int v);
	void set_s2mm_frame_buffer(u32 addrress, u32 no);
	void set_mm2s_frame_buffer(u32 addrress, u32 no);
	void set_s2mm_resolution(u32 h, u32 v, u32 stride);
	void set_mm2s_resolution(u32 h, u32 v, u32 stride);
	void active_s2mm_frame_buffer(u32 no);
	void active_mm2s_frame_buffer(u32 no);
	u32 get_mm2s_frame_buffer();
	u32 get_s2mm_frame_buffer();
	VDMA_STATUS mm2s_check_status();
	VDMA_STATUS s2mm_check_status();
	u32 mm2s_get_status_reg();
	u32 s2mm_get_status_reg();
	void enable_verical_flip();
	void disable_verical_flip();
	void set_s2mm_frame_bufffer_offset_address(int h, int v);
};

#include "file_system_rw.hpp"

file_system_rw::file_system_rw(){

}
file_system_rw::~file_system_rw(){

}
u32 file_system_rw::write_file_system(int size,int src_address, int des_bulk_start_id){
	u32 status;
	int bulk_no = (size + 511) / 512;
	for (int i = 0; i < bulk_no; i++){
		status = xilSdWrite((u8*)(src_address + 512*i), (i + des_bulk_start_id), 1);
		if (status != XST_SUCCESS){
			xil_printf("[ERROR  ]: Error in MMCC writing, bulk id =  %d and ddr address = %d *#", i + des_bulk_start_id, src_address + 512*i);
		}
	}
	return status;
}
u32 file_system_rw::read_file_system(int size, int des_address, int src_bulk_start_id){
	u32 status;
	int bulk_no = (size + 511) / 512;
	for (int i = 0; i < bulk_no; i++){
		status = xilSdRead((u8*)(des_address + 512*i), (i + src_bulk_start_id), 1);
		if (status != XST_SUCCESS){
			xil_printf("[ERROR  ]: Error in MMCC reading, bulk id =  %d and ddr address = %d *#", i + src_bulk_start_id, des_address + 512*i);
		}
	}
	return status;
}

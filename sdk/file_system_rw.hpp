#pragma once
#include "../share/address.hpp"
#include "../platform/emmc.hpp"
class file_system_rw{
public:
	file_system_rw();
	~file_system_rw();
	u32 write_file_system(int size, int address, int bulk_start_id);
	u32 read_file_system(int size, int address, int bulk_start_id);
private:
};

#pragma once
#include "xvprocss.h"
class scaler{
public:
	scaler(u32 device_id);
	~scaler();
	void init();
	void set_input_resolution(u32 h, u32 v);
	void set_output_resolution(u32 h, u32 v);
	void set_scale_factor(float scale_factor_width, float scale_factor_height);
	void set_video_format(XVidC_ColorFormat f);
private:
	u32 device_id;
	XVprocSs Vproc_ptr;
	XVidC_VideoStream Stream_in;
	XVidC_VideoStream Stream_out;
};

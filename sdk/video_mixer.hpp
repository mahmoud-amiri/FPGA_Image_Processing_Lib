#pragma once
#include "xv_mix_l2.h"
#include "../share/address.hpp"
#include "xil_types.h"
enum LAYER_NAME {TPG_BACKGROUND = 0, OVERLAY = 3, CAMERA_DAY = 1,  CAMERA_IR = 2};

class video_mixer{
public:
	video_mixer(u32 device_id);
	~video_mixer();
	void init();
	void enable_layer(LAYER_NAME l);
	void set_transparency(LAYER_NAME l, int t);
	void disable_layer(LAYER_NAME l);
	void set_layer_window(LAYER_NAME l, u32 x, u32 y, u32 w, u32 h);
private:
	u32 device_id;
	XV_Mix_l2  mix;
	XVidC_ColorFormat Cfmt;
	XVidC_VideoStream VidStream;
	XVidC_VideoTiming const *TimingPtr;
	XVidC_VideoWindow MixLayerConfig[4] =
	{// X   Y     W    H
			{200,  0,  1520, 1079}, //Layer 1
			{200,  0,  1520, 1079}, //Layer 2
			{0,  0,  1919, 1079}, //Layer 3

	};
};
//void init_video_mixer();

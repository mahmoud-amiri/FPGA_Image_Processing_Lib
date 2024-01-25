#include "scaler.hpp"
scaler::scaler(u32 device_id){
	this->device_id = device_id;
}
scaler::~scaler(){

}
void scaler::init(){
	XVprocSs_Config *VprocSsConfigPtr;

	VprocSsConfigPtr = XVprocSs_LookupConfig(device_id);
	Vproc_ptr.UsrDelayUs = 0;
	XVprocSs_CfgInitialize(&Vproc_ptr, VprocSsConfigPtr, VprocSsConfigPtr->BaseAddress);

	const XVidC_VideoTimingMode *VmPtrIn, *VmPtrOut ;
	VmPtrIn=XVidC_GetVideoModeData(XVIDC_VM_1920x1080_60_P);
	Stream_in.Timing = VmPtrIn->Timing;
	Stream_in.VmId = VmPtrIn->VmId;
	Stream_in.ColorFormatId = XVIDC_CSF_YCRCB_444;
	Stream_in.ColorDepth = (XVidC_ColorDepth) Vproc_ptr.Config.ColorDepth;
	Stream_in.PixPerClk = (XVidC_PixelsPerClock) Vproc_ptr.Config.PixPerClock;
	Stream_in.FrameRate = VmPtrIn->FrameRate;
	Stream_in.IsInterlaced = 0;

	VmPtrOut=XVidC_GetVideoModeData(XVIDC_VM_1920x1080_60_P);
	Stream_out.Timing = VmPtrOut->Timing;
	Stream_out.VmId = VmPtrOut->VmId;
	Stream_out.ColorFormatId = XVIDC_CSF_YCRCB_444;
	Stream_out.ColorDepth = (XVidC_ColorDepth)Vproc_ptr.Config.ColorDepth;
	Stream_out.PixPerClk = (XVidC_PixelsPerClock)Vproc_ptr.Config.PixPerClock;
	Stream_out.FrameRate = VmPtrOut->FrameRate;
	Stream_out.IsInterlaced = 0;

	XVprocSs_SetVidStreamIn(&Vproc_ptr, &Stream_in);
	XVprocSs_SetVidStreamOut(&Vproc_ptr, &Stream_out);
	XVprocSs_SetSubsystemConfig(&Vproc_ptr);

}
void scaler::set_input_resolution(u32 h, u32 v){
	Stream_in.Timing.HActive = h;
	Stream_in.Timing.VActive = v;
	XVprocSs_SetVidStreamIn(&Vproc_ptr, &Stream_in);
	XVprocSs_SetSubsystemConfig(&Vproc_ptr);
}
void scaler::set_output_resolution(u32 h, u32 v){
	Stream_out.Timing.HActive = h;
	Stream_out.Timing.VActive = v;
	XVprocSs_SetVidStreamOut(&Vproc_ptr, &Stream_out);
	XVprocSs_SetSubsystemConfig(&Vproc_ptr);
}
void scaler::set_video_format(XVidC_ColorFormat f){
	Stream_in.ColorFormatId = f;
	Stream_out.ColorFormatId = f;
	XVprocSs_SetVidStreamIn(&Vproc_ptr, &Stream_in);
	XVprocSs_SetVidStreamOut(&Vproc_ptr, &Stream_out);
	XVprocSs_SetSubsystemConfig(&Vproc_ptr);
}
void scaler::set_scale_factor(float scale_factor_width, float scale_factor_height){
	u32 h_out;
	u32 v_out;
	u32 h_in;
	u32 v_in;
	h_in = Stream_in.Timing.HActive;
	v_in = Stream_in.Timing.VActive;
	h_out = (u32)((float)h_in * scale_factor_width);
	v_out = (u32)((float)v_in * scale_factor_height);
	Stream_out.Timing.HActive = h_out;
	Stream_out.Timing.VActive = v_out;
	XVprocSs_SetVidStreamOut(&Vproc_ptr, &Stream_out);
	XVprocSs_SetSubsystemConfig(&Vproc_ptr);
}

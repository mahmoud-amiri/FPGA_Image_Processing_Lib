#include "video_mixer.hpp"

video_mixer::video_mixer(u32 device_id){
	this->device_id = device_id;
}
video_mixer::~video_mixer(){

}
void video_mixer::init(){
	XVMix_Initialize(&mix, device_id);
	XVMix_GetLayerColorFormat(&mix, XVMIX_LAYER_MASTER, &Cfmt);
	VidStream.PixPerClk     = XVIDC_PPC_1;
	VidStream.ColorFormatId = Cfmt;
	VidStream.ColorDepth    = XVIDC_BPC_8;
	VidStream.VmId = XVIDC_VM_1920x1080_60_P;
	TimingPtr = XVidC_GetTimingInfo(VidStream.VmId);
	VidStream.Timing = *TimingPtr;
	VidStream.FrameRate = XVidC_GetFrameRate(VidStream.VmId);
	int NumLayers,  Status;
	XVMix_LayerDisable(&mix, XVMIX_LAYER_MASTER);
	XVMix_SetVidStream(&mix, &VidStream);
	NumLayers = XVMix_GetNumLayers(&mix);
	Status = XVMix_SetLayerBufferAddr(&mix, XVMIX_LAYER_3, OVERLAY_FINAL_BUFF_ADDRESS);
	XVMix_SetBackgndColor(&mix, XVMIX_BKGND_BLUE, VidStream.ColorDepth);
	XVMix_LayerEnable(&mix, XVMIX_LAYER_MASTER);
	XVMix_InterruptDisable(&mix);
	XVMix_Start(&mix);
}
void video_mixer::enable_layer(LAYER_NAME l){
	int layerIndex;
	XVidC_VideoWindow Win;
	layerIndex = l;
	mix.Layer[l].ColorFormat = XVIDC_CSF_YCRCB_444;
	Win = MixLayerConfig[layerIndex-1];
	XVMix_SetLayerWindow(&mix, (XVMix_LayerId)layerIndex, &Win, 1920*4);
	if(XVMix_IsAlphaEnabled(&mix, (XVMix_LayerId)layerIndex)) {
		XVMix_SetLayerAlpha(&mix, (XVMix_LayerId)layerIndex, 128);//XVMIX_ALPHA_MAX);
	}
	XVMix_LayerEnable(&mix, (XVMix_LayerId)layerIndex);
}
void video_mixer::disable_layer(LAYER_NAME l){
	XVMix_LayerDisable(&mix, (XVMix_LayerId)l);
}
void video_mixer::set_transparency(LAYER_NAME l, int t){
	XVMix_SetLayerAlpha(&mix, (XVMix_LayerId)l, t);
}
void video_mixer::set_layer_window(LAYER_NAME l, u32 x, u32 y, u32 w, u32 h){
	XVidC_VideoWindow win;
	win.Height = h;
	win.Width = w;
	win.StartX = x;
	win.StartY = y;
	XVMix_SetLayerWindow(&mix, (XVMix_LayerId)l, &win, 1920*4);
}

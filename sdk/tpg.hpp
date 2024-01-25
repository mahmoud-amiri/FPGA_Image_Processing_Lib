#pragma once
#define ON_DEF 1

#define OFF_DEF 0
enum TPG_BACKGROUND_PATTERN{TPG_BLACK = 7, TPG_WHITE = 8 ,TPG_RED = 4, TPG_GREEN = 5, TPG_BLUE = 6, TPG_COLOR_BAR = 9, TPG_ZONE_PLATE = 10};
class tpg {
public:
	tpg(int address);
	~tpg();
	void ap_start();
	void ap_stop();
	void auto_restart(int status );
	void set_active_hight(int size );
	void set_active_width(int size );
	void set_background_pattern(TPG_BACKGROUND_PATTERN pattern );
	void set_foreground_pattern(int pattern );
	void set_motion_speed(int speed );
	void set_color_format(int format );
	void set_box_size(int size );
	void set_box_color(int* color );
	void set_zone_plat_default_params();
private:
	int	address;
	int control_register ;
	int active_height_register ;
	int active_width_register ;
	int background_pattern_id_register ;
	int foreground_pattern_id_register ;
	int motion_speed_register ;
	int color_format_register ;
	int box_size_register ;
	int box_color_red_y_register ;
	int box_color_red_u_register ;
	int box_color_red_v_register ;
	int zplate_hor_cntl_start_register	;
	int zplate_hor_cntl_delta_register	;
	int zplate_ver_cntl_start_register	;
	int zplate_ver_cntl_delta_register ;

};

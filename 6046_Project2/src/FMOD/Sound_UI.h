#pragma once
#include "../globalOpenGL.h"//"OpenGL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"
#include "FmodManager.h"
#include "imgui/imgui.h"
#include <vector>

#define MASTER_CH	"Master"
#define BGM_CH1		"BGM1"
#define BGM_CH2		"BGM2"
#define BGM_CH3		"BGM3"
#define	FX1_CH		"fx1"
#define FX2_CH		"fx2"

#define DSP_ECHO			"echo"
#define DSP_DISTORTION		"dist"
#define DSP_CHORUS			"chorus"
#define DSP_LOWPASSFILTER	"lpf"
#define DSP_HIGHPASSFILTER	"hpf"
#define DSP_FADER			"fader"
#define DSP_PITCHSHIFT		"pitch"
#define DSP_FLANGE			"flange"
#define DSP_TREMELO			"tremolo"

class Sound_UI
{
public:
	Sound_UI(FModManager* fmod,cXML* a_xml);
	~Sound_UI();
	
	bool iscompress[3];
	bool dspenable[9];

	void render();

protected:
	bool MyKnob(const char* label, float* p_value, float v_min, float v_max);
	void MStoMinSec(const unsigned int ms, unsigned int* min, unsigned int* sec);
	void mastervolume(const char *id,const ImVec2 position, float* curr_music_volume, float* curr_music_pan);
	void musicvolume(const char* id, const ImVec2 position, float* curr_music_volume);
	void fxvolume(const char* id, const ImVec2 position);
	void infotext(const char* id, const ImVec2 position, float* curr_music_volume, float* curr_music_pan);
	void bgmload(std::string CH_name,std::string id);
	void dsptab(const char* id, const ImVec2 position);



	std::string file_name_;
	std::string file_format_;
	std::string file_type_;
	int channel_;
	int bps_; //bits per sample
	float freq;
	float freq_original;
	float playspeed;
	int priority;
	unsigned int music_length;
	unsigned int music_length_min;
	unsigned int music_length_sec;
	unsigned int music_pos;
	unsigned int music_pos_min;
	unsigned int music_pos_sec;
	int loading_flag;
};


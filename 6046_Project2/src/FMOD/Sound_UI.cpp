#include "Sound_UI.h"

FModManager* fmodmanager_;
cXML* xml_;

Sound_UI::Sound_UI(FModManager* fmod,cXML* a_xml)
{
	fmodmanager_ = fmod;
	xml_ = a_xml;
	for (size_t i = 0; i < 3; i++)
	{
		iscompress[i] = false;
	}
	for (size_t i = 0; i < 9; i++)
	{
		dspenable[i] = false;
	}
	channel_ = 0;
	bps_ = 0;
	freq = 0.f;
	freq_original = 0.f;
	playspeed = 1.f;
	priority = 0;
	music_length = 0;
	music_length_min = 0;
	music_length_sec = 0;
	music_pos = 0;
	music_pos_min = 0;
	music_pos_sec = 0;
	loading_flag = 0;
}

Sound_UI::~Sound_UI()
{
}

void Sound_UI::render()
{
	float curr_music_volume;
	float curr_music_pan;

	//setup ui structure
	ImGui::Begin("Audio Settings");
	ImGui::BeginGroup();
	ImGui::BeginChild("##BGM1", ImVec2(450, 65),true);
	
	
	{
		
		ImGui::Text("BGM1: %s ",xml_->my_music[0].fname.c_str());
		ImGui::SameLine();
		ImGui::Checkbox("compress##CMPSS1", &iscompress[0]);
		ImGui::SameLine();
		if (ImGui::Button("Load##BGM1"))
		{
			fmodmanager_->stop_sound(BGM_CH1);
			fmodmanager_->stop_sound(BGM_CH2);
			fmodmanager_->stop_sound(BGM_CH3);
			fmodmanager_->remove_sound("bgm1");
			fmodmanager_->create_sound("bgm1", xml_->my_music[0], FMOD_LOOP_NORMAL, iscompress[0]);
			fmodmanager_->play_sound("bgm1", BGM_CH1);
			fmodmanager_->get_sound_name("bgm1", &file_name_);
			fmodmanager_->get_sound_format("bgm1", &file_type_, &file_format_, &channel_, &bps_);
			fmodmanager_->get_sound_defualt("bgm1", &freq, &priority);
			freq_original = freq;
			fmodmanager_->get_sound_lengh("bgm1", &music_length);
			MStoMinSec(music_length, &music_length_min, &music_length_sec);
			loading_flag = 1;
		}

	}
	ImGui::EndChild();
	ImGui::BeginChild("##BGM2", ImVec2(450, 65), true);
	{
		ImGui::Text("BGM2: %s ", xml_->my_music[1].fname.c_str());
		ImGui::SameLine();
		ImGui::Checkbox("compress##CMPSS2", &iscompress[1]);
		ImGui::SameLine();
		if (ImGui::Button("Load##BGM2"))
		{	
			fmodmanager_->stop_sound(BGM_CH1);
			fmodmanager_->stop_sound(BGM_CH2);
			fmodmanager_->stop_sound(BGM_CH3);
			fmodmanager_->remove_sound("bgm2");
			fmodmanager_->create_sound("bgm2", xml_->my_music[1], FMOD_LOOP_NORMAL, iscompress[1]);
			fmodmanager_->play_sound("bgm2", BGM_CH2);
			fmodmanager_->get_sound_name("bgm2", &file_name_);
			fmodmanager_->get_sound_format("bgm2", &file_type_, &file_format_, &channel_, &bps_);
			fmodmanager_->get_sound_defualt("bgm2", &freq, &priority);
			freq_original = freq;
			fmodmanager_->get_sound_lengh("bgm2", &music_length);
			MStoMinSec(music_length, &music_length_min, &music_length_sec);
			loading_flag = 2;
		}

	}
	ImGui::EndChild();
	ImGui::BeginChild("##BGM3", ImVec2(450, 65), true);
	{
		ImGui::Text("BGM3: %s ", xml_->my_music[2].fname.c_str());
		ImGui::SameLine();
		ImGui::Checkbox("compress##CMPSS3", &iscompress[2]);
		ImGui::SameLine();
		if (ImGui::Button("Load##BGM3"))
		{
			fmodmanager_->stop_sound(BGM_CH1);
			fmodmanager_->stop_sound(BGM_CH2);
			fmodmanager_->stop_sound(BGM_CH3);
			fmodmanager_->remove_sound("bgm3");
			fmodmanager_->create_sound("bgm3", xml_->my_music[2], FMOD_LOOP_NORMAL, iscompress[2]);
			fmodmanager_->play_sound("bgm3", BGM_CH3);
			fmodmanager_->get_sound_name("bgm3", &file_name_);
			fmodmanager_->get_sound_format("bgm3", &file_type_, &file_format_, &channel_, &bps_);
			fmodmanager_->get_sound_defualt("bgm3", &freq, &priority);
			freq_original = freq;
			fmodmanager_->get_sound_lengh("bgm3", &music_length);
			MStoMinSec(music_length, &music_length_min, &music_length_sec);
			loading_flag = 3;
		}

	}
	ImGui::EndChild();
	//ImGui::EndGroup();

	//ImGui::SameLine();

	//DSP tab
	//dsptab("##dsp-tools", ImVec2(0, 200));


	////master volume
	mastervolume("Master_volume_ctrl", ImVec2(120, 140), &curr_music_volume, &curr_music_pan);
	
		ImGui::SameLine();
	//master pitch
	{
		ImGui::BeginChild("Master_pitch_ctrl", ImVec2(100, 140), true);
		{
			FModManager::CHgroup* channel_group;
			if (!fmodmanager_->find_channel_group(MASTER_CH, &channel_group))
			{
				//cannot find channel group
				//do something...
			}

			float current_pitch;
			channel_group->group_ptr->getPitch(&current_pitch);
			ImGui::VSliderFloat("##master pitch (no dsp)", ImVec2(30, 105), &current_pitch, 0.5f, 2.0f, "%.2f");
			ImGui::Text("master pitch");
			//ImGui::SliderFloat("master pitch (no dsp)", &current_pitch, 0.5f, 2.0f, "%.2f");
			channel_group->group_ptr->setPitch(current_pitch);
		}
		ImGui::EndChild();
		//ImGui::EndChild();
	}

	ImGui::SameLine();

	//music volume
	musicvolume("Music_volume_ctrl", ImVec2(120, 140), &curr_music_volume);

	ImGui::SameLine();

	//FX volume
	fxvolume("FX_volume_ctrl", ImVec2(85, 140));
	ImGui::EndGroup();

	ImGui::SameLine();

	//DSP tab
	dsptab("##dsp-tools", ImVec2(0, 350));

	//info 
	infotext("##info", ImVec2(0, 150), &curr_music_volume, &curr_music_pan);

	ImGui::End();

}
// ocornut (2016) https://github.com/ocornut/imgui/issues/942#issuecomment-268369298
bool Sound_UI::MyKnob(const char* label, float* p_value, float v_min, float v_max)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	float radius_outer = 20.0f;
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 center = ImVec2(pos.x + radius_outer, pos.y + radius_outer);
	float line_height = ImGui::GetTextLineHeight();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float ANGLE_MIN = 3.141592f * 0.75f;
	float ANGLE_MAX = 3.141592f * 2.25f;

	ImGui::InvisibleButton(label, ImVec2(radius_outer * 2, radius_outer * 2 + line_height + style.ItemInnerSpacing.y));
	bool value_changed = false;
	bool is_active = ImGui::IsItemActive();
	bool is_hovered = ImGui::IsItemActive();
	if (is_active && io.MouseDelta.x != 0.0f)
	{
		float step = (v_max - v_min) / 200.0f;
		*p_value += io.MouseDelta.x * step;
		if (*p_value < v_min) *p_value = v_min;
		if (*p_value > v_max) *p_value = v_max;
		value_changed = true;
	}

	float t = (*p_value - v_min) / (v_max - v_min);
	float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
	float angle_cos = cosf(angle), angle_sin = sinf(angle);
	float radius_inner = radius_outer * 0.40f;
	draw_list->AddCircleFilled(center, radius_outer, ImGui::GetColorU32(ImGuiCol_FrameBg), 16);
	draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - 2), center.y + angle_sin * (radius_outer - 2)), ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);
	draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
	draw_list->AddText(ImVec2(pos.x, pos.y + radius_outer * 2 + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), label);

	if (is_active || is_hovered)
	{
		ImGui::SetNextWindowPos(ImVec2(pos.x - style.WindowPadding.x, pos.y - line_height - style.ItemInnerSpacing.y - style.WindowPadding.y));
		ImGui::BeginTooltip();
		ImGui::Text("%.3f", *p_value);
		ImGui::EndTooltip();
	}

	return value_changed;
}

void Sound_UI::MStoMinSec(const unsigned int ms, unsigned int* min, unsigned int* sec)
{
	*min = ((ms / (1000 * 60)) % 60);
	*sec = (ms / 1000) % 60;
}

void Sound_UI::mastervolume(const char *id, const ImVec2 position,float* curr_music_volume,float* curr_music_pan)
{

	ImGui::BeginChild(id, position, true);
	FModManager::CHgroup* channel_group;
	fmodmanager_->find_channel_group(MASTER_CH, &channel_group);

	float current_volume;
	bool volume_enabled;
	fmodmanager_->get_channel_vol(MASTER_CH, &current_volume);
	fmodmanager_->get_channel_group_enabled(MASTER_CH, &volume_enabled);

	current_volume *= 100;
	*curr_music_volume = current_volume;
	ImGui::Checkbox("enable##master_volume", &volume_enabled);
	MyKnob("master volume", &current_volume, 0.0f, 100.0f);
	//ImGui::SliderFloat("master volume", &current_volume, 0.0f, 100.0f, "%.0f");
	current_volume /= 100;


	fmodmanager_->set_channel_vol(MASTER_CH, current_volume);
	//ImGui::SameLine();

	fmodmanager_->set_channel_group_enabled(MASTER_CH, volume_enabled);

	//master pan
	float pan;
	fmodmanager_->get_channel_group_pan(MASTER_CH, &pan);

	channel_group->current_pan = pan;
	*curr_music_pan = pan;
	ImGui::SliderFloat("##master pan", &channel_group->current_pan, -1.0f, 1.0f, "%.2f");
	ImGui::Text("master pan");
	fmodmanager_->set_channel_group_pan(MASTER_CH, channel_group->current_pan);
	ImGui::EndChild();

}

void Sound_UI::musicvolume(const char* id, const ImVec2 position, float* curr_music_volume)
{
	ImGui::BeginChild(id, position, true);

	FModManager::CHgroup* channel_group;
	bool volume_enabled;
	float current_volume;

	fmodmanager_->find_channel_group(BGM_CH1, &channel_group);
	fmodmanager_->get_channel_vol(BGM_CH1, &current_volume);	
	fmodmanager_->get_channel_group_enabled(BGM_CH1, &volume_enabled);

	current_volume *= 100;
	if (*curr_music_volume > current_volume)
	{
		*curr_music_volume = current_volume;
	}

	ImGui::Checkbox("enable##music_volume", &volume_enabled);
	MyKnob("music volume", &current_volume, 0.0f, 100.0f);
	//ImGui::SliderFloat("music volume", &current_volume, 0.0f, 100.0f, "%.0f");
	current_volume /= 100;

	fmodmanager_->set_channel_vol(BGM_CH1, current_volume);
	fmodmanager_->set_channel_group_enabled(BGM_CH1, volume_enabled);

	//music pan //todo -> playback speed by freq

	fmodmanager_->get_channel_freq(BGM_CH1, &freq);
	ImGui::SliderFloat("##music pan", &playspeed, -1.f, 3.0f, "%.2f");
	ImGui::Text("playback speed");
	freq = freq_original* playspeed;

	fmodmanager_->set_channel_freq(BGM_CH1, freq);
	
	
	ImGui::EndChild();
}


void Sound_UI::fxvolume(const char* id, const ImVec2 position)
{
	ImGui::BeginChild(id, position, true);

	FModManager::CHgroup* channel_group;

	fmodmanager_->find_channel_group(FX1_CH, &channel_group);

	float current_volume;
	bool volume_enabled;

	fmodmanager_->get_channel_vol(FX1_CH, &current_volume);
	fmodmanager_->get_channel_group_enabled(FX1_CH, &volume_enabled);

	current_volume *= 100;
	ImGui::Checkbox("enable##fx_volume", &volume_enabled);
	MyKnob("fx volume", &current_volume, 0.0f, 100.0f);
	//ImGui::SliderFloat("fx volume", &current_volume, 0.0f, 100.0f, "%.0f");
	current_volume /= 100;

	fmodmanager_->set_channel_vol(FX1_CH, current_volume);
	fmodmanager_->set_channel_group_enabled(FX1_CH, volume_enabled);

	ImGui::EndChild();
}

void Sound_UI::infotext(const char* id, const ImVec2 position, float* curr_music_volume, float* curr_music_pan)
{
	ImGui::BeginChild(id, position, true);
	{
		std::string curCH;
		switch (loading_flag)
		{
		case 1:
			curCH = BGM_CH1;
			break;
		case 2:
			curCH = BGM_CH2;
			break;
		case 3:
			curCH = BGM_CH3;
			break;
		default:
			break;
		}
		ImGui::Text("Name: %s", file_name_.c_str());
		ImGui::Text("Format: %s", file_format_.c_str());
		ImGui::Text("Type: %s", file_type_.c_str());
		ImGui::Text("Frequency: %.0f", freq);
		fmodmanager_->get_playback_pos(curCH, &music_pos);
		MStoMinSec(music_pos, &music_pos_min, &music_pos_sec);
		//ImGui::Text("Length: %02d:%02d/%02d:%02d", (int)music_pos_min, (int)music_pos_sec, (int)music_length_min, (int)music_length_sec);
		ImGui::Text("Length: ");
		ImGui::SameLine();
		char buf[32];
		float progress = 0.f;
		if (music_length != 0)
		{
			progress = (float)music_pos / (float)music_length;
		}
		sprintf_s(buf, "%02d:%02d/%02d:%02d", music_pos_min, music_pos_sec, music_length_min, music_length_sec);
		ImGui::ProgressBar(progress, ImVec2(150, 15), buf);
		ImGui::Text("Music Volume: %.02f", *curr_music_volume);
		ImGui::Text("Music Balance: %.02f", *curr_music_pan);
	}
	ImGui::EndChild();
}

void Sound_UI::dsptab(const char* id, const ImVec2 position)
{
	ImGui::BeginChild(id, position, true);

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("DSPTabBar", tab_bar_flags))

	{
		switch (loading_flag)
		{
		case 1:
			if (ImGui::BeginTabItem("ECHO"))
			{
				static bool enable;
				static float ech_dly = 500;
				static float ech_feedbck = 50;
				static float ech_drylv = 0;
				static float ech_wetlv = 0;
				static bool dsp_enable_flag =false;
				//todo read and add dsp
				ImGui::Checkbox("enable##DSP_echo_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
					//fmodmanager_->remove_dsp(BGM_CH1, DSP_ECHO);
				}
			
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_ECHO, 0, &ech_dly, NULL, NULL);
				ImGui::VSliderFloat("##echo_dly", ImVec2(30, 90), &ech_dly, 1, 5000,"");
				fmodmanager_->set_dsp_param(DSP_ECHO, 0, ech_dly);
				ImGui::Text("%4.0f", ech_dly);
				ImGui::Text("Delay");
				ImGui::EndGroup();

				ImGui::SameLine(60,10);
				
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_ECHO, 1, &ech_feedbck, NULL, NULL);
				ImGui::VSliderFloat("##echo_feedbck", ImVec2(30, 90), &ech_feedbck, 0, 100, "");
				fmodmanager_->set_dsp_param(DSP_ECHO, 1, ech_feedbck);
				ImGui::Text("%.2f", ech_feedbck);
				ImGui::Text("Feedback");
				ImGui::EndGroup();

				ImGui::SameLine(120,10);
				
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_ECHO, 2, &ech_drylv, NULL, NULL);
				ImGui::VSliderFloat("##echo_drylv", ImVec2(30, 90), &ech_drylv, -80, 10, "");
				fmodmanager_->set_dsp_param(DSP_ECHO, 2, ech_drylv);
				ImGui::Text("%.2f", ech_drylv);
				ImGui::Text("DryLevel");
				ImGui::EndGroup();

				ImGui::SameLine(180,10);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_ECHO, 3, &ech_wetlv, NULL, NULL);
				ImGui::VSliderFloat("##echo_wetlv", ImVec2(30, 90), &ech_wetlv, -80, 10, "");
				fmodmanager_->set_dsp_param(DSP_ECHO, 3, ech_wetlv);
				ImGui::Text("%.2f", ech_wetlv);
				ImGui::Text("WetLevel");
				ImGui::EndGroup();

				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH1, DSP_ECHO);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH1, DSP_ECHO);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}

			if (ImGui::BeginTabItem("Distortion"))
			{
				static bool enable;
				static float distlv = 0.5f;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_dist_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_DISTORTION, 0, &distlv, NULL, NULL);
				ImGui::VSliderFloat("##dist_lv", ImVec2(30, 90), &distlv, 0, 1, "");
				fmodmanager_->set_dsp_param(DSP_DISTORTION, 0, distlv);
				ImGui::Text("%.2f", distlv);
				ImGui::Text("distortion level");
				ImGui::EndGroup();

				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH1, DSP_DISTORTION);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH1, DSP_DISTORTION);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}

			if (ImGui::BeginTabItem("CHORUS"))
			{
				static bool enable;
				static float chr_mix = 50.f;
				static float chr_rate = 0.8f;
				static float chr_depth = 3.f;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_chor_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_CHORUS, 0, &chr_mix, NULL, NULL);
				ImGui::VSliderFloat("##chr_mix", ImVec2(30, 90), &chr_mix, 0, 100, "");
				fmodmanager_->set_dsp_param(DSP_CHORUS, 0, chr_mix);
				ImGui::Text("%.2f", chr_mix);
				ImGui::Text("Mix");
				ImGui::EndGroup();

				ImGui::SameLine(60, 10);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_CHORUS, 1, &chr_rate, NULL, NULL);
				ImGui::VSliderFloat("##chr_rate", ImVec2(30, 90), &chr_rate, 0, 20, "");
				fmodmanager_->set_dsp_param(DSP_CHORUS, 1, chr_rate);
				ImGui::Text("%.2f", chr_rate);
				ImGui::Text("Rate");
				ImGui::EndGroup();

				ImGui::SameLine(120, 10);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_CHORUS, 2, &chr_depth, NULL, NULL);
				ImGui::VSliderFloat("##chr_depth", ImVec2(30, 90), &chr_depth, 0, 100, "");
				fmodmanager_->set_dsp_param(DSP_CHORUS, 2, chr_depth);
				ImGui::Text("%.2f", chr_depth);
				ImGui::Text("Depth");
				ImGui::EndGroup();

				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH1, DSP_CHORUS);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH1, DSP_CHORUS);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}
			break;
		case 2:
			if (ImGui::BeginTabItem("LPF"))
			{
				static bool enable;
				static float cutoff = 5000.f;
				static float resonance = 1.f;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_LPF_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_LOWPASSFILTER, 0, &cutoff, NULL, NULL);
				ImGui::VSliderFloat("##lpf_cutoff", ImVec2(30, 90), &cutoff, 1, 22000, "");
				fmodmanager_->set_dsp_param(DSP_LOWPASSFILTER, 0, cutoff);
				ImGui::Text("%4.0f", cutoff);
				ImGui::Text("CutOff");
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_LOWPASSFILTER, 1, &resonance, NULL, NULL);
				ImGui::VSliderFloat("##lpf_resonance", ImVec2(30, 90), &resonance, 0, 10, "");
				fmodmanager_->set_dsp_param(DSP_LOWPASSFILTER, 1, resonance);
				ImGui::Text("%4.02f", resonance);
				ImGui::Text("Resonance");
				ImGui::EndGroup();

				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH2, DSP_LOWPASSFILTER);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH2, DSP_LOWPASSFILTER);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}

			if (ImGui::BeginTabItem("HPF"))
			{
				static bool enable;
				static float cutoff = 5000.f;
				static float resonance = 1.f;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_HPF_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_HIGHPASSFILTER, 0, &cutoff, NULL, NULL);
				ImGui::VSliderFloat("##hpf_cutoff", ImVec2(30, 90), &cutoff, 1, 22000, "");
				fmodmanager_->set_dsp_param(DSP_HIGHPASSFILTER, 0, cutoff);
				ImGui::Text("%.2f", cutoff);
				ImGui::Text("CutOff");
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_HIGHPASSFILTER, 1, &resonance, NULL, NULL);
				ImGui::VSliderFloat("##hpf_resonance", ImVec2(30, 90), &resonance, 1, 10, "");
				fmodmanager_->set_dsp_param(DSP_HIGHPASSFILTER, 1, resonance);
				ImGui::Text("%.2f", resonance);
				ImGui::Text("Resonance");
				ImGui::EndGroup();
				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH2, DSP_HIGHPASSFILTER);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH2, DSP_HIGHPASSFILTER);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}

			if (ImGui::BeginTabItem("FADER"))
			{
				static bool enable;
				static float gain = 0;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_fade_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_FADER, 0, &gain, NULL, NULL);
				ImGui::VSliderFloat("##fdr_gain", ImVec2(30, 90), &gain, -80, 10, "");
				fmodmanager_->set_dsp_param(DSP_FADER, 0, gain);
				ImGui::Text("%.2f", gain);
				ImGui::Text("Gain");
				ImGui::EndGroup();

				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH2, DSP_FADER);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH2, DSP_FADER);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}
			break;
		case 3:
			if (ImGui::BeginTabItem("PITCH"))
			{
				static bool enable;
				static float pitch = 1;
				static float fftsize = 1024;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_pitch_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_PITCHSHIFT, 0, &pitch, NULL, NULL);
				ImGui::VSliderFloat("##ptch_pitch", ImVec2(30, 90), &pitch, 0.5, 2, "");
				fmodmanager_->set_dsp_param(DSP_PITCHSHIFT, 0, pitch);
				ImGui::Text("%.2f", pitch);
				ImGui::Text("CutOff");
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_PITCHSHIFT, 1, &fftsize, NULL, NULL);
				ImGui::VSliderFloat("##ptch_fftsize", ImVec2(30, 90), &fftsize, 256, 4096, "");//todo chk
				fmodmanager_->set_dsp_param(DSP_PITCHSHIFT, 1, fftsize);
				ImGui::Text("%.2f", fftsize);
				ImGui::Text("FFT size");
				ImGui::EndGroup();
				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH3, DSP_PITCHSHIFT);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH3, DSP_PITCHSHIFT);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}

			if (ImGui::BeginTabItem("FLANGE"))
			{
				static bool enable;
				static float flng_mix = 50.f;
				static float flng_rate = 1.f;
				static float flng_depth = 1.f;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_FLANGE_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_FLANGE, 0, &flng_mix, NULL, NULL);
				ImGui::VSliderFloat("##flng_mix", ImVec2(30, 90), &flng_mix, 0, 100, "");
				fmodmanager_->set_dsp_param(DSP_FLANGE, 0, flng_mix);
				ImGui::Text("%.2f", flng_mix);
				ImGui::Text("Mix");
				ImGui::EndGroup();

				ImGui::SameLine(60, 10);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_FLANGE, 1, &flng_depth, NULL, NULL);
				ImGui::VSliderFloat("##flng_depth", ImVec2(30, 90), &flng_depth, 0.01, 1, "");
				fmodmanager_->set_dsp_param(DSP_FLANGE, 1, flng_depth);
				ImGui::Text("%.2f", flng_depth);
				ImGui::Text("Depth");
				ImGui::EndGroup();

				ImGui::SameLine(120, 10);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_FLANGE, 2, &flng_rate, NULL, NULL);
				ImGui::VSliderFloat("##flng_rate", ImVec2(30, 90), &flng_rate, 0, 20, "");
				fmodmanager_->set_dsp_param(DSP_FLANGE, 2, flng_rate);
				ImGui::Text("%.2f", flng_rate);
				ImGui::Text("Rate");
				ImGui::EndGroup();
				
				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH3, DSP_FLANGE);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH3, DSP_FLANGE);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}

			if (ImGui::BeginTabItem("TREMELO"))
			{
				static bool enable;
				static float tml_freq = 5.f;
				static float tml_depth = 1.f;
				static float tml_shape = 1.f;
				static float tml_skew = 0.f;
				static float tml_duty = 0.5f;
				static float tml_sqrt = 1.f;
				static float tml_phase = 0.f;
				static float tml_spread= 0.f;
				static bool dsp_enable_flag = false;

				ImGui::Checkbox("enable##DSP_TML_enable", &enable);
				if (!enable)
				{
					ImGui::BeginDisabled(true);
				}
				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 0, &tml_freq, NULL, NULL);
				ImGui::VSliderFloat("##tml_freq", ImVec2(20, 90), &tml_freq, 0.01, 20, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 0, tml_freq);
				ImGui::Text("%.2f", tml_freq);
				ImGui::Text("Freq");
				ImGui::EndGroup();

				ImGui::SameLine(50, 0);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 1, &tml_depth, NULL, NULL);
				ImGui::VSliderFloat("##tml_depth", ImVec2(20, 90), &tml_depth, 0, 1, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 1, tml_depth);
				ImGui::Text("%.2f", tml_depth);
				ImGui::Text("Depth");
				ImGui::EndGroup();

				ImGui::SameLine(100, 0);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 2, &tml_shape, NULL, NULL);
				ImGui::VSliderFloat("##tml_shape", ImVec2(20, 90), &tml_shape, 0, 1, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 2, tml_shape);
				ImGui::Text("%.2f", tml_shape);
				ImGui::Text("Shape");
				ImGui::EndGroup();

				ImGui::SameLine(150, 0);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 3, &tml_skew, NULL, NULL);
				ImGui::VSliderFloat("##tml_skew", ImVec2(20, 90), &tml_skew, -1, 1, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 3, tml_skew);
				ImGui::Text("%.2f", tml_skew);
				ImGui::Text("Skew");
				ImGui::EndGroup();

				//ImGui::SameLine();

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 4, &tml_duty, NULL, NULL);
				ImGui::VSliderFloat("##tml_duty", ImVec2(20, 90), &tml_duty, 0, 1, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 4, tml_duty);
				ImGui::Text("%.2f", tml_duty);
				ImGui::Text("Duty");
				ImGui::EndGroup();

				ImGui::SameLine(50, 0);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 5, &tml_sqrt, NULL, NULL);
				ImGui::VSliderFloat("##tml_sqrt", ImVec2(20, 90), &tml_sqrt, 0, 1, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 5, tml_sqrt);
				ImGui::Text("%.2f", tml_sqrt);
				ImGui::Text("Square");
				ImGui::EndGroup();

				ImGui::SameLine(100, 0);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 6, &tml_phase, NULL, NULL);
				ImGui::VSliderFloat("##tml_phase", ImVec2(20, 90), &tml_phase, 0, 1, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 6, tml_phase);
				ImGui::Text("%.2f", tml_phase);
				ImGui::Text("Phase");
				ImGui::EndGroup();

				ImGui::SameLine(150, 0);

				ImGui::BeginGroup();
				//todo read dsp
				fmodmanager_->get_dsp_param(DSP_TREMELO, 7, &tml_spread, NULL, NULL);
				ImGui::VSliderFloat("##tml_spread", ImVec2(20, 90), &tml_spread, -1, 1, "");
				fmodmanager_->set_dsp_param(DSP_TREMELO, 7, tml_spread);
				ImGui::Text("%.2f", tml_spread);
				ImGui::Text("Spread");
				ImGui::EndGroup();

				if (!enable)
				{
					ImGui::EndDisabled();
				}
				//toggle checking
				if (dsp_enable_flag != enable)
				{
					if (enable)
					{
						fmodmanager_->add_dsp(BGM_CH3, DSP_TREMELO);
						dsp_enable_flag = true;
					}
					else
					{
						fmodmanager_->remove_dsp(BGM_CH3, DSP_TREMELO);
						dsp_enable_flag = false;
					}
				}
				ImGui::EndTabItem();

			}
			break;
		default:
			break;
		}

		ImGui::EndTabBar();

	}



	ImGui::EndChild();
}



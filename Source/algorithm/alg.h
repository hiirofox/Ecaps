#pragma once

#include "AdditiveCore.h"
#include "Disperse.h"
#include "Sync.h"
#include "Unison.h"
#include "Octaver.h"
#include "FreqStretch.h"
#include "FreqShifter.h"




//�ƻ���
/*
* ����ɣ�
* disperse
* unison
* sync��αsync
* octaver
* 
* δ��ɣ�
* Ƶ�����죨�Ҳ�֪����ô���ݣ�
* Ƶ��ƽ�ƣ�����freq shifter��
* Ƶ��ƫ�ƣ����ˡ��༭����г����Ƶ�ʣ�
* Ƶ��ƫ�ƣ�����phase disperser���༭����г����Ƶ�ʣ�
* phaser
* filter
* reverb ����Ƶ����ģ���Ҫ��Ƶ��ƫ�ƴ��������λ��ϵ��
* 
* 
* 
* д���ܸ���ť��lfo�Ĺ��ܣ������ϵĻ��ܱ�������
* ����ģ��ϳ��������Ǽӷ�
* д���ִ���ui
* ���ܻ�Ҫ��һ����ͨ�˲�����������ģһЩ���������淨��
* fm���ƾ�����ѡ4��ģʽ��f(phase)m,p(pitch)m,fs(freq shift),am��������sytrus
* ��һЩ����ӵ㸣��ɬͼ�ʵ�����������
*/
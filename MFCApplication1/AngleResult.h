#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;

class AngleResult
{
private:
	unsigned char err_angle_[2];//data6=err_angle_[0],data5=err_angle_[1]
	unsigned char err_offset_[2];//data4=err_offset_[0],data3=err_offset_[1]
	int DectoHex(int dec, unsigned char *hex, int length)
	{
		int i;
		for (i = length - 1; i >= 0; i--)
		{
			hex[i] = (dec % 256) & 0xFF;
			dec /= 256;
		}
		return 0;
	}

public:
	AngleResult() {};
	AngleResult(int angle, int offset)
	{
		angle_ = angle;
		offset_ = offset;
		UpDate();
	}
	int angle_;
	int offset_;
	unsigned char can_frame_ID[4];
	unsigned char can_data_[8];
	void UpDate();
};
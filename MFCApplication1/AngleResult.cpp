#include "AngleResult.h"

#include <atlstr.h>

void AngleResult::UpDate()
{

	//set can data
	can_data_[0] = 0x77;
	can_data_[1] = 0x15;
	can_data_[2] = 0x10;
	can_data_[3] = (long int)(offset_ * 1 / 5.0 + 32000.0) % 256;
	can_data_[4] = (long int)(offset_ * 1 / 5.0 + 32000.0) / 256;
	can_data_[5] = (long int)(angle_ * 128.0 + 25600.0) % 256;
	can_data_[6] = (long int)(angle_ * 128.0 + 25600.0) / 256;
	can_data_[7] = 0xFF;
	//set can_frameID;
	//can_frame_ID = 0x0CFFFFC5;//¡„X¡„C
	int strFID[] = { 0, 0, 0, 0, 0, 0, 8, 1};
	can_frame_ID[0] = (strFID[1] ) + (strFID[0] ) * 16;
	can_frame_ID[1] = (strFID[3] ) + (strFID[2] ) * 16;
	can_frame_ID[2] = (strFID[5] ) + (strFID[4] ) * 16;
	can_frame_ID[3] = (strFID[7] ) + (strFID[6] ) * 16;
}
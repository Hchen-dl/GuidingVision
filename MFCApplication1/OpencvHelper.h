#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <iostream>
using namespace cv;
using namespace std;

typedef struct Result
{
	int angle;//航向偏差
	int offset;//横向偏差
};
class OpencvHelper
{
private:
	Mat tem_image_;
	Mat template_image_;
	Mat grey_image_;
	Mat thresh_image_;
public :
	Mat src_image_;	
	Mat homography_;
	Rect ROI_;	
	VideoCapture videoCapture_;
	//flags
	bool do_video_record_;
	bool do_image_process_;
	bool do_send_can_msg_;

	//打开相机
	int OpenCamera(string videopath=NULL);
	//Mat dst_image_;
	//获取图像中导航参数
	Result GetCropRows();
	Vec4i LengthenLine(Vec4i line, Mat draw);

	//获取投影变换后的导航参数
	Result GetResult(vector<Point2f>line);
	vector<Result> results;//每次找出line后存储，与之前结果进行比较~决定取舍。

	//S(x)
	Mat ImgTemplate(Mat Img);
	void GetImage(bool is_from_camera, bool paused);

	//ImageProcess
	vector<Point2f> GetLine_Tradition();
	Result GetLine_Texture();
	vector<Point2f> GetLine();
	int Save(string picpath);

	void SetImage(Mat src);
	void GreyTransform();
	void OTSUBinarize();
	void EXGCalcultate();
	void DilateImage();
};

enum OpType {
	OT_ADD,
	OT_SUB,
	OT_MUL,
	OT_DIV,
};

template<class T>
class VecSum {
	OpType type_;
	const T& op1_;
	const T& op2_;
public:
	VecSum(int type, const T& op1, const T& op2) : type_(type), op1_(op1), op2_(op2) {}

	int operator[](const int i) const {
		switch (type_) {
		case OT_ADD: return op1_[i] + op2_[i];
		case OT_SUB: return op1_[i] - op2_[i];
		case OT_MUL: return op1_[i] * op2_[i];
		case OT_DIV: return op1_[i] / op2_[i];
		default: throw "bad type";
		}
	}
};

template<class T>
VecSum<T> operator+(const T& t1, const T& t2) {
	return VecSum<T>(OT_ADD, t1, t2);
}
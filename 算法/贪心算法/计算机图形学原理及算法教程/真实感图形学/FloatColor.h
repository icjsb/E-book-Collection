// FloatColor.h: interface for the CFloatColor class.
#ifndef _CFLOATCOLOR_H
#define _CFLOATCOLOR_H
#include "Grphcs.h"

class CFloatColor  
{
public:
	CFloatColor();
	CFloatColor(float red , float green, float blue, float alpha  = 1.0f);
	CFloatColor(const FLOATCOLORRGB& rgb);
	CFloatColor(const FLOATCOLORRGBA& rgba);
	virtual ~CFloatColor();

public:

	//������ɫ
	void Set(float red,float green,float blue,float alpha = 1.0f);

	//��ȡ��ɫ
	FLOATCOLORRGB  GetRGB() const;
	FLOATCOLORRGBA GetRGBA() const;

	//���� "=" �����
	inline CFloatColor operator = (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator = (const CFloatColor& color);
	inline CFloatColor operator = (const FLOATCOLORRGBA& rgba);

	//���� "+" �����
	inline CFloatColor operator + (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator + (const CFloatColor& color);
	inline CFloatColor operator + (const FLOATCOLORRGBA& rgba);

	//���� "+=" �����
	inline CFloatColor operator += (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator += (const CFloatColor& color);
	inline CFloatColor operator += (const FLOATCOLORRGBA& rgba);

	//���� "*" �����
	inline CFloatColor operator * (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator * (const CFloatColor& color);
	inline CFloatColor operator * (const FLOATCOLORRGBA& rgba);
	inline CFloatColor operator * (float fc);

	//���� "*=" �����
	inline CFloatColor operator *= (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator *= (const CFloatColor& color);
	inline CFloatColor operator *= (const FLOATCOLORRGBA& rgba);
	inline CFloatColor operator *= (float fc);

	//��ɫ��һ������
	inline CFloatColor Clamp();

public:

	//������ɫ
	float  red, green, blue, alpha;

};
#endif 


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ���������  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//���� "=" �����
inline CFloatColor CFloatColor::operator = (const CFloatColor& color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
	alpha = color.alpha;
	return *this;
}

//���� "=" �����
inline CFloatColor CFloatColor::operator = (const FLOATCOLORRGB& rgb)
{
	red = rgb.red;
	green = rgb.green;
	blue = rgb.blue;
	alpha = 1.0f;
	return *this;
}

//���� "=" �����,
inline CFloatColor CFloatColor::operator = (const FLOATCOLORRGBA& rgba)
{
	red = rgba.red;
	green = rgba.green;
	blue = rgba.blue;
	alpha = rgba.alpha;
	return *this;
}


//���� "+" �����
inline CFloatColor CFloatColor::operator + (const CFloatColor& color)
{
	CFloatColor clr;
	clr.red =   red   + color.red;
	clr.green = green + color.green;
	clr.blue =  blue  + color.blue;

	//���� alpha ����,������,����Ҳ�򵥵�ִ�д����ӷ�
	clr.alpha = alpha + color.alpha;
	return clr;
}

//���� "+" �����
inline CFloatColor CFloatColor::operator + (const FLOATCOLORRGB& rgb)
{
	CFloatColor clr;
	clr.red =   red   + rgb.red;
	clr.green = green + rgb.green;
	clr.blue =  blue  + rgb.blue;

	//���� alpha ����,������,����Ҳ�򵥵���1.0����
	clr.alpha = 1.0f;
	return clr;
}

//���� "+" �����,
inline CFloatColor CFloatColor::operator + (const FLOATCOLORRGBA& rgba)
{
	CFloatColor clr;
	clr.red =   red   + rgba.red;
	clr.green = green + rgba.green;
	clr.blue =  blue  + rgba.blue;
	clr.alpha = alpha + rgba.alpha;
	return clr;
}

//���� "+=" �����
inline CFloatColor CFloatColor::operator += (const CFloatColor& color)
{
	red   += color.red;
	green += color.green;
	blue  += color.blue;
	alpha += color.alpha;
	return *this;
}

//���� "+=" �����
inline CFloatColor CFloatColor::operator += (const FLOATCOLORRGB& rgb)
{
	red   += rgb.red;
	green += rgb.green;
	blue  += rgb.blue;
	alpha = 1.0f;
	return *this;
}

//���� "+=" �����,
inline CFloatColor CFloatColor::operator += (const FLOATCOLORRGBA& rgba)
{
	red   += rgba.red;
	green += rgba.green;
	blue  += rgba.blue;
	alpha += rgba.alpha;
	return *this;
}

//���� "*" �����
inline CFloatColor CFloatColor::operator * (const CFloatColor& color)
{
	CFloatColor clr;
	clr.red =   red   * color.red;
	clr.green = green * color.green;
	clr.blue =  blue  * color.blue;
	clr.alpha = alpha * color.alpha;
	return clr;
}

//���� "*" �����
inline CFloatColor CFloatColor::operator * (const FLOATCOLORRGB& rgb)
{
	CFloatColor clr;
	clr.red =   red   * rgb.red;
	clr.green = green * rgb.green;
	clr.blue =  blue  * rgb.blue;

	//alpha ���������ֲ���
	clr.alpha = alpha; 
	return clr;
}

//���� "*" �����,
inline CFloatColor CFloatColor::operator * (const FLOATCOLORRGBA& rgba)
{
	CFloatColor clr;
	clr.red =   red   * rgba.red;
	clr.green = green * rgba.green;
	clr.blue =  blue  * rgba.blue;
	clr.alpha = alpha * rgba.alpha;
	return clr;
}

//���� "*" �����,
inline CFloatColor CFloatColor::operator * (float fc)
{
	CFloatColor clr;
	clr.red =   red   * fc;
	clr.green = green * fc;
	clr.blue =  blue  * fc;
	clr.alpha = alpha * fc;
	return clr;
}

//////////////////////
//���� "*=" �����
inline CFloatColor CFloatColor::operator *= (const CFloatColor& color)
{
	red   *= color.red;
	green *= color.green;
	blue  *= color.blue;
	alpha *= color.alpha;
	return *this;
}

//���� "*=" �����
inline CFloatColor CFloatColor::operator *= (const FLOATCOLORRGB& rgb)
{
	red   *= rgb.red;
	green *= rgb.green;
	blue  *= rgb.blue;
	return *this;
}

//���� "*=" �����,
inline CFloatColor CFloatColor::operator *= (const FLOATCOLORRGBA& rgba)
{
	red   *= rgba.red;
	green *= rgba.green;
	blue  *= rgba.blue;
	alpha *= rgba.alpha;
	return *this;
}

//���� "*=" �����,
inline CFloatColor CFloatColor::operator *= (float fc)
{
	red   *= fc;
	green *= fc;
	blue  *= fc;
	alpha *= fc;
	return *this;
}



//	��ɫ��һ������
inline CFloatColor CFloatColor::Clamp()
{
	CFloatColor clr;
	clr.red = (red < 0.0f) ? 0.0f : ((red > 1.0f) ? 1.0f : red);
	clr.green = (green < 0.0f) ? 0.0f : ((green > 1.0f) ? 1.0f : green);
	clr.blue = (blue < 0.0f) ? 0.0f : ((blue > 1.0f) ? 1.0f : blue);
	clr.alpha = (alpha < 0.0f) ? 0.0f : ((alpha > 1.0f) ? 1.0f : alpha);
	return clr;
}
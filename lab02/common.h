#ifndef COMMON_H
#define COMMON_H

namespace ST {
enum ShapeType {
    None         = 0x00,
    Line         = 0x01<<0,
    Rectangle    = 0x01<<1,   //矩形
    Ellipse      = 0x01<<2,   //椭圆
    Triangle     = 0x01<<3,   //三角
    Diamond      = 0x01<<4,   //菱形
    Text         = 0x01<<5,   //文本
    picture      = 0x01<<6,   //图片
    TypeMask     = 0x0f
};
}

#define BACKGROUND_COLOR Qt::white
#define FOREGROUND_COLOR Qt::red


#endif // COMMON_H

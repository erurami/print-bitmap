#include <cmath>
#include <cstdio>


int intAbs(int a)
{
    return a < 0 ? -a : a;
}

void moveCursorToLeft(int x)
{
    if (x == 0) return;
    printf("\033[%dD", x);
}

void moveCursorToRight(int x)
{
    if (x == 0) return;
    printf("\033[%dC", x);
}

void moveCursorToUp(int y)
{
    if (y == 0) return;
    printf("\033[%dA", y);
}

void moveCursorToDown(int y)
{
    if (y == 0) return;
    printf("\033[%dB", y);
}

/* ---------------------------------*/

Color::Color(int r, int g, int b)
{
    mRgb[0] = r;
    mRgb[1] = g;
    mRgb[2] = b;
    HsvFromRgbMember();
}

Color::Color()
    :Color(0, 0, 0)
{
}


int Color::GetR() const {return mRgb[0];}
int Color::GetG() const {return mRgb[1];}
int Color::GetB() const {return mRgb[2];}
int Color::GetH() const {return mHsv[0];}
int Color::GetS() const {return mHsv[1];}
int Color::GetV() const {return mHsv[2];}

void Color::GetRgb(int* pRgbDes) const
{for (int i = 0; i < 3; i++) pRgbDes[i] = mRgb[i];}

void Color::GetHsv(int* pHsvDes) const
{for (int i = 0; i < 3; i++) pHsvDes[i] = mHsv[i];}


#define CALC_RGB_AND_RETURN() return RgbFromHsvMember()
#define CALC_HSV_AND_RETURN() return HsvFromRgbMember()
bool Color::SetRValue(int r){mRgb[0] = r; CALC_HSV_AND_RETURN();}
bool Color::SetGValue(int g){mRgb[1] = g; CALC_HSV_AND_RETURN();}
bool Color::SetBValue(int b){mRgb[2] = b; CALC_HSV_AND_RETURN();}
bool Color::SetHValue(int h){mHsv[0] = h; CALC_RGB_AND_RETURN();}
bool Color::SetSValue(int s){mHsv[1] = s; CALC_RGB_AND_RETURN();}
bool Color::SetVValue(int v){mHsv[2] = v; CALC_RGB_AND_RETURN();}

bool Color::SetRgb(int r, int g, int b)
{mRgb[0] = r; mRgb[1] = g; mRgb[2] = b; CALC_HSV_AND_RETURN();}

bool Color::SetHsv(int h, int s, int v)
{mHsv[0] = h; mHsv[1] = s; mHsv[2] = v; CALC_RGB_AND_RETURN();}
#undef CALC_RGB_AND_RETURN
#undef CALC_HSV_AND_RETURN

void Color::ApplyToForegroundColor(void)
{
    printf("\033[38;2;%d;%d;%dm", mRgb[0], mRgb[1], mRgb[2]);
}

void Color::ApplyToBackgroundColor(void)
{
    printf("\033[48;2;%d;%d;%dm", mRgb[0], mRgb[1], mRgb[2]);
}




Color Color::operator +  (const Color& rhs) const
{
    Color sum_color;

    sum_color.SetRgb(this->GetR() + rhs.GetR(),
                     this->GetG() + rhs.GetG(),
                     this->GetB() + rhs.GetB());
    return sum_color;
}



bool  Color::operator == (const Color& rhs) const
{
    return (this->GetR() == rhs.GetR()) and
           (this->GetG() == rhs.GetG()) and
           (this->GetB() == rhs.GetB());
}


bool  Color::operator != (const Color& rhs) const
{
    return (this->GetR() != rhs.GetR()) or
           (this->GetG() != rhs.GetG()) or
           (this->GetB() != rhs.GetB());
}




bool Color::RgbFromHsvMember()
{
    bool was_hsv_valid = CheckAndFixHsvMember();

    unsigned short int& r = mRgb[0];
    unsigned short int& g = mRgb[1];
    unsigned short int& b = mRgb[2];

    double tmp1 = static_cast<double>(mHsv[2] * mHsv[1]) / 255;
    int tmp2 = mHsv[0] % 120;
    int tmp3 = mHsv[2] - static_cast<int>(tmp1);

    #define value_1   mHsv[2]
    #define value_2   tmp3
    #define value_3_1 (static_cast<int>(tmp1 * tmp2) / 60 + tmp3)
    #define value_3_2 (static_cast<int>(tmp1 * (60 - tmp2)) / 60 + mHsv[2])
    #define value_3   (tmp2 < 60) ? value_3_1 : value_3_2

    if (300 <= mHsv[0]){
    r = value_1; g = value_2; b = value_3; return was_hsv_valid;
    }
    if (240 <= mHsv[0]){
    r = value_3; g = value_2; b = value_1; return was_hsv_valid;
    }
    if (180 <= mHsv[0]){
    r = value_2; g = value_3; b = value_1; return was_hsv_valid;
    }
    if (120 <= mHsv[0]){
    r = value_2; g = value_1; b = value_3; return was_hsv_valid;
    }
    if ( 60 <= mHsv[0]){
    r = value_3; g = value_1; b = value_2; return was_hsv_valid;
    }

    r = value_1; g = value_3; b = value_2; return was_hsv_valid;
    #undef value_1
    #undef value_2
    #undef value_3_1
    #undef value_3_2
    #undef value_3
}

bool Color::HsvFromRgbMember()
{
    bool was_rgb_valid = CheckAndFixRgbMember();

    unsigned short int& h = mHsv[0];
    unsigned short int& s = mHsv[1];
    unsigned short int& v = mHsv[2];

    int V_max = 0, V_min = 255, diff;

    for (int i=0; i<3; i++)
    {
        if (mRgb[i] > V_max) V_max = mRgb[i];
        if (mRgb[i] < V_min) V_min = mRgb[i];
    }

    diff = V_max - V_min;


    v = V_max;
    s = (V_max == 0) ? 0: (diff * 255 / V_max);

    if (diff == 0) {h = 0; return was_rgb_valid;}
    if (V_max == mRgb[0])
    {
        h = 60 * (std::fmod((static_cast<double>(mRgb[1] - mRgb[2]) / diff), 6.0));
        if (h >= 0) return was_rgb_valid;
    }
    if (V_max == mRgb[1])
    {
        h = 60 * ((static_cast<double>(mRgb[2] - mRgb[0]) / diff) + 2);
        if (h >= 0) return was_rgb_valid;
    }
    if (V_max == mRgb[2])
    {
        h = 60 * ((static_cast<double>(mRgb[0] - mRgb[1]) / diff) + 4);
        if (h >= 0) return was_rgb_valid;
    }
    h = 0;
    return was_rgb_valid;
}


bool Color::CheckAndFixRgbMember()
{
    bool is_rgb_valid = true;
    if (mRgb[0] > 255) {mRgb[0] = 255; is_rgb_valid = false;}
    if (mRgb[0] <   0) {mRgb[0] =   0; is_rgb_valid = false;}
    if (mRgb[1] > 255) {mRgb[1] = 255; is_rgb_valid = false;}
    if (mRgb[1] <   0) {mRgb[1] =   0; is_rgb_valid = false;}
    if (mRgb[2] > 255) {mRgb[2] = 255; is_rgb_valid = false;}
    if (mRgb[2] <   0) {mRgb[2] =   0; is_rgb_valid = false;}
    return is_rgb_valid;
}

bool Color::CheckAndFixHsvMember()
{
    bool is_hsv_valid = true;
    if (mHsv[0] > 360) {mHsv[0] = 360; is_hsv_valid = false;}
    if (mHsv[0] <   0) {mHsv[0] =   0; is_hsv_valid = false;}
    if (mHsv[1] > 255) {mHsv[1] = 255; is_hsv_valid = false;}
    if (mHsv[1] <   0) {mHsv[1] =   0; is_hsv_valid = false;}
    if (mHsv[2] > 255) {mHsv[2] = 255; is_hsv_valid = false;}
    if (mHsv[2] <   0) {mHsv[2] =   0; is_hsv_valid = false;}
    return is_hsv_valid;
}
/* --------------------------------- */

Pixel::Pixel()
{
    mForegroundColor.SetRgb(255, 255, 255);
    mBackgroundColor.SetRgb(0, 0, 0);
    mCharacter = ' ';
}

Pixel::Pixel(char character)
{
    mForegroundColor.SetRgb(255, 255, 255);
    mBackgroundColor.SetRgb(0, 0, 0);
    mCharacter = character;
}

Pixel::Pixel(const Color* pForegroundColor, const Color* pBackgroundColor, char character)
{
    mForegroundColor.SetRgb(pForegroundColor->GetR(),
                            pForegroundColor->GetG(),
                            pForegroundColor->GetB());
    mBackgroundColor.SetRgb(pBackgroundColor->GetR(),
                            pBackgroundColor->GetG(),
                            pBackgroundColor->GetB());
    mCharacter = character;
}


char Pixel::GetCharacter() const
{
    return mCharacter;
}

void Pixel::SetCharacter(char character)
{
    if (character < 32 || character == 127)
    {
        character = 32;
    }
    mCharacter = character;
}

void Pixel::SetCharacterNoCheck(char character)
{
    mCharacter = character;
}


void Pixel::SetForeColor(const Color* pColor)
{
    mForegroundColor = *pColor;
}
void Pixel::SetForeColor(int r, int g, int b)
{
    mForegroundColor.SetRgb(r, g, b);
}
void Pixel::SetForeColorHsv(int h, int s, int v)
{
    mForegroundColor.SetHsv(h, s, v);
}

void Pixel::SetBackColor(const Color* pColor)
{
    mBackgroundColor = *pColor;
}
void Pixel::SetBackColor(int r, int g, int b)
{
    mBackgroundColor.SetRgb(r, g, b);
}
void Pixel::SetBackColorHsv(int h, int s, int v)
{
    mBackgroundColor.SetHsv(h, s, v);
}


void Pixel::Print() const
{
    printf("\033[48;2;%d;%d;%dm\033[38;2;%d;%d;%dm%c\033[m",
            mBackgroundColor.GetR(),
            mBackgroundColor.GetG(),
            mBackgroundColor.GetB(),
            mForegroundColor.GetR(),
            mForegroundColor.GetG(),
            mForegroundColor.GetB(),
            mCharacter);
}


bool Pixel::operator == (const Pixel& rhx) const
{
    return (this->mForegroundColor == rhx.mForegroundColor) &&
           (this->mBackgroundColor == rhx.mBackgroundColor) &&
           (this->mCharacter == rhx.mCharacter);
}

bool Pixel::operator != (const Pixel& rhx) const
{
    return (this->mForegroundColor != rhx.mForegroundColor) ||
           (this->mBackgroundColor != rhx.mBackgroundColor) ||
           (this->mCharacter != rhx.mCharacter);
}


/*-----------------------------------------*/


Surface::Surface(int width, int height)
{
    mWidth = width;
    mHeight = height;
    mpBuffer = new Pixel [width * height];
    mpChangedPoints = new bool [width * height];
    for (int i = 0; i < width * height; i++)
    {
        mpChangedPoints[i] = true;
    }
}

Surface::Surface(int width, int height, const Pixel* pFillBy)
    :Surface(width, height)
{
    Fill(pFillBy);
}

Surface::~Surface()
{
    delete [] mpBuffer;
    delete [] mpChangedPoints;
}


bool Surface::IsThisInSurface(int x, int y)
{
    if (x < 0       || y < 0 ||
        x >= mWidth || y >= mHeight)
    {
        return false;
    }
    return true;
}


void Surface::Blit(int x, int y, const Surface* pSurface)
{
    int tmp;
    int blitting_pixel_index;
    Pixel blitting_pixel;

    for (int i = 0; i < pSurface->GetHeight(); i++)
    {
        if ((i + y) >= mHeight) break;

        tmp = (i + y) * mWidth;

        for (int j = 0; j < pSurface->GetWidth(); j++)
        {
            if ((j + x) >= mWidth) break;


            blitting_pixel_index = tmp + j + x;
            blitting_pixel = pSurface->GetPixelAt(j, i);

            if (mpBuffer[blitting_pixel_index] != blitting_pixel)
            {
                mpChangedPoints[blitting_pixel_index] = true;
                mpBuffer[blitting_pixel_index] = blitting_pixel;
            }
        }

    }
    return;
}


void Surface::Fill(const Pixel* pFillBy)
{
    int tmp = mWidth * mHeight;
    for (int i = 0; i < tmp; i++)
    {
        if (mpBuffer[i] != *pFillBy)
        {
            mpChangedPoints[i] = true;
            mpBuffer[i] = *pFillBy;
        }
    }
    return;
}

/*TODO: SET_PIXEL_AT macro 
 *          Check the difference of the pixel and if it's diffferent, 
 *          mark the pixel to changed pixels array and change the pixel data.*/
/*TODO: SET_BACKGROUND_COLOR macro
 *          simillar to SET_PIXEL_AT*/
/**/

#define FILL_BACKGROUND_COLOR(fill_color) \
    int tmp = mWidth * mHeight;\
    for (int i = 0; i < tmp; i++)\
    {\
        if (mpBuffer[i].mBackgroundColor != fill_color)\
        {\
            mpChangedPoints[i] = true;\
            mpBuffer[i].mBackgroundColor = fill_color;\
        }\
    }

void Surface::FillBackground(const Color* pFillColor)
{
    FILL_BACKGROUND_COLOR(*pFillColor)
    return;
}

void Surface::FillBackground(int r, int g, int b)
{
    Color fill_color(r, g, b);
    FILL_BACKGROUND_COLOR(fill_color)
    return;
}

void Surface::FillBackgroundHsv(int h, int s, int v)
{
    Color fill_color;
    fill_color.SetHsv(h, s, v);
    FILL_BACKGROUND_COLOR(fill_color)
    return;
}

#undef FILL_BACKGROUND_COLOR

#define FILL_FOREGROUND_COLOR(fill_color) \
    int tmp = mWidth * mHeight;\
    for (int i = 0; i < tmp; i++)\
    {\
        if (mpBuffer[i].mForegroundColor != fill_color)\
        {\
            mpChangedPoints[i] = true;\
            mpBuffer[i].mForegroundColor = fill_color;\
        }\
    }

void Surface::FillForeground(const Color* pFillColor)
{
    FILL_FOREGROUND_COLOR(*pFillColor)
    return;
}

void Surface::FillForeground(int r, int g, int b)
{
    Color fill_color(r, g, b);
    FILL_FOREGROUND_COLOR(fill_color)
    return;
}

void Surface::FillForegroundHsv(int h, int s, int v)
{
    Color fill_color;
    fill_color.SetHsv(h, s, v);
    FILL_FOREGROUND_COLOR(fill_color)
    return;
}

#undef FILL_FOREGROUND_COLOR

void Surface::FillChar(char fillBy)
{
    if (fillBy < 32 || fillBy == 127)
    {
        fillBy = 32;
    }

    int tmp = mWidth * mHeight;
    for (int i = 0; i < tmp; i++)
    {
        if (mpBuffer[i].GetCharacter() != fillBy)
        {
            mpChangedPoints[i] = true;
            mpBuffer[i].SetCharacterNoCheck(fillBy);
        }
    }
}


// These macro doesn't includes semi-coron.
#define RETURN_IF_POS_INCORRECT(x, y) if (IsThisInSurface(x, y) == false) return false
#define DECLARE_PIXEL_INDEX(x, y) int pixel_index = x + y * mWidth

#define SET_PIXEL(pixel_index, set_pixel) \
    mpChangedPoints[pixel_index] = true; \
    mpBuffer[pixel_index] = set_pixel

bool Surface::SetPixelAt(int x, int y, const Pixel* pSetPixel)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    if (mpBuffer[pixel_index] != *pSetPixel)
    {
        SET_PIXEL(pixel_index, *pSetPixel);
    }
    return true;
}

#undef SET_PIXEL

#define SET_BACKGROUND_COLOR(pixel_index, set_color) \
    if (mpBuffer[pixel_index].mBackgroundColor != set_color)\
    {\
        mpChangedPoints[pixel_index] = true; \
        mpBuffer[pixel_index].mBackgroundColor = set_color;\
    }

bool Surface::SetBackgroundAt(int x, int y, const Color* pSetColor)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    SET_BACKGROUND_COLOR(pixel_index, *pSetColor)
    return true;
}

bool Surface::SetBackgroundAt(int x, int y, int r, int g, int b)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    Color set_color(r, g, b);

    SET_BACKGROUND_COLOR(pixel_index, set_color);
    return true;
}

bool Surface::SetBackgroundHsvAt(int x, int y, int h, int s, int v)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    Color set_color;
    set_color.SetHsv(h, s, v);

    SET_BACKGROUND_COLOR(pixel_index, set_color);
    return true;
}

#undef SET_BACKGROUND_COLOR


#define SET_FOREGROUND_COLOR(pixel_index, set_color) \
    if (mpBuffer[pixel_index].mForegroundColor != set_color)\
    {\
        mpChangedPoints[pixel_index] = true; \
        mpBuffer[pixel_index].mForegroundColor = set_color;\
    }

bool Surface::SetForegroundAt(int x, int y, const Color* pSetColor)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    SET_FOREGROUND_COLOR(pixel_index, *pSetColor)
    return true;
}

bool Surface::SetForegroundAt(int x, int y, int r, int g, int b)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    Color set_color(r, g, b);

    SET_FOREGROUND_COLOR(pixel_index, set_color);
    return true;
}

bool Surface::SetForegroundHsvAt(int x, int y, int h, int s, int v)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    Color set_color;
    set_color.SetHsv(h, s, v);

    SET_FOREGROUND_COLOR(pixel_index, set_color);
    return true;
}

#undef SET_FOREGROUND_COLOR

bool Surface::SetCharAt(int x, int y, char setChar)
{
    RETURN_IF_POS_INCORRECT(x, y);
    DECLARE_PIXEL_INDEX(x, y);

    if (mpBuffer[pixel_index].GetCharacter() != setChar)
    {
        mpChangedPoints[pixel_index] = true;
        mpBuffer[pixel_index].SetCharacter(setChar);
    }
    return true;
}

#undef DECLARE_PIXEL_INDEX
#undef RETURN_IF_POS_INCORRECT




#define LOOP_FOR_RECTANGLE(x, y, width, height, WhatToDo, Arg) \
    int first_column_index = x + y * mWidth;\
    int drawing_pixel_index;\
    \
    for (int i = 0; i < height; i++)\
    {\
        if ((i + y) >= mHeight) break;\
        drawing_pixel_index = first_column_index;\
        for (int j = 0; j <= width; j++)\
        {\
            if ((j + x) > mWidth) break;\
            WhatToDo(drawing_pixel_index, Arg);\
            drawing_pixel_index++;\
        }\
        first_column_index += mWidth;\
    }

#define LOOP_FOR_RECTANGLE2(x, y, width, height, WhatToDo, Arg1, Arg2) \
    int first_column_index = x + y * mWidth;\
    int drawing_pixel_index;\
    \
    for (int i = 0; i < height; i++)\
    {\
        if ((i + y) >= mHeight) break;\
        drawing_pixel_index = first_column_index;\
        for (int j = 0; j <= width; j++)\
        {\
            if ((j + x) > mWidth) break;\
            WhatToDo(drawing_pixel_index, Arg1, Arg2);\
            drawing_pixel_index++;\
        }\
        first_column_index += mWidth;\
    }


#define SET_PIXEL_AT(pixel_index, set_pixel) \
    if (mpBuffer[pixel_index] != set_pixel)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index] = set_pixel;\
    }

#define SET_BACKGROUND_AT(pixel_index, set_color) \
    if (mpBuffer[pixel_index].mBackgroundColor != set_color)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index].mBackgroundColor = set_color;\
    }


#define SET_CHAR_AT(pixel_index, chara, char_color) \
    if (mpBuffer[pixel_index].GetCharacter() != chara ||\
        mpBuffer[pixel_index].mForegroundColor != char_color)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index].SetCharacterNoCheck(chara);\
        mpBuffer[pixel_index].mForegroundColor = char_color;\
    }

#define CHECK_CHAR_AND_CORRECT(character) \
    if (character < 32 || character == 127)\
    {\
        character = 32;\
    }

void Surface::DrawRectangle(int x, int y,
                            int width, int height,
                            const Pixel* pPixel,
                            int outlineWidth = 0)
{
    LOOP_FOR_RECTANGLE(x, y, width, height, SET_PIXEL_AT, *pPixel);
}


void Surface::DrawBackgroundRectangle(int x, int y,
                                      int width, int height,
                                      const Color* pColor,
                                      int outlineWidth = 0)
{
    LOOP_FOR_RECTANGLE(x, y, width, height, SET_BACKGROUND_AT, *pColor);
}

void Surface::DrawBackgroundRectangle(int x, int y,
                                      int width, int height,
                                      int r, int g, int b,
                                      int outlineWidth = 0)
{
    Color color(r, g, b);
    LOOP_FOR_RECTANGLE(x, y, width, height, SET_BACKGROUND_AT, color);
}

void Surface::DrawBackgroundRectangleHsv(int x, int y,
                                         int width, int height,
                                         int h, int s, int v,
                                         int outlineWidth = 0)
{
    Color color;
    color.SetHsv(h, s, v);
    LOOP_FOR_RECTANGLE(x, y, width, height, SET_BACKGROUND_AT, color);
}

void Surface::DrawCharRectangle(int x, int y,
                                int width, int height,
                                char character, const Color* pColor,
                                int outlineWidth = 0)
{
    CHECK_CHAR_AND_CORRECT(character);

    LOOP_FOR_RECTANGLE2(x, y, width, height, SET_CHAR_AT, character, *pColor);
}

void Surface::DrawCharRectangle(int x, int y,
                                int width, int height,
                                char character, int r, int g, int b,
                                int outlineWidth = 0)
{
    CHECK_CHAR_AND_CORRECT(character);

    Color char_color(r, g, b);
    LOOP_FOR_RECTANGLE2(x, y, width, height, SET_CHAR_AT, character, char_color);
}

void Surface::DrawCharRectangleHsv(int x, int y,
                                   int width, int height,
                                   char character, int h, int s, int v,
                                   int outlineWidth = 0)
{
    CHECK_CHAR_AND_CORRECT(character);

    Color char_color;
    char_color.SetHsv(h, s, v);
    LOOP_FOR_RECTANGLE2(x, y, width, height, SET_CHAR_AT, character, char_color);
}


#undef LOOP_FOR_RECTANGLE
#undef SET_PIXEL_AT
#undef SET_FOREGROUND_AT
#undef SET_BACKGROUND_AT
#undef SET_CHAR_AT
#undef CHECK_CHAR_AND_CORRECT


#define SET_PIXEL_AT(pixel_index, set_pixel) \
    if (mpBuffer[pixel_index] != set_pixel)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index] = set_pixel;\
    }

#define DRAW_LINE(what_to_do, arg1) \
    int drawing_pixel_index;\
    int diff_x, diff_y, count, step;\
    diff_x = intAbs(x2 - x1);\
    diff_y = intAbs(y2 - y1);\
    if (diff_x > diff_y)\
    {\
        if (x1 > x2)\
        {\
            step = (y1 > y2) ? 1 : -1;\
            count = x1; x1 = x2; x2 = count;\
            y1 = y2;\
        }\
        else\
        {\
            step = (y1 < y2) ? 1 : -1;\
        }\
        drawing_pixel_index = y1 * mWidth + x1;\
        what_to_do(drawing_pixel_index, arg1);\
        count = diff_x >> 1;\
        for (; x1 <= x2; x1++)\
        {\
            count -= diff_y;\
            if (count < 0)\
            {\
                count += diff_x;\
                y1 += step;\
            }\
            drawing_pixel_index =  y1 * mWidth + x1;\
            what_to_do(drawing_pixel_index, arg1);\
        }\
    }\
    else\
    {\
        if (y1 > y2)\
        {\
            step = (x1 > x2) ? 1 : -1;\
            count = y1; y1 = y2; y2 = count;\
            x1 = x2;\
        }\
        else\
        {\
            step = (x1 < x2) ? 1 : -1;\
        }\
        drawing_pixel_index = y1 * mWidth + x1;\
        what_to_do(drawing_pixel_index, arg1);\
        count = diff_y >> 1;\
        for (; y1 < y2; y1++)\
        {\
            count -= diff_x;\
            if (count < 0)\
            {\
                count += diff_y;\
                x1 += step;\
            }\
            drawing_pixel_index = y1 * mWidth + x1;\
            what_to_do(drawing_pixel_index, arg1);\
        }\
    }

#define SET_PIXEL_AT(pixel_index, set_pixel) \
    if (mpBuffer[pixel_index] != set_pixel)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index] = set_pixel;\
    }

#define SET_BACKGROUND_AT(pixel_index, set_color) \
    if (mpBuffer[pixel_index].mBackgroundColor != set_color)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index].mBackgroundColor = set_color;\
    }

#define SET_CHARACTER_AT(pixel_index, set_color) \
    if (mpBuffer[pixel_index].mForegroundColor != set_color ||\
        mpBuffer[pixel_index].GetCharacter() != character)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index].mForegroundColor = set_color;\
        mpBuffer[pixel_index].SetCharacterNoCheck(character);\
    }

#define CHECK_CHAR_AND_CORRECT(character) \
    if (character < 32 || character == 127)\
    {\
        character = 32;\
    }

/*Maybe it can be optimased when the line was vertical or holizontal. */

/*TODO: Check values before draw (for all)*/

void Surface::DrawLine(int x1, int y1,
                       int x2, int y2,
                       const Pixel* pPixel,
                       int lineWidth = 1)
{
    DRAW_LINE(SET_PIXEL_AT, *pPixel);
}

void Surface::DrawBackgroundLine(int x1, int y1,
                                 int x2, int y2,
                                 const Color* pColor,
                                 int lineWidth = 1)
{
    DRAW_LINE(SET_BACKGROUND_AT, *pColor);
}

void Surface::DrawBackgroundLine(int x1, int y1,
                                 int x2, int y2,
                                 int r, int g, int b,
                                 int lineWidth = 1)
{
    Color line_color(r, g, b);

    DRAW_LINE(SET_BACKGROUND_AT, line_color);
}

void Surface::DrawBackgroundLineHsv(int x1, int y1,
                                    int x2, int y2,
                                    int h, int s, int v,
                                    int lineWidth = 1)
{
    Color line_color;
    line_color.SetHsv(h, s, v);

    DRAW_LINE(SET_BACKGROUND_AT, line_color);
}

void Surface::DrawCharLine(int x1, int y1,
                           int x2, int y2,
                           char character, const Color* pColor,
                           int lineWidth = 1)
{
    CHECK_CHAR_AND_CORRECT(character);
    DRAW_LINE(SET_CHARACTER_AT, *pColor);
}

void Surface::DrawCharLine(int x1, int y1,
                           int x2, int y2,
                           char character, int r, int g, int b,
                           int lineWidth = 1)
{
    CHECK_CHAR_AND_CORRECT(character);

    Color char_color(r, g, b);

    DRAW_LINE(SET_CHARACTER_AT, char_color);
}

void Surface::DrawCharLineHsv(int x1, int y1,
                              int x2, int y2,
                              char character, int h, int s, int v,
                              int lineWidth = 1)
{
    CHECK_CHAR_AND_CORRECT(character);

    Color char_color;
    char_color.SetHsv(h, s, v);

    DRAW_LINE(SET_CHARACTER_AT, char_color);
}

#undef DRAW_LINE
#undef SET_PIXEL_AT
#undef SET_BACKGROUND_AT
#undef SET_CHARACTER_AT
#undef CHECK_CHAR_AND_CORRECT

#define DRAW_CIRCLE(WHAT_TO_DO, arg) \
    int drawing_point_index;\
    int drawing_x, drawing_y;\
    drawing_x = radius;\
    drawing_y = 0;\
    while (drawing_x > drawing_y)\
    {\
        drawing_point_index = (y + drawing_y / 2) * mWidth + (x + drawing_x);\
        WHAT_TO_DO(drawing_point_index, arg);\
        drawing_point_index = (y + drawing_y / 2) * mWidth + (x - drawing_x);\
        WHAT_TO_DO(drawing_point_index, arg);\
        drawing_point_index = (y - drawing_y / 2) * mWidth + (x + drawing_x);\
        WHAT_TO_DO(drawing_point_index, arg);\
        drawing_point_index = (y - drawing_y / 2) * mWidth + (x - drawing_x);\
        WHAT_TO_DO(drawing_point_index, arg);\
        drawing_point_index = (y + drawing_x / 2) * mWidth + (x + drawing_y);\
        WHAT_TO_DO(drawing_point_index, arg);\
        drawing_point_index = (y + drawing_x / 2) * mWidth + (x - drawing_y);\
        WHAT_TO_DO(drawing_point_index, arg);\
        drawing_point_index = (y - drawing_x / 2) * mWidth + (x + drawing_y);\
        WHAT_TO_DO(drawing_point_index, arg);\
        drawing_point_index = (y - drawing_x / 2) * mWidth + (x - drawing_y);\
        WHAT_TO_DO(drawing_point_index, arg);\
        radius -= (drawing_y++ << 1) - 1;\
        if (radius < 0)\
        {\
            radius += (--drawing_x) << 1;\
        }\
    }

#define SET_PIXEL_AT(pixel_index, set_pixel) \
    if (mpBuffer[pixel_index] != set_pixel)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index] = set_pixel;\
    }

#define SET_BACKGROUND_AT(pixel_index, set_color) \
    if (mpBuffer[pixel_index].mBackgroundColor != set_color)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index].mBackgroundColor = set_color;\
    }

#define SET_CHARACTER_AT(pixel_index, set_color) \
    if (mpBuffer[pixel_index].GetCharacter() != character ||\
        mpBuffer[pixel_index].mForegroundColor != set_color)\
    {\
        mpChangedPoints[pixel_index] = true;\
        mpBuffer[pixel_index].SetCharacterNoCheck(character);\
        mpBuffer[pixel_index].mForegroundColor = set_color;\
    }

#define CHECK_CHAR_AND_CORRECT(character) \
    if (character < 32 || character == 127)\
    {\
        character = 32;\
    }

void Surface::DrawCircle(int x, int y,
                         int radius,
                         const Pixel* pPixel,
                         int outlineWidth = 1)
{
    DRAW_CIRCLE(SET_PIXEL_AT, *pPixel);
}

void Surface::DrawBackgroundCircle(int x, int y,
                                   int radius,
                                   const Color* pColor,
                                   int outlineWidth = 1)
{
    DRAW_CIRCLE(SET_BACKGROUND_AT, *pColor);
}

void Surface::DrawBackgroundCircle(int x, int y,
                                   int radius,
                                   int r, int g, int b,
                                   int outlineWidth = 1)
{
    Color circle_color(r, g, b);

    DRAW_CIRCLE(SET_BACKGROUND_AT, circle_color);
}

void Surface::DrawBackgroundCircleHsv(int x, int y,
                                      int radius,
                                      int h, int s, int v,
                                      int outlineWidth = 1)
{
    Color circle_color;
    circle_color.SetHsv(h, s, v);

    DRAW_CIRCLE(SET_BACKGROUND_AT, circle_color);
}

void Surface::DrawCharCircle(int x, int y,
                             int radius,
                             char character, const Color* pColor,
                             int outlineWidth = 1)
{
    DRAW_CIRCLE(SET_CHARACTER_AT, *pColor);
}

void Surface::DrawCharCircle(int x, int y,
                             int radius,
                             char character, int r, int g, int b,
                             int outlineWidth = 1)
{
    Color char_color(r, g, b);

    DRAW_CIRCLE(SET_CHARACTER_AT, char_color);
}

void Surface::DrawCharCircleHsv(int x, int y,
                                int radius,
                                char character, int h, int s, int v,
                                int outlineWidth = 1)
{
    Color char_color;
    char_color.SetHsv(h, s, v);

    DRAW_CIRCLE(SET_CHARACTER_AT, char_color);
}

#undef DRAW_CIRCLE
#undef SET_PIXEL_AT
#undef SET_BACKGROUND_AT
#undef SET_CHARACTER_AT
#undef CHECK_CHAR_AND_CORRECT

void Surface::DrawString(int x, int y,
                         const char pString[],
                         const Color* pTextColor)
{
    char drawing_character;

    int drawing_character_index = y * mWidth + x;
    int drawing_x = x;

    for (int i = 0; ; i++)
    {
        drawing_character = pString[i];

        if (drawing_x >= mWidth)
        {
            break;
        }
        if (drawing_character == '\0')
        {
            break;
        }

        if (mpBuffer[drawing_character_index].GetCharacter() != drawing_character ||
            mpBuffer[drawing_character_index].mForegroundColor != *pTextColor)
        {
            mpChangedPoints[drawing_character_index] = true;
            mpBuffer[drawing_character_index].SetCharacter(drawing_character);
            mpBuffer[drawing_character_index].mForegroundColor = *pTextColor;
        }
        drawing_character_index++;
    }
}

void Surface::DrawString(int x, int y,
                         const char pString[],
                         int textR, int textG, int textB)
{
    Color text_color(textR, textG, textB);

    char drawing_character;

    int drawing_character_index = y * mWidth + x;
    int drawing_x = x;

    for (int i = 0; ; i++)
    {
        drawing_character = pString[i];

        if (drawing_x >= mWidth)
        {
            break;
        }
        if (drawing_character == '\0')
        {
            break;
        }

        if (mpBuffer[drawing_character_index].GetCharacter() != drawing_character ||
            mpBuffer[drawing_character_index].mForegroundColor != text_color)
        {
            mpChangedPoints[drawing_character_index] = true;
            mpBuffer[drawing_character_index].SetCharacter(drawing_character);
            mpBuffer[drawing_character_index].mForegroundColor = text_color;
        }
        drawing_character_index++;
    }
}

void Surface::DrawStringHsv(int x, int y,
                            const char pString[],
                            int textH, int textS, int textV)
{
    Color text_color;
    text_color.SetHsv(textH, textS, textV);

    char drawing_character;

    int drawing_character_index = y * mWidth + x;
    int drawing_x = x;

    for (int i = 0; ; i++)
    {
        drawing_character = pString[i];

        if (drawing_x >= mWidth)
        {
            break;
        }
        if (drawing_character == '\0')
        {
            break;
        }

        if (mpBuffer[drawing_character_index].GetCharacter() != drawing_character ||
            mpBuffer[drawing_character_index].mForegroundColor != text_color)
        {
            mpChangedPoints[drawing_character_index] = true;
            mpBuffer[drawing_character_index].SetCharacter(drawing_character);
            mpBuffer[drawing_character_index].mForegroundColor = text_color;
        }
        drawing_character_index++;
    }
}


void Surface::Print() const
{
    Color last_background_color = mpBuffer[0].mBackgroundColor;
    Color last_foreground_color = mpBuffer[0].mForegroundColor;
    Pixel printing_pixel;

    last_background_color.ApplyToBackgroundColor();
    last_foreground_color.ApplyToForegroundColor();

    int cursor_position[2] = {0, 0};

    int first_column_index = 0;

    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            if (mpChangedPoints[first_column_index + j])
            {
                moveCursorToRight(j - cursor_position[0]);
                printing_pixel = mpBuffer[first_column_index + j];


                if (printing_pixel.mBackgroundColor != last_background_color)
                {
                    printing_pixel.mBackgroundColor.ApplyToBackgroundColor();
                    last_background_color = printing_pixel.mBackgroundColor;
                }
                if (printing_pixel.mForegroundColor != last_foreground_color)
                {
                    printing_pixel.mForegroundColor.ApplyToForegroundColor();
                    last_foreground_color = printing_pixel.mForegroundColor;
                }


                printf("%c", printing_pixel.GetCharacter());

                mpChangedPoints[first_column_index + j] = false;
                cursor_position[0] = j + 1;

            }
        }

        first_column_index += mWidth;

        printf("\033[1E");
        cursor_position[1]++;
        cursor_position[0] = 0;
    }


    printf("\033[m");
    printf("\033[%dD\033[%dA", cursor_position[0], cursor_position[1]);
    return;
}


Pixel Surface::GetPixelAt(int x, int y) const
{
    return mpBuffer[y * mWidth + x];
}

int Surface::GetWidth(void) const
{
    return mWidth;
}

int Surface::GetHeight(void) const
{
    return mHeight;
}

void Surface::GetWH(int* sizeDes) const
{
    sizeDes[0] = mWidth;
    sizeDes[1] = mHeight;
    return;
}



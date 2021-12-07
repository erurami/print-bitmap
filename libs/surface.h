#pragma once

/* =============================== prototypes ============================ */

void moveCursorToLeft(int x);
void moveCursorToRight(int x);
void moveCursorToUp(int y);
void moveCursorToDown(int y);

class Color
{

    private:

        unsigned short int mRgb[3];
        unsigned short int mHsv[3];


        bool RgbFromHsvMember();
        bool HsvFromRgbMember();

        bool CheckAndFixRgbMember();
        bool CheckAndFixHsvMember();

    public:

        Color();
        Color(int r, int g, int b);

        int GetR(void) const;
        int GetG(void) const;
        int GetB(void) const;

        int GetH(void) const;
        int GetS(void) const;
        int GetV(void) const;

        void GetRgb(int* pDestination) const;
        void GetHsv(int* pDestination) const;


        bool SetRValue(int r);
        bool SetGValue(int g);
        bool SetBValue(int b);

        bool SetHValue(int h);
        bool SetSValue(int s);
        bool SetVValue(int v);

        bool SetRgb(int r, int g, int b);
        bool SetHsv(int h, int s, int v);


        void ApplyToBackgroundColor(void);
        void ApplyToForegroundColor(void);


        Color operator +  (const Color& rhs) const;

        bool  operator == (const Color& rhs) const;
        bool  operator != (const Color& rhs) const;

};


class Pixel
{

    private:

        char mCharacter;

    public:

        Pixel();
        Pixel(char character);
        Pixel(const Color* pForegroundColor, const Color* pBackgroundColor, char character);

        Color mForegroundColor;
        Color mBackgroundColor;

        char GetCharacter() const;
        void SetCharacter(char character);
        void SetCharacterNoCheck(char character);

        void SetForeColor(const Color* pColor);
        void SetForeColor(int r, int g, int b);
        void SetForeColorHsv(int h, int s, int v);

        void SetBackColor(const Color* pColor);
        void SetBackColor(int r, int g, int b);
        void SetBackColorHsv(int h, int s, int v);


        void Print() const;

        bool operator == (const Pixel& rhx) const;
        bool operator != (const Pixel& rhx) const;

};


class Surface
{

    private:

        Pixel* mpBuffer;
        bool* mpChangedPoints;

        int mWidth;
        int mHeight;


        bool IsThisInSurface(int x, int y);

    public:

        explicit Surface(int width, int height);
        explicit Surface(int width, int height, const Pixel* pFillBy);

        ~Surface();


        void Blit(int x, int y, const Surface* pSurface);
        void Fill(const Pixel* pFillBy);

        void FillBackground(const Color* pFillColor);
        void FillBackground(int r, int g, int b);
        void FillBackgroundHsv(int h, int s, int v);

        void FillForeground(const Color* pFillColor);
        void FillForeground(int r, int g, int b);
        void FillForegroundHsv(int h, int s, int v);

        void FillChar(char fillBy);


        bool SetPixelAt(int x, int y, const Pixel* pSetPixel);

        bool SetBackgroundAt(int x, int y, const Color* pSetColor);
        bool SetBackgroundAt(int x, int y, int r, int g, int b);
        bool SetBackgroundHsvAt(int x, int y, int h, int s, int v);

        bool SetForegroundAt(int x, int y, const Color* pSetColor);
        bool SetForegroundAt(int x, int y, int r, int g, int b);
        bool SetForegroundHsvAt(int x, int y, int h, int s, int v);

        bool SetCharAt(int x, int y, char setChar);



        void DrawRectangle(int x, int y,
                           int width, int height,
                           const Pixel* pPixel,
                           int outlineWidth);

        void DrawBackgroundRectangle(int x, int y,
                                     int width, int height,
                                     const Color* pColor,
                                     int outlineWidth);

        void DrawBackgroundRectangle(int x, int y,
                                     int width, int height,
                                     int r, int g, int b,
                                     int outlineWidth);

        void DrawBackgroundRectangleHsv(int x, int y,
                                        int width, int height,
                                        int h, int s, int v,
                                        int outlineWidth);

        void DrawCharRectangle(int x, int y,
                               int width, int height,
                               char character, const Color* color,
                               int outlineWidth);

        void DrawCharRectangle(int x, int y,
                               int width, int height,
                               char character, int r, int g, int b,
                               int outlineWidth);

        void DrawCharRectangleHsv(int x, int y,
                                  int width, int height,
                                  char character, int h, int s, int v,
                                  int outlineWidth);

        void DrawLine(int x1, int y1,
                      int x2, int y2,
                      const Pixel* pPixel,
                      int lineWidth);

        void DrawBackgroundLine(int x1, int y1,
                                int x2, int y2,
                                const Color* pColor,
                                int lineWidth);

        void DrawBackgroundLine(int x1, int y1,
                                int x2, int y2,
                                int r, int g, int b,
                                int lineWidth);

        void DrawBackgroundLineHsv(int x1, int y1,
                                   int x2, int y2,
                                   int h, int s, int v,
                                   int lineWidth);

        void DrawCharLine(int x1, int y1,
                          int x2, int y2,
                          const char character, const Color* pColor,
                          int lineWidth);

        void DrawCharLine(int x1, int y1,
                          int x2, int y2,
                          const char character, int r, int g, int b,
                          int lineWidth);

        void DrawCharLineHsv(int x1, int y1,
                             int x2, int y2,
                             const char character, int h, int s, int v,
                             int lineWidth);

        void DrawCircle(int x, int y,
                        int radius,
                        const Pixel* pPixel,
                        int outlineWidth);

        void DrawBackgroundCircle(int x, int y,
                                  int radius,
                                  const Color* pColor,
                                  int outlineWidth);

        void DrawBackgroundCircle(int x, int y,
                                  int radius,
                                  int r, int g, int b,
                                  int outlineWidth);

        void DrawBackgroundCircleHsv(int x, int y,
                                     int radius,
                                     int h, int s, int v,
                                     int outlineWidth);

        void DrawCharCircle(int x, int y,
                            int radius,
                            char character, const Color* pColor,
                            int outlineWidth);

        void DrawCharCircle(int x, int y,
                            int radius,
                            char character, int r, int g, int b,
                            int outlineWidth);

        void DrawCharCircleHsv(int x, int y,
                               int radius,
                               char character, int h, int s, int v,
                               int outlineWidth);

        void DrawString(int x, int y,
                        const char pString[],
                        const Color* pTextColor);

        void DrawString(int x, int y,
                        const char pString[],
                        int textR, int textG, int textB);

        void DrawStringHsv(int x, int y,
                           const char pString[],
                           int textH, int textS, int textV);


        void Print(void) const;



        Pixel GetPixelAt(int x, int y) const;
        char  GetCharAt(int x, int y) const;
        Color GetBackgroundColorAt(int x, int y) const;
        Color GetForegroundColorAt(int x, int y) const;

        int GetWidth (void) const;
        int GetHeight(void) const;

        void GetWH(int* sizeDes) const;

        Surface& operator  = (const Surface& rhs);

};


/* ========================================================================= */

#include "surface.cpp"

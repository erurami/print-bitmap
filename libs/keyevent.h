#pragma once

#include <conio.h>


typedef struct
{
    char Type;
    long Info;
} Event;


int   getEvents(Event* pEventDes, int maxEventGet);
Event waitEvent();


#define NORMAL_CHARACTER_KEY_EVENT 0
#define SPECIAL_CHARACTER_KEY_EVENT 1

/*normal key events*/

#define K_SPACE 32

/*!*/
#define K_EXCLAMATION 33
/*"*/
#define K_DOUBLE_QUOTATION 34
/*#*/
#define K_NUMBER_SIGN 35
/*$*/
#define K_DOLLAR_SIGN 36
/*%*/
#define K_PERCENT_SIGN 37
/*&*/
#define K_AND 38
/*'*/
#define K_APOSTROPHE 39
/*(*/
#define K_ROUND_BRACKET1 40
/*)*/
#define K_ROUND_BRACKET2 41
/***/
#define K_ASTERISK 42
/*+*/
#define K_PLUS 43
/*,*/
#define K_COMMA 44
/*-*/
#define K_MINUS 45
/*.*/
#define K_FULL_STOP 46
#define K_PERIOD 46
/*'/'*/
#define K_SLASH 47

#define K_0 48
#define K_1 49
#define K_2 50
#define K_3 51
#define K_4 52
#define K_5 53
#define K_6 54
#define K_7 55
#define K_8 56
#define K_9 57

/*:*/
#define K_COLON 58
/*;*/
#define K_SEMICOLON 59
/*<*/
#define K_LESS_THAN 60
/*=*/
#define K_EQUALS 61
/*>*/
#define K_GREATER_THAN 62
/*?*/
#define K_QUESTION_MARK 63
/*`*/
#define K_GRAVE_ACCENT 64

#define K_SHIFT_A 65
#define K_SHIFT_B 66
#define K_SHIFT_C 67
#define K_SHIFT_D 68
#define K_SHIFT_E 69
#define K_SHIFT_F 70
#define K_SHIFT_G 71
#define K_SHIFT_H 72
#define K_SHIFT_I 73
#define K_SHIFT_J 74
#define K_SHIFT_K 75
#define K_SHIFT_L 76
#define K_SHIFT_M 77
#define K_SHIFT_N 78
#define K_SHIFT_O 79
#define K_SHIFT_P 80
#define K_SHIFT_Q 81
#define K_SHIFT_R 82
#define K_SHIFT_S 83
#define K_SHIFT_T 84
#define K_SHIFT_U 85
#define K_SHIFT_V 86
#define K_SHIFT_W 87
#define K_SHIFT_X 88
#define K_SHIFT_Y 89
#define K_SHIFT_Z 90

/*[*/
#define K_SQUARE_BRACKET1 91
/*\*/
#define K_BACKSLASH 92
/*]*/
#define K_SQUARE_BRACKET2 93
/*^*/
#define K_CARET 94
/*_*/
#define K_UNDERSCORE 95
/*@*/
#define K_AT_SIGN 96

#define K_A 97
#define K_B 98
#define K_C 99
#define K_D 100
#define K_E 101
#define K_F 102
#define K_G 103
#define K_H 104
#define K_I 105
#define K_J 106
#define K_K 107
#define K_L 108
#define K_M 109
#define K_N 110
#define K_O 111
#define K_P 112
#define K_Q 113
#define K_R 114
#define K_S 115
#define K_T 116
#define K_U 117
#define K_V 118
#define K_W 119
#define K_X 120
#define K_Y 121
#define K_Z 122

/*{*/
#define K_CURLY_BRACKET1 123
/*|*/
#define K_VERTICAL_BAR 124
/*}*/
#define K_CURLY_BRACKET2 125


/*special key events*/

#define K_CTRL_A 1
#define K_CTRL_B 2
#define K_CTRL_C 3
#define K_CTRL_D 4
#define K_CTRL_E 5
#define K_CTRL_F 6
#define K_CTRL_G 7
#define K_CTRL_H 8
#define K_CTRL_I 9
#define K_CTRL_J 10
#define K_CTRL_K 11
#define K_CTRL_L 12
#define K_CTRL_M 13
#define K_CTRL_N 14
#define K_CTRL_O 15
#define K_CTRL_P 16
#define K_CTRL_Q 17
#define K_CTRL_R 18
#define K_CTRL_S 19
#define K_CTRL_T 20
#define K_CTRL_U 21
#define K_CTRL_V 22
#define K_CTRL_W 23
#define K_CTRL_X 24
#define K_CTRL_Y 25
#define K_CTRL_Z 26

#define K_ARROW_LEFT  75
#define K_ARROW_UP    72
#define K_ARROW_RIGHT 77
#define K_ARROW_DOWN  80

#include "keyevent.cpp"

/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef DESKADV_PALETTE_H
#define DESKADV_PALETTE_H

namespace Deskadv {

// TODO: Not sure if palette uses any of the Win3.1 default palette indexes
//       i.e. whether the palette setting skips these or overwrites them.
// 1 - dark red
// 2 - dark green
// 3 - dark yellow
// 4 - dark blue
// 5 - dark magenta
// 6 - dark cyan
// 7 - light grey
// 8 - money green
// 9 - sky blue
// --
// 246 - cream
// 247 - medium grey
// 248 - dark grey
// 249 - red
// 250 - green
// 251 - yellow
// 252 - blue
// 253 - magenta
// 254 - cyan
// --
// 0 - black and 255 - white are also in W3.1 default palette, but are set here
// to the same values so not critical if they are set or skipped.

const static uint   TRANSPARENT =   0;
const static uint         BLACK =   0;
const static uint         WHITE = 255;

const static uint    LIGHT_GREY =   7;
const static uint   MEDIUM_GREY = 247;
const static uint     DARK_GREY = 248;

const static uint  ARROW_SHADOW =  24;
const static uint         GREEN = 200;
const static uint HEALTH_YELLOW = 176;
const static uint    HEALTH_RED = 204;
const static uint    POWER_BLUE = 203;

// Data is RGB
static const uint8 indyPalette[256 * 3] = {
	0x00, 0x00, 0x00, // 00
	0x00, 0x00, 0x00, // 01
	0x00, 0x00, 0x00, // 02
	0x00, 0x00, 0x00, // 03
	0x00, 0x00, 0x00, // 04
	0x00, 0x00, 0x00, // 05
	0x00, 0x00, 0x00, // 06
	0xc1, 0xcc, 0xd9, // 07
	0x00, 0x00, 0x00, // 08
	0x00, 0x00, 0x00, // 09

	0xfb, 0xfb, 0xfb,  // 10
	0xe3, 0xe3, 0xe3,  // 11
	0xd3, 0xd3, 0xd3,  // 12
	0xc3, 0xc3, 0xc3,  // 13
	0xb3, 0xb3, 0xb3,  // 14
	0xab, 0xab, 0xab,  // 15
	0x9b, 0x9b, 0x9b,  // 16
	0x8b, 0x8b, 0x8b,  // 17
	0x7b, 0x7b, 0x7b,  // 18
	0x73, 0x73, 0x73,  // 19
	0x63, 0x63, 0x63,  // 20
	0x53, 0x53, 0x53,  // 21
	0x4b, 0x4b, 0x4b,  // 22
	0x3b, 0x3b, 0x3b,  // 23
	0x2b, 0x2b, 0x2b,  // 24
	0x23, 0x23, 0x23,  // 25
	0x00, 0xc7, 0x43,  // 26
	0x00, 0xb7, 0x3f,  // 27
	0x00, 0xab, 0x3f,  // 28
	0x00, 0x9f, 0x3b,  // 29
	0x00, 0x93, 0x37,  // 30
	0x00, 0x87, 0x33,  // 31
	0x00, 0x7b, 0x33,  // 32
	0x00, 0x6f, 0x2f,  // 33
	0x00, 0x63, 0x2b,  // 34
	0x00, 0x53, 0x23,  // 35
	0x00, 0x47, 0x1f,  // 36
	0x00, 0x37, 0x17,  // 37
	0x00, 0x27, 0x0f,  // 38
	0x00, 0x1b, 0x0b,  // 39
	0x00, 0x0b, 0x07,  // 40
	0x00, 0x00, 0x00,  // 41
	0x3b, 0xfb, 0x7b,  // 42
	0x6b, 0x7b, 0xc3,  // 43
	0x5b, 0x53, 0xab,  // 44
	0x53, 0x43, 0x93,  // 45
	0x53, 0x2b, 0x7b,  // 46
	0x4b, 0x1b, 0x63,  // 47
	0x3b, 0x13, 0x3b,  // 48
	0xab, 0xd7, 0xff,  // 49
	0x8f, 0xc3, 0xf3,  // 50
	0x73, 0xb3, 0xe7,  // 51
	0x5b, 0xa3, 0xdb,  // 52
	0x43, 0x97, 0xcf,  // 53
	0x2f, 0x8b, 0xc3,  // 54
	0x1b, 0x7f, 0xb7,  // 55
	0x0b, 0x73, 0xaf,  // 56
	0x00, 0x6b, 0xa3,  // 57
	0xeb, 0xff, 0xff,  // 58
	0xd7, 0xf3, 0xf3,  // 59
	0xc7, 0xe7, 0xe7,  // 60
	0xb7, 0xdb, 0xdb,  // 61
	0xa3, 0xcf, 0xcf,  // 62
	0x97, 0xc3, 0xc3,  // 63
	0x7f, 0xb3, 0xb3,  // 64
	0x63, 0xa3, 0xa3,  // 65
	0x4f, 0x93, 0x93,  // 66
	0x3b, 0x83, 0x83,  // 67
	0x2b, 0x73, 0x73,  // 68
	0x1b, 0x5f, 0x5f,  // 69
	0x0f, 0x4f, 0x4f,  // 70
	0x07, 0x3f, 0x3f,  // 71
	0x00, 0x2f, 0x2f,  // 72
	0x00, 0x1f, 0x1f,  // 73
	0x5b, 0xfb, 0xd3,  // 74
	0x43, 0xfb, 0xc3,  // 75
	0x23, 0xfb, 0xb3,  // 76
	0x00, 0xfb, 0xa3,  // 77
	0x00, 0xe3, 0x93,  // 78
	0x00, 0xcb, 0x83,  // 79
	0x00, 0xb3, 0x73,  // 80
	0x00, 0x9b, 0x63,  // 81
	0x00, 0x5b, 0x8b,  // 82
	0x00, 0x4f, 0x77,  // 83
	0x00, 0x43, 0x67,  // 84
	0x00, 0x37, 0x57,  // 85
	0x00, 0x2f, 0x47,  // 86
	0x00, 0x23, 0x37,  // 87
	0x00, 0x17, 0x27,  // 88
	0x00, 0x0f, 0x17,  // 89
	0x00, 0xfb, 0x4f,  // 90
	0x00, 0xef, 0x4b,  // 91
	0x00, 0xdf, 0x47,  // 92
	0x00, 0xd3, 0x47,  // 93
	0x00, 0x9f, 0x67,  // 94
	0x00, 0x7f, 0x5b,  // 95
	0x00, 0x63, 0x43,  // 96
	0x00, 0x47, 0x27,  // 97
	0x00, 0x2b, 0x1b,  // 98
	0x23, 0x23, 0x00,  // 99
	0x00, 0x00, 0x00,  // 100
	0x00, 0x00, 0x00,  // 101
	0x00, 0x00, 0x00,  // 102
	0x00, 0x00, 0x00,  // 103
	0x8b, 0x37, 0xdb,  // 104
	0x77, 0x2b, 0xb3,  // 105
	0xfb, 0xfb, 0xdb,  // 106
	0xfb, 0xfb, 0xbb,  // 107
	0xfb, 0xfb, 0x9b,  // 108
	0xfb, 0xfb, 0x7b,  // 109
	0xfb, 0xfb, 0x5b,  // 110
	0xfb, 0xfb, 0x43,  // 111
	0xfb, 0xfb, 0x23,  // 112
	0xfb, 0xfb, 0x00,  // 113
	0xe3, 0xe3, 0x00,  // 114
	0xcb, 0xcb, 0x00,  // 115
	0xb3, 0xb3, 0x00,  // 116
	0x9b, 0x9b, 0x00,  // 117
	0x83, 0x83, 0x00,  // 118
	0x73, 0x73, 0x00,  // 119
	0x5b, 0x5b, 0x00,  // 120
	0x43, 0x43, 0x00,  // 121
	0xff, 0xbf, 0x47,  // 122
	0xf7, 0xaf, 0x33,  // 123
	0xef, 0xa3, 0x1f,  // 124
	0xe7, 0x97, 0x0f,  // 125
	0xe3, 0x8b, 0x00,  // 126
	0xcb, 0x7b, 0x00,  // 127
	0xb3, 0x6b, 0x00,  // 128
	0x9b, 0x5b, 0x00,  // 129
	0x7b, 0x47, 0x00,  // 130
	0x5f, 0x37, 0x00,  // 131
	0x43, 0x27, 0x00,  // 132
	0x27, 0x17, 0x00,  // 133
	0xfb, 0x63, 0x5b,  // 134
	0xfb, 0x43, 0x43,  // 135
	0xfb, 0x23, 0x23,  // 136
	0xfb, 0x00, 0x00,  // 137
	0xfb, 0x00, 0x00,  // 138
	0xdb, 0x00, 0x00,  // 139
	0xc3, 0x00, 0x00,  // 140
	0xab, 0x00, 0x00,  // 141
	0x8b, 0x00, 0x00,  // 142
	0x73, 0x00, 0x00,  // 143
	0x5b, 0x00, 0x00,  // 144
	0x43, 0x00, 0x00,  // 145
	0xbf, 0xbb, 0xfb,  // 146
	0xaf, 0xab, 0xf7,  // 147
	0xa3, 0x9b, 0xf3,  // 148
	0x97, 0x8f, 0xef,  // 149
	0x87, 0x7f, 0xeb,  // 150
	0x7f, 0x73, 0xe7,  // 151
	0x6b, 0x5b, 0xdf,  // 152
	0x47, 0x3b, 0xcb,  // 153
	0xf7, 0xb3, 0x43,  // 154
	0xf7, 0xbb, 0x4f,  // 155
	0xf7, 0xc7, 0x5b,  // 156
	0xf7, 0xcf, 0x6b,  // 157
	0xf7, 0xd7, 0x77,  // 158
	0xf7, 0xdf, 0x83,  // 159
	0xf7, 0xe7, 0x93,  // 160
	0xf7, 0xcf, 0x6b,  // 161
	0x00, 0x43, 0xcb,  // 162
	0x00, 0x33, 0xbb,  // 163
	0x00, 0x23, 0xa3,  // 164
	0x00, 0x1b, 0x93,  // 165
	0x00, 0x0b, 0x7b,  // 166
	0x00, 0x00, 0x6b,  // 167
	0x00, 0x00, 0x53,  // 168
	0x00, 0x00, 0x43,  // 169
	0x00, 0xff, 0xff,  // 170
	0x00, 0xe3, 0xf7,  // 171
	0x00, 0xcf, 0xf3,  // 172
	0x00, 0xb7, 0xef,  // 173
	0x00, 0xa3, 0xeb,  // 174
	0x00, 0x8b, 0xe7,  // 175
	0x00, 0x77, 0xdf,  // 176
	0x00, 0x63, 0xdb,  // 177
	0x00, 0x4f, 0xd7,  // 178
	0x00, 0x3f, 0xd3,  // 179
	0x00, 0x2f, 0xcf,  // 180
	0x77, 0xc7, 0xe3,  // 181
	0x6b, 0xb7, 0xdb,  // 182
	0x63, 0xa7, 0xd3,  // 183
	0x5b, 0x97, 0xcb,  // 184
	0x53, 0x8b, 0xc3,  // 185
	0xdb, 0xeb, 0xfb,  // 186
	0xd3, 0xe3, 0xfb,  // 187
	0xc3, 0xdb, 0xfb,  // 188
	0xbb, 0xd3, 0xfb,  // 189
	0xb3, 0xcb, 0xfb,  // 190
	0xa3, 0xc3, 0xfb,  // 191
	0x9b, 0xbb, 0xfb,  // 192
	0x8f, 0xb7, 0xfb,  // 193
	0x83, 0xb3, 0xfb,  // 194
	0x73, 0xa3, 0xfb,  // 195
	0x63, 0x9b, 0xfb,  // 196
	0x5b, 0x93, 0xf3,  // 197
	0x5b, 0x8b, 0xeb,  // 198
	0x53, 0x8b, 0xdb,  // 199
	0x53, 0x83, 0xd3,  // 200
	0x4b, 0x7b, 0xcb,  // 201
	0x4b, 0x7b, 0xbb,  // 202
	0x43, 0x73, 0xb3,  // 203
	0x43, 0x6b, 0xab,  // 204
	0x3b, 0x63, 0xa3,  // 205
	0x3b, 0x63, 0x9b,  // 206
	0x33, 0x5b, 0x93,  // 207
	0x33, 0x5b, 0x8b,  // 208
	0x2b, 0x53, 0x83,  // 209
	0x2b, 0x4b, 0x73,  // 210
	0x23, 0x4b, 0x6b,  // 211
	0x23, 0x43, 0x5b,  // 212
	0x1b, 0x3b, 0x53,  // 213
	0x1b, 0x3b, 0x4b,  // 214
	0x1b, 0x33, 0x43,  // 215
	0x13, 0x2b, 0x3b,  // 216
	0x0b, 0x23, 0x2b,  // 217
	0x00, 0xab, 0x6f,  // 218
	0x00, 0xa3, 0x6b,  // 219
	0x00, 0x9f, 0x67,  // 220
	0x00, 0xa3, 0x6b,  // 221
	0x00, 0xab, 0x6f,  // 222
	0xe7, 0x93, 0x07,  // 223
	0xe7, 0x97, 0x0f,  // 224
	0xeb, 0x9f, 0x17,  // 225
	0xef, 0xa3, 0x23,  // 226
	0xf3, 0xab, 0x2b,  // 227
	0xf7, 0xb3, 0x37,  // 228
	0xef, 0xa7, 0x27,  // 229
	0xeb, 0x9f, 0x1b,  // 230
	0xe7, 0x97, 0x0f,  // 231
	0x0b, 0xcb, 0xfb,  // 232
	0x0b, 0xa3, 0xfb,  // 233
	0x0b, 0x73, 0xfb,  // 234
	0x0b, 0x4b, 0xfb,  // 235
	0x0b, 0x23, 0xfb,  // 236
	0x0b, 0x73, 0xfb,  // 237
	0x00, 0x13, 0x93,  // 238
	0x00, 0x0b, 0xd3,  // 239
	0x00, 0x00, 0x00,  // 240
	0x00, 0x00, 0x00,  // 241
	0x00, 0x00, 0x00,  // 242
	0x00, 0x00, 0x00,  // 243
	0x00, 0x00, 0x00,  // 244
	0x00, 0x00, 0x00,  // 245

	0x00, 0x00, 0x00, // 246
	0x83, 0x99, 0xb1, // 247
	0x4f, 0x65, 0x7d, // 248
	0x00, 0x00, 0x00, // 249
	0x00, 0x00, 0x00, // 250
	0x00, 0x00, 0x00, // 251
	0x00, 0x00, 0x00, // 252
	0x00, 0x00, 0x00, // 253
	0x00, 0x00, 0x00, // 254
	0xff, 0xff, 0xff  // 255
};

// Data is BGR, not RGB
static const uint8 yodaPalette[256 * 3] = {
	0x00, 0x00, 0x00, // 00
	0x00, 0x00, 0x00, // 01
	0x00, 0x00, 0x00, // 02
	0x00, 0x00, 0x00, // 03
	0x00, 0x00, 0x00, // 04
	0x00, 0x00, 0x00, // 05
	0x00, 0x00, 0x00, // 06
	0xd9, 0xcc, 0xc1, // 07
	0x00, 0x00, 0x00, // 08
	0x00, 0x00, 0x00, // 09

	0xff, 0xff, 0x8b, // 10
	0xc3, 0xcf, 0x4b, // 11
	0x8b, 0xa3, 0x1b, // 12
	0x57, 0x77, 0x00, // 13
	0x8b, 0xa3, 0x1b, // 14
	0xc3, 0xcf, 0x4b, // 15
	0xfb, 0xfb, 0xfb, // 16
	0xeb, 0xe7, 0xe7, // 17
	0xdb, 0xd3, 0xd3, // 18
	0xcb, 0xc3, 0xc3, // 19
	0xbb, 0xb3, 0xb3, // 20
	0xab, 0xa3, 0xa3, // 21
	0x9b, 0x8f, 0x8f, // 22
	0x8b, 0x7f, 0x7f, // 23
	0x7b, 0x6f, 0x6f, // 24
	0x67, 0x5b, 0x5b, // 25
	0x57, 0x4b, 0x4b, // 26
	0x47, 0x3b, 0x3b, // 27
	0x33, 0x2b, 0x2b, // 28
	0x23, 0x1b, 0x1b, // 29
	0x13, 0x0f, 0x0f, // 30
	0x00, 0x00, 0x00, // 31
	0x00, 0xc7, 0x43, // 32
	0x00, 0xb7, 0x43, // 33
	0x00, 0xab, 0x3f, // 34
	0x00, 0x9f, 0x3f, // 35
	0x00, 0x93, 0x3f, // 36
	0x00, 0x87, 0x3b, // 37
	0x00, 0x7b, 0x37, // 38
	0x00, 0x6f, 0x33, // 39
	0x00, 0x63, 0x33, // 40
	0x00, 0x53, 0x2b, // 41
	0x00, 0x47, 0x27, // 42
	0x00, 0x3b, 0x23, // 43
	0x00, 0x2f, 0x1b, // 44
	0x00, 0x23, 0x13, // 45
	0x00, 0x17, 0x0f, // 46
	0x00, 0x0b, 0x07, // 47
	0x4b, 0x7b, 0xbb, // 48
	0x43, 0x73, 0xb3, // 49
	0x43, 0x6b, 0xab, // 50
	0x3b, 0x63, 0xa3, // 51
	0x3b, 0x63, 0x9b, // 52
	0x33, 0x5b, 0x93, // 53
	0x33, 0x5b, 0x8b, // 54
	0x2b, 0x53, 0x83, // 55
	0x2b, 0x4b, 0x73, // 56
	0x23, 0x4b, 0x6b, // 57
	0x23, 0x43, 0x5f, // 58
	0x1b, 0x3b, 0x53, // 59
	0x1b, 0x37, 0x47, // 60
	0x1b, 0x33, 0x43, // 61
	0x13, 0x2b, 0x3b, // 62
	0x0b, 0x23, 0x2b, // 63
	0xd7, 0xff, 0xff, // 64
	0xbb, 0xef, 0xef, // 65
	0xa3, 0xdf, 0xdf, // 66
	0x8b, 0xcf, 0xcf, // 67
	0x77, 0xc3, 0xc3, // 68
	0x63, 0xb3, 0xb3, // 69
	0x53, 0xa3, 0xa3, // 70
	0x43, 0x93, 0x93, // 71
	0x33, 0x87, 0x87, // 72
	0x27, 0x77, 0x77, // 73
	0x1b, 0x67, 0x67, // 74
	0x13, 0x5b, 0x5b, // 75
	0x0b, 0x4b, 0x4b, // 76
	0x07, 0x3b, 0x3b, // 77
	0x00, 0x2b, 0x2b, // 78
	0x00, 0x1f, 0x1f, // 79
	0xdb, 0xeb, 0xfb, // 80
	0xd3, 0xe3, 0xfb, // 81
	0xc3, 0xdb, 0xfb, // 82
	0xbb, 0xd3, 0xfb, // 83
	0xb3, 0xcb, 0xfb, // 84
	0xa3, 0xc3, 0xfb, // 85
	0x9b, 0xbb, 0xfb, // 86
	0x8f, 0xb7, 0xfb, // 87
	0x83, 0xb3, 0xf7, // 88
	0x73, 0xa7, 0xfb, // 89
	0x63, 0x9b, 0xfb, // 90
	0x5b, 0x93, 0xf3, // 91
	0x5b, 0x8b, 0xeb, // 92
	0x53, 0x8b, 0xdb, // 93
	0x53, 0x83, 0xd3, // 94
	0x4b, 0x7b, 0xcb, // 95
	0x9b, 0xc7, 0xff, // 96
	0x8f, 0xb7, 0xf7, // 97
	0x87, 0xb3, 0xef, // 98
	0x7f, 0xa7, 0xf3, // 99
	0x73, 0x9f, 0xef, // 100
	0x53, 0x83, 0xcf, // 101
	0x3b, 0x6b, 0xb3, // 102
	0x2f, 0x5b, 0xa3, // 103
	0x23, 0x4f, 0x93, // 104
	0x1b, 0x43, 0x83, // 105
	0x13, 0x3b, 0x77, // 106
	0x0b, 0x2f, 0x67, // 107
	0x07, 0x27, 0x57, // 108
	0x00, 0x1b, 0x47, // 109
	0x00, 0x13, 0x37, // 110
	0x00, 0x0f, 0x2b, // 111
	0xfb, 0xfb, 0xe7, // 112
	0xf3, 0xf3, 0xd3, // 113
	0xeb, 0xe7, 0xc7, // 114
	0xe3, 0xdf, 0xb7, // 115
	0xdb, 0xd7, 0xa7, // 116
	0xd3, 0xcf, 0x97, // 117
	0xcb, 0xc7, 0x8b, // 118
	0xc3, 0xbb, 0x7f, // 119
	0xbb, 0xb3, 0x73, // 120
	0xaf, 0xa7, 0x63, // 121
	0x9b, 0x93, 0x47, // 122
	0x87, 0x7b, 0x33, // 123
	0x6f, 0x67, 0x1f, // 124
	0x5b, 0x53, 0x0f, // 125
	0x47, 0x43, 0x00, // 126
	0x37, 0x33, 0x00, // 127
	0xff, 0xf7, 0xf7, // 128
	0xef, 0xdf, 0xdf, // 129
	0xdf, 0xc7, 0xc7, // 130
	0xcf, 0xb3, 0xb3, // 131
	0xbf, 0x9f, 0x9f, // 132
	0xb3, 0x8b, 0x8b, // 133
	0xa3, 0x7b, 0x7b, // 134
	0x93, 0x6b, 0x6b, // 135
	0x83, 0x57, 0x57, // 136
	0x73, 0x4b, 0x4b, // 137
	0x67, 0x3b, 0x3b, // 138
	0x57, 0x2f, 0x2f, // 139
	0x47, 0x27, 0x27, // 140
	0x37, 0x1b, 0x1b, // 141
	0x27, 0x13, 0x13, // 142
	0x1b, 0x0b, 0x0b, // 143
	0xf7, 0xb3, 0x37, // 144
	0xe7, 0x93, 0x07, // 145
	0xfb, 0x53, 0x0b, // 146
	0xfb, 0x00, 0x00, // 147
	0xcb, 0x00, 0x00, // 148
	0x9f, 0x00, 0x00, // 149
	0x6f, 0x00, 0x00, // 150
	0x43, 0x00, 0x00, // 151
	0xbf, 0xbb, 0xfb, // 152
	0x8f, 0x8b, 0xfb, // 153
	0x5f, 0x5b, 0xfb, // 154
	0x93, 0xbb, 0xff, // 155
	0x5f, 0x97, 0xf7, // 156
	0x3b, 0x7b, 0xef, // 157
	0x23, 0x63, 0xc3, // 158
	0x13, 0x53, 0xb3, // 159
	0x00, 0x00, 0xff, // 160
	0x00, 0x00, 0xef, // 161
	0x00, 0x00, 0xe3, // 162
	0x00, 0x00, 0xd3, // 163
	0x00, 0x00, 0xc3, // 164
	0x00, 0x00, 0xb7, // 165
	0x00, 0x00, 0xa7, // 166
	0x00, 0x00, 0x9b, // 167
	0x00, 0x00, 0x8b, // 168
	0x00, 0x00, 0x7f, // 169
	0x00, 0x00, 0x6f, // 170
	0x00, 0x00, 0x63, // 171
	0x00, 0x00, 0x53, // 172
	0x00, 0x00, 0x47, // 173
	0x00, 0x00, 0x37, // 174
	0x00, 0x00, 0x2b, // 175
	0x00, 0xff, 0xff, // 176
	0x00, 0xe3, 0xf7, // 177
	0x00, 0xcf, 0xf3, // 178
	0x00, 0xb7, 0xef, // 179
	0x00, 0xa3, 0xeb, // 180
	0x00, 0x8b, 0xe7, // 181
	0x00, 0x77, 0xdf, // 182
	0x00, 0x63, 0xdb, // 183
	0x00, 0x4f, 0xd7, // 184
	0x00, 0x3f, 0xd3, // 185
	0x00, 0x2f, 0xcf, // 186
	0x97, 0xff, 0xff, // 187
	0x83, 0xdf, 0xef, // 188
	0x73, 0xc3, 0xdf, // 189
	0x5f, 0xa7, 0xcf, // 190
	0x53, 0x8b, 0xc3, // 191
	0x2b, 0x2b, 0x00, // 192
	0x23, 0x23, 0x00, // 193
	0x1b, 0x1b, 0x00, // 194
	0x13, 0x13, 0x00, // 195
	0xff, 0x0b, 0x00, // 196
	0xff, 0x00, 0x4b, // 197
	0xff, 0x00, 0xa3, // 198
	0xff, 0x00, 0xff, // 199
	0x00, 0xff, 0x00, // 200
	0x00, 0x4b, 0x00, // 201
	0xff, 0xff, 0x00, // 202
	0xff, 0x33, 0x2f, // 203
	0x00, 0x00, 0xff, // 204
	0x00, 0x1f, 0x97, // 205
	0xdf, 0x00, 0xff, // 206
	0x73, 0x00, 0x77, // 207
	0x6b, 0x7b, 0xc3, // 208
	0x57, 0x57, 0xab, // 209
	0x57, 0x47, 0x93, // 210
	0x53, 0x37, 0x7f, // 211
	0x4f, 0x27, 0x67, // 212
	0x47, 0x1b, 0x4f, // 213
	0x3b, 0x13, 0x3b, // 214
	0x27, 0x77, 0x77, // 215
	0x23, 0x73, 0x73, // 216
	0x1f, 0x6f, 0x6f, // 217
	0x1b, 0x6b, 0x6b, // 218
	0x1b, 0x67, 0x67, // 219
	0x1b, 0x6b, 0x6b, // 220
	0x1f, 0x6f, 0x6f, // 221
	0x23, 0x73, 0x73, // 222
	0x27, 0x77, 0x77, // 223
	0xff, 0xff, 0xef, // 224
	0xf7, 0xf7, 0xdb, // 225
	0xf3, 0xef, 0xcb, // 226
	0xef, 0xeb, 0xbb, // 227
	0xf3, 0xef, 0xcb, // 228
	0xe7, 0x93, 0x07, // 229
	0xe7, 0x97, 0x0f, // 230
	0xeb, 0x9f, 0x17, // 231
	0xef, 0xa3, 0x23, // 232
	0xf3, 0xab, 0x2b, // 233
	0xf7, 0xb3, 0x37, // 234
	0xef, 0xa7, 0x27, // 235
	0xeb, 0x9f, 0x1b, // 236
	0xe7, 0x97, 0x0f, // 237
	0x0b, 0xcb, 0xfb, // 238
	0x0b, 0xa3, 0xfb, // 239
	0x0b, 0x73, 0xfb, // 240
	0x0b, 0x4b, 0xfb, // 241
	0x0b, 0x23, 0xfb, // 242
	0x0b, 0x73, 0xfb, // 243
	0x00, 0x13, 0x93, // 244
	0x00, 0x0b, 0xd3, // 245

	0x00, 0x00, 0x00, // 246
	0xb1, 0x99, 0x83, // 247
	0x7d, 0x65, 0x4f, // 248
	0x00, 0x00, 0x00, // 249
	0x00, 0x00, 0x00, // 250
	0x00, 0x00, 0x00, // 251
	0x00, 0x00, 0x00, // 252
	0x00, 0x00, 0x00, // 253
	0x00, 0x00, 0x00, // 254
	0xff, 0xff, 0xff  // 255
	};

} // End of namespace Deskadv

#endif

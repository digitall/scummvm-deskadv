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

static const uint8 palette[1024] = {
	0x00, 0x00, 0x00, 0x00, // 00
	0x00, 0x00, 0x00, 0x00, // 01
	0x00, 0x00, 0x00, 0x00, // 02
	0x00, 0x00, 0x00, 0x00, // 03
	0x00, 0x00, 0x00, 0x00, // 04
	0x00, 0x00, 0x00, 0x00, // 05
	0x00, 0x00, 0x00, 0x00, // 06
	0x00, 0x00, 0x00, 0x00, // 07
	0x00, 0x00, 0x00, 0x00, // 08
	0x00, 0x00, 0x00, 0x00, // 09
	0xff, 0xff, 0x8b, 0x00, // 10
	0xc3, 0xcf, 0x4b, 0x00, // 11
	0x8b, 0xa3, 0x1b, 0x00, // 12
	0x57, 0x77, 0x00, 0x00, // 13
	0x8b, 0xa3, 0x1b, 0x00, // 14
	0xc3, 0xcf, 0x4b, 0x00, // 15
	0xfb, 0xfb, 0xfb, 0x00, // 16
	0xeb, 0xe7, 0xe7, 0x00, // 17
	0xdb, 0xd3, 0xd3, 0x00, // 18
	0xcb, 0xc3, 0xc3, 0x00, // 19
	0xbb, 0xb3, 0xb3, 0x00, // 20
	0xab, 0xa3, 0xa3, 0x00, // 21
	0x9b, 0x8f, 0x8f, 0x00, // 22
	0x8b, 0x7f, 0x7f, 0x00, // 23
	0x7b, 0x6f, 0x6f, 0x00, // 24
	0x67, 0x5b, 0x5b, 0x00, // 25
	0x57, 0x4b, 0x4b, 0x00, // 26
	0x47, 0x3b, 0x3b, 0x00, // 27
	0x33, 0x2b, 0x2b, 0x00, // 28
	0x23, 0x1b, 0x1b, 0x00, // 29
	0x13, 0x0f, 0x0f, 0x00, // 30
	0x00, 0x00, 0x00, 0x00, // 31
	0x00, 0xc7, 0x43, 0x00, // 32
	0x00, 0xb7, 0x43, 0x00, // 33
	0x00, 0xab, 0x3f, 0x00, // 34
	0x00, 0x9f, 0x3f, 0x00, // 35
	0x00, 0x93, 0x3f, 0x00, // 36
	0x00, 0x87, 0x3b, 0x00, // 37
	0x00, 0x7b, 0x37, 0x00, // 38
	0x00, 0x6f, 0x33, 0x00, // 39
	0x00, 0x63, 0x33, 0x00, // 40
	0x00, 0x53, 0x2b, 0x00, // 41
	0x00, 0x47, 0x27, 0x00, // 42
	0x00, 0x3b, 0x23, 0x00, // 43
	0x00, 0x2f, 0x1b, 0x00, // 44
	0x00, 0x23, 0x13, 0x00, // 45
	0x00, 0x17, 0x0f, 0x00, // 46
	0x00, 0x0b, 0x07, 0x00, // 47
	0x4b, 0x7b, 0xbb, 0x00, // 48
	0x43, 0x73, 0xb3, 0x00, // 49
	0x43, 0x6b, 0xab, 0x00, // 50
	0x3b, 0x63, 0xa3, 0x00, // 51
	0x3b, 0x63, 0x9b, 0x00, // 52
	0x33, 0x5b, 0x93, 0x00, // 53
	0x33, 0x5b, 0x8b, 0x00, // 54
	0x2b, 0x53, 0x83, 0x00, // 55
	0x2b, 0x4b, 0x73, 0x00, // 56
	0x23, 0x4b, 0x6b, 0x00, // 57
	0x23, 0x43, 0x5f, 0x00, // 58
	0x1b, 0x3b, 0x53, 0x00, // 59
	0x1b, 0x37, 0x47, 0x00, // 60
	0x1b, 0x33, 0x43, 0x00, // 61
	0x13, 0x2b, 0x3b, 0x00, // 62
	0x0b, 0x23, 0x2b, 0x00, // 63
	0xd7, 0xff, 0xff, 0x00, // 64
	0xbb, 0xef, 0xef, 0x00, // 65
	0xa3, 0xdf, 0xdf, 0x00, // 66
	0x8b, 0xcf, 0xcf, 0x00, // 67
	0x77, 0xc3, 0xc3, 0x00, // 68
	0x63, 0xb3, 0xb3, 0x00, // 69
	0x53, 0xa3, 0xa3, 0x00, // 70
	0x43, 0x93, 0x93, 0x00, // 71
	0x33, 0x87, 0x87, 0x00, // 72
	0x27, 0x77, 0x77, 0x00, // 73
	0x1b, 0x67, 0x67, 0x00, // 74
	0x13, 0x5b, 0x5b, 0x00, // 75
	0x0b, 0x4b, 0x4b, 0x00, // 76
	0x07, 0x3b, 0x3b, 0x00, // 77
	0x00, 0x2b, 0x2b, 0x00, // 78
	0x00, 0x1f, 0x1f, 0x00, // 79
	0xdb, 0xeb, 0xfb, 0x00, // 80
	0xd3, 0xe3, 0xfb, 0x00, // 81
	0xc3, 0xdb, 0xfb, 0x00, // 82
	0xbb, 0xd3, 0xfb, 0x00, // 83
	0xb3, 0xcb, 0xfb, 0x00, // 84
	0xa3, 0xc3, 0xfb, 0x00, // 85
	0x9b, 0xbb, 0xfb, 0x00, // 86
	0x8f, 0xb7, 0xfb, 0x00, // 87
	0x83, 0xb3, 0xf7, 0x00, // 88
	0x73, 0xa7, 0xfb, 0x00, // 89
	0x63, 0x9b, 0xfb, 0x00, // 90
	0x5b, 0x93, 0xf3, 0x00, // 91
	0x5b, 0x8b, 0xeb, 0x00, // 92
	0x53, 0x8b, 0xdb, 0x00, // 93
	0x53, 0x83, 0xd3, 0x00, // 94
	0x4b, 0x7b, 0xcb, 0x00, // 95
	0x9b, 0xc7, 0xff, 0x00, // 96
	0x8f, 0xb7, 0xf7, 0x00, // 97
	0x87, 0xb3, 0xef, 0x00, // 98
	0x7f, 0xa7, 0xf3, 0x00, // 99
	0x73, 0x9f, 0xef, 0x00, // 100
	0x53, 0x83, 0xcf, 0x00, // 101
	0x3b, 0x6b, 0xb3, 0x00, // 102
	0x2f, 0x5b, 0xa3, 0x00, // 103
	0x23, 0x4f, 0x93, 0x00, // 104
	0x1b, 0x43, 0x83, 0x00, // 105
	0x13, 0x3b, 0x77, 0x00, // 106
	0x0b, 0x2f, 0x67, 0x00, // 107
	0x07, 0x27, 0x57, 0x00, // 108
	0x00, 0x1b, 0x47, 0x00, // 109
	0x00, 0x13, 0x37, 0x00, // 110
	0x00, 0x0f, 0x2b, 0x00, // 111
	0xfb, 0xfb, 0xe7, 0x00, // 112
	0xf3, 0xf3, 0xd3, 0x00, // 113
	0xeb, 0xe7, 0xc7, 0x00, // 114
	0xe3, 0xdf, 0xb7, 0x00, // 115
	0xdb, 0xd7, 0xa7, 0x00, // 116
	0xd3, 0xcf, 0x97, 0x00, // 117
	0xcb, 0xc7, 0x8b, 0x00, // 118
	0xc3, 0xbb, 0x7f, 0x00, // 119
	0xbb, 0xb3, 0x73, 0x00, // 120
	0xaf, 0xa7, 0x63, 0x00, // 121
	0x9b, 0x93, 0x47, 0x00, // 122
	0x87, 0x7b, 0x33, 0x00, // 123
	0x6f, 0x67, 0x1f, 0x00, // 124
	0x5b, 0x53, 0x0f, 0x00, // 125
	0x47, 0x43, 0x00, 0x00, // 126
	0x37, 0x33, 0x00, 0x00, // 127
	0xff, 0xf7, 0xf7, 0x00, // 128
	0xef, 0xdf, 0xdf, 0x00, // 129
	0xdf, 0xc7, 0xc7, 0x00, // 130
	0xcf, 0xb3, 0xb3, 0x00, // 131
	0xbf, 0x9f, 0x9f, 0x00, // 132
	0xb3, 0x8b, 0x8b, 0x00, // 133
	0xa3, 0x7b, 0x7b, 0x00, // 134
	0x93, 0x6b, 0x6b, 0x00, // 135
	0x83, 0x57, 0x57, 0x00, // 136
	0x73, 0x4b, 0x4b, 0x00, // 137
	0x67, 0x3b, 0x3b, 0x00, // 138
	0x57, 0x2f, 0x2f, 0x00, // 139
	0x47, 0x27, 0x27, 0x00, // 140
	0x37, 0x1b, 0x1b, 0x00, // 141
	0x27, 0x13, 0x13, 0x00, // 142
	0x1b, 0x0b, 0x0b, 0x00, // 143
	0xf7, 0xb3, 0x37, 0x00, // 144
	0xe7, 0x93, 0x07, 0x00, // 145
	0xfb, 0x53, 0x0b, 0x00, // 146
	0xfb, 0x00, 0x00, 0x00, // 147
	0xcb, 0x00, 0x00, 0x00, // 148
	0x9f, 0x00, 0x00, 0x00, // 149
	0x6f, 0x00, 0x00, 0x00, // 150
	0x43, 0x00, 0x00, 0x00, // 151
	0xbf, 0xbb, 0xfb, 0x00, // 152
	0x8f, 0x8b, 0xfb, 0x00, // 153
	0x5f, 0x5b, 0xfb, 0x00, // 154
	0x93, 0xbb, 0xff, 0x00, // 155
	0x5f, 0x97, 0xf7, 0x00, // 156
	0x3b, 0x7b, 0xef, 0x00, // 157
	0x23, 0x63, 0xc3, 0x00, // 158
	0x13, 0x53, 0xb3, 0x00, // 159
	0x00, 0x00, 0xff, 0x00, // 160
	0x00, 0x00, 0xef, 0x00, // 161
	0x00, 0x00, 0xe3, 0x00, // 162
	0x00, 0x00, 0xd3, 0x00, // 163
	0x00, 0x00, 0xc3, 0x00, // 164
	0x00, 0x00, 0xb7, 0x00, // 165
	0x00, 0x00, 0xa7, 0x00, // 166
	0x00, 0x00, 0x9b, 0x00, // 167
	0x00, 0x00, 0x8b, 0x00, // 168
	0x00, 0x00, 0x7f, 0x00, // 169
	0x00, 0x00, 0x6f, 0x00, // 170
	0x00, 0x00, 0x63, 0x00, // 171
	0x00, 0x00, 0x53, 0x00, // 172
	0x00, 0x00, 0x47, 0x00, // 173
	0x00, 0x00, 0x37, 0x00, // 174
	0x00, 0x00, 0x2b, 0x00, // 175
	0x00, 0xff, 0xff, 0x00, // 176
	0x00, 0xe3, 0xf7, 0x00, // 177
	0x00, 0xcf, 0xf3, 0x00, // 178
	0x00, 0xb7, 0xef, 0x00, // 179
	0x00, 0xa3, 0xeb, 0x00, // 180
	0x00, 0x8b, 0xe7, 0x00, // 181
	0x00, 0x77, 0xdf, 0x00, // 182
	0x00, 0x63, 0xdb, 0x00, // 183
	0x00, 0x4f, 0xd7, 0x00, // 184
	0x00, 0x3f, 0xd3, 0x00, // 185
	0x00, 0x2f, 0xcf, 0x00, // 186
	0x97, 0xff, 0xff, 0x00, // 187
	0x83, 0xdf, 0xef, 0x00, // 188
	0x73, 0xc3, 0xdf, 0x00, // 189
	0x5f, 0xa7, 0xcf, 0x00, // 190
	0x53, 0x8b, 0xc3, 0x00, // 191
	0x2b, 0x2b, 0x00, 0x00, // 192
	0x23, 0x23, 0x00, 0x00, // 193
	0x1b, 0x1b, 0x00, 0x00, // 194
	0x13, 0x13, 0x00, 0x00, // 195
	0xff, 0x0b, 0x00, 0x00, // 196
	0xff, 0x00, 0x4b, 0x00, // 197
	0xff, 0x00, 0xa3, 0x00, // 198
	0xff, 0x00, 0xff, 0x00, // 199
	0x00, 0xff, 0x00, 0x00, // 200
	0x00, 0x4b, 0x00, 0x00, // 201
	0xff, 0xff, 0x00, 0x00, // 202
	0xff, 0x33, 0x2f, 0x00, // 203
	0x00, 0x00, 0xff, 0x00, // 204
	0x00, 0x1f, 0x97, 0x00, // 205
	0xdf, 0x00, 0xff, 0x00, // 206
	0x73, 0x00, 0x77, 0x00, // 207
	0x6b, 0x7b, 0xc3, 0x00, // 208
	0x57, 0x57, 0xab, 0x00, // 209
	0x57, 0x47, 0x93, 0x00, // 210
	0x53, 0x37, 0x7f, 0x00, // 211
	0x4f, 0x27, 0x67, 0x00, // 212
	0x47, 0x1b, 0x4f, 0x00, // 213
	0x3b, 0x13, 0x3b, 0x00, // 214
	0x27, 0x77, 0x77, 0x00, // 215
	0x23, 0x73, 0x73, 0x00, // 216
	0x1f, 0x6f, 0x6f, 0x00, // 217
	0x1b, 0x6b, 0x6b, 0x00, // 218
	0x1b, 0x67, 0x67, 0x00, // 219
	0x1b, 0x6b, 0x6b, 0x00, // 220
	0x1f, 0x6f, 0x6f, 0x00, // 221
	0x23, 0x73, 0x73, 0x00, // 222
	0x27, 0x77, 0x77, 0x00, // 223
	0xff, 0xff, 0xef, 0x00, // 224
	0xf7, 0xf7, 0xdb, 0x00, // 225
	0xf3, 0xef, 0xcb, 0x00, // 226
	0xef, 0xeb, 0xbb, 0x00, // 227
	0xf3, 0xef, 0xcb, 0x00, // 228
	0xe7, 0x93, 0x07, 0x00, // 229
	0xe7, 0x97, 0x0f, 0x00, // 230
	0xeb, 0x9f, 0x17, 0x00, // 231
	0xef, 0xa3, 0x23, 0x00, // 232
	0xf3, 0xab, 0x2b, 0x00, // 233
	0xf7, 0xb3, 0x37, 0x00, // 234
	0xef, 0xa7, 0x27, 0x00, // 235
	0xeb, 0x9f, 0x1b, 0x00, // 236
	0xe7, 0x97, 0x0f, 0x00, // 237
	0x0b, 0xcb, 0xfb, 0x00, // 238
	0x0b, 0xa3, 0xfb, 0x00, // 239
	0x0b, 0x73, 0xfb, 0x00, // 240
	0x0b, 0x4b, 0xfb, 0x00, // 241
	0x0b, 0x23, 0xfb, 0x00, // 242
	0x0b, 0x73, 0xfb, 0x00, // 243
	0x00, 0x13, 0x93, 0x00, // 244
	0x00, 0x0b, 0xd3, 0x00, // 245
	0x00, 0x00, 0x00, 0x00, // 246
	0x00, 0x00, 0x00, 0x00, // 247
	0x00, 0x00, 0x00, 0x00, // 248
	0x00, 0x00, 0x00, 0x00, // 249
	0x00, 0x00, 0x00, 0x00, // 250
	0x00, 0x00, 0x00, 0x00, // 251
	0x00, 0x00, 0x00, 0x00, // 252
	0x00, 0x00, 0x00, 0x00, // 253
	0x00, 0x00, 0x00, 0x00, // 254
	0xff, 0xff, 0xff, 0x00, // 255
	};

} // End of namespace Deskadv

#endif

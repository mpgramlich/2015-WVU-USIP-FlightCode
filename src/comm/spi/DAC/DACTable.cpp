/*
 * DACTable.cpp
 *
 *  Created on: Jul 31, 2015
 *      Author: Matt Gramlich
 */

#include "DACTable.h"

int DACTable::currentPlace = 0;

BYTE DACTable::zeroVoltage[3] = { 0, 0x80, 0x00};

BYTE DACTable::table[DACTable::size] __attribute__ ((aligned(2))) = {
		0, 0x66, 0x66,
		0, 0x67, 0x0A,
		0, 0x67, 0xAE,
		0, 0x68, 0x52,
		0, 0x68, 0xF6,
		0, 0x69, 0x9A,
		0, 0x6A, 0x3E,
		0, 0x6A, 0xE2,
		0, 0x6B, 0x86,
		0, 0x6C, 0x2A,
		0, 0x6C, 0xCE,
		0, 0x6D, 0x72,
		0, 0x6E, 0x16,
		0, 0x6E, 0xBA,
		0, 0x6F, 0x5E,
		0, 0x70, 0x02,
		0, 0x70, 0xA6,
		0, 0x71, 0x4A,
		0, 0x71, 0xEE,
		0, 0x72, 0x92,
		0, 0x73, 0x36,
		0, 0x73, 0xDA,
		0, 0x74, 0x7E,
		0, 0x75, 0x22,
		0, 0x75, 0xC6,
		0, 0x76, 0x6A,
		0, 0x77, 0x0E,
		0, 0x77, 0xB2,
		0, 0x78, 0x56,
		0, 0x78, 0xFA,
		0, 0x79, 0x9E,
		0, 0x7A, 0x42,
		0, 0x7A, 0xE6,
		0, 0x7B, 0x8A,
		0, 0x7C, 0x2E,
		0, 0x7C, 0xD2,
		0, 0x7D, 0x76,
		0, 0x7E, 0x1A,
		0, 0x7E, 0xBE,
		0, 0x7F, 0x62,
		0, 0x80, 0x06,
		0, 0x80, 0xAA,
		0, 0x81, 0x4E,
		0, 0x81, 0xF2,
		0, 0x82, 0x96,
		0, 0x83, 0x3A,
		0, 0x83, 0xDE,
		0, 0x84, 0x82,
		0, 0x85, 0x26,
		0, 0x85, 0xCA,
		0, 0x86, 0x6E,
		0, 0x87, 0x12,
		0, 0x87, 0xB6,
		0, 0x88, 0x5A,
		0, 0x88, 0xFE,
		0, 0x89, 0xA2,
		0, 0x8A, 0x46,
		0, 0x8A, 0xEA,
		0, 0x8B, 0x8E,
		0, 0x8C, 0x32,
		0, 0x8C, 0xD6,
		0, 0x8D, 0x7A,
		0, 0x8E, 0x1E,
		0, 0x8E, 0xC2,
		0, 0x8F, 0x66,
		0, 0x90, 0x0A,
		0, 0x90, 0xAE,
		0, 0x91, 0x52,
		0, 0x91, 0xF6,
		0, 0x92, 0x9A,
		0, 0x93, 0x3E,
		0, 0x93, 0xE2,
		0, 0x94, 0x86,
		0, 0x95, 0x2A,
		0, 0x95, 0xCE,
		0, 0x96, 0x72,
		0, 0x97, 0x16,
		0, 0x97, 0xBA,
		0, 0x98, 0x5E,
		0, 0x99, 0x02,
		0, 0x99, 0xA6,
		0, 0x9A, 0xE2,
		0, 0x9C, 0x29,
		0, 0x9D, 0x70,
		0, 0x9E, 0xB7,
		0, 0x9F, 0xFE,
		0, 0xA1, 0x45,
		0, 0xA2, 0x8C,
		0, 0xA3, 0xD3,
		0, 0xA5, 0x1A,
		0, 0xA6, 0x61,
		0, 0xA7, 0xA8,
		0, 0xA8, 0xEF,
		0, 0xAA, 0x36,
		0, 0xAB, 0x7D,
		0, 0xAC, 0xC4,
		0, 0xAE, 0x0B,
		0, 0xAF, 0x52,
		0, 0xB0, 0x99,
		0, 0xB1, 0xE0,
		0, 0xB3, 0x27,
		0, 0xB4, 0x6E,
		0, 0xB5, 0xB5,
		0, 0xB6, 0xFC,
		0, 0xB8, 0x43,
		0, 0xB9, 0x8A,
		0, 0xBA, 0xD1,
		0, 0xBC, 0x18,
		0, 0xBD, 0x5F,
		0, 0xBE, 0xA6,
		0, 0xBF, 0xED,
		0, 0xC1, 0x34,
		0, 0xC2, 0x7B,
		0, 0xC3, 0xC2,
		0, 0xC5, 0x09,
		0, 0xC6, 0x50,
		0, 0xC7, 0x97,
		0, 0xC8, 0xDE,
		0, 0xCA, 0x25,
		0, 0xCB, 0x6C,
		0, 0xCC, 0xB3,
		0, 0xCB, 0x6C,
		0, 0xCA, 0x25,
		0, 0xC8, 0xDE,
		0, 0xC7, 0x97,
		0, 0xC6, 0x50,
		0, 0xC5, 0x09,
		0, 0xC3, 0xC2,
		0, 0xC2, 0x7B,
		0, 0xC1, 0x34,
		0, 0xBF, 0xED,
		0, 0xBE, 0xA6,
		0, 0xBD, 0x5F,
		0, 0xBC, 0x18,
		0, 0xBA, 0xD1,
		0, 0xB9, 0x8A,
		0, 0xB8, 0x43,
		0, 0xB6, 0xFC,
		0, 0xB5, 0xB5,
		0, 0xB4, 0x6E,
		0, 0xB3, 0x27,
		0, 0xB1, 0xE0,
		0, 0xB0, 0x99,
		0, 0xAF, 0x52,
		0, 0xAE, 0x0B,
		0, 0xAC, 0xC4,
		0, 0xAB, 0x7D,
		0, 0xAA, 0x36,
		0, 0xA8, 0xEF,
		0, 0xA7, 0xA8,
		0, 0xA6, 0x61,
		0, 0xA5, 0x1A,
		0, 0xA3, 0xD3,
		0, 0xA2, 0x8C,
		0, 0xA1, 0x45,
		0, 0x9F, 0xFE,
		0, 0x9E, 0xB7,
		0, 0x9D, 0x70,
		0, 0x9C, 0x29,
		0, 0x9A, 0xE2,
		0, 0x99, 0xA6,
		0, 0x99, 0x02,
		0, 0x98, 0x5E,
		0, 0x97, 0xBA,
		0, 0x97, 0x16,
		0, 0x96, 0x72,
		0, 0x95, 0xCE,
		0, 0x95, 0x2A,
		0, 0x94, 0x86,
		0, 0x93, 0xE2,
		0, 0x93, 0x3E,
		0, 0x92, 0x9A,
		0, 0x91, 0xF6,
		0, 0x91, 0x52,
		0, 0x90, 0xAE,
		0, 0x90, 0x0A,
		0, 0x8F, 0x66,
		0, 0x8E, 0xC2,
		0, 0x8E, 0x1E,
		0, 0x8D, 0x7A,
		0, 0x8C, 0xD6,
		0, 0x8C, 0x32,
		0, 0x8B, 0x8E,
		0, 0x8A, 0xEA,
		0, 0x8A, 0x46,
		0, 0x89, 0xA2,
		0, 0x88, 0xFE,
		0, 0x88, 0x5A,
		0, 0x87, 0xB6,
		0, 0x87, 0x12,
		0, 0x86, 0x6E,
		0, 0x85, 0xCA,
		0, 0x85, 0x26,
		0, 0x84, 0x82,
		0, 0x83, 0xDE,
		0, 0x83, 0x3A,
		0, 0x82, 0x96,
		0, 0x81, 0xF2,
		0, 0x81, 0x4E,
		0, 0x80, 0xAA,
		0, 0x80, 0x06,
		0, 0x7F, 0x62,
		0, 0x7E, 0xBE,
		0, 0x7E, 0x1A,
		0, 0x7D, 0x76,
		0, 0x7C, 0xD2,
		0, 0x7C, 0x2E,
		0, 0x7B, 0x8A,
		0, 0x7A, 0xE6,
		0, 0x7A, 0x42,
		0, 0x79, 0x9E,
		0, 0x78, 0xFA,
		0, 0x78, 0x56,
		0, 0x77, 0xB2,
		0, 0x77, 0x0E,
		0, 0x76, 0x6A,
		0, 0x75, 0xC6,
		0, 0x75, 0x22,
		0, 0x74, 0x7E,
		0, 0x73, 0xDA,
		0, 0x73, 0x36,
		0, 0x72, 0x92,
		0, 0x71, 0xEE,
		0, 0x71, 0x4A,
		0, 0x70, 0xA6,
		0, 0x70, 0x02,
		0, 0x6F, 0x5E,
		0, 0x6E, 0xBA,
		0, 0x6E, 0x16,
		0, 0x6D, 0x72,
		0, 0x6C, 0xCE,
		0, 0x6C, 0x2A,
		0, 0x6B, 0x86,
		0, 0x6A, 0xE2,
		0, 0x6A, 0x3E,
		0, 0x69, 0x9A,
		0, 0x68, 0xF6,
		0, 0x68, 0x52,
		0, 0x67, 0xAE,
		0, 0x67, 0x0A
						};

//old table
/*
		0,0x0,0x1E,
		0,0x0,0xC3,
		0,0x1,0x68,
		0,0x2,0xD,
		0,0x2,0xB2,
		0,0x3,0x57,
		0,0x3,0xFC,
		0,0x4,0xA1,
		0,0x5,0x46,
		0,0x5,0xEB,
		0,0x6,0x90,
		0,0x7,0x35,
		0,0x7,0xDA,
		0,0x8,0x7F,
		0,0x9,0x24,
		0,0x9,0xC9,
		0,0xA,0x6E,
		0,0xB,0x13,
		0,0xB,0xB8,
		0,0xC,0x5D,
		0,0xD,0x2,
		0,0xD,0xA7,
		0,0xE,0x4C,
		0,0xE,0xF1,
		0,0xF,0x96,
		0,0x10,0x3B,
		0,0x10,0xE0,
		0,0x11,0x85,
		0,0x12,0x2A,
		0,0x12,0xCF,
		0,0x13,0x74,
		0,0x14,0x19,
		0,0x14,0xBE,
		0,0x15,0x63,
		0,0x16,0x8,
		0,0x16,0xAD,
		0,0x17,0x52,
		0,0x17,0xF7,
		0,0x18,0x9C,
		0,0x19,0x41,
		0,0x19,0xE6,
		0,0x1A,0x8B,
		0,0x1B,0x30,
		0,0x1B,0xD5,
		0,0x1C,0x7A,
		0,0x1D,0x1F,
		0,0x1D,0xC4,
		0,0x1E,0x69,
		0,0x1F,0x0E,
		0,0x1F,0xB3,
		0,0x20,0x58,
		0,0x20,0xFD,
		0,0x21,0xA2,
		0,0x22,0x47,
		0,0x22,0xEC,
		0,0x23,0x91,
		0,0x24,0x36,
		0,0x24,0xDB,
		0,0x25,0x80,
		0,0x26,0x25,
		0,0x26,0xCA,
		0,0x27,0x6F,
		0,0x28,0x14,
		0,0x28,0xB9,
		0,0x29,0x5E,
		0,0x2A,0x3,
		0,0x2A,0xA8,
		0,0x2B,0x4D,
		0,0x2B,0xF2,
		0,0x2C,0x97,
		0,0x2D,0x3C,
		0,0x2D,0xE1,
		0,0x2E,0x86,
		0,0x2F,0x2B,
		0,0x2F,0xD0,
		0,0x30,0x75,
		0,0x31,0x1A,
		0,0x31,0xBF,
		0,0x32,0x64,
		0,0x33,0x9,
		0,0x33,0xAE,
		0,0x34,0x53,
		0,0x34,0xF8,
		0,0x35,0x9D,
		0,0x36,0x42,
		0,0x36,0xE7,
		0,0x37,0x8C,
		0,0x38,0x31,
		0,0x38,0xD6,
		0,0x39,0x7B,
		0,0x3A,0x20,
		0,0x3A,0xC5,
		0,0x3B,0x6A,
		0,0x3C,0x0F,
		0,0x3C,0xB4,
		0,0x3D,0x59,
		0,0x3D,0xFE,
		0,0x3E,0xA3,
		0,0x3F,0x48,
		0,0x3F,0xED,
		0,0x40,0x92,
		0,0x41,0x37,
		0,0x41,0xDC,
		0,0x42,0x81,
		0,0x43,0x26,
		0,0x43,0xCB,
		0,0x44,0x70,
		0,0x45,0x15,
		0,0x45,0xBA,
		0,0x46,0x5F,
		0,0x47,0x4,
		0,0x47,0xA9,
		0,0x48,0x4E,
		0,0x48,0xF3,
		0,0x49,0x98,
		0,0x4A,0x3D,
		0,0x4A,0xE2,
		0,0x4B,0x87,
		0,0x4C,0x2C,
		0,0x4C,0xD1,
		0,0x4D,0x76,
		0,0x4E,0x1B,
		0,0x4E,0xC0,
		0,0x4F,0x65,
		0,0x50,0x0A,
		0,0x50,0xAF,
		0,0x51,0x54,
		0,0x51,0xF9,
		0,0x52,0x9E,
		0,0x53,0x43,
		0,0x53,0xE8,
		0,0x54,0x8D,
		0,0x55,0x32,
		0,0x55,0xD7,
		0,0x56,0x7C,
		0,0x57,0x21,
		0,0x57,0xC6,
		0,0x58,0x6B,
		0,0x59,0x10,
		0,0x59,0xB5,
		0,0x5A,0x5A,
		0,0x5A,0xFF,
		0,0x5B,0xA4,
		0,0x5C,0x49,
		0,0x5C,0xEE,
		0,0x5D,0x93,
		0,0x5E,0x38,
		0,0x5E,0xDD,
		0,0x5F,0x82,
		0,0x60,0x27,
		0,0x60,0xCC,
		0,0x61,0x71,
		0,0x62,0x16,
		0,0x62,0xBB,
		0,0x63,0x60,
		0,0x64,0x5,
		0,0x64,0xAA,
		0,0x65,0x4F,
		0,0x65,0xF4,
		0,0x66,0x99,
		0,0x67,0x3E,
		0,0x67,0xE3,
		0,0x68,0x88,
		0,0x69,0x2D,
		0,0x69,0xD2,
		0,0x6A,0x77,
		0,0x6B,0x1C,
		0,0x6B,0xC1,
		0,0x6C,0x66,
		0,0x6D,0x0B,
		0,0x6D,0xB0,
		0,0x6E,0x55,
		0,0x6E,0xFA,
		0,0x6F,0x9F,
		0,0x70,0x44,
		0,0x70,0xE9,
		0,0x71,0x8E,
		0,0x72,0x33,
		0,0x72,0xD8,
		0,0x73,0x7D,
		0,0x74,0x22,
		0,0x74,0xC7,
		0,0x75,0x6C,
		0,0x76,0x11,
		0,0x76,0xB6,
		0,0x77,0x5B,
		0,0x78,0x0,
		0,0x78,0xA5,
		0,0x79,0x4A,
		0,0x79,0xEF,
		0,0x7A,0x94,
		0,0x7B,0x39,
		0,0x7B,0xDE,
		0,0x7C,0x83,
		0,0x7D,0x28,
		0,0x7D,0xCD,
		0,0x7E,0x72,
		0,0x7F,0x17,
		0,0x7F,0xBC,
		0,0x80,0x61,
		0,0x81,0x6,
		0,0x81,0xAB,
		0,0x82,0x50,
		0,0x82,0xF5,
		0,0x83,0x9A,
		0,0x84,0x3F,
		0,0x84,0xE4,
		0,0x85,0x89,
		0,0x86,0x2E,
		0,0x86,0xD3,
		0,0x87,0x78,
		0,0x88,0x1D,
		0,0x88,0xC2,
		0,0x89,0x67,
		0,0x8A,0x0C,
		0,0x8A,0xB1,
		0,0x8B,0x56,
		0,0x8B,0xFB,
		0,0x8C,0xA0,
		0,0x8D,0x45,
		0,0x8D,0xEA,
		0,0x8E,0x8F,
		0,0x8F,0x34,
		0,0x8F,0xD9,
		0,0x90,0x7E,
		0,0x91,0x23,
		0,0x91,0xC8,
		0,0x92,0x6D,
		0,0x93,0x12,
		0,0x93,0xB7,
		0,0x94,0x5C,
		0,0x95,0x1,
		0,0x95,0xA6,
		0,0x96,0x4B,
		0,0x96,0xF0,
		0,0x97,0x95,
		0,0x98,0x3A,
		0,0x98,0xDF,
		0,0x99,0x84,
		0,0x9A,0x29,
		0,0x9A,0xCE,
		0,0x9B,0x73,
		0,0x9C,0x18,
		0,0x9C,0xBD,
		0,0x9D,0x62,
		0,0x9E,0x7,
		0,0x9E,0xAC,
		0,0x9F,0x51,
		0,0x9F,0xF6,
		0,0xA0,0x9B,
		0,0xA1,0x40,
		0,0xA1,0xE5,
		0,0xA2,0x8A,
		0,0xA3,0x2F,
		0,0xA3,0xD4,
		0,0xA4,0x79,
		0,0xA5,0x1E,
		0,0xA5,0xC3,
		0,0xA6,0x68,
		0,0xA7,0x0D,
		0,0xA7,0xB2,
		0,0xA8,0x57,
		0,0xA8,0xFC,
		0,0xA9,0xA1,
		0,0xAA,0x46,
		0,0xAA,0xEB,
		0,0xAB,0x90,
		0,0xAC,0x35,
		0,0xAC,0xDA,
		0,0xAD,0x7F,
		0,0xAE,0x24,
		0,0xAE,0xC9,
		0,0xAF,0x6E,
		0,0xB0,0x13,
		0,0xB0,0xB8,
		0,0xB1,0x5D,
		0,0xB2,0x2,
		0,0xB2,0xA7,
		0,0xB3,0x4C,
		0,0xB3,0xF1,
		0,0xB4,0x96,
		0,0xB5,0x3B,
		0,0xB5,0xE0,
		0,0xB6,0x85,
		0,0xB7,0x2A,
		0,0xB7,0xCF,
		0,0xB8,0x74,
		0,0xB9,0x19,
		0,0xB9,0xBE,
		0,0xBA,0x63,
		0,0xBB,0x8,
		0,0xBB,0xAD,
		0,0xBC,0x52,
		0,0xBC,0xF7,
		0,0xBD,0x9C,
		0,0xBE,0x41,
		0,0xBE,0xE6,
		0,0xBF,0x8B,
		0,0xC0,0x30,
		0,0xC0,0xD5,
		0,0xC1,0x7A,
		0,0xC2,0x1F,
		0,0xC2,0xC4,
		0,0xC3,0x69,
		0,0xC4,0x0E,
		0,0xC4,0xB3,
		0,0xC5,0x58,
		0,0xC5,0xFD,
		0,0xC6,0xA2,
		0,0xC7,0x47,
		0,0xC7,0xEC,
		0,0xC8,0x91,
		0,0xC9,0x36,
		0,0xC9,0xDB,
		0,0xCA,0x80,
		0,0xCB,0x25,
		0,0xCB,0xCA,
		0,0xCC,0x6F,
		0,0xCD,0x14,
		0,0xCD,0xB9,
		0,0xCE,0x5E,
		0,0xCF,0x3,
		0,0xCF,0xA8,
		0,0xD0,0x4D,
		0,0xD0,0xF2,
		0,0xD1,0x97,
		0,0xD2,0x3C,
		0,0xD2,0xE1,
		0,0xD3,0x86,
		0,0xD4,0x2B,
		0,0xD4,0xD0,
		0,0xD5,0x75,
		0,0xD6,0x1A,
		0,0xD6,0xBF,
		0,0xD7,0x64,
		0,0xD8,0x9,
		0,0xD8,0xAE,
		0,0xD9,0x53,
		0,0xD9,0xF8,
		0,0xDA,0x9D,
		0,0xDB,0x42,
		0,0xDB,0xE7,
		0,0xDC,0x8C,
		0,0xDD,0x31,
		0,0xDD,0xD6,
		0,0xDE,0x7B,
		0,0xDF,0x20,
		0,0xDF,0xC5,
		0,0xE0,0x6A,
		0,0xE1,0x0F,
		0,0xE1,0xB4,
		0,0xE2,0x59,
		0,0xE2,0xFE,
		0,0xE3,0xA3,
		0,0xE4,0x48,
		0,0xE4,0xED,
		0,0xE5,0x92,
		0,0xE6,0x37,
		0,0xE6,0xDC,
		0,0xE7,0x81,
		0,0xE8,0x26,
		0,0xE8,0xCB,
		0,0xE9,0x70,
		0,0xEA,0x15,
		0,0xEA,0xBA,
		0,0xEB,0x5F,
		0,0xEC,0x4,
		0,0xEC,0xA9,
		0,0xED,0x4E,
		0,0xED,0xF3,
		0,0xEE,0x98,
		0,0xEF,0x3D,
		0,0xEF,0xE2,
		0,0xF0,0x87,
		0,0xF1,0x2C,
		0,0xF1,0xD1,
		0,0xF2,0x76,
		0,0xF3,0x1B,
		0,0xF3,0xC0,
		0,0xF4,0x65,
		0,0xF5,0x0A,
		0,0xF5,0xAF,
		0,0xF6,0x54,
		0,0xF6,0xF9,
		0,0xF7,0x9E,
		0,0xF8,0x43,
		0,0xF8,0xE8,
		0,0xF9,0x8D,
		0,0xFA,0x32,
		0,0xFA,0xD7,
		0,0xFB,0x7C,
		0,0xFC,0x21,
		0,0xFC,0xC6,
		0,0xFD,0x6B,
		0,0xFE,0x10,
		0,0xFE,0xB5,
		0,0xFF,0x5A,
		0,0xFF,0xFF,
		0,0xFF,0xFF,
		0,0xFF,0x5A,
		0,0xFE,0xB5,
		0,0xFE,0x10,
		0,0xFD,0x6B,
		0,0xFC,0xC6,
		0,0xFC,0x21,
		0,0xFB,0x7C,
		0,0xFA,0xD7,
		0,0xFA,0x32,
		0,0xF9,0x8D,
		0,0xF8,0xE8,
		0,0xF8,0x43,
		0,0xF7,0x9E,
		0,0xF6,0xF9,
		0,0xF6,0x54,
		0,0xF5,0xAF,
		0,0xF5,0x0A,
		0,0xF4,0x65,
		0,0xF3,0xC0,
		0,0xF3,0x1B,
		0,0xF2,0x76,
		0,0xF1,0xD1,
		0,0xF1,0x2C,
		0,0xF0,0x87,
		0,0xEF,0xE2,
		0,0xEF,0x3D,
		0,0xEE,0x98,
		0,0xED,0xF3,
		0,0xED,0x4E,
		0,0xEC,0xA9,
		0,0xEC,0x4,
		0,0xEB,0x5F,
		0,0xEA,0xBA,
		0,0xEA,0x15,
		0,0xE9,0x70,
		0,0xE8,0xCB,
		0,0xE8,0x26,
		0,0xE7,0x81,
		0,0xE6,0xDC,
		0,0xE6,0x37,
		0,0xE5,0x92,
		0,0xE4,0xED,
		0,0xE4,0x48,
		0,0xE3,0xA3,
		0,0xE2,0xFE,
		0,0xE2,0x59,
		0,0xE1,0xB4,
		0,0xE1,0x0F,
		0,0xE0,0x6A,
		0,0xDF,0xC5,
		0,0xDF,0x20,
		0,0xDE,0x7B,
		0,0xDD,0xD6,
		0,0xDD,0x31,
		0,0xDC,0x8C,
		0,0xDB,0xE7,
		0,0xDB,0x42,
		0,0xDA,0x9D,
		0,0xD9,0xF8,
		0,0xD9,0x53,
		0,0xD8,0xAE,
		0,0xD8,0x9,
		0,0xD7,0x64,
		0,0xD6,0xBF,
		0,0xD6,0x1A,
		0,0xD5,0x75,
		0,0xD4,0xD0,
		0,0xD4,0x2B,
		0,0xD3,0x86,
		0,0xD2,0xE1,
		0,0xD2,0x3C,
		0,0xD1,0x97,
		0,0xD0,0xF2,
		0,0xD0,0x4D,
		0,0xCF,0xA8,
		0,0xCF,0x3,
		0,0xCE,0x5E,
		0,0xCD,0xB9,
		0,0xCD,0x14,
		0,0xCC,0x6F,
		0,0xCB,0xCA,
		0,0xCB,0x25,
		0,0xCA,0x80,
		0,0xC9,0xDB,
		0,0xC9,0x36,
		0,0xC8,0x91,
		0,0xC7,0xEC,
		0,0xC7,0x47,
		0,0xC6,0xA2,
		0,0xC5,0xFD,
		0,0xC5,0x58,
		0,0xC4,0xB3,
		0,0xC4,0x0E,
		0,0xC3,0x69,
		0,0xC2,0xC4,
		0,0xC2,0x1F,
		0,0xC1,0x7A,
		0,0xC0,0xD5,
		0,0xC0,0x30,
		0,0xBF,0x8B,
		0,0xBE,0xE6,
		0,0xBE,0x41,
		0,0xBD,0x9C,
		0,0xBC,0xF7,
		0,0xBC,0x52,
		0,0xBB,0xAD,
		0,0xBB,0x8,
		0,0xBA,0x63,
		0,0xB9,0xBE,
		0,0xB9,0x19,
		0,0xB8,0x74,
		0,0xB7,0xCF,
		0,0xB7,0x2A,
		0,0xB6,0x85,
		0,0xB5,0xE0,
		0,0xB5,0x3B,
		0,0xB4,0x96,
		0,0xB3,0xF1,
		0,0xB3,0x4C,
		0,0xB2,0xA7,
		0,0xB2,0x2,
		0,0xB1,0x5D,
		0,0xB0,0xB8,
		0,0xB0,0x13,
		0,0xAF,0x6E,
		0,0xAE,0xC9,
		0,0xAE,0x24,
		0,0xAD,0x7F,
		0,0xAC,0xDA,
		0,0xAC,0x35,
		0,0xAB,0x90,
		0,0xAA,0xEB,
		0,0xAA,0x46,
		0,0xA9,0xA1,
		0,0xA8,0xFC,
		0,0xA8,0x57,
		0,0xA7,0xB2,
		0,0xA7,0x0D,
		0,0xA6,0x68,
		0,0xA5,0xC3,
		0,0xA5,0x1E,
		0,0xA4,0x79,
		0,0xA3,0xD4,
		0,0xA3,0x2F,
		0,0xA2,0x8A,
		0,0xA1,0xE5,
		0,0xA1,0x40,
		0,0xA0,0x9B,
		0,0x9F,0xF6,
		0,0x9F,0x51,
		0,0x9E,0xAC,
		0,0x9E,0x7,
		0,0x9D,0x62,
		0,0x9C,0xBD,
		0,0x9C,0x18,
		0,0x9B,0x73,
		0,0x9A,0xCE,
		0,0x9A,0x29,
		0,0x99,0x84,
		0,0x98,0xDF,
		0,0x98,0x3A,
		0,0x97,0x95,
		0,0x96,0xF0,
		0,0x96,0x4B,
		0,0x95,0xA6,
		0,0x95,0x1,
		0,0x94,0x5C,
		0,0x93,0xB7,
		0,0x93,0x12,
		0,0x92,0x6D,
		0,0x91,0xC8,
		0,0x91,0x23,
		0,0x90,0x7E,
		0,0x8F,0xD9,
		0,0x8F,0x34,
		0,0x8E,0x8F,
		0,0x8D,0xEA,
		0,0x8D,0x45,
		0,0x8C,0xA0,
		0,0x8B,0xFB,
		0,0x8B,0x56,
		0,0x8A,0xB1,
		0,0x8A,0x0C,
		0,0x89,0x67,
		0,0x88,0xC2,
		0,0x88,0x1D,
		0,0x87,0x78,
		0,0x86,0xD3,
		0,0x86,0x2E,
		0,0x85,0x89,
		0,0x84,0xE4,
		0,0x84,0x3F,
		0,0x83,0x9A,
		0,0x82,0xF5,
		0,0x82,0x50,
		0,0x81,0xAB,
		0,0x81,0x6,
		0,0x80,0x61,
		0,0x7F,0xBC,
		0,0x7F,0x17,
		0,0x7E,0x72,
		0,0x7D,0xCD,
		0,0x7D,0x28,
		0,0x7C,0x83,
		0,0x7B,0xDE,
		0,0x7B,0x39,
		0,0x7A,0x94,
		0,0x79,0xEF,
		0,0x79,0x4A,
		0,0x78,0xA5,
		0,0x78,0x0,
		0,0x77,0x5B,
		0,0x76,0xB6,
		0,0x76,0x11,
		0,0x75,0x6C,
		0,0x74,0xC7,
		0,0x74,0x22,
		0,0x73,0x7D,
		0,0x72,0xD8,
		0,0x72,0x33,
		0,0x71,0x8E,
		0,0x70,0xE9,
		0,0x70,0x44,
		0,0x6F,0x9F,
		0,0x6E,0xFA,
		0,0x6E,0x55,
		0,0x6D,0xB0,
		0,0x6D,0x0B,
		0,0x6C,0x66,
		0,0x6B,0xC1,
		0,0x6B,0x1C,
		0,0x6A,0x77,
		0,0x69,0xD2,
		0,0x69,0x2D,
		0,0x68,0x88,
		0,0x67,0xE3,
		0,0x67,0x3E,
		0,0x66,0x99,
		0,0x65,0xF4,
		0,0x65,0x4F,
		0,0x64,0xAA,
		0,0x64,0x5,
		0,0x63,0x60,
		0,0x62,0xBB,
		0,0x62,0x16,
		0,0x61,0x71,
		0,0x60,0xCC,
		0,0x60,0x27,
		0,0x5F,0x82,
		0,0x5E,0xDD,
		0,0x5E,0x38,
		0,0x5D,0x93,
		0,0x5C,0xEE,
		0,0x5C,0x49,
		0,0x5B,0xA4,
		0,0x5A,0xFF,
		0,0x5A,0x5A,
		0,0x59,0xB5,
		0,0x59,0x10,
		0,0x58,0x6B,
		0,0x57,0xC6,
		0,0x57,0x21,
		0,0x56,0x7C,
		0,0x55,0xD7,
		0,0x55,0x32,
		0,0x54,0x8D,
		0,0x53,0xE8,
		0,0x53,0x43,
		0,0x52,0x9E,
		0,0x51,0xF9,
		0,0x51,0x54,
		0,0x50,0xAF,
		0,0x50,0x0A,
		0,0x4F,0x65,
		0,0x4E,0xC0,
		0,0x4E,0x1B,
		0,0x4D,0x76,
		0,0x4C,0xD1,
		0,0x4C,0x2C,
		0,0x4B,0x87,
		0,0x4A,0xE2,
		0,0x4A,0x3D,
		0,0x49,0x98,
		0,0x48,0xF3,
		0,0x48,0x4E,
		0,0x47,0xA9,
		0,0x47,0x4,
		0,0x46,0x5F,
		0,0x45,0xBA,
		0,0x45,0x15,
		0,0x44,0x70,
		0,0x43,0xCB,
		0,0x43,0x26,
		0,0x42,0x81,
		0,0x41,0xDC,
		0,0x41,0x37,
		0,0x40,0x92,
		0,0x3F,0xED,
		0,0x3F,0x48,
		0,0x3E,0xA3,
		0,0x3D,0xFE,
		0,0x3D,0x59,
		0,0x3C,0xB4,
		0,0x3C,0x0F,
		0,0x3B,0x6A,
		0,0x3A,0xC5,
		0,0x3A,0x20,
		0,0x39,0x7B,
		0,0x38,0xD6,
		0,0x38,0x31,
		0,0x37,0x8C,
		0,0x36,0xE7,
		0,0x36,0x42,
		0,0x35,0x9D,
		0,0x34,0xF8,
		0,0x34,0x53,
		0,0x33,0xAE,
		0,0x33,0x9,
		0,0x32,0x64,
		0,0x31,0xBF,
		0,0x31,0x1A,
		0,0x30,0x75,
		0,0x2F,0xD0,
		0,0x2F,0x2B,
		0,0x2E,0x86,
		0,0x2D,0xE1,
		0,0x2D,0x3C,
		0,0x2C,0x97,
		0,0x2B,0xF2,
		0,0x2B,0x4D,
		0,0x2A,0xA8,
		0,0x2A,0x3,
		0,0x29,0x5E,
		0,0x28,0xB9,
		0,0x28,0x14,
		0,0x27,0x6F,
		0,0x26,0xCA,
		0,0x26,0x25,
		0,0x25,0x80,
		0,0x24,0xDB,
		0,0x24,0x36,
		0,0x23,0x91,
		0,0x22,0xEC,
		0,0x22,0x47,
		0,0x21,0xA2,
		0,0x20,0xFD,
		0,0x20,0x58,
		0,0x1F,0xB3,
		0,0x1F,0x0E,
		0,0x1E,0x69,
		0,0x1D,0xC4,
		0,0x1D,0x1F,
		0,0x1C,0x7A,
		0,0x1B,0xD5,
		0,0x1B,0x30,
		0,0x1A,0x8B,
		0,0x19,0xE6,
		0,0x19,0x41,
		0,0x18,0x9C,
		0,0x17,0xF7,
		0,0x17,0x52,
		0,0x16,0xAD,
		0,0x16,0x8,
		0,0x15,0x63,
		0,0x14,0xBE,
		0,0x14,0x19,
		0,0x13,0x74,
		0,0x12,0xCF,
		0,0x12,0x2A,
		0,0x11,0x85,
		0,0x10,0xE0,
		0,0x10,0x3B,
		0,0xF,0x96,
		0,0xE,0xF1,
		0,0xE,0x4C,
		0,0xD,0xA7,
		0,0xD,0x2,
		0,0xC,0x5D,
		0,0xB,0xB8,
		0,0xB,0x13,
		0,0xA,0x6E,
		0,0x9,0xC9,
		0,0x9,0x24,
		0,0x8,0x7F,
		0,0x7,0xDA,
		0,0x7,0x35,
		0,0x6,0x90,
		0,0x5,0xEB,
		0,0x5,0x46,
		0,0x4,0xA1,
		0,0x3,0xFC,
		0,0x3,0x57,
		0,0x2,0xB2,
		0,0x2,0x0d,
		0,0x1,0x68,
		0,0x0,0xC3,
		0,0x0,0x1E,
 */

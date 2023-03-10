/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may
* *    be used to endorse or promote products derived from this software
* *    without specific prior written permission.
*
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/


/*****************************************************************************
   1 ??????????
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "PppInterface.h"
#include "Taf_MmiStrParse.h"
#include "AppVcApi.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "TafStdlib.h"

#include "at_common.h"
#include "securec.h"


/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDPROC_C


/*****************************************************************************
   2 ????????????
*****************************************************************************/

/* The following tables maps the 256 characters of PBM8 to the corresponding
 * unicode characters. */
AT_PB_CONVERSION_TABLE_STRU  g_astIraToUnicode[AT_PB_IRA_MAX_NUM] =
{
    {0x00, 0, 0x0000}, /* Null */
    {0x01, 0, 0x0001}, /* Start of heading */
    {0x02, 0, 0x0002}, /* Start of text */
    {0x03, 0, 0x0003}, /* End of text */
    {0x04, 0, 0x0004}, /* End of transmission */
    {0x05, 0, 0x0005}, /* Inquiry */
    {0x06, 0, 0x0006}, /* ACK */
    {0x07, 0, 0x0007}, /* Bell */
    {0x08, 0, 0x0008}, /* Backspace */
    {0x09, 0, 0x0009}, /* Tab */
    {0x0A, 0, 0x000A}, /* Line feed */
    {0x0B, 0, 0x000B}, /* Vertical tab */
    {0x0C, 0, 0x000C}, /* Form feed */
    {0x0D, 0, 0x000D}, /* Carriage return */
    {0x0E, 0, 0x000E}, /* Shift out */
    {0x0F, 0, 0x000F}, /* Shift in */
    {0x10, 0, 0x0010}, /* Data link escape */
    {0x11, 0, 0x0011}, /* Device control one */
    {0x12, 0, 0x0012}, /* Device control two */
    {0x13, 0, 0x0013}, /* Device control three */
    {0x14, 0, 0x0014}, /* Device control four */
    {0x15, 0, 0x0015}, /* NAK */
    {0x16, 0, 0x0016}, /* Synch */
    {0x17, 0, 0x0017}, /* End of block */
    {0x18, 0, 0x0018}, /* Cancel */
    {0x19, 0, 0x0019}, /* End of medium */
    {0x1A, 0, 0x001A}, /* Substitute */
    {0x1B, 0, 0x001B}, /* ESC */
    {0x1C, 0, 0x001C}, /* File separator */
    {0x1D, 0, 0x001D}, /* Group separator */
    {0x1E, 0, 0x001E}, /* Record separator */
    {0x1F, 0, 0x001F}, /* Unit separator */
    {0x20, 0, 0x0020}, /* Space */
    {0x21, 0, 0x0021}, /* Exclamation mark */
    {0x22, 0, 0x0022}, /* Quotation mark */
    {0x23, 0, 0x0023}, /* Number sign */
    {0x24, 0, 0x0024}, /* Dollar sign */
    {0x25, 0, 0x0025}, /* Percent sign */
    {0x26, 0, 0x0026}, /* Ampersand */
    {0x27, 0, 0x0027}, /* Apostrophe */
    {0x28, 0, 0x0028}, /* Left parenthesis */
    {0x29, 0, 0x0029}, /* Right parenthesis */
    {0x2A, 0, 0x002A}, /* Asterisk */
    {0x2B, 0, 0x002B}, /* Plus */
    {0x2C, 0, 0x002C}, /* Comma */
    {0x2D, 0, 0x002D}, /* Hyphen */
    {0x2E, 0, 0x002E}, /* Full stop */
    {0x2F, 0, 0x002F}, /* Solidus */
    {0x30, 0, 0x0030}, /* Zero */
    {0x31, 0, 0x0031}, /* One */
    {0x32, 0, 0x0032}, /* Two */
    {0x33, 0, 0x0033}, /* Three */
    {0x34, 0, 0x0034}, /* Four */
    {0x35, 0, 0x0035}, /* Five */
    {0x36, 0, 0x0036}, /* Six */
    {0x37, 0, 0x0037}, /* Seven */
    {0x38, 0, 0x0038}, /* Eight */
    {0x39, 0, 0x0039}, /* Nine */
    {0x3A, 0, 0x003A}, /* Colon */
    {0x3B, 0, 0x003B}, /* Semicolon */
    {0x3C, 0, 0x003C}, /* < (Less than) */
    {0x3D, 0, 0x003D}, /* = Equals */
    {0x3E, 0, 0x003E}, /* > greater than */
    {0x3F, 0, 0x003F}, /* Question mark */
    {0x40, 0, 0x0040}, /* AT Sign */
    {0x41, 0, 0x0041}, /* Latin A */
    {0x42, 0, 0x0042}, /* Latin B */
    {0x43, 0, 0x0043}, /* Latin C */
    {0x44, 0, 0x0044}, /* Latin D */
    {0x45, 0, 0x0045}, /* Latin E */
    {0x46, 0, 0x0046}, /* Latin F */
    {0x47, 0, 0x0047}, /* Latin G */
    {0x48, 0, 0x0048}, /* Latin H */
    {0x49, 0, 0x0049}, /* Latin I */
    {0x4A, 0, 0x004A}, /* Latin J */
    {0x4B, 0, 0x004B}, /* Latin K */
    {0x4C, 0, 0x004C}, /* Latin L */
    {0x4D, 0, 0x004D}, /* Latin M */
    {0x4E, 0, 0x004E}, /* Latin N */
    {0x4F, 0, 0x004F}, /* Latin O */
    {0x50, 0, 0x0050}, /* Latin P */
    {0x51, 0, 0x0051}, /* Latin Q */
    {0x52, 0, 0x0052}, /* Latin R */
    {0x53, 0, 0x0053}, /* Latin S */
    {0x54, 0, 0x0054}, /* Latin T */
    {0x55, 0, 0x0055}, /* Latin U */
    {0x56, 0, 0x0056}, /* Latin V */
    {0x57, 0, 0x0057}, /* Latin W */
    {0x58, 0, 0x0058}, /* Latin X */
    {0x59, 0, 0x0059}, /* Latin Y */
    {0x5A, 0, 0x005A}, /* Latin Z */
    {0x5B, 0, 0x005B}, /* Left square bracket */
    {0x5C, 0, 0x005C}, /* Reverse solidus */
    {0x5D, 0, 0x005D}, /* Right square bracket */
    {0x5E, 0, 0x005E}, /* Circumflex accent */
    {0x5F, 0, 0x005F}, /* Low line */
    {0x60, 0, 0x0060}, /* Grave accent */
    {0x61, 0, 0x0061}, /* Latin a */
    {0x62, 0, 0x0062}, /* Latin b */
    {0x63, 0, 0x0063}, /* Latin c */
    {0x64, 0, 0x0064}, /* Latin d */
    {0x65, 0, 0x0065}, /* Latin e */
    {0x66, 0, 0x0066}, /* Latin f */
    {0x67, 0, 0x0067}, /* Latin g */
    {0x68, 0, 0x0068}, /* Latin h */
    {0x69, 0, 0x0069}, /* Latin i */
    {0x6A, 0, 0x006A}, /* Latin j */
    {0x6B, 0, 0x006B}, /* Latin k */
    {0x6C, 0, 0x006C}, /* Latin l */
    {0x6D, 0, 0x006D}, /* Latin m */
    {0x6E, 0, 0x006E}, /* Latin n */
    {0x6F, 0, 0x006F}, /* Latin o */
    {0x70, 0, 0x0070}, /* Latin p */
    {0x71, 0, 0x0071}, /* Latin q */
    {0x72, 0, 0x0072}, /* Latin r */
    {0x73, 0, 0x0073}, /* Latin s */
    {0x74, 0, 0x0074}, /* Latin t */
    {0x75, 0, 0x0075}, /* Latin u */
    {0x76, 0, 0x0076}, /* Latin v */
    {0x77, 0, 0x0077}, /* Latin w */
    {0x78, 0, 0x0078}, /* Latin x */
    {0x79, 0, 0x0079}, /* Latin y */
    {0x7A, 0, 0x007A}, /* Latin z */
    {0x7B, 0, 0x007B}, /* Left curly bracket */
    {0x7C, 0, 0x007C}, /* Vertical line */
    {0x7D, 0, 0x007D}, /* Right curly bracket */
    {0x7E, 0, 0x007E}, /* Tilde */
    {0x7F, 0, 0x007F}, /* DEL */
    {0x80, 0, 0x0080}, /* control character 0x80 */
    {0x81, 0, 0x0081}, /* control character 0x81 */
    {0x82, 0, 0x0082}, /* control character 0x82 */
    {0x83, 0, 0x0083}, /* control character 0x83 */
    {0x84, 0, 0x0084}, /* control character 0x84 */
    {0x85, 0, 0x0085}, /* control character 0x85 */
    {0x86, 0, 0x0086}, /* control character 0x86 */
    {0x87, 0, 0x0087}, /* control character 0x87 */
    {0x88, 0, 0x0088}, /* control character 0x88 */
    {0x89, 0, 0x0089}, /* control character 0x89 */
    {0x8A, 0, 0x008A}, /* control character 0x8A */
    {0x8B, 0, 0x008B}, /* control character 0x8B */
    {0x8C, 0, 0x008C}, /* control character 0x8C */
    {0x8D, 0, 0x008D}, /* control character 0x8D */
    {0x8E, 0, 0x008E}, /* control character 0x8E */
    {0x8F, 0, 0x008F}, /* control character 0x8F */
    {0x90, 0, 0x0394}, /* Greek capital letter delta */
    {0x91, 0, 0x20AC}, /* Euro sign */
    {0x92, 0, 0x03A6}, /* Greek capital letter phi */
    {0x93, 0, 0x0393}, /* Greek capital letter gamma */
    {0x94, 0, 0x039B}, /* Greek capital letter lamda */
    {0x95, 0, 0x03A9}, /* Greek capital letter omega */
    {0x96, 0, 0x03A0}, /* Greek capital letter pi */
    {0x97, 0, 0x03A8}, /* Greek capital letter psi */
    {0x98, 0, 0x03A3}, /* Greek capital letter sigma */
    {0x99, 0, 0x0398}, /* Greek capital letter theta */
    {0x9A, 0, 0x039E}, /* Greek capital letter xi */
    {0x9B, 0, 0x009B}, /* control character 0x9B */
    {0x9C, 0, 0x009C}, /* control character 0x9C */
    {0x9D, 0, 0x009D}, /* control character 0x9D */
    {0x9E, 0, 0x009E}, /* control character 0x9E */
    {0x9F, 0, 0x009F}, /* control character 0x9F */
    {0xA0, 0, 0x00A0}, /* Non-Block Space */
    {0xA1, 0, 0x00A1}, /* Inverted exclamation mark */
    {0xA2, 0, 0x00A2}, /* Cent sign */
    {0xA3, 0, 0x00A3}, /* Pound sign */
    {0xA4, 0, 0x00A4}, /* Currency sign */
    {0xA5, 0, 0x00A5}, /* Yen sign */
    {0xA6, 0, 0x00A6}, /* Broken Vertical bar */
    {0xA7, 0, 0x00A7}, /* Section sign */
    {0xA8, 0, 0x00A8}, /* Diaeresis */
    {0xA9, 0, 0x00A9}, /* Copyright sign */
    {0xAA, 0, 0x00AA}, /* Feminine ordinal indicator */
    {0xAB, 0, 0x00AB}, /* Left-pointing double angle quotation mark */
    {0xAC, 0, 0x00AC}, /* Not sign */
    {0xAD, 0, 0x00AD}, /* Soft hyphen */
    {0xAE, 0, 0x00AE}, /* Registered sign */
    {0xAF, 0, 0x00AF}, /* Macron */
    {0xB0, 0, 0x00B0}, /* Degree sign */
    {0xB1, 0, 0x00B1}, /* Plus-minus sign */
    {0xB2, 0, 0x00B2}, /* Superscript two */
    {0xB3, 0, 0x00B3}, /* Superscript three */
    {0xB4, 0, 0x00B4}, /* Acute accent */
    {0xB5, 0, 0x00B5}, /* Micro sign */
    {0xB6, 0, 0x00B6}, /* Pilcrow sign */
    {0xB7, 0, 0x00B7}, /* Middle dot */
    {0xB8, 0, 0x00B8}, /* Cedilla */
    {0xB9, 0, 0x00B9}, /* Superscript one */
    {0xBA, 0, 0x00BA}, /* Masculine ordinal indicator */
    {0xBB, 0, 0x00BB}, /* Right-pointing double angle quotation mark */
    {0xBC, 0, 0x00BC}, /* Fraction one quarter */
    {0xBD, 0, 0x00BD}, /* Fraction one half */
    {0xBE, 0, 0x00BE}, /* Fraction three quarters */
    {0xBF, 0, 0x00BF}, /* Inverted question mark */
    {0xC0, 0, 0x00C0}, /* Latin A With grave */
    {0xC1, 0, 0x00C1}, /* Latin A With acute */
    {0xC2, 0, 0x00C2}, /* Latin A With circumflex */
    {0xC3, 0, 0x00C3}, /* Latin A With tilde */
    {0xC4, 0, 0x00C4}, /* Latin A With diaeresis */
    {0xC5, 0, 0x00C5}, /* Latin A With ring above */
    {0xC6, 0, 0x00C6}, /* Latin AE */
    {0xC7, 0, 0x00C7}, /* Latin C with cedilla */
    {0xC8, 0, 0x00C8}, /* Latin E with grave */
    {0xC9, 0, 0x00C9}, /* Latin E with acute */
    {0xCA, 0, 0x00CA}, /* Latin E with circumflex */
    {0xCB, 0, 0x00CB}, /* Latin E with diaeresis */
    {0xCC, 0, 0x00CC}, /* Latin I with grave */
    {0xCD, 0, 0x00CD}, /* Latin I with acute */
    {0xCE, 0, 0x00CE}, /* Latin I with circumflex */
    {0xCF, 0, 0x00CF}, /* Latin I with diaeresis */
    {0xD0, 0, 0x00D0}, /* Latin CAPITAL LETTER ETH (Icelandic) */
    {0xD1, 0, 0x00D1}, /* Latin CAPITAL LETTER N WITH TILDE */
    {0xD2, 0, 0x00D2}, /* Latin CAPITAL LETTER O WITH GRAVE */
    {0xD3, 0, 0x00D3}, /* Latin CAPITAL LETTER O WITH ACUTE */
    {0xD4, 0, 0x00D4}, /* Latin CAPITAL LETTER O WITH CIRCUMFLEX */
    {0xD5, 0, 0x00D5}, /* Latin CAPITAL LETTER O WITH TILDE */
    {0xD6, 0, 0x00D6}, /* Latin CAPITAL LETTER O WITH DIAERESIS */
    {0xD7, 0, 0x00D7}, /* MULTIPLICATION SIGN */
    {0xD8, 0, 0x00D8}, /* Latin CAPITAL LETTER O WITH STROKE */
    {0xD9, 0, 0x00D9}, /* Latin CAPITAL LETTER U WITH GRAVE */
    {0xDA, 0, 0x00DA}, /* Latin CAPITAL LETTER U WITH ACUTE */
    {0xDB, 0, 0x00DB}, /* Latin CAPITAL LETTER U WITH CIRCUMFLEX */
    {0xDC, 0, 0x00DC}, /* Latin CAPITAL LETTER U WITH DIAERESIS */
    {0xDD, 0, 0x00DD}, /* Latin CAPITAL LETTER Y WITH ACUTE */
    {0xDE, 0, 0x00DE}, /* Latin CAPITAL LETTER THORN (Icelandic) */
    {0xDF, 0, 0x00DF}, /* Latin SHARP S (German) */
    {0xE0, 0, 0x00E0}, /* Latin A WITH GRAVE */
    {0xE1, 0, 0x00E1}, /* Latin A WITH ACUTE */
    {0xE2, 0, 0x00E2}, /* Latin A WITH CIRCUMFLEX */
    {0xE3, 0, 0x00E3}, /* Latin A WITH TILDE */
    {0xE4, 0, 0x00E4}, /* Latin A WITH DIAERESIS */
    {0xE5, 0, 0x00E5}, /* Latin A WITH RING ABOVE */
    {0xE6, 0, 0x00E6}, /* Latin AE */
    {0xE7, 0, 0x00E7}, /* Latin C WITH CEDILLA */
    {0xE8, 0, 0x00E8}, /* Latin E WITH GRAVE */
    {0xE9, 0, 0x00E9}, /* Latin E WITH ACUTE */
    {0xEA, 0, 0x00EA}, /* Latin E WITH CIRCUMFLEX */
    {0xEB, 0, 0x00EB}, /* Latin E WITH DIAERESIS */
    {0xEC, 0, 0x00EC}, /* Latin I WITH GRAVE */
    {0xED, 0, 0x00ED}, /* Latin I WITH ACUTE */
    {0xEE, 0, 0x00EE}, /* Latin I WITH CIRCUMFLEX */
    {0xEF, 0, 0x00EF}, /* Latin I WITH DIAERESIS */
    {0xF0, 0, 0x00F0}, /* Latin ETH (Icelandic) */
    {0xF1, 0, 0x00F1}, /* Latin N WITH TILDE */
    {0xF2, 0, 0x00F2}, /* Latin O WITH GRAVE */
    {0xF3, 0, 0x00F3}, /* Latin O WITH ACUTE */
    {0xF4, 0, 0x00F4}, /* Latin O WITH CIRCUMFLEX */
    {0xF5, 0, 0x00F5}, /* Latin O WITH TILDE */
    {0xF6, 0, 0x00F6}, /* Latin O WITH DIAERESIS */
    {0xF7, 0, 0x00F7}, /* DIVISION SIGN */
    {0xF8, 0, 0x00F8}, /* Latin O WITH STROKE */
    {0xF9, 0, 0x00F9}, /* Latin U WITH GRAVE */
    {0xFA, 0, 0x00FA}, /* Latin U WITH ACUTE */
    {0xFB, 0, 0x00FB}, /* Latin U WITH CIRCUMFLEX */
    {0xFC, 0, 0x00FC}, /* Latin U WITH DIAERESIS */
    {0xFD, 0, 0x00FD}, /* Latin Y WITH ACUTE */
    {0xFE, 0, 0x00FE}, /* Latin THORN (Icelandic) */
    {0xFF, 0, 0x00FF}, /* Latin Y WITH DIAERESIS */
};

/* The following table maps the gsm7 alphabet to the corresponding unicode
 * characters. This table is exactly 128 entries large. */
AT_PB_CONVERSION_TABLE_STRU g_astGsmToUnicode[AT_PB_GSM_MAX_NUM] =
{
    {0x00, 0, 0x0040}, /* COMMERCIAL AT */
    {0x01, 0, 0x00A3}, /* POUND SIGN */
    {0x02, 0, 0x0024}, /* DOLLAR SIGN */
    {0x03, 0, 0x00A5}, /* YEN SIGN */
    {0x04, 0, 0x00E8}, /* Latin E WITH GRAVE */
    {0x05, 0, 0x00E9}, /* Latin E WITH ACUTE */
    {0x06, 0, 0x00F9}, /* Latin U WITH GRAVE */
    {0x07, 0, 0x00EC}, /* Latin I WITH GRAVE */
    {0x08, 0, 0x00F2}, /* Latin O WITH GRAVE */
    {0x09, 0, 0x00E7}, /* Latin C WITH CEDILLA */
    {0x0A, 0, 0x000A}, /* LINE FEED */
    {0x0B, 0, 0x00D8}, /* Latin CAPITAL LETTER O WITH STROKE */
    {0x0C, 0, 0x00F8}, /* Latin O WITH STROKE */
    {0x0D, 0, 0x000D}, /* CARRIAGE RETURN */
    {0x0E, 0, 0x00C5}, /* Latin CAPITAL LETTER A WITH RING ABOVE */
    {0x0F, 0, 0x00E5}, /* Latin A WITH RING ABOVE */
    {0x10, 0, 0x0394}, /* GREEK CAPITAL LETTER DELTA */
    {0x11, 0, 0x005F}, /* LOW LINE */
    {0x12, 0, 0x03A6}, /* GREEK CAPITAL LETTER PHI */
    {0x13, 0, 0x0393}, /* GREEK CAPITAL LETTER GAMMA */
    {0x14, 0, 0x039B}, /* GREEK CAPITAL LETTER LAMDA */
    {0x15, 0, 0x03A9}, /* GREEK CAPITAL LETTER OMEGA */
    {0x16, 0, 0x03A0}, /* GREEK CAPITAL LETTER PI */
    {0x17, 0, 0x03A8}, /* GREEK CAPITAL LETTER PSI */
    {0x18, 0, 0x03A3}, /* GREEK CAPITAL LETTER SIGMA */
    {0x19, 0, 0x0398}, /* GREEK CAPITAL LETTER THETA */
    {0x1A, 0, 0x039E}, /* GREEK CAPITAL LETTER XI */
    {0x1B, 0, 0x00A0}, /* ESCAPE TO EXTENSION TABLE */
    {0x1C, 0, 0x00C6}, /* Latin CAPITAL LETTER AE */
    {0x1D, 0, 0x00E6}, /* Latin AE */
    {0x1E, 0, 0x00DF}, /* Latin SHARP S (German) */
    {0x1F, 0, 0x00C9}, /* Latin CAPITAL LETTER E WITH ACUTE */
    {0x20, 0, 0x0020}, /* SPACE */
    {0x21, 0, 0x0021}, /* EXCLAMATION MARK */
    {0x22, 0, 0x0022}, /* QUOTATION MARK */
    {0x23, 0, 0x0023}, /* NUMBER SIGN */
    {0x24, 0, 0x00A4}, /* CURRENCY SIGN */
    {0x25, 0, 0x0025}, /* PERCENT SIGN */
    {0x26, 0, 0x0026}, /* AMPERSAND */
    {0x27, 0, 0x0027}, /* APOSTROPHE */
    {0x28, 0, 0x0028}, /* LEFT PARENTHESIS */
    {0x29, 0, 0x0029}, /* RIGHT PARENTHESIS */
    {0x2A, 0, 0x002A}, /* ASTERISK */
    {0x2B, 0, 0x002B}, /* PLUS SIGN */
    {0x2C, 0, 0x002C}, /* COMMA */
    {0x2D, 0, 0x002D}, /* HYPHEN-MINUS */
    {0x2E, 0, 0x002E}, /* FULL STOP */
    {0x2F, 0, 0x002F}, /* SOLIDUS */
    {0x30, 0, 0x0030}, /* DIGIT ZERO */
    {0x31, 0, 0x0031}, /* DIGIT ONE */
    {0x32, 0, 0x0032}, /* DIGIT TWO */
    {0x33, 0, 0x0033}, /* DIGIT THREE */
    {0x34, 0, 0x0034}, /* DIGIT FOUR */
    {0x35, 0, 0x0035}, /* DIGIT FIVE */
    {0x36, 0, 0x0036}, /* DIGIT SIX */
    {0x37, 0, 0x0037}, /* DIGIT SEVEN */
    {0x38, 0, 0x0038}, /* DIGIT EIGHT */
    {0x39, 0, 0x0039}, /* DIGIT NINE */
    {0x3A, 0, 0x003A}, /* COLON */
    {0x3B, 0, 0x003B}, /* SEMICOLON */
    {0x3C, 0, 0x003C}, /* LESS-THAN SIGN */
    {0x3D, 0, 0x003D}, /* EQUALS SIGN */
    {0x3E, 0, 0x003E}, /* GREATER-THAN SIGN */
    {0x3F, 0, 0x003F}, /* QUESTION MARK */
    {0x40, 0, 0x00A1}, /* INVERTED EXCLAMATION MARK */
    {0x41, 0, 0x0041}, /* Latin CAPITAL LETTER A */
    {0x42, 0, 0x0042}, /* Latin CAPITAL LETTER B */
    {0x43, 0, 0x0043}, /* Latin CAPITAL LETTER C */
    {0x44, 0, 0x0044}, /* Latin CAPITAL LETTER D */
    {0x45, 0, 0x0045}, /* Latin CAPITAL LETTER E */
    {0x46, 0, 0x0046}, /* Latin CAPITAL LETTER F */
    {0x47, 0, 0x0047}, /* Latin CAPITAL LETTER G */
    {0x48, 0, 0x0048}, /* Latin CAPITAL LETTER H */
    {0x49, 0, 0x0049}, /* Latin CAPITAL LETTER I */
    {0x4A, 0, 0x004A}, /* Latin CAPITAL LETTER J */
    {0x4B, 0, 0x004B}, /* Latin CAPITAL LETTER K */
    {0x4C, 0, 0x004C}, /* Latin CAPITAL LETTER L */
    {0x4D, 0, 0x004D}, /* Latin CAPITAL LETTER M */
    {0x4E, 0, 0x004E}, /* Latin CAPITAL LETTER N */
    {0x4F, 0, 0x004F}, /* Latin CAPITAL LETTER O */
    {0x50, 0, 0x0050}, /* Latin CAPITAL LETTER P */
    {0x51, 0, 0x0051}, /* Latin CAPITAL LETTER Q */
    {0x52, 0, 0x0052}, /* Latin CAPITAL LETTER R */
    {0x53, 0, 0x0053}, /* Latin CAPITAL LETTER S */
    {0x54, 0, 0x0054}, /* Latin CAPITAL LETTER T */
    {0x55, 0, 0x0055}, /* Latin CAPITAL LETTER U */
    {0x56, 0, 0x0056}, /* Latin CAPITAL LETTER V */
    {0x57, 0, 0x0057}, /* Latin CAPITAL LETTER W */
    {0x58, 0, 0x0058}, /* Latin CAPITAL LETTER X */
    {0x59, 0, 0x0059}, /* Latin CAPITAL LETTER Y */
    {0x5A, 0, 0x005A}, /* Latin CAPITAL LETTER Z */
    {0x5B, 0, 0x00C4}, /* Latin CAPITAL LETTER A WITH DIAERESIS */
    {0x5C, 0, 0x00D6}, /* Latin CAPITAL LETTER O WITH DIAERESIS */
    {0x5D, 0, 0x00D1}, /* Latin CAPITAL LETTER N WITH TILDE */
    {0x5E, 0, 0x00DC}, /* Latin CAPITAL LETTER U WITH DIAERESIS */
    {0x5F, 0, 0x00A7}, /* SECTION SIGN */
    {0x60, 0, 0x00BF}, /* INVERTED QUESTION MARK */
    {0x61, 0, 0x0061}, /* Latin A */
    {0x62, 0, 0x0062}, /* Latin B */
    {0x63, 0, 0x0063}, /* Latin C */
    {0x64, 0, 0x0064}, /* Latin D */
    {0x65, 0, 0x0065}, /* Latin E */
    {0x66, 0, 0x0066}, /* Latin F */
    {0x67, 0, 0x0067}, /* Latin G */
    {0x68, 0, 0x0068}, /* Latin H */
    {0x69, 0, 0x0069}, /* Latin I */
    {0x6A, 0, 0x006A}, /* Latin J */
    {0x6B, 0, 0x006B}, /* Latin K */
    {0x6C, 0, 0x006C}, /* Latin L */
    {0x6D, 0, 0x006D}, /* Latin M */
    {0x6E, 0, 0x006E}, /* Latin N */
    {0x6F, 0, 0x006F}, /* Latin O */
    {0x70, 0, 0x0070}, /* Latin P */
    {0x71, 0, 0x0071}, /* Latin Q */
    {0x72, 0, 0x0072}, /* Latin R */
    {0x73, 0, 0x0073}, /* Latin S */
    {0x74, 0, 0x0074}, /* Latin T */
    {0x75, 0, 0x0075}, /* Latin U */
    {0x76, 0, 0x0076}, /* Latin V */
    {0x77, 0, 0x0077}, /* Latin W */
    {0x78, 0, 0x0078}, /* Latin X */
    {0x79, 0, 0x0079}, /* Latin Y */
    {0x7A, 0, 0x007A}, /* Latin Z */
    {0x7B, 0, 0x00E4}, /* Latin A WITH DIAERESIS */
    {0x7C, 0, 0x00F6}, /* Latin O WITH DIAERESIS */
    {0x7D, 0, 0x00F1}, /* Latin N WITH TILDE */
    {0x7E, 0, 0x00FC}, /* Latin U WITH DIAERESIS */
    {0x7F, 0, 0x00E0}, /* Latin A WITH GRAVE */
};

/* GSM7BIT ??UCS2????????????,GSM7BIT????????????????0x1b??????????GSM7BIT??????
????????0x1B65????????????UCS2??????0x20AC?????????????????? */
AT_PB_CONVERSION_TABLE_STRU g_astGsm7extToUnicode[AT_PB_GSM7EXT_MAX_NUM] =
{
    {0x65, 0, 0x20AC}, /* EURO SIGN */
    {0x0A, 0, 0x000C}, /* FORM FEED */
    {0x14, 0, 0x005E}, /* CIRCUMFLEX ACCENT */
    {0x28, 0, 0x007B}, /* LEFT CURLY BRACKET */
    {0x29, 0, 0x007D}, /* RIGHT CURLY BRACKET */
    {0x2F, 0, 0x005C}, /* REVERSE SOLIDUS */
    {0x3C, 0, 0x005B}, /* LEFT SQUARE BRACKET */
    {0x3D, 0, 0x007E}, /* TILDE */
    {0x3E, 0, 0x005D}, /* RIGHT SQUARE BRACKET */
    {0x40, 0, 0x007C}, /* VERTICAL LINE */
};

const AT_STRING_TYPE_STRU gastAtStringTab[]=
{
    {AT_STRING_SM,(TAF_UINT8*)"\"SM\""},
    {AT_STRING_ME,(TAF_UINT8*)"\"ME\""},
    {AT_STRING_ON,(TAF_UINT8*)"\"ON\""},
    {AT_STRING_EN,(TAF_UINT8*)"\"EN\""},
    {AT_STRING_FD,(TAF_UINT8*)"\"FD\""},
    {AT_STRING_BD,(TAF_UINT8*)"\"BD\""},
    {AT_STRING_REC_UNREAD_TEXT,(TAF_UINT8*)"\"REC UNREAD\""},
    {AT_STRING_REC_READ_TEXT,(TAF_UINT8*)"\"REC READ\""},
    {AT_STRING_STO_UNSENT_TEXT,(TAF_UINT8*)"\"STO UNSENT\""},
    {AT_STRING_STO_SENT_TEXT,(TAF_UINT8*)"\"STO SENT\""},
    {AT_STRING_ALL_TEXT,(TAF_UINT8*)"\"ALL\""},
    {AT_STRING_REC_UNREAD_PDU,(TAF_UINT8*)"0"},
    {AT_STRING_REC_READ_PDU,(TAF_UINT8*)"1"},
    {AT_STRING_STO_UNSENT_PDU,(TAF_UINT8*)"2"},
    {AT_STRING_STO_SENT_PDU,(TAF_UINT8*)"3"},
    {AT_STRING_ALL_PDU,(TAF_UINT8*)"4"},
    {AT_STRING_IP,(TAF_UINT8*)"\"IP\""},
    {AT_STRING_IPv4,    (VOS_UINT8*)"\"IPv4\""},
    {AT_STRING_PPP,(TAF_UINT8*)"\"PPP\""},
    {AT_STRING_IPV6,(VOS_UINT8*)"\"IPV6\""},
    {AT_STRING_IPV4V6,(VOS_UINT8*)"\"IPV4V6\""},
    {AT_STRING_IPv6,    (VOS_UINT8*)"\"IPv6\""},
    {AT_STRING_IPv4v6,  (VOS_UINT8*)"\"IPv4v6\""},

    {AT_STRING_0E0,(TAF_UINT8*)"\"0E0\""},
    {AT_STRING_1E2,(TAF_UINT8*)"\"1E2\""},
    {AT_STRING_7E3,(TAF_UINT8*)"\"7E3\""},
    {AT_STRING_1E3,(TAF_UINT8*)"\"1E3\""},
    {AT_STRING_1E4,(TAF_UINT8*)"\"1E4\""},
    {AT_STRING_1E5,(TAF_UINT8*)"\"1E5\""},
    {AT_STRING_1E6,(TAF_UINT8*)"\"1E6\""},
    {AT_STRING_1E1,(TAF_UINT8*)"\"1E1\""},
    {AT_STRING_5E2,(TAF_UINT8*)"\"5E2\""},
    {AT_STRING_5E3,(TAF_UINT8*)"\"5E3\""},
    {AT_STRING_4E3,(TAF_UINT8*)"\"4E3\""},
    {AT_STRING_6E8,(TAF_UINT8*)"\"6E8\""},

    {AT_STRING_CREG,(TAF_UINT8*)"+CREG: "},
    {AT_STRING_CGREG,(TAF_UINT8*)"+CGREG: "},
#if(FEATURE_ON == FEATURE_LTE)
    {AT_STRING_CEREG,(TAF_UINT8*)"+CEREG: "},

    {AT_STRING_SIB16TIME, (VOS_UINT8 *)"^SIB16TIME: "},
#endif
    {AT_STRING_SRVST,(TAF_UINT8*)"^SRVST: "},
    {AT_STRING_MODE,(TAF_UINT8*)"^MODE: "},
    {AT_STRING_RSSI,(TAF_UINT8*)"^RSSI: "},
    {AT_STRING_TIME,(TAF_UINT8*)"^TIME: "},
    {AT_STRING_CTZV,(TAF_UINT8*)"+CTZV: "},
    {AT_STRING_CTZE,(TAF_UINT8*)"+CTZE: "},
    {AT_STRING_ERRRPT,(TAF_UINT8*)"^ERRRPT:"},

    {AT_STRING_CCALLSTATE, (VOS_UINT8 *)"^CCALLSTATE"},

    {AT_STRING_CERSSI, (VOS_UINT8 *)"^CERSSI:"},

    {AT_STRING_ACINFO, (VOS_UINT8 *)"^ACINFO:"},

    {AT_STRING_CS_CHANNEL_INFO, (VOS_UINT8 *)"^CSCHANNELINFO:"},

    {AT_STRING_RESET, (VOS_UINT8 *)"^RESET:"},

    {AT_STRING_REFCLKFREQ, (VOS_UINT8 *)"^REFCLKFREQ"},

    {AT_STRING_REJINFO, (VOS_UINT8 *)"^REJINFO: "},

    {AT_STRING_PLMNSELEINFO, (VOS_UINT8 *)"^PLMNSELEINFO:"},

    {AT_STRING_NETSCAN, (VOS_UINT8 *)"^NETSCAN: "},

#if (FEATURE_IMS == FEATURE_ON)
    {AT_STRING_CIREPH, (VOS_UINT8 *)"+CIREPH"},
    {AT_STRING_CIREPI, (VOS_UINT8 *)"+CIREPI"},
    {AT_STRING_CIREGU, (VOS_UINT8 *)"+CIREGU"},

    {AT_STRING_CALL_MODIFY_IND, (VOS_UINT8 *)"^CALLMODIFYIND:"},
    {AT_STRING_CALL_MODIFY_BEG, (VOS_UINT8 *)"^CALLMODIFYBEG:"},
    {AT_STRING_CALL_MODIFY_END, (VOS_UINT8 *)"^CALLMODIFYEND:"},

    {AT_STRING_ECONFSTATE, (VOS_UINT8 *)"^ECONFSTATE:"},

#endif

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    {AT_STRING_CDISP,       (TAF_UINT8*)"^CDISP: "},
    {AT_STRING_CCONNNUM,    (TAF_UINT8*)"^CCONNNUM: "},
    {AT_STRING_CCALLEDNUM,  (TAF_UINT8*)"^CCALLEDNUM: "},
    {AT_STRING_CCALLINGNUM, (TAF_UINT8*)"^CCALLINGNUM: "},
    {AT_STRING_CREDIRNUM,   (TAF_UINT8*)"^CREDIRNUM: "},
    {AT_STRING_CSIGTONE,    (TAF_UINT8*)"^CSIGTONE: "},
    {AT_STRING_CLCTR,       (TAF_UINT8*)"^CLCTR: "},
    {AT_STRING_CCWAC,       (TAF_UINT8*)"^CCWAC: "},
#endif
    {AT_STRING_FILECHANGE, (VOS_UINT8 *)"^FILECHANGE:"},

#if((FEATURE_ON == FEATURE_LTE) && (FEATURE_ON == FEATURE_LTE_MBMS))
    {AT_STRING_MBMSEV,      (VOS_UINT8 *)"^MBMSEV:"},
#endif

    {AT_STRING_SRCHEDPLMNINFO, (VOS_UINT8 *)"^SRCHEDPLMNINFO:"},

    {AT_STRING_MCC,       (TAF_UINT8*)"^MCC:"},

    {AT_STRING_CMOLRE,      (VOS_UINT8 *)"+CMOLRE: "},
    {AT_STRING_CMOLRN,      (VOS_UINT8 *)"+CMOLRN: "},
    {AT_STRING_CMOLRG,      (VOS_UINT8 *)"+CMOLRG: "},
    {AT_STRING_CMTLR,       (VOS_UINT8 *)"+CMTLR: "},

#if (FEATURE_IMS == FEATURE_ON)
    {AT_STRING_DMCN,        (VOS_UINT8 *)"^DMCN"},
#endif

    {AT_STRING_IMS_REG_FAIL,   (VOS_UINT8 *)"^IMSREGFAIL: "},

    {AT_STRING_IMSI_REFRESH,    (VOS_UINT8 *)"^IMSIREFRESH"},

    {AT_STRING_AFCCLKUNLOCK, (VOS_UINT8 *)"^AFCCLKUNLOCK: "},

    {AT_STRING_IMS_HOLD_TONE, (VOS_UINT8 *)"^IMSHOLDTONE"},

    {AT_STRING_LIMITPDPACT, (VOS_UINT8 *)"^LIMITPDPACT"},

    {AT_STRING_IMS_REG_ERR, (VOS_UINT8 *)"^IMSREGERR:"},

    {AT_STRING_CUST_PCO_INFO, (VOS_UINT8 *)"^CUSTPCOINFO:"},

    {AT_STRING_BLACK_CELL_MCC, (VOS_UINT8 *)"^REPORTBLACKCELLMCC: "},

    {AT_STRING_ECC_STATUS, (VOS_UINT8 *)"^ECCSTATUS: "},
    {AT_STRING_EPDUR,          (VOS_UINT8 *)"^EPDUR: "},

    {AT_STRING_LINE_RPLMN, (VOS_UINT8 *)"^REPORTLINERPLMN: "},
    {AT_STRING_LINE_INDEX, (VOS_UINT8 *)"^REPORTLINEINDEX: "},

    {AT_STRING_LCACELLEX,  (VOS_UINT8 *)"^LCACELLEX: "},
    {AT_STRING_VT_FLOW_RPT, (VOS_UINT8 *)"^VTFLOWRPT: "},

    {AT_STRING_CALL_ALT_SRV, (VOS_UINT8 *)"^CALLALTSRV"},

    {AT_STRING_FINETIMEINFO,  (VOS_UINT8 *)"^FINETIMEINFO: "},
    {AT_STRING_SFN,           (VOS_UINT8 *)"^SFN: "},
    {AT_STRING_FINETIMEFAIL,  (VOS_UINT8 *)"^FINETIMEFAIL: "},

    {AT_STRING_PHYCOMACK,     (VOS_UINT8 *)"^PHYCOMACK: "},

    {AT_STRING_BOOSTERNTF,    (VOS_UINT8 *)"^BOOSTERNTF: "},

    {AT_STRING_MTREATTACH,    (VOS_UINT8 *)"^MTREATTACH"},

    {AT_STRING_IMPU,          (VOS_UINT8 *)"^IMPU: "},

#if (FEATURE_DSDS == FEATURE_ON)
    {AT_STRING_DSDSSTATE,     (VOS_UINT8 *)"^DSDSSTATE: "},
#endif

    {AT_STRING_TEMPPROTECT,   (VOS_UINT8 *)"^TEMPPROTECT: "},

    {AT_STRING_DIALOGNTF,     (VOS_UINT8 *)"^DIALOGNTF"},
    {AT_STRINT_RTTEVENT,      (VOS_UINT8 *)"^RTTEVT"},
    {AT_STRINT_RTTERROR,      (VOS_UINT8 *)"^RTTERR"},

    {AT_STRING_EMRSSIRPT,     (VOS_UINT8 *)"^EMRSSIRPT: "},

    {AT_STRING_ELEVATOR,      (VOS_UINT8 *)"^ELEVATOR"},

    {AT_STRING_ULFREQRPT,      (VOS_UINT8 *)"^ULFREQRPT"},

    {AT_STRING_PSEUDBTS,      (VOS_UINT8 *)"^PSEUDBTS"},
#if (FEATURE_UE_MODE_NR == FEATURE_ON)
    {AT_STRING_C5GREG,        (TAF_UINT8*)"+C5GREG: "},
    {AT_STRING_CSERSSI,       (VOS_UINT8*)"^CSERSSI:"},
#endif
    {AT_STRING_NDISSTAT,      (VOS_UINT8 *)"^NDISSTAT"},
    {AT_STRING_NDISSTATEX,    (VOS_UINT8 *)"^NDISSTATEX"},

    {AT_STRING_DETECTPLMN,    (VOS_UINT8 *)"^DETECTPLMN"},

    {AT_STRING_BUTT,(TAF_UINT8*)"\"\""},
};

VOS_UINT8                               gaucAtCrLf[] = "\r\n";                  /*????????*/
const TAF_UINT8                         gaucAtCmeErrorStr[] = "+CME ERROR: ";   /*????????????*/
const TAF_UINT8                         gaucAtCmsErrorStr[] = "+CMS ERROR: ";   /*????????????*/

const TAF_UINT8                         gaucAtTooManyParaStr[]   = "TOO MANY PARAMETERS"; /*????????????????*/

AT_CMD_FORMAT_TYPE                      gucAtCmdFmtType = AT_CMD_TYPE_BUTT;

AT_SEND_DATA_BUFFER_STRU                gstAtSendData;                          /* ???????????????????????? */
AT_SEND_DATA_BUFFER_STRU                gstAtCombineSendData[AT_MAX_CLIENT_NUM];/* ???????????????????????? */

/* gstAtSendData.aucBuffer????0????MUX?????????? */
TAF_UINT8                              *pgucAtSndCrLfAddr = &gstAtSendData.aucBuffer[1];
TAF_UINT8                              *pgucAtSndCodeAddr = &gstAtSendData.aucBuffer[3];

TAF_LOG_PRIVACY_AT_CMD_ENUM_UINT32      g_enLogPrivacyAtCmd = TAF_LOG_PRIVACY_AT_CMD_BUTT;

/*????????????????????????????????????????????????4??????????????
??pgucAtSndCrLfAddr??pgucAtSndCodeAddr??????????4????????????????
????????????????(AT??????????????????????????????????????????????)*/
TAF_UINT8                               gstAtSendDataBuffer[AT_CMD_MAX_LEN];

AT_V_TYPE                               gucAtVType      = AT_V_ENTIRE_TYPE;     /* ?????????????????? */
AT_CSCS_TYPE                            gucAtCscsType   = AT_CSCS_IRA_CODE;     /* ????TE???????? */

AT_CMD_ECHO_TYPE                        gucAtEType      = AT_E_ECHO_CMD;
VOS_UINT32                              gucAtXType      = 0;   /* CONNECT <text> result code is given upon entering online data state.
                                                   Dial tone and busy detection are disabled. */
VOS_UINT32                              gucAtQType      = 0;   /* DCE transmits result codes */


MN_OPERATION_ID_T                       g_OpId = 0;

MN_MSG_RAW_TS_DATA_STRU                 g_astAtMsgRawTsData[AT_MSG_MAX_MSG_SEGMENT_NUM];
MN_MSG_TS_DATA_INFO_STRU                g_stAtMsgTsDataInfo;
MN_MSG_SEND_PARM_STRU                   g_stAtMsgDirectParm;
MN_MSG_WRITE_PARM_STRU                  g_stAtMsgWriteParm;
MN_MSG_SEND_ACK_PARM_STRU               g_stAtMsgAckParm;

AT_CSTA_NUM_TYPE_ENUM_U8                g_enAtCstaNumType = (0x80 | (MN_CALL_TON_INTERNATIONAL << 4) | (MN_CALL_NPI_ISDN));
AT_PB_INFO_STRU                         gstPBATInfo;


/* ????^PORTSEL????????????????????^PORTSEL? ?????????? */
TAF_UINT8                               gucAtPortSel  = 0;

/*?????????????????????????????????????????????? */
VOS_UINT32                              g_ulLcStartTime = 0;

TAF_UINT8                               gastAtPppIndexTab[AT_MAX_CLIENT_NUM];   /* PppId??Index????????????????PppId */

VOS_BOOL                                g_bAtDataLocked         = VOS_TRUE;     /* ??????????????????????????????????????^DATALOCK???????????????????? */
VOS_UINT8                               g_ucDtrDownFlag         = VOS_FALSE;    /* ??????????????????????????DTR??????????????AT??????????????VOS_TRUE,????DCD??????
                                                                                ????CST????AT????AT_CstDlDataInd??????????????????????????????VOS_TRUE,????????????????????
                                                                                ????????????*/

/*????????????????????????????????????AT_PHY_PORT_ENUM????????*/
CBTCPM_RCV_FUNC                         g_apAtPortDataRcvFuncTab[AT_PHY_PORT_MAX]
                                                = {VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR};


#if (FEATURE_SECURITY_SHELL == FEATURE_ON)
AT_SP_WORD_CTX_STRU                     g_stSpWordCtx = {0};
#endif

AT_PS_INTERNAL_TIMEOUT_RESULT_STRU            g_astAtInterTimeoutResultTab[] =
{
    /* Inter Timer Name */                  /* ???????????? */
    {AT_S0_TIMER,                           AT_RcvTiS0Expired                       },
    {AT_HOLD_CMD_TIMER,                     AT_BlockCmdTimeOutProc                  },
    {AT_SIMLOCKWRITEEX_TIMER,               AT_RcvTiSimlockWriteExExpired           },
#if (FEATURE_AT_HSUART == FEATURE_ON)
    {AT_VOICE_RI_TIMER,                     AT_RcvTiVoiceRiExpired                  },
    {AT_SMS_RI_TIMER,                       AT_RcvTiSmsRiExpired                    },
#endif
#if(FEATURE_ON == FEATURE_LTE)
    {AT_SHUTDOWN_TIMER,                     AT_RcvTiShutDownExpired                 },
#endif
    {AT_AUTH_PUBKEY_TIMER,                  AT_RcvTiAuthPubkeyExpired               },
};

/*****************************************************************************
   3 ??????????????
*****************************************************************************/
VOS_VOID At_AdjustLocalDate(
        TIME_ZONE_TIME_STRU                 *pstUinversalTime,
        VOS_INT8                             cAdjustValue,
        TIME_ZONE_TIME_STRU                 *pstLocalTime
        );

/*****************************************************************************
   4 ????????
*****************************************************************************/


MN_OPERATION_ID_T  At_GetOpId(
    VOS_VOID
)
{
    g_OpId++;
    g_OpId %= MN_OP_ID_BUTT;
    if (g_OpId == 0)
    {
        g_OpId++;
    }
    return (g_OpId);
}



TAF_UINT32 At_ClientIdToUserId (
    TAF_UINT16                              usClientId,
    TAF_UINT8                              *pucIndexId
)
{
    TAF_UINT8                           i;
    *pucIndexId                         = 0;

    /* ??????????????client id */
    /* MODEM 0??????ClientId */
    if (usClientId == AT_BROADCAST_CLIENT_ID_MODEM_0)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
        return AT_SUCCESS;
    }

    /* MODEM 1??????ClientId */
    if(usClientId == AT_BROADCAST_CLIENT_ID_MODEM_1)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
        return AT_SUCCESS;
    }

    /* MODEM 2??????ClientId */
    if(usClientId == AT_BROADCAST_CLIENT_ID_MODEM_2)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_2;
        return AT_SUCCESS;
    }


    /* ?????????????? */
    for ( i = 0; i < AT_MAX_CLIENT_NUM ; i++ )
    {
        if ( gastAtClientTab[i].ucUsed == AT_CLIENT_NULL )
        {
            continue;
        }
        if ( gastAtClientTab[i].usClientId == usClientId )
        {
            *pucIndexId = i;        /* ???????? */
            return AT_SUCCESS;
        }
    }

    return AT_FAILURE;
}


TAF_UINT32 At_ClientIdToUserBroadCastId (
    TAF_UINT16                              usClientId,
    TAF_UINT8                              *pucIndexId
)
{
    VOS_UINT32                          ulRst;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRst = AT_GetModemIdFromClient(usClientId, &enModemId);
    if (ulRst != VOS_OK)
    {
        AT_ERR_LOG1("At_ClientIdToUserBroadCastId:Get ModemID From ClientID fail,ClientID=%d", usClientId);
        return AT_FAILURE;
    }

    if (enModemId == MODEM_ID_0)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    }
#if (MULTI_MODEM_NUMBER > 1)
    else if(enModemId == MODEM_ID_1)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    }
#if (MULTI_MODEM_NUMBER > 2)
    else
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_2;
    }
#endif
#endif

    return AT_SUCCESS;
}



TAF_VOID At_SendReportMsg(TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen)
{
    MN_AT_IND_EVT_STRU                 *pstEvent = VOS_NULL_PTR;
    VOS_UINT_PTR                        ulTmpAddr;
    errno_t                             lMemResult;

    /* ????????????ITEM????4?????? */
    /*lint -save -e516 */
    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
    /*lint -restore */
    if (pstEvent == TAF_NULL_PTR)
    {
        AT_ERR_LOG("At_SendCmdMsg:ERROR:Alloc Msg");
        return;
    }

    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEvent->ulSenderPid       = AT_GetDestPid(((SI_PB_EVENT_INFO_STRU *)pData)->ClientId, I0_WUEPS_PID_TAF);
    pstEvent->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEvent->usMsgName         = ucType;
    pstEvent->usLen             = usLen;

    ulTmpAddr = (VOS_UINT_PTR)pstEvent->aucContent;
    lMemResult = memcpy_s((VOS_VOID *)ulTmpAddr, usLen, pData, usLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, usLen, usLen);

    /*??????????AT_PID;*/
    if ( PS_SEND_MSG( WUEPS_PID_AT, pstEvent ) != 0 )
    {
        AT_ERR_LOG("At_SendReportMsg:ERROR");
        return;
    }

    return;
}


VOS_UINT16 AT_ReportSysCfgExTestCmdResult(
    VOS_UINT8                           ucIndex
)
{

    return 0;
}



/*****************************************************************************
 Prototype      : At_ScanDelChar
 Description    : ??????????
 Input          : pData --- ??????
                  pLen  --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_ScanDelChar( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT16 usChkLen  = 0;
    TAF_UINT16 usLen     = 0;
    TAF_UINT8  *pWrite   = pData;
    TAF_UINT8  *pRead    = pData;

    if(*pLen == 0)
    {
        return AT_FAILURE;
    }

    /* ???????????? */
    while ( usChkLen++ < *pLen )
    {
        if( ucAtS5 == *pRead)       /*????????????*/
        {
            if( usLen > 0 )
            {
                pWrite--;
                usLen--;
            }
        }
        else                        /*????????????*/
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_ScanCtlChar
 Description    : ??????????
 Input          : pData --- ??????
                  pLen  --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_ScanCtlChar( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT8  *pWrite    = pData;
    TAF_UINT8  *pRead     = pData;
    TAF_UINT16 usChkLen   = 0;
    TAF_UINT16 usLen      = 0;

    if(*pLen == 0)
    {
        return AT_FAILURE;
    }

    /* ???? */
    while( usChkLen++ < *pLen )
    {
        /*????????????*/
        if( *pRead >= 0x20 )
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}


TAF_UINT32 At_ScanBlankChar( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT8  *pCheck     = pData;
    TAF_UINT8  *pWrite     = pData;
    TAF_UINT8  *pRead      = pData;
    TAF_UINT32 ulChkQout   = 0;
    TAF_UINT16 usChkLen    = 0;
    TAF_UINT16 usQoutNum   = 0;
    TAF_UINT16 usQoutCount = 0;
    TAF_UINT16 usLen       = 0;

    if(*pLen == 0)
    {
        return AT_FAILURE;
    }

    /* ???????? */
    while( usQoutNum ++ < *pLen )
    {
        if(*pCheck++ == '"')
        {
            ulChkQout++;
        }
    }
    if((ulChkQout % 2) == 1)
    {
        return AT_FAILURE;
    }

    /* ???? */
    while( usChkLen++ < *pLen )
    {
        /* ???????????????????? */
        if( *pRead == '\"' )
        {
            usQoutCount++;
        }

        /* ???????????????? */
        if(( (*pRead != 0x20) && ((usQoutCount % 2) == 0) ) || ( (usQoutCount % 2) == 1 ))
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}


TAF_UINT32 At_ScanResetCmd( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT8  *pSearch = TAF_NULL_PTR;
    TAF_UINT16 usLen    = *pLen;

    /* ?????????? */
    pData[usLen] = 0;

    /* ???????????????????? */
    At_UpString(pData,usLen);

    pSearch = (TAF_UINT8 *)VOS_StrStr((TAF_CHAR*)pData,"&F");

    while(pSearch != TAF_NULL_PTR)
    {
        if( (*(pSearch+2) > '0') && (*(pSearch+2) <= '9'))
        {
            return AT_FAILURE;  /* ???????? */
        }
        if( *(pSearch+2) == '0')
        {
            *(pSearch+2) = 13;  /* ???????????????????????? */
        }
        pSearch = (TAF_UINT8 *)VOS_StrStr((TAF_CHAR*)(pSearch+2),"&F");
    }

    At_ScanCtlChar(pData,&usLen);

    *pLen  =  usLen;
    return AT_SUCCESS;
}



MN_MSG_SEND_PARM_STRU * At_GetDirectSendMsgMem(
    TAF_VOID
)
{
    memset_s(&g_stAtMsgDirectParm, sizeof(g_stAtMsgDirectParm), 0x00, sizeof(g_stAtMsgDirectParm));
    return &g_stAtMsgDirectParm;
}


MN_MSG_TS_DATA_INFO_STRU * At_GetMsgMem(
    VOS_VOID
)
{
    memset_s(&g_stAtMsgTsDataInfo, sizeof(g_stAtMsgTsDataInfo), 0x00, sizeof(g_stAtMsgTsDataInfo));
    return &g_stAtMsgTsDataInfo;
}


MN_MSG_RAW_TS_DATA_STRU *At_GetLongMsgSegMem(
    TAF_VOID
)
{
    memset_s(g_astAtMsgRawTsData, sizeof(g_astAtMsgRawTsData), 0x00, (sizeof(MN_MSG_RAW_TS_DATA_STRU)*AT_MSG_MAX_MSG_SEGMENT_NUM));
    return g_astAtMsgRawTsData;
}


MN_MSG_WRITE_PARM_STRU * At_GetWriteMsgMem(
    TAF_VOID
)
{
    memset_s(&g_stAtMsgWriteParm, sizeof(g_stAtMsgWriteParm), 0x00, sizeof(g_stAtMsgWriteParm));
    return &g_stAtMsgWriteParm;
}


MN_MSG_SEND_ACK_PARM_STRU * At_GetAckMsgMem(
    VOS_VOID
)
{
    memset_s(&g_stAtMsgAckParm, sizeof(g_stAtMsgAckParm), 0x00, sizeof(g_stAtMsgAckParm));
    return &g_stAtMsgAckParm;
}



TAF_UINT32  At_SendPduMsgOrCmd(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
)
{
    errno_t                             lMemResult;
    TAF_UINT32                          ulRet;
    MN_MSG_SEND_PARM_STRU               *pstSendDirectParm = VOS_NULL_PTR;
    TAF_UINT32                          uAddrlLen           = 0;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo = VOS_NULL_PTR;
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU               *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if ((gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_CMGS_PDU_SET)
     && (gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_CMGC_PDU_SET))
    {
        AT_WARN_LOG("At_SendPduMsgOrCmd: invalid command operation.");
        return AT_ERROR;
    }

    /*Refer to protocol 31102 4.2.25 */
    if (gastAtClientTab[ucIndex].AtSmsData.ucPduLen > ulLen)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: invalid tpdu data length.");
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }

    pstSendDirectParm = At_GetDirectSendMsgMem();

    pstSendDirectParm->enMemStore   = MN_MSG_MEM_STORE_NONE;
    pstSendDirectParm->enClientType = MN_MSG_CLIENT_NORMAL;

    /*sca*/
    if (ulLen > gastAtClientTab[ucIndex].AtSmsData.ucPduLen)
    {
        ulRet = At_GetScaFromInputStr(pData, &pstSendDirectParm->stMsgInfo.stScAddr, &uAddrlLen);
        if (ulRet != MN_ERR_NO_ERROR)
        {
            return AT_CMS_INVALID_PDU_MODE_PARAMETER;
        }

        if (ulLen != (gastAtClientTab[ucIndex].AtSmsData.ucPduLen + uAddrlLen))
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: invalid tpdu data length.");
            return AT_CMS_INVALID_PDU_MODE_PARAMETER;
        }
    }

    if (pstSendDirectParm->stMsgInfo.stScAddr.ucBcdLen == 0)
    {
        if (pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen == 0)
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: without sca.");
            return AT_CMS_SMSC_ADDRESS_UNKNOWN;
        }
        lMemResult = memcpy_s(&pstSendDirectParm->stMsgInfo.stScAddr,
                              sizeof(pstSendDirectParm->stMsgInfo.stScAddr),
                              &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
                              sizeof(pstSendDirectParm->stMsgInfo.stScAddr));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstSendDirectParm->stMsgInfo.stScAddr), sizeof(pstSendDirectParm->stMsgInfo.stScAddr));
    }

    pstSendDirectParm->stMsgInfo.stTsRawData.ulLen = gastAtClientTab[ucIndex].AtSmsData.ucPduLen;
    lMemResult = memcpy_s(pstSendDirectParm->stMsgInfo.stTsRawData.aucData,
                          sizeof(pstSendDirectParm->stMsgInfo.stTsRawData.aucData),
                          &pData[uAddrlLen],
                          gastAtClientTab[ucIndex].AtSmsData.ucPduLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstSendDirectParm->stMsgInfo.stTsRawData.aucData), gastAtClientTab[ucIndex].AtSmsData.ucPduLen);
    if (gastAtClientTab[ucIndex].CmdCurrentOpt == AT_CMD_CMGS_PDU_SET)
    {
        pstSendDirectParm->stMsgInfo.stTsRawData.enTpduType = MN_MSG_TPDU_SUBMIT;
    }
    else
    {
        pstSendDirectParm->stMsgInfo.stTsRawData.enTpduType = MN_MSG_TPDU_COMMAND;
    }

    /*????PDU??????????????????????????*/
    pstTsDataInfo = At_GetMsgMem();
    ulRet = MN_MSG_Decode(&pstSendDirectParm->stMsgInfo.stTsRawData, pstTsDataInfo);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: fail to decode.");
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }

    pstRawData = At_GetLongMsgSegMem();
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstRawData);
    if(ulRet != MN_ERR_NO_ERROR)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: fail to encode.");
    }
    else
    {
        if (pstRawData->ulLen != pstSendDirectParm->stMsgInfo.stTsRawData.ulLen)
        {
            AT_NORM_LOG1("At_SendPduMsgOrCmd: pstSendParm->stMsgInfo.stTsRawData.ulLen not match:",
                         pstSendDirectParm->stMsgInfo.stTsRawData.ulLen);
            AT_NORM_LOG1("At_SendPduMsgOrCmd: pstRawData->ulLen not match:", pstRawData->ulLen);
            pstSendDirectParm->stMsgInfo.stTsRawData.ulLen = pstRawData->ulLen;
        }
    }

    gastAtClientTab[ucIndex].opId = opId;
    ulRet = MN_MSG_Send(gastAtClientTab[ucIndex].usClientId,
                        opId,
                        pstSendDirectParm);
    if (ulRet == MN_ERR_NO_ERROR)
    {
        gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = 1;
        ulRet = AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        if (ulRet == MN_ERR_CLASS_SMS_NOAVAILDOMAIN)
        {
            ulRet = AT_CMS_UNKNOWN_ERROR;
        }
        else
        {
            ulRet = AT_ERROR;
        }
    }
    return ulRet;
}



TAF_UINT32  At_SendPduMsgAck(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
)
{
    errno_t                             lMemResult;
    MN_MSG_SEND_ACK_PARM_STRU           *pstAckParm = VOS_NULL_PTR;
    TAF_UINT32                          ulRet;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo = VOS_NULL_PTR;

    if (ulLen != gastAtClientTab[ucIndex].AtSmsData.ucPduLen)
    {
        AT_NORM_LOG("At_SendPduMsgAck: the length of PDU is not consistent.");
        return AT_CMS_OPERATION_NOT_ALLOWED;    /* ???????????? */
    }

    /* ???????????? */
    pstAckParm = At_GetAckMsgMem();

    /*gastAtClientTab[ucIndex].AtSmsData.ucNumType??0????????????????????????????????????????????*/
    if (gastAtClientTab[ucIndex].AtSmsData.ucCnmaType == 1)
    {
        pstAckParm->bRpAck = TAF_TRUE;
        pstAckParm->stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ACK;
    }
    else
    {
        pstAckParm->bRpAck = TAF_FALSE;
        pstAckParm->enRpCause = MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED;
        pstAckParm->stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ERR;
    }

    /*gastAtClientTab[ucIndex].AtSmsData.ucPduLen??0????????????????????????????????????????????*/
    pstAckParm->stTsRawData.ulLen = (TAF_UINT32)gastAtClientTab[ucIndex].AtSmsData.ucPduLen;
    lMemResult = memcpy_s(pstAckParm->stTsRawData.aucData, sizeof(pstAckParm->stTsRawData.aucData), pData, ulLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstAckParm->stTsRawData.aucData), ulLen);
    pstTsDataInfo = At_GetMsgMem();
    ulRet = MN_MSG_Decode(&pstAckParm->stTsRawData, pstTsDataInfo);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: Fail to decode.");
        return AT_ERROR;
    }

    if ((pstAckParm->bRpAck == TAF_FALSE)
     && (pstTsDataInfo->u.stDeliverRptErr.enFailCause == MN_MSG_TP_CAUSE_MEMORY_FULL))
    {
        pstAckParm->enRpCause = MN_MSG_RP_CAUSE_MEMORY_EXCEEDED;
    }

    gastAtClientTab[ucIndex].opId = opId;
    if (MN_MSG_SendAck(gastAtClientTab[ucIndex].usClientId, opId, pstAckParm) == MN_ERR_NO_ERROR)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNMA_PDU_SET;
        gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = 1;
        ulRet = AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        ulRet = AT_ERROR;
    }
    return ulRet;
}



VOS_UINT32  At_WritePduMsgToMem(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
)
{
    errno_t                             lMemResult;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    TAF_UINT32                          ulAddrLen           = 0;
    TAF_UINT32                          ulRet;
    MN_MSG_WRITE_PARM_STRU              *pstWriteParm = VOS_NULL_PTR;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo = VOS_NULL_PTR;
    MN_MSG_TPDU_TYPE_ENUM_U8            aucMtiMapTpduType[4] = {MN_MSG_TPDU_DELIVER,
                                                                MN_MSG_TPDU_SUBMIT,
                                                                MN_MSG_TPDU_COMMAND,
                                                                MN_MSG_TPDU_MAX};
    TAF_UINT8                           ucFo;
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_CMGW_PDU_SET)
    {
        AT_WARN_LOG("At_WritePduMsgToMem: invalid command operation.");
        return AT_ERROR;
    }

    if (gastAtClientTab[ucIndex].AtSmsData.ucPduLen > ulLen)
    {
        AT_NORM_LOG("At_WritePduMsgToMem: invalid tpdu data length.");
        return AT_ERROR;
    }

    pstWriteParm = At_GetWriteMsgMem();

    pstWriteParm->enWriteMode = MN_MSG_WRITE_MODE_INSERT;
    pstWriteParm->enMemStore = pstSmsCtx->stCpmsInfo.enMemSendorWrite;
    pstWriteParm->enStatus = gastAtClientTab[ucIndex].AtSmsData.SmState;

    /*sca*/
    if (ulLen > gastAtClientTab[ucIndex].AtSmsData.ucPduLen)
    {
        ulRet = At_GetScaFromInputStr(pData, &pstWriteParm->stMsgInfo.stScAddr, &ulAddrLen);
        if (ulRet != MN_ERR_NO_ERROR)
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: fail to get sca from user input.");
            return AT_ERROR;
        }

        if (ulLen != (gastAtClientTab[ucIndex].AtSmsData.ucPduLen + ulAddrLen))
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: the length of <pdu> is not consistent with <length>.");
            return AT_ERROR;
        }

    }

    if (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen == 0)
    {
        if (pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen == 0)
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: without sca.");
        }
        else
        {
            lMemResult = memcpy_s(&pstWriteParm->stMsgInfo.stScAddr,
                                  sizeof(pstWriteParm->stMsgInfo.stScAddr),
                                  &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
                                  sizeof(pstWriteParm->stMsgInfo.stScAddr));
            TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstWriteParm->stMsgInfo.stScAddr), sizeof(pstWriteParm->stMsgInfo.stScAddr));
        }
    }

    pstWriteParm->stMsgInfo.stTsRawData.ulLen = gastAtClientTab[ucIndex].AtSmsData.ucPduLen;
    lMemResult = memcpy_s(pstWriteParm->stMsgInfo.stTsRawData.aucData,
                          sizeof(pstWriteParm->stMsgInfo.stTsRawData.aucData),
                          &pData[ulAddrLen],
                          gastAtClientTab[ucIndex].AtSmsData.ucPduLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstWriteParm->stMsgInfo.stTsRawData.aucData), gastAtClientTab[ucIndex].AtSmsData.ucPduLen);

    ucFo = pstWriteParm->stMsgInfo.stTsRawData.aucData[0];
    pstWriteParm->stMsgInfo.stTsRawData.enTpduType = aucMtiMapTpduType[(ucFo & 0x03)];;

    /*????PDU??????????????????????????*/
    pstTsDataInfo = At_GetMsgMem();
    ulRet = MN_MSG_Decode(&pstWriteParm->stMsgInfo.stTsRawData, pstTsDataInfo);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        AT_NORM_LOG("At_WritePduMsgToMem: Fail to decode.");
        return AT_ERROR;
    }

    pstRawData = At_GetLongMsgSegMem();
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstRawData);
    if(ulRet != MN_ERR_NO_ERROR)
    {
        AT_NORM_LOG("At_WritePduMsgToMem: fail to encode.");
    }
    else
    {
        if (pstRawData->ulLen != pstWriteParm->stMsgInfo.stTsRawData.ulLen)
        {
            AT_NORM_LOG1("At_WritePduMsgToMem: pstSendParm->stMsgInfo.stTsRawData.ulLen not match:",
                         pstWriteParm->stMsgInfo.stTsRawData.ulLen);
            AT_NORM_LOG1("At_WritePduMsgToMem: pstRawData->ulLen not match:", pstRawData->ulLen);
            pstWriteParm->stMsgInfo.stTsRawData.ulLen = pstRawData->ulLen;
        }

    }

    gastAtClientTab[ucIndex].opId = opId;
    ulRet = MN_MSG_Write(gastAtClientTab[ucIndex].usClientId, opId, pstWriteParm);
    if (ulRet == MN_ERR_NO_ERROR)
    {
        ulRet = AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    return ulRet;
}


VOS_UINT32 AT_ConvertCharToHex(
    VOS_UINT8                           ucChar,
    VOS_UINT8                          *pucHexValue
)
{
    if( (ucChar >= '0') && (ucChar <= '9') )
    {
        *pucHexValue = ucChar - '0';
    }
    else if( (ucChar >= 'a') && (ucChar <= 'f') )
    {
        *pucHexValue = (ucChar - 'a') + 10;
    }
    else if( (ucChar >= 'A') && (ucChar <= 'F') )
    {
        *pucHexValue = (ucChar - 'A') + 10;
    }
    else
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}


VOS_VOID AT_GetInvalidCharLengthForSms(
    VOS_UINT8                          *pucPdu,
    VOS_UINT32                          ulLen,
    VOS_UINT32                         *pulInvalidCharLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulInvalidCharLength;
    VOS_UINT8                           ucHex;

    ulInvalidCharLength = 0;
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        ulRet = AT_ConvertCharToHex(pucPdu[ulLoop], &ucHex);
        if (ulRet != AT_FAILURE)
        {
            break;
        }

        ulInvalidCharLength++;
    }

    *pulInvalidCharLength = ulInvalidCharLength;

    return;
}


VOS_UINT32 AT_ProcAbnormalPdu(
    VOS_UINT8                          *pucPdu,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulInvalidCharLength;

    if (pucPdu[ulLen] == AT_ESC)
    {
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }

    /* ????At_SmsPduProc????????????????????????,CTRL+Z??ESC??????????
       At_SmsPduProc????????????CASE??????CTRL+Z,????????????????????ESC????
       ?????????????????????????????????????? */
    AT_GetInvalidCharLengthForSms(pucPdu, ulLen, &ulInvalidCharLength);
    if (ulInvalidCharLength == ulLen)
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }
}


TAF_UINT32 At_SmsPduProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    VOS_UINT32                          ulInvalidCharLength;
    TAF_UINT16                          usTmpLen            = usLen;
    TAF_UINT32                          ulRet;

    usTmpLen -= 1;              /* ???????????????? */
    switch (pData[usTmpLen])    /* ?????????????????????????????? */
    {
    case AT_CTRL_Z:
        /* ??????????????????????,????/??/PDU[????/????] */
        AT_GetInvalidCharLengthForSms(pData, usTmpLen, &ulInvalidCharLength);
        pData    += ulInvalidCharLength;
        usTmpLen -= (VOS_UINT16)ulInvalidCharLength;

        if(At_UnicodePrint2Unicode(pData,&usTmpLen) == AT_FAILURE)
        {
            return AT_CMS_INVALID_PDU_MODE_PARAMETER;
        }

        switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
        case AT_CMD_CMGS_PDU_SET:
        case AT_CMD_CMGC_PDU_SET:
            ulRet = At_SendPduMsgOrCmd(ucIndex, pData, usTmpLen);
            break;

        case AT_CMD_CMGW_PDU_SET:
            ulRet = At_WritePduMsgToMem(ucIndex, pData, usTmpLen);
            break;

        case AT_CMD_CNMA_PDU_SET:
            ulRet = At_SendPduMsgAck(ucIndex, pData, usTmpLen);
            break;

        default:
            ulRet = AT_ERROR;                                                   /*  ????????*/
        }
        break;
    default:
        ulRet = AT_ProcAbnormalPdu(pData, usTmpLen);                            /*  ????????*/
        break;
    }

    return ulRet;
}


VOS_UINT32 At_EncodeTextMsgTpUd(
    VOS_UINT8                           ucIndex,
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    MN_MSG_USER_DATA_STRU              *pstUserData
)
{
    VOS_UINT32                          ulRet;
    errno_t                             lMemResult;

    if (gastAtClientTab[ucIndex].usSmsTxtLen > MN_MSG_MAX_LEN)
    {
        AT_NORM_LOG("At_EncodeTextMsgTpUd: invalid text message length.");
        return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
    }

    if ((gucAtCscsType == AT_CSCS_IRA_CODE)
     && (enMsgCoding == MN_MSG_MSG_CODING_7_BIT))
    {
        ulRet = TAF_STD_ConvertAsciiToDefAlpha(gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                                               gastAtClientTab[ucIndex].usSmsTxtLen,
                                               pstUserData->aucOrgData,
                                               &pstUserData->ulLen,
                                               MN_MSG_MAX_LEN);
        if (ulRet == MN_ERR_INVALIDPARM)
        {
            AT_NORM_LOG("At_EncodeTextMsgTpUd: TAF_STD_ConvertAsciiToDefAlpha fail.");
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }

    }
    else if ((AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
          && (enMsgCoding == MN_MSG_MSG_CODING_8_BIT))
    {
        TAF_STD_ConvertDefAlphaToAscii(gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                                       gastAtClientTab[ucIndex].usSmsTxtLen,
                                       pstUserData->aucOrgData,
                                       &pstUserData->ulLen);
        return AT_SUCCESS;
    }
    else
    {
        pstUserData->ulLen = gastAtClientTab[ucIndex].usSmsTxtLen;
        lMemResult = memcpy_s(pstUserData->aucOrgData,
                              MN_MSG_MAX_LEN,
                              gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                              pstUserData->ulLen);
        TAF_MEM_CHK_RTN_VAL(lMemResult, MN_MSG_MAX_LEN, pstUserData->ulLen);
    }

    return AT_SUCCESS;
}


TAF_UINT32  At_SendTextMsgOrCmd(
    TAF_UINT8                           ucIndex
)
{
    errno_t                             lMemResult;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo = VOS_NULL_PTR;
    TAF_UINT32                          ulRet;
    MN_MSG_SEND_PARM_STRU               *pstSendDirectParm = VOS_NULL_PTR;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    AT_MODEM_SMS_CTX_STRU               *pstSmsCtx = VOS_NULL_PTR;

    if ((gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_CMGS_TEXT_SET)
     && (gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_CMGC_TEXT_SET))
    {
        AT_WARN_LOG("At_SendTextMsgOrCmd: invalid command operation.");
        return AT_ERROR;
    }

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstTsDataInfo = At_GetMsgMem();
    pstSendDirectParm = At_GetDirectSendMsgMem();
    pstSendDirectParm->enMemStore   = MN_MSG_MEM_STORE_NONE;
    pstSendDirectParm->enClientType = MN_MSG_CLIENT_NORMAL;

    /*sc*/
    if (pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen == 0)
    {
        AT_NORM_LOG("At_SendTextMsgOrCmd: no SCA.");
        return AT_CMS_SMSC_ADDRESS_UNKNOWN;
    }
    lMemResult = memcpy_s(&pstSendDirectParm->stMsgInfo.stScAddr,
                          sizeof(pstSendDirectParm->stMsgInfo.stScAddr),
                          &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
                          sizeof(pstSendDirectParm->stMsgInfo.stScAddr));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstSendDirectParm->stMsgInfo.stScAddr), sizeof(pstSendDirectParm->stMsgInfo.stScAddr));

    if (gastAtClientTab[ucIndex].CmdCurrentOpt == AT_CMD_CMGS_TEXT_SET)
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_SUBMIT;

        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);

        /*Mr??0,??MN????*/

        /*Da*/
        lMemResult = memcpy_s(&pstTsDataInfo->u.stSubmit.stDestAddr,
                              sizeof(pstTsDataInfo->u.stSubmit.stDestAddr),
                              &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                              sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstTsDataInfo->u.stSubmit.stDestAddr), sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));

        /*PID*/
        pstTsDataInfo->u.stSubmit.enPid = pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid;

        /*DCS*/
        ulRet = MN_MSG_DecodeDcs(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs,
                                 &pstTsDataInfo->u.stSubmit.stDcs);
        if (ulRet != MN_ERR_NO_ERROR)
        {
            AT_NORM_LOG("At_SendTextMsgOrCmd: Fail to decode DCS.");
            return AT_ERROR;
        }

        /*VP*/
        lMemResult = memcpy_s(&pstTsDataInfo->u.stSubmit.stValidPeriod,
                              sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod),
                              &(pstSmsCtx->stCscaCsmpInfo.stVp),
                              sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod), sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod));

        /*UDL UD*/
        ulRet = At_EncodeTextMsgTpUd(ucIndex,
                                     pstTsDataInfo->u.stSubmit.stDcs.enMsgCoding,
                                     &pstTsDataInfo->u.stSubmit.stUserData);
        if (ulRet != AT_SUCCESS)
        {
            AT_WARN_LOG("At_WriteTextMsgToMem: Fail to get User Data.");
            return ulRet;
        }
    }
    else
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_COMMAND;
        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);
        /*Mr??0,??MN????*/
        /*PID*/
        /*PID*/
        pstTsDataInfo->u.stCommand.enPid = gastAtClientTab[ucIndex].AtSmsData.enPid;

        /*TP-CT*/
        pstTsDataInfo->u.stCommand.enCmdType = gastAtClientTab[ucIndex].AtSmsData.CommandType;
        /*TP-MN*/ /* ??????????????????????TAF_SMS_CMD_MSG_NUM_ABSOLUTE,?????? */
        pstTsDataInfo->u.stCommand.ucMsgNumber = gastAtClientTab[ucIndex].AtSmsData.ucMessageNumber;

        /*Da*/
        lMemResult = memcpy_s(&pstTsDataInfo->u.stCommand.stDestAddr,
                              sizeof(pstTsDataInfo->u.stCommand.stDestAddr),
                              &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                              sizeof(pstTsDataInfo->u.stCommand.stDestAddr));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstTsDataInfo->u.stCommand.stDestAddr), sizeof(pstTsDataInfo->u.stCommand.stDestAddr));
        /*CDL CD*/
        if (gastAtClientTab[ucIndex].usSmsTxtLen > MN_MSG_MAX_COMMAND_DATA_LEN)
        {
            AT_NORM_LOG("At_SendTextMsgOrCmd: invalid text command length.");
            return AT_ERROR;
        }

        /*??????????gastAtClientTab[ucIndex].usSmsTxtLen??????????????????????????????????*/
        pstTsDataInfo->u.stCommand.ucCommandDataLen = (TAF_UINT8)gastAtClientTab[ucIndex].usSmsTxtLen;
        lMemResult = memcpy_s(pstTsDataInfo->u.stCommand.aucCmdData,
                              MN_MSG_MAX_COMMAND_DATA_LEN,
                              gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                              gastAtClientTab[ucIndex].usSmsTxtLen);
        TAF_MEM_CHK_RTN_VAL(lMemResult, MN_MSG_MAX_COMMAND_DATA_LEN, gastAtClientTab[ucIndex].usSmsTxtLen);
    }

    ulRet = MN_MSG_Encode(pstTsDataInfo, &pstSendDirectParm->stMsgInfo.stTsRawData);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        AT_WARN_LOG("At_SendTextMsgOrCmd: Fail to encode sms message or command.");
        return At_ChgMnErrCodeToAt(ucIndex, ulRet);
    }

    gastAtClientTab[ucIndex].opId = opId;
    ulRet = MN_MSG_Send(gastAtClientTab[ucIndex].usClientId,
                              gastAtClientTab[ucIndex].opId,
                              pstSendDirectParm);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        AT_ERR_LOG("At_SendTextMsgOrCmd: Fail to send sms message or command.");
        if (ulRet == MN_ERR_CLASS_SMS_NOAVAILDOMAIN)
        {
            ulRet = AT_CMS_UNKNOWN_ERROR;
        }
        else
        {
            ulRet = AT_ERROR;
        }
    }
    else
    {
        ulRet = AT_WAIT_ASYNC_RETURN;
        gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = 1;
    }
    return ulRet;
}


TAF_UINT32  At_WriteTextMsgToMem(
    TAF_UINT8                           ucIndex
)
{
    errno_t                             lMemResult;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo = VOS_NULL_PTR;
    TAF_UINT32                          ulRet;
    MN_MSG_WRITE_PARM_STRU              *pstWriteParm = VOS_NULL_PTR;
    MN_MSG_DCS_CODE_STRU                *pstDcs = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_CMGW_TEXT_SET)
    {
        AT_WARN_LOG("At_WriteTextMsgToMem: invalid command operation.");
        return AT_ERROR;
    }

    pstTsDataInfo = At_GetMsgMem();
    pstWriteParm = At_GetWriteMsgMem();
    pstWriteParm->enWriteMode = MN_MSG_WRITE_MODE_INSERT;
    pstWriteParm->enMemStore = pstSmsCtx->stCpmsInfo.enMemSendorWrite;
    pstWriteParm->enStatus = gastAtClientTab[ucIndex].AtSmsData.SmState;

    if (pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen == 0)
    {
        AT_NORM_LOG("At_WriteTextMsgToMem: no SCA.");
        return AT_ERROR;
    }
    lMemResult = memcpy_s(&pstWriteParm->stMsgInfo.stScAddr,
                          sizeof(pstWriteParm->stMsgInfo.stScAddr),
                          &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
                          sizeof(pstWriteParm->stMsgInfo.stScAddr));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstWriteParm->stMsgInfo.stScAddr), sizeof(pstWriteParm->stMsgInfo.stScAddr));

    if ((gastAtClientTab[ucIndex].AtSmsData.SmState == MN_MSG_STATUS_MO_NOT_SENT)
     || (gastAtClientTab[ucIndex].AtSmsData.SmState == MN_MSG_STATUS_MO_SENT))
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_SUBMIT;

        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);

        /*Mr??0,??MN????*/
        pstTsDataInfo->u.stSubmit.ucMr = 0xff;

        /*Da*/
        lMemResult = memcpy_s(&pstTsDataInfo->u.stSubmit.stDestAddr,
                              sizeof(pstTsDataInfo->u.stSubmit.stDestAddr),
                              &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                              sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstTsDataInfo->u.stSubmit.stDestAddr), sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));

        /*PID*/
        pstTsDataInfo->u.stSubmit.enPid = pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid;

        /*DCS*/
        pstDcs = &pstTsDataInfo->u.stSubmit.stDcs;
        ulRet = MN_MSG_DecodeDcs(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs, pstDcs);
        if (ulRet != MN_ERR_NO_ERROR)
        {
            AT_NORM_LOG("At_WriteTextMsgToMem: Fail to decode DCS.");
            return AT_ERROR;
        }

        /*VP*/
        lMemResult = memcpy_s(&pstTsDataInfo->u.stSubmit.stValidPeriod,
                              sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod),
                              &(pstSmsCtx->stCscaCsmpInfo.stVp),
                              sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod), sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod));

        /*UDL UD*/
        ulRet = At_EncodeTextMsgTpUd(ucIndex,
                                     pstTsDataInfo->u.stSubmit.stDcs.enMsgCoding,
                                     &pstTsDataInfo->u.stSubmit.stUserData);
        if (ulRet != AT_SUCCESS)
        {
            AT_WARN_LOG("At_WriteTextMsgToMem: Fail to get User Data.");
            return ulRet;
        }

    }
    else
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_DELIVER;

        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);

        /*Mr??0,??MN????*/

        /*Da*/
        lMemResult = memcpy_s(&pstTsDataInfo->u.stDeliver.stOrigAddr,
                              sizeof(pstTsDataInfo->u.stSubmit.stDestAddr),
                              &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                              sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstTsDataInfo->u.stSubmit.stDestAddr), sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));

        /*PID*/
        pstTsDataInfo->u.stDeliver.enPid = pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid;

        /*DCS*/
        pstDcs = &pstTsDataInfo->u.stDeliver.stDcs;
        ulRet = MN_MSG_DecodeDcs(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs, pstDcs);
        if (ulRet != MN_ERR_NO_ERROR)
        {
            AT_NORM_LOG("At_WriteTextMsgToMem: Fail to decode DCS.");
            return AT_ERROR;
        }

        /*SCTS??*/

        /*UDL UD*/
        ulRet = At_EncodeTextMsgTpUd(ucIndex,
                                     pstTsDataInfo->u.stDeliver.stDcs.enMsgCoding,
                                     &pstTsDataInfo->u.stDeliver.stUserData);

        if (ulRet != AT_SUCCESS)
        {
            AT_WARN_LOG("At_WriteTextMsgToMem: Fail to get User Data.");
            return ulRet;
        }

    }

    ulRet = MN_MSG_Encode(pstTsDataInfo, &pstWriteParm->stMsgInfo.stTsRawData);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        AT_WARN_LOG("At_WriteTextMsgToMem: Fail to encode sms message or command.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_Write(gastAtClientTab[ucIndex].usClientId,
                         gastAtClientTab[ucIndex].opId,
                         pstWriteParm);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        ulRet = AT_ERROR;
    }
    else
    {
        ulRet = AT_WAIT_ASYNC_RETURN;
    }
    return ulRet;
}


TAF_UINT32 At_SmsTextProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    TAF_UINT16                          usTmpLen            = usLen;
    TAF_UINT8                           ucSmsProcType       = 0;
    TAF_UINT32                          ulRet;
    errno_t                             lMemResult;

    if (gucAtCscsType != AT_CSCS_IRA_CODE)
    {
        usTmpLen -= 1;
        if(pData[usTmpLen] == AT_CTRL_Z)
        {
            ucSmsProcType = 1;
        }
        else if(ucAtS3 == pData[usTmpLen])
        {
            ucSmsProcType = 2;
        }
        else
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }
        if(At_UnicodePrint2Unicode(pData,&usTmpLen) == AT_FAILURE)
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }

        /* UNICODE ???????? */
        if ((gastAtClientTab[ucIndex].usSmsTxtLen + usTmpLen) > AT_UNICODE_SMS_MAX_LENGTH)
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }
    }
    else
    {
        if(pData[usTmpLen - 1] == AT_CTRL_Z)
        {
            usTmpLen -= 1;
            ucSmsProcType = 1;
        }
        else if(ucAtS3 == pData[usTmpLen - 1])
        {
            ucSmsProcType = 2;
        }
        else
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }

        /* ASCII ???????? */
        if ((gastAtClientTab[ucIndex].usSmsTxtLen + usTmpLen) > AT_ASCII_SMS_MAX_LENGTH)
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }
    }

    switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
    case AT_CMD_CMGS_TEXT_SET:
    case AT_CMD_CMGW_TEXT_SET:
    case AT_CMD_CMGC_TEXT_SET:
        lMemResult = memcpy_s(&gastAtClientTab[ucIndex].AtSmsData.aucBuffer[gastAtClientTab[ucIndex].usSmsTxtLen],
                              AT_SMS_SEG_MAX_LENGTH - gastAtClientTab[ucIndex].usSmsTxtLen,
                              pData,
                              usTmpLen);
        TAF_MEM_CHK_RTN_VAL(lMemResult, AT_SMS_SEG_MAX_LENGTH - gastAtClientTab[ucIndex].usSmsTxtLen, usTmpLen);
        break;

    default:
        return AT_ERROR;
    }
    gastAtClientTab[ucIndex].usSmsTxtLen += usTmpLen;
    if (ucSmsProcType == 1)
    {
        switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
        case AT_CMD_CMGS_TEXT_SET:
        case AT_CMD_CMGC_TEXT_SET:
            ulRet = At_SendTextMsgOrCmd(ucIndex);
            break;
        default:
            ulRet = At_WriteTextMsgToMem(ucIndex);
            break;
        }

    }
    else
    {
        /* ??????????????,???????????????? */
        ulRet = AT_WAIT_SMS_INPUT;
    }
    return ulRet;
}

TAF_UINT32 At_SmsProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ???????????????? */
    if (pstSmsCtx->enCmgfMsgFormat == AT_CMGF_MSG_FORMAT_TEXT)                  /* TEXT */
    {
        return At_SmsTextProc(ucIndex,pData,usLen);
    }
    else
    {
        /* ????????????????????AT_ERROR */
        return At_SmsPduProc(ucIndex,pData,usLen);                              /* PDU */
    }
}



VOS_UINT32 At_ParseSimLockPara(
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist,
    VOS_UINT32                          ulParaCnt
)
{
    VOS_UINT8                           *pucParaStart = VOS_NULL_PTR;
    VOS_UINT32                          ulParaIdx;
    VOS_UINT32                          ulChkRslt;
    VOS_UINT32                          i;

    if (pstParalist == VOS_NULL_PTR)
    {
        AT_ERR_LOG("At_PareseSimLockPara: pstParalist = VOS_NULL_PTR!");
        return AT_FAILURE;
    }

    pucParaStart  = pucData;
    ulParaIdx     = 0;

    /* ??AT^simlock=pucData??pucData????????  */
    for ( i = 0; i < usLen ; i++ )
    {
        if (pucData[i] == ',')
        {
            /* ?????????????? */
            ulChkRslt = At_CheckAndParsePara((pstParalist + ulParaIdx),
                                                   pucParaStart, (pucData + i));
            if (ulChkRslt != AT_OK)
            {
                return AT_FAILURE;
            }

            pucParaStart = (pucData + i) + 1;
            ++ ulParaIdx;

            if (ulParaIdx >= ulParaCnt)
            {
                return AT_FAILURE;
            }
        }

    }

    /*  ??????????????????copy???????????? */
    ulChkRslt = At_CheckAndParsePara((pstParalist + ulParaIdx),
                                           pucParaStart, (pucData + usLen));
    if (ulChkRslt != AT_OK)
    {
        return AT_FAILURE;
    }

    ++ ulParaIdx;

    if (ulParaIdx > ulParaCnt)
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;

}

VOS_UINT32 At_DispatchSimlockCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist
)
{
    VOS_UINT8                           ucSimLockOP;

    if ((ulParaCnt < 1) || (pstParalist == VOS_NULL_PTR))
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_FAILURE;
    }

    if ((pstParalist[0].usParaLen != 1)
     || (pstParalist[0].aucPara[0] <'0')
     || (pstParalist[0].aucPara[0] > '2'))
    {
        /*????????*/
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_FAILURE;
    }

    ucSimLockOP = pstParalist[0].aucPara[0] - '0';

    if (ucSimLockOP == AT_SIMLOCK_OPRT_UNLOCK)
    {
        At_UnlockSimLock(ucIndex, ulParaCnt,pstParalist);
    }
    else if (ucSimLockOP == AT_SIMLOCK_OPRT_SET_PLMN_INFO)
    {
        At_SetSimLockPlmnInfo(ucIndex, ulParaCnt,pstParalist);
    }
    else
    {
        AT_GetSimLockStatus(ucIndex);
    }
    return AT_SUCCESS;
}



VOS_UINT32 At_ProcSimLockPara(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_INT8                            cRet;
    VOS_UINT16                          usCmdLen;
    VOS_UINT8                           *pucDataPara = TAF_NULL_PTR;
    VOS_UINT32                          ulParaCnt;
    AT_PARSE_PARA_TYPE_STRU             *pstParalist = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    errno_t                             lMemResult;

    if (usLen == 0)
    {
        return AT_FAILURE;
    }
    /*lint -save -e516 */
    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
    /*lint -restore */
    if (pucDataPara == VOS_NULL_PTR)
    {
        AT_ERR_LOG("At_ProcSimLockPara: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    lMemResult = memcpy_s(pucDataPara, usLen, pucData, usLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, usLen, usLen);


    /* ??????????????????????????"AT^SIMLOCK"????????????AT_FAILURE */
    usCmdLen =(VOS_UINT16)VOS_StrLen("AT^SIMLOCK=");

    if (usLen <= usCmdLen)
    {
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        return AT_FAILURE;
    }

    /* ??????????????????????"AT^SIMLOCK"????????AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^SIMLOCK=", usCmdLen);

    if (cRet != 0)
    {
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        return AT_FAILURE;
    }


    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^SIMLOCK", AT_EXTEND_CMD_TYPE);

    /* ???????????? */
    ulParaCnt = At_GetParaCnt(pucDataPara, usLen);

    if (ulParaCnt < 1)
    {
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_SUCCESS;
    }

    /* ??????????????61?????????? */
    if (ulParaCnt > 61)
    {
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        At_FormatResultData(ucIndex, AT_SIMLOCK_PLMN_NUM_ERR);
        return AT_SUCCESS;
    }

    pstParalist = (AT_PARSE_PARA_TYPE_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT,
                                (ulParaCnt * sizeof(AT_PARSE_PARA_TYPE_STRU)));

    if (pstParalist == VOS_NULL_PTR)
    {
        AT_ERR_LOG("At_ProcSimLockPara: pstParalist Memory malloc failed!");
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_SUCCESS;
    }
    else
    {
        memset_s(pstParalist, ulParaCnt * sizeof(AT_PARSE_PARA_TYPE_STRU), 0x00, (VOS_SIZE_T)(ulParaCnt * sizeof(AT_PARSE_PARA_TYPE_STRU)));
    }

    /* ?? At^simlock???????????? At???????????????? */
    ulRslt = At_ParseSimLockPara((pucDataPara + usCmdLen), (usLen - usCmdLen),
                                                    pstParalist, ulParaCnt);

    if (ulRslt == AT_SUCCESS)
    {
        /* ????at^simlock=oprt,paralist????oprt???? Simlock?????????? */
        At_DispatchSimlockCmd(ucIndex, ulParaCnt, pstParalist);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    /*lint -save -e516 */
    PS_MEM_FREE(WUEPS_PID_AT,pstParalist);
    PS_MEM_FREE(WUEPS_PID_AT,pucDataPara);
    /*lint -restore */

    return AT_SUCCESS;

}


VOS_UINT32 AT_HandleFacAuthPubKeyExCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    AT_AUTH_PUBKEYEX_CMD_PROC_CTX      *pstAuthPubKeyCtx = VOS_NULL_PTR;
    VOS_UINT8                          *pucDataPara = VOS_NULL_PTR;
    AT_PARSE_CMD_NAME_TYPE_STRU         stAtCmdName;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFirstParaVal;
    VOS_UINT32                          ulSecParaVal;
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulTempIndex;
    errno_t                             lMemResult;
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    VOS_UINT16                          usSecCommaPos;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT16                          usThirdParaLen;
    VOS_INT8                            cRet;

    ulTempIndex  = (VOS_UINT32)ucIndex;
    ulTimerName  = AT_AUTH_PUBKEY_TIMER;
    ulTimerName |= AT_INTERNAL_PROCESS_TYPE;
    ulTimerName |= (ulTempIndex<<12);

    pstAuthPubKeyCtx = AT_GetAuthPubkeyExCmdCtxAddr();

    memset_s(&stAtCmdName, sizeof(stAtCmdName), 0x00, sizeof(stAtCmdName));

    /* ?????????????? */
    usPos               = 0;
    pucDataPara         = VOS_NULL_PTR;
    usLoop              = 0;
    usCommaCnt          = 0;
    usFirstCommaPos     = 0;
    usSecCommaPos       = 0;
    usFirstParaLen      = 0;
    usSecondParaLen     = 0;
    ulFirstParaVal      = 0;
    ulSecParaVal        = 0;
    usCmdlen            = (VOS_UINT16)VOS_StrLen("AT^FACAUTHPUBKEYEX=");

    if (usLen < usCmdlen)
    {
        return AT_FAILURE;
    }

    /*lint -save -e516 */
    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usCmdlen);
    /*lint -restore */
    if (pucDataPara == VOS_NULL_PTR)
    {
        AT_ERR_LOG("AT_HandleFacAuthPubKeyExCmd: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    /*??????????????????????????*/
    lMemResult = memcpy_s(pucDataPara, usCmdlen, pucData, usCmdlen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, usCmdlen, usCmdlen);

    /* AT???????????????? */
    At_UpString(pucDataPara, usCmdlen);

    /* ??????????????????????"AT^FACAUTHPUBKEYEX="????????AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^FACAUTHPUBKEYEX=", usCmdlen);
    if (cRet != 0)
    {
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        return AT_FAILURE;
    }

    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^FACAUTHPUBKEYEX", AT_EXTEND_CMD_TYPE);

    /* ????????(??????????????AT)?????????? */
    usPos = (VOS_UINT16)VOS_StrLen("AT");

    stAtCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^FACAUTHPUBKEYEX");
    lMemResult = memcpy_s(stAtCmdName.aucCmdName,
                          sizeof(stAtCmdName.aucCmdName),
                          (pucData + usPos),
                          stAtCmdName.usCmdNameLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(stAtCmdName.aucCmdName), stAtCmdName.usCmdNameLen);
    stAtCmdName.aucCmdName[stAtCmdName.usCmdNameLen] = '\0';
    usPos += stAtCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ?????????????????????????? */
    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (*(pucData + usLoop) == ',')
        {
            usCommaCnt++;

            /* ?????????????????????? */
            if (usFirstCommaPos == 0)
            {
                usFirstCommaPos = usLoop + 1;
            }
            else
            {
                if (usSecCommaPos == 0)
                {
                    usSecCommaPos = usLoop + 1;
                }
            }
        }
    }

    /* ??????????????2????AT???????????????? */
    if (usCommaCnt != 2)
    {
        AT_WARN_LOG("AT_HandleFacAuthPubKeyExCmd: usCommaCnt != 2!");
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);
        AT_ClearAuthPubkeyCtx();
        (VOS_VOID)AT_StopRelTimer(ulTimerName, &(pstAuthPubKeyCtx->hAuthPubkeyProtectTimer));
        return AT_SUCCESS;
    }

    /* ?????????????? */
    usFirstParaLen  = (usFirstCommaPos - usPos) - (VOS_UINT16)VOS_StrLen(",");
    usSecondParaLen = usSecCommaPos - usFirstCommaPos - (VOS_UINT16)VOS_StrLen(",");
    usThirdParaLen  = usLen - usSecCommaPos;

    /* ???????????????? */
    if (atAuc2ul(pucData + usPos, usFirstParaLen, &ulFirstParaVal) == AT_FAILURE)
    {
        AT_WARN_LOG("AT_HandleFacAuthPubKeyExCmd: ulFirstParaVal value invalid");
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);
        AT_ClearAuthPubkeyCtx();
        (VOS_VOID)AT_StopRelTimer(ulTimerName, &(pstAuthPubKeyCtx->hAuthPubkeyProtectTimer));
        return AT_SUCCESS;
    }

    /* ???????????????? */
    if (atAuc2ul(pucData + usFirstCommaPos, usSecondParaLen, &ulSecParaVal) == AT_FAILURE)
    {
        AT_WARN_LOG("AT_HandleFacAuthPubKeyExCmd: ulSecParaVal value invalid");
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);
        AT_ClearAuthPubkeyCtx();
        (VOS_VOID)AT_StopRelTimer(ulTimerName, &(pstAuthPubKeyCtx->hAuthPubkeyProtectTimer));
        return AT_SUCCESS;
    }

    /* ???????????????????????????????? */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType = AT_EXTEND_CMD_TYPE;

    AT_PR_LOGI("enter");

    ulResult = AT_SetFacAuthPubkeyExPara(ucIndex, ulFirstParaVal, ulSecParaVal, usThirdParaLen, (pucData + usSecCommaPos));
    if (ulResult != AT_WAIT_ASYNC_RETURN)
    {
        AT_PR_LOGI(KERN_ERR "return OK");

        At_FormatResultData(ucIndex, ulResult);
    }

    /*lint -save -e516 */
    PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
    /*lint -restore */
    return AT_SUCCESS;
}


VOS_UINT32 AT_HandleSimLockDataWriteCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    errno_t                             lMemResult;
    VOS_INT8                            cRet;
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT8                          *pucDataPara = VOS_NULL_PTR;
    AT_SIMLOCKDATAWRITE_SET_REQ_STRU   *pstSimlockDataWrite = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    AT_PARSE_CMD_NAME_TYPE_STRU         stAtCmdName;

    memset_s(&stAtCmdName, sizeof(stAtCmdName), 0x00, sizeof(stAtCmdName));

    /* ?????????????? */
    pucDataPara         = VOS_NULL_PTR;
    pstSimlockDataWrite = VOS_NULL_PTR;

    /* ??????AT????????????????????????????????????AT^SIMLOCKDATAWRITE???????????????????????????????? */
    if ((VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN) != usLen)
    {
        return AT_FAILURE;
    }

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^SIMLOCKDATAWRITE=");
    /*lint -save -e516 */
    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usCmdlen);
    /*lint -restore */
    if (pucDataPara == VOS_NULL_PTR)
    {
        AT_ERR_LOG("AT_HandleSimLockDataWriteCmd: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    /*??????????????????????????*/
    lMemResult = memcpy_s(pucDataPara, usCmdlen, pucData, usCmdlen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, usCmdlen, usCmdlen);

    /* AT???????????????? */
    At_UpString(pucDataPara, usCmdlen);

    /* ??????????????????????"AT^SIMLOCKDATAWRITE="????????AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^SIMLOCKDATAWRITE=", usCmdlen);
    if (cRet != 0)
    {
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        return AT_FAILURE;
    }


    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^SIMLOCKDATAWRITE", AT_EXTEND_CMD_TYPE);

    /* ????????(??????????????AT)?????????? */
    usPos = (VOS_UINT16)VOS_StrLen("AT");
    stAtCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^SIMLOCKDATAWRITE");
    lMemResult = memcpy_s(stAtCmdName.aucCmdName,
                          AT_CMD_NAME_LEN + 1,
                          (pucData + usPos),
                          stAtCmdName.usCmdNameLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, AT_CMD_NAME_LEN + 1, stAtCmdName.usCmdNameLen);
    stAtCmdName.aucCmdName[stAtCmdName.usCmdNameLen] = '\0';
    usPos += stAtCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ???????????????????? */
    pstSimlockDataWrite = (AT_SIMLOCKDATAWRITE_SET_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_SIMLOCKDATAWRITE_SET_REQ_STRU));
    if (pstSimlockDataWrite == VOS_NULL_PTR)
    {
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        /*lint -restore */
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_SUCCESS;
    }

    /* ???????? */
    lMemResult = memcpy_s(pstSimlockDataWrite->aucCategoryData, AT_SIMLOCKDATAWRITE_PARA_LEN, (pucData + usPos), (VOS_SIZE_T)(usLen - usPos));
    TAF_MEM_CHK_RTN_VAL(lMemResult, AT_SIMLOCKDATAWRITE_PARA_LEN, (VOS_SIZE_T)(usLen - usPos));

    /* ???????????????????????????????? */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType = AT_EXTEND_CMD_TYPE;

    AT_PR_LOGI("enter");

    ulResult = AT_SetSimlockDataWritePara(ucIndex, pstSimlockDataWrite);
    if (ulResult != AT_WAIT_ASYNC_RETURN)
    {
        AT_PR_LOGI("return OK");

        At_FormatResultData(ucIndex, ulResult);
    }
    /*lint -save -e516 */
    PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
    PS_MEM_FREE(WUEPS_PID_AT, pstSimlockDataWrite);
    /*lint -restore */
    return AT_SUCCESS;
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 AT_HandleApSndApduCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT32                          ulLengthValue;
    VOS_UINT32                          ulResult;
    errno_t                             lMemResult;
    VOS_UINT8                           ucHeadChar;
    VOS_UINT8                           ucTailChar;

    /* CISA??????????AP?????????????????????????? */
    if (AT_IsApPort(ucIndex) != VOS_TRUE)
    {
        return AT_FAILURE;
    }

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^CISA=");

    /* ??????????????????????"AT^CISA="????????AT_FAILURE */
    if (VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CISA=", usCmdlen) != 0)
    {
        return AT_FAILURE;
    }

    /* ??????AT^CISA=????? */
    if (VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CISA=?", VOS_StrLen("AT^CISA=?")) == 0)
    {
        At_FormatResultData(ucIndex, AT_ERROR);

        return AT_SUCCESS;
    }

    /* ????????(??????????????AT)?????????? */
    usPos = (VOS_UINT16)VOS_StrLen("AT");

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^CISA");

    lMemResult = memcpy_s(g_stATParseCmd.stCmdName.aucCmdName,
                          AT_CMD_NAME_LEN + 1,
                          (pucData + usPos),
                          g_stATParseCmd.stCmdName.usCmdNameLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, AT_CMD_NAME_LEN + 1, g_stATParseCmd.stCmdName.usCmdNameLen);

    g_stATParseCmd.stCmdName.aucCmdName[g_stATParseCmd.stCmdName.usCmdNameLen] = '\0';

    usPos += g_stATParseCmd.stCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ?????????????????????????? */
    usCommaCnt      = 0;
    usFirstCommaPos = 0;
    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (*(pucData + usLoop) == ',')
        {
            usCommaCnt++;

            /* ?????????????????????? */
            if (usFirstCommaPos == 0)
            {
                usFirstCommaPos = usLoop + 1;
            }
        }
    }

    /* ??????????????1????AT???????????????? */
    if (usCommaCnt != 1)
    {
        AT_WARN_LOG("AT_HandleApSndApduCmd: usCommaCnt != 1!");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ???????????????????????????? */
    ucHeadChar      = *(pucData + usFirstCommaPos);
    ucTailChar      = *(pucData + usLen - VOS_StrLen("\""));
    if ( (ucHeadChar != '"')
      || (ucTailChar != '"') )
    {
        AT_WARN_LOG("AT_HandleApSndApduCmd: <command> not a string");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ?????????????????? */
    usFirstParaLen  = (usFirstCommaPos - usPos) - (VOS_UINT16)VOS_StrLen(",");
    usSecondParaLen = usLen - usFirstCommaPos - (VOS_UINT16)(2 * VOS_StrLen("\""));

    if (atAuc2ul(pucData + usCmdlen, usFirstParaLen, &ulLengthValue) == AT_FAILURE)
    {
        AT_WARN_LOG("AT_HandleApSndApduCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }
    /* ???????????????????????????????? */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType             = AT_EXTEND_CMD_TYPE;

    /* ???????????????????????? */
    ulResult = atMatchCmdName(ucIndex, g_stATParseCmd.ucCmdFmtType);

    if(ulResult != ERR_MSP_SUCCESS)
    {
        At_FormatResultData(ucIndex, ulResult);

        return AT_SUCCESS;
    }

    ulResult = AT_SetCISAPara(ucIndex,
                              ulLengthValue,
                              (pucData + usFirstCommaPos + VOS_StrLen("\"")),
                              usSecondParaLen);

    if (ulResult != AT_WAIT_ASYNC_RETURN)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return AT_SUCCESS;
}
#endif

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_HandleApXsmsSndCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT32                          ulLengthValue;
    VOS_UINT32                          ulResult;
    errno_t                             lMemResult;
    VOS_UINT8                           ucHeadChar;
    VOS_UINT8                           ucTailChar;

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^CCMGS=");

    /* ??????????????????????"AT^CCMGS="????????AT_FAILURE */
    if (VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGS=", usCmdlen) != 0)
    {
        return AT_FAILURE;
    }

    /* ??????AT^CCMGS=????? */
    if (VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGS=?", VOS_StrLen("AT^CCMGS=?")) == 0)
    {
        At_FormatResultData(ucIndex, AT_OK);

        return AT_SUCCESS;
    }

    /* ????????(??????????????AT)?????????? */
    usPos = (VOS_UINT16)VOS_StrLen("AT");

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^CCMGS");

    lMemResult = memcpy_s(g_stATParseCmd.stCmdName.aucCmdName,
                          AT_CMD_NAME_LEN + 1,
                          (pucData + usPos),
                          g_stATParseCmd.stCmdName.usCmdNameLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, AT_CMD_NAME_LEN + 1, g_stATParseCmd.stCmdName.usCmdNameLen);

    g_stATParseCmd.stCmdName.aucCmdName[g_stATParseCmd.stCmdName.usCmdNameLen] = '\0';

    usPos += g_stATParseCmd.stCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ?????????????????????????? */
    usCommaCnt      = 0;
    usFirstCommaPos = 0;
    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (*(pucData + usLoop) == ',')
        {
            usCommaCnt++;

            /* ?????????????????????? */
            if (usFirstCommaPos == 0)
            {
                usFirstCommaPos = usLoop + 1;
            }
        }
    }

    /* ??????????????1????AT???????????????? */
    if (usCommaCnt != 1)
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: usCommaCnt != 1!");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ???????????????????????????? */
    ucHeadChar      = *(pucData + usFirstCommaPos);
    ucTailChar      = *(pucData + usLen - VOS_StrLen("\""));
    if ( (ucHeadChar != '"')
      || (ucTailChar != '"') )
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <PDU> not a string");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ?????????????????? */
    usFirstParaLen  = (usFirstCommaPos - usPos) - (VOS_UINT16)VOS_StrLen(",");
    usSecondParaLen = usLen - usFirstCommaPos - (VOS_UINT16)(2 * VOS_StrLen("\""));

    if (atAuc2ul(pucData + usCmdlen, usFirstParaLen, &ulLengthValue) == AT_FAILURE)
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }
    /* ???????????????????????????????? */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType             = AT_EXTEND_CMD_TYPE;

    /* ???????????????????????? */
    ulResult = atMatchCmdName(ucIndex, g_stATParseCmd.ucCmdFmtType);

    if (ulResult != ERR_MSP_SUCCESS)
    {
        At_FormatResultData(ucIndex, ulResult);

        return AT_SUCCESS;
    }

    ulResult = AT_SetCcmgsPara(ucIndex,
                               ulLengthValue,
                               (pucData + usFirstCommaPos + VOS_StrLen("\"")),
                               usSecondParaLen);

    if (ulResult != AT_WAIT_ASYNC_RETURN)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_HandleApXsmsWriteCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    VOS_UINT16                          usSecondCommaPos;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT16                          usThirdParaLen;
    VOS_UINT32                          ulLengthValue;
    VOS_UINT32                          ulStatValue;
    VOS_UINT32                          ulResult;
    errno_t                             lMemResult;
    VOS_UINT8                           ucHeadChar;
    VOS_UINT8                           ucTailChar;

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^CCMGW=");

    /* ??????????????????????"AT^CCMGW="????????AT_FAILURE */
    if (VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGW=", usCmdlen) != 0)
    {
        return AT_FAILURE;
    }

    /* ??????AT^CCMGS=????? */
    if (VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGW=?", VOS_StrLen("AT^CCMGW=?")) == 0)
    {
        At_FormatResultData(ucIndex, AT_OK);

        return AT_SUCCESS;
    }

    /* ????????(??????????????AT)?????????? */
    usPos = (VOS_UINT16)VOS_StrLen("AT");

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^CCMGW");

    lMemResult = memcpy_s(g_stATParseCmd.stCmdName.aucCmdName,
                          AT_CMD_NAME_LEN + 1,
                          (pucData + usPos),
                          g_stATParseCmd.stCmdName.usCmdNameLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, AT_CMD_NAME_LEN + 1, g_stATParseCmd.stCmdName.usCmdNameLen);

    g_stATParseCmd.stCmdName.aucCmdName[g_stATParseCmd.stCmdName.usCmdNameLen] = '\0';

    usPos += g_stATParseCmd.stCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ?????????????????????????? */
    usCommaCnt      = 0;
    usFirstCommaPos = 0;
    usSecondCommaPos= 0;

    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (*(pucData + usLoop) == ',')
        {
            usCommaCnt++;

            /* ?????????????????????? */
            if (usFirstCommaPos == 0)
            {
                usFirstCommaPos = usLoop + 1;
            }

            /* ?????????????????????? */
            if ((usSecondCommaPos == 0)
                && (usCommaCnt == 2))
            {
                usSecondCommaPos = usLoop + 1;
            }
        }
    }

    /* ??????????????2????AT???????????????? */
    if (usCommaCnt != 2)
    {
        AT_WARN_LOG("AT_HandleApXsmsWriteCmd: usCommaCnt != 1!");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ???????????????????????????? */
    ucHeadChar      = *(pucData + usSecondCommaPos);
    ucTailChar      = *(pucData + usLen - VOS_StrLen("\""));
    if ( (ucHeadChar != '"')
      || (ucTailChar != '"') )
    {
        AT_WARN_LOG("AT_HandleApXsmsWriteCmd: <PDU> not a string");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ?????????????????? */
    usFirstParaLen  = (usFirstCommaPos - usPos) - (VOS_UINT16)VOS_StrLen(",");
    usSecondParaLen = usSecondCommaPos - usFirstCommaPos - (VOS_UINT16)VOS_StrLen(",");
    usThirdParaLen  = usLen - usSecondCommaPos - (VOS_UINT16)(2 * VOS_StrLen("\""));

    /* ????????1<len>???? */
    if (atAuc2ul(pucData + usCmdlen, usFirstParaLen, &ulLengthValue) == AT_FAILURE)
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ????????2<stat>???? */
    if (atAuc2ul(pucData + usFirstCommaPos,
                               usSecondParaLen,
                               &ulStatValue) == AT_FAILURE)
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ???????????????????????????????? */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType             = AT_EXTEND_CMD_TYPE;

    /* ???????????????????????? */
    ulResult = atMatchCmdName(ucIndex, g_stATParseCmd.ucCmdFmtType);

    if (ulResult != ERR_MSP_SUCCESS)
    {
        At_FormatResultData(ucIndex, ulResult);

        return AT_SUCCESS;
    }

    ulResult = AT_SetCcmgwPara(ucIndex,
                               ulLengthValue,
                               ulStatValue,
                               (pucData + usSecondCommaPos + VOS_StrLen("\"")),
                               usThirdParaLen);

    if (ulResult != AT_WAIT_ASYNC_RETURN)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return AT_SUCCESS;
}
#endif

VOS_UINT32 At_HandleApModemSpecialCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                          *pucSystemAppConfig = VOS_NULL_PTR;

    /* ???????????????? */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

    if ( *pucSystemAppConfig != SYSTEM_APP_ANDROID)
    {
        return AT_FAILURE;
    }

    /* ????AT^FACAUTHPUBKEYEX=<index>,<total>,<pubkey>????????(????<pubkey>????) */
    if (AT_HandleFacAuthPubKeyExCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }

    /* ????AT^SIMLOCKDATAWRITEEX=<layer>,<total>,<index>,<simlock_data>,[hmac]????????(????<simlock_data>????) */
    if (AT_HandleSimLockDataWriteExCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }

    /* ????AT^SIMLOCKOTADATAWRITE=<layer>,<total>,<index>,<simlock_data>,[hmac]????????(????<simlock_data>????) */
    if (AT_HandleSimLockOtaDataWriteCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }

#if (FEATURE_SC_NETWORK_UPDATE == FEATURE_ON)
    /* ????AT^SIMLOCKNWDATAWRITE=<layer>,<total>,<index>,<simlock_data>,[hmac]????????(????<simlock_data>????) */
    if (AT_HandleSimLockNWDataWriteCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }
#endif

    /* ????AT^SIMLOCKDATAWRITE=<simlock_data_write>????????(????<simlock_data_write>????) */
    if (AT_HandleSimLockDataWriteCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)
    /* ????AT^CISA=<length>,<command> */
    if (AT_HandleApSndApduCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }
#endif

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    if (AT_HandleApXsmsSndCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }

    if (AT_HandleApXsmsWriteCmd(ucIndex, pucData, usLen) == AT_SUCCESS)
    {
        return AT_SUCCESS;
    }
#endif

    /* ??????^EOPLMN?????????????????? */

    return AT_FAILURE;
}


TAF_UINT32 At_CheckUsimStatus (
    TAF_UINT8                          *pucCmdName,
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRst;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU   stQuickStartFlg;

    stQuickStartFlg.ulQuickStartSta = AT_QUICK_START_DISABLE;
    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulGetModemIdRslt != VOS_OK)
    {
        AT_ERR_LOG("At_CheckUsimStatus:Get Modem Id fail!");
        return AT_ERROR;
    }

    pstSmsCtx      = AT_GetModemSmsCtxAddrFromModemId(enModemId);
    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);




    /* ???????????????????? PIN ???? */
    if (TAF_ACORE_NV_READ(enModemId, en_NV_Item_FollowOn_OpenSpeed_Flag, (VOS_VOID*)(&stQuickStartFlg), sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)) != NV_OK)
    {
       stQuickStartFlg.ulQuickStartSta = AT_QUICK_START_DISABLE;
    }

    if(stQuickStartFlg.ulQuickStartSta == AT_QUICK_START_ENABLE)
    {
        return AT_SUCCESS;
    }

    /*SMS??????????????????????????????????????????????????CMGL??????????????????????*/
    if (VOS_StrCmp((TAF_CHAR*)pucCmdName, "+CMGL") == 0)
    {
        if (pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec != 0)
        {
            return AT_SUCCESS;
        }
    }


    switch (pstUsimInfoCtx->enCardStatus)
    {
        case USIMM_CARDAPP_SERVIC_AVAILABLE:
            ulRst = AT_SUCCESS;
            break;
        case USIMM_CARDAPP_SERVIC_SIM_PIN:
            ulRst = AT_CME_SIM_PIN_REQUIRED;
            break;
        case USIMM_CARDAPP_SERVIC_SIM_PUK:
            ulRst = AT_CME_SIM_PUK_REQUIRED;
            break;
        case USIMM_CARDAPP_SERVIC_UNAVAILABLE:
        case USIMM_CARDAPP_SERVIC_NET_LCOK:
        case USIMM_CARDAPP_SERVICE_IMSI_LOCK:
            ulRst = AT_CME_SIM_FAILURE;
            break;
        case USIMM_CARDAPP_SERVIC_ABSENT:
            ulRst = AT_CME_SIM_NOT_INSERTED;
            break;

        case USIMM_CARDAPP_SERVIC_BUTT:

            ulRst = AT_CME_SIM_BUSY;
            break;


        default:
            ulRst = AT_ERROR;
            break;
    }

    return ulRst;
}




VOS_VOID At_SetMode(VOS_UINT8 ucIndex, AT_MODE_TYPE Mode, VOS_UINT8 ucSubMode)
{
    /* ????ONLINE-COMMAND????, ????????????????, ????????????STOP */
    if ( (gastAtClientTab[ucIndex].Mode == AT_DATA_MODE)
      && (Mode == AT_ONLINE_CMD_MODE) )
    {
        gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;
    }

#if (FEATURE_AT_HSUART == FEATURE_ON)
    /*
     * HSUART??????DATA??????????CMD/ONLINE_CMD????:
     * ????HSUART??????????????, ????????????????????, ??????????????????
     */
    if (AT_CheckHsUartUser(ucIndex) == VOS_TRUE)
    {
        if ( (gastAtClientTab[ucIndex].Mode == AT_DATA_MODE)
          && ((Mode == AT_ONLINE_CMD_MODE) || (Mode == AT_CMD_MODE)) )
        {
            AT_HSUART_ClearDataBuff(ucIndex);
        }
    }
#endif

    /* ???????????? */
    if ( ( (gastAtClientTab[ucIndex].Mode == AT_ONLINE_CMD_MODE)
        || (gastAtClientTab[ucIndex].Mode == AT_DATA_MODE) )
      && (Mode == AT_CMD_MODE) )
    {
        /* ??????Q??????????,??????????NO CARRIER????????DCD??????
           ??????DCD????????????????At_FormatResultData??????*/

        gastAtClientTab[ucIndex].DataMode = AT_DATA_BUTT_MODE;
        gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;
        AT_NORM_LOG("At_SetMode exit data mode");
    }

    gastAtClientTab[ucIndex].Mode          = Mode;

    if (gastAtClientTab[ucIndex].Mode == AT_CMD_MODE)
    {
        g_stParseContext[ucIndex].ucMode = ucSubMode;
    }
    else if (gastAtClientTab[ucIndex].Mode == AT_ONLINE_CMD_MODE)
    {
        g_stParseContext[ucIndex].ucMode = ucSubMode;
    }
    else
    {
        gastAtClientTab[ucIndex].DataMode  = ucSubMode;
        gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;
        AT_NORM_LOG("At_SetMode enter data mode");
    }
}



TAF_UINT32 AT_CountDigit(TAF_UINT8 *pData,TAF_UINT32 ulLen,TAF_UINT8 Char,TAF_UINT32 ulIndex)
{
    TAF_UINT8   *pTmp   = TAF_NULL_PTR;
    TAF_UINT8   *pCheck = TAF_NULL_PTR;
    TAF_UINT32  count   = 0;
    TAF_UINT32  ChkLen  = 0;
    TAF_UINT32  TmpLen  = 0;

    pTmp  = pData;

    /*????????????*/
    if( (Char == *pTmp) || (Char == *((pTmp + ulLen) - 1)))
    {
        return 0;
    }

    pCheck = pData;
    while( TmpLen++ < ulLen )
    {
        /*????????????????????????????*/
        if(( (*pCheck >= '0') && (*pCheck <= '9') )|| ((*pCheck == Char) && (*(pCheck+1) != Char)))
        {
            pCheck++;
        }
        else
        {
            return 0;
        }
    }

    while( ChkLen++ < ulLen )
    {
        if(Char == *pTmp)
        {
            count++;
            if(count == ulIndex)
            {
                return ChkLen;
            }
        }
        pTmp++;
    }

    return 0;
}

VOS_VOID At_InterTimerOutProc(
    VOS_UINT8                           ucIndex
)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult;

    pstUartCtx = AT_GetUartCtxAddr();
    ulResult   = AT_FAILURE;

    /*??????????????????????????????????*/
    switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        case AT_CMD_COPS_SET_AUTOMATIC:
        case AT_CMD_COPS_SET_MANUAL:
        case AT_CMD_COPS_SET_DEREGISTER:
        case AT_CMD_COPS_SET_MANUAL_AUTOMATIC_MANUAL:
            ulResult= AT_CME_NETWORK_TIMEOUT;
            break;

        case AT_CMD_CUSD_REQ:
            ulResult= AT_CME_NETWORK_TIMEOUT;
            break;

        case AT_CMD_PPP_ORG_SET:
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_REL_PPP_REQ);

            /*??PPP????HDLC??????????*/
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_HDLC_DISABLE);

            /* ???????????? */
            At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);

            /* ??NO CARRIER???? */
            ulResult = AT_NO_CARRIER;
            break;

        case AT_CMD_D_IP_CALL_SET:
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_REL_PPP_RAW_REQ);

            /*??PPP????HDLC??????????*/
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_HDLC_DISABLE);

            ulResult = AT_ERROR;
            break;

        case AT_CMD_H_PS_SET:
        case AT_CMD_PS_DATA_CALL_END_SET:

            /* ???????????? */
            At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);
            ulResult = AT_ERROR;
            break;

#if(FEATURE_ON == FEATURE_LTE)
        case AT_CMD_SET_TMODE:
            ulResult = AT_ERROR;
            break;
#endif

        case AT_CMD_COPS_ABORT_PLMN_LIST:
            ulResult = AT_ABORT;
            break;

        case AT_CMD_NETSCAN_ABORT:
            ulResult = AT_ABORT;
            break;

        case AT_CMD_CMGS_TEXT_SET:
        case AT_CMD_CMGS_PDU_SET:
        case AT_CMD_CMGC_TEXT_SET:
        case AT_CMD_CMGC_PDU_SET:
        case AT_CMD_CMSS_SET:
        case AT_CMD_CMST_SET:
            ulResult = AT_CMS_UNKNOWN_ERROR;
            break;

        case AT_CMD_CPBR2_SET:
        case AT_CMD_CPBR_SET:
            if (AT_CheckHsUartUser(ucIndex) == VOS_TRUE)
            {
                pstUartCtx->pWmLowFunc = VOS_NULL_PTR;
            }

            ulResult = AT_ERROR;
            break;

        case AT_CMD_VMSET_SET:
            AT_InitVmSetCtx();
            ulResult = AT_ERROR;
            break;

        default:
            ulResult= AT_ERROR;
            break;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    At_FormatResultData(ucIndex,ulResult);
    return;

}


VOS_UINT32 AT_DockHandleCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    errno_t                             lMemResult;
    VOS_UINT8                           i;
    VOS_UINT16                          usLength = 0;
    VOS_UINT8                           aucCmdTmp[100] = {0};

    if (usLen > sizeof(aucCmdTmp))
    {
        return AT_FAILURE;
    }

    /* ????AT????????????????E5 */
    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        if (gastAtClientTab[i].UserType == AT_APP_USER)
        {
            memset_s(aucCmdTmp, sizeof(aucCmdTmp), 0x00, sizeof(aucCmdTmp));
            lMemResult = memcpy_s(aucCmdTmp, sizeof(aucCmdTmp), pucData, usLen);
            TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(aucCmdTmp), usLen);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%s%s%s",
                                gaucAtCrLf, aucCmdTmp, gaucAtCrLf);
            At_SendResultData(i, pgucAtSndCodeAddr, usLength);
            return AT_SUCCESS;
        }
    }

    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      : At_MatchCmdName
 Description    : ??????????
 Input          : ucIndex  --- ??????????
                  CmdType  --- ????????
                  pRetName --- ??????????????
                  pRetPara --- ????????????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_MatchCmdName (TAF_UINT16 ucIndex,TAF_UINT32 CmdType)
{
    /*  */
    return AT_FAILURE;
}



VOS_UINT32 AT_HandleDockSetCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_ParseSetDockCmd(pucData, usLen);
    if (ulResult != AT_SUCCESS)
    {
        return AT_FAILURE;
    }

    if (At_MatchCmdName(ucIndex, gucAtCmdFmtType) == AT_FAILURE)
    {
        At_FormatResultData(ucIndex, AT_CMD_NOT_SUPPORT);
        return AT_SUCCESS;
    }


    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^DOCK", AT_EXTEND_CMD_TYPE);

    ulResult = At_SetParaCmd(ucIndex);

    At_FormatResultData(ucIndex, ulResult);

    return AT_SUCCESS;
}


VOS_VOID AT_RcvTiS0Expired(
    REL_TIMER_MSG                      *pstMsg
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    MN_CALL_SUPS_PARAM_STRU             stCallMgmtParam;
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT16                          usReqClientId;
    MODEM_ID_ENUM_UINT16                enModemId;

    /* ????timer name????????????index */
    ucClientIndex = (VOS_UINT8)(pstMsg->ulName >> 12);

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucClientIndex);

    memset_s(&stCallMgmtParam, sizeof(stCallMgmtParam), 0x00, sizeof(MN_CALL_SUPS_PARAM_STRU));

    /* ????????voice??????????????????calltype ????????voice */
    stCallMgmtParam.enCallType    = MN_CALL_TYPE_VOICE;
    stCallMgmtParam.enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH;

    stCallMgmtParam.callId = (MN_CALL_ID_T)pstMsg->ulPara;

    /* ????ClientId??????ClientId 0x3fff????0x7fff??
       AT??????incoming????????????????????????????????????????ulName????????Client Index??0x3f????0x7f
       ????????????MN_CALL_Sups????????ClientId
    */
    if (ucClientIndex == AT_BROADCAST_CLIENT_INDEX_MODEM_0)
    {
        usReqClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    }
    else if (ucClientIndex == AT_BROADCAST_CLIENT_INDEX_MODEM_1)
    {
        usReqClientId = AT_BROADCAST_CLIENT_ID_MODEM_1;
    }
    else
    {
        usReqClientId = AT_BROADCAST_CLIENT_ID_MODEM_2;
    }

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = usReqClientId;
    stCtrl.ucOpId                       = 0;

    if (AT_GetModemIdFromClient(usReqClientId, &enModemId) != VOS_OK)
    {
        return;
    }

    /* AT??CCM???????????????? */
    if (TAF_CCM_CallCommonReq(&stCtrl,
                                        &stCallMgmtParam,
                                        ID_TAF_CCM_CALL_SUPS_CMD_REQ,
                                        sizeof(stCallMgmtParam),
                                        enModemId) != VOS_OK)
    {
        AT_WARN_LOG("AT_ProcTimerS0: S0 Answer Fail");
    }
    AT_PR_LOGH("AT_RcvTiS0Expired: CallId = %d", stCallMgmtParam.callId);
    pstCcCtx->stS0TimeInfo.bTimerStart = TAF_FALSE;
    pstCcCtx->stS0TimeInfo.ulTimerName = 0;

    return;
}



VOS_VOID AT_RcvTiShutDownExpired(REL_TIMER_MSG *pstTmrMsg)
{
#if (VOS_WIN32 == VOS_OS_VER)
    mdrv_sysboot_shutdown(0);
#else
    mdrv_sysboot_shutdown();
#endif
    return;
}


AT_PS_INTERNAL_TIMEOUT_FUNC AT_GetInternalTimeOutResultFunc(VOS_UINT32 ulInterTimerName)
{
    AT_PS_INTERNAL_TIMEOUT_RESULT_STRU *pstInterTimeoutFuncTblPtr = VOS_NULL_PTR;
    AT_PS_INTERNAL_TIMEOUT_FUNC         pInterTimeoutFunc         = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstInterTimeoutFuncTblPtr = AT_GET_INTERNAL_TIMEOUT_RSLT_FUNC_TBL_PTR();

    for (ulCnt = 0; ulCnt < AT_GET_INTERNAL_TIMEOUT_RSLT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (ulInterTimerName == pstInterTimeoutFuncTblPtr[ulCnt].ulInterTimerName)
        {
            pInterTimeoutFunc = pstInterTimeoutFuncTblPtr[ulCnt].pInternalTimeoutFunc;
            break;
        }
    }

    return pInterTimeoutFunc;
}


TAF_VOID At_TimeOutProc(
    REL_TIMER_MSG                       *pMsg
)
{
    /* ???????????????????? */
    AT_PS_INTERNAL_TIMEOUT_FUNC         pInterTimeoutFunc         = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    if (pMsg == VOS_NULL_PTR)
    {
        AT_WARN_LOG("At_TimeOutProc pMsg is NULL");
        return;
    }

    ucIndex = (VOS_UINT8)pMsg->ulName;
    if ((pMsg->ulName & 0x00000f00) == AT_INTERNAL_PROCESS_TYPE)
    {
        pInterTimeoutFunc = AT_GetInternalTimeOutResultFunc(pMsg->ulName & 0x000000ff);

        /* ?????????????????????? */
        if (pInterTimeoutFunc != VOS_NULL_PTR)
        {
            pInterTimeoutFunc(pMsg);
        }
        else
        {
            AT_ERR_LOG1("At_TimeOutProc: not find timeout func, Msg is ", pMsg->ulName);
        }
        return;
    }
    else
    {
        ucIndex = (VOS_UINT8)pMsg->ulName;
        if(ucIndex >= AT_MAX_CLIENT_NUM)
        {
            AT_WARN_LOG("At_TimeOutProc FAILURE");
            return;
        }

        if(gastAtClientTab[ucIndex].CmdCurrentOpt == AT_CMD_CURRENT_OPT_BUTT)
        {
            AT_WARN_LOG("At_TimeOutProc AT_CMD_CURRENT_OPT_BUTT");
            return;
        }

        AT_LOG1("At_TimeOutProc ucIndex:",ucIndex);
        AT_LOG1("At_TimeOutProc gastAtClientTab[ucIndex].CmdCurrentOpt:",gastAtClientTab[ucIndex].CmdCurrentOpt);

        At_InterTimerOutProc(ucIndex);

    }
}
/*****************************************************************************
 Prototype      : At_GetStrContent
 Description    :
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT8* At_GetStrContent(TAF_UINT32 ulType)
{
    if(ulType < AT_STRING_BUTT)
    {
        return gastAtStringTab[ulType].pucText;
    }
    else
    {
        return gastAtStringTab[AT_STRING_BUTT].pucText;
    }
}

/* PC??????AT??A??????C??, At_sprintf??????????,?????????????????????? */


/*lint -e713 -e507 -e530*/
VOS_INT32 At_sprintf(VOS_INT32 MaxLength,VOS_CHAR *pHeadAddr,VOS_CHAR *pCurrAddr,const VOS_CHAR *fmt,...)
{
    VOS_INT32 slLength = 0;
    VOS_UINT32 ulNum = 0;
    VOS_INT32 lNumSrc = 0;      /* ???????? */
    VOS_INT32 slNum = 0;        /* ???????????? */
    VOS_UINT32 ulSignFlag = VOS_FALSE;
    VOS_CHAR *pData = NULL;
    VOS_CHAR *sc = NULL;
    VOS_CHAR *s = NULL;
    va_list args;
    VOS_UINT32 ulLen1 = 0, ulLen2 = 0;   /* ulLen1:%????????????; ulLen2:?????????????? */

    if(pCurrAddr < pHeadAddr)
    {
        return 0;
    }

    va_start(args, fmt);
    for (pData = (VOS_CHAR *)fmt; *pData != '\0'; ++pData)
    {
        if(*pData == '%')
        {
            ulLen1 = 0;
            ulLen2 = 0;

            pData++;

            if((*pData) == '+' && *(pData + 1) == 'd')
            {
                pData++;
                ulSignFlag = VOS_TRUE;
                ulLen1 = 0;     /* ?????????????????? */
            }

            if((*pData) == '0')
            {
                pData++;
                ulLen1 = 0;     /* ?????????????????? */
            }

            /* ????????????????????9???????? */
            if(((*pData) >= '0') && ((*pData) <= '9'))
            {
                ulLen1 = (VOS_UINT32)(VOS_INT32)((*pData) - '0');     /* ?????????? */
                pData++;
            }

            /* ??????????????d,s,X,?????????????????????? */
            switch(*pData)
            {
            case 'c':
                {
                    slLength++;
                    break;
                }

            case 's':
                s = va_arg(args, VOS_CHAR *);
                if(s == NULL)
                {
                    slLength += (VOS_INT32)strlen("(null)");
                    break;
                }

                for (sc = s; *sc != '\0'; ++sc)
                {
                    slLength++;
                }
                break;

            case 'd':
                lNumSrc = va_arg(args, VOS_INT32);
                slNum = lNumSrc;

                slLength++;
                ulLen2++;                   /* ?????????? */

                while ((slNum > 9) || (slNum < (-9)))
                {
                    slNum = slNum / 10;
                    slLength++;
                    ulLen2++;               /* ?????????? */
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                else if(lNumSrc < 0 || ulSignFlag == VOS_TRUE)    /* ????ulLen2 >= ulLen1,??lNumSrc<0???????????????????????? */
                {
                    slLength++;
                    ulSignFlag = VOS_FALSE;
                }
                else
                {
                }
                break;

            case 'u':
                ulNum = va_arg(args, VOS_UINT32);

                slLength++;
                ulLen2++;                   /* ?????????? */
                while (ulNum > 9)
                {
                    ulNum = ulNum / 10;
                    slLength++;
                    ulLen2++;               /* ?????????? */
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                break;

            case 'X':
                /* continue */
            case 'x':
                ulNum = va_arg(args, VOS_UINT32);

                slLength++;
                ulLen2++;                   /* ?????????? */

                while (ulNum > 0x0f)
                {
                    ulNum = ulNum / 16;
                    slLength++;
                    ulLen2++;               /* ?????????? */
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                break;

            default:
                va_end(args);
                return 0;
            }
        }
        else
        {
            slLength++;     /* ??1 */
        }
    }
    va_end(args);

    if(pCurrAddr - pHeadAddr + slLength >= (VOS_INT32)(MaxLength))
    {
        return 0;
    }

    va_start(args, fmt);

    if(slLength != VOS_vsprintf_s(pCurrAddr, (VOS_UINT32)(MaxLength - (pCurrAddr - pHeadAddr)), fmt, args))
    {
        va_end(args);
        return 0;
    }

    va_end(args);

    return slLength;
}

/*lint +e713 +e507 +e530*/

/*lint -e713 -e507 -e530*/

TAF_INT32 At_sprintfUnsigned(TAF_INT32 MaxLength,TAF_CHAR *headaddr,TAF_CHAR *curraddr,const TAF_CHAR *fmt,...)
{
    TAF_INT32  Length = 0;
    TAF_UINT32 ulnum = 0;
    TAF_CHAR *pData = TAF_NULL_PTR;
    TAF_CHAR *sc = TAF_NULL_PTR;
    TAF_CHAR *s = TAF_NULL_PTR;
    va_list args;

    if(curraddr < headaddr)
    {
        AT_ERR_LOG("At_sprintf curraddr < headaddr");
        return 0;
    }

    va_start(args, fmt);
    for (pData = (TAF_CHAR*)fmt; *pData != '\0'; ++pData)
    {
        if(*pData == '%')
        {
            pData++;
            /* ??????????????d,s,X,?????????????????????? */
            switch(*pData)
            {
            case 's':
                s = (TAF_CHAR *)va_arg(args, TAF_INT8 *);

                for (sc = s; *sc != '\0'; ++sc)
                {
                    Length++;
                }
                break;

            case 'd':
                ulnum = va_arg(args, TAF_UINT32);

                Length++;

                while (ulnum > 9)
                {
                    ulnum = ulnum / 10;
                    Length++;
                }
                break;

            case 'X':
                ulnum = va_arg(args, TAF_UINT32);

                Length++;
                while (ulnum > 0x0f)
                {
                    ulnum = ulnum / 16;
                    Length++;
                }
                break;

            case '0':
                ulnum = va_arg(args, TAF_UINT32);
                pData++;                                                        /*????????????*/

                Length += (*pData - '0');
                pData++;                                                        /*????X????*/
                break;

            default:
                AT_ERR_LOG("At_sprintf ERROR case");
                va_end(args);
                return 0;
            }
        }
        else
        {
            Length++;     /* ??1 */
        }
    }
    va_end(args);

    if(((curraddr - headaddr) + Length) >= MaxLength)
    {
        AT_ERR_LOG("At_sprintf too long");
        return 0;
    }

    va_start(args, fmt);
    if(Length != VOS_vsprintf_s(curraddr, (VOS_UINT32)(MaxLength -(curraddr - headaddr)), fmt, args))
    {
        AT_ERR_LOG("At_sprintf Length is ERROR!");
    }
    va_end(args);

    return Length;
}
/*lint +e713 +e507 +e530*/


TAF_VOID AT_MapCallTypeModeToClccMode(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    VOS_UINT8                          *penClccMode
)
{
    switch(enCallType)
    {
    case MN_CALL_TYPE_VOICE:
    case MN_CALL_TYPE_EMERGENCY:
    case MN_CALL_TYPE_MIEC :
    case MN_CALL_TYPE_AIEC :
    case MN_CALL_TYPE_TEST :
    case MN_CALL_TYPE_RECFGURATION :
    case MN_CALL_TYPE_PSAP_ECALL:
        *penClccMode = 0;
        break;
    case MN_CALL_TYPE_FAX:
        *penClccMode = 2;
        break;
    default:
        *penClccMode = 1;
        break;
    }
}



AT_CMD_CURRENT_OPT_ENUM At_GetMnOptType(MN_MMI_OPERATION_TYPE_ENUM_U8 enType)
{
    switch(enType)
    {
    case TAF_MMI_CALL_ORIG:/* TAF_MMI_CALL_ORIG */
        return AT_CMD_D_CS_VOICE_CALL_SET;
    case TAF_MMI_CALL_CHLD_REQ:/* TAF_MMI_CALL_CHLD_REQ */
        return AT_CMD_CHLD_SET;
    case TAF_MMI_CHANGE_PIN:/* TAF_MMI_CHANGE_PIN */
        return AT_CMD_CPIN_UNBLOCK_SET;
    case TAF_MMI_CHANGE_PIN2:/* TAF_MMI_CHANGE_PIN2 */
        return AT_CMD_CPIN2_UNBLOCK_SET;
    case TAF_MMI_UNBLOCK_PIN:/* TAF_MMI_UNBLOCK_PIN */
        return AT_CMD_CPIN_VERIFY_SET;
    case TAF_MMI_UNBLOCK_PIN2:/* TAF_MMI_UNBLOCK_PIN2 */
        return AT_CMD_CPIN2_VERIFY_SET;
    case TAF_MMI_REGISTER_SS:/* TAF_MMI_REGISTER_SS */
        return AT_CMD_SS_REGISTER;
    case TAF_MMI_ERASE_SS:/* TAF_MMI_ERASE_SS */
        return AT_CMD_SS_ERASE;
    case TAF_MMI_ACTIVATE_SS:/* TAF_MMI_ACTIVATE_SS */
        return AT_CMD_SS_ACTIVATE;
    case TAF_MMI_DEACTIVATE_SS:/* TAF_MMI_DEACTIVATE_SS */
        return AT_CMD_SS_DEACTIVATE;
    case TAF_MMI_INTERROGATE_SS:/* TAF_MMI_INTERROGATE_SS */
        return AT_CMD_SS_INTERROGATE;
    case TAF_MMI_REGISTER_PASSWD:/* TAF_MMI_REGISTER_PASSWD */
        return AT_CMD_SS_REGISTER_PSWD;
	/* Delete TAF_MMI_GET_PASSWD???? */
    case TAF_MMI_PROCESS_USSD_REQ:/* TAF_MMI_PROCESS_USSD_REQ */
        return AT_CMD_CUSD_REQ;
    case TAF_MMI_SUPPRESS_CLIP:/* TAF_MMI_SUPPRESS_CLIP */
        return AT_CMD_CLIP_READ;
    case TAF_MMI_INVOKE_CLIP:/* TAF_MMI_INVOKE_CLIP */
        return AT_CMD_CLIP_READ;

    case TAF_MMI_DEACTIVATE_CCBS:/* TAF_MMI_DEACTIVATE_CCBS */
        return AT_CMD_SS_DEACTIVE_CCBS;

    case TAF_MMI_INTERROGATE_CCBS:
        return AT_CMD_SS_INTERROGATE_CCBS;

    default:
        break;

    }

    return AT_CMD_INVALID;
}


VOS_UINT32 At_UnlockSimLock(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist
)
{
    AT_PARSE_PARA_TYPE_STRU            *pstPwdPara = VOS_NULL_PTR;
    DRV_AGENT_SIMLOCK_SET_REQ_STRU      stSimlockReq;
    errno_t                             lMemResult;

    stSimlockReq.ulPwdLen    = 0;

    if (ulParaCnt == 2)
    {
        pstPwdPara              = (AT_PARSE_PARA_TYPE_STRU*)(pstParalist + 1);

        if (pstPwdPara->usParaLen == TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX)
        {
            if (At_CheckNumString(pstPwdPara->aucPara,
                                                TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX) != AT_FAILURE)
            {
                stSimlockReq.ulPwdLen    = TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX;

                lMemResult = memcpy_s(stSimlockReq.aucPwd, sizeof(stSimlockReq.aucPwd), pstPwdPara->aucPara, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);
                TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(stSimlockReq.aucPwd), TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);
                stSimlockReq.aucPwd[stSimlockReq.ulPwdLen] = 0;
            }
        }
    }

    if (AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                  gastAtClientTab[ucIndex].opId,
                                                  DRV_AGENT_SIMLOCK_SET_REQ,
                                                  &stSimlockReq,
                                                  sizeof(stSimlockReq),
                                                  I0_WUEPS_PID_DRV_AGENT) == TAF_SUCCESS)
    {
        /*???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_SIMLOCK_SET_REQ;

        /* ????SIMLOCK??????????????????????????????????????????????????????*/
        if(At_StartTimer(AT_SET_PARA_TIME, ucIndex) != AT_SUCCESS)
        {
            At_FormatResultData(ucIndex, AT_ERROR);
            return VOS_ERR;
        }

        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

        return VOS_OK;
    }

    At_FormatResultData(ucIndex, AT_ERROR);
    return VOS_ERR;

}


VOS_VOID AT_RcvFuncReg(AT_PHY_PORT_ENUM_UINT32 ulPhyPort, CBTCPM_RCV_FUNC pRcvFunc)
{
    /*check para*/
    if (ulPhyPort >= AT_PORT_BUTT)
    {
        AT_ERR_LOG("AT_RcvFuncReg: PHY PORT ERR!");
        return;
    }

    if (pRcvFunc == VOS_NULL_PTR)
    {
        AT_ERR_LOG("AT_RcvFuncReg: pRcvFunc is NULL!");
        return;
    }

    g_apAtPortDataRcvFuncTab[ulPhyPort] = pRcvFunc;
}




VOS_UINT32 At_ProcXmlText ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    errno_t                                 lMemResult;
    VOS_UINT16                              usTmpLen;
    AT_XML_PROC_TYPE_ENUM_UINT8             enXmlProcType;
    AT_MTA_CPOS_REQ_STRU                   *pstCposSetReq = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32    enCposOpType;
    AT_MODEM_AGPS_CTX_STRU                 *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ?????????????? */
    usTmpLen           = usLen;
    enXmlProcType      = AT_XML_PROC_TYPE_BUTT;
    enCposOpType       = MTA_AT_CPOS_BUTT;

    /* ????"Ctrl-Z"?????????????????? */
    if (pData[usTmpLen - 1] == AT_CTRL_Z)
    {
        usTmpLen       -= 1;
        enXmlProcType  = AT_XML_PROC_TYPE_FINISH;
        enCposOpType   = MTA_AT_CPOS_SEND;
    }
    /* ????"CR"?????????????????? */
    else if (pData[usTmpLen - 1] == AT_CR)
    {
        enXmlProcType  = AT_XML_PROC_TYPE_CONTINUE;
    }
    /* ????"ESC"?????????????????????? */
    else if (pData[usTmpLen - 1] == AT_ESC)
    {
        usTmpLen       -= 1;
        enXmlProcType  = AT_XML_PROC_TYPE_FINISH;
        enCposOpType   = MTA_AT_CPOS_CANCEL;
    }
    else
    {
        return AT_ERROR;
    }

    /* ??????????????????XML?????? */
    if (enCposOpType != MTA_AT_CPOS_CANCEL)
    {
        /* XML???????????? */
        if (((pstAgpsCtx->stXml.pcXmlTextCur - pstAgpsCtx->stXml.pcXmlTextHead) + usTmpLen) > AT_XML_MAX_LEN)
        {
            return AT_ERROR;
        }

        lMemResult = memcpy_s(pstAgpsCtx->stXml.pcXmlTextCur,
                              AT_XML_MAX_LEN - (unsigned int)(pstAgpsCtx->stXml.pcXmlTextCur - pstAgpsCtx->stXml.pcXmlTextHead),
                              pData,
                              usTmpLen);
        TAF_MEM_CHK_RTN_VAL(lMemResult, AT_XML_MAX_LEN - (unsigned int)(pstAgpsCtx->stXml.pcXmlTextCur - pstAgpsCtx->stXml.pcXmlTextHead), usTmpLen);

        pstAgpsCtx->stXml.pcXmlTextCur += usTmpLen;
    }

    /* ????XML?????????????????? */
    if (enXmlProcType == AT_XML_PROC_TYPE_FINISH)
    {
        pstCposSetReq = (AT_MTA_CPOS_REQ_STRU*)PS_MEM_ALLOC( WUEPS_PID_AT,
                                                             sizeof(AT_MTA_CPOS_REQ_STRU));
        if (pstCposSetReq == VOS_NULL_PTR)
        {
            AT_ERR_LOG("At_ProcXmlText: Memory malloc failed!");
            return AT_ERROR;
        }
        memset_s(pstCposSetReq, sizeof(AT_MTA_CPOS_REQ_STRU), 0x00, sizeof(AT_MTA_CPOS_REQ_STRU));

        /* ???????????? */
        pstCposSetReq->enCposOpType = enCposOpType;

        /* ????????????Ctrl-Z????????????MTA */
        if (enCposOpType == MTA_AT_CPOS_SEND)
        {
            pstCposSetReq->ulXmlLength  = (VOS_UINT32)(pstAgpsCtx->stXml.pcXmlTextCur - pstAgpsCtx->stXml.pcXmlTextHead);
            lMemResult = memcpy_s(pstCposSetReq->acXmlText,
                       MTA_CPOS_XML_MAX_LEN,
                       pstAgpsCtx->stXml.pcXmlTextHead,
                       pstCposSetReq->ulXmlLength);
            TAF_MEM_CHK_RTN_VAL(lMemResult, MTA_CPOS_XML_MAX_LEN, pstCposSetReq->ulXmlLength);
        }

        /* ??????MTA???? */
        ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                          gastAtClientTab[ucIndex].opId,
                                          ID_AT_MTA_CPOS_SET_REQ,
                                          pstCposSetReq,
                                          sizeof(AT_MTA_CPOS_REQ_STRU),
                                          I0_UEPS_PID_MTA);

        /* ????XML???????? */
        /*lint -save -e516 */
        PS_MEM_FREE(WUEPS_PID_AT, pstCposSetReq);
        /*lint -restore */

        if (ulResult != TAF_SUCCESS)
        {
            AT_ERR_LOG("At_ProcXmlText: AT_FillAndSndAppReqMsg fail.");
            return AT_ERROR;
        }

        /* ????AT???????????????????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOS_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_WAIT_XML_INPUT;
}

/* ????^EOPLMN????????????????????????????????AT?????????????? */
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

TAF_UINT32 At_CheckCurrRatModeIsCL (
    VOS_UINT8                           ucIndex
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    VOS_UINT8                          *pucIsCLMode = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    /* ????modemid??????????????????????AT???? */
    if (ulGetModemIdRslt != VOS_OK)
    {
        AT_ERR_LOG("At_CurrRatModeIsCL:Get Modem Id fail!");
        return VOS_FALSE;
    }

    pucIsCLMode = AT_GetModemCLModeCtxAddrFromModemId(enModemId);

    if (*pucIsCLMode == VOS_TRUE)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
#endif

VOS_UINT32 AT_ConvertMtaResult(
    MTA_AT_RESULT_ENUM_UINT32           enResult
)
{
    AT_RRETURN_CODE_ENUM_UINT32         enReturnCode;

    switch (enResult)
    {
        case MTA_AT_RESULT_NO_ERROR:
            enReturnCode = AT_OK;
            break;
        case MTA_AT_RESULT_INCORRECT_PARAMETERS:
            enReturnCode = AT_CME_INCORRECT_PASSWORD;
            break;
        case MTA_AT_RESULT_OPTION_TIMEOUT:
            enReturnCode = AT_CME_NETWORK_TIMEOUT;
            break;
        case MTA_AT_RESULT_ERROR:
        default:
            enReturnCode = AT_ERROR;
            break;
    }

    return enReturnCode;
}

VOS_UINT32  AT_GetSeconds(VOS_VOID)
{
    VOS_UINT32 ulsecond;
    VOS_UINT32 ultimelow    = 0;
    VOS_UINT32 ultimehigh   = 0;
    VOS_UINT64 ulltimeCount = 0;

    if (mdrv_timer_get_accuracy_timestamp(&ultimehigh, &ultimelow) == ERR_MSP_SUCCESS)
    {
        ulltimeCount = ((VOS_UINT64)ultimehigh << 32) | ((VOS_UINT64)ultimelow);
        ulltimeCount = ulltimeCount / SLICE_TO_SECOND_UINT;
    }

    /*??U64??slice????????????????????????32??????????32??????????????????????????136??*/
    ulsecond = (VOS_UINT32)(ulltimeCount & SLICE_TO_MAX_SECOND);

    return ulsecond;
}


VOS_VOID AT_GetLiveTime(
    NAS_MM_INFO_IND_STRU               *pstATtime,
    NAS_MM_INFO_IND_STRU               *pstNewTime,
    VOS_UINT32                          ulNwSecond
)
{
    TIME_ZONE_TIME_STRU                 stNewTime;
    VOS_UINT32                          ulNowSecond;
    VOS_UINT32                          ulSeconds;
    VOS_UINT32                          ulAdjustDate;
    VOS_UINT32                          ulIndex;
    errno_t                             lMemResult;

    memset_s(&stNewTime, sizeof(TIME_ZONE_TIME_STRU), 0x00, sizeof(TIME_ZONE_TIME_STRU));

    /* ???????????????????????? */
    if ((pstATtime->ucIeFlg & NAS_MM_INFO_IE_UTLTZ) == NAS_MM_INFO_IE_UTLTZ)
    {
        lMemResult = memcpy_s(pstNewTime, sizeof(NAS_MM_INFO_IND_STRU), pstATtime, sizeof(NAS_MM_INFO_IND_STRU));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(NAS_MM_INFO_IND_STRU), sizeof(NAS_MM_INFO_IND_STRU));

        if(ulNwSecond == 0)
        {
            return;
        }

        ulNowSecond = AT_GetSeconds();

        /* ????ulNowSecond ??????slice?????????????????????????????????????????????? */
        if (ulNowSecond >= ulNwSecond)
        {
            ulSeconds = ulNowSecond - ulNwSecond;
        }
        else
        {
            /*????????????????????, +1????????????0??????*/
            ulSeconds = SLICE_TO_MAX_SECOND - ulNwSecond + ulNowSecond + 1;
        }

        if (ulSeconds != 0)
        {
            lMemResult = memcpy_s(&stNewTime, sizeof(TIME_ZONE_TIME_STRU),
                                  &pstATtime->stUniversalTimeandLocalTimeZone, sizeof(TIME_ZONE_TIME_STRU));
            TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TIME_ZONE_TIME_STRU), sizeof(TIME_ZONE_TIME_STRU));

            stNewTime.ucSecond += (VOS_UINT8)(ulSeconds % AT_MINUTE_TO_SECONDS);          /*??*/
            stNewTime.ucMinute += (VOS_UINT8)((ulSeconds / AT_MINUTE_TO_SECONDS) % AT_MINUTE_TO_SECONDS);   /*??*/
            stNewTime.ucHour   += (VOS_UINT8)((ulSeconds / (AT_MINUTE_TO_SECONDS * AT_HOUR_TO_MINUTES)) % AT_DAY_TO_HOURS); /*??*/
            ulAdjustDate = (ulSeconds / (AT_MINUTE_TO_SECONDS * AT_HOUR_TO_MINUTES * AT_DAY_TO_HOURS));                   /*??*/

            if (stNewTime.ucSecond >= AT_MINUTE_TO_SECONDS)
            {
                stNewTime.ucMinute += stNewTime.ucSecond / AT_MINUTE_TO_SECONDS;  /*??*/
                stNewTime.ucSecond  = stNewTime.ucSecond % AT_MINUTE_TO_SECONDS;  /*??????????*/
            }

            if (stNewTime.ucMinute >= AT_HOUR_TO_MINUTES)
            {
                stNewTime.ucHour  += stNewTime.ucMinute / AT_HOUR_TO_MINUTES;   /*????*/
                stNewTime.ucMinute = stNewTime.ucMinute % AT_HOUR_TO_MINUTES;   /*??????????*/
            }

            if ((ulAdjustDate > 0) || (stNewTime.ucHour >= AT_DAY_TO_HOURS))
            {
                ulAdjustDate += (stNewTime.ucHour / AT_DAY_TO_HOURS);        /*????*/
                stNewTime.ucHour = stNewTime.ucHour % AT_DAY_TO_HOURS;       /*????????????*/

                lMemResult = memcpy_s(&pstNewTime->stUniversalTimeandLocalTimeZone, sizeof(TIME_ZONE_TIME_STRU),
                                      &stNewTime, sizeof(TIME_ZONE_TIME_STRU));
                TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TIME_ZONE_TIME_STRU), sizeof(TIME_ZONE_TIME_STRU));

                for ( ulIndex = 0; ulIndex < ulAdjustDate; ulIndex++ )
                {
                    At_AdjustLocalDate( &stNewTime, 1, &pstNewTime->stUniversalTimeandLocalTimeZone );
                    lMemResult = memcpy_s(&stNewTime, sizeof(TIME_ZONE_TIME_STRU),
                                          &pstNewTime->stUniversalTimeandLocalTimeZone, sizeof(TIME_ZONE_TIME_STRU));
                    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TIME_ZONE_TIME_STRU), sizeof(TIME_ZONE_TIME_STRU));
                }
            }
            else
            {
                lMemResult = memcpy_s(&pstNewTime->stUniversalTimeandLocalTimeZone, sizeof(TIME_ZONE_TIME_STRU),
                                      &stNewTime, sizeof(TIME_ZONE_TIME_STRU));
                TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TIME_ZONE_TIME_STRU), sizeof(TIME_ZONE_TIME_STRU));
            }
        }
    }

}






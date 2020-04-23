#pragma once
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string.h>                                      
#include <conio.h>            

using namespace std;
string txt1; string txt2;


static void php_similar_str(const char* txt1, int len1, const char* txt2, int len2, int* pos1, int* pos2, int* max)
{
    char* p, * q;
    char* end1 = (char*)txt1 + len1;
    char* end2 = (char*)txt2 + len2;
    int l;

    *max = 0;
    for (p = (char*)txt1; p < end1; p++) {
        for (q = (char*)txt2; q < end2; q++) {
            for (l = 0; (p + l < end1) && (q + l < end2) && (p[l] == q[l]); l++);
            if (l > * max) {
                *max = l;
                *pos1 = p - txt1;
                *pos2 = q - txt2;
            }
        }
    }
}
/* }}} */


/* {{{ php_similar_char
 */
static int php_similar_char(const char* txt1, int len1, const char* txt2, int len2)
{
    int sum;
    int pos1, pos2, max;

    php_similar_str(txt1, len1, txt2, len2, &pos1, &pos2, &max);

    if ((sum = max)) {
        if (pos1 && pos2) {
            sum += php_similar_char(txt1, pos1,
                txt2, pos2);
        }
        if ((pos1 + max < len1) && (pos2 + max < len2)) {
            sum += php_similar_char(txt1 + pos1 + max, len1 - pos1 - max,
                txt2 + pos2 + max, len2 - pos2 - max);
        }
    }

    return sum;
}

float similar_text(string txt1, string txt2, float prosent) {
    int len1, len2; int result;
    len1 = txt1.length();  len2 = txt2.length();
    setlocale(LC_ALL, "rus"); cout.imbue(locale("rus_rus.1251"));//выводит русские буквы
    if (len1 + len2 > 0) {
        result = php_similar_char(txt1.c_str(), len1, txt2.c_str(), len2);
        prosent = (200.0 * result) / (len1 + len2);
       // printf("   %.2f%%    ", prosent);

            if (prosent > 99) {
                printf("   ѕеренаправл€ет на ваш сайт\n");
            }
            else {
                printf("   %.2f%%    ", prosent);
                if (prosent >= 55 and prosent <= 99) {
                    printf("ƒанный сайт €вл€етс€ клоном\n");
                }
            }
        
         printf("\n");
    }
    else
        result = 0; prosent = 0;
    return prosent;
}
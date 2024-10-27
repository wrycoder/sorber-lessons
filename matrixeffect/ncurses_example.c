// SEE: https://stackoverflow.com/questions/61812458/handling-unicode-characters-in-c-and-ncurses
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

void sprintutf8(char * buffer, uint32_t code)
{
  if (code < 0x80)
    sprintf(buffer, "%c", code);
  else if (code < 0x800)
    sprintf(buffer, "%c%c",
      0xC0 | (code >> 6),
      0x80 | (code & 0x3F));
  else
    sprintf(buffer, "%c%c%c",
      0xE0 | (code >> 12),
      0x80 | (code >> 6 & 0x3F),
      0x80 | (code & 0x3F));
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    initscr();              // Initialize stdscr
    char displaychars[4];
    uint shcha_char = 0x0429;

    const char *shades[] = { "\u2588",
                         "\u2593",
                         "\u2592",
                         "\u2591",
                         " "};

    const char *_letters[] = { "\u03E8", /* Coptic Capital Letter Hori */
                                  "\u03E9", /* Coptic Small Letter Hori */
                                  "\u03EA", /* Coptic Capital Letter Gangia */
                                  "\u03EB", /* Coptic Small Letter Gangia */
                                  "\u0428", /* Cyrillic Capital Letter Sha */
                                  "\u0429", /* Cyrillic Capital Letter Shcha */
                                  "\u0436", /* Cyrillic Small Letter Zhe */
                                  "\u0437", /* Cyrillic Small Letter Ze */
                                  "\u043B", /* Cyrillic Small Letter El */
                                  "\u0444", /* Cyrillic Small Ef */
                                  "\u044B", /* Cyrillic Small Yeru */
                                  "\u044E", /* Cyrillic Small Yu */
                                  "\u0454", /* Cyrillic Small Ukrainian Ie */
                                  "\u0462", /* Cyrillic Capital Yat */
                                  "\u0463", /* Cyrillic Small Yat */
                                  "\u0464", /* Cyrillic Capital Iotified E */
                                  "\u0465", /* Cyrillic Small Iotified E */
                                  "\u3061", /* Hiragana */
                                  "\u304D", /* Hiragana */
                                  " "};


    for(int x = 0; x < 20; x++)
    {
        mvaddstr(1, x, shades[x%4]);
    }

    for(int x = 0; x < 20; x++)
    {
        mvaddstr(2, x, _letters[x]);
    }

    for(int x = 0; x < 20; x++)
    {
      sprintutf8(displaychars, (shcha_char + x));
      mvaddstr(3, x, displaychars);
    }

    mvprintw(4, 0, "Press ANY KEY to finish");
    refresh();

    int ch = getch();
    endwin();
}



/*
 * ConsoleExecute.c
 *
 *  Created on: 26 août 2008
 *      Author: color
 */

#include <windows.h>
#include <shellapi.h>
#include <stdio.h>

int main()
  {
    /* autre exemple :
    // ShellExecute(NULL, "open","http://www.scriptzone-fr.com",0,0,SW_NORMAL);
    */
    char typed[256];
    scanf("%s",&typed);
    ShellExecute(NULL, "open",typed,0,0,SW_NORMAL);

    return (0);
  }

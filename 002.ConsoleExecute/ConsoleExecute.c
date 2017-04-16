#include <windows.h>
#include <shellapi.h>


int main()
{
// autre exemple :
//ShellExecute(NULL, "open","http://www.scriptzone-fr.com",0,0,SW_NORMAL);
// 
	 char typed[100];
	 scanf("%s",&typed);
	 ShellExecute(NULL, "open",typed,0,0,SW_NORMAL);

return (0);
}

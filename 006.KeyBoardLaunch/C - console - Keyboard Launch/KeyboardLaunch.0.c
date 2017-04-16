/* 
Ce programme fonctionne sans fenetre
à l'interception d'une touche 
KeyboardLaunch.0 ouvre une console qui attend une commande et un return
KeyboardLaunch.0, fonctionne, mais à degraisser
- ajouter un moyen de désactiver, éventuellement depuis sys tray,
- faire lire le code de la touche d'appel dans le nom, ex: kbd222 = ascii 222
- faire un mode debug verbose sur console
- ajouter la fonction quit sur appui escape pour la console
- si code= 222, penser a vider le buffer pour ne pas interfere avec les autres softs
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

char typed[1];
BYTE KeyState[256];
WORD wBuf;
char *ParametresLigneDeCommande = "/a /k \"chdir C:\\\@ \" ";
char ch;
/* syntaxe due aux caracteres speciaux // et /" qui remplacent / et " */

 // Global instance du hook
 HHOOK hKeyHook;
 
 // Gestion du hook
 __declspec(dllexport) LRESULT CALLBACK KeyEvent (int nCode, WPARAM wParam, LPARAM lParam ) {

 // Action du clavier et les touches tappées
 if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN)) {

 // Structure pour récupération des informations
 KBDLLHOOKSTRUCT hooked = *((KBDLLHOOKSTRUCT*)lParam);

 /* Traitement récupération dec codes des touches */

 GetKeyboardState(KeyState); /*Etat du clavier*/
 ToAscii(hooked.vkCode, hooked.scanCode ,KeyState,&wBuf,0); /*Conversion code > ascii*/
 //on rajoute les touches non traitées par le hook
	 
 switch(hooked.vkCode){
 case 222 :{ShellExecute(0,0,"cmd.exe",ParametresLigneDeCommande,NULL,SW_SHOWNORMAL); break;
	 }

/* code de la touche de launch ,
syntaxe de la commande :
ShellExecute(handle, *LPCSTR plOperation, *LPCSTR plFichier, *LPCSTR plParametres, *LPCSTR plDossier, SW_SHOWNORMAL);
 

*/
	 
 default : {break;} // rien
 }


 }
 // Renvoi des messages au sytème
 return CallNextHookEx(hKeyHook, nCode,wParam,lParam);
 }
 

 // Boucle des messages
 void MsgLoop()
 {
 MSG message;
 while (GetMessage(&message,NULL,0,0)) {
 TranslateMessage( &message );
 DispatchMessage( &message );
 }
 }


 DWORD WINAPI KeyLogger(LPVOID lpParameter)
 {
 // Récuperation de l'instance de notre executable
 HINSTANCE hExe = GetModuleHandle(NULL);
 if (!hExe) return 1;

 // on demarre le hook
 hKeyHook = SetWindowsHookEx (WH_KEYBOARD_LL,(HOOKPROC) KeyEvent,hExe, NULL);
 if(hKeyHook==NULL)
 printf("[le hook clavier a plante !]\n");
 else
 printf("[hook clavier en cours ...]\n");

 // Boucle des messages
 MsgLoop();
 return 0;
 }
///////////////////////////////////////////////////
// départ appli
// launch
// 

//	
// 
////
 int main(int argc, char *argv[])
 {
 // initialisation des options pour la fonction CreateThread
 HANDLE hThread;
 DWORD dwThread;
 DWORD exThread;
 printf("\n[ms 2l] \n");


// on crée le thread qui va démarrer le hook
 hThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE) KeyLogger, (LPVOID)NULL, NULL, &dwThread);

 if (hThread) {
 // Attente à l'infini
 return WaitForSingleObject(hThread,INFINITE);
 } else {
 return 0;
 }
 } 

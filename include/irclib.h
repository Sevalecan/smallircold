#ifndef IRCLIB_H
#define IRCLIB_H

/*
Copyright (c) 2004 Jonathan Seeley

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising
from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you
    wrote the original software. If you use this software in a product, an acknowledgment in
    the product documentation would be appreciated but is not required.
    
    2. Altered source versions must be plainly marked as such, and must not be misrepresented
    as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/

#define _GNU_SOURCE
#include <stdio.h>
#ifdef _IL_WIN_
#include <winsock2.h>
#include <mem.h>
#define CLOSE_SOCKET(a) closesocket(a)
#else
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <asm/ioctls.h>
#include <sys/socket.h>
#define flock64 flock_ex64
#define flock flock_ex
#include <sys/fcntl.h>
#include <errno.h>
#undef flock
#undef flock64
#include <bits/fcntl.h>
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define CLOSE_SOCKET(a) shutdown(a, 0)
#endif
#include <stdint.h>
#include "cintvect.h"

#define FLAGS_REGISTERED 0x00000001

enum {
E_INVALIDCLIENT = 1,           // iclient is null
E_INVALIDCONNECTION,           // not a valid socket in given iclient
E_BADPARAMS,                   // bad paramaters, generally everything except iclient in a function call
E_NOSOCKET,                    // no socket
E_NOMEMORY,                    // no more memory :(
E_NOSUCHCHANNEL,               // you are joined on this channel
E_NOREALLOC,                   // realloc fucked up
E_SOCKETERROR,                 // socket problems, you handle these by yourself
E_INVALIDSOCKET,               // socket isnt valid
E_SOCKETERROR_NOMEMORY,        // no memory for sawkets
E_EMPTY,                       // empty
E_NOSUCHHANDLER,               // no such response handler
E_ALREADYREGISTERED            // you cannot register to the server twice
} IRC_FERRORS;

typedef struct ss_irc_client {
    int socket;
    char *nickname, *username, *realname, *hostname, *servername, *serverhost, *chanlist;
    char *inbuf, *outbuf;
    unsigned long int inlen, outlen;
    unsigned long int flags;
} irc_client;  // IRC Client data

typedef struct ss_irc_rhandle {
    int (*irc_rfpointer)(irc_client *, const char *);          // irc response handle
    char *cotype;                                              // commands to respond to
} irc_rhandle;
typedef struct errreplist {
    unsigned short errn;
    char *name;
    char *error;
} irc_errlist,irc_replist;                                     // error/reply list
typedef struct irr_stc {
    char *com;
    unsigned long int errv;                                    // error value
    int (*irc_rfpointer)(irc_client *, const char *);          // pointer to function that returned the value
} ircr_lsto;                                                   // failed call object
typedef struct irc_stcr {
    unsigned long int errc;                                    // count of return objects
    ircr_lsto *list;                                           // list of return objects
} ircr_lst;
/*
why the hell does the above exist? good question.
It is there because my new irc response handler will call not just one
function pertaining to the command, but every. cool huh?
*/
extern irc_rhandle _defhlist[];                                // default handle list, defined in irclib.c
extern irc_errlist _deferrlist[];                              // default error list
extern irc_replist _defreplist[];                              // default reply list ZOINKZ


/* functions prefixed with '_' are not made for direct use */
int _irc_sstring(const char *st, char **gt);                   // switch string :P
int _irc_addchan(irc_client *iclient, const char *channel);    // add a channel to the chanlist array
int _irc_delchan(irc_client *iclient, const char *channel);    // remove a channel from the chanlist array
int _irc_snick(irc_client *iclient, const char *nick);         // set the stored nick
int _irc_suname(irc_client *iclient, const char *uname);       // set stored user name
int _irc_srname(irc_client *iclient, const char *rname);       // set stored real name
int _irc_shname(irc_client *iclient, const char *hname);       // set stored hostname
int _irc_ssname(irc_client *iclient, const char *sname);       // set stored server name
int _irc_sshost(irc_client *iclient, const char *shost);       // set stored server host

int irc_connect(irc_client *iclient,
                const char *serverhost,
                unsigned short port);                          // connect to a server
int irc_disconnect(irc_client *iclient);                       // disconnect from server
ircr_lst *irc_handle_r(irc_client *iclient, irc_rhandle *ihandle,
                 char *data);                                  
                 // respond to some data from a given list of response handlers
int irc_pollio(irc_client *iclient);                           // poll irc in/out buffers
int irc_pushio(irc_client *iclient,
               char io,
               char fb,
               char *data);                                    // append data to input or output buffers
int irc_popio(irc_client *iclient,
              char io,
              char fb,
              char **dest);                                    // pop in or output data from buffers
/* io is 0 for output and 1 for input, fb is 0 for back, 1 for front. */

int irc_free_erl(ircr_lst *lst);
int irc_changenick(irc_client *iclient, const char *nickname); // change your nickname
int irc_sendpass(irc_client *iclient, const char *password);   // send the password
int irc_register(irc_client *iclient,
                 const char *username,
                 const char *hostname,
                 const char *servername,
                 const char *realname);                        // register on the irc server
int irc_joinchan(irc_client *iclient, const char *channel);    // join a channel
int irc_partchan(irc_client *iclient, const char *channel);    // part a channel
int irc_privmsg(irc_client *iclient,
                const char *target,
                const char *message);                          // privmsg a channel or a person
int irc_notice(irc_client *iclient,
               const char *target,
               const char *message);                           // notice a channel or person
int irc_ctcp(irc_client *iclient, char *target, char *message);// CTCP someone or something
int irc_ctcpr(irc_client *iclient, char *target, char *message);// CTCP Reply, uses notice instead or privmsg
int irc_settopic(irc_client *iclient,
                 char *channel,
                 char *topic);                                 // set channel topic
int irc_setmode(irc_client *iclient,
                char *target,
                char *mode);                                   // set channel or user mode
int irc_kick(irc_client *iclient,
             char *channel,
             char *user,
             char *message);                                   // kick someone from a channel
int irc_list(irc_client *iclient, char *params);               // list channels params can be NULL
int irc_invite(irc_client *iclient, char *user, char *channel);// invite <user> to <channel>
int irc_kill(irc_client *iclient, char *kuser, char *message); // kill a users connection to the server
int irc_ping(irc_client *iclient, char *param);                // ping a server
int irc_pong(irc_client *iclient, char *param);                // pong a server
int irc_quit(irc_client *iclient, char *message);              // send QUIT message to server.

/* POING, its time for response handlers.. TADAH */

int h_irc_ping(irc_client *iclient, const char *data);
int h_irc_ctcpre(irc_client *iclient, const char *data);
int h_irc_ctcprp(irc_client *iclient, const char *data);

int d_irc_pmsg(irc_client *iclient, const char *data); //debug

#endif

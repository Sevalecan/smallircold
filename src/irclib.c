#ifndef IRCLIB_C
#define IRCLIB_C
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


#include <irclib.h>

irc_rhandle _defhlist[] = {
{h_irc_ping, "PING"},
{d_irc_pmsg, "PRIVMSG"},          // debug
{NULL, NULL}
};

irc_errlist _deferrlist[] = {
{401,"ERR_NOSUCHNICK", "<nickname> :No such nick/channel"},
{402,"ERR_NOSUCHSERVER", "<server name> :No such server"},
{403,"ERR_NOSUCHCHANNEL", "<channel name> :No such channel"},
{404,"ERR_CANNOTSENDTOCHAN", "<channel name> :Cannot send to channel"},
{405,"ERR_TOOMANYCHANNELS", "<channel name> :You have joined too many channels"},
{406,"ERR_WASNOSUCHNICK", "<nickname> :There was no such nickname"},
{407,"ERR_TOOMANYTARGETS", "<target> :Duplicate recipients. No message delivered"},
{409,"ERR_NOORIGIN", ":No origin specified"},
{411,"ERR_NORECIPIENT", ":No recipient given (<command>)"},
{412,"ERR_NOTEXTTOSEND", ":No text to send"},
{413,"ERR_NOTOPLEVEL", "<mask> :No toplevel domain specified"},
{414,"ERR_WILDTOPLEVEL", "<mask> :Wildcard in toplevel domain"},
{421,"ERR_UNKNOWNCOMMAND", "<command> :Unknown command"},
{422,"ERR_NOMOTD", ":MOTD File is missing"},
{423,"ERR_NOADMININFO", "<server> :No administrative info available"},
{424,"ERR_FILEERROR", ":File error doing <file op> on <file>"},
{431,"ERR_NONICKNAMEGIVEN", ":No nickname given"},
{432,"ERR_ERRONEUSNICKNAME", "<nick> :Erroneus nickname"},
{433,"ERR_NICKNAMEINUSE", "<nick> :Nickname is already in use"},
{436,"ERR_NICKCOLLISION", "<nick> :Nickname collision KILL"},
{441,"ERR_USERNOTINCHANNEL", "<nick> <channel> :They aren't on that channel"},
{442,"ERR_NOTONCHANNEL", "<channel> :You're not on that channel"},
{443,"ERR_USERONCHANNEL", "<user> <channel> :is already on channel"},
{444,"ERR_NOLOGIN", "<user> :User not logged in"},
{445,"ERR_SUMMONDISABLED", ":SUMMON has been disabled"},
{446,"ERR_USERSDISABLED", ":USERS has been disabled"},
{451,"ERR_NOTREGISTERED", ":You have not registered"},
{461,"ERR_NEEDMOREPARAMS", "<command> :Not enough parameters"},
{462,"ERR_ALREADYREGISTRED", ":You may not reregister"},
{463,"ERR_NOPERMFORHOST", ":Your host isn't among the privileged"},
{464,"ERR_PASSWDMISMATCH", ":Password incorrect"},
{465,"ERR_YOUREBANNEDCREEP", ":You are banned from this server"},
{467,"ERR_KEYSET", "<channel> :Channel key already set"},
{471,"ERR_CHANNELISFULL", "<channel> :Cannot join channel (+l)"},
{472,"ERR_UNKNOWNMODE", "<char> :is unknown mode char to me"},
{473,"ERR_INVITEONLYCHAN", "<channel> :Cannot join channel (+i)"},
{474,"ERR_BANNEDFROMCHAN", "<channel> :Cannot join channel (+b)"},
{475,"ERR_BADCHANNELKEY", "<channel> :Cannot join channel (+k)"},
{481,"ERR_NOPRIVILEGES", ":Permission Denied- You're not an IRC operator"},
{482,"ERR_CHANOPRIVSNEEDED", "<channel> :You're not channel operator"},
{483,"ERR_CANTKILLSERVER", ":You cant kill a server!"},
{491,"ERR_NOOPERHOST", ":No O-lines for your host"},
{501,"ERR_UMODEUNKNOWNFLAG", ":Unknown MODE flag"},
{502,"ERR_USERSDONTMATCH", ":Cant change mode for other users"},
{0, NULL, NULL}};

irc_replist _defreplist[] = {
{302,"RPL_USERHOST", ":[<reply>{<space><reply>}]"},
{303,"RPL_ISON", ":[<nick> {<space><nick>}]"},
{301,"RPL_AWAY", "<nick> :<away message>"},
{305,"RPL_UNAWAY", ":You are no longer marked as being away"},
{306,"RPL_NOWAWAY", ":You have been marked as being away"},
{311,"RPL_WHOISUSER", "<nick> <user> <host> * :<real name>"},
{312,"RPL_WHOISSERVER", "<nick> <server> :<server info>"},
{313,"RPL_WHOISOPERATOR", "<nick> :is an IRC operator"},
{317,"RPL_WHOISIDLE", "<nick> <integer> :seconds idle"},
{318,"RPL_ENDOFWHOIS", "<nick> :End of /WHOIS list"},
{319,"RPL_WHOISCHANNELS", "<nick> :{[@|+]<channel><space>}"},
{314,"RPL_WHOWASUSER", "<nick> <user> <host> * :<real name>"},
{369,"RPL_ENDOFWHOWAS", "<nick> :End of WHOWAS"},
{321,"RPL_LISTSTART", "Channel :Users Name"},
{322,"RPL_LIST", "<channel> <# visible> :<topic>"},
{323,"RPL_LISTEND", ":End of /LIST"},
{324,"RPL_CHANNELMODEIS", "<channel> <mode> <mode params>"},
{331,"RPL_NOTOPIC", "<channel> :No topic is set"},
{332,"RPL_TOPIC", "<channel> :<topic>"},
{341,"RPL_INVITING", "<channel> <nick>"},
{342,"RPL_SUMMONING", "<user> :Summoning user to IRC"},
{351,"RPL_VERSION", "<version>.<debuglevel> <server> :<comments>"},
{352,"RPL_WHOREPLY", "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"},
{315,"RPL_ENDOFWHO", "<name> :End of /WHO list"},
{353,"RPL_NAMREPLY", "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"},
{366,"RPL_ENDOFNAMES", "<channel> :End of /NAMES list"},
{364,"RPL_LINKS", "<mask> <server> :<hopcount> <server info>"},
{365,"RPL_ENDOFLINKS", "<mask> :End of /LINKS list"},
{367,"RPL_BANLIST", "<channel> <banid>"},
{368,"RPL_ENDOFBANLIST", "<channel> :End of channel ban list"},
{371,"RPL_INFO", ":<string>"},
{374,"RPL_ENDOFINFO", ":End of /INFO list"},
{375,"RPL_MOTDSTART", ":- <server> Message of the day - "},
{372,"RPL_MOTD", ":- <text>"},
{376,"RPL_ENDOFMOTD", ":End of /MOTD command"},
{381,"RPL_YOUREOPER", ":You are now an IRC operator"},
{382,"RPL_REHASHING", "<config file> :Rehashing"},
{391,"RPL_TIME", "<server> :<string showing server's local time>"},
{392,"RPL_USERSSTART", ":UserID Terminal Host"},
{393,"RPL_USERS", ":%-8s %-9s %-8s"},
{394,"RPL_ENDOFUSERS", ":End of users"},
{395,"RPL_NOUSERS", ":Nobody logged in"},
{200,"RPL_TRACELINK", "Link <version & debug level> <destination> <next server>"},
{201,"RPL_TRACECONNECTING", "Try. <class> <server>"},
{202,"RPL_TRACEHANDSHAKE", "H.S. <class> <server>"},
{203,"RPL_TRACEUNKNOWN", "???? <class> [<client IP address in dot form>]"},
{204,"RPL_TRACEOPERATOR", "Oper <class> <nick>"},
{205,"RPL_TRACEUSER", "User <class> <nick>"},
{206,"RPL_TRACESERVER", "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server>"},
{208,"RPL_TRACENEWTYPE", "<newtype> 0 <client name>"},
{261,"RPL_TRACELOG", "File <logfile> <debug level>"},
{211,"RPL_STATSLINKINFO", "<linkname> <sendq> <sent messages> <sent bytes> <received messages> <received bytes> <time open>"},
{212,"RPL_STATSCOMMANDS", "<command> <count>"},
{213,"RPL_STATSCLINE", "C <host> * <name> <port> <class>"},
{214,"RPL_STATSNLINE", "N <host> * <name> <port> <class>"},
{215,"RPL_STATSILINE", "I <host> * <host> <port> <class>"},
{216,"RPL_STATSKLINE", "K <host> * <username> <port> <class>"},
{218,"RPL_STATSYLINE", "Y <class> <ping frequency> <connect frequency> <max sendq>"},
{219,"RPL_ENDOFSTATS", "<stats letter> :End of /STATS report"},
{241,"RPL_STATSLLINE", "L <hostmask> * <servername> <maxdepth>"},
{242,"RPL_STATSUPTIME", ":Server Up %d days %d:%02d:%02d"},
{243,"RPL_STATSOLINE", "O <hostmask> * <name>"},
{244,"RPL_STATSHLINE", "H <hostmask> * <servername>"},
{221,"RPL_UMODEIS", "<user mode string>"},
{251,"RPL_LUSERCLIENT", ":There are <integer> users and <integer> invisible on <integer> servers"},
{252,"RPL_LUSEROP", "<integer> :operator(s) online"},
{253,"RPL_LUSERUNKNOWN", "<integer> :unknown connection(s)"},
{254,"RPL_LUSERCHANNELS", "<integer> :channels formed"},
{255,"RPL_LUSERME", ":I have <integer> clients and <integer> servers"},
{256,"RPL_ADMINME", "<server> :Administrative info"},
{257,"RPL_ADMINLOC1", ":<admin info>"},
{258,"RPL_ADMINLOC2", ":<admin info>"},
{259,"RPL_ADMINEMAIL", ":<admin info>"},
{0, NULL, NULL} //terminating NULL object
};

int _irc_addchan(irc_client *iclient, const char *channel) {
    if (iclient == NULL) return E_INVALIDCLIENT;
    if (channel == NULL) return E_BADPARAMS;
    if (channel[0] == '\0') return E_BADPARAMS;
    if (iclient->chanlist == NULL) {
        iclient->chanlist = malloc(strlen(channel)+1);
        if (iclient->chanlist == NULL) return E_NOMEMORY;
        strcpy(iclient->chanlist, channel);
    }
    else {
        char *nc;
        int np = strlen(iclient->chanlist)+strlen(channel)+2;
        nc = realloc(iclient->chanlist, np);
        if (nc == NULL) return E_NOMEMORY;
        iclient->chanlist = nc;
        strcat(iclient->chanlist, ",");
        strcat(iclient->chanlist, channel);
    }
    return 0;
}

int _irc_delchan(irc_client *iclient, const char *channel) {
    char *rchan;
    
    if (iclient == NULL) return E_INVALIDCLIENT;
    if (channel == NULL) return E_BADPARAMS;
    if (channel[0] == '\0') return E_BADPARAMS;
    if (iclient->chanlist == NULL) return E_NOMEMORY;
    
    rchan = strstr(iclient->chanlist, channel);
    if (rchan == NULL) return E_NOSUCHCHANNEL;
    if (rchan+strlen(channel) == '\0') {
        if (rchan == iclient->chanlist) { 
             free(iclient->chanlist);
             iclient->chanlist = NULL;
             return 0;
        }
        char *nc;
        int np;
        np = strlen(iclient->chanlist)-strlen(channel)+1;
        nc = realloc(iclient->chanlist, np);
        if (nc == NULL) {
             iclient->chanlist[strlen(iclient->chanlist)-strlen(channel)] = 0;
             return E_NOREALLOC;
        }
        iclient->chanlist = nc;
        iclient->chanlist[np-1] = 0;
    }
    if (*(rchan+strlen(channel)) == ',') {
        char *nc;
        memmove(rchan, rchan+strlen(channel)+1, strlen(rchan+strlen(channel)+1)+1);
        nc = realloc(iclient->chanlist, strlen(iclient->chanlist)+1);
        if (nc == NULL) E_NOREALLOC;
        iclient->chanlist = nc;
    }
    return 0;
}
    
int _irc_sstring(const char *st, char **gt) {
    if (st == NULL && *gt != NULL || st != NULL && st[0] == 0 && *gt != NULL) {
        free(*gt);
        gt = NULL;
    }
    else if ((st == NULL || st[0] == 0) && *gt == NULL) return 0;
    else if (st != NULL && *gt == NULL) {
        *gt = malloc(strlen(st)+1);
        if (*gt == NULL) return E_NOMEMORY;
        strcpy(*gt, st);
    }
    else if (st != NULL && *gt != NULL) {
        char *nc;
        nc = realloc(*gt, strlen(st)+1);
        if (nc == 0) return E_NOMEMORY;
        *gt = nc;
        strcpy(*gt, st);
    }
    return 0;
}

int _irc_snick(irc_client *iclient, const char *nick) {
    if (iclient == NULL) return E_INVALIDCLIENT;
    _irc_sstring(nick, &iclient->nickname);
}

int _irc_suname(irc_client *iclient, const char *uname) {
    if (iclient == NULL) return E_INVALIDCLIENT;
    _irc_sstring(uname, &iclient->username);
}

int _irc_srname(irc_client *iclient, const char *rname) {
    if (iclient == NULL) return E_INVALIDCLIENT;
    _irc_sstring(rname, &iclient->realname);
}

int _irc_shname(irc_client *iclient, const char *hname) {
    if (iclient == NULL) return E_INVALIDCLIENT;
    _irc_sstring(hname, &iclient->hostname);
}

int _irc_ssname(irc_client *iclient, const char *sname) {
    if (iclient == NULL) return E_INVALIDCLIENT;
    _irc_sstring(sname, &iclient->servername);
}

int _irc_sshost(irc_client *iclient, const char *shost) {
    _irc_sstring(shost, &(iclient->serverhost));
}

int irc_connect(irc_client *iclient, const char *serverhost, unsigned short port) {
    int nret;
    struct sockaddr_in iaddr;
    struct hostent *ia;
    
    if (!iclient) return E_INVALIDCLIENT;
    if (serverhost == NULL) return E_BADPARAMS;
    if (port == 0) port = 6667;
    memset(iclient, 0, sizeof(irc_client));
    
    iclient->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (iclient->socket == INVALID_SOCKET) return E_INVALIDSOCKET;
    ia = gethostbyname(serverhost);
    iaddr.sin_family = AF_INET;
    iaddr.sin_port = htons(port);
    // argh
    // iaddr.sin_addr = *((struct in_addr *)*ia->h_addr_list);
    iaddr.sin_addr = *((struct in_addr *)*ia->h_addr_list);
    nret = connect(iclient->socket, (const struct sockaddr *)&iaddr, sizeof(struct sockaddr_in));
    if (nret == SOCKET_ERROR) return E_SOCKETERROR;
    return 0;
}

#define _IRCDISC_DF(x) \
if (x) free(x)

#define _IRCDISC_DX(y) _IRCDISC_DF(iclient->y)

int irc_disconnect(irc_client *iclient) {
    CLOSE_SOCKET(iclient->socket);
    _IRCDISC_DX(chanlist);
    _IRCDISC_DX(username);
    _IRCDISC_DX(nickname);
    _IRCDISC_DX(realname);
    _IRCDISC_DX(hostname);
    _IRCDISC_DX(servername);
    _IRCDISC_DX(serverhost);
    _IRCDISC_DX(inbuf);
    _IRCDISC_DX(outbuf);
    memset(iclient, 0, sizeof(iclient));
    return 0;
}

ircr_lst *irc_handle_r(irc_client *iclient, irc_rhandle *ihandle, char *data) {
    int cnt, cmdlen, ret;
    cintvect *tdat;
    ircr_lst *rdat;
    ircr_lsto *ts;
    char *cmd;
    tdat = civ_new();
    rdat = malloc(sizeof(ircr_lst));
    if (tdat == NULL || rdat == NULL) return 0;
    if (data[0] == ':') {
        cmd = 1+strchr(data, ' ');
        cmdlen = strchr(cmd, ' ')-cmd;
    }
    else {
        cmd = data;
        cmdlen = strchr(cmd, ' ')-cmd;
    }
    for (cnt=0;ihandle[cnt].cotype != NULL;cnt++) {
        if (strlen(ihandle[cnt].cotype) == cmdlen) {
            ret = strncmp(ihandle[cnt].cotype, cmd, cmdlen);
            if (ret == 0) {
                ret = ihandle[cnt].irc_rfpointer(iclient, data);
                if (ret != 0) {
                    ts = malloc(sizeof(ircr_lsto));
                    if (ts == NULL) return NULL;
                    civ_push(tdat, (int)ts);
                    ts->errv = ret;
                    ts->irc_rfpointer = ihandle[cnt].irc_rfpointer;
                    ts->com = ihandle[cnt].cotype;
                }
            }    
        }
    }
    
    if (tdat->count > 0) {
        rdat->errc = tdat->count;
        rdat->list = (ircr_lsto *)tdat->lst;
    }
    else {
        free(rdat);
        rdat = NULL;
    }    
    free(tdat);
    
    return rdat;
}

int irc_free_erl(ircr_lst *lst) {
    int x;
    for (x = 0;x<lst->errc;x++) {
        free((void *)&(lst->list[x]));
    }    
    free(lst);
    return 0;
}    

int irc_pollio(irc_client *iclient) {
    int rsize, ret, sw;
    char *nc, *blanks;
    if (iclient == NULL) return E_INVALIDCLIENT;
    if (iclient->socket == 0) return E_INVALIDSOCKET;
    
    blanks = malloc(1024);
    if (blanks == NULL) return E_NOMEMORY;
    
    // input polling.
    sw = 1;
    #ifdef _IL_WIN_
    ioctlsocket(iclient->socket, FIONBIO, (unsigned long *)&sw);
    #else
    sw = fcntl(iclient->socket, F_GETFL);
    sw |= O_NONBLOCK;
    fcntl(iclient->socket, F_SETFL, sw);
    #endif
    #ifdef _IL_DEBUG
    printf("Pollio Errno before recv: %u\r\n", errno);
    #endif
    rsize = recv(iclient->socket, blanks, 1024, MSG_PEEK);
    #ifdef _IL_DEBUG
    printf("Pollio Errno after recv: %u\r\nRecv return: %d\r\n", errno, rsize);
    #endif
    sw = 0;
    #ifdef _IL_WIN_
    ioctlsocket(iclient->socket, FIONBIO, (unsigned long *)&sw);
    #else
    sw = fcntl(iclient->socket, F_GETFL);
    sw &= ~O_NONBLOCK;
    fcntl(iclient->socket, F_SETFL, sw);
    #endif
    free(blanks);
    if (rsize > 0) {
        if (iclient->inlen == 0 || iclient->inbuf == 0) {
           iclient->inbuf = malloc(rsize);
           if (iclient->inbuf == NULL) {
              return E_NOMEMORY;
           }
           iclient->inlen = rsize;
           memset(iclient->inbuf, 0, rsize);
           ret = recv(iclient->socket, iclient->inbuf, rsize, 0);
           if (ret == SOCKET_ERROR) {
              free(iclient->inbuf);
              iclient->inbuf = NULL;
              iclient->inlen = 0;
              return E_SOCKETERROR;
           }
           iclient->inlen = ret;
        }
        else {
           nc = realloc(iclient->inbuf, rsize+iclient->inlen);
           if (nc == NULL) return E_NOMEMORY;
           iclient->inbuf = nc;
           ret = recv(iclient->socket, iclient->inbuf+iclient->inlen, rsize, 0);
           if (ret == SOCKET_ERROR) {
              nc = realloc(iclient->inbuf, iclient->inlen);
              if (nc != NULL)
                 iclient->inbuf = nc;
              return E_SOCKETERROR;
           }
           iclient->inlen += ret;
        }
    }
    
    //output polling
    
    
    if (iclient->outbuf == NULL || iclient->outlen == 0) return 0;
    int rcount, cur, fclen;
    rcount = 0;
    for (cur=0;cur < iclient->outlen;cur++) {
        if (iclient->outbuf[cur] == '\r') {
           rcount++;
           fclen = cur;
        }
    }
    fclen+=2;
    ret = send(iclient->socket, iclient->outbuf, fclen, 0);
    if (ret == SOCKET_ERROR) return E_SOCKETERROR;
    rcount = ret;
    if (ret < fclen) {
        ret = send(iclient->socket, &iclient->outbuf[ret], fclen-ret, 0);
        if (ret == SOCKET_ERROR) {
           memcpy(iclient->outbuf, iclient->outbuf+rcount, iclient->outlen-rcount);
           nc = realloc(iclient->outbuf, iclient->outlen-rcount);
           if (nc == NULL) return E_SOCKETERROR_NOMEMORY;
           iclient->outbuf = nc;
           iclient->outlen -= rcount;
           return E_SOCKETERROR;
        }
        rcount += ret;
    }
    memcpy(iclient->outbuf, iclient->outbuf+rcount, iclient->outlen-rcount);
    nc = realloc(iclient->outbuf, iclient->outlen-rcount);
    iclient->outlen -= rcount;
    if (iclient->outlen == 0) iclient->outbuf = NULL;
    if (nc == NULL && iclient->outlen != 0) return E_NOMEMORY;
    if (iclient->outlen > 0) iclient->outbuf = nc;
    
    return 0;
}

int irc_pushio(irc_client *iclient, char io, char fb, char *data) {
    char *nc;
    if (!iclient) return E_INVALIDCLIENT;
    if (data == NULL || io > 1 || fb > 1) return E_BADPARAMS;
    if (io) {            // input
       if (iclient->inbuf == NULL) { // if its null, it really doesnt ^$#@^ing matter...
          iclient->inbuf = malloc(strlen(data));
          if (iclient->inbuf == NULL) return E_NOMEMORY;
          memcpy(iclient->inbuf, data, strlen(data));
          iclient->inlen = strlen(data);
          return 0;
       }
       
       if (!fb) {        // back
          nc = realloc(iclient->inbuf, iclient->inlen+strlen(data));
          if (nc == NULL) return E_NOMEMORY;
          iclient->inbuf = nc;
          memcpy(iclient->inbuf+iclient->inlen, data, strlen(data));
          iclient->inlen += strlen(data);
          return 0;
       }
       else {            // front
          nc = realloc(iclient->inbuf, iclient->inlen+strlen(data));
          if (nc == NULL) return E_NOMEMORY;
          iclient->inbuf = nc;
          memmove(iclient->inbuf+strlen(data), iclient->inbuf, iclient->inlen);
          memcpy(iclient->inbuf, data, strlen(data));
          iclient->inlen += strlen(data);
          return 0;
       }
    }
    else {
       if (iclient->outbuf == NULL) { // if its null, it really doesnt ^$#@^ing matter...
          iclient->outbuf = malloc(strlen(data));
          if (iclient->outbuf == NULL) return E_NOMEMORY;
          memcpy(iclient->outbuf, data, strlen(data));
          iclient->outlen = strlen(data);
          return 0;
       }
       
       if (!fb) {        // back
          nc = realloc(iclient->outbuf, iclient->outlen+strlen(data));
          if (nc == NULL) return E_NOMEMORY;
          iclient->outbuf = nc;
          memcpy(iclient->outbuf+iclient->outlen, data, strlen(data));
          iclient->outlen += strlen(data);
          return 0;
       }
       else {            // front
          nc = realloc(iclient->outbuf, iclient->outlen+strlen(data));
          if (nc == NULL) return E_NOMEMORY;
          iclient->outbuf = nc;
          memmove(iclient->outbuf+strlen(data), iclient->outbuf, iclient->outlen);
          memcpy(iclient->outbuf, data, strlen(data));
          iclient->outlen += strlen(data);
          return 0;
       }
    }                         // output
    return 0;
}

int irc_popio(irc_client *iclient, char io, char fb, char **dest) {
    char *nc;
    if (!iclient) return E_INVALIDCLIENT;
    if (io > 1 || fb > 1 || dest == NULL) return E_BADPARAMS;
    *dest = NULL;
    if (io) { // input
        if (iclient->inbuf == NULL || iclient->inlen == 0) return E_EMPTY;
        int pb;
        if (!fb) { // back
            for (pb=3;pb<(iclient->inlen+1);pb++) {
               if (iclient->inbuf[iclient->inlen-pb] == '\n') break;
            }
            if (pb == iclient->inlen) {
               nc = realloc(iclient->inbuf, iclient->inlen+1);
               if (nc == NULL) return E_NOMEMORY;
               nc[iclient->inlen] = 0;
               *dest = nc;
               iclient->inbuf = NULL;
               iclient->inlen = 0;
               return 0;
            }
            *dest = malloc(pb);
            if (*dest == NULL) return E_NOMEMORY;
            memcpy(*dest, (iclient->inbuf+iclient->inlen-pb)+1, pb-1);
            *dest[pb-1] = 0;
            nc = realloc(iclient->inbuf, iclient->inlen-(pb-1));
            iclient->inlen = iclient->inlen-(pb-1);
            if (nc == NULL) return E_NOREALLOC;
            iclient->inbuf = nc;
            iclient->inlen = iclient->inlen-(pb-1);
            return 0;
        }
        else {     // front
            for (pb=0;pb<iclient->inlen;pb++) {
               if (iclient->inbuf[pb] == '\n') break;
            }
            if (iclient->inbuf[pb] != '\n') return E_EMPTY;
            pb++;
            *dest = malloc(pb+1);
            if (*dest == NULL) return E_NOMEMORY;
            memcpy(*dest, iclient->inbuf, pb);
            (*dest)[pb] = 0;
            if (iclient->inlen == pb || iclient->inlen < pb) {
                free(iclient->inbuf);
                iclient->inbuf = NULL;
                iclient->inlen = 0;
            }
            else {
                    memcpy(iclient->inbuf, iclient->inbuf+pb, iclient->inlen-pb);
                    nc = realloc(iclient->inbuf, iclient->inlen-pb);
                    iclient->inlen = iclient->inlen-pb;
                    if (nc == NULL) return E_NOREALLOC;
                    iclient->inbuf = nc;
                }
        }
    }
    else {    // output
        int pb;
        if (iclient->outbuf == NULL) return E_EMPTY;
        if (!fb) { // back
            for (pb=3;pb<(iclient->outlen+1);pb++) {
               if (iclient->outbuf[iclient->outlen-pb] == '\n') break;
            }
            if (pb == iclient->outlen) {
               nc = realloc(iclient->outbuf, iclient->outlen+1);
               if (nc == NULL) return E_NOMEMORY;
               nc[iclient->outlen] = 0;
               *dest = nc;
               iclient->outbuf = NULL;
               iclient->outlen = 0;
               return 0;
            }
            *dest = malloc(pb);
            if (*dest == NULL) return E_NOMEMORY;
            memcpy(*dest, (iclient->outbuf+iclient->outlen-pb)+1, pb-1);
            *dest[pb-1] = 0;
            nc = realloc(iclient->outbuf, iclient->outlen-(pb-1));
            iclient->outlen = iclient->outlen-(pb-1);
            if (nc == NULL) return E_NOREALLOC;
            iclient->outbuf = nc;
            return 0;
        }
        else {     // front
            for (pb=0;pb<iclient->outlen;pb++) {
               if (iclient->outbuf[pb] == '\n') break;
            }
            pb++;
            *dest = malloc(pb+1);
            if (*dest == NULL) return E_NOMEMORY;
            memcpy(*dest, iclient->outbuf, pb);
            *dest[pb] = 0;
            memcpy(iclient->outbuf, iclient->outbuf+pb, iclient->outlen-pb);
            nc = realloc(iclient->outbuf, iclient->outlen-pb);
            iclient->outlen = iclient->outlen-pb;
            if (nc == NULL) return E_NOREALLOC;
            iclient->outbuf = nc;
        }
    }
    return 0;
}

// gotta redo the stuff below
int irc_changenick(irc_client *iclient, const char *nickname) {
    int ret;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!nickname || nickname[0] == '\0') return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    output = malloc(8+strlen(nickname));
    if (output == NULL) return E_NOMEMORY;
    
    strcpy(output, "NICK ");
    strcat(output, nickname);
    strcat(output, "\r\n");
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_sendpass(irc_client *iclient, const char *password) {
    int ret;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!password || !password[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    output = malloc(8+strlen(password));
    if (output == NULL) return E_NOMEMORY;
    strcpy(output, "PASS");
    strcat(output, password);
    strcat(output, "\r\n");
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_register(irc_client *iclient, const char *username, const char *hostname,
                 const char *servername, const char *realname) {
    int ret;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if ((iclient->flags & FLAGS_REGISTERED) != 0) return E_ALREADYREGISTERED;
    if (!username || !hostname || !servername || !realname) return E_BADPARAMS;
    if (!username[0] || !hostname[0] || !servername[0] || !realname[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "USER %s %s %s :%s\r\n", username, hostname, servername, realname);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    iclient->username = malloc(strlen(username)+1);
    if (iclient->username == NULL) return E_NOMEMORY;
    strcpy(iclient->username, username);
    iclient->hostname = malloc(strlen(hostname)+1);
    if (iclient->hostname == NULL) {
        free(iclient->username);
        return E_NOMEMORY;
    }
    strcpy(iclient->hostname, hostname);
    iclient->realname = malloc(strlen(realname)+1);
    if (iclient->realname == NULL) {
        free(iclient->username);
        free(iclient->hostname);
        return E_NOMEMORY;
    }
    strcpy(iclient->realname, realname);
    iclient->servername = malloc(strlen(servername)+1);
    if (iclient->servername == NULL) {
        free(iclient->username);
        free(iclient->hostname);
        free(iclient->realname);
        return E_NOMEMORY;
    }
    strcpy(iclient->servername, servername);
    
    
    return ret;
}

int irc_joinchan(irc_client *iclient, const char *channel) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!channel || !channel[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "JOIN %s\r\n", channel);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_partchan(irc_client *iclient, const char *channel) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!channel || !channel[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "PART %s\r\n", channel);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_privmsg(irc_client *iclient,
                const char *target,
                const char *message) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!target || !target[0] || !message || !message[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "PRIVMSG %s :%s\r\n", target, message);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_notice(irc_client *iclient,
               const char *target,
               const char *message) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!target || !target[0] || !message || !message[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "NOTICE %s :%s\r\n", target, message);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_ctcp(irc_client *iclient, char *target, char *message) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!target || !target[0] || !message || !message[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "PRIVMSG %s :\x001%s\x001\r\n", target, message);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_ctcpr(irc_client *iclient, char *target, char *message) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!target || !target[0] || !message || !message[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "NOTICE %s :\x001%s\x001\r\n", target, message);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_settopic(irc_client *iclient, char *channel, char *topic) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!channel || !channel[0] || !topic || !topic[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "TOPIC %s :%s\r\n", channel, topic);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_setmode(irc_client *iclient, char *target, char *mode) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!target || !target[0] || !mode || !mode[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "MODE %s %s\r\n", target, mode);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_kick(irc_client *iclient, char *channel, char *user, char *message) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!channel || !channel[0] || !user || !user[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    if (!message || !message[0]) asprintf(&output, "KICK %s %s\r\n", channel, user);
    else asprintf(&output, "KICK %s %s :%s\r\n", channel, user, message);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_list(irc_client *iclient, char *params) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    if (!params[0] || !params) asprintf(&output, "LIST\r\n");
    else asprintf(&output, "LIST %s\r\n", params);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_invite(irc_client *iclient, char *user, char *channel) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!channel || !channel[0] || !user || !user[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "INVITE %s %s\r\n", user, channel);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_kill(irc_client *iclient, char *kuser, char *message) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!message || !message[0] || !kuser || !kuser[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "KILL %s %s\r\n", kuser, message);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_quit(irc_client *iclient, char *message) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!iclient->socket) return E_INVALIDSOCKET;
    if (!message || !message[0]) asprintf(&output, "QUIT\r\n");
    
    else asprintf(&output, "QUIT :%s\r\n", message);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_ping(irc_client *iclient, char *param) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!param || !param[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    
    asprintf(&output, "PING %s\r\n", param);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int irc_pong(irc_client *iclient, char *param) {
    int ret = 0;
    char *output = NULL;
    if (!iclient) return E_INVALIDCLIENT;
    if (!param || !param[0]) return E_BADPARAMS;
    if (!iclient->socket) return E_INVALIDSOCKET;
    if (strstr(param, "\r\n") != 0) asprintf(&output, "PONG %s\r\n", param);
    else asprintf(&output, "PONG %s", param);
    ret = irc_pushio(iclient, 0, 0, output);
    free(output);
    
    return ret;
}

int h_irc_ping(irc_client *iclient, const char *data) {   
    int ret;
    char *output;
    if (!data || !data[0]) return E_BADPARAMS;
    if (data[0] == ':') {
    // ok good RFC compliant...
    output = strchr(data, ' ');
    output = strchr(output+1, ' ');
    output += 1;
    }
    else output = 1+strchr(data, ' ');
    if (output == (char *)1) output = NULL;
    
    ret = irc_pong(iclient, output);
    return ret;
}

int d_irc_pmsg(irc_client *iclient, const char *data) { // debug
    int ret;
    char *output, *ctcp;
    int a,b;
    if (!data || !data[0]) return E_BADPARAMS;
    //if (strlen(data+1) < strlen("Sevalecan")) return 0;
    
    //detect if its CTCP
    ctcp = 1+strchr(data, ' ');
    if (ctcp > 1) {
    ctcp = 1+strchr(data, ':');
    if (ctcp > 1 && *ctcp == 0x01) {
        ctcp++;
        if (strncmp(ctcp, "PING", 4) == 0) {
            ctcp[a = (strchr(ctcp, 0x01)-ctcp)] = 0;
            data[b = (strchr(data, '!')-data-1)] = 0;
            irc_ctcp(iclient, data, ctcp);
            ctcp[a] = 0x1;
            ctcp[b] = '!';
            return 0;
        }    
        
    }    
    }    
    
    if (strncmp(data+1, "Sevalecan", 9) != 0 && strncmp(data+1, "theta", 5) != 0 && strncmp(data+1, "[BAF]", 5) != 0) return 0;
    output = strchr(data, ' ');
    output = strchr(output+1, ' ');
    output = strchr(output+1, ' ');
    if (output == NULL) return 0;
    output += 2;
    if (*(output+1) == '\r') return 0;
    if (strncmp(output, "!com", 4) == 0) {
        output += 5;
        if (*output == '\r' || *output == '\n') return 0;
        return irc_pushio(iclient, 0, 0, output);
    }
    return 0;
}

#endif

#include <irclib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    int pv;
    char *bs;
    int ret,x;
    ircr_lst *er;
    char *fp;
    irc_client *test;
    WORD sockVersion;
	WSADATA wsaData;
	
	sockVersion = MAKEWORD(1, 1);
	WSAStartup(sockVersion, &wsaData);
	
	bs = malloc(1024);
	memset(bs, 0, 1024);
	
    test = malloc(sizeof(irc_client));
    memset(test, 0, sizeof(irc_client));
    ret = irc_connect(test, "irc.freenode.net", 6667);
    printf("Connect: %u\r\n", ret);
    if (ret != 0) return 1;
    sleep(1000);
    ret = irc_changenick(test, "Sevaletest");
    printf("Nick Change: %u\r\n", ret);
    ret = irc_pollio(test);
    sleep(1000);
    irc_register(test, "a", "b", "c", "d");
    irc_pollio(test);
    irc_joinchan(test, "#allegro");
    irc_pollio(test);
    /*
    Sleep(1000);
    irc_privmsg(test, "#allegro", "Sup ma bitches? I AM NOW BUGLESS");
    for (x=0;x<10;x++) {
    irc_pollio(test);
    Sleep(1000);
    }
    */
    ret = 0;
    while (1) {
        irc_pollio(test);
        ret = irc_popio(test, 1, 1, &fp);
        if (ret == 0) {
            printf("%s", fp);
            if (strstr(fp, "\r\n") != NULL) {
                er = irc_handle_r(test, _defhlist, fp);
                if (er != NULL) {
                    if (er->errc > 0) {
                        for (pv=0;pv<er->errc;pv++) {
                            printf("Handling failed:\r\n");
                            printf("Function: %p\r\nHandles: %s\r\nError Value: %u\r\n\r\n", er->list[pv].irc_rfpointer, er->list[pv].com, er->list[pv].errv);
                        }    
                    }
                    irc_free_erl(er);
                    er = NULL;
                }    
            }
            free(fp);
        }
        sleep(20);
    }
    
    irc_quit(test, NULL);
    irc_pollio(test);
    irc_disconnect(test);
    free(test);
    free(bs);
    WSACleanup();
    
    return 0;
}



/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2013 EIA Electronics
 *
 * Authors:
 * Kurt Van Dijck <kurt.van.dijck@eia.be>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the version 2 of the GNU General Public License
 * as published by the Free Software Foundation
 */

#include <errno.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <err.h>
#include <getopt.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/j1939.h>

/* main */
int main(int argc, char *argv[])
{
	int ret, sock, opt;
	unsigned int j;
	int verbose = 0;
	socklen_t peernamelen;
	struct sockaddr_can sockname, peername;
    sockname.can_family = AF_CAN;
    sockname.can_ifindex = if_nametoindex("can0");
    sockname.can_addr.j1939.addr = 0x80;
    sockname.can_addr.j1939.name = J1939_NO_NAME;
    sockname.can_addr.j1939.pgn = 0x4900;

    peername.can_family = AF_CAN;
    peername.can_ifindex = if_nametoindex("can0");
    peername.can_addr.j1939.addr = 0x80;
    peername.can_addr.j1939.name = J1939_NO_NAME;
    peername.can_addr.j1939.pgn = 0x4900;
	// uint8_t dat[128];
	uint8_t dat[4096];
	int valid_peername = 0;
	unsigned int todo_send = 0;
	int todo_recv = 0, todo_echo = 0, todo_prio = -1;
	int todo_connect = 0, todo_names = 0, todo_wait = 0, todo_rebind = 0;
	int todo_broadcast = 0, todo_promisc = 0;
	int no_bind = 0;

	// printf("todo_promisc --\n");
	printf("peer-addr:%d,name:%d,pgn:%d,\n",peername.can_addr.j1939.addr,peername.can_addr.j1939.name,peername.can_addr.j1939.pgn);

	/* open socket */
	if (verbose)
		fprintf(stderr, "- socket(PF_CAN, SOCK_DGRAM, CAN_J1939);\n");
	//russell:设置socket为can_j1939
	sock = ret = socket(PF_CAN, SOCK_DGRAM, CAN_J1939);
	if (ret < 0)
		err(1, "socket(j1939)");

	printf("todo_broadcast --\n");
	ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
				&todo_broadcast, sizeof(todo_broadcast));
	if (ret < 0)
		err(1, "setsockopt: filed to set broadcast");



	printf("bind --\n");
	ret = bind(sock, (void *)&sockname, sizeof(sockname));
	if (ret < 0)
		err(1, "bind()");

	/* main loop */
	if ((todo_echo || todo_recv) && verbose)
		fprintf(stderr, "- while (1)\n");


	peernamelen = sizeof(peername);
	printf("peer---addr:%d,name:%d,pgn:%d,\n",peername.can_addr.j1939.addr,peername.can_addr.j1939.name,peername.can_addr.j1939.pgn);

	ret = recvfrom(sock, dat, sizeof(dat), 0,
			(void *)&peername, &peernamelen);

	if (todo_recv) {
		int i;

		if (todo_names && peername.can_addr.j1939.name)
			printf("%016llx ", peername.can_addr.j1939.name);
		printf("%02x %05x:", peername.can_addr.j1939.addr,
				peername.can_addr.j1939.pgn);
		for (i = 0, j = 0; i < ret; ++i, j++) {
			if (j == 8) {
				printf("\n%05x    ", i);
				j = 0;
			}
			printf(" %02x", dat[i]);
		}
		printf("\n");
	}
	// }
	if (todo_wait)
		for (;;)
			sleep(1);
	return 0;
}


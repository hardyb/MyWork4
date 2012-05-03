/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: example-broadcast.c,v 1.3 2010/11/06 15:03:48 adamdunkels Exp $
 */

/**
 * \file
 *         Testing the broadcast layer in Rime
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "net/rime.h"
#include "random.h"

#include "dev/button-sensor.h"

#include "dev/leds.h"

#include <stdio.h>

#include "RoutingAndAggregation.h"

#define MAX_RETRANSMISSIONS 4
#define NUM_HISTORY_ENTRIES 4
#define THE_NODE_CONSTRAINT 4

static unsigned char nodeConstraint;


static struct RoutingData moduleRD;

static unsigned short if1;
static unsigned short if2;
static unsigned short u16;


struct newNeighbor
{
struct newNeighbor* next;
unsigned short interfaceName;
};

struct newMessage
{
struct newMessage* next;
rimeaddr_t interface;
unsigned char message[MESSAGE_SIZE];
};





MEMB(newNeighbors_memb, struct newNeighbor, 20);
MEMB(newMessages_memb, struct newMessage, 20);

LIST(new_neighbors);
LIST(new_messages);



/* ========================================================================= */
/* Declare processes */
/* ========================================================================= */
PROCESS(example_broadcast_process, "Broadcast example");
PROCESS(runicast_process, "Runicast Process");
PROCESS(handle_messages_process, "Message Process");
AUTOSTART_PROCESSES(&example_broadcast_process, &runicast_process, &handle_messages_process);



/* ========================================================================= */
/* Connection structures */
/* ========================================================================= */
static struct broadcast_conn broadcast;
static struct runicast_conn runicast;




/* ========================================================================= */
/* Call backs, Polls and other Functions */
/* ========================================================================= */

static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
  struct newMessage *m;

  printf("broadcast message received from %d.%d: ''\n",
         from->u8[0], from->u8[1]);

//u16 = ((int)from->u8[0] << 8) | (int)from->u8[1];

/* Initially just asume its a neighbour message*/
	//InsertInterfaceNode(&(moduleRD.interfaceTree), u16);
	//printf("Inserted interface\n");

/* Neighbour message was broadcast so tell them about us */
    m = memb_alloc(&newMessages_memb);
	//m->interface = u16;
	rimeaddr_copy(&(m->interface), from); 
	memcpy(m->message, (char*)packetbuf_dataptr(), paketbuf_datalen());
    list_add(new_messages, m);
    printf("Added message to list\n");
 

}


static void recv_runicast(struct runicast_conn *c, const rimeaddr_t *from, uint8_t seqno)
{
	printf("runicast message received from %d.%d, seqno %d\n", from->u8[0], from->u8[1], seqno);

    m = memb_alloc(&newMessages_memb);
	rimeaddr_copy(&(m->interface), from); 
	memcpy(m->message, (char*)packetbuf_dataptr(), paketbuf_datalen());
    list_add(new_messages, m);
    printf("Added message to list\n");

}
static void sent_runicast(struct runicast_conn *c, const rimeaddr_t *to, uint8_t retransmissions)
{
  printf("runicast message sent to %d.%d, retransmissions %d\n",
	 to->u8[0], to->u8[1], retransmissions);
}
static void timedout_runicast(struct runicast_conn *c, const rimeaddr_t *to, uint8_t retransmissions)
{
  printf("runicast message timed out when sending to %d.%d, retransmissions %d\n",
	 to->u8[0], to->u8[1], retransmissions);
}




static void send_message(unsigned short _interface, char* _msg)
{
	static rimeaddr_t iface;

	packetbuf_copyfrom(_msg, MESSAGE_SIZE);
	iface.u8[0] = (unsigned char)(_interface >> 8);
	iface.u8[1] = (unsigned char)(_interface & 0xFF);

	printf("%u.%u: sending runicast to address %u.%u\n",
	rimeaddr_node_addr.u8[0],
	rimeaddr_node_addr.u8[1],
	iface.u8[0],
	iface.u8[1]);
	runicast_send(&runicast, &iface, MAX_RETRANSMISSIONS);

}

static void bcast_message(char* _msg)
{
	packetbuf_copyfrom(_msg, MESSAGE_SIZE);
	printf("%u.%u: sending broadcast\n",
	rimeaddr_node_addr.u8[0],
	rimeaddr_node_addr.u8[1]);
	broadcast_send(&broadcast);

}


static void handle_application_data(char* _msg)
{
	// work still to do here	
	// packetbuf_copyto(_msg, MESSAGE_SIZE);


}









static void
messagehandler(void)
{
	static struct newMessage* mm;
	static unsigned short inf;

	mm = list_pop(new_messages);
	if ( mm != 0 )
	{
		printf("Processing a message\n");
		inf = ((int)mm->interface->u8[0] << 8) | (int)mm->interface->u8[1];
		handle_message(mm->message, inf);
		memb_free(&newMessages_memb, mm);
	}

  process_poll(&handle_messages_process);
}


/* ========================================================================= */
/* Call back structures */
/* ========================================================================= */
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static const struct runicast_callbacks runicast_callbacks = {recv_runicast,
							     sent_runicast,
							     timedout_runicast};




/* ========================================================================= */
/* The actual processes */
/* ========================================================================= */


PROCESS_THREAD(handle_messages_process, ev, data)
{
  PROCESS_POLLHANDLER(messagehandler());
  PROCESS_EXITHANDLER(exithandler());
  PROCESS_BEGIN();

  /*
   * initializing  stuff
   */

  process_poll(&handle_messages_process);

  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_EXIT);
  /*
   * do any end bits
   */
  PROCESS_END();
}




PROCESS_THREAD(runicast_process, ev, data)
{
/*  static struct etimer et;*/
  static rimeaddr_t recv;
  static rimeaddr_t iface;
  static struct newNeighbor* nn;
  static struct etimer et;

  PROCESS_EXITHANDLER(runicast_close(&runicast);)

  PROCESS_BEGIN();

  runicast_open(&runicast, 144, &runicast_callbacks);
  printf("Opened runicast in runicast process\n");

while(1)
{
	/*PROCESS_WAIT_UNTIL(list_length(new_neighbors) > 0 && !runicast_is_transmitting(&runicast));*/
	etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

if ( !runicast_is_transmitting(&runicast) )/*list_length(new_neighbors) > 0*/
{
    printf("About to check list\n");
	nn = list_pop(new_neighbors);
	if ( nn != 0 )
{
    printf("About to runicast_send\n");
	packetbuf_copyfrom("Hello", 5);

	/* Will this work - interface name is just an unsigned short not a rime addr */
	iface.u8[0] = (unsigned char)(nn->interfaceName >> 8);
	iface.u8[1] = (unsigned char)(nn->interfaceName & 0xFF);
	rimeaddr_copy(&recv, &iface); 

	printf("%u.%u: sending runicast to address %u.%u\n",
	rimeaddr_node_addr.u8[0],
	rimeaddr_node_addr.u8[1],
	recv.u8[0],
	recv.u8[1]);

	runicast_send(&runicast, &recv, MAX_RETRANSMISSIONS);
	memb_free(&newNeighbors_memb, nn);
}
}

}




  PROCESS_END();
}


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();
	moduleRD.grTree = NULL;
	moduleRD.interfaceTree = NULL;
	moduleRD.stateTree = NULL;
	moduleRD.kdRoot = NULL;
	rd = &moduleRD;
	nodeConstraint = THE_NODE_CONSTRAINT;

	if1 = 0;
	if2 = 0;

	broadcast_open(&broadcast, 129, &broadcast_call);

	setMessageCallBack(send_message);
	setBroadcastCallBack(bcast_message);
	setApplicationCallBack(handle_application_data);
	weAreSourceFor(4);
	weAreSinkFor(3);
	StartUp();



	etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

	packetbuf_copyfrom("Hello", 5);
	broadcast_send(&broadcast);
	printf("broadcast message sent\n");

  while(1) {

    /* Delay 2-4 seconds */
	etimer_set(&et, CLOCK_SECOND);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	/*PROCESS_WAIT_EVENT();*/
    printf("Bcast Process timer expired\n");

	struct InterfaceNode* i;
	i = FindInterfaceNode(moduleRD.interfaceTree, 256);
	if ( i )
	{
		printf("Found    : %u\n", i->i->iName);
	}
	else
	{
		printf("NOT Found: %u\n", i->i->iName);
	}
	
	i = FindInterfaceNode(moduleRD.interfaceTree, 512);
	if ( i )
	{
		printf("Found    : %u\n", i->i->iName);
	}
	else
	{
		printf("NOT Found: %u\n", i->i->iName);
	}

	i = FindInterfaceNode(moduleRD.interfaceTree, 768);
	if ( i )
	{
		printf("Found    : %u\n", i->i->iName);
	}
	else
	{
		printf("NOT Found: %u\n", i->i->iName);
	}



    //packetbuf_copyfrom("Hello", 5);
    //broadcast_send(&broadcast);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
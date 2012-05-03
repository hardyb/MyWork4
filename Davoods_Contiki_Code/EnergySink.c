//getvalues and print using printf
#include "contiki.h"
#include "net/rime.h"
#include "random.h"

#include "dev/button-sensor.h"

#include "dev/leds.h"

#include <stdio.h>




static char messageSet[80][20] =
{
"value,1.0,1000, end",
"value,1.0,1100, end",
"value,1.0,1200, end",
"value,1.0,1300, end",
"value,1.0,1400, end",
"value,1.0,1500, end",
"value,1.0,1600, end",
"value,1.0,1700, end",
"value,1.0,1800, end",
"value,1.0,1900, end",
"value,1.0,1800, end",
"value,1.0,1700, end",
"value,1.0,1600, end",
"value,1.0,1500, end",
"value,1.0,1400, end",
"value,1.0,1300, end",
"value,1.0,1200, end",
"value,1.0,1100, end",
"value,1.0,1200, end",
"value,1.0,1300, end",
"value,2.0,2000, end",
"value,1.0,1000, end",
"value,2.0,2100, end",
"value,1.0,1100, end",
"value,2.0,2200, end",
"value,1.0,1200, end",
"value,2.0,2300, end",
"value,1.0,1300, end",
"value,2.0,2400, end",
"value,1.0,1400, end",
"value,2.0,2500, end",
"value,1.0,1500, end",
"value,2.0,2600, end",
"value,1.0,1600, end",
"value,2.0,2700, end",
"value,1.0,1700, end",
"value,2.0,2800, end",
"value,1.0,1800, end",
"value,2.0,2900, end",
"value,1.0,1900, end",
"value,2.0,2800, end",
"value,1.0,1800, end",
"value,2.0,2700, end",
"value,1.0,1700, end",
"value,2.0,2600, end",
"value,1.0,1600, end",
"value,2.0,2500, end",
"value,1.0,1500, end",
"value,2.0,2400, end",
"value,1.0,1400, end",
"value,2.0,2300, end",
"value,1.0,1300, end",
"value,2.0,2200, end",
"value,1.0,1200, end",
"value,2.0,2100, end",
"value,1.0,1100, end",
"value,2.0,2200, end",
"value,1.0,1200, end",
"value,2.0,2300, end",
"value,1.0,1300, end",
"value,3.0,3000, end",
"value,3.0,3100, end",
"value,3.0,3200, end",
"value,3.0,3300, end",
"value,3.0,3400, end",
"value,3.0,3500, end",
"value,3.0,3600, end",
"value,3.0,3700, end",
"value,3.0,3800, end",
"value,3.0,3900, end",
"value,3.0,3800, end",
"value,3.0,3700, end",
"value,3.0,3600, end",
"value,3.0,3500, end",
"value,3.0,3400, end",
"value,3.0,3300, end",
"value,3.0,3200, end",
"value,3.0,3100, end",
"value,3.0,3200, end",
"value,3.0,3300, end"
};




/*---------------------------------------------------------------------------*/
PROCESS(example_broadcast_process, "Broadcast example");
AUTOSTART_PROCESSES(&example_broadcast_process);
/*---------------------------------------------------------------------------*/
typedef struct{
unsigned int id;
signed long value;
}pkt;

static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
//pkt inpacket;
//memcpy(&inpacket,packetbuf_dataptr(),sizeof(pkt));
//if(inpacket.id == 1){
//  printf("value,%d.%d,%li,end\n",
//         from->u8[0], from->u8[1], inpacket.value);
//}
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_broadcast_process, ev, data)
{
	static struct etimer et;
	static int i = 0;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  broadcast_open(&broadcast, 129, &broadcast_call);

  while(1) {

    /* Delay 2-4 seconds */
    etimer_set(&et, CLOCK_SECOND );

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

	printf("%s\n", messageSet[i]);
	i++;
	if ( i > 79 )
	{
	i = 0;
	}

   // printf("I am alive\n");
  }

  PROCESS_END();
}









/*---------------------------------------------------------------------------*/
/******************************************************************************/
#include <stdio.h>

#include "host.h"
#include "util.h"
#include "pipe.h"

/*
 * we need to show the packets that come to our network "stack"
 */
void dump_packets(void)
{
	
}

int main(void)
{
	/* 
	 * start named pipe, this is where the host will receive user commands.
	 * it will be a producer/consumer design. pipe name should be passed as
	 * command-line argument
	 */
	create_pipe(PIPE_NAME);
	printf("Pipe created.\n");

	/*
	 * open a socket to do the communication. packet transaction will be 
	 * simulated above a normal connection.
	 */

	/*
	 * once connection is stablished we can start the SIM STATE MACHINE.
	 * our state machine will start in CLOSED 
	 */

	/* loop until gets work to do */
	while (TRUE)
	{
		/* get work */

		/* 
		 * depending on the packet we receive do the work. also this 
		 * depends on the state machine.
		 *
		 * for now only handle handshake
		 */
		{
			/* SYN packet */

			/* RST packet */

			/* ACK packet */
		}
			 
	}

}

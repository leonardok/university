/******************************************************************************/
#include <stdio.h>

#include "host.h"
#include "util.h"

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

	/*
	 * open a socket to do the communication. packet transaction will be 
	 * simulated above a normal connection.
	 */

	/*
	 * once connection is stablished we can start the SIM STATE MACHINE.
	 * our state machine will start in CLOSED and will chnage
	 * when a SYN_PKG is received.
	 */

	/* loop until gets work to do */
	while (TRUE)
	{
		/* get work */

		/* execute work */
	}

}

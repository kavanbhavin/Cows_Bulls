#include "bsp.h"
#include "mrfi.h"
#include "radios/family1/mrfi_spi.h"
#include <string.h>
#include "uart_utility.h"

/* Useful #defines */
#define RED_SEND_LED 		0x01

int buffer_ready=0;
int current_index =0;
mrfiPacket_t 	packet;
int finished_turn;

void main(void){
	int status;
	/* Perform board-specific initialization */
	BSP_Init();
	
	/* Initialize minimal RF interface, wake up radio */
	MRFI_Init();
	MRFI_WakeUp();
	init_uart();
	packet.frame[13]='\n';
	/* Construct a packet to send over the radio.
		 * 
		 *  Packet frame structure:
		 *  ---------------------------------------------------
		 *  | Length (1B) | Dest (4B) | Source (4B) | Payload |
		 *  ---------------------------------------------------
		 */

		/* First byte of packet frame holds message length in bytes */
	packet.frame[0] = 5 + 8;	/* Includes 8-byte address header */
		
		/* Next 8 bytes are addresses, 4 each for source and dest. */
	packet.frame[1] = 0x12;		/* Destination */
	packet.frame[2] = 0x34;
	packet.frame[3] = 0xab;
	packet.frame[4] = 0xcd;
		
	packet.frame[5] = 0x02;		/* Source */
	packet.frame[6] = 0x00;
	packet.frame[7] = 0x01;
	packet.frame[8] = 0x02;
	/* Enable  USCI_A0 RX  interrupt   */
	IE2    |=  UCA0RXIE;
	__bis_SR_register(GIE);   //interrupts  enabled
	while(1){
		if(buffer_ready){
			status = MRFI_Transmit(&packet , MRFI_TX_TYPE_FORCED);
			buffer_ready = 0;
			if(status == MRFI_TX_RESULT_FAILED){
				uart_puts("Failure to transmit");
			}
		}else{
			__no_operation();
		}
	}
}

/* Function to execute upon receiving a packet
 *   Called by the driver when new packet arrives */
void MRFI_RxCompleteISR(void) {}

/*  Echo    back    RXed    character,  confirm TX  buffer  is  ready   first   */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void    USCI0RX_ISR(void)
{
	packet.frame[9+current_index] = UCA0RXBUF;
	if(current_index==3){
		current_index=0;
		buffer_ready = 1;
		/* Disnable  USCI_A0 RX  interrupt   */
		IE2    &=  ~UCA0RXIE;
	}else{
		current_index++;
	}
}

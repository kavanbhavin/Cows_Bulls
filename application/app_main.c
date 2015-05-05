#include "bsp.h"
#include "mrfi.h"
#include "radios/family1/mrfi_spi.h"
#include <string.h>
#include "uart_utility.h"
#include "cows_bulls_model.h"

/* Useful #defines */
#define RED_SEND_LED 		0x01
#define ENABLE_READING_INTERRRUPT() IE2    |=  UCA0RXIE


int buffer_ready=0;
int current_index =0;
int received_packet=0;
char guess[4];
mrfiPacket_t 	guess_packet;
mrfiPacket_t	guess_response_packet;
mrfiPacket_t	incoming_packet;

void play_game(){
	while(1){
		if(buffer_ready){
			status =MRFI_Transmit(&guess_packet , MRFI_TX_TYPE_FORCED);
			buffer_ready = 0;
			if(status == MRFI_TX_RESULT_FAILED){
				uart_puts("Failure to transmit");
			}
			ENABLE_READING_INTERRRUPT();
			while(!received_packet) __no_operation();
			send_response_packet();
		}else __no_operation();
	}
}

void send_response_packet(){
	int i, status;
	for(i=0; i<4; i++){
		guess[i] = packet[10+i];
	}
	result_t result = evaluate_guess(guess);
	guess_response_packet[10] = result.correct_digits;
	guess_response_packet[11] = result.digits_in_wrong_places;
	status = MRFI_Transmit(&guess_response_packet , MRFI_TX_TYPE_FORCED);
	if(status == MRFI_TX_RESULT_FAILED){
				uart_puts("Failure to transmit");
	}
}

void main(void){
	int status;
	/* Perform board-specific initialization */
	BSP_Init();
	
	/* Initialize minimal RF interface, wake up radio */
	MRFI_Init();
	MRFI_WakeUp();
	init_uart();
	/* Construct a packet to send over the radio.
	* 
	*  Packet frame structure:
	*  ----------------------------------------------------------------------
	*  | Length (1B) | Dest (4B) | Source (4B) | Packet Type (1B) | Payload |
	*  ----------------------------------------------------------------------
	*/
	/* For our payload the first byte will be a character that represents
	* if the packet is a guess-response packet or a guess packet
	* R will represent a response packet while, G will represent a guess packet
	* For a response packet, the second byte will be the number of correct digits
	* and the third byte will be the number of digits that were in the guess,
	* but not in the right position
	* For the guess packet there will just be four bytes containing the guesses
	*/


	/* First byte of packet frame holds message length in bytes */
	guess_packet.frame[0] = 5 + 8;	/* Includes 8-byte address header TODO FIX THIS */
		
	/* Next 8 bytes are addresses, 4 each for source and dest. */
	guess_packet.frame[1] = 0x12;		/* Destination */
	guess_packet.frame[2] = 0x34;
	guess_packet.frame[3] = 0xab;
	guess_packet.frame[4] = 0xcd;
		
	guess_packet.frame[5] = 0x02;		/* Source */
	guess_packet.frame[6] = 0x00;
	guess_packet.frame[7] = 0x01;
	guess_packet.frame[8] = 0x02;
	guess_packet.frame[9] = 'G';

	guess_response_packet.frame[0] = 3+8;
	guess_response_packet.frame[1] = 0x12;		/* Destination */
	guess_response_packet.frame[2] = 0x34;
	guess_response_packet.frame[3] = 0xab;
	guess_response_packet.frame[4] = 0xcd;
		
	guess_response_packet.frame[5] = 0x02;		/* Source */
	guess_response_packet.frame[6] = 0x00;
	guess_response_packet.frame[7] = 0x01;
	guess_response_packet.frame[8] = 0x02;
	guess_response_packet.frame[9] = 'R';

	/* Enable  USCI_A0 RX  interrupt   */
	IE2    |=  UCA0RXIE;
	__bis_SR_register(GIE);   //interrupts  enabled
	while(1){
		if(buffer_ready){
			char code[4];
			for(int i=0; i<4; i++){
				code[i] = guess_packet.frame[10+i];
			}
			set_code(code);
			ENABLE_READING_INTERRRUPT();
			play_game();
		}else __no_operation();
	}
}

void process_guess(){
	uart_putc(incoming_packet.frame[10]);
	uart_puts(" correct digits\n");
	uart_putc(incoming_packet.frame[11]);
	uart_puts(" digits in code but not write place\n");
}


/* Function to execute upon receiving a packet
 *   Called by the driver when new packet arrives */
void MRFI_RxCompleteISR(void) {
	MRFI_Receive(&incoming_packet);
	/*Check what kind of packet it is*/
	if(incoming_packet.frame[9] == 'G'){
		received_packet = 1;
	}
	if(incoming_packet.frame[9] != 'R'){
		/*Some garbage packet so just return*/
		return;
	}
	/* We have received a response for one of our guesses */
	process_guess();
}

/*  Echo    back    RXed    character,  confirm TX  buffer  is  ready   first   */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void    USCI0RX_ISR(void)
{
	guess_packet.frame[10+current_index] = UCA0RXBUF;
	if(current_index==3){
		current_index=0;
		buffer_ready = 1;
		/* Disable  USCI_A0 RX  interrupt   */
		IE2    &=  ~UCA0RXIE;
	}else{
		current_index++;
	}
}

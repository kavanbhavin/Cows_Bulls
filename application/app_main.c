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
int received_evaluation = 0;
int other_msp_is_awake =0;
char guess[4];

int opponent_won=0;
int we_won=0;

mrfiPacket_t 	guess_packet;
mrfiPacket_t	guess_response_packet;
/* The incoming packet from the other player */
mrfiPacket_t	incoming_packet;

void send_response_packet(){
	int status;
	status = MRFI_Transmit(&guess_response_packet , MRFI_TX_TYPE_FORCED);
	if(status == MRFI_TX_RESULT_FAILED){
				uart_puts("Failure to transmit");
	}
	received_packet = 0;
}


void play_game(){
	int status;
	uart_puts("Enter your guess\n");
	while(1){
		if(buffer_ready){
			received_evaluation = 0;
			status =MRFI_Transmit(&guess_packet , MRFI_TX_TYPE_FORCED);
			buffer_ready = 0;
			if(status == MRFI_TX_RESULT_FAILED){
				uart_puts("Failure to transmit");
			}
			ENABLE_READING_INTERRRUPT();
			while(!received_packet) __no_operation();
			send_response_packet();
			while(!received_evaluation) __no_operation();
			if(!opponent_won && !we_won){
				uart_puts("Enter your guess\n");
				continue;
			}
			if(opponent_won && we_won){
				uart_puts("Draw\n");
				return;
			}
			if(opponent_won){
				uart_puts("You lost\n");
				return;
			}
			if(we_won){
				uart_puts("You won\n");
				return;
			}
		}else __no_operation();
	}
}

void reset_state(){
	int i;
	opponent_won = 0;
	we_won = 0;
	current_index = 0;
	for(i=0; i<4; i++){
		buffer[i] = 0;
	}
	for(i=0; i<5000; i++){
		__no_operation();
	}
}

void main(void){
	int i, status;
	uint8_t address[]= {192,168,87,14};
	mrfiPacket_t ping;
	WDTCTL =   WDTPW   +   WDTHOLD;
	init_uart();
	/* Perform board-specific initialization */
	BSP_Init();
	
	/* Initialize minimal RF interface, wake up radio */
	MRFI_Init();
	MRFI_WakeUp();
	/* Construct a packet to send over the radio.
	* 
	*  Packet frame structure:
	*  ----------------------------------------------------------------------
	*  | Length (1B) | Dest (4B) | Source (4B) | Packet Type (1B) | Payload |
	*  ----------------------------------------------------------------------
	*/
	/* For our payload the first byte will be a character that represents
	* if the packet is a guess-response packet or a guess packet, or a ping packet
	* R will represent a response packet while, G will represent a guess packet
	* For a response packet, the second byte will be the number of correct digits
	* and the third byte will be the number of digits that were in the guess,
	* but not in the right position
	* For the guess packet there will just be four bytes containing the guesses
	*/


	/* First byte of packet frame holds message length in bytes */
	/* Set a filter address for packets received by the radio
	 *   This should match the "destination" address of
	 *   the packets sent by the transmitter. */
	/* Attempt to turn on address filtering
	 *   If unsuccessful, turn on both LEDs and wait forever */
	status = MRFI_SetRxAddrFilter(address);	
	if(status != 0){
		uart_puts("Error turning on filter\n");
	}
	MRFI_EnableRxAddrFilter();
	/* Turn on the radio receiver */
	MRFI_RxOn();
	/* Next 8 bytes are addresses, 4 each for source and dest. */
	guess_packet.frame[0] = 5 + 8;
	guess_packet.frame[1] = 192;		/* Destination */
	guess_packet.frame[2] = 168;
	guess_packet.frame[3] = 87;
	guess_packet.frame[4] = 31;
		
	guess_packet.frame[5] = 192;		/* Source */
	guess_packet.frame[6] = 168;
	guess_packet.frame[7] = 87;
	guess_packet.frame[8] = 14;
	guess_packet.frame[9] = 'G';

	guess_response_packet.frame[0] = 3+8;
	guess_response_packet.frame[1] = 192;		/* Destination */
	guess_response_packet.frame[2] = 168;
	guess_response_packet.frame[3] = 87;
	guess_response_packet.frame[4] = 31;
		
	guess_response_packet.frame[5] = 192;		/* Source */
	guess_response_packet.frame[6] = 168;
	guess_response_packet.frame[7] = 87;
	guess_response_packet.frame[8] = 14;
	guess_response_packet.frame[9] = 'R';
	
	ping.frame[0] = 13;
	ping.frame[1] = 192;		/* Destination */
	ping.frame[2] = 168;
	ping.frame[3] = 87;
	ping.frame[4] = 31;
		
	ping.frame[5] = 192;		/* Source */
	ping.frame[6] = 168;
	ping.frame[7] = 87;
	ping.frame[8] = 14;
	ping.frame[9] = 'P';
	for(i=10; i<=13; i++){
		ping.frame[i] = 'K';
	}

	/* Enable  USCI_A0 RX  interrupt   */
	IE2    |=  UCA0RXIE;
	__bis_SR_register(GIE);   //interrupts  enabled
	uart_puts("Connecting...\n");
	while(!other_msp_is_awake){
		status = MRFI_Transmit(&ping, MRFI_TX_TYPE_FORCED);
		if(status == MRFI_TX_RESULT_FAILED){
			uart_puts("Failure to transmit");
		}
		for(i=0; i<=5000; i++){
			__no_operation();
		}
	}
	for(i=0; i<=1000; i++){
		status = MRFI_Transmit(&ping, MRFI_TX_TYPE_FORCED);
		if(status == MRFI_TX_RESULT_FAILED){
			uart_puts("Failure to transmit");
		}
		for(i=0; i<=5000; i++){
			__no_operation();
		}
	}
	uart_puts("Connected\n");
	uart_puts("Enter your code\n");
	while(1){
		if(buffer_ready){
			char code[4];
			for(i=0; i<4; i++){
				code[i] = guess_packet.frame[10+i];
			}
			set_code(code);
			buffer_ready=0;
			ENABLE_READING_INTERRRUPT();
			play_game();
			uart_puts("Game over\n");
			reset_state();
			uart_puts("Enter your code\n");
		}else __no_operation();
	}
}

void process_opponent_response(){
	uart_putc(incoming_packet.frame[10]);
	uart_puts(" correct digits\n");
	uart_putc(incoming_packet.frame[11]);
	uart_puts(" digits in code but not write place\n");
	received_evaluation = 1;
	if(incoming_packet.frame[10]=='4'){
		we_won = 1;
	}
}

void process_response_packet(){
	int i;
	result_t result;
	for(i=0; i<4; i++){
		guess[i] = incoming_packet.frame[10+i];
	}
	result = evaluate_guess(guess);
	guess_response_packet.frame[10] = '0'+result.correct_digits;
	guess_response_packet.frame[11] = '0'+result.digits_in_wrong_places;
	if(result.correct_digits == 4){
		opponent_won =1;
	}
}

/* Function to execute upon receiving a packet
 *   Called by the driver when new packet arrives */
void MRFI_RxCompleteISR(void) {
	MRFI_Receive(&incoming_packet);
	/*Check what kind of packet it is*/
	if(incoming_packet.frame[9] == 'P'){
		other_msp_is_awake ++;
		return;
	}
	if(incoming_packet.frame[9] == 'G'){
		process_response_packet();
		received_packet = 1;
		return;
	}
	if(incoming_packet.frame[9] != 'R'){
		/*Some garbage packet so just return*/
		return;
	}
	/* We have received a response for one of our guesses */
	process_opponent_response();
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

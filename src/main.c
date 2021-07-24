#include "TYPES.h"

#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "USART_INTERFACE.h"
#include "NVIC_INTERFACE.h"
#include "DELAY_INTERFACE.h"
#include "MADC_interface.h"

#include "ESP8266_INTERFACE.h"


int main ( void ){



	/* Initialize RCC to work with 8MHz */
	MRCC_VidInit();

	/* Enable USART 1 */
	MRCC_VidEnablePeripheralClock( APB2_BUS , USART1_RCC );

	/* Enable ADC 1 */
	MRCC_VidEnablePeripheralClock( APB2_BUS , ADC1_RCC );

	/* Enable GPIOA */
	MRCC_VidEnablePeripheralClock( APB2_BUS , GPIOA_RCC  );

	/* Enable GPIOA */
		MRCC_VidEnablePeripheralClock( APB2_BUS , AFIO_RCC  );

		MNVK_EnableInt(18); //enable NVIC interrupt for ADC1 & ADC2
			MADC_init();

	/* Configure A9  (Tx1) as Output AFPP @ 2MHz */
	MGPIO_VidSetPinDirection  ( GPIOA , PIN9 , OUTPUT_SPEED_2MHZ_AFPP ) ;

	/* Configure A10 (RX1) as input Floating     */
	MGPIO_VidSetPinDirection  ( GPIOA , PIN10 , INPUT_FLOATING        ) ;

	/* Configure A0  (A0) as INPUT ANALOG */
	MGPIO_VidSetPinDirection  ( GPIOA , PIN0 , INPUT_ANLOG ) ;

	/* Enable NVIC For USART1 */
	MNVIC_VidSetPriority      ( USART1 , 1 , NO_SUB_PRIORITY , GROUP3 ) ;
	MNVIC_VidEnablePeripheral ( USART1                                ) ;

	/*Initialize ADC*/
	ADC1_voidInit();

	/* Initialize UART */
	MUSART_VidInit();

	/* Setting ESP8266 Mode */
	ESP8266_VidInit();

	/* Connecting To WIFI Network */
	ESP8266_VidConnectToWiFi( (u8 *)"OPPO F7" , (u8 *)"53741023" );
	while(1){

		u8 IR_value=0;
		IR_value=MADC1_getdata();
		IR_value=9462/(IR_value-16.92);
		while(IR_value>20)
		{
		/* Connecting To thingspeak.com */
		ESP8266_VidConnectToSrvTcp( (u8 *)"api.thingspeak.com" , (u8 *)"80");
		_delay_ms(2000);

		ESP8266_VidSendHttpReq( "GET https://api.thingspeak.com/update?api_key=09WX4JS2V5GVQKYL","1","80");

		}
		/* Connecting To thingspeak.com */
		ESP8266_VidConnectToSrvTcp( (u8 *)"api.thingspeak.com" , (u8 *)"80" );
		_delay_ms(2000);

		ESP8266_VidSendHttpReq( "GET https://api.thingspeak.com/update?api_key=09WX4JS2V5GVQKYL","0","80");


	}
	return 0;

}

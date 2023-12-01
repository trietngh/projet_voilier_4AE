#include "Driver_Roulis.h"
#include "Driver_Delay.h"


#define ROULIS_POWER_CTL_ADDR 0X2D
#define ROULIS_POWER_CTL_VALUE 0x08

#define ROULIS_BW_RATE_ADDR 0X2C
#define ROULIS_BW_RATE_VALUE 0x0A

#define ROULIS_DATA_FORMAT_ADDR 0x31
#define ROULIS_DATA_FORMAT_VALUE 0x08

#define ROULIS_DATAZ0_ADDR 0x36
#define ROULIS_DATAZ1_ADDR 0x37

#define ROULIS_READ_MASK 0x01 << 7
#define ROULIS_WRITE_MASK 0x00 

#define ROULIS_MULTI_BYTE_MASK 0x01 << 6
#define ROULIS_SINGLE_BYTE_MASK 0x00

#define ROULIS_TILT_LIMITE 0xA1

typedef struct {
	uint16_t DataZ;
} Data_Accelero_TypeDef;

void ROULIS_SendMsg(char MsgToConfig, char MsgToSend);

void ROULIS_ReadMsg(char MsgToConfig, char * msgReceived, uint8_t nbByteRead);

void ROULIS_GetAngle(Data_Accelero_TypeDef * dataAccelero);

void ROULIS_Init(){
	/* Byte contain the information for following byte including :
			R/W | MB | address of registre to R/W 
	*/
	char msg_config = 0x00;
	
	/* Init SPI for communication with Accelerometer */
	MySPI_Init(ROULIS_SPI);
	//DELAY_WaitFor(150);
	
	/* Configure the accelerometer according to the following requirement :
			- No low mode required
			- Normal measure (Bit D3 of reg POWER_CTL)
			- 100Hz (default) output data rate
			- Full resolution, right aligned data, range +-2g
		 Note that the value is writen direcly to the registre, not by masking.
	*/
	/* Configure POWER_CTL registre */
	msg_config = ROULIS_WRITE_MASK | ROULIS_SINGLE_BYTE_MASK | ROULIS_POWER_CTL_ADDR;
	ROULIS_SendMsg(msg_config,ROULIS_POWER_CTL_VALUE);
	
	/* Configure BW_Rate registre */
	msg_config = ROULIS_WRITE_MASK | ROULIS_SINGLE_BYTE_MASK | ROULIS_BW_RATE_ADDR;

	ROULIS_SendMsg(msg_config,ROULIS_BW_RATE_VALUE);
	
	/* Configure Data_Format registre */
	msg_config = ROULIS_WRITE_MASK | ROULIS_SINGLE_BYTE_MASK | ROULIS_DATA_FORMAT_ADDR;

	ROULIS_SendMsg(msg_config,ROULIS_DATA_FORMAT_VALUE);
}


bool ROULIS_CheckTiltLimit(){
	bool limit_exceeded = false;
	Data_Accelero_TypeDef dataAccelero;
	/* Get current incline angle from accelerometer */
	ROULIS_GetAngle(&dataAccelero);
	
	if (dataAccelero.DataZ < ROULIS_TILT_LIMITE){
		limit_exceeded = true;
	}
	return limit_exceeded;
}

void ROULIS_SendMsg(char MsgToConfig, char MsgToSend){
	DELAY_Wait(500);
	MySPI_Clear_NSS();
	MySPI_Send(MsgToConfig);
	MySPI_Send(MsgToSend);
	MySPI_Set_NSS();
	DELAY_Wait(500);
}

void ROULIS_ReadMsg(char MsgToConfig, char * msgReceived, uint8_t nbByteRead){
	uint8_t iter;
	MySPI_Clear_NSS();	
	MySPI_Send(MsgToConfig);
	for(iter= 0; iter < nbByteRead; iter++){
		msgReceived[iter] = MySPI_Read();
		//DELAY_WaitFor(150);
	}	
	MySPI_Set_NSS();
}

/* Get angle of incline in (by the form of acceleration) */
void ROULIS_GetAngle(Data_Accelero_TypeDef * dataAccelero){
	/* Byte contain the information for following byte including :
			R/W | MB | address of registre to R/W 
	*/
	/* Read registre DATAZ0 & DATAZ1 */
	char msg_config = ROULIS_READ_MASK | ROULIS_MULTI_BYTE_MASK | ROULIS_DATAZ0_ADDR;
		
	/* Number of byte read (must be double of the axis used) */
	const char nb_byte_read = 2;
	
	/* Message receive from accelerometer */
	char msgReceived[nb_byte_read];
	
	ROULIS_ReadMsg(msg_config, msgReceived, nb_byte_read);
	
	dataAccelero->DataZ = msgReceived[0] + (msgReceived[1] << 8);
}

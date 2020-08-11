

#include "mcp_can.h"
#include <util/delay.h>
#include "mcp_can_dfs.h"
#include <avr/io.h>
#include "spi.h"
#define spi_readwrite SPI.transfer
#define spi_read() spi_readwrite(0x00)


//------------------------------------------------------------------------------------------------------------


/*********************************************************************************************************
 ** Function name:           mcp2515_reset
 ** Descriptions:            reset the device
 *********************************************************************************************************/
void MCP_CAN::mcp2515_reset(void)
{
	//MCP2515_SELECT();
	PORTB&=~(1<<SS);
	_delay_ms(2);
	spi_tranceiver(MCP_RESET);						//spi_readwrite(MCP_RESET);
	PORTB|=(1<<SS);
	//MCP2515_UNSELECT();
	_delay_ms(1);
}

/*********************************************************************************************************
 ** Function name:           mcp2515_readRegister
 ** Descriptions:            read register
 *********************************************************************************************************/
INT8U MCP_CAN::mcp2515_readRegister(const INT8U address) //SHUBHAM
{
	INT8U ret;
	//MCP2515_SELECT();
	PORTB&=~(1<<SS);
	_delay_ms(2);
	spi_tranceiver(MCP_READ);			//spi_readwrite(MCP_READ);
	spi_tranceiver(address);			//spi_readwrite(address);
	//spi_tranceiver(MCP_RESET);			//ret = spi_read();  //spi_readwrite(0x00)
	_delay_ms(10);
	ret = spi_tranceiver(0x00);//SHUBHAM don't care data
	PORTB|=(1<<SS);  //MCP2515_UNSELECT();

	return ret;
}

/*********************************************************************************************************
 ** Function name:           mcp2515_readRegisterS
 ** Descriptions:            read registerS
 *********************************************************************************************************/
void MCP_CAN::mcp2515_readRegisterS(const INT8U address, INT8U values[], const INT8U n)
{
	INT8U i;

	INT8U buffer=0x00;
	PORTB&=~(1<<SS);//MCP2515_SELECT();
	spi_tranceiver(MCP_READ);						//spi_readwrite(MCP_READ);
	spi_tranceiver(address);						//spi_readwrite(address);
	// mcp2515 has auto-increment of address-pointer
	for (i = 0; i < n; i++)
	{
		values[i] = spi_tranceiver(buffer);
	}
	PORTB|=(1<<SS);//	MCP2515_UNSELECT();
}

/*********************************************************************************************************
 ** Function name:           mcp2515_setRegister
 ** Descriptions:            set register
 *********************************************************************************************************/
void MCP_CAN::mcp2515_setRegister(const INT8U address, const INT8U value)
{
	//();
	PORTB&=~(1<<SS);
	spi_tranceiver(MCP_WRITE);
	spi_tranceiver(address);
	spi_tranceiver(value);
	PORTB|=(1<<SS);//MCP2515_UNSELECT();
}

/*********************************************************************************************************
 ** Function name:           mcp2515_setRegisterS
 ** Descriptions:            set registerS
 *********************************************************************************************************/
void MCP_CAN::mcp2515_setRegisterS(const INT8U address, const INT8U values[], const INT8U n)
{	INT8U i;
	PORTB&=~(1<<SS);	//MCP2515_SELECT();

	spi_tranceiver(MCP_WRITE);						//spi_readwrite(MCP_READ);
	spi_tranceiver(address);						//spi_readwrite(address);

	for (i = 0; i < n; i++)
	{
		spi_tranceiver(values[i]);

	}
	PORTB|=(1<<SS);

	//MCP2515_UNSELECT();
}

/*********************************************************************************************************
 ** Function name:           mcp2515_modifyRegister
 ** Descriptions:            set bit of one register
 *********************************************************************************************************/
void MCP_CAN::mcp2515_modifyRegister(const INT8U address, const INT8U mask, const INT8U data)
{
	//	MCP2515_SELECT();
	PORTB&=~(1<<SS);


	spi_tranceiver(MCP_BITMOD);
	spi_tranceiver(address);
	spi_tranceiver(mask);
	spi_tranceiver(data);
	PORTB|=(1<<SS);
	//	MCP2515_UNSELECT();
}

/*********************************************************************************************************
 ** Function name:           mcp2515_readStatus
 ** Descriptions:            read mcp2515's Status
 *********************************************************************************************************/
INT8U MCP_CAN::mcp2515_readStatus(void)
{
	INT8U i;
	INT8U buffer=0x00;
	PORTB&=~(1<<SS);//MCP2515_SELECT();
	spi_tranceiver(MCP_READ_STATUS);
	i = spi_tranceiver(buffer);
	PORTB|=(1<<SS);
	//MCP2515_UNSELECT();

	return i;
}

/*********************************************************************************************************
 ** Function name:           mcp2515_setCANCTRL_Mode
 ** Descriptions:            set control mode
 *********************************************************************************************************/
INT8U MCP_CAN::mcp2515_setCANCTRL_Mode(const INT8U newmode)
{
	INT8U i;

	mcp2515_modifyRegister(MCP_CANCTRL, MODE_MASK, newmode); //sets ip chip in configuration mode


	i = mcp2515_readRegister(MCP_CANCTRL);                     //SHUBHAM
	i &= MODE_MASK;

	if (i == newmode)
	{
		//led_blink(PIN4,1);
		return MCP2515_OK;
	}

	//led_blink(PIN5,1);
	return MCP2515_FAIL;

}

/*********************************************************************************************************
 ** Function name:           mcp2515_configRate
 ** Descriptions:            set boadrate
 *********************************************************************************************************/
INT8U MCP_CAN::mcp2515_configRate(const INT8U canSpeed, const INT8U clock)
{
	INT8U set, cfg1, cfg2, cfg3,res;
	set = 1;

	switch (canSpeed)
	{
	case (CAN_100KBPS) :
			cfg1 = MCP_8MHz_100kBPS_CFG1;
    		cfg2 = MCP_8MHz_100kBPS_CFG2;
    		cfg3 = MCP_8MHz_100kBPS_CFG3;
	    	break;
   	case (CAN_125KBPS) :
			cfg1 = MCP_8MHz_125kBPS_CFG1;
			cfg2 = MCP_8MHz_125kBPS_CFG2;
			cfg3 = MCP_8MHz_125kBPS_CFG3;
			//led_blink(PIN4,1);
 			break;
	case (CAN_200KBPS) :
   			cfg1 = MCP_8MHz_200kBPS_CFG1;
			cfg2 = MCP_8MHz_200kBPS_CFG2;
			cfg3 = MCP_8MHz_200kBPS_CFG3;
			break;
	case (CAN_250KBPS) :
			cfg1 = MCP_8MHz_250kBPS_CFG1;
   			cfg2 = MCP_8MHz_250kBPS_CFG2;
			cfg3 = MCP_8MHz_250kBPS_CFG3;
    		break;
	case (CAN_500KBPS) :
			cfg1 = MCP_8MHz_500kBPS_CFG1;
			cfg2 = MCP_8MHz_500kBPS_CFG2;
			cfg3 = MCP_8MHz_500kBPS_CFG3;
			break;
	case (CAN_1000KBPS) :
			cfg1 = MCP_8MHz_1000kBPS_CFG1;
			cfg2 = MCP_8MHz_1000kBPS_CFG2;
   			cfg3 = MCP_8MHz_1000kBPS_CFG3;
			break;
	default:
			set = 0;
   			break;
			}

	if (set) {
		mcp2515_setRegister(MCP_CNF1, cfg1);

		_delay_ms(4);
		mcp2515_setRegister(MCP_CNF2, cfg2);
		_delay_ms(4);
		mcp2515_setRegister(MCP_CNF3, cfg3);
		_delay_ms(4);

		if((res=mcp2515_readRegister(MCP_CNF1))==cfg1)
		{
			//led_blink(PIN4,1);
			_delay_ms(4);

			if((res=mcp2515_readRegister(MCP_CNF2))==cfg2)
			{
				//led_blink(PIN4,1);
				_delay_ms(4);
				if((res=mcp2515_readRegister(MCP_CNF3))==cfg3)
				{
				//	led_blink(PIN4,1);
					return MCP2515_OK;
				}
			}
		}
	}
		return MCP2515_FAIL;
}

/*********************************************************************************************************
 ** Function name:           mcp2515_initCANBuffers
 ** Descriptions:            init canbuffers
 *********************************************************************************************************/
void MCP_CAN::mcp2515_initCANBuffers(void)
{
	INT8U i, a1, a2, a3;

	INT8U std = 0;
	INT8U ext = 1;
	INT32U ulMask = 0x00, ulFilt = 0x00;


	mcp2515_write_id(MCP_RXM0SIDH, ext, ulMask);			/*Set both masks to 0           */



	mcp2515_write_id(MCP_RXM1SIDH, ext, ulMask);			/*Mask register ignores ext bit */

	/* Set all filters to 0         */
	mcp2515_write_id(MCP_RXF0SIDH, ext, ulFilt);			/* RXB0: extended               */
	mcp2515_write_id(MCP_RXF1SIDH, std, ulFilt);			/* RXB1: standard               */
	mcp2515_write_id(MCP_RXF2SIDH, ext, ulFilt);			/* RXB2: extended               */
	mcp2515_write_id(MCP_RXF3SIDH, std, ulFilt);			/* RXB3: standard               */
	mcp2515_write_id(MCP_RXF4SIDH, ext, ulFilt);
	mcp2515_write_id(MCP_RXF5SIDH, std, ulFilt);

	/* Clear, deactivate the three  */
	/* transmit buffers             */
	/* TXBnCTRL -> TXBnD7           */
	a1 = MCP_TXB0CTRL;
	a2 = MCP_TXB1CTRL;
	a3 = MCP_TXB2CTRL;
	for (i = 0; i < 14; i++) {                                          /* in-buffer loop               */
		mcp2515_setRegister(a1, 0);
		mcp2515_setRegister(a2, 0);
		mcp2515_setRegister(a3, 0);
		a1++;
		a2++;
		a3++;
	}
	mcp2515_setRegister(MCP_RXB0CTRL, 0);
	mcp2515_setRegister(MCP_RXB1CTRL, 0);
/*
	//-------------------------------------------------------------------------------------------------------------------------------

	res=mcp2515_readRegister(MCP_RXM0SIDH);
	if(res==0x)
	res=mcp2515_readRegister(MCP_RXM1SIDH);


    res=mcp2515_readRegister(MCP_RXF0SIDH);			// RXB0: extended
    res=mcp2515_readRegister(MCP_RXF1SIDH);			// RXB0: extended
    res=mcp2515_readRegister(MCP_RXF2SIDH);			// RXB0: extended
    res=mcp2515_readRegister(MCP_RXF3SIDH);			// RXB0: extended
    res=mcp2515_readRegister(MCP_RXF4SIDH);			// RXB0: extended
    res=mcp2515_readRegister(MCP_RXF5SIDH);			// RXB0: extended
*/


}

/*********************************************************************************************************
 ** Function name:           mcp2515_init
 ** Descriptions:            init the device
 *********************************************************************************************************/

INT8U MCP_CAN::mcp2515_init(const INT8U canSpeed, const INT8U clock)                       /* mcp2515init8*/
{

	INT8U res=0xff;

	mcp2515_reset();
	res = mcp2515_setCANCTRL_Mode(MODE_CONFIG);
	_delay_ms(10);
	res=mcp2515_readRegister(MCP_CANSTAT);
	res&=MODE_MASK;

	if (res != MODE_CONFIG)
	{
		return -1;
	}
	res=0xff;
	/* set baudrate                 */
	res=mcp2515_configRate(canSpeed, clock);
	if(res==MCP2515_FAIL)
	{
		return -1;
	}
	if (res == MCP2515_OK) {
		/* init canbuffers              */
		mcp2515_initCANBuffers();

		/* interrupt mode               */
		mcp2515_setRegister(MCP_CANINTE, MCP_RX0IF | MCP_RX1IF);
		res = mcp2515_setCANCTRL_Mode(MODE_NORMAL);
		/* enter normal mode
		 *  */
		_delay_ms(100);
		//res = mcp2515_setCANCTRL_Mode(MODE_NORMAL); //SHUBHAM REMOVED IT
		mcp2515_setRegister(MCP_CANCTRL,MODE_NORMAL);
		res=mcp2515_readRegister(MCP_CANSTAT);
		res&=MODE_MASK;

		if (res==0x00)
		{
			return 0;
		}
	}
	return -1;

}

/*********************************************************************************************************
 ** Function name:           mcp2515_write_id
 ** Descriptions:            write can id
 *********************************************************************************************************/
void MCP_CAN::mcp2515_write_id(const INT8U mcp_addr, const INT8U ext, const INT32U id)
{
	uint16_t canid;
	INT8U tbufdata[4];

	canid = (uint16_t)(id & 0x0FFFF);

	if (ext == 1)
	{
		tbufdata[MCP_EID0] = (INT8U)(canid & 0xFF);
		tbufdata[MCP_EID8] = (INT8U)(canid >> 8);
		canid = (uint16_t)(id >> 16);
		tbufdata[MCP_SIDL] = (INT8U)(canid & 0x03);
		tbufdata[MCP_SIDL] += (INT8U)((canid & 0x1C) << 3);
		tbufdata[MCP_SIDL] |= MCP_TXB_EXIDE_M;
		tbufdata[MCP_SIDH] = (INT8U)(canid >> 5);
	}
	else
	{
		tbufdata[MCP_SIDH] = (INT8U)(canid >> 3);
		tbufdata[MCP_SIDL] = (INT8U)((canid & 0x07) << 5);
		tbufdata[MCP_EID0] = 0;
		tbufdata[MCP_EID8] = 0;
	}
	mcp2515_setRegisterS(mcp_addr, tbufdata, 4);
}

/***********************************************************************
 *
 *
 * **********************************
 ** Function name:           mcp2515_read_id
 ** Descriptions:            read can id
 *********************************************************************************************************/
void MCP_CAN::mcp2515_read_id(const INT8U mcp_addr, INT8U* ext, INT32U* id)
{
	INT8U tbufdata[4];

	*ext = 0;
	*id = 0;

	mcp2515_readRegisterS(mcp_addr, tbufdata, 4);

	*id = (tbufdata[MCP_SIDH] << 3) + (tbufdata[MCP_SIDL] >> 5);

	if ((tbufdata[MCP_SIDL] & MCP_TXB_EXIDE_M) == MCP_TXB_EXIDE_M)
	{
		/* extended id                  */
		*id = (*id << 2) + (tbufdata[MCP_SIDL] & 0x03);
		*id = (*id << 8) + tbufdata[MCP_EID8];
		*id = (*id << 8) + tbufdata[MCP_EID0];
		*ext = 1;
	}
}

/*********************************************************************************************************
 ** Function name:           mcp2515_write_canMsg
 ** Descriptions:            write msg
 *********************************************************************************************************/
void MCP_CAN::mcp2515_write_canMsg(const INT8U buffer_sidh_addr)
{

	INT8U mcp_addr;
	mcp_addr = buffer_sidh_addr;
	mcp2515_setRegisterS(mcp_addr + 5, m_nDta, m_nDlc);                  /* write data bytes             */
	if (m_nRtr == 1)                                                   /* if RTR set bit in byte       */
	{
		m_nDlc |= MCP_RTR_MASK;
	}
	mcp2515_setRegister((mcp_addr + 4), m_nDlc);                        /* write the RTR and DLC        */
	mcp2515_write_id(mcp_addr, m_nExtFlg, m_nID);                     /* write CAN id                 */

}

/*********************************************************************************************************
 ** Function name:           mcp2515_read_canMsg
 ** Descriptions:            read message
 *********************************************************************************************************/
void MCP_CAN::mcp2515_read_canMsg(const INT8U buffer_sidh_addr)        /* read can msg                 */
{
	INT8U mcp_addr, ctrl;

	mcp_addr = buffer_sidh_addr;

	mcp2515_read_id(mcp_addr, &m_nExtFlg, &m_nID);

	ctrl = mcp2515_readRegister(mcp_addr - 1);
	m_nDlc = mcp2515_readRegister(mcp_addr + 4);

	if ((ctrl & 0x08)) {
		m_nRtr = 1;
	}
	else {
		m_nRtr = 0;
	}

	m_nDlc &= MCP_DLC_MASK;
	mcp2515_readRegisterS(mcp_addr + 5, &(m_nDta[0]), m_nDlc);
}

/*********************************************************************************************************
 ** Function name:           sendMsg
 ** Descriptions:            send message
 *********************************************************************************************************/
void MCP_CAN::mcp2515_start_transmit(const INT8U mcp_addr)              /* start transmit               */
{
	INT8U res;
	mcp2515_modifyRegister(mcp_addr - 1, MCP_TXB_TXREQ_M, MCP_TXB_TXREQ_M);
	//mcp2515_setRegister(mcp_addr - 1,MCP_TXB_TXREQ_M);//SHUBHAM
	res=mcp2515_readRegister(mcp_addr - 1);

	if((res&=0x08)==0x08)
	{
		//led_blink(PIN7,1);

	}
	//mcp2515_setRegister(mcp_addr - 1,MCP_TXB_TXREQ_M);//SHUBHAM
}

/*********************************************************************************************************
 ** Function name:           sendMsg
 ** Descriptions:            send message
 *********************************************************************************************************/
INT8U MCP_CAN::mcp2515_getNextFreeTXBuf(INT8U *txbuf_n)                 /* get Next free txbuf          */
{
	INT8U res=0xff, i, ctrlval;
	INT8U ctrlregs[MCP_N_TXBUFFERS] = { MCP_TXB0CTRL, MCP_TXB1CTRL, MCP_TXB2CTRL };

	res = MCP_ALLTXBUSY;
	*txbuf_n = 0x00;

	/* check all 3 TX-Buffers       */
	for (i = 0; i < MCP_N_TXBUFFERS; i++) {
		ctrlval = mcp2515_readRegister(ctrlregs[i]);
		if ((ctrlval & MCP_TXB_TXREQ_M) == 0) {
			*txbuf_n = ctrlregs[i] + 1;                                   /* return SIDH-address of Buffe */
			/* r                            */
			res = MCP2515_OK;
			return res;                                                 /* ! function exit              */
		}
	}
	return res;
}

/*********************************************************************************************************
 ** Function name:           set CS
 ** Descriptions:            init CS pin and set UNSELECTED
 *********************************************************************************************************/
MCP_CAN::MCP_CAN()
{
	m_nExtFlg = 0;          /* identifier xxxID             */
    m_nID = 0;                                                      /* can id                       */
	m_nDlc = 64;                                                     /* data length:                 */
	//m_nDta[MAX_CHAR_IN_MESSAGE];                            	/* data                         */
	m_nRtr = 0xff;                                                     /* rtr                          */
	m_nfilhit= 0xff;
	SPICS = SS;
}
/*
 *********************************************************************************************************
 ** Function name:           init
 ** Descriptions:            init can and set speed
 *********************************************************************************************************/
INT8U MCP_CAN::begin(INT8U speedset, const INT8U clockset)
{
	INT8U res;

	//SPI.begin();
	res = mcp2515_init(speedset, clockset);

	if (res == MCP2515_OK)
	{

		//led_blink(PIN4,1);
		return CAN_OK;

	}
	else
	{
		//led_blink(PIN5,1);
		return CAN_FAILINIT;
	}
}

/*********************************************************************************************************
 ** Function name:           init_Mask
 ** Descriptions:            init canid Masks
 *********************************************************************************************************/
INT8U MCP_CAN::init_Mask(INT8U num, INT8U ext, INT32U ulData)
{
	INT8U res = MCP2515_OK;
#if DEBUG_MODE
	Serial.print("Begin to set Mask!!\r\n");
#endif
	res = mcp2515_setCANCTRL_Mode(MODE_CONFIG);
	if (res > 0){
#if DEBUG_MODE
		Serial.print("Enter setting mode fall\r\n");
#endif
		return res;
	}

	if (num == 0){
		mcp2515_write_id(MCP_RXM0SIDH, ext, ulData);

	}
	else if (num == 1){
		mcp2515_write_id(MCP_RXM1SIDH, ext, ulData);
	}
	else res = MCP2515_FAIL;

	res = mcp2515_setCANCTRL_Mode(MODE_NORMAL);
	if (res > 0){
#if DEBUG_MODE
		Serial.print("Enter normal mode fall\r\n");
#endif
		return res;
	}
#if DEBUG_MODE
	Serial.print("set Mask success!!\r\n");
#endif
	return res;
}

/*********************************************************************************************************
 ** Function name:           init_Filt
 ** Descriptions:            init canid filters
 *********************************************************************************************************/
INT8U MCP_CAN::init_Filt(INT8U num, INT8U ext, INT32U ulData)
{
	INT8U res = MCP2515_OK;
#if DEBUG_MODE
	Serial.print("Begin to set Filter!!\r\n");
#endif
	res = mcp2515_setCANCTRL_Mode(MODE_CONFIG);
	if (res > 0)
	{
#if DEBUG_MODE
		Serial.print("Enter setting mode fall\r\n");
#endif
		return res;
	}

	switch (num)
	{
	case 0:
		mcp2515_write_id(MCP_RXF0SIDH, ext, ulData);
		break;

	case 1:
		mcp2515_write_id(MCP_RXF1SIDH, ext, ulData);
		break;

	case 2:
		mcp2515_write_id(MCP_RXF2SIDH, ext, ulData);
		break;

	case 3:
		mcp2515_write_id(MCP_RXF3SIDH, ext, ulData);
		break;

	case 4:
		mcp2515_write_id(MCP_RXF4SIDH, ext, ulData);
		break;

	case 5:
		mcp2515_write_id(MCP_RXF5SIDH, ext, ulData);
		break;

	default:
		res = MCP2515_FAIL;
	}


	res = mcp2515_setCANCTRL_Mode(MODE_NORMAL);
	if (res > 0)
	{
#if DEBUG_MODE
		Serial.print("Enter normal mode fall\r\nSet filter fail!!\r\n");
#endif
		return res;
	}
#if DEBUG_MODE
	Serial.print("set Filter success!!\r\n");
#endif

	return res;
}

/*********************************************************************************************************
 ** Function name:           setMsg
 ** Descriptions:            set can message, such as dlc, id, dta[] and so on
 *********************************************************************************************************/
INT8U MCP_CAN::setMsg(INT32U id, INT8U ext, INT8U len, INT8U *pData)
{
	int i;
	m_nExtFlg = ext;
	m_nID = id;
	m_nDlc = len;
	for(i=0;i< MAX_CHAR_IN_MESSAGE; i++)
	{
		m_nDta[i] = *(pData + i);
	}
	return MCP2515_OK;
}

/*********************************************************************************************************
 ** Function name:           clearMsg
{
 ** Descriptions:            set all message to zero
 *********************************************************************************************************/
INT8U MCP_CAN::clearMsg()
{
	m_nID = 0;
	m_nDlc = 0b1000;
	m_nExtFlg = 0;
	m_nRtr = 0;
	m_nfilhit = 0;
	for (int i = 0; i < m_nDlc; i++)
		m_nDta[i] = 0x00;

	return MCP2515_OK;
}

/*********************************************************************************************************
 ** Function name:           sendMsg
 ** Descriptions:            send message
 *********************************************************************************************************/
INT8U MCP_CAN::sendMsg()
{
	INT8U res, res1, txbuf_n;
	uint16_t uiTimeOut = 0;

	do {
		res = mcp2515_getNextFreeTXBuf(&txbuf_n);                       /* info = addr.                 */
		uiTimeOut++;
	} while (res == MCP_ALLTXBUSY && (uiTimeOut < TIMEOUTVALUE));

	if (uiTimeOut == TIMEOUTVALUE)
	{
		return CAN_GETTXBFTIMEOUT;                                      /* get tx buff time out         */
	}
	uiTimeOut = 0;
	mcp2515_write_canMsg(txbuf_n);
	mcp2515_start_transmit(txbuf_n);
	do
	{
		uiTimeOut++;
		res1 = mcp2515_readRegister(txbuf_n-1);		/* read send buff ctrl reg 	*/
		res1 = res1 & 0x08;
	} while (res1 && (uiTimeOut < TIMEOUTVALUE));

	if (uiTimeOut == TIMEOUTVALUE)                                       /* send msg timeout             */
	{
		return CAN_SENDMSGTIMEOUT;
	}
	return CAN_OK;
}

/*********************************************************************************************************
 ** Function name:           sendMsgBuf
 ** Descriptions:            send buf
 *********************************************************************************************************/
INT8U MCP_CAN::sendMsgBuf(INT32U id, INT8U ext, INT8U len, INT8U *buf)
{
	INT8U res;
	setMsg(id, ext, len, buf);
	res=sendMsg();
	return res;
}

/*********************************************************************************************************
 ** Function name:           readMsg
 ** Descriptions:            read message
 *********************************************************************************************************/
INT8U MCP_CAN::readMsg()
{
	INT8U stat, res;

	stat = mcp2515_readStatus();

	if (stat & MCP_STAT_RX0IF)                                        /* Msg in Buffer 0              */
	{
		mcp2515_read_canMsg(MCP_RXBUF_0);
		mcp2515_modifyRegister(MCP_CANINTF, MCP_RX0IF, 0);
		res = CAN_OK;
	}
	else if (stat & MCP_STAT_RX1IF)                                   /* Msg in Buffer 1              */
	{
		mcp2515_read_canMsg(MCP_RXBUF_1);
		mcp2515_modifyRegister(MCP_CANINTF, MCP_RX1IF, 0);
		res = CAN_OK;
	}
	else
	{
		res = CAN_NOMSG;
	}
	return res;
}

/*********************************************************************************************************
 ** Function name:           readMsgBuf
 ** Descriptions:            read message buf
 *********************************************************************************************************/
INT8U MCP_CAN::readMsgBuf(INT8U *len, INT8U buf[])
{
	int res;
	res=readMsg();
	*len = m_nDlc;
	for (int i = 0; i < m_nDlc; i++)
	{
		buf[i] = m_nDta[i];
	}
	return res;
}

/*********************************************************************************************************
 ** Function name:           checkReceive
 ** Descriptions:            check if got something
 *********************************************************************************************************/
INT8U MCP_CAN::checkReceive(void)
{
	INT8U res;
	res = mcp2515_readStatus();                                         /* RXnIF in Bit 1 and 0         */
	if (res & MCP_STAT_RXIF_MASK)
	{
		return CAN_MSGAVAIL;
	}
	else
	{
		return CAN_NOMSG;
	}
}

/*********************************************************************************************************
 ** Function name:           checkError
 ** Descriptions:            if something error
 *********************************************************************************************************/
INT8U MCP_CAN::checkError(void)
{
	INT8U eflg = mcp2515_readRegister(MCP_EFLG);

	if (eflg & MCP_EFLG_ERRORMASK)
	{
		return CAN_CTRLERROR;
	}
	else
	{
		return CAN_OK;
	}
}

/*********************************************************************************************************
 ** Function name:           getCanId
 ** Descriptions:            when receive something ,u can get the can id!!
 *********************************************************************************************************/
INT32U MCP_CAN::getCanId(void)
{

	return m_nID;
}


/*********************************************************************************************************
  END FILE
 *********************************************************************************************************/

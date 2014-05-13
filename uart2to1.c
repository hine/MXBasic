/****************************************************************************
    uart2to1.c   for SBDBT32
****************************************************************************/

#ifdef USE_SBDBT32

char UART2GetBaudError()
{
    unsigned int errorPercent = 0;

	errorPercent = ((BAUD_ERROR*100+BAUDRATE2/2)/BAUDRATE2);
    return (char)errorPercent;
}


char UART2GetChar()
{
    char Temp;

    while(IFS0bits.U1RXIF == 0);

    Temp = U1RXREG;
    IFS0bits.U1RXIF = 0;
    return Temp;
}

void UART2Init()
{

    U1BRG = BAUDRATEREG2;
    U1MODE = 0;
    U1MODEbits.BRGH = BRGH2;
    U1STA = 0;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    IFS0bits.U1RXIF = 0;
    
    U1STAbits.URXEN = 1;

    // delay
    {int n;
        for(n = 0; n < 2; n++);
    }
}

char UART2IsPressed()
{
    if(IFS0bits.U1RXIF == 1)
        return 1;
    return 0;
}

void UART2PrintString( char *str )
{
    unsigned char c;

    while( (c = *str++) )
        UART2PutChar(c);
}

void UART2PutChar( char ch )
{
    while(U1STAbits.UTXBF == 1);

    U1TXREG = ch;
    while(U1STAbits.TRMT == 0);
}

void  UART2PutDec(unsigned char dec)
{
    unsigned char res;
    unsigned char printed_already = 0;

    res = dec;

    if (res/100)
    {
        UART2PutChar( res/100 + '0' );
        printed_already = 1;
    }
    res = res - (res/100)*100;

    if ((res/10) || (printed_already == 1))
    {
        UART2PutChar( res/10 + '0' );
    }
    res = res - (res/10)*10;

    UART2PutChar( res + '0' );
}

const unsigned char CharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void UART2PutHex( int toPrint )
{
    int printVar;

    printVar = toPrint;
    toPrint = (toPrint>>4) & 0x0F;
    UART2PutChar( CharacterArray[toPrint] );

    toPrint = printVar & 0x0F;
    UART2PutChar( CharacterArray[toPrint] );

    return;
}

void UART2PutHexWord( unsigned int toPrint )
{
    unsigned int printVar;

    printVar = (toPrint>>12) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>8) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>4) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = toPrint & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    return;
}

void UART2PutHexDWord( unsigned long toPrint )
{
    unsigned long printVar;

    printVar = (toPrint>>28) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>24) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>20) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>16) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>12) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>8) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>4) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = toPrint & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    return;
}

char UART2Char2Hex(char ch){
  // Wrong char
  if(ch > 102)
    return 0;  
  
  // From a to f     
  if(ch > 96)
    return (ch-87);
    
  // Wrong char    
  if(ch > 70)
    return 0;
  
  // From A to F    
  if(ch > 64)
    return (ch-55);

  // Wrong char  
  if(ch > 57)
    return 0;
  
  // From 0 - 9
  if(ch > 47)
    return(ch-48);
  else
  // Wrong char
    return 0;
}

char UART2Hex2Char(char hex){
char h;
  h = hex&0x0f;
  // From 0xa to 0xf
  if(h>9)
    return (h+55);
  else
    return (h+48);
}

void UART2ClrError(void){
    // Clear error flag
    if(U1STAbits.OERR)
		U1STAbits.OERR = 0;
}

#endif   // USE_SBDBT32

/*** end of uart2to1.c *****************************************************/


#include <SPI.h>
const int CS_PIN =53;
#define size 100
struct block_page
{
  unsigned char n:7;
  unsigned int b:11;
  unsigned char p:6;
};
struct col
{
  unsigned int a:13;
};
void setup()
{
  struct block_page d;
   struct col c={0};
  Serial.begin(9600);
  delay(1020);
  SPI.begin();
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  reset();//0xFF;
  readDeviceID();//0x9F
  //to_check_lock_register();
  //set_a_feacure_address();

  
//--------------------THIS CONTENT IS WRITE SMALL AMOUNTE OF DATA IT CAN POSIBLE SPICIFIC BLOCK & PAGE IS POSIBLE (DONE) STATRT -----------



    // const char* data = "Hello,hi i am bharath kumar i am india";
    // int len = strlen(data);
    // d={0,1,1};
    // erase_block(d);
    // write_to_data(d,c,data,len);
    // char readData[len+1];
    // readPage(d,c,readData,len);



//--------------------THIS CONTENT IS WRITE SMALL AMOUNTE OF DATA IT CAN POSIBLE SPICIFIC BLOCK & PAGE IS POSIBLE (DONE) END -----------


//...............THIS CONTENT IS WRITE DATA TOTAL 2175 DATA WRITE SPECIFIC BLOCK & PAGE (DONE) START------------------------------------



      // unsigned char data[2200];
      // uint32_t len=2200;
      // for (uint32_t i = 0; i < len; i++) {
      //   data[i] ='1'; // Example data
      // }
      // d={0,1,1};
      // erase_block(d);
      // write_to_data(d,c,data,len);
      // char readData[len+1];
      // readPage(d,c,readData,len);




//...............THIS CONTENT IS WRITE DATA READ TOTAL 2175 DATA WRITE SPECIFIC BLOCK & PAGE (DONE) END------------------------------------






//--------------------THIS CONTENT IS WRITE DATA READ SMOLL AMOUNT OF DATA AND ONE TIME SET DATA WRITE MULTIPLILE BLOCKS & MULTIPLE PAGES SAME DATA (DONE) START---------------------
  
  
  
      // const char* data = "Hello,hi i am bharath kumar i am india";
      // int len = strlen(data);
      // for(int j=0;j<10;j++)
      // {
      //   d={0,3,j};
      //   erase_block(d);
      //   write_to_data(d,c,data,len);
      // }
      // char readData[len+1];
      // for(int i=0;i<10;i++)
      // {
      //     readPage(d,c,readData,len);
      // }



//--------------------THIS CONTENT IS WRITE DATA READ SMOLL AMOUNT OF DATA AND ONE TIME SET DATA WRITE MULTIPLILE BLOCKS & MULTIPLE PAGES SAME DATA (DONE) START---------------------



//--------------------  THIS CONTENTE WRITE AND READ DATA TOTAL 2175 BYTES WRITE MULTIPLE BLOCKS & PAGES EACH BLOCKS &PAGES DIFFENT DATA (DONE) START-------------------------------



       unsigned char data[2200];
       uint32_t len=2200;
       for(int j=0;j<2;j++)
       {
         d={0,76,j};
         erase_block(d);
         if(j==0)
         { 
           for (uint32_t i = 0; i < len; i++) 
           {
             data[i] ='4'; // Example data
           }
           write_to_data(d,c,data,len);
           Serial.print("this is the bharth\n");
         }
         else if(j==1)
         {
           for (uint32_t i = 0; i < len; i++) 
           {
             data[i] ='7'; // Example data
           }
           write_to_data(d,c,data,len);
           Serial.print("this the i am kumar\n");
         }
       }
       unsigned char readData[len+1];
       for(int i=0;i<2;i++)
       {
         d={0,76,i};
         readPage(d,c,readData,len);
       }



  //--------------------  THIS CONTENTE WRITE AND READ DATA TOTAL 2175 BYTES WRITE MULTIPLE BLOCKS & PAGES EACH BLOCKS &PAGES DIFFENT DATA (DONE) START-------------------------------


}
void loop() {

}
//===================THIS FUNCTION RESET DEVICE (0xFF) START========================
void reset() 
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0xFF); // Reset command
  digitalWrite(CS_PIN, HIGH);
  //printStatus("1--------0xFF");
}
//===================THIS FUNCTION RESET DEVICE (0xFF) END========================
//===================THIS FUNCTION READ THE DEVIXE INFIRMATION (0x9F) START========================
void readDeviceID() 
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x9F); // Read ID command
  byte id0 = SPI.transfer(0x00);
  byte id1 = SPI.transfer(0x00);
  byte id2 = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  Serial.print("Manufacturer ID: 0x");
  Serial.println(id1, HEX);
  Serial.print("Device ID: 0x");
  Serial.println(id2, HEX);
  //printStatus("2--------0x0F");
}
//===================THIS FUNCTION READ THE DEVIXE INFIRMATION (0x9F) END========================

//===================THIS FUNCTION IS THE TO CHECK ANYTHING BLOCKS & PAGES IS BLOKED OR NOT COMMAND (0X0F) ADDRESS(0XA0) START==================================
void to_check_lock_register()
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x0F); // Get Feature
  SPI.transfer(0xA0); // Status register
  int a=SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  Serial.print(">>>>>>>>>>>>this is the read block lock register valuew:-");
  Serial.println(a,HEX);
}
//===================THIS FUNCTION IS THE TO CHECK ANYTHING BLOCKS & PAGES IS BLOKED OR NOT COMMAND (0X0F) ADDRESS(0XA0) END==================================
//===================THIS FUNCTION IS IF IN CASE BLOKED  SOME BLOCKS & PAGES UNBLOCK COMMAND (0X1F) ADDRESS (0XA0) START=====================================
void set_a_feacure_address()
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x1F); // Get Feature
  SPI.transfer(0xA0); // Status register
  SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  Serial.print("----------------complite the  set register--------------\n");
}
//===================THIS FUNCTION IS IF IN CASE BLOKED  SOME BLOCKS & PAGES UNBLOCK COMMAND (0X1F) ADDRESS (0XA0) END=====================================


//===================THIS FUNCTION IS THE ERASE BLOCK COMMAND (0X53 32-kb) or (0XD8 64-Kb) START=========================================================
unsigned char erase[4];
void erase_block(struct block_page d)
{
   erase[0]=0x52;
   erase[1]=(d.b>>10|d.n)&0xFF;
   erase[2]=(d.b>>2)&0xFF;
   erase[3]=(d.b<<6|d.p)&0xFF;
  write_enable();  
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(erase[0]);
  SPI.transfer(erase[1]);
  SPI.transfer(erase[2]);
  SPI.transfer(erase[3]);
  digitalWrite(CS_PIN, HIGH);
  waitUntilReady();
  //check_eraise_status();
  delayMicroseconds(250);
}
//---------------AFTER COMPLITION ERAISE TO CHEC WHAT ABOUTE STATES REGISTER CONDITION------------------------------------------------
void check_eraise_status()
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x0F); // Get Feature
  SPI.transfer(0xC0); // Status register
  uint8_t s = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  Serial.println(s, HEX);
  Serial.print("E_FAIL (bit 2): ");
  Serial.println((s & 0x04) ? "Erase Failure (1)" : "Erase success (0)");
  if (s & 0x04) 
  {
    Serial.println("***** Erase Failure (E_FAIL bit 2 is set) *****");
  } else {
    Serial.println("----- Block erased successfully. -----");
  }
}
//===================THIS FUNCTION IS THE ERASE BLOCK COMMAND (0X53 32-kb) or (0XD8 64-Kb) START=========================================================


//==================THIS FUNCTION WRITE ENABLE COMMAND (0X06)===============================
void write_enable()
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x06);
  digitalWrite(CS_PIN, HIGH);
   waitUntilReady();
 // printStatus("write_status_check_and_value-->");

}
//-----------------CHECK AFTER WHAT ABOUT STATUS REGISTER VALUE----------------------------
void write_enable_check_status(const char* label)
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x0F); // Get Feature
  SPI.transfer(0xC0); // Status Register
  uint8_t status = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  Serial.print(label);
  Serial.println(status, HEX);
  Serial.print("WEL (bit 1): ");
  Serial.println((status & 0x02) ? "Write Enabled (1)" : "Not Enabled (0)");
}
//==================THIS FUNCTION WRITE ENABLE COMMAND (0X06)===============================



//==================THIS FUNCTION IS WAIT SOME TIME UNTIL LAST BIT IS 0 START===================
void waitUntilReady() 
{
  uint8_t s;
  do {
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x0F); // Get Feature command
    SPI.transfer(0xC0); // Status register address
    s = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    delay(1);
  } while (s & 0x01); // Check busy bit
}
//==================THIS FUNCTION IS WAIT SOME TIME UNTIL LAST BIT IS 0 END===================


//=============THIS FUNCTION THE WRITE DATA AND PROGREAM EXECUTE IN CHIPE PASS THE COULUME ADDRESS AND BLOCK& PAGE ADDRESS COOMAD PROGREAM LOAD (0X02) PROGREAM EXECUTE (0X10) START========
unsigned char program[4];
unsigned char write[4];
void write_to_data(struct block_page d,struct col c, uint8_t* data,uint32_t len)
{
  write[0]=0x02;
  write[1]=c.a>>7&0x1F;
  write[2]=c.a&0xFF;
  printStatus("this is the after programe execution---");
  write_enable();
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(write[0]);
  SPI.transfer(write[1]);
  SPI.transfer(write[2]);
  for (int i = 0; i < len; i++) {
    SPI.transfer(data[i]);
  }
  digitalWrite(CS_PIN, HIGH);
  //---------------------this is the operation is the progream execute command----------------
  program[0]=0x10;
  program[1]=(d.b>>10|d.n)&0xFF;
  program[2]=(d.b>>2)&0xFF;
  program[3]=(d.b<<6|d.p)&0xFF;
  write_enable();
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(program[0]);           // PROGRAM EXECUTE
  SPI.transfer(program[1]);    // Row address byte 2
  SPI.transfer(program[2]);     // Row address byte 1
  SPI.transfer(program[3]);            // Row address byte 0
  digitalWrite(CS_PIN, HIGH);
  waitUntilReady();
}
//=============THIS FUNCTION THE WRITE DATA AND PROGREAM EXECUTE IN CHIPE PASS THE COULUME ADDRESS AND BLOCK& PAGE ADDRESS COOMAD PROGREAM LOAD (0X02) PROGREAM EXECUTE (0X10) END========



//=============THUS FUNCTIONS IS READ DATA FROM  CHIPE TO READ PATA COULUME ADDRESS AND BLOCK & PAGE ADDRESS COMMAND IS PAGE READ(0X13) READ FROM CACHE (0X03) START==========================
unsigned char read[4];
unsigned char cache[4];
void readPage(struct block_page d,struct col c, uint8_t* buffer, uint32_t length) 
{
  read[0]=0x13;
  read[1]=(d.b>>10|d.n)&0xFF;
  read[2]=(d.b>>2)&0xFF;
  read[3]=(d.b<<6|d.p)&0xFF;
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(read[0]); // Page Read command the to set the this command  to read page address 
  SPI.transfer(read[1]);
  SPI.transfer(read[2]);
  SPI.transfer(read[3]); 
  digitalWrite(CS_PIN, HIGH);
  waitUntilReady();  

  cache[0]=0x03;
  cache[1]=c.a>>7&0x1F;
  cache[2]=c.a&0xFF;
  cache[3]=0x00;
//---------------------THIS OPERATION IS READ THE DATA IN CHIPE----------------
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(cache[0]); // Read From Cache command the command tonreaf the data frome in address the to variable 
  SPI.transfer(cache[1]);
  SPI.transfer(cache[2]);
  SPI.transfer(cache[3]); // Dummy byte
  uint32_t i;
  for (i = 0; i < length; i++) {
    buffer[i] = SPI.transfer(0x00);
  }
  buffer[i]='\0';
  digitalWrite(CS_PIN, HIGH);
  //-------------------AFTER READ DATA PRINT IN SIDE FUNCTION PRINT-----------------------
  char ch;
  for (uint32_t i = 0; i < length; i++) {
    ch=buffer[i];
    Serial.print(ch);
  }
  Serial.println();
}
//=============THUS FUNCTIONS IS READ DATA FROM  CHIPE TO READ PATA COULUME ADDRESS AND BLOCK & PAGE ADDRESS COMMAND IS PAGE READ(0X13) READ FROM CACHE (0X03) END==========================


//============================THIS FUNCTION IS READ ALL STATUS REGISTE BIT(0-3) VALUES START===================================

void printStatus(const char* label) 
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x0F); // Get Feature
  SPI.transfer(0xC0); // Status Register
  uint8_t status = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  Serial.print(label);
  Serial.println();
  Serial.print(" - Status Reg: 0x");
  Serial.println(status, HEX);
  Serial.print("  OIP (bit 0): ");
  Serial.println((status & 0x01) ? "Busy (1)" : "Ready (0)");
  Serial.print("  WEL (bit 1): ");
  Serial.println((status & 0x02) ? "Write Enabled (1)" : "Not Enabled (0)");
  Serial.print("  E_FAIL (bit 2): ");
  Serial.println((status & 0x04) ? "Erase Failure (1)" : "Erase OK (0)");
  Serial.print("  P_FAIL (bit 3): ");
  Serial.println((status & 0x08) ? "Program Failure (1)" : "Program OK (0)");
  Serial.println("--------------------------------------");
}
//============================THIS FUNCTION IS READ ALL STATUS REGISTE BIT(0-3) VALUES END===================================
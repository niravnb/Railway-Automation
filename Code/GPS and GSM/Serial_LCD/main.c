#include <stdio.h>                /* prototype declarations for I/O functions */
#include <LPC214x.H>              /* LPC21xx definitions                      */
#include "Serial.h"
#include "lcd.h"
												    
#define UART0_TEXT "\n\r Sagar shah  \n\r Urmil Patel \n\r Deep Patel   \n\r Nirav Bhavsar "
#define UART1_TEXT "\n\r Testing UART1 NGX's BlueBoard \n\r BlueBoard Revision : 1 \n\r Firmware Version: 1 \n\r For more information on BlueBoard visit www.ngxtechnologies.com"
#define UART0_SMS0 "AT+CMGF=1"
#define SMS_READ "AT+CMGR=1\r\n"
#define DELET_SMS_ALL "AT+CMGD=1,4\r\n"

#define UART0_SMS1 "AT+CMGS=\"8128371074\"\r\n"
//#define UART0_NUMBER "9429830608"
#define UART0_NEWLINE "\n\r"
#define UART0_SMS2 "Hi sagar"
#define UART0_SMS3 "TRAIN AT VADODARA: STARTED"

#define UART0_GPS "AT+CMGS=\"8128371074\"\r\n"
//#define UART0_NUMBER "9429830608"
//#define UART0_NEWLINE "\n\r"
#define UART0_GPS1 "Latitiude: "
#define UART0_GPS2 "Longitude: "
#define UART0_SPACE "    "
#define UART0_GPS_PC "AT+CMGS=\"8128371074\"\r\n"			   //change the number after final implementation 8128371074
//#define UART0_NEWLINE_PC "\r\n"

unsigned char Gpsdata;             // for incoming serial data
unsigned int finish =0;            // indicate end of message
unsigned int pos_cnt=0;            // position counter
unsigned int lat_cnt=0;            // latitude data counter 
unsigned int log_cnt=0;            // longitude data counter
unsigned int flg    =0;            // GPS flag 
unsigned int com_cnt=0;            // comma counter
unsigned char lat[20];             // latitude array
unsigned char lg[20];              // longitude array
unsigned int i,j,k;
void delay(unsigned long int count);
void gps();
void send_loc_to_pc();

int uart0_getkey1 (void)  {                     /* Read character from Serial Port   */

unsigned int i = 0;
	//	 return 0;
  while (!(U0LSR & 0x01))
  {
      i++;
	  if(i > 65000)
	    return 0;
  }

  return (U0RBR);
}
void Receive_GPS_Data()
  {
    while(finish==0){
               // Check GPS data
        Gpsdata = uart1_getkey();
        flg = 1;
       if( Gpsdata=='$' && pos_cnt == 0)   // finding GPRMC header
         pos_cnt=1;
       if( Gpsdata=='G' && pos_cnt == 1)
         pos_cnt=2;
       if( Gpsdata=='P' && pos_cnt == 2)
         pos_cnt=3;
       if( Gpsdata=='R' && pos_cnt == 3)
         pos_cnt=4;
       if( Gpsdata=='M' && pos_cnt == 4)
         pos_cnt=5;
       if( Gpsdata=='C' && pos_cnt==5 )
         pos_cnt=6;
       if(pos_cnt==6 &&  Gpsdata ==','){   // count commas in message
         com_cnt++;
         flg=0;
       }
 
       if(com_cnt==3 && flg==1){
        lat[lat_cnt++] =  Gpsdata;         // latitude
        flg=0;
       }
 
       if(com_cnt==5 && flg==1){
         lg[log_cnt++] =  Gpsdata;         // Longitude
         flg=0;
       }
 
       if( Gpsdata == '*' && com_cnt >= 5){
         com_cnt = 0;                      // end of GPRMC message
         lat_cnt = 0;
         log_cnt = 0;
         flg     = 0;
         finish  = 1;
 
      }
    }
   }



void gps()
{
    Receive_GPS_Data();


  while(finish!=1);
   
   lcd_clear() ; 
   lcd_putstring(0,"Lat:");    // printing GPS data to serial monitor
   
//    uart0_puts (UART0_GPS);
	//delay(10000);
   //uart0_puts (UART0_GPS1);
   //uart0_putc(0x1A);
		   		for(k=0;k<9;k++)
		   		{
		   		lcd_putchar(lat[k]);
				 //uart0_putc(lat[k]);
		  		 }
   
   lcd_putstring(1,"Lon:");
		    for(k=0;k<10;k++)
		   {
		   lcd_putchar(lg[k]);
		   //uart0_putc(lg[k]);
		   }


finish = 0;
   pos_cnt = 0;

	/*	     uart0_puts (UART0_GPS);
 		 uart0_puts (UART0_GPS1);
  	uart0_puts (UART0_GPS2);


 uart0_putc(0x1A);*/

  	/*		uart0_init();
			
 			uart0_puts (UART0_GPS);	  // Transffer data to PC through Serial
			//uart0_putc('"');
			//uart0_puts (UART0_NUMBER);	  // Transffer data to PC through Serial
			//uart0_putc('"');
			//uart0_puts (UART0_NEWLINE);	  // Transffer data to PC through Serial
			for(i=0;i<5;i++)
			{
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			}
			uart0_puts(UART0_GPS1);	  // Transffer data to PC through Serial
			delay(10000);
				for(k=0;k<9;k++)
		   		{
		   		//lcd_putchar(lat[k]);
				 uart0_putc(lat[k]);
				 delay(10000);
		  		 }
						 delay(10000);
						 delay(10000);
						 delay(10000);
						 
			uart0_puts (UART0_SPACE);
			delay(10000);
			delay(10000);

			uart0_puts(UART0_GPS2);	  // Transffer data to PC through Serial
			delay(10000);

				for(k=0;k<10;k++)
		   		{
		   		//lcd_putchar(lat[k]);
				 uart0_putc(lg[k]);
				 delay(10000);
		  		 }

			//uart0_puts (UART0_NEWLINE);
			delay(10000);
			uart0_putc(0x1A);
	  */
}



void send_loc_to_pc()
{

			uart0_init();
		
				
 			uart0_puts (UART0_GPS_PC);
			  // Transffer data to PC through Serial
			
			for(i=0;i<5;i++)
			{
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			}
		
			delay(10000);
				for(k=0;k<2;k++)
		   		{
				 uart0_putc(lat[k]);
				 delay(10000);
		  		}

				uart0_putc(0x2E);
				delay(10000);
				for(k=2;k<4;k++)
		   		{
				 uart0_putc(lat[k]);
				 delay(10000);
		  		}
			
				for(k=5;k<9;k++)
		   		{
				 uart0_putc(lat[k]);
				 delay(10000);
		  		}
			
						 delay(10000);
						 delay(10000);
						 delay(10000);
				uart0_putc(0x2C);		 
						  delay(10000);
						 delay(10000);
						 delay(10000);
				for(k=1;k<3;k++)
		   		{
				 uart0_putc(lg[k]);
				 delay(10000);
		  		}

				uart0_putc(0x2E);
				delay(10000);
				for(k=3;k<5;k++)
		   		{
				 uart0_putc(lg[k]);
				 delay(10000);
		  		}	

				for(k=6;k<10;k++)
		   		{
				 uart0_putc(lg[k]);
				 delay(10000);
		  		}

			delay(10000);
			delay(10000);
			delay(10000);

			uart0_putc(0x1A);

		for(i=0;i<10;i++)
			{
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);																					   
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			
			delay(10000);
			delay(10000);
			delay(10000);
			}


}


/**
**************************************************************************

****1111
  Function Name : delay()

  Description :This function suspends the tasks for specified ticks.	

  Input :  ticks:no of ticks in multiple of 1 usec
            task: task to be suspended

  Output : void

  Note :
*******************************************************************************
*/


void delay( unsigned long int count)
{
  unsigned long int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}

  




/****************/
/* main program */
/****************/
int main (void)  {                /* execution starts here                    */
			int count,count1, rec_rec;
			 int d=0;
	PINSEL0 = 0x00000000 ;   // Configure P0.0 to P0.15 as GPIO
	PINSEL1 = 0x00000000 ;   // Configure P0.16 to P0.31 as GPIO
    IO0DIR = 0x00000030 ;     // Configure P0.10 to P0.13 and P0.18 to
			//char gpsinit;
  uart1_init();
  //uart0_init();					  // Initialize UART0
  init_lcd();
	
 
 		gps();	
		/*	
		//	uart0_puts (UART0_NEWLINE_PC);
		*/	
		send_loc_to_pc();

	
			

  count =0;
  while(1)                        /* An embedded program does not stop */
  {
			    
				count =0;
				count1=0;
			    uart0_puts(DELET_SMS_ALL);
				for(i=0;i<5;i++)
				{
			    delay(10000);
			    delay(10000);
			    delay(10000);
			
			    delay(10000);
			    delay(10000);
			    delay(10000);
			    delay(10000);
			    delay(10000);
			    delay(10000);
			    delay(10000);
			    delay(10000);
			    delay(10000);
				}
					while(rec_rec != ':')
					{
						rec_rec = 	uart0_getkey();
					}
							for(i=0;i<7;i++)
							{
						//	 if(rec_rec == '+')
						    delay(10000);
						    delay(10000);
						    delay(10000);
						
						// 		 Receive_byte[i] = rec_rec;
							 delay(10000);
							     delay(10000);
						    delay(10000);
						    delay(10000);
						
						// 		 Receive_byte[i] = rec_rec;
							 delay(10000);
						    delay(10000);
						    delay(10000);
						    delay(10000);
						
						// 		 Receive_byte[i] = rec_rec;
							 delay(10000);
							     delay(10000);
						    delay(10000);
						    delay(10000);
						
						// 		 Receive_byte[i] = rec_rec;
							 delay(10000);
							 }

					     uart0_puts(SMS_READ);
//	 delay(10000);

					 	while(1)
						{
						   if(rec_rec == ':')
						    count1++;
							rec_rec = 	uart0_getkey();
							if(count1 == 3)
							 break;
						}

	 while(1)
	 {				   //IO0SET = 0x00000030;                                                      //P0.21 as Output                          
				 	 rec_rec = 	uart0_getkey();
					 if( rec_rec == 0xA)
					 {
					   count++;
					   rec_rec = uart0_getkey();
					 }
			// 	 	 rec_rec = 	uart0_getkey();

						 if(count == 1)
						 {
				

							  if( rec_rec == 'C')
		 				    {
							SPD_50:
									lcd_clear();	
							  		lcd_putstring(0,"TRAIN VADODARA");
							  		lcd_putstring(1,"STARTED");
									
									//Train_flag = 1;
									  rec_rec=0;
									  rec_rec = uart0_getkey1();
								//	  rec_rec=0;
									  rec_rec = uart0_getkey1();
									  rec_rec=0;

									  while(rec_rec == 0)
									  {
									  
					     				IO0SET = 0x00000010;				

					
										       for(d=0; d<10; d++);		
												{
											    delay(50000);
		//										rec_rec = uart0_getkey1();
     											 }		// delay

                        						 IO0CLR = 0x00000010; 	// SET (1) P0.10 to P0.13 and 
                                                                         // P0.18 to P0.21, LEDs OFF
		   
		  
												for(d=0; d<10; d++);		
												{
												    delay(50000);
		//											rec_rec = uart0_getkey1();

												 }		// delay
											rec_rec = uart0_getkey1();
					 
									   }
									lcd_putstring(1,"STOPPED ");

									/*uart0_puts(DELET_SMS_ALL);
									for(i=0;i<5;i++)
									{
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
								    delay(10000);
									}  */
									// rec_rec=0;
									count=0;
									
									break;
				
							   }
						   else if ( rec_rec == 'A')
						   {
						   	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"STOPPED");

													//train_flag=0;
							 //rec_rec=0;
								//	  rec_rec = uart0_getkey();
											  rec_rec=0;
									  rec_rec = uart0_getkey1();
								//	  rec_rec=0;
									  rec_rec = uart0_getkey1();
									  rec_rec=0;
			 

									  while(rec_rec == 0)
									  {
								
							 IO0CLR = 0x00000010; 	
							  
		  
												for(d=0; d<10; d++);		
												{
												    delay(50000);
												 }		// delay
									  rec_rec = uart0_getkey1();
					 		
											}

							//count=0;
							
							break;
				
						   }
						   else if ( rec_rec == 'B')
						   {
						   	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"RUNNING AT 25%");
						//	Train_flag = 2;
						  rec_rec=0;
									 // rec_rec = uart0_getkey();
					 
									  rec_rec=0;
									  rec_rec = uart0_getkey1();
								//	  rec_rec=0;
									  rec_rec = uart0_getkey1();
									  rec_rec=0;
											
									  while(rec_rec == 0)
									  {
									  
							 			IO0SET = 0x00000010;				

					
										       for(d=0; d<2; d++);		
												{
											    delay(50000);
												 }		// delay

                        						 IO0CLR = 0x00000010; 	// SET (1) P0.10 to P0.13 and 
                                                                         // P0.18 to P0.21, LEDs OFF
		   
		  
												for(d=0; d<20; d++);		
												{
												    delay(50000);
												 }		// delay
									rec_rec = uart0_getkey1();
					 	
					 }
					 goto SPD_75;
					 						   	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"STOPPED");

							//count=0;
							
							break;
				
						   }

						   else if ( rec_rec == 'D')
						   {
						   SPD_75:	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"RUNNING AT 75%");

								//Train_flag =3;
								rec_rec=0;
									  rec_rec = uart0_getkey1();
								//	  rec_rec=0;
									  rec_rec = uart0_getkey1();
									  rec_rec=0;

									 // rec_rec = uart0_getkey();
					 

									  while(rec_rec == 0)
									  {
									  
											 IO0CLR = 0x00000010;				

					
										       for(d=0; d<10; d++);		
												{
											    delay(50000);
												 }		// delay

                        						 IO0SET = 0x00000010; 	// SET (1) P0.10 to P0.13 and 
                                                                         // P0.18 to P0.21, LEDs OFF
		   
		  
												for(d=0; d<2; d++);		
												{
												    delay(50000);
												 }		// delay
								rec_rec = uart0_getkey1();
					 		
						}
						goto SPD_100;		//count=0;
													   	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"STOPPED");

							break;
				
						   }
						  
						   else if ( rec_rec == 'E')
						   {
							 SPD_100:
						   	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"RUNNING AT 100%");

											  //Train_flag = 4;
							  rec_rec=0;
									  rec_rec = uart0_getkey1();
					 				  rec_rec = uart0_getkey1();
										rec_rec=0;

									  while(rec_rec == 0)
									  {
									 
							 IO0SET = 0x00000010; 	
							  
		  
												for(d=0; d<10; d++);		
												{
												    delay(50000);
												 }		// delay
									 rec_rec = uart0_getkey1();
					 	
								   }
							 goto SPD_50;
                        	 
							 IO0CLR = 0x00000010; 	// SET (1) P0.10 to P0.13 and 

						   	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"STOPPED");

							//count=0;
							
							break;
				
						   }


						     else if ( rec_rec == 'G')
						   {
						   	lcd_clear();	
							//gps();
							lcd_putstring(0,"LOCATION");
					  		lcd_putstring(1,"SENDING");
							delay(10000);
							delay(10000);
							delay(10000);
							delay(10000);
							

							send_loc_to_pc();
							
							delay(10000);
							lcd_clear();
							lcd_putstring(0,"LOCATION");
					  		lcd_putstring(1,"SENT");
							delay(10000);

					  		break;	
						   }
						  else
						  {
						  	lcd_clear();	
					  		lcd_putstring(0,"TRAIN VADODARA");
					  		lcd_putstring(1,"NOT AVAILABLE");
							 //count=0;
							break;	  						  	
						  	
						 
					  		
				
						  }
						  
					}
						 else
						 {
						  
						 }


	
			 }
  		}
	    }	 
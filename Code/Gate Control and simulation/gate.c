#include <P89V51Rx2.H>
sbit sen1 = P3^2;
sbit sen2 = P3^3;
sbit buzzer = P1^0;	
sbit green = P1^2;
sbit red = P1^1;	

void delay(double n)
{
		double i,j;
	for(i=0;i<n;i++);
		  for(j=0;j<1000;j++);

}


void close()
{				   		
 							buzzer = 1;
							delay(20000);
							buzzer = 0;

							red = 0;
							green = 1;

						
									 P2=0x09;
									 delay(1); 	
									 P2=0x0a;
									 delay(1);
						             P2=0x06;
									 delay(1);
									 P2=0x05;
									 delay(1); 
									 P2=0x09;
									 delay(1); 	
									 P2=0x0a;
									 delay(1);

					          
}

void open()
{
							
								buzzer = 1;
								delay(20000);
								buzzer = 0;
							
										     P2=0x0a;
											 delay(1);  
											 P2=0x09;
											 delay(1); 
											 P2=0x05;
											 delay(1); 	
											 P2=0x06;
											 delay(1);
								             P2=0x0a;
											 delay(1);
											 P2=0x09;
											 delay(1); 
										
											
										

	          		
							
							
								green = 0;
								red = 1;
}





     void main(void)
	{
	     
		  
		 P2=0x00;
		 P1=0x00;
		 P3=0x00;

		 red=1;
		
		for(;;)
	{
		if(sen1 == 1)
		{
			delay(10000);
			if(sen1 == 1)
			{
			close();

			while(sen2 == 0);
			delay(5000);
			while(sen2 == 1);
		
	
			open();
			}
	  	}
		
		if(sen2 == 1)
		{
			delay(10000);
			if(sen2 == 1)
			{
			close();

			while(sen1 == 0);
			delay(5000);
			while(sen1 == 1);
		
	
			open();
			}
	  	}
		
				
		
	}
}
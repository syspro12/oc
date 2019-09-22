
//Sun
/*

Write a SMAC0 CPU simulator program in C for the following instruction set
Mnemonic Opcode Meaning
MOVER    04     Move memory operand contents to register
MOVEM    05     Move register operand contents to memory
READ     09     Read into memory operand
PRINT    10     Print contents of memory operand
COMP     06     Compare register & mem operand to set
				condition code appropriately
BC       07     Branch to 2nd operator depending on cond
				code specified as 1st operand
MULT     03     Multiply memory operand to register operand
DIV      08     Divide memory operand to register operand
ADD      01     Add memory operand to register operand
SUB      02     Subtract memory operand to register operand
STOP     00     Stop of halt execution

Assemble following program manually and execute it using above simulator.
//Progran to find if the given number is maximum of 2 nos

		READ N1
		READ N2
		MOVER AREG, N1
		COMP AREG, N2
		BC GT SHOW
		PRINT N2
		STOP
	SHOW PRINT N1
		STOP
  		N1 DS 1
  		N2 DS 1
		END

*/

#include<stdio.h>
#include<stdlib.h>


long memory[1000] ;
int pc , opcode , reg , address ;
int registers[4] , flag[] = {0,0,0,0,0,1};
long op1 , op2 ;
//main() 
main(char *argv[] , int argc)
{
	FILE *fp ;
	int k ;
//	char filename[30];
	//	printf("Enter file name");
	//	scanf("%s",&filename);

		fp = fopen("filename","r");
               

		if(fp==NULL)
		{
			printf("Invalid file name.") ;
			exit(0) ;
		}
		else
		{	
			pc = 0 ;
				//reading machine code and storing in memory w.r.t pc(program counter)
			while(!feof(fp))
				fscanf(fp,"%ld",&memory[pc++]) ;
			k = pc-1 ;
			//after storing is done re-intialize pc to 0
			pc=0 ;
			
			while(1) 
			{	//formulae for storing opcode register and address in those variables
				opcode = memory[pc]/10000 ;
				reg = ((memory[pc]%10000)/1000) ;
				address = (memory[pc]%10000)%1000 ;
				
				switch(opcode)
				{
					case 0 :
						exit(0) ;
					break ;
					
					case 1 :	//adding and storing answer in register
						registers[reg]+=memory[address] ;
					break ;
					
					case 2 :	//subtracting and storing answer in register
						registers[reg]-=memory[address] ;
					break ;
					
					case 3 :	//multiply and stores answer in register
						registers[reg]*=memory[address] ;
					break ;
					
					case 4 :	//mover
						registers[reg]=memory[address] ;
					break ;
					
					case 5 :	//movem 
						memory[address]=registers[reg] ;
					break ;
					
					case 6 :	//compare op1 and op2 will store values of what to be compared
						op1 = registers[reg] ;
						op2 = memory[address] ;
					break ;
										
					case 7 :	//bc 
						address = address-1 ;
						
						switch(reg)
						{
							case 0 :
								if(op1>op2)
									pc = address ;
								printf("\n%daddress : ",pc) ;
							break ;
							
							case 1 :
								if(op1>=op2)
									pc = address ;
							break ;
							
							case 2 :
								if(op1==op2)
									pc = address ;
							break ;
							
							case 3 :
								if(op1<op2)
									pc = address ;
							break ;
							
							case 4 :
								if(op1<=op2)
									pc = address ;
							break ;
							
							case 5 :
								pc = address ;
							break ;
						}
					break ;
					
					case 8 :	//div
						memory[address]/=registers[reg] ;
					break ;
					
					case 9 :	//read
						printf("Enter the value : ") ;
						scanf("%ld",&memory[address]) ;
					break ;
					
					case 10 :	//accept i/p
					  if(memory[address]==1)
						//printf("Answer is : %ld\n",memory[address]) ;
					    printf("Number 1 is greater\n");
					  else
					    printf("Number 2 is greater\n");
					break ;
				}
				pc++ ;
			}
		}
	return 0 ;
}

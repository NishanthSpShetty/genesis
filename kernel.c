/*
   kernel.c
 */

void kmain(void){
	const char *str = "my first kernel";
	char *vidptr = (char*)0xb80000; //video memory address
	unsigned int i =0;
	unsigned int j = 0;

	/*clear the screen before printing
	  80 columns* 25 lines each of 2bytes
	  */
	while(j<80*25*2){
		/*blank char*/
		vidptr[j] = ' ';
		vidptr[j+1]=0x07 ; 
		j = j+2;
	}

	j=0;

	while(str[j]!='\0'){
		vidptr[i]=str[j];
		vidptr[i+1]=0x07;
		++j;
		i = i+2;
	}
	return;
}

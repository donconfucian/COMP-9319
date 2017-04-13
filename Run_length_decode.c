#include <stdio.h>
#include <stdlib.h>

int main(int argc , char *argv[]){
    if(argc == 2) // there is only one argument , get input and print the result to screen
    {

        FILE *inf;// claim for the input file;
        register int get_char; //get char from the file;
        register int count,base,dig;
        //count to save the original counter,base is the 128(since it is 7 bit),dig is the every 7 bit part of counter.

        if(!(inf=fopen(argv[1],"rb"))){//input file getted and status check;

            printf("Can not open input_file\n");
            exit(0);
        }

        get_char = fgetc(inf);
        //tar_char = get_char;
        while(get_char!= -1)
        {

            if(get_char<128){//if get_char is smaller than 128 , then it is a ASCII symbol;

                printf("%c",get_char);
            }else {//else it is a converted counter by the rlencode program;

                count = 0;//initial state is 0;
                base = 1; //depend on my rlencode program , we will deal with low part at first;
                while (get_char > 127) { //till the get_char is a counter;
                    dig = (get_char ^ 128);// take a xor operation to derive the original number;
                    count += dig * base;   // since we divided count into several 7 bit parts;
                    get_char = fgetc(inf); // get the next char;
                    base *= 128;           //next count digit will go to next 7 bit part;
                }
                printf("[%d]", count);//print the original count;
                if(get_char!=-1){//may have chance get the end of file ;
                    printf("%c",get_char);//the while loop break since we got a char, so we need to print it;
                }

            }
            get_char = fgetc(inf);//go to next round;
        }
        printf("\n");
        fclose(inf);



    }
    else //there are two arguments , get input and save the encoded result to a file
    {
        FILE *inf , *ouf;
        register int get_char,temp_char; //
        register int count,base,dig; //claim high frequency using var into register memo

        if(!(inf=fopen(argv[1],"rb"))){

            printf("Can not open input_file\n");
            exit(0);
        }
        if(!(ouf=fopen(argv[2],"wb"))){


            printf("Can not open output_file\n");
            exit(0);
        }


        get_char = getc(inf);

        while(get_char!= -1)
        {

            if(get_char<128){
                //printf("%c 1",get_char);
                temp_char=get_char;
                putc(get_char,ouf);
            }else {


                count = 0;
                base = 1;
                while (get_char > 127) {
                    dig = (get_char ^ 128);
                    count += dig * base;
                    get_char = getc(inf);
                    base *= 128;

                }
                count = count+3;
                while(count>0){
                    //printf("%c 2",get_char);
                    putc(temp_char,ouf);
                    count--;
                }

            }
            get_char = getc(inf);
        }

        fclose(inf);
        fclose(ouf);

    }


}

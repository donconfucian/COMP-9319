#include <stdio.h>
#include <stdlib.h>

int main(int argc , char *argv[]){
    if(argc == 2) // there is only one argument , get input and print the result to screen;
    {

        FILE *inf;//name the input file;
        char tar_char , get_char; //tar_char to save a target char,get_char to get from input file;
        register int count; //claim a counter to save the occurrence of a char;

        if(!(inf=fopen(argv[1],"rb"))){//get input file and status check;

            printf("Can not open input_file\n");
            exit(0);
        }

        get_char = getc(inf);//get char from file;
        tar_char = get_char;//save the target in the first time;
        count = 1;//turn count to 1;
        while(get_char!=EOF)//while the file is not end,go through the while loop;
        {
            get_char=getc(inf);//get char from input file
            if(tar_char==get_char){//if getted char is equal to the target char;
                count++;// count add 1;

            }
            else if(count==1){//when mismatch char, case 1:count equals to 1;
                printf("%c",tar_char);//print target char for one time;
                tar_char=get_char;//go to next round
                count = 1;
            }else if(count==2) {//when mismatch char, case 2:count equals to 2;
                printf("%c",tar_char);//print target char for two times;
                printf("%c",tar_char);
                tar_char = get_char;//go to next round
                count = 1;
            }else {
                printf("%c[%d]",tar_char,count-3);//print target char and occurrence to screen;
                tar_char = get_char;//go to next round
                count = 1;

            }
        }
        printf("\n");
        fclose(inf);//in the end,close the file is a good habit;



    }
    else //there are two arguments , get input and save the encoded result to a file
    {
        FILE *inf , *ouf;//name the input file;
        char tar_char , get_char , bic; //tar_char to save a target char,get_char to get from input file;
        register int count,num_len,mod,val; //claim a counter to count occurrence,

        if(!(inf=fopen(argv[1],"rb"))){//get input file and status check;

            printf("Can not open input_file\n");
            exit(0);
        }
        if(!(ouf=fopen(argv[2],"wb"))){//get input file and status check;


            printf("Can not open output_file\n");
            exit(0);
        }


        get_char = getc(inf);//get char from file;
        tar_char = get_char;//save the target in the first time;
        count = 1;//turn count to 1;
        while(get_char!=EOF)//while the file is not end,go through the while loop;
        {
            get_char=getc(inf);//get char from file;
            if(tar_char==get_char){//if getted char is equal to the target char;
                count++;//count add 1;

            }
            else if(count==1){//when mismatch char, case 1:count equals to 1;
                putc(tar_char,ouf);//put tar_char to output file;
                tar_char=get_char;
                count = 1;
            }else if(count==2) {//when mismatch char, case 2:count equals to 2;
                putc(tar_char, ouf);//put tar_char to output file twice;
                putc(tar_char, ouf);
                tar_char = get_char;
                count = 1;
            }else if(count<128){//when mismatch char, case 3:count less than 128;
                putc(tar_char, ouf);//put tar_char to output file;
                count = count -3;   //count start from 3;
                bic = (count | 128);//use "or" operation with 128(1000 0000) to turn count into signed mode;
                putc(bic,ouf);
                tar_char = get_char;
                count = 1;

            }else{//when mismatch char, case 4:count greater than 128;
                putc(tar_char, ouf);//put tar_char to output file;
                count = count -3;   //count start from 3;
                while(count/128>=1) //while count is greater than 128, save the mode part to file;
                {
                    mod = count%128;//save the number from low part to high part;
                    bic = (mod|128);
                    putc(bic,ouf);
                    count = count/128;

                }
                bic = (count|128);//deal with the largest part;
                putc(bic,ouf);
                tar_char = get_char;
                count = 1;

            }
        }
        fclose(inf);
        fclose(ouf);

    }


}

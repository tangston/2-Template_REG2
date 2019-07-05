#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define  offset_left     8 ;
#define  offset_right    16  ;
    
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]);
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]);

void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]);
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]);

void delay(void);

void delay(void){
    
    int count =0x23000;
    while(count--);
}
int main (void){

    GPIO_InitTypeDef    GPIO_Initialize_Structure;
    int x,count=0;   
    uint32_t    GPIO_Pin_x[17]={ GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7
                            ,GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15,GPIO_Pin_All};
    
    /*以下是本人观摩老师直接写入32位操作寄存器的寄存器编程方法，自己发现规律后得出的结果。湖大设计的板子毕竟没原理图*/                        
    
    //打开AFIO，我估摸着是LED和数码管是复用的，所以需要另外复用AFIO来配置这俩谁亮谁不亮的问题
    RCC->APB2ENR|=1<<0;	
     // 打开 GPIOB segment selection SEL 端口的时钟
	RCC->APB2ENR  |=  ( (1) << 3 );
	// 打开 GPIOE LED 端口的时钟
	RCC->APB2ENR  |=  ( (1) << 6 );
    AFIO->MAPR |= 0x02000000;//关闭JTAG-DP，启用SW-DP，有人回看到这里的话，不明白就去翻手册，里面有，以后解释官方库的时候编者再注释目录索引
     /*******  你敢信，我们学校跑个LED的门路都那么多。学过数字逻辑之后应该明白，数字设备使用需要方波驱动    
     *******   所以以后的每个功能块的驱动，都有各自的时钟晶振，正是因为STM32过于强大，所以他默认所有时钟端口都是关闭的
     *******   全部打开的话，能耗会出奇的高，板子能煎鸡蛋                 
     *******/
                            
    GPIO_Initialize_Structure.GPIO_Speed=  GPIO_Speed_10MHz;
    GPIO_Initialize_Structure.GPIO_IOtype= GPIO_IOtype_Output_PushPull;
    
  
    /*配置GPIOE LED灯是 pin8到pin15位推挽输出*/
    for(x=8;x<=15;x++){
        GPIO_Initialize_Structure.GPIO_Pin= GPIO_Pin_x[x];
        GPIO_Init(GPIOE, &GPIO_Initialize_Structure);
    }
    
    /*配置GPIOB 的什么鬼东西  pin0到pin3 位推挽输出,至于为什么我还不清楚*/
    /*2019/6/24查阅原理图发现，GPIOB的Pin3是select LED，而Pin0-pin2有3个管脚，能代表2的三次方=8种状态，意味着使能哪个数码管*/
    
    for(x=0;x<=3;x++){
        GPIO_Initialize_Structure.GPIO_Pin= GPIO_Pin_x[x];
        GPIO_Init(GPIOB, &GPIO_Initialize_Structure);
        /*配置GPIOB 的 pin0到pin3 位设置高电平*/ 
        GPIO_ResetBits(GPIOB,GPIO_Pin_x[x]);
    } 
    
      GPIO_SetBits(GPIOB,GPIO_Pin_x[3]);//select LED置高电平是让LED导通
   // GPIO_SetBits(GPIOE,GPIO_Pin_9);//32位的STM32，1个pin，需要1*4位来配置，这里是亮LED灯的第L1,跑马灯程序已经写出来了，不用这个测试函数了，不然第一次老是亮L0
/**************************************     up above are for all stm32 initialize GPIOs  *************************************************************************************************/
    
/**************************************     down below are the true main program *************************************************************************************************/    
    while(1){
       
        if(count<=0x10){
            
            led_mode1_left(&count,GPIO_Pin_x);
            //count++; //调试的时候请注释上面一行，取消注释该行
        }
        else if(count>0x10&&count<=0x20){
            
            led_mode2_left(&count,GPIO_Pin_x);
             //count++; //调试的时候请注释上面一行，取消注释该行
        }
        else if(count>0x20&&count<=0x30){
            
            led_mode2_right(&count,GPIO_Pin_x);
            //count++; //调试的时候请注释上面一行，取消注释该行
        }
        else{
            
            led_mode1_right(&count,GPIO_Pin_x);
            //count++; //调试的时候请注释上面一行，取消注释该行
        }
        
       count %=0x40;
      
      
    }
    
   // return 0;


}


/*仅一个灯亮的左右方向跑马*/
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]){
    //初始化一下跑马灯为全灭 
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[16]);
    
    
    int led_number=*the_first_light;//备份一下，主要操作备份
    (* the_first_light)++;
    
    //led是GPIOE的pin8到15
    led_number %=8;
    led_number+=offset_left;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
     
}
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]){
     //初始化一下跑马灯为全灭
      GPIO_ResetBits(GPIOE,GPIO_Pin_x[16]);
    
    int led_number=-(*the_first_light);//备份一下，主要操作备份
    (* the_first_light)++;
    
    //led是GPIOE的pin8到15
   // led_number-=64;//变成负数
    led_number %=8;
    if(led_number==0){led_number --;}//led_number=0呃话，会被置位成全亮，这里复制粘贴的时候搞反了，懒得改代码，干脆改参数
    
    led_number+=offset_right;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    
     
}


/*仅一个灯灭的左右方向跑马*/
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]){
     GPIO_SetBits(GPIOE,GPIO_Pin_x[16]);//初始化为全亮
    
    
    int led_number=*the_first_dark;//备份一下，主要操作备份
    
    (* the_first_dark)++;
    
    //led是GPIOE的pin8到15
    led_number %=8;
    led_number+=offset_left;
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
   
   
     
}
void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_x[16]);//初始化为全亮
    
    int led_number=-(*the_first_dark);//备份一下，主要操作备份
    
    (* the_first_dark)++;
    
    //led是GPIOE的pin8到15
    led_number %=8;  
    led_number+=offset_right;
    if(led_number==16){led_number --;}//led_number=16呃话，会被置位成全灭
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();

    
     
}

void SystemInit(void){
    
  

}



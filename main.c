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
    
    /*�����Ǳ��˹�Ħ��ʦֱ��д��32λ�����Ĵ����ļĴ�����̷������Լ����ֹ��ɺ�ó��Ľ����������Ƶİ��ӱϾ�ûԭ��ͼ*/                        
    
    //��AFIO���ҹ�������LED��������Ǹ��õģ�������Ҫ���⸴��AFIO����������˭��˭����������
    RCC->APB2ENR|=1<<0;	
     // �� GPIOB segment selection SEL �˿ڵ�ʱ��
	RCC->APB2ENR  |=  ( (1) << 3 );
	// �� GPIOE LED �˿ڵ�ʱ��
	RCC->APB2ENR  |=  ( (1) << 6 );
    AFIO->MAPR |= 0x02000000;//�ر�JTAG-DP������SW-DP�����˻ؿ�������Ļ��������׾�ȥ���ֲᣬ�����У��Ժ���͹ٷ����ʱ�������ע��Ŀ¼����
     /*******  ����ţ�����ѧУ�ܸ�LED����·����ô�ࡣѧ�������߼�֮��Ӧ�����ף������豸ʹ����Ҫ��������    
     *******   �����Ժ��ÿ�����ܿ�����������и��Ե�ʱ�Ӿ���������ΪSTM32����ǿ��������Ĭ������ʱ�Ӷ˿ڶ��ǹرյ�
     *******   ȫ���򿪵Ļ����ܺĻ����ĸߣ������ܼ弦��                 
     *******/
                            
    GPIO_Initialize_Structure.GPIO_Speed=  GPIO_Speed_10MHz;
    GPIO_Initialize_Structure.GPIO_IOtype= GPIO_IOtype_Output_PushPull;
    
  
    /*����GPIOE LED���� pin8��pin15λ�������*/
    for(x=8;x<=15;x++){
        GPIO_Initialize_Structure.GPIO_Pin= GPIO_Pin_x[x];
        GPIO_Init(GPIOE, &GPIO_Initialize_Structure);
    }
    
    /*����GPIOB ��ʲô����  pin0��pin3 λ�������,����Ϊʲô�һ������*/
    /*2019/6/24����ԭ��ͼ���֣�GPIOB��Pin3��select LED����Pin0-pin2��3���ܽţ��ܴ���2�����η�=8��״̬����ζ��ʹ���ĸ������*/
    
    for(x=0;x<=3;x++){
        GPIO_Initialize_Structure.GPIO_Pin= GPIO_Pin_x[x];
        GPIO_Init(GPIOB, &GPIO_Initialize_Structure);
        /*����GPIOB �� pin0��pin3 λ���øߵ�ƽ*/ 
        GPIO_ResetBits(GPIOB,GPIO_Pin_x[x]);
    } 
    
      GPIO_SetBits(GPIOB,GPIO_Pin_x[3]);//select LED�øߵ�ƽ����LED��ͨ
   // GPIO_SetBits(GPIOE,GPIO_Pin_9);//32λ��STM32��1��pin����Ҫ1*4λ�����ã���������LED�Ƶĵ�L1,����Ƴ����Ѿ�д�����ˣ�����������Ժ����ˣ���Ȼ��һ��������L0
/**************************************     up above are for all stm32 initialize GPIOs  *************************************************************************************************/
    
/**************************************     down below are the true main program *************************************************************************************************/    
    while(1){
       
        if(count<=0x10){
            
            led_mode1_left(&count,GPIO_Pin_x);
            //count++; //���Ե�ʱ����ע������һ�У�ȡ��ע�͸���
        }
        else if(count>0x10&&count<=0x20){
            
            led_mode2_left(&count,GPIO_Pin_x);
             //count++; //���Ե�ʱ����ע������һ�У�ȡ��ע�͸���
        }
        else if(count>0x20&&count<=0x30){
            
            led_mode2_right(&count,GPIO_Pin_x);
            //count++; //���Ե�ʱ����ע������һ�У�ȡ��ע�͸���
        }
        else{
            
            led_mode1_right(&count,GPIO_Pin_x);
            //count++; //���Ե�ʱ����ע������һ�У�ȡ��ע�͸���
        }
        
       count %=0x40;
      
      
    }
    
   // return 0;


}


/*��һ�����������ҷ�������*/
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]){
    //��ʼ��һ�������Ϊȫ�� 
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[16]);
    
    
    int led_number=*the_first_light;//����һ�£���Ҫ��������
    (* the_first_light)++;
    
    //led��GPIOE��pin8��15
    led_number %=8;
    led_number+=offset_left;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
     
}
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]){
     //��ʼ��һ�������Ϊȫ��
      GPIO_ResetBits(GPIOE,GPIO_Pin_x[16]);
    
    int led_number=-(*the_first_light);//����һ�£���Ҫ��������
    (* the_first_light)++;
    
    //led��GPIOE��pin8��15
   // led_number-=64;//��ɸ���
    led_number %=8;
    if(led_number==0){led_number --;}//led_number=0�������ᱻ��λ��ȫ�������︴��ճ����ʱ��㷴�ˣ����øĴ��룬�ɴ�Ĳ���
    
    led_number+=offset_right;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    
     
}


/*��һ����������ҷ�������*/
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]){
     GPIO_SetBits(GPIOE,GPIO_Pin_x[16]);//��ʼ��Ϊȫ��
    
    
    int led_number=*the_first_dark;//����һ�£���Ҫ��������
    
    (* the_first_dark)++;
    
    //led��GPIOE��pin8��15
    led_number %=8;
    led_number+=offset_left;
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
   
   
     
}
void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_x[16]);//��ʼ��Ϊȫ��
    
    int led_number=-(*the_first_dark);//����һ�£���Ҫ��������
    
    (* the_first_dark)++;
    
    //led��GPIOE��pin8��15
    led_number %=8;  
    led_number+=offset_right;
    if(led_number==16){led_number --;}//led_number=16�������ᱻ��λ��ȫ��
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();

    
     
}

void SystemInit(void){
    
  

}



//���뻷����Visual C++ 6.0��EasyX_20190219(beta)
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
  
void pen()
 {
     int x0, y0;  
     MOUSEMSG m;        // ���������Ϣ
     while (true)
     {
     flag:                //���ÿ�ʼ
         m = GetMouseMsg();// ��ȡһ�������Ϣ
         switch (m.uMsg)

         {
         case WM_LBUTTONDOWN:x0 = m.x; y0 = m.y;    //����һ�ΰ���ʱ���õ����꣨x0,y0��
             while (true)
             {
                 m = GetMouseMsg();// ��ȡһ�������Ϣ
                 line(x0, y0, m.x, m.y);
                 x0 = m.x; y0 = m.y;
                 switch (m.uMsg)
                 {
                 case WM_LBUTTONUP:
                     goto flag;   //���ص�flag����������
                     break;     
                 }
             }
             break;   
         }
     }
 } 
void main()
{        
    initgraph(640, 480); 
	setcolor(YELLOW);
    MOUSEMSG m;   
	while(true)
	   {pen();}
}


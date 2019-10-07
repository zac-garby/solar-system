 # include <iostream.h>
 # include <graphics.h>
 # include <stdlib.h>
 # include <conio.h>
 # include <math.h>
 # include <dos.h>


 /*************************************************************************///-------------------------------  Planet  ------------------------------///*************************************************************************/class Planet
 {
    private:
       int x;
       int y;
       int rx;
       int ry;
       int color;
       int radius;
       int position;

       float displacement;

       char* Buffer;

    public:
       Planet( )   { x=y=rx=ry=radius=0; }
       ~Planet( )  { delete Buffer; }
       Planet(constint,constint,constint,constfloat);

       void Show( );
       void Move( );
       void ShowOrbit( );
       void GetNextPosition( );
 };

 /*************************************************************************///-----------------------------  Planet( )  -----------------------------///*************************************************************************/

 Planet::Planet(constint _rx,constint _ry,constint _radius,
                         constfloat _displacement)
 {
    rx=_rx;
    ry=_ry;

    x=(319+rx);
    y=240;

    radius=_radius;
    displacement=_displacement;
    position=0;
 }

 /*************************************************************************///----------------------------  ShowOrbit( )  ---------------------------///*************************************************************************/void Planet::ShowOrbit( )
 {
    setcolor(1);
      ellipse(320,240,0,360,rx,ry);
 }

 /*************************************************************************///--------------------------------  Show( )  ----------------------------///*************************************************************************/void Planet::Show( )
 {
    color=(random(14)+8);

    if(color==8 || color==14 || color==16)
       color=(random(6)+1);

    Buffer=newchar[imagesize((x-(radius+3)),(y-(radius+3)),
                        (x+radius+3),(y+radius+3))];

    getimage((x-(radius+3)),(y-(radius+3)),(x+radius+3),(y+radius+3),Buffer);

    setcolor(color);
    setfillstyle(1,color);
      pieslice(x,y,0,360,radius);

    setcolor(11);
      circle(x,y,radius);
 }

 /*************************************************************************///--------------------------------  Move  -------------------------------///*************************************************************************/void Planet::Move( )
 {
    putimage((x-(radius+3)),(y-(radius+3)),Buffer,0);

    delete Buffer;

    GetNextPosition( );

    Buffer=newchar[imagesize((x-(radius+3)),(y-(radius+3)),
                    (x+(radius+3)),(y+(radius+3)))];

    getimage((x-(radius+3)),(y-(radius+3)),(x+(radius+3)),
                        (y+(radius+3)),Buffer);

    setcolor(color);
    setfillstyle(1,color);
      pieslice(x,y,0,360,radius);

    setcolor((15-color));
      circle(x,y,radius);
 }

 /*************************************************************************///-------------------------  GetNextPosition( )  ------------------------///*************************************************************************/void Planet::GetNextPosition( )
 {
    float angle=(displacement*position);

    x=(int)(rx*cosl(angle)+320+0.5);
    y=(int)(ry*sinl(angle)+240+0.5);

    if((y==240 || y==239) && x>320)
       position=1;

    position++;
 }

 /*************************************************************************//*************************************************************************//*******************************  main( )  *******************************//*************************************************************************//*************************************************************************/void main( )
 {
    int driver=VGA;
    int mode=VGAHI;
    int error_code;

    initgraph(&driver,&mode,"..\\Bgi");

    error_code=graphresult( );

    if(error_code!=grOk)
    {
       restorecrtmode( );
       textmode(BW80);
       clrscr( );

       cout<<" \n Fatal Error  : Graphic Driver not initialized"<<endl;
       cout<<" Error Reason : "<<grapherrormsg(error_code)<<endl;
       cout<<" \n Press any key to exit...";

       getch( );
       exit(1);
    }

    setlinestyle(0,0,3);

    setcolor(7);
      rectangle(0,0,getmaxx( ),getmaxy( ));

    setlinestyle(0,0,0);

    for(int count=0;count<5000;count++)
       putpixel(random(640),random(480),random(15));

    settextstyle(2,0,7);
      setcolor(9);
    outtextxy(15,10,"Solar");
    outtextxy(16,10,"Solar");
    outtextxy(16,11,"Solar");

      setcolor(3);
    outtextxy(72,10,"System");
    outtextxy(73,10,"System");
    outtextxy(73,11,"System");

      setcolor(11);
    outtextxy(22,27,"Simulation");
    outtextxy(23,27,"Simulation");
    outtextxy(23,28,"Simulation");

    setcolor(7);
    settextstyle(2,0,4);
      outtextxy(10,465,"Press any key to exit.");

    setcolor(14);
    setfillstyle(1,14);
      pieslice(320,240,0,360,12);

   setcolor(12);
     circle(320,240,12);

   setcolor(4);
     circle(320,240,13);

    Planet Mercury(50,30,8,0.0175);
    Planet Venus(80,55,8,0.0155);
    Planet Earth(110,80,8,0.0135);
    Planet Mars(140,105,8,0.0115);
    Planet Jupiter(170,130,8,0.0095);
    Planet Saturn(200,155,8,0.0075);
    Planet Uranus(230,180,8,0.0055);
    Planet Neptune(260,205,8,0.0035);
    Planet Pluto(290,230,8,0.0015);

    Mercury.ShowOrbit( );
    Mercury.Show( );

    Venus.ShowOrbit( );
    Venus.Show( );

    Earth.ShowOrbit( );
    Earth.Show( );

    Mars.ShowOrbit( );
    Mars.Show( );

    Jupiter.ShowOrbit( );
    Jupiter.Show( );

    Saturn.ShowOrbit( );
    Saturn.Show( );

    Uranus.ShowOrbit( );
    Uranus.Show( );

    Neptune.ShowOrbit( );
    Neptune.Show( );

    Pluto.ShowOrbit( );
    Pluto.Show( );

    do
    {
       delay(25);

       Mercury.Move( );
       Venus.Move( );
       Earth.Move( );
       Mars.Move( );
       Jupiter.Move( );
       Saturn.Move( );
       Uranus.Move( );
       Neptune.Move( );
       Pluto.Move( );
    }
    while(!kbhit( ));

    getch( );
    closegraph( );
 }{\rtf1}
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
fstream file;
list<int> arr;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");



HMENU hmenu;
void AddMenus(HWND hwnd)
{
    hmenu = CreateMenu();
    HMENU hh = CreateMenu();

    AppendMenu(hmenu , MF_POPUP,(UINT_PTR)hh,"Graphics Menu");
    AppendMenu(hh,MF_STRING , 1,"Parametric Line");
    AppendMenu(hh,MF_STRING , 2,"Line DDA");
    AppendMenu(hh,MF_STRING , 3,"Line Mid");

    AppendMenu(hh,MF_STRING , 4,"Ellipse polar");
    AppendMenu(hh,MF_STRING , 5,"Direct Ellipse");

    AppendMenu(hh,MF_STRING , 6,"Mid Ellipse");
    AppendMenu(hh,MF_STRING , 7,"Beizer curve");
    AppendMenu(hh,MF_STRING , 8,"Hermite curve");
    AppendMenu(hh,MF_STRING , 9,"Splines curve");
    AppendMenu(hh,MF_STRING , 10,"PolygonClip");
    AppendMenu(hh,MF_STRING , 11,"LineClip");
    AppendMenu(hh,MF_STRING , 12,"Save");
    AppendMenu(hh,MF_STRING , 13,"load");

    //AppendMenu(hmenu , MF_STRING,1,"ParamLine");
    SetMenu(hwnd,hmenu);
}



int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
int Round(int val)
{

    return (int)(val+0.5);
}
void DrawLine(HDC hdc,int x1,int y1,int x2, int y2, COLORREF C)
{
    arr.push_back(x1);
    arr.push_back(y1);
    arr.push_back(x2);
    arr.push_back(y2);
    arr.push_back(900000000);
    arr.push_back(1);
    for(double t=0 ; t<=1 ; t+=0.001)
    {
        int x = Round(x1+t*(x2-x1));
        int y = Round(y1+t*(y2-y1));
        SetPixel(hdc , x,y,C);
    }

}

void DrawLineDDA(HDC hdc , int x1,int y1,int x2,int y2,COLORREF C)
{
    arr.push_back(x1);
    arr.push_back(y1);
    arr.push_back(x2);
    arr.push_back(y2);
    arr.push_back(900000000);
    arr.push_back(2);
    int x =x1,y= y1;
    int dx = x2-x1;
    int dy = y2-y1;
    int e = 2*dy-dx;
    int e1 = 2*(dy-dx);
    int e2 = 2*dy;
    SetPixel(hdc,x,y,C);
    while(x<x2)
    {
        x++;
        if(e>=0)
        {
            y++;
            e+=e1;
        }
        else e+=e2;
        SetPixel(hdc,x,y,C);
    }
}

void MidPointLine(HDC hdc, int x1,int y1,int x2,int y2,COLORREF C)
{
    arr.push_back(x1);
    arr.push_back(y1);
    arr.push_back(x2);
    arr.push_back(y2);
    arr.push_back(900000000);
    arr.push_back(3);
    int x=x1,y=y1,dx=x2-x1,dy=y2-y1;
    int d = dx + (2*dy+1-2*y1) - 2*dy*(x1+1-x1);
    SetPixel(hdc,x1,y1,C);
    while(x<x2)
    {
        if(d>0)
        {
            x++;
            d+=(-2*dy);
        }
        else
        {
            x++;
            y++;
            d+=(-2*dy)+(2*dx);
        }
        SetPixel(hdc,x,y,C);
    }
}

void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc + y, yc + x, c);
    SetPixel(hdc, xc - y, yc + x, c);
    SetPixel(hdc, xc - y, yc - x, c);
    SetPixel(hdc, xc + y, yc - x, c);
}


void DrawEllipsePolar(HDC hdc,int xc,int yc, int R1,int R2,COLORREF c)
{
    arr.push_back(xc);
    arr.push_back(yc);
    arr.push_back(R1);
    arr.push_back(R2);
    arr.push_back(900000000);
    arr.push_back(4);
    int x ,y;
    double theta = 0;
    while(theta <360)
    {
        x = R1*cos(theta) + xc;
        y = R2*sin(theta) +yc;
        theta+=0.01;
        SetPixel(hdc,x,y,c);
    }

}

void Ellipsee(HDC hdc,int xc,int yc, int R1,int R2,COLORREF c)
{
    arr.push_back(xc);
    arr.push_back(yc);
    arr.push_back(R1);
    arr.push_back(R2);
    arr.push_back(900000000);
    arr.push_back(5);
    int x =R1 ,y =R2;
    for(double t =0 ; t<=2 ; t+=0.001)
    {
        x = R1*cos(t);
        y = R2*sin(t);

        SetPixel(hdc, xc + x, yc + y, c);
        SetPixel(hdc, xc - x, yc + y, c);
        SetPixel(hdc, xc - x, yc - y, c);
        SetPixel(hdc, xc + x, yc - y, c);


    }
}

void DrawEllipsemid(HDC hdc,int xc,int yc, int R1,int R2,COLORREF c)
{
    arr.push_back(xc);
    arr.push_back(yc);
    arr.push_back(R1);
    arr.push_back(R2);
    arr.push_back(900000000);
    arr.push_back(6);
    int x = 0, y = R2;

    int p = pow(R2,2.0)- pow(R1,2)*R2 + pow(R1,2)/4;


    while(2.0*R2*R2*x <= 2.0*R1*R1*y)
    {
        if(p < 0)
        {
            x++;
            p = p+2*R2*R2*x+R2*R2;
        }
        else
        {
            x++;
            y--;
            p = p+2*R2*R2*x-2*R1*R1*y-R2*R2;
        }
        SetPixel(hdc, xc + x, yc + y, c);
        SetPixel(hdc, xc - x, yc + y, c);
        SetPixel(hdc, xc - x, yc - y, c);
        SetPixel(hdc, xc + x, yc - y, c);
    }

    p=R2*R2*(x+0.5)*(x+0.5)+R1*R1*(y-1)*(y-1)-R1*R1*R2*R2;
    while(y > 0)
    {
        if(p <= 0)
        {
            x++;
            y--;
            p = p+2*R2*R2*x-2*R1*R1*y+R1*R1;
        }
        else
        {
            y--;
            p = p-2*R1*R1*y+R1*R1;
        }
        SetPixel(hdc, xc + x, yc + y, c);
        SetPixel(hdc, xc - x, yc + y, c);
        SetPixel(hdc, xc - x, yc - y, c);
        SetPixel(hdc, xc + x, yc - y, c);
    }
}
void bezierCurveHDC( HDC hdc,int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,COLORREF c )
{
    arr.push_back(x0);
    arr.push_back(y0);
    arr.push_back(x1);
    arr.push_back(y1);
    arr.push_back(x2);
    arr.push_back(y2);
    arr.push_back(x3);
    arr.push_back(y3);
    arr.push_back(900000000);
    arr.push_back(7);
    double xu = 0.0 , yu = 0.0 , u = 0.0 ;
    for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
    {
        xu = pow(1-u,3)*x0+3*u*pow(1-u,2)*x1+3*pow(u,2)*(1-u)*x2
             +pow(u,3)*x3;
        yu = pow(1-u,3)*y0+3*u*pow(1-u,2)*y1+3*pow(u,2)*(1-u)*y2
             +pow(u,3)*y3;
        SetPixel(hdc, xu, yu, c);
    }
}


void hermiteCurve( HDC hdc,int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,COLORREF c )
{

    arr.push_back(x0);
    arr.push_back(y0);
    arr.push_back(x1);
    arr.push_back(y1);
    arr.push_back(x2);
    arr.push_back(y2);
    arr.push_back(x3);
    arr.push_back(y3);
    arr.push_back(900000000);
    arr.push_back(8);
    double xu = 0.0 , yu = 0.0 , u = 0.0 ;
    for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
    {
        xu=(2*pow(u,3)-3*pow(u,2)+1)*x0+(-2*pow(u,3)+3*pow(u,2))*x1+(pow(u,3)-2*pow(u,2)+u)*x2+(pow(u,3)-pow(u,2))*x3;
        yu=(2*pow(u,3)-3*pow(u,2)+1)*y0+(-2*pow(u,3)+3*pow(u,2))*y1+(pow(u,3)-2*pow(u,2)+u)*y2+(pow(u,3)-pow(u,2))*y3;
        SetPixel(hdc, xu, yu, c);

    }
}
void splines( HDC hdc,int x0,int y0,int x1,int y1,int x2,int y2,COLORREF c )
{
    arr.push_back(x0);
    arr.push_back(y0);
    arr.push_back(x1);
    arr.push_back(y1);
    arr.push_back(x2);
    arr.push_back(y2);
    arr.push_back(900000000);
    arr.push_back(9);
    double xu = 0.0 , yu = 0.0 , u = 0.0 ,s0,s1,s2,k0,k1,k2;
    s0=x0;
    s1=-3*x0+4*x1-x2;
    s2=2*x2-4*x1+2*x0;
    k0=y0;
    k1=-3*y0+4*y1-y2;
    k2=2*y2-4*y1+2*y0;
    for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
    {
        xu = s0+s1*u+s2*u*u;
        yu = k0+k1*u+k2*u*u;
        SetPixel(hdc, xu, yu, c);
    }
}
struct vertex
{

    double x, y;
    vertex(double x1=0 , double y1=0)
    {
        x = x1;
        y = y1;
    }
};
typedef bool (*Is_inside)(vertex& v,int edge);
typedef vertex (*Intersect)(vertex& v1,vertex& v2,int edge);
int Round(double x)
{
    return (int)(x+0.5);
}
void drawline(HDC hdc, int x1,int y1,int x2, int y2,COLORREF c)
{

    for(double t = 0; t <= 1; t += 0.001)
    {
        int x=Round(x1+(t*(x2-x1)));
        int y=Round(y1+(t*(y2-y1)));
        SetPixel(hdc,x,y,c);
    }

    /*
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    */
}

vector<vertex> ClipWithEdge(vector<vertex> p,int edge,Is_inside inside ,Intersect intersection )
{
    vector<vertex> output;
    vertex v = p[p.size()-1];
    bool v_inside = inside(v,edge);

    for(int i=0; i<(int)p.size(); i++)
    {
        vertex v2=p[i];
        bool v2_in=inside(v2,edge);
        if(!v_inside && v2_in)
        {
            output.push_back(intersection(v,v2,edge));
            output.push_back(v2);
        }
        else if(v_inside && v2_in) output.push_back(v2);
        else if(v_inside) output.push_back(intersection(v,v2,edge));
        v=v2;
        v_inside=v2_in;

    }
    return output;

}
bool InLeft(vertex& v,int edge)
{
    return v.x>=edge;
}
bool InRight(vertex& v,int edge)
{
    return v.x<=edge;
}
bool InTop(vertex& v,int edge)
{
    return v.y>=edge;
}
bool InBottom(vertex& v,int edge)
{
    return v.y<=edge;
}

vertex VIntersect(vertex& v1,vertex& v2,int xedge)
{
    vertex res;
    res.x=xedge;
    res.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
    return res;
}

vertex HIntersect(vertex& v1,vertex& v2,int yedge)
{
    vertex res;
    res.y=yedge;
    res.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
    return res;
}
void PolygonClip(HDC hdc,POINT *p,int n,int xleft,int ytop,int xright,int ybottom)
{
    arr.push_back(xleft);
    arr.push_back(ytop);
    arr.push_back(xright);
    arr.push_back(ybottom);
    arr.push_back(p[0].x);
    arr.push_back(p[0].y);
    arr.push_back(p[1].x);
    arr.push_back(p[1].y);
    arr.push_back(p[2].x);
    arr.push_back(p[2].y);
    arr.push_back(p[3].x);
    arr.push_back(p[3].y);
    arr.push_back(p[4].x);
    arr.push_back(p[4].y);
    arr.push_back(900000000);
    arr.push_back(10);
    vector<vertex> vlist;
    for(int i=0; i<n; i++)vlist.push_back(vertex(p[i].x,p[i].y));
    vlist=ClipWithEdge(vlist,xleft,InLeft,VIntersect);
    vlist=ClipWithEdge(vlist,ytop,InTop,HIntersect);
    vlist=ClipWithEdge(vlist,xright,InRight,VIntersect);
    vlist=ClipWithEdge(vlist,ybottom,InBottom,HIntersect);
    vertex v1=vlist[vlist.size()-1];
    for(int i=0; i<(int)vlist.size(); i++)
    {

        vertex v2=vlist[i];
        drawline(hdc,v1.x,v1.y,v2.x,v2.y,RGB(128,0,128));
        v1=v2;
    }
}
struct point
{
    int x,y;
};


union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y>ytop)
        out.top=1;
    else if(y<ybottom)
        out.bottom=1;
    return out;
}
pair<int, int> VIntersect(double xs,double ys,double xe,double ye,int x,double &xi,double &yi)
{
    pair<int,int> p;
    xi=x;
    yi=ys+(x-xs)*(ye-ys)/(xe-xs);
    p.first=xi;
    p.second=yi;
    return p;
}
pair<int, int> HIntersect(double xs,double ys,double xe,double ye,int y,double &xi,double &yi)
{
    pair<int,int> p;
    yi=y;
    xi=xs+(y-ys)*(xe-xs)/(ye-ys);
    p.first=xi;
    p.second=yi;
    return p;
}
void CohenSuth(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom,COLORREF C)
{
     arr.push_back(xs);
    arr.push_back(ys);
    arr.push_back(xe);
    arr.push_back(ye);
   arr.push_back(xleft);
    arr.push_back(ytop);
    arr.push_back(xright);
    arr.push_back(ybottom);
    arr.push_back(900000000);
    arr.push_back(11);
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);

    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);

    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        pair<int, int> point;
        double xi,yi;

        if(out1.All)
        {
            if(out1.left)
                point = VIntersect(x1,y1,x2,y2,xleft, xi, yi);
            else if(out1.top)
                point = HIntersect(x1,y1,x2,y2,ytop, xi, yi);
            else if(out1.right)
                point = VIntersect(x1,y1,x2,y2,xright, xi, yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom, xi, yi);
            x1=point.first;
            y1=point.second;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                point = VIntersect(x1,y1,x2,y2,xleft,xi,yi);
            else if(out2.top)
                point = HIntersect(x1,y1,x2,y2,ytop,xi,yi);
            else if(out2.right)
                point = VIntersect(x1,y1,x2,y2,xright,xi,yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom,xi,yi);
            x2=point.first;
            y2=point.second;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }

    if(!out1.All && !out2.All)
    {
        cout<<"ddddd"<<endl;
        drawline(hdc,x1,y1,x2,y2,C);


    }

}
void save()
{
    file.open("file.txt",ios::out);
    list< int> ::iterator it;
    for(it=arr.begin(); it!=arr.end(); ++it)
    {
        if(*it==900000000)
        {
            ++it;
            file<<"f"<<*it<<endl;
        }
        else
        {
            file<<*it<<" ";
        }

    }
    file.close();
    arr.clear();
}
void load(HDC hdc )
{
  file.open("file.txt",ios::in);
  string str ;string s = "";
  vector <int> v ;
  while(!file.eof()){

    getline(file,str);
    int idx = str.find('f') , x=0;
    for(int i=0 ; i<idx ; i++)
    {
        if(str[i] == ' ')
        {
            istringstream iss (s);
            iss >> x;
            v.push_back(x);
            s="";
            continue;
        }
        s += str[i];
    }
    string xx="";
    for(int t=idx+1 ; t< str.size();t++){
        xx+=str[t];
    }

    if(xx == "1"){
        DrawLine(hdc,v[0],v[1],v[2], v[3], RGB(0,0,0));
        v.clear();
    }
    else if(xx == "2"){
        DrawLineDDA(hdc,v[0],v[1],v[2], v[3],RGB(128,0,128));
        v.clear();
    }
    else if(xx == "3"){
        MidPointLine(hdc,v[0],v[1],v[2], v[3],RGB(128,200,128));
        v.clear();
    }
    else if(xx == "4"){
        DrawEllipsePolar(hdc , v[0],v[1],v[2],v[3],RGB(255,0,0));
        v.clear();
    }
    else if(xx == "5"){
        Ellipsee(hdc , v[0],v[1],v[2],v[3],RGB(255,0,0));
        v.clear();
    }
    else if(xx == "6"){
        DrawEllipsemid(hdc , v[0],v[1],v[2],v[3],RGB(255,0,0));
        v.clear();
    }
    else if(xx == "7"){
        bezierCurveHDC(hdc,v[0],v[1],v[2], v[3],v[4],v[5],v[6],v[7],RGB(0,0,0));
        v.clear();
    }
    else if(xx == "8"){
        hermiteCurve(hdc,v[0],v[1],v[2], v[3],v[4],v[5],v[6],v[7],RGB(0,0,0));
        v.clear();
    }
    else if(xx == "9"){
        splines(hdc,v[0],v[1],v[2], v[3],v[4],v[5],RGB(0,0,0));
        v.clear();
    }
    else if(xx == "10")
        {
            int xW1, yW1, xW2, yW2;
            POINT *p = new POINT[5];
            xW1=v[0];
            yW1=v[1];
            xW2=v[2];
            yW2=v[3];
            p[0].x=v[4];
            p[0].y=v[5];
            p[1].x=v[6];
            p[1].y=v[7];
            p[2].x=v[8];
            p[2].y=v[9];
            p[3].x=v[10];
            p[3].y=v[11];
            p[4].x=v[12];
            p[4].y=v[13];
            drawline(hdc, xW1, yW1, xW1, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW1, xW2, yW1, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW2, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW2, yW1, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            PolygonClip(hdc,p,5,xW1,yW1,xW2,yW2);
            v.clear();

    }
    else if(xx == "11")
        {
            int xW1, yW1, xW2, yW2;
            xW1=v[4];
            yW1=v[5];
            xW2=v[6];
            yW2=v[7];
            drawline(hdc, xW1, yW1, xW1, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW1, xW2, yW1, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW2, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW2, yW1, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            CohenSuth(hdc,v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],RGB(255,100,255));
            v.clear();

    }
  }


}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int x1 , y1 ,x2 ,y2,x3,y3,x4,y4,x5,y5,r1,r2,xW1, yW1, xW2, yW2,counter=-1;
    HDC hdc = GetDC(hwnd);
    static  POINT *p = new POINT[5];
    switch (message)                  /* handle the messages */
    {

    case WM_CREATE:
        AddMenus(hwnd);
        break;
    case WM_LBUTTONDOWN:
        if (counter != -1) break;
        xW1 = LOWORD(lParam);
        yW1 = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        if (counter != -1) break;
        xW2 = LOWORD(lParam);
        yW2 = HIWORD(lParam);
        counter = 0;
        hdc = GetDC(hwnd);
        break;
    case WM_LBUTTONDBLCLK :
        if(counter==0)
        {
            x1 = LOWORD(lParam);
            y1 = HIWORD(lParam);
            cout<<x1<<"    "<<y1<<endl;
            counter++;
        }
        else if(counter==1)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            cout<<x2<<"    "<<y2<<endl;
            counter++;
        }
        else if(counter==2)
        {
            x3 = LOWORD(lParam);
            y3 = HIWORD(lParam);
            cout<<x3<<"    "<<y3<<endl;
            counter++;
        }
        else if(counter==3)
        {
            x4 = LOWORD(lParam);
            y4 = HIWORD(lParam);
            cout<<x4<<"    "<<y4<<endl;
            counter++;
        }
        else if(counter==4)
        {
            x5 = LOWORD(lParam);
            y5 = HIWORD(lParam);
            cout<<x4<<"    "<<y4<<endl;
            counter++;
        }
        else if(counter==5)
        {
            counter=0;
        }
        break;

    case WM_COMMAND:

        switch(wParam)
        {
        case 1:
            MessageBeep(MB_MODEMASK);
            DrawLine(hdc , x1,y1,x2,y2,RGB(255,0,0));
            counter=-1;
            break;


        case 2:
            MessageBeep(MB_MODEMASK);
            DrawLineDDA(hdc,x1,y1,x2,y2,RGB(128,0,128));
            counter=-1;
            break;
        case 3 :
            MessageBeep(MB_MODEMASK);
            MidPointLine(hdc,x1,y1,x2,y2,RGB(128,200,128));
            counter=-1;
            break;


        case 4:
            MessageBeep(MB_MODEMASK);
            r2 = (int)sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
            r1 = r2*2/4;
            DrawEllipsePolar(hdc , x1,y1,r1,r2,RGB(255,0,0));
            counter=-1;
            break;


        case 5:
            MessageBeep(MB_MODEMASK);
            r2 = (int)sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
            r1 = r2*2/4;
            Ellipsee(hdc,x1,y1,r1,r2,RGB(128,0,128));
            counter=-1;
            break;
        case 6 :
            MessageBeep(MB_MODEMASK);
            r2 = (int)sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
            r1 = r2*2/4;
            DrawEllipsemid(hdc,x1,y1,r1,r2,RGB(128,200,128));
            counter=-1;
            break;
        case 7 :
            MessageBeep(MB_MODEMASK);
            bezierCurveHDC(hdc,x1,y1,x2,y2,x3,y3,x4,y4,RGB(0,0,0));
            counter=-1;
            break;
        case 8 :
            MessageBeep(MB_MODEMASK);
            hermiteCurve(hdc,x1,y1,x3,y3,x2,y2,x4,y4,RGB(0,0,0));
            counter=-1;
            break;
        case 9 :
            MessageBeep(MB_MODEMASK);
            splines(hdc,x1,y1,x2,y2,x3,y3,RGB(0,0,0));
            counter=-1;
            break;
        case 10 :
            MessageBeep(MB_MODEMASK);
            p[0].x=x1;
            p[0].y=y1;
            p[1].x=x2;
            p[1].y=y2;
            p[2].x=x3;
            p[2].y=y3;
            p[3].x=x4;
            p[3].y=y4;
            p[4].x=x5;
            p[4].y=y5;
            drawline(hdc, xW1, yW1, xW1, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW1, xW2, yW1, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW2, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW2, yW1, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            PolygonClip(hdc,p,5,xW1,yW1,xW2,yW2);
            counter=-1;
            break;
        case 11 :
            MessageBeep(MB_MODEMASK);
            drawline(hdc, xW1, yW1, xW1, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW1, xW2, yW1, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW1, yW2, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            drawline(hdc, xW2, yW1, xW2, yW2, COLORREF(RGB(255, 0, 0)));
            CohenSuth(hdc,x1,y1,x2,y2,xW1,yW2,xW2,yW1,RGB(255,100,255));
            CohenSuth(hdc,x1, y1, x3, y3,xW1,yW2,xW2,yW1,RGB(255,100,255));
            CohenSuth(hdc,x3, y3, x2, y2,xW1,yW2,xW2,yW1,RGB(255,100,155));
            counter=-1;
            break;
        case 12 :
            MessageBeep(MB_MODEMASK);
            save();
            break;
        case 13 :
            MessageBeep(MB_MODEMASK);
            load(hdc);
            break;
        }
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}



function [t,x,y]=gendata(a,b,c,d,x0,y0)
% 输入为4个参数及两个初值，输出为Volterra模型的数值仿真结果
h=0.01;
t=0:h:50;
x=t;y=t;
x(1)=x0;y(1)=y0;
for i=2:length(t)
    k1(1)=x(i-1)*(a-b*y(i-1));
    k1(2)=y(i-1)*(-c+d*x(i-1));
    k2(1)=(x(i-1)+0.5*h*k1(1))*(a-b*(y(i-1)+0.5*h*k1(2)));
    k2(2)=(y(i-1)+0.5*h*k1(2))*(-c+d*(x(i-1)+0.5*h*k1(1)));
    k3(1)=(x(i-1)+0.5*h*k2(1))*(a-b*(y(i-1)+0.5*h*k2(2)));
    k3(2)=(y(i-1)+0.5*h*k2(2))*(-c+d*(x(i-1)+0.5*h*k2(1)));
    k4(1)=(x(i-1)+h*k3(1))*(a-b*(y(i-1)+h*k3(2)));
    k4(2)=(y(i-1)+h*k3(2))*(-c+d*(x(i-1)+h*k3(1)));
    x(i)=x(i-1)+h/6*(k1(1)+2*k2(1)+2*k3(1)+k4(1));
    y(i)=y(i-1)+h/6*(k1(2)+2*k2(2)+2*k3(2)+k4(2));
end
end
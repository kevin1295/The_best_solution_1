clc
num = csvread('result.csv', 2, 0) %读取出该区域的数据作为表格
C=num(:,3) %从B矩阵取出第一列的所有行
B=num(:,2) 
A=num(:,1) 
clc
xx=linspace(min(A),max(A),20); %产生min(A)到max(A)均摊的50个点，目的上拟合离散点数量上的不足
yy=linspace(min(B),max(B),20); 
[xt,yt]=meshgrid(xx,yy); %做成二维网格
zt=griddata(A,B,C,xt,yt,'v4'); %用v4点的方式进行填充
surf(xt,yt,zt) %输出结果图形
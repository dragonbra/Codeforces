[num]=xlsread('D:\GitHub\acm-codes\��ģ\data.xls');

x0 = num(:,3)'; clear num; %����x0����ÿ��ú̿����

x1 = zeros(size(x0)); z1 = zeros(size(x0));

for i = 1:size(x0,2)
    x1(i) = sum(x0(:,1:i));
end

for i = 2:size(x0,2)
    z1(i) = ( x1(i) + x1(i-1) ) / 2;
end

y = x0'; 
t = ones(size(z1'));
B = [-z1' t];

a_hat = inv(B'*B)*B'*y;
a = a_hat(1,1);
b = a_hat(2,1);

x0_hat = zeros(1,31)
for k = 0:30
    x0_hat(k+1) = (x0(1)-b/a) * (1-exp(a))*exp(-a*k);
end
x0_hat = x0_hat';
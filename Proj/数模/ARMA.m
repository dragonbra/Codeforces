close all
clear all
load Data_EquityIdx   %��˹����ۺ�ָ��
len = 120;
% Y = DataTable.NASDAQ(1:len)
load data input;
Y = input(:,10:10);
data = Y;
plot(Y)

y_h_adf = adftest(Y)
y_h_kpss = kpsstest(Y)

Yd1 = diff(Y);
yd1_h_adf = adftest(Yd1)
yd1_h_kpss = kpsstest(Yd1)

% ACF��PACF����ȷ������
% figure
% autocorr(aimY)
% figure
% parcorr(aimY)

% ͨ��AIC��BIC��׼����ѡ������
% max_ar = 3;
% max_ma = 3;
% [AR_Order,MA_Order] = ARMA_Order_Select(Y,max_ar,max_ma,1);   

AR_Order =    1
MA_Order =    3

Mdl = arima(AR_Order, 1, MA_Order);  %�ڶ�������ֵΪ1����һ�ײ��
EstMdl = estimate(Mdl,data);
[res,~,logL] = infer(EstMdl,data);   %res���в�

stdr = res/sqrt(EstMdl.Variance);
figure('Name','�в����')
subplot(2,3,1)
plot(stdr)
title('Standardized Residuals')
subplot(2,3,2)
histogram(stdr,10)
title('Standardized Residuals')
subplot(2,3,3)
autocorr(stdr)
subplot(2,3,4)
parcorr(stdr)
subplot(2,3,5)
qqplot(stdr)

% Durbin-Watson ͳ���Ǽ�������ѧ��������õ�����ض���
diffRes0 = diff(res);  
SSE0 = res'*res;
DW0 = (diffRes0'*diffRes0)/SSE0 % Durbin-Watson statistic����ֵ�ӽ�2���������Ϊ���в�����һ������ԡ�

% 5.Ԥ��
step = 300; %Ԥ�ⲽ��Ϊ300
[forData,YMSE] = forecast(EstMdl,step,'Y0',data);   %matlab2018�����°汾дΪPredict_Y(i+1) = forecast(EstMdl,1,'Y0',Y(1:i)); 
lower = forData - 1.96*sqrt(YMSE); %95������������
upper = forData + 1.96*sqrt(YMSE); %95������������

figure()
plot(data,'Color',[.7,.7,.7]);
hold on
h1 = plot(length(data):length(data)+step,[data(end);lower],'r:','LineWidth',2);
plot(length(data):length(data)+step,[data(end);upper],'r:','LineWidth',2)
h2 = plot(length(data):length(data)+step,[data(end);forData],'k','LineWidth',2);
legend([h1 h2],'95% ��������','Ԥ��ֵ',...
	     'Location','NorthWest')
title('ú̿���� Forecast')
hold off

forData = normrnd(forData, sqrt(YMSE) );
figure()
plot(forData)
clc;
clear all;
close all;

MyBarcode = xlsread('datalog-5.csv'); 
%That is the values of the data in the picture are in format of 8 bit integers (maximum 255). 
%This property will be transfered to any variables that we want to assign the value of image to that like MyRawImage
%Therefore we need to change the variable type there after and for this reason we use the following command to change 
%the variable types to double  
OneLineData = double((MyBarcode(:,2)));
% %Moving Average Filter with window size of ws
for ws=7:14
for i=1:length(OneLineData)-(ws-1)
     OneLineDataAve(i)=sum(OneLineData(i:i+(ws-1)))/ws;
end;

% 
for i=1:length(OneLineDataAve)-1
    DataAveDif(i) = abs(OneLineDataAve(i+1) - OneLineDataAve(i));
end
% for iMinPeakHeight = 0.2:0.1:1.0
[pks,locs] = findpeaks(DataAveDif,'MinPeakHeight',0.5,'MinPeakDistance',4);

widths = (locs(2:end)-locs(1:end-1));
widths = round(widths/min(widths));
for i=1:length(widths)
    if widths(i) >= 2
        widths(i) = 3;  
    end
end
% 
% if length(widths)== 9
%     break
% end
% end

%**************Patern Recognition Using Lookup Table
LOOKUPTABLE = [311113113  %A
               113113113  %B
               313113111  %C
               111133113  %D
               311133111  %E
               113133111  %F
               111113313  %G
               311113311  %H
               113113311  %I
               111133311  %J
               311111133  %K
               113111133  %L
               313111131  %M
               111131133  %N
               311131131  %O
               113131131  %P
               111111333  %Q
               311111331  %R
               113111331  %S
               111131331  %T
               331111113  %U
               133111113  %V
               333111111  %W
               131131113  %X
               331131111  %Y
               133131111  %Z
               ]; 
           
CODE = str2num(strrep(num2str(widths), ' ', ''));
  plot(DataAveDif)
  hold on 
  plot(locs,pks,'or')
  figure;
  c = find(LOOKUPTABLE == CODE);
  Letter = char(64+c);
  widths
  if c > 0
      plot(OneLineData)
      hold on
      plot(OneLineDataAve)
      figure;
      plot(DataAveDif)
      hold on 
      plot(locs,pks,'or')
      c = find(LOOKUPTABLE == CODE)
      Letter = char(64+c)
      break
  end
end

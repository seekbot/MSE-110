clc;
clear all;
close all;

%**************Patern Recognition Using Lookup Table
LOOKUPTABLE = [311113113  %A
               113113113  %B
               312113111  %C
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
           
MyBarcode = xlsread('datalog-5.csv'); % import csv datalog
OneLineData = double((MyBarcode(:,2))); % Access the entire 2nd column

for ws=7:14 % Moving Avg. Filter Range

	% % 1st run (1st filtering condition)
	for i=1:length(OneLineData)-(ws-1) % Moving Avg. Filter data
		OneLineDataAve(i)=sum(OneLineData(i:i+(ws-1)))/ws;
	end;
 
	for i=1:length(OneLineDataAve)-1 % Derivative
		DataAveDif(i) = abs(OneLineDataAve(i+1) - OneLineDataAve(i));
	end

	for vMinPeakHeight = 0.2:0.1:1.8 % Search for all possible MinPeakHeight
		[pks,locs] = findpeaks(DataAveDif,'MinPeakHeight',vMinPeakHeight,'MinPeakDistance',4);

		widths = (locs(2:end)-locs(1:end-1));
		widths = round(widths/min(widths));

		% filter to 1 or 3
		for i=1:length(widths) 
			if widths(i) > 2 % 1st condition (> 2)
				widths(i) = 3;  
			else 
				widths(i)=1;
			end
		end

		if length(widths) == 9 % for all widths with length of 9 char.
			CODE = str2num(strrep(num2str(widths), ' ', ''));
			 c = find(LOOKUPTABLE == CODE);
			Letter = char(64+c);
		
			if c > 0 % If ASCII char. is found
			  plot(OneLineData) 
			  hold on
			  plot(OneLineDataAve) 
			  figure;
			  plot(DataAveDif)
			  hold on 
			  plot(locs,pks,'or')
			  c = find(LOOKUPTABLE == CODE)
			  Letter = char(64+c)
			  return % terminate this script if a ASCII char. is found
			end
		end
	end

	% % 2nd run (2nd filtering condition)
	for i=1:length(OneLineData)-(ws-1) % Moving avg. filter data
		OneLineDataAve(i)=sum(OneLineData(i:i+(ws-1)))/ws;
	end;

	for i=1:length(OneLineDataAve)-1 % Derivative
		DataAveDif(i) = abs(OneLineDataAve(i+1) - OneLineDataAve(i));
	end

	for vMinPeakHeight = 0.2:0.1:1.8 % Search for all possible MinPeakHeight
		[pks,locs] = findpeaks(DataAveDif,'MinPeakHeight',vMinPeakHeight,'MinPeakDistance',4);

		widths = (locs(2:end)-locs(1:end-1));
		widths = round(widths/min(widths));

		% filter to 1 or 3
		for i=1:length(widths) 
			if widths(i) >= 2 % 2nd condition (>= 2)
				widths(i) = 3;  
			else 
				widths(i)=1;
			end
		end

		if length(widths) == 9
			CODE = str2num(strrep(num2str(widths), ' ', ''));
			 c = find(LOOKUPTABLE == CODE);
			Letter = char(64+c);
			
			if c > 0 % If ASCII char. is found
				plot(OneLineData)
				hold on
				plot(OneLineDataAve)
				figure;
				plot(DataAveDif)
				hold on 
				plot(locs,pks,'or')
				c = find(LOOKUPTABLE == CODE)
				Letter = char(64+c)
				return % terminate this script if ASCII char. is found
			end
		end
	end
end

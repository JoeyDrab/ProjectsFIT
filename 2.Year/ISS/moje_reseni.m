
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%            %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%% Jozef Dráb %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%% <xdrabj00> %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%            %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


1
[sig, Fs] = audioread('xdrabj00.wav');
% vzorkovacia frekvencia
Fs;		
%Fs = 16 000 Hz
dlzka_sig = length(sig);	% dlzka signalu
%dlzka_sig = 16 000 Hz
dlzka_sec = length(sig)/Fs;	% dlzka v sekundach
%dlzka_sec = 1s

2
[sig,Fs] = audioread('xdrabj00.wav');
% fourirova transformacia signalu
X = abs(fft(sig));	
	plot(X(1:8000)); 
	xlabel('frekvencia [Hz]'); 
	ylabel('amplituda'); 
	title('Spekrutm vstupneho signalu xdrabj00'); 
	print -dpng Pr2.png;	

3
[sig,Fs] = audioread('xdrabj00.wav');
X = abs(fft(sig));
% maximum spektra v [HZ]
poz = (find(X == max(X), 1, 'first') - 1)
pozicia = poz * Fs / length(X) / 2;
% pozicia = 238 Hz

4
a = [1.0000,  0.2289, 0.4662];
b = [0.2324, -0.4112, 0.2324];
b0 = 0.2324;
b1 = -0.4112;
b2 = 0.2324;
b_help = (b1^2 - 4*b0*b2)^(1/2)
bx1 = -(b1 + b_help)/(2*b0)
bx2 = -(b1 - b_help)/(2*b0)
a0 = 1;
a1 = 0.2289;
a2 = 0.4662;
a_help = (a1^2 - 4*a0*a2)^(1/2)
ax1= -(a1 + a_help)/(2*a0)
ax2= -(a1 - a_help)/(2*a0)

	subplot(224); 
	[m, n, o] = zplane (b1,b0); 
	set(findobj(m, 'Type', 'line'), 'Color', 'b'); 
	legend('nuly','poly'); 
	title('Nuly a poly signalu xdrabj00'); 
	print -dpng Pr4.png;

% nie je stabilny

5
a=[1.0000,  0.2289, 0.4662];
b=[0.2324, -0.4112, 0.2324];
Fs=16000;
 
	H = freqz(b,a,256); 
	f=(0:255) / 256 * Fs / 2;
	subplot(224); 
	plot (f,abs(H)); 
	grid; 
	xlabel('f'); 
	ylabel('|H(f)|'); 
	title('priepustnost vzorku xdrabj00'); 
	print -dpng Pr5.png;
	
6
[sig,Fs] = audioread('xdrabj00.wav');
a=[1.0000,  0.2289, 0.4662];
b=[0.2324, -0.4112, 0.2324];

	
	y= filter(b, a, sig);
	x = abs(fft(y));

	plot(x(1:8000)); 
	xlabel('frekvencia [Hz]'); 
	ylabel('amplituda'); 
	print -dpng Pr6.png;
	
7
[sig,Fs] = audioread('xdrabj00.wav');
a=[1.0000,  0.2289, 0.4662];
b=[0.2324, -0.4112, 0.2324];
	
y= filter(b, a, sig);
x = abs(fft(y));

[velkost,index] = max(x);

% velkost = 649.9445
%index = 5346




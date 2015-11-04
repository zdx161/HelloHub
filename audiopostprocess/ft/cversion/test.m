close all;
Adc = 2;
A1 = 3;
A2 = 1.5;
F1 = 50;
F2 = 75;
Fs = 256;
P1 = -30;
P2 = 90;
N = 256;
t = [0:1/Fs:N/Fs];

S = Adc + A1 * cos(2*pi*F1*t+pi*P1/180) + A2 * cos(2*pi*F2*t+pi*P2/180);

plot(S);
title('signal pricture');

figure;
Y = fft(S,N);
Ayy = (abs(Y));
plot(Ayy(1:N));
title('FFT module');

figure;
Ayy = Ayy/(N/2);
Ayy(1) = Ayy(1) / 2;
F = ([1:N]-1) * Fs / N;
plot(F(1:N/2), Ayy(1:N/2));
title('amplitude - frequency');

figure;
Pyy = [1:N/2];
for i = "1:N/2"
    Pyy(i) = phase(Y(i));
    Pyy(i) = Pyy(i) * 180 / pi;
end
plot(F(1:N/2), Pyy(1:N/2));
title('phase - frequency');

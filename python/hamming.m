 y = zeros(100, 1);
for t = 0:99
   y(t + 1) = 2 + 3 * cos(2 * pi * 3 / 100 * t + pi * 30 / 180 );% + 9 * cos(2 * pi * 6 / 100 * t + pi * 30 / 180);
end
figure;
plot(y);

%fft(y)
%f = fft(y);
%it = ifft(f);
%figure;
%plot(it);

fs = 100;
wp = 3 * pi / 50;
ws = 5 * pi / 50;
deltaw = ws  - wp;
N = ceil(6.6 * pi / deltaw) + 1;
wdham = (hamming(N + 1))';
Wn = (3 + 5) / 100;
b = fir1(N, Wn, wdham);
%figure;
%plot(b);
cv = conv(y, b, 'same');
figure;
plot(cv);
%fft(cv)
%[H,w] = freqz(b, 1);
%db = 20 * log10(abs(H));


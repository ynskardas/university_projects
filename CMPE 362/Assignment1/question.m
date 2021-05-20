fs = 100;
t = -10:1/fs:10-1/fs;
x = sawtooth(2*pi*0.1*t+pi);
k3 = 1:3;
k5 = 1:5;
k15 = 1:15;
b3 = -2/pi * 1 ./ k3 .* cos(pi .* k3);
b5 = -2/pi * 1 ./ k5 .* cos(pi .* k5);
b15 = -2/pi * 1 ./ k15 .* cos(pi .* k15);
x3_1 = b3(1) * sin(2 * pi * k3(1) / 10 .* t);
x3_2 = b3(2) * sin(2 * pi * k3(2) / 10 .* t);
x3_3 = b3(3) * sin(2 * pi * k3(3) / 10 .* t);
x3 = x3_1 + x3_2 + x3_3;

x5_1 = b5(1) * sin(2 * pi * k5(1) / 10 .* t);
x5_2 = b5(2) * sin(2 * pi * k5(2) / 10 .* t);
x5_3 = b5(3) * sin(2 * pi * k5(3) / 10 .* t);
x5_4 = b5(4) * sin(2 * pi * k5(4) / 10 .* t);
x5_5 = b5(5) * sin(2 * pi * k5(5) / 10 .* t);
x5 = x5_1 + x5_2 + x5_3 + x5_4 + x5_5;

x15_1  = b15(1) * sin(2 * pi * k15(1) / 10 .* t);
x15_2  = b15(2) * sin(2 * pi * k15(2) / 10 .* t);
x15_3  = b15(3) * sin(2 * pi * k15(3) / 10 .* t);
x15_4  = b15(4) * sin(2 * pi * k15(4) / 10 .* t);
x15_5  = b15(5) * sin(2 * pi * k15(5) / 10 .* t);
x15_6  = b15(6) * sin(2 * pi * k15(6) / 10 .* t);
x15_7  = b15(7) * sin(2 * pi * k15(7) / 10 .* t);
x15_8  = b15(8) * sin(2 * pi * k15(8) / 10 .* t);
x15_9  = b15(9) * sin(2 * pi * k15(9) / 10 .* t);
x15_10 = b15(10) * sin(2 * pi * k15(10) / 10 .* t);
x15_11 = b15(11) * sin(2 * pi * k15(11) / 10 .* t);
x15_12 = b15(12) * sin(2 * pi * k15(12) / 10 .* t);
x15_13 = b15(13) * sin(2 * pi * k15(13) / 10 .* t);
x15_14 = b15(14) * sin(2 * pi * k15(14) / 10 .* t);
x15_15 = b15(15) * sin(2 * pi * k15(15) / 10 .* t);
x15 = x15_1 + x15_2 + x15_3 + x15_4 + x15_5 + x15_6 + x15_7 + x15_8 + x15_9 + x15_10 + x15_11 + x15_12 + x15_13 + x15_14 + x15_15;


plot(t,x);
hold on;
plot(t,x3);
hold on;
plot(t,x5);
hold on;
plot(t,x15);
hold off;
ylabel("amplitude"); xlabel("time"); title("Signal and Harmonics sum");
legend("original", "sum of first 3 harmonics", "sum of first 5 harmonics", "sum of first 15 harmonics");
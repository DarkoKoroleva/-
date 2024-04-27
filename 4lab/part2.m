det_all = zeros(1, 9);
for i = 1:9
    det_all(i) = 10.^(-i+1);
end
figure
data = load('data1.txt');
loglog(data(:,2), data(:,3), 'red');
grid on; 
hold on;
loglog(data(:,2), data(:,4), 'blue');
hold on;

figure
data2 = load('data2.txt');
loglog(det_all(1, :), data2(:,1), 'red');
grid on;
hold on; 
% D = zeros(10);
% B = randi(10, 10, 10);
% det_curr = 1;
% 
% for i=1:9
%     D(i, i) = rand(1);
%     det_curr = det_curr*D(i, i);
% end
% D(10,10) = 10 / det_curr
% % det(D);
% B2 = inv(B);
% A =B2*D*B;
% det(A);
% 
% writematrix(A,'M_tab.txt','WriteMode','append','Delimiter','tab');

B = zeros(10);
det_curr = 1;

for i=1:10
    B(i, i) = rand(1);
    det_curr = det_curr*B(i, i);
end
det(B);
[Q, r]=qr(rand(3));
A =Q.'*B*Q;
det(A);

% writematrix(A,'M_tab.txt','WriteMode','append','Delimiter','tab');


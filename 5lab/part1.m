B = zeros(10);
det_curr = 1;
B(1,1)=2;
B(2,2)=2;

eigenvalues = zeros(1, 10);

for i=3:10
    B(i, i) = rand(1) + 1;
    det_curr = det_curr*B(i, i);
end


[Q, r]=qr(rand(10));
A =Q.'*B*Q;
det(A);
own_values(1, 1) = max(diag(B));
own_values(1, 2) = min(diag(B));

e=1;
for i = 1:10 
    e =e*0.1;
    B(1,1)=B(2,2)-e;
    [Q, r]=qr(rand(10));
    A =Q.'*B*Q;
    own_values(1, 1) = max(diag(B));
    own_values(1, 2) = min(diag(B));
    
    for j=1:10
        eigenvalues(1, j) = B(j,j);
    end
    eigenvalues = sort(eigenvalues, 'descend');
    writematrix(eigenvalues,'eigenvalues.txt','WriteMode','append','Delimiter','tab');
    writematrix(A,'M_tab.txt','WriteMode','append','Delimiter','tab');
    writematrix(own_values,'M_tab.txt','WriteMode','append','Delimiter','tab');
end



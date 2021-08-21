
dx = 0.0001;
E = 0.09;
x = -pi/2+E:dx:pi/2-E;

y0 = tan(x);
y1 = mex_tan(x);

%dy = y0-y1 ; % error
%abs_dy = abs(y0-y1) ;   % absolute error
%relerr = abs(y0-y1)./y0 ;  % relative error
%pererr = abs(y0-y1)./y0*100 ;   % percentage error
%mean_err = mean(abs(y0-y1)) ;    % mean absolute error
%MSE = mean((y0-y1).^2) ;        % Mean square error
%RMSE = sqrt(mean((y0-y1).^2)) ; % Root mean square error

figure;
% rows,cols.index
subplot (1, 3, 1)
plot(x,y0,      x,y1);
legend('tan', 'fmtan');
title('curves')

subplot (1, 3, 2)
plot(x,abs(y0-y1));
legend('tan - fmtan');
title('abs error')

subplot (1, 3, 3)
plot(x, log10(abs(y0-y1)./y0));
legend('tan - fmtan');
title('log(abs error)')
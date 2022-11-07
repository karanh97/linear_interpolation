clear all;
clc;
tic
pts = readmatrix("..\build\Release\data_2\20000\triangulation_prog1_matlab_20000.csv");
% v = readmatrix("build\Release\data_2\1000000\triangulation_prog1_vals_matlab_1000000.csv");
func = readmatrix("..\build\Release\data_2\20000\poster_5000.csv");
% v = (1) + (0.2 .* pts(:,1)) + (0.03 .* pts(:,2))
v = (0.001 .* pts(:,1) .* pts(:,1)) + (0.002 .* pts(:,2) .* pts(:,2)) + (0.003 .* pts(:,1) .* pts(:,2));
DT = delaunay(pts(:,1),pts(:,2));
ztest = griddata(pts(:,1), pts(:,2), v, func(1000:4000, 1), func(1000:4000, 2));
% writematrix(ztest, "..\build\Release\data_2\1000000\function\quadratic\interpolation_1000000_5000_function_matlab.csv")
timeElapsed = toc
xq = func(1000:4000, 1);
yq = func(1000:4000, 2);

figure(1)
hold on
plot3(pts(:,1),pts(:,2),v,'.','markersize',12);
plot3(xq, yq, ztest,'*','MarkerSize',15);
xlabel('X-coordinate')
ylabel('Y-coordinate')
zlabel('Elevation')
grid on
hold off
view(3)

% plotting delaunay triangulation of points
figure(2)
hold on
triplot(DT,pts(:,1),pts(:,2));
scatter(xq, yq, 50, 'red');
xlabel('X-coordinate')
ylabel('Y-coordinate')
hold off

% using meshgrid to create a set of 2-D points at the data points

% figure(3)
% surf(xq,yq,ztest);
% xlabel('X-coordinate')
% ylabel('Y-coordinate')
% zlabel('Elevation')
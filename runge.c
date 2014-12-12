#include <stdio.h>

#define G 0.6578
#define H 0.01
#define N 10000

double abso(double x){
	return x>0 ? x : -x;
}

double fg(double y1){
	return (-0.5) * y1  +  0.5 * (-0.3) * abso(y1 + 1.0)  +  0.5 * (0.3) * abso(y1 - 1);
}



double f1(double y1, double y2){
	return G * 9.0 * (y2 - y1) - 9.0 * fg(y1);
}

double f2(double y1, double y2, double y3){
	return G * (y1 - y2)  +  y3;
}

double f3(double y2){
	return (-1) * 7 * y2;
}

double delta(double y1, double y2, double y3, double delta[4]){
	int i;
	double ka[4], kb[4], kc[4], kd[4];

	ka[1] = H * f1(y1, y2);
	ka[2] = H * f2(y1, y2, y3);
	ka[3] = H * f3(y2);

	kb[1] = H * f1(y1 + 0.5*ka[1], y2 + 0.5*ka[2]);
	kb[2] = H * f2(y1 + 0.5*ka[1], y2 + 0.5*ka[2], y3 + 0.5*ka[3]);
	kb[3] = H * f3(y2 + 0.5*ka[2]);

	kc[1] = H * f1(y1 + 0.5*kb[1], y2 + 0.5*kb[2]);
	kc[2] = H * f2(y1 + 0.5*kb[1], y2 + 0.5*kb[2], y3 + 0.5*kb[3]);
	kc[3] = H * f3(y2 + 0.5*kb[2]);

	kd[1] = H * f1(y1 + kc[1], y2 + kc[2]);
	kd[2] = H * f2(y1 + kc[1], y2 + kc[2], y3 + kc[3]);
	kd[3] = H * f3(y2 + kc[2]);

	for(i=1; i<=3; i++){
		delta[i] = (1.0 / 6.0) * (ka[i] + 2*kb[i] + 2*kc[i] + kd[i]);
	}
}

int main(void){
	FILE *fp;
	int i;

	double y1 = 0.1;
	double y2 = 0.1;
	double y3 = 0.1;

	double del[4] = {0, 0, 0, 0};

	fp = fopen("output.txt", "w");
	
	//fprintf(fp, "%f %f %f\r\n", y1, y2, y3);
	//初期点

	for(i=0; i<100000; i++){
			delta(y1, y2, y3, del);
		
			y1 += del[1];
			y2 += del[2];
			y3 += del[3];
	}

	for(i=0; i<6000; i++){
		int j;

		for(j=0; j<6; j++){
		delta(y1, y2, y3, del);
	
		y1 += del[1];
		y2 += del[2];
		y3 += del[3];
		}
		
		fprintf(fp, "%f %f %f\r\n", y1, y2, y3);
	}

	fclose(fp);

	return 0;
}
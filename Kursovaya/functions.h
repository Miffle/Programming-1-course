#ifndef KURSOVAYA_PO_PROGE_FUNCTIONS_H
#define KURSOVAYA_PO_PROGE_FUNCTIONS_H
void time(float *t, float tn, float dt, int n) {
    for (int i = 0; i <= n; i++) {
        t[i] = tn + i * dt;
        //printf("%2.3f ", t[i]);
    }

}
void Uvh(float *Uvh, float *t, int n){
    int o = n/2 ;

    float z = 250.0 / (n / 2.0);
    for (int i = 1; i <= o; i++) {
        if(t[i] <= 0.0) {
            Uvh[i] = Uvh[i - 1] + z;
        }
    }
    int i = 0;
    for(int j = n; j>o; j--){
        Uvh[j] = Uvh[i];
        i++;
    }
    //else { Uvh[i] = Uvh[i - 1] - z; };

}

void Uvih(int n, float *Uvh, float *Uvih){
    float U0 = 50, U1 = 100, a = 400;
    for(int i = 1; i<=n; i++){
        if((0.0<=Uvh[i]) && ( Uvh[i] < U0)){
            Uvih[i] = cbrtf(a*(Uvh[i] * Uvh[i]));
        }
        else(Uvih[i] = U1);
        //printf("%5.2f\n", Uvih[i]);
    }
}
float parametr(float *times, int n, float *U, int k){
    int y; int h = 0;
    for(y = n; y > (n/2); y--){
        if(U[y]<k){
            h++;
        }
        else{break;}
    }
    float b = times[n-h];
    float j = times[h];
    float time = (b - j);
    return time;
}

void files(int n, float *Uvx, float *Uvix, float *t){
    FILE *f1, *f2, *f3;
    f1 = fopen("../massiv_t.txt", "w");
    f2 = fopen("../massiv_Uvx.txt", "w");
    f3 = fopen("../massiv_Uvix.txt", "w");
    for (int i = 0; i <= n; i++) {
        fprintf(f1, "%6.3f\n", t[i]);
        fprintf(f2, "%6.3f\n", Uvx[i]);
        fprintf(f3, "%6.3f\n", Uvix[i]);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);


}
void zastavka() {
    FILE* f = fopen("../zast.txt", "r");
    char ch;
    while (!feof(f))
    {
        fscanf(f, "%c", &ch);
        printf("%c", ch);
    }
    fclose(f);
}

void show(float *t, float *Uvx, float *Uvix, int n) {
    printf(" Time       Uvx        Uvix\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%8.4f  :  %8.4f :  %8.4f  \n", t[i], Uvx[i], Uvix[i]);
    }
}
#endif

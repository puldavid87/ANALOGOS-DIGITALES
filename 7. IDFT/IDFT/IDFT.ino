
#define  SIG_LENGTH 320
#define SHORT_SIG_LENGTH 88
#define SHORT_ECG 100
#define LONG_ECG  640

extern double InputSignal_1kHz_15kHz[SIG_LENGTH];
extern double short_InputSignal_1kHz_15Hz[SHORT_SIG_LENGTH];
extern double ECG_100pts[100];
extern double _640_points_ecg_[640];
void calc_sig_idft(double *idft_out_arr, double *sig_src_rex_arr,double *sig_src_imx_arr, uint32_t idft_length);


double REX[LONG_ECG/2 ];
double IMX[LONG_ECG/2];
double IDFT_OUTPUT[LONG_ECG];
void plot_both(void);
 void get_dft_output_mag(void);


/**@note USE full signal length for DUE demo**/

void setup() {
Serial.begin(115200);


  calc_sig_dft(&_640_points_ecg_[0],&REX[0], &IMX[0],LONG_ECG);

 calc_sig_idft(&IDFT_OUTPUT[0], &REX[0],&IMX[0],LONG_ECG);

 plot_signal(IDFT_OUTPUT,LONG_ECG);

}

void loop() {


}

void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, uint32_t sig_length)
{
  int i,k,j;
  for(j=0;j<(sig_length/2);j++)
  {
     sig_dest_rex_arr[j] =0;
      sig_dest_imx_arr[j] =0;
  }
  
   for(k=0;k<(sig_length/2);k++)
  {
    for(i=0;i<sig_length;i++)
    {
               sig_dest_rex_arr[k] =  sig_dest_rex_arr[k] + sig_src_arr[i]*cos(2*PI*k*i/sig_length);
               sig_dest_imx_arr[k] =  sig_dest_imx_arr[k] - sig_src_arr[i]*sin(2*PI*k*i/sig_length);


    }
  }
}

void calc_sig_idft(double *idft_out_arr, double *sig_src_rex_arr,double *sig_src_imx_arr, uint32_t idft_length)
{
  uint32_t i,j,k;
   for(k=0;k<idft_length/2;k++)
   {
     sig_src_rex_arr[k] = sig_src_rex_arr[k] /(idft_length/2);
     sig_src_imx_arr[k] = -sig_src_imx_arr[k] /(idft_length/2);

   }
    sig_src_rex_arr[0] = sig_src_rex_arr[0]/2;
    sig_src_imx_arr[0] = -sig_src_imx_arr[0]/2;

    for(i=0;i<idft_length;i++)
    {
       idft_out_arr[i]=0;
    }
     for(k=0;k<idft_length/2;k++)
     {
       for(i=0;i<idft_length;i++)
       {
        idft_out_arr[i] = idft_out_arr[i]+ sig_src_rex_arr[k] * cos(2*PI*k*i/idft_length);
        idft_out_arr[i] = idft_out_arr[i]+ sig_src_imx_arr[k] * sin(2*PI*k*i/idft_length);
       }
     }

  
}

void get_dft_output_mag(void)
{
  uint32_t k;
  for(k=0;k<SHORT_SIG_LENGTH;k++)
  {
    REX[k] = sqrt(pow(REX[k],2)+pow(IMX[k],2));
  }
}


void plot_signal(double *sig_src_arr, uint32_t signal_length)
{
  int i;
   for( i=0;i<signal_length;i++){
      Serial.print((_640_points_ecg_[i]*1000) +2000);

  Serial.print(",");
    Serial.println(sig_src_arr[i]*1000);

 delay(10);

  }
}


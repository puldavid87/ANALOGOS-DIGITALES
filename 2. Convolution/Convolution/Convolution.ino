
#define SIG_LENGTH 320
#define IMP_RSP_LENGTH 29
#define OFFSET 5
extern double InputSignal_1kHz_15kHz[SIG_LENGTH];
extern double  Impulse_response[IMP_RSP_LENGTH];

double output_signal_arr[SIG_LENGTH+IMP_RSP_LENGTH];

void plot_signal(double *sig_src_arr, uint32_t signal_length);
void plot_both(void);

void convolution(double *sig_src_arr,
                 double *sig_dest_arr,
                 double *imp_response_arr,
                 uint32_t sig_src_length,
                 uint32_t imp_response_length
                 );


void setup() {
  Serial.begin(115200);

     convolution((double *)&InputSignal_1kHz_15kHz[0],
                 (double *)&output_signal_arr[0],
                 (double *)&Impulse_response[0],
                 (uint32_t) SIG_LENGTH,
                 (uint32_t) IMP_RSP_LENGTH
                 );

 plot_both();

}

void loop() {

}



void plot_both(void)
{
  uint32_t i;
  for(i=0;i<SIG_LENGTH;i++){
  Serial.print(InputSignal_1kHz_15kHz[i]+OFFSET);
  Serial.print(",");
  Serial.println(output_signal_arr[i]);
  delay(5);
  
  }
}






void plot_signal(double *sig_src_arr, uint32_t signal_length)
{
  uint32_t i;
  for(i=0;i<signal_length;i++)
  {
    Serial.println(sig_src_arr[i]); 
    delay(10);
  
  }

}

void convolution(double *sig_src_arr,
                 double *sig_dest_arr,
                 double *imp_response_arr,
                 uint32_t sig_src_length,
                 uint32_t imp_response_length
                 )
 {
   uint32_t i,j;
   for (i=0;i<(sig_src_length+ imp_response_length);i++)   
   {
    sig_dest_arr[i]=0;       
   }
    for(i=0;i<sig_src_length;i++)
    {
      for(j=0;j<imp_response_length;j++)
      {
        sig_dest_arr[i+j] = sig_dest_arr[i+j]+ sig_src_arr[i]*imp_response_arr[j];
      }
      
    }
 }




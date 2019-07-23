#define ARM_MATH_CM3
#include <arm_math.h>

#define SIG_LENGTH 320
#define IMP_RSP_LENGTH 29
#define OFFSET 5

extern float32_t InputSignal_1kHz_15kHz[SIG_LENGTH];
extern float32_t  Impulse_response[IMP_RSP_LENGTH];

float32_t output_signal_arr[SIG_LENGTH+IMP_RSP_LENGTH];

void plot_signal(float32_t *sig_src_arr, uint32_t signal_length);
void plot_both(void);




void setup() {
  Serial.begin(115200);

  arm_conv_f32(&InputSignal_1kHz_15kHz[0],
               SIG_LENGTH,
               &Impulse_response[0],
               IMP_RSP_LENGTH,
               &output_signal_arr[0]
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
  delay(10);
  
  }
}






void plot_signal(float32_t *sig_src_arr, uint32_t signal_length)
{
  uint32_t i;
  for(i=0;i<signal_length;i++)
  {
    Serial.println(sig_src_arr[i]); 
    delay(10);
  
  }

}





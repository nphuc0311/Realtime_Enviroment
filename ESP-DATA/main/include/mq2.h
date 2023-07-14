#ifndef _MQ2_
#define _MQ2_

#define EXAMPLE_ADC_ATTEN           ADC_ATTEN_DB_11
#define ADC_BITWIDTH                13

struct mq2_reading
{
    int adc_raw[10];
    int voltage[10];
    float percent;
};

struct mq2_reading mq2_read();
void mq2_init();

#endif
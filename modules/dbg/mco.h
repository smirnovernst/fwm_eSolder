#ifndef MCO_H_
#define MCO_H_



typedef enum {
    MCO1_HSI = 0,
    MCO1_LSE, 
    MCO1_HSE,
    MCO1_PLL,
    MCO1_None
}MCO1_t;

typedef enum {
    MCO2_SYSCLK = 0,
    MCO2_PLLI2S,
    MCO2_HSE,
    MCO2_PLL,
    MCO2_None
}MCO2_t;


typedef enum {
    MCOPrescaller_NO = 0,
    MCOPrescaller_2,
    MCOPrescaller_3,
    MCOPrescaller_4,
    MCOPrescaller_5,
    MCOPrescaller_None
}MCOPrescaller_t;

void MCO2Enable(MCO2_t mode, MCOPrescaller_t prsc);

#endif //!MCO_H_
#ifndef CAL_H
#define CAL_H

#pragma pack(push, 1)

typedef struct
{
    float m_DACdcP = 1;   //DACdc V-to-bin slope, x > 0
    float m_DACdcN = 1;   //DACdc V-to-bin slope, x < 0
    float b_DACdc = 0;    //DACdc V-to-bin intercept
    float m_refP = 1;     //Ref bin-to-V slope, x > 0
    float m_refN = 1;     //Ref bin-to-V slope, x < 0
    float b_ref = 0;      //Ref bin-to-V intercept
    float m_eweP = 1;     //Ewe bin-to-V slope, x > 0
    float m_eweN = 1;     //Ewe bin-to-V slope, x < 0
    float b_ewe = 0;      //Ewe bin-to-V intercept
    float m_eceP = 1;     //Ece bin-to-V slope, x > 0
    float m_eceN = 1;     //Ece bin-to-V slope, x < 0
    float b_ece = 0;      //Ece bin-to-V intercept
	float m_iP[8] = { 1, (float)1e-1, (float)1e-2, (float)1e-3, (float)1e-4, (float)1e-5, (float)1e-6, (float)1e-7 };    //Current bin-to-mA slope, x > 0
	float m_iN[8] = { 1, (float)1e-1, (float)1e-2, (float)1e-3, (float)1e-4, (float)1e-5, (float)1e-6, (float)1e-7 };    //Current bin-to-mA slope, x < 0
    float b_i[8];     //Current bin-to-mA intercept
    float m_DACac;    //DACac bin-to-mVAC slope
} cal_t;

#pragma pack(pop)

#endif
#ifndef __SI47xx_H
#define __SI47xx_H
/* ∂®“Âøÿ÷∆√¸¡Ó */
#define SI47xx_POWER_UP                   0x01
#define SI47xx_GET_REV                    0x10
#define SI47xx_POWER_DOWN                 0x11
#define SI47xx_SET                        0x12
#define SI47xx_GET                        0x13
#define SI47xx_GET_INT_STATUS             0x14
#define SI47xx_PATCH_ARGS                 0x15
#define SI47xx_PATCH_DATA                 0x16
#define SI47xx_GPO_IEN                    0x0001
#define SI47xx_DIGITAL_OUTPUT_FORMA       0x0102
#define SI47xx_DIGITAL_OUTPUT_SAMPLE_RAT  0x0104
#define SI47xx_REFCLK_FRE                 0x0201
#define SI47xx_REFCLK_PRESCALE            0x0202

#define SI47xx_FM_TUNE_FREQ               0x20
#define SI47xx_FM_SEEK_START              0x21
#define SI47xx_FM_TUNE_STATUS             0x22
#define SI47xx_FM_RSQ_STATUS              0x23
#define SI47xx_FM_RDS_STATUS              0x24
#define SI47xx_FM_AGC_STATUS              0x27
#define SI47xx_FM_AGC_OVERRIDE            0x28

#define SI47xx_AM_TUNE_FREQ               0x40
#define SI47xx_AM_SEEK_START              0x41
#define SI47xx_AM_TUNE_STATUS             0x42
#define SI47xx_AM_RSQ_STATUS              0x43
#define SI47xx_AM_AGC_STATUS              0x47
#define SI47xx_AM_AGC_OVERRIDE            0x48
#define SI47xx_GPIO_CTL                   0x80
#define SI47xx_GPIO_SET                   0x81

/* AM */
#define SI47xx_AM_DEEMPHASI                          0x3100
#define SI47xx_AM_CHANNEL_FILTER                     0x3102
#define SI47xx_AM_AUTOMATIC_VOLUME_CONTROL_MAX_GAI   0x3103
#define SI47xx_AM_MODE_AFC_SW_PULL_IN_RANG           0x3104
#define SI47xx_AM_MODE_AFC_SW_LOCK_IN_RANG           0x3105
#define SI47xx_AM_RSQ_INTERRUPT                      0x3200
#define SI47xx_AM_RSQ_SNR_HIGH_THRESHOL              0x3201
#define SI47xx_AM_RSQ_SNR_LOW_THRESHOL               0x3202
#define SI47xx_AM_RSQ_RSSI_HIGH_THRESHOL             0x3203
#define SI47xx_AM_RSQ_RSSI_LOW_THRESHOL              0x3204
#define SI47xx_AM_SOFT_MUTE_RAT                      0x3300
#define SI47xx_AM_SOFT_MUTE_SLOP                     0x3301
#define SI47xx_AM_SOFT_MUTE_MAX_ATTENUATIO           0x3302
#define SI47xx_AM_SOFT_MUTE_SNR_THRESHOL             0x3303
#define SI47xx_AM_SOFT_MUTE_RELEASE_RAT              0x3304
#define SI47xx_AM_SOFT_MUTE_ATTAC_RATE               0x3305

/* FM */
#define SI47xx_FM_DEEMPHASIS                         0x1100
#define SI47xx_FM_CHANNEL_FILTER                     0x1102
#define SI47xx_FM_BLEND_STEREO_THRESHOLD             0x1105
#define SI47xx_FM_BLEND_MONO_THRESHOLD               0x1106
#define SI47xx_FM_ANTENNA_INPUT                      0x1107
#define SI47xx_FM_MAX_TUNE_ERROR                     0x1108
#define SI47xx_FM_RSQ_INT_SOURCE                     0x1200
#define SI47xx_FM_RSQ_SNR_HI_THRESHOLD               0x1201
#define SI47xx_FM_RSQ_SNR_LO_THRESHOLD               0x1202
#define SI47xx_FM_RSQ_RSSI_HI_THRESHOLD              0x1203
#define SI47xx_FM_RSQ_RSSI_LO_THRESHOLD              0x1204
#define SI47xx_FM_RSQ_MULTIPATH_HI_THRESHOLD         0x1205
#define SI47xx_FM_RSQ_MULTIPATH_LO_THRESHOLD         0x1206
#define SI47xx_FM_RSQ_BLEND_THRESHOLD                0x1207
#define SI47xx_FM_SOFT_MUTE_RATE                     0x1300
#define SI47xx_FM_SOFT_MUTE_SLOPE                    0x1301
#define SI47xx_FM_SOFT_MUTE_MAX_ATTENUATION          0x1302
#define SI47xx_FM_SOFT_MUTE_SNR_THRESHOLD            0x1303
#define SI47xx_FM_SOFT_MUTE_RELEASE_RATE             0x1304
#define SI47xx_FM_SOFT_MUTE_ATTACK_RATE              0x1305
#define SI47xx_FM_SEEK_BAND_BOTTOM                   0x1400
#define SI47xx_FM_SEEK_BAND_TOP                      0x1401
#define SI47xx_FM_SEEK_FREQ_SPACING                  0x1402
#define SI47xx_FM_SEEK_TUNE_SNR_THRESHOLD            0x1403
#define SI47xx_FM_SEEK_TUNE_RSSI_TRESHOLD            0x1404
#define SI47xx_FM_RDS_INT_SOURCE                     0x1500
#define SI47xx_FM_RDS_INT_FIFO_COUNT                 0x1501
#define SI47xx_FM_RDS_CONFIG                         0x1502
#define SI47xx_FM_RDS_CONFIDENCE                     0x1503
#define SI47xx_FM_AGC_ATTACK_RATE                    0x1700
#define SI47xx_FM_AGC_RELEASE_RATE                   0x1701
#define SI47xx_FM_BLEND_RSSI_STEREO_THRESHOLD        0x1800
#define SI47xx_FM_BLEND_RSSI_MONO_THRESHOLD          0x1801
#define SI47xx_FM_BLEND_RSSI_ATTACK_RATE             0x1802
#define SI47xx_FM_BLEND_RSSI_RELEASE_RATE            0x1803
#define SI47xx_FM_BLEND_SNR_STEREO_THRESHOLD         0x1804
#define SI47xx_FM_BLEND_SNR_MONO_THRESHOLD           0x1805
#define SI47xx_FM_BLEND_SNR_ATTACK_RATE              0x1806
#define SI47xx_FM_BLEND_SNR_RELEASE_RATE             0x1807
#define SI47xx_FM_BLEND_MULTIPATH_STEREO_THRESHOLD   0x1808
#define SI47xx_FM_BLEND_MULTIPATH_MONO_THRESHOLD     0x1809
#define SI47xx_FM_BLEND_MULTIPATH_ATTACK_RATE        0x180A
#define SI47xx_FM_BLEND_MULTIPATH_RELEASE_RATE       0x180B
#define SI47xx_FM_BLEND_MAX_STE_REO_SEPARATION       0x180C
#define SI47xx_FM_NB_DETECT_THRESHOLD                0x1900
#define SI47xx_FM_NB_INTERVAL                        0x1901
#define SI47xx_FM_NB_RATE                            0x1902
#define SI47xx_FM_NB_IIR_FILTER                      0x1903
#define SI47xx_FM_NB_DELAY                           0x1904
#define SI47xx_FM_HICUT_SNR_HIGH_THRESHOLD           0x1A00
#define SI47xx_FM_HICUT_SNR_LOW_THRESHOLD            0x1A01
#define SI47xx_FM_HICUT_ATTACK_RATE                  0x1A02
#define SI47xx_FM_HICUT_RELEASE_RATE                 0x1A03
#define SI47xx_FM_HICUT_MULTIPA_TH_TRIGGER_THRESHOLD 0x1A04
#define SI47xx_FM_HICUT_MULTIPA_TH_END_THRESHOLD     0x1A05
#define SI47xx_FM_HICUT_CUTOFF_FRE_QUENCY            0x1A06
#define SI47xx_RX_VOLUME                             0x4000
#define SI47xx_RX_HARD_MUTE                          0x4001

static void si47xx_fm_mode(void);
static void si47xx_fm_tune_status(unsigned char *buf);
static int si47xx_fm_serach(void);
static void si47xx_fm_tune(int frequency);
static void si47xx_am_mode(void);
static int si47xx_am_serach(void);
static void si47xx_am_tune(int frequency);
static void si47xx_vol(int val);
static void si47xx_mute(int mute);
static void si47xx_reset(void);
static void si47xx_power_on(void);
static void si47xx_power_off(void);
#endif


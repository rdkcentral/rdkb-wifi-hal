/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef __WIFI_HAL_GENERIC_H__
#define __WIFI_HAL_GENERIC_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
#ifndef ULLONG
#define ULLONG unsigned long long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef USHORT
#define USHORT unsigned short
#endif

#ifndef BOOL
#define BOOL  unsigned char
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif


#define WIFI_HAL_SUCCESS             0
#define WIFI_HAL_ERROR              -1
#define WIFI_HAL_INTERNAL_ERROR     -2
#define WIFI_HAL_UNSUPPORTED        -3
#define WIFI_HAL_INVALID_ARGUMENTS  -4
#define WIFI_HAL_INVALID_VALUE      -5


#ifndef RADIO_INDEX_1
#define RADIO_INDEX_1 1
#define RADIO_INDEX_2 2
#define RADIO_INDEX_3 3

#define AP_INDEX_1 1
#define AP_INDEX_2 2
#define AP_INDEX_3 3
#define AP_INDEX_4 4
#define AP_INDEX_5 5
#define AP_INDEX_6 6
#define AP_INDEX_7 7
#define AP_INDEX_8 8
#define AP_INDEX_9 9
#define AP_INDEX_10 10
#define AP_INDEX_11 11
#define AP_INDEX_12 12
#define AP_INDEX_13 13
#define AP_INDEX_14 14
#define AP_INDEX_15 15
#define AP_INDEX_16 16
#define AP_INDEX_17 17
#define AP_INDEX_18 18
#define AP_INDEX_19 19
#define AP_INDEX_20 20
#define AP_INDEX_21 21
#define AP_INDEX_22 22
#define AP_INDEX_23 23
#define AP_INDEX_24 24
#endif


#ifdef WIFI_HAL_VERSION_3
#define MAX_NUM_RADIOS           3
#else
#define MAX_NUM_RADIOS           2
#endif

#define MAX_NUM_VAP_PER_RADIO    8

#define MAC_STR_LEN        18
#ifndef ETHER_ADDR_LEN
#define ETHER_ADDR_LEN        6
#endif /* ETHER_ADDR_LEN */

#define ACL_MACADDR_SIZE        18
#define ACL_MACFLT_NUM          16
#define MAC_LIST_SIZE        ( (ACL_MACADDR_SIZE * WL_MACADDR_SIZE) + 2 )
#define ACL_MAC_ARRAY_MAX       512
#define ASSOC_MAC_ARRAY_MAX    1024
#define SUPPORTED_STANDARDS_RADIO2_4GHZ "b,g,n"
#define SUPPORTED_STANDARDS_RADIO5GHZ "a,n,ac"
#define RESTORE_CNFG_FILE_NAME  "/data/.nvram_restore_cfg.txt"
#define NVRAM_LINE_MAX       (1024)

//defines for HAL version 3.0.0
#define WIFI_HAL_MAJOR_VERSION 3        /**< This is the major verion of this HAL. */
#define WIFI_HAL_MINOR_VERSION 0        /**< This is the minor verson of the HAL. */
#define WIFI_HAL_MAINTENANCE_VERSION 0  /**< This is the maintenance version of the HAL. */
#define WIFI_HAL_VERSION (WIFI_HAL_MAJOR_VERSION *1000+ WIFI_HAL_MINOR_VERSION *10+ WIFI_HAL_MAINTENANCE_VERSION)

#define MAX_NUM_TWT_SESSION  50    /**< Maximum number of TWT sessions for an AP (TODO to be defined) */
#define MAX_STA_PER_SESSION  100   /**< Maximum number of stations connected to a Broadcast TWT session (TODO to be defined) */
#define MAX_BSR 32
#define MAX_RU_ALLOCATIONS  74

//Mode 1: When a client connect or associate message is received by the AP, then the WiFi HAL lay must invoke wifi_apAssociatedDevice_callback with event_type: CONN_NEW.
#define CONN_NEW 1
//Mode 2: If the AP status for a client is connected or associated and the AP receives a client connect or associate message from this client, wifi_apAssociatedDevice_callback need to be invoked from hal layer to notify RDKB with event_type: CONN_RENEW
#define CONN_RENEW 2
//Mode 3: If the AP changes a client’s status to “disconnected” due to the AP’s client inactivity timeout (RDKB could read this timeout from wifi_getRadioClientInactivityTimout ) and then the client re-connects or associates back to same AP , then the WiFi HAL layer must invoke a wifi_apAssociatedDevice_callback with event_type: CONN_RECONN_AFTER_INACTIVITY
#define CONN_RECONN_AFTER_INACTIVITY 3

#define KI1_VER_MASK            0xf8

#define KI1_PW_KEY              0x08
#define KI1_INSTALL             0x40
#define KI1_ACK                 0x80

#define KI1_MSG1_BITS   (KI1_PW_KEY | KI1_ACK)
#define KI1_MSG3_BITS   (KI1_PW_KEY | KI1_INSTALL|KI1_ACK)

#define KI0_MIC                 0x01
#define KI0_SECURE              0x02
#define KI0_ENCR                0x10

#define KI0_MSG3_BITS   (KI0_MIC | KI0_SECURE | KI0_ENCR)
#define KI0_MSG4_BITS   (KI0_MIC | KI0_SECURE)

#define KEY_MSG_1_OF_4(msg)             \
        ((((msg)->key_info[1] & KI1_VER_MASK) == KI1_MSG1_BITS) && ((msg)->key_info[0] == 0))

#define KEY_MSG_2_OF_4(msg)             \
        ((((msg)->key_info[1] & KI1_VER_MASK) == KI1_PW_KEY) && ((msg)->key_info[0] == KI0_MIC))

#define KEY_MSG_3_OF_4(msg)             \
        ((((msg)->key_info[1] & KI1_VER_MASK) == KI1_MSG3_BITS) && ((msg)->key_info[0] == KI0_MSG3_BITS))

#define KEY_MSG_4_OF_4(msg)             \
        ((((msg)->key_info[1] & KI1_VER_MASK) == KI1_PW_KEY) && ((msg)->key_info[0] == KI0_MSG4_BITS))


/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
typedef unsigned char   mac_address_t[6];
typedef char            mac_addr_str_t[18];

typedef mac_address_t   bssid_t;
typedef char            ssid_t[32];
typedef UINT    wifi_radio_index_t;
typedef unsigned int u_int32_t;

typedef char            nas_id_t[49];
typedef unsigned char   r0r1_key_t[16];
typedef char            r0r1_key_str_t[33];

typedef char	wifi_interface_name_t[32];
typedef char	wifi_vap_name_t[64];

typedef struct {
    bssid_t        bssid;
    ssid_t         ssid;
    int            rssi; 
    unsigned short caps;
    unsigned int   beacon_int;
    unsigned int   freq;
    unsigned char  ie[256];
    size_t         ie_len;
}__attribute__((packed)) wifi_bss_info_t;

typedef enum {
    wifi_ip_family_ipv4,
    wifi_ip_family_ipv6
} wifi_ip_family_t;

typedef struct {
    wifi_ip_family_t family;
    union { /* network byte ordered */
        UINT   IPv4addr;           /* 32-bit IPv4 address */
        UCHAR  IPv6addr[16];       /* 128-bit IPv6 address */
    } u;
}__attribute__((packed)) ip_addr_t;

typedef enum {
    WIFI_HAL_DISABLE = 0,
    WIFI_HAL_ENABLE = 1,
} eWifiEnable;

/**
 * @brief Wifi hal version
 */
typedef struct {
    UINT    major;
    UINT    minor;
}__attribute__((packed)) wifi_hal_version_t;

/**
 * @brief Wifi Frequency Band Types
 */
typedef enum{
    WIFI_FREQUENCY_2_4_BAND = 0x1,
    WIFI_FREQUENCY_5_BAND   = 0x2,
    WIFI_FREQUENCY_5L_BAND  = 0x4,
    WIFI_FREQUENCY_5H_BAND  = 0x8,
    WIFI_FREQUENCY_6_BAND   = 0x10,
    WIFI_FREQUENCY_60_BAND  = 0x20
} wifi_freq_bands_t;

#define MAX_NUM_FREQ_BAND 4

/**
 * @brief Wifi Channel Bandwidth Types
 */
typedef enum{
    WIFI_CHANNELBANDWIDTH_20MHZ = 0x1,
    WIFI_CHANNELBANDWIDTH_40MHZ = 0x2,
    WIFI_CHANNELBANDWIDTH_80MHZ = 0x4,
    WIFI_CHANNELBANDWIDTH_160MHZ = 0x8,
    WIFI_CHANNELBANDWIDTH_80_80MHZ = 0x10
} wifi_channelBandwidth_t;

typedef struct {
    INT channel;
    wifi_freq_bands_t   band;
}__attribute__((packed)) wifi_channel_t;

#define MAX_CHANNELS    64

/**
 * @brief Channel list
 */
typedef struct {
    INT num_channels;                  /**< The number of available channels in channels_list. */
    INT channels_list[MAX_CHANNELS];   /**< List of channels. */
}__attribute__((packed)) wifi_channels_list_t;

/**
 * @brief Wifi 802.11 variant Types
 */
typedef enum {
    WIFI_80211_VARIANT_A = 0x01,
    WIFI_80211_VARIANT_B = 0x02,
    WIFI_80211_VARIANT_G = 0x04,
    WIFI_80211_VARIANT_N = 0x08,
    WIFI_80211_VARIANT_H = 0x10,
    WIFI_80211_VARIANT_AC = 0x20,
    WIFI_80211_VARIANT_AD = 0x40,
    WIFI_80211_VARIANT_AX = 0x80
} wifi_ieee80211Variant_t;

#define MAXNUMBEROFTRANSMIPOWERSUPPORTED 21

/**
 * @brief Radio transmit power supported list
 */
typedef struct {
    UINT transmitPowerSupported[MAXNUMBEROFTRANSMIPOWERSUPPORTED]; /**< List of transmit power supported. */
    UINT numberOfElements;                                         /**< The number of valid elements in transmitPowerSupported. */
}__attribute__((packed)) wifi_radio_trasmitPowerSupported_list_t;

/**
 * @brief Wifi supported bitrates
 */
typedef enum {
    WIFI_BITRATE_DEFAULT = 0x0001,      /* WIFI_BITRATE_DEFAULT is used in the set api to default the bitrate configuration */
    WIFI_BITRATE_1MBPS   = 0x0002,
    WIFI_BITRATE_2MBPS   = 0x0004,
    WIFI_BITRATE_5_5MBPS = 0x0008,
    WIFI_BITRATE_6MBPS   = 0x0010,
    WIFI_BITRATE_9MBPS   = 0x0020,
    WIFI_BITRATE_11MBPS  = 0x0040,
    WIFI_BITRATE_12MBPS  = 0x0080,
    WIFI_BITRATE_18MBPS  = 0x0100,
    WIFI_BITRATE_24MBPS  = 0x0200,
    WIFI_BITRATE_36MBPS  = 0x0400,
    WIFI_BITRATE_48MBPS  = 0x0800,
    WIFI_BITRATE_54MBPS  = 0x1000
} wifi_bitrate_t;

#ifdef WIFI_HAL_RSN_SELECTOR
#undef WIFI_HAL_RSN_SELECTOR
#endif
#define WIFI_HAL_RSN_SELECTOR(a, b, c, d) \
   ((((unsigned int) (a)) << 24) | (((unsigned int) (b)) << 16) | (((unsigned int) (c)) << 8) | \
   (unsigned int) (d))

#define WIFI_HAL_RSN_CIPHER_SUITE_NONE WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 0)
#define WIFI_HAL_RSN_CIPHER_SUITE_TKIP WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 2)
#if 0
#define WIFI_HAL_RSN_CIPHER_SUITE_WRAP WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 3)
#endif
#define WIFI_HAL_RSN_CIPHER_SUITE_CCMP WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 4)
#define WIFI_HAL_RSN_CIPHER_SUITE_AES_128_CMAC WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 6)
#define WIFI_HAL_RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 7)
#define WIFI_HAL_RSN_CIPHER_SUITE_GCMP WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 8)
#define WIFI_HAL_RSN_CIPHER_SUITE_GCMP_256 WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 9)
#define WIFI_HAL_RSN_CIPHER_SUITE_CCMP_256 WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 10)
#define WIFI_HAL_RSN_CIPHER_SUITE_BIP_GMAC_128 WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 11)
#define WIFI_HAL_RSN_CIPHER_SUITE_BIP_GMAC_256 WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 12)
#define WIFI_HAL_RSN_CIPHER_SUITE_BIP_CMAC_256 WIFI_HAL_RSN_SELECTOR(0x00, 0x0f, 0xac, 13)

#define WIFI_CIPHER_CAPA_ENC_WEP40          0x00000001
#define WIFI_CIPHER_CAPA_ENC_WEP104         0x00000002
#define WIFI_CIPHER_CAPA_ENC_TKIP           0x00000004
#define WIFI_CIPHER_CAPA_ENC_CCMP           0x00000008
#define WIFI_CIPHER_CAPA_ENC_WEP128         0x00000010
#define WIFI_CIPHER_CAPA_ENC_GCMP           0x00000020
#define WIFI_CIPHER_CAPA_ENC_GCMP_256       0x00000040
#define WIFI_CIPHER_CAPA_ENC_CCMP_256       0x00000080
#define WIFI_CIPHER_CAPA_ENC_BIP            0x00000100
#define WIFI_CIPHER_CAPA_ENC_BIP_GMAC_128   0x00000200
#define WIFI_CIPHER_CAPA_ENC_BIP_GMAC_256   0x00000400
#define WIFI_CIPHER_CAPA_ENC_BIP_CMAC_256   0x00000800
#define WIFI_CIPHER_CAPA_ENC_GTK_NOT_USED   0x00001000

typedef enum {
    wifi_countrycode_AC, /**< ASCENSION ISLAND */
    wifi_countrycode_AD, /**< ANDORRA */
    wifi_countrycode_AE, /**< UNITED ARAB EMIRATES */
    wifi_countrycode_AF, /**< AFGHANISTAN */
    wifi_countrycode_AG, /**< ANTIGUA AND BARBUDA */
    wifi_countrycode_AI, /**< ANGUILLA */
    wifi_countrycode_AL, /**< ALBANIA */
    wifi_countrycode_AM, /**< ARMENIA */
    wifi_countrycode_AN, /**< NETHERLANDS ANTILLES */
    wifi_countrycode_AO, /**< ANGOLA */
    wifi_countrycode_AQ, /**< ANTARCTICA */
    wifi_countrycode_AR, /**< ARGENTINA */
    wifi_countrycode_AS, /**< AMERICAN SAMOA */
    wifi_countrycode_AT, /**< AUSTRIA */
    wifi_countrycode_AU, /**< AUSTRALIA */
    wifi_countrycode_AW, /**< ARUBA */
    wifi_countrycode_AZ, /**< AZERBAIJAN */    
    wifi_countrycode_BA, /**< BOSNIA AND HERZEGOVINA */
    wifi_countrycode_BB, /**< BARBADOS */
    wifi_countrycode_BD, /**< BANGLADESH */
    wifi_countrycode_BE, /**< BELGIUM */
    wifi_countrycode_BF, /**< BURKINA FASO */
    wifi_countrycode_BG, /**< BULGARIA */
    wifi_countrycode_BH, /**< BAHRAIN */
    wifi_countrycode_BI, /**< BURUNDI */
    wifi_countrycode_BJ, /**< BENIN */
    wifi_countrycode_BM, /**< BERMUDA */
    wifi_countrycode_BN, /**< BRUNEI DARUSSALAM */
    wifi_countrycode_BO, /**< BOLIVIA */
    wifi_countrycode_BR, /**< BRAZIL */
    wifi_countrycode_BS, /**< BAHAMAS */
    wifi_countrycode_BT, /**< BHUTAN */
    wifi_countrycode_BV, /**< BOUVET ISLAND */
    wifi_countrycode_BW, /**< BOTSWANA */
    wifi_countrycode_BY, /**< BELARUS */
    wifi_countrycode_BZ, /**< BELIZE */
    wifi_countrycode_CA, /**< CANADA */
    wifi_countrycode_CC, /**< COCOS (KEELING) ISLANDS */
    wifi_countrycode_CD, /**< CONGO, THE DEMOCRATIC REPUBLIC OF THE */
    wifi_countrycode_CF, /**< CENTRAL AFRICAN REPUBLIC */
    wifi_countrycode_CG, /**< CONGO */
    wifi_countrycode_CH, /**< SWITZERLAND */
    wifi_countrycode_CI, /**< COTE D'IVOIRE */
    wifi_countrycode_CK, /**< COOK ISLANDS */
    wifi_countrycode_CL, /**< CHILE */
    wifi_countrycode_CM, /**< CAMEROON */
    wifi_countrycode_CN, /**< CHINA */
    wifi_countrycode_CO, /**< COLOMBIA */
    wifi_countrycode_CP, /**< CLIPPERTON ISLAND */
    wifi_countrycode_CR, /**< COSTA RICA */
    wifi_countrycode_CU, /**< CUBA */
    wifi_countrycode_CV, /**< CAPE VERDE */
    wifi_countrycode_CY, /**< CYPRUS */
    wifi_countrycode_CX, /**< CHRISTMAS ISLAND */
    wifi_countrycode_CZ, /**< CZECH REPUBLIC */
    wifi_countrycode_DE, /**< GERMANY */
    wifi_countrycode_DJ, /**< DJIBOUTI */
    wifi_countrycode_DK, /**< DENMARK */
    wifi_countrycode_DM, /**< DOMINICA */
    wifi_countrycode_DO, /**< DOMINICAN REPUBLIC */
    wifi_countrycode_DZ, /**< ALGERIA */
    wifi_countrycode_EC, /**< ECUADOR */
    wifi_countrycode_EE, /**< ESTONIA */
    wifi_countrycode_EG, /**< EGYPT */
    wifi_countrycode_EH, /**< WESTERN SAHARA */
    wifi_countrycode_ER, /**< ERITREA */
    wifi_countrycode_ES, /**< SPAIN */
    wifi_countrycode_ET, /**< ETHIOPIA */
    wifi_countrycode_FI, /**< FINLAND */
    wifi_countrycode_FJ, /**< FIJI */
    wifi_countrycode_FK, /**< FALKLAND ISLANDS (MALVINAS) */
    wifi_countrycode_FM, /**< MICRONESIA, FEDERATED STATES OF */
    wifi_countrycode_FO, /**< FAROE ISLANDS */
    wifi_countrycode_FR, /**< FRANCE */
    wifi_countrycode_GA, /**< GABON */
    wifi_countrycode_GB, /**< UNITED KINGDOM */
    wifi_countrycode_GD, /**< GRENADA */
    wifi_countrycode_GE, /**< GEORGIA */
    wifi_countrycode_GF, /**< FRENCH GUIANA */
    wifi_countrycode_GG, /**< GUERNSEY */
    wifi_countrycode_GH, /**< GHANA */
    wifi_countrycode_GI, /**< GIBRALTAR */
    wifi_countrycode_GL, /**< GREENLAND */    
    wifi_countrycode_GM, /**< GAMBIA */
    wifi_countrycode_GN, /**< GUINEA */
    wifi_countrycode_GP, /**< GUADELOUPE */
    wifi_countrycode_GQ, /**< EQUATORIAL GUINEA */
    wifi_countrycode_GR, /**< GREECE */
    wifi_countrycode_GS, /**< SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS */
    wifi_countrycode_GT, /**< GUATEMALA */    
    wifi_countrycode_GU, /**< GUAM */
    wifi_countrycode_GW, /**< GUINEA-BISSAU */
    wifi_countrycode_GY, /**< GUYANA */
    wifi_countrycode_HR, /**< CROATIA */
    wifi_countrycode_HT, /**< HAITI */
    wifi_countrycode_HM, /**< HEARD ISLAND AND MCDONALD ISLANDS */
    wifi_countrycode_HN, /**< HONDURAS */
    wifi_countrycode_HK, /**< HONG KONG */
    wifi_countrycode_HU, /**< HUNGARY */
    wifi_countrycode_IS, /**< ICELAND */
    wifi_countrycode_IN, /**< INDIA */
    wifi_countrycode_ID, /**< INDONESIA */
    wifi_countrycode_IR, /**< IRAN, ISLAMIC REPUBLIC OF */
    wifi_countrycode_IQ, /**< IRAQ */
    wifi_countrycode_IE, /**< IRELAND */
    wifi_countrycode_IL, /**< ISRAEL */
    wifi_countrycode_IM, /**< MAN, ISLE OF */
    wifi_countrycode_IT, /**< ITALY */
    wifi_countrycode_IO, /**< BRITISH INDIAN OCEAN TERRITORY */
    wifi_countrycode_JM, /**< JAMAICA */
    wifi_countrycode_JP, /**< JAPAN */
    wifi_countrycode_JE, /**< JERSEY */
    wifi_countrycode_JO, /**< JORDAN */
    wifi_countrycode_KE, /**< KENYA */
    wifi_countrycode_KG, /**< KYRGYZSTAN */
    wifi_countrycode_KH, /**< CAMBODIA */
    wifi_countrycode_KI, /**< KIRIBATI */
    wifi_countrycode_KM, /**< COMOROS */
    wifi_countrycode_KN, /**< SAINT KITTS AND NEVIS */
    wifi_countrycode_KP, /**< KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF */
    wifi_countrycode_KR, /**< KOREA, REPUBLIC OF */
    wifi_countrycode_KW, /**< KUWAIT */
    wifi_countrycode_KY, /**< CAYMAN ISLANDS */
    wifi_countrycode_KZ, /**< KAZAKHSTAN */
    wifi_countrycode_LA, /**< LAO PEOPLE'S DEMOCRATIC REPUBLIC */
    wifi_countrycode_LB, /**< LEBANON */
    wifi_countrycode_LC, /**< SAINT LUCIA */
    wifi_countrycode_LI, /**< LIECHTENSTEIN */
    wifi_countrycode_LK, /**< SRI LANKA */
    wifi_countrycode_LR, /**< LIBERIA */
    wifi_countrycode_LS, /**< LESOTHO */
    wifi_countrycode_LT, /**< LITHUANIA */
    wifi_countrycode_LU, /**< LUXEMBOURG */
    wifi_countrycode_LV, /**< LATVIA */
    wifi_countrycode_LY, /**< LIBYAN ARAB JAMAHIRIYA */
    wifi_countrycode_MA, /**< MOROCCO */
    wifi_countrycode_MC, /**< MONACO */
    wifi_countrycode_MD, /**< MOLDOVA, REPUBLIC OF */
    wifi_countrycode_ME, /**< MONTENEGRO */
    wifi_countrycode_MG, /**< MADAGASCAR */
    wifi_countrycode_MH, /**< MARSHALL ISLANDS */
    wifi_countrycode_MK, /**< MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF */
    wifi_countrycode_ML, /**< MALI */
    wifi_countrycode_MM, /**< MYANMAR */
    wifi_countrycode_MN, /**< MONGOLIA */
    wifi_countrycode_MO, /**< MACAO */
    wifi_countrycode_MQ, /**< MARTINIQUE */
    wifi_countrycode_MR, /**< MAURITANIA */
    wifi_countrycode_MS, /**< MONTSERRAT */
    wifi_countrycode_MT, /**< MALTA */
    wifi_countrycode_MU, /**< MAURITIUS */
    wifi_countrycode_MV, /**< MALDIVES */
    wifi_countrycode_MW, /**< MALAWI */
    wifi_countrycode_MX, /**< MEXICO */
    wifi_countrycode_MY, /**< MALAYSIA */
    wifi_countrycode_MZ, /**< MOZAMBIQUE */
    wifi_countrycode_NA, /**< NAMIBIA */
    wifi_countrycode_NC, /**< NEW CALEDONIA */
    wifi_countrycode_NE, /**< NIGER */
    wifi_countrycode_NF, /**< NORFOLK ISLAND */
    wifi_countrycode_NG, /**< NIGERIA */
    wifi_countrycode_NI, /**< NICARAGUA */
    wifi_countrycode_NL, /**< NETHERLANDS */
    wifi_countrycode_NO, /**< NORWAY */
    wifi_countrycode_NP, /**< NEPAL */    
    wifi_countrycode_NR, /**< NAURU */
    wifi_countrycode_NU, /**< NIUE */    
    wifi_countrycode_NZ, /**< NEW ZEALAND */
    wifi_countrycode_MP, /**< NORTHERN MARIANA ISLANDS */
    wifi_countrycode_OM, /**< OMAN */
    wifi_countrycode_PA, /**< PANAMA */
    wifi_countrycode_PE, /**< PERU */
    wifi_countrycode_PF, /**< FRENCH POLYNESIA */
    wifi_countrycode_PG, /**< PAPUA NEW GUINEA */
    wifi_countrycode_PH, /**< PHILIPPINES */
    wifi_countrycode_PK, /**< PAKISTAN */
    wifi_countrycode_PL, /**< POLAND */
    wifi_countrycode_PM, /**< SAINT PIERRE AND MIQUELON */
    wifi_countrycode_PN, /**< PITCAIRN */
    wifi_countrycode_PR, /**< PUERTO RICO */
    wifi_countrycode_PS, /**< PALESTINIAN TERRITORY, OCCUPIED */
    wifi_countrycode_PT, /**< PORTUGAL */    
    wifi_countrycode_PW, /**< PALAU */
    wifi_countrycode_PY, /**< PARAGUAY */
    wifi_countrycode_QA, /**< QATAR */
    wifi_countrycode_RE, /**< REUNION */
    wifi_countrycode_RO, /**< ROMANIA */
    wifi_countrycode_RS, /**< SERBIA */
    wifi_countrycode_RU, /**< RUSSIAN FEDERATION */
    wifi_countrycode_RW, /**< RWANDA */
    wifi_countrycode_SA, /**< SAUDI ARABIA */
    wifi_countrycode_SB, /**< SOLOMON ISLANDS */
    wifi_countrycode_SD, /**< SUDAN */
    wifi_countrycode_SE, /**< SWEDEN */
    wifi_countrycode_SC, /**< SEYCHELLES */
    wifi_countrycode_SG, /**< SINGAPORE */
    wifi_countrycode_SH, /**< SAINT HELENA */
    wifi_countrycode_SI, /**< SLOVENIA */
    wifi_countrycode_SJ, /**< SVALBARD AND JAN MAYEN */
    wifi_countrycode_SK, /**< SLOVAKIA */
    wifi_countrycode_SL, /**< SIERRA LEONE */
    wifi_countrycode_SM, /**< SAN MARINO */
    wifi_countrycode_SN, /**< SENEGAL */
    wifi_countrycode_SO, /**< SOMALIA */
    wifi_countrycode_SR, /**< SURINAME */
    wifi_countrycode_ST, /**< SAO TOME AND PRINCIPE */
    wifi_countrycode_SV, /**< EL SALVADOR */
    wifi_countrycode_SY, /**< SYRIAN ARAB REPUBLIC */
    wifi_countrycode_SZ, /**< SWAZILAND */
    wifi_countrycode_TA, /**< TRISTAN DA CUNHA */
    wifi_countrycode_TC, /**< TURKS AND CAICOS ISLANDS */
    wifi_countrycode_TD, /**< CHAD */
    wifi_countrycode_TF, /**< FRENCH SOUTHERN TERRITORIES */
    wifi_countrycode_TG, /**< TOGO */
    wifi_countrycode_TH, /**< THAILAND */
    wifi_countrycode_TJ, /**< TAJIKISTAN */
    wifi_countrycode_TK, /**< TOKELAU */
    wifi_countrycode_TL, /**< TIMOR-LESTE (EAST TIMOR) */
    wifi_countrycode_TM, /**< TURKMENISTAN */
    wifi_countrycode_TN, /**< TUNISIA */
    wifi_countrycode_TO, /**< TONGA */
    wifi_countrycode_TR, /**< TURKEY */
    wifi_countrycode_TT, /**< TRINIDAD AND TOBAGO */
    wifi_countrycode_TV, /**< TUVALU */
    wifi_countrycode_TW, /**< TAIWAN, PROVINCE OF CHINA */
    wifi_countrycode_TZ, /**< TANZANIA, UNITED REPUBLIC OF */
    wifi_countrycode_UA, /**< UKRAINE */
    wifi_countrycode_UG, /**< UGANDA */
    wifi_countrycode_UM, /**< UNITED STATES MINOR OUTLYING ISLANDS */
    wifi_countrycode_US, /**< UNITED STATES */
    wifi_countrycode_UY, /**< URUGUAY */
    wifi_countrycode_UZ, /**< UZBEKISTAN */
    wifi_countrycode_VA, /**< HOLY SEE (VATICAN CITY STATE) */
    wifi_countrycode_VC, /**< SAINT VINCENT AND THE GRENADINES */
    wifi_countrycode_VE, /**< VENEZUELA */
    wifi_countrycode_VG, /**< VIRGIN ISLANDS, BRITISH */
    wifi_countrycode_VI, /**< VIRGIN ISLANDS, U.S. */
    wifi_countrycode_VN, /**< VIET NAM */
    wifi_countrycode_VU, /**< VANUATU */
    wifi_countrycode_WF, /**< WALLIS AND FUTUNA */
    wifi_countrycode_WS, /**< SAMOA */
    wifi_countrycode_YE, /**< YEMEN */
    wifi_countrycode_YT, /**< MAYOTTE */
    wifi_countrycode_YU, /**< YUGOSLAVIA */
    wifi_countrycode_ZA, /**< SOUTH AFRICA */
    wifi_countrycode_ZM, /**< ZAMBIA */
    wifi_countrycode_ZW, /**< ZIMBABWE */
    wifi_countrycode_max /**< Max number of country code */
} wifi_countrycode_type_t;

/**
 * @brief Wifi Radio CSI capabilities
 */
typedef struct {
    UINT maxDevices;              /**< The maximun number of stations that can be configured to collect the CSI data.  Return 0 if CSI is not supported. */
    BOOL soudingFrameSupported;   /**< The value is TRUE, if the radio supports to sending souding frames in the MAC layer. */
}__attribute__((packed)) wifi_radio_csi_capabilities_t;

#define MAXIFACENAMESIZE    64

/**
 * @brief Wifi Radio Capabilities
 */
typedef struct {
    UINT index;
    CHAR ifaceName[MAXIFACENAMESIZE];                                     /**< The interface name. */
    UINT numSupportedFreqBand;                                           /**< The Number of supported frequencies band */
    wifi_freq_bands_t band[MAX_NUM_FREQ_BAND];                           /**< The frequencies band list */
    wifi_channels_list_t channel_list[MAX_NUM_FREQ_BAND];                /**< The list of supported channels for each frequencies band supported. */
    wifi_channelBandwidth_t channelWidth[MAX_NUM_FREQ_BAND];             /**< The Channel Bandwidth supported (uses bitmask to return multiples Bandwidth) for each frequencies band supported.. */
    wifi_ieee80211Variant_t mode[MAX_NUM_FREQ_BAND];                     /**< The supported modes (uses bitmask to return multiples modes) for each frequencies band supported. */
    UINT maxBitRate[MAX_NUM_FREQ_BAND];                                 /**< The maximum PHY bit rate supported for each frequencies band supported. */
    UINT supportedBitRate[MAX_NUM_FREQ_BAND];                           /**< The supported data transmit rates in Mbps for each frequencies band supported. It uses bitmask to return multiples bitrates and wifi_bitrate_t has the definition of valid values*/
    wifi_radio_trasmitPowerSupported_list_t transmitPowerSupported_list[MAX_NUM_FREQ_BAND]; /**< List of transmit power supported for each frequencies band supported. */
    BOOL autoChannelSupported;                                          /**< The value is TRUE, if Auto Channel is supported. */
    BOOL DCSSupported;                                                  /**< The value is TRUE, if DCS is supported. */
    BOOL zeroDFSSupported;                                              /**< The value is TRUE, if Zero DFS is supported. Zero DFS (also known as Background CAC) allows Wi-Fi stack to continue operation on main channel and at the same time run background CAC.*/
    wifi_radio_csi_capabilities_t csi;                                   /**< CSI capabilities */
    UINT cipherSupported;                                                /**< The list of supported cipher (uses bitmask to return multiples values). */
    UINT numcountrySupported;                                            /**< Number of supported countries. */
    wifi_countrycode_type_t countrySupported[wifi_countrycode_max];      /**< The Supported country list. it should return the current country code on first entry. */
    UINT maxNumberVAPs;                                                  /**< Max number of VAPs */
}__attribute__((packed)) wifi_radio_capabilities_t;

/**
 * @brief Wifi interface Property info
 */
typedef struct {
    unsigned int     phy_index;           /**< actual index of the phy device */
    unsigned int     rdk_radio_index;     /**< radio index of upper layer */
    wifi_interface_name_t  interface_name;
    wifi_interface_name_t  bridge_name;
    int              vlan_id;
    BOOL             primary;
    unsigned int     index;
    wifi_vap_name_t  vap_name;
}__attribute__((packed)) wifi_interface_name_idex_map_t;

/**
 * @brief Wifi Plataform Property
 */
typedef struct {
     UINT numRadios;                               /**< Number of radios. */
     wifi_radio_capabilities_t radiocap[MAX_NUM_RADIOS]; /**< Radio capabilities */
     wifi_interface_name_idex_map_t interface_map[(MAX_NUM_RADIOS * MAX_NUM_VAP_PER_RADIO)];
}__attribute__((packed)) wifi_platform_property_t;

/**
 * @brief Wifi HAL Capabilities
 */
typedef struct {
    wifi_hal_version_t  version;            /**< The HAL version. */
    wifi_platform_property_t wifi_prop;     /**< The plataform Property that includes the number of radios and supported frequency bands. */
    BOOL BandSteeringSupported;             /**< If BandSteeringSupported is TRUE, bandsteering is support by the HAL */
}__attribute__((packed)) wifi_hal_capability_t;

/**
 * @brief Wifi TWT agreement type
 */
typedef enum {
    wifi_twt_agreement_type_individual,      /**< Set an individual TWT session. */
    wifi_twt_agreement_type_broadcast,       /**< Set a Broadcast TWT session. */
} wifi_twt_agreement_type_t;

/**
 * @brief Wifi TWT Operation
 */
typedef struct {
    BOOL    implicit;           /**< True if the TWT session is implicit, or false to be explicit*/
    BOOL    announced;          /**< True if the TWT session is announced, or false to be unannounced */
    BOOL    trigger_enabled;    /**< Enable the TWT trigger */
    UINT    flowID;             /**< Agreement identifier */
} wifi_twt_operation_t;

typedef struct {
    UINT    wakeTime_uSec;          /**< Wake time of the TWT session in microseconds */
    UINT    wakeInterval_uSec;      /**< TWT wake interval in microseconds*/
    UINT    minWakeDuration_uSec;   /**< Minimum TWT wake interval in microseconds*/
    UINT    channel;                /**< Channel of the TWT session*/
} wifi_twt_individual_params_t;

typedef struct {
    UINT    wakeDuration_uSec;      /**< Wake time of the TWT session in microseconds */
    UINT    wakeInterval_uSec;      /**< TWT wake interval in microseconds */
} wifi_twt_broadcast_params_t;

typedef struct {
    wifi_twt_agreement_type_t   agreement;          /**< Agreement of the TWT session i.e. Individual or broadcast  */
    wifi_twt_operation_t        operation;          /**< Set the operation of the TWT session */
    union {
        wifi_twt_individual_params_t    individual; /**< Set configuration for Individual TWT session */
        wifi_twt_broadcast_params_t     broadcast;  /**< Set configuration for Broadcast TWT session */
    } params;
    BOOL sessionPaused;                             /**< TRUE if the session is in pause, but it hasn't been teardown  */
} wifi_twt_params_t;

typedef struct {
    wifi_twt_params_t    twt_params;                /**< configuration of a TWT session */
} wifi_80211ax_params_t;

typedef struct {
    UINT numTwtSession;                                     /**< Number of TWT session for that device */
    wifi_twt_params_t    twtParams[MAX_NUM_TWT_SESSION];    /**< List of TWT session that device has joined */
}wifi_twt_dev_info_t;

typedef struct {
    wifi_twt_params_t twtParameters;                        /**< Configuration of the TWT session */
    INT IdTWTsession;                                       /**< ID that identify univocally a TWT session for that AP */
    mac_address_t macAddr[MAX_STA_PER_SESSION];             /**< List of MAC addresses connected to the TWT session*/
    UINT numDevicesInSession;                               /**< Number of devices connected to the TWT session */
} wifi_twt_sessions_t;

typedef enum {
    WIFI_RU_TYPE_26,
    WIFI_RU_TYPE_52,
    WIFI_RU_TYPE_106,
    WIFI_RU_TYPE_242,
    WIFI_RU_TYPE_484,
    WIFI_RU_TYPE_996,
    WIFI_RU_TYPE_2X996,
} wifi_ru_type_t;

/**
 * @brief Wifi access category (AC) type
 */
typedef enum {
    wifi_access_category_background,
    wifi_access_category_best_effort,
    wifi_access_category_video,
    wifi_access_category_voice,
} wifi_access_category_t;

typedef struct {
    wifi_access_category_t  access_category;
    UINT        queue_size;
} wifi_bsr_t;

typedef struct {
    UCHAR   subchannels;
    wifi_ru_type_t  type;
} wifi_ru_allocation_t;

typedef enum {
    WIFI_DL_MU_TYPE_NONE,
    WIFI_DL_MU_TYPE_OFDMA,
    WIFI_DL_MU_TYPE_MIMO,
    WIFI_DL_MU_TYPE_OFDMA_MIMO
} wifi_dl_mu_type_t;

typedef enum {
    WIFI_UL_MU_TYPE_NONE,
    WIFI_UL_MU_TYPE_OFDMA,
} wifi_ul_mu_type_t;

typedef struct {
    wifi_dl_mu_type_t       cli_DownlinkMuType;
    wifi_bsr_t              cli_BufferStatus[MAX_BSR];
    UCHAR                   cli_AllocatedDownlinkRuNum;
    wifi_ru_allocation_t    cli_DownlinkRuAllocations[MAX_RU_ALLOCATIONS];
} wifi_dl_mu_stats_t;

typedef struct {
    wifi_ul_mu_type_t       cli_UpinkMuType;
    UCHAR                   cli_ChannelStateInformation;
    wifi_bsr_t              cli_BufferStatus[MAX_BSR];
    UCHAR                   cli_AllocatedUplinkRuNum;
    wifi_ru_allocation_t    cli_UplinkRuAllocations[MAX_RU_ALLOCATIONS];
} wifi_ul_mu_stats_t;

typedef enum {
    WIFI_EVENT_CHANNELS_CHANGED,
    WIFI_EVENT_DFS_RADAR_DETECTED
} wifi_chan_eventType_t;

/* connection status of STA */
typedef enum {
   wifi_connection_status_disabled,
   wifi_connection_status_disconnected,
   wifi_connection_status_connected,
   wifi_connection_status_ap_not_found
} wifi_connection_status_t;


#define MAX_NR                  8
#define MAX_NC                  4
#define MAX_SUB_CARRIERS        256
#define MAX_PILOTS              26

/* RSSI in each of received streams of the received frame */
typedef INT    wifi_streams_rssi_t    [MAX_NR];
/* CSI data for each subcarrier over Nc and Nr */
typedef UINT    wifi_carrier_data_t    [MAX_NR][MAX_NC];
/* CSI data over 80MHz BW */
typedef wifi_carrier_data_t        wifi_csi_matrix_t [MAX_SUB_CARRIERS];

typedef UCHAR    wifi_evm_data_t    [MAX_NC][MAX_NR];
typedef wifi_evm_data_t    wifi_evm_matrix_t[MAX_PILOTS];

/**
 * @brief This structure hold the information about the wifi interface.
 */
typedef struct _wifi_frame_info
{
    UCHAR    bw_mode;            /* Bit 0-3: 0:20MHz; 1:40MHz; 2:80MHz; 3:160MHz */
                                /* Bit 4: 80+80MHz */
                                /* Bit 4-7: 0:11n; 1:11ac */
    UCHAR    mcs;                /* Encoded as 11ac numbering */    
    UCHAR    Nr;                    /* Number of antennas used to receive the frame */
    UCHAR    Nc;                    /* Number of streams used to transmit the frame */
    wifi_streams_rssi_t    nr_rssi;    /* RSSI on each of Nr */
    USHORT    valid_mask;            /* Bit mask that determines which regions of CSI capture (tones) are valid. One bit represents 20MHz chunk. */
    USHORT    phy_bw;                /* VAP BW at the time of capture, indicated as 20, 40, 80, 160 */
    USHORT    cap_bw;                /* Frame BW at the time of capture */
    UINT    num_sc;                /* Number of subcarriers in the payload so that information can be used in conjunction with the number of streams to fully decode valid regions */
    UCHAR    decimation;            /* Value to indicate degree to which CSI matrix is decimated in terms of number of subcarriers present.*/
    UINT    channel;            /* Primary Channel of received frame */
    ULLONG    time_stamp;            /* PHY timestamp of CSI capture with at minimum millisecond    */
                                /* resolution. Ideally this can be resolved to a standard epoch */
                                /* format with millisecond resolution. */
} wifi_frame_info_t;

/**
 * @brief This structure hold the information about the wifi interface.
 */
typedef struct _wifi_csi_data
{
    wifi_frame_info_t    frame_info;    /* as defined above */
    wifi_csi_matrix_t    csi_matrix;        /* The NC value representing the number of non-zero columns 
                                    in the H matrix is equal to the number of spatial streams in the 
                                    packet. The NR value representing the number of rows in the H matrix 
                                    is equal to the number of antennas at the receiver. 
                                    Irrespective of the NC and NR values, the output H matrix is always 
                                    of size 4x4. For example, if the frame uses 2 spatial streams 
                                    and the receiver has 3 antennas, NC=2, NR=3. 
                                    However, the H matrix will be of size 4x4 with a 3x2 sub-matrix 
                                    with non-zero values. Rest of the values of the matrix will be zero. */
    wifi_evm_matrix_t    evm_matrix;    /* Similar scheme to the CSI matrix, Nc represents the number of non-zero columns and Nr represents the number of nonzero rows. There are 16 elements to accommodate the full number of pilots in a 160 MHz capture. Each element is an EVM value for a pilot expressed in dB. */
} wifi_csi_data_t;

/**
 * @brief This structure hold the information about the wifi interface.
 */
typedef struct _wifi_associated_dev3
{
        mac_address_t cli_MACAddress;           /**< The MAC address of an associated device. */
        CHAR  cli_IPAddress[64];                /**< IP of the associated device  (deprecated, keep it empty) */
        BOOL  cli_AuthenticationState; /**< Whether an associated device has authenticated (true) or not (false). */
        UINT  cli_LastDataDownlinkRate; /**< The median PHY rate in Mbps of the most recent 16 unicast data frame transmissions from the access point to the associated device. */
        UINT  cli_LastDataUplinkRate;   /**< The median PHY rate in Mbps of the most recent 16 unicast data frame transmissions from the associated device to the access point. */
        INT   cli_SignalStrength;               /**< An indicator of radio signal strength of the uplink from the associated device to the access point, measured in dBm, as an average of the last 100 packets received from the device. */
        UINT  cli_Retransmissions;      /**< The number of packets that had to be re-transmitted, from the last 100 packets sent to the associated device. Multiple re-transmissions of the same packet count as one. */
        BOOL  cli_Active;                               /**<      boolean -       Whether or not this node is currently present in the WiFi AccessPoint network. */

        CHAR  cli_OperatingStandard[64];        /**< Radio standard the associated Wi-Fi client device is operating under. Enumeration of: */
        CHAR  cli_OperatingChannelBandwidth[64];        /**< The operating channel bandwidth of the associated device. The channel bandwidth (applicable to 802.11n and 802.11ac specifications only). Enumeration of: */
        INT   cli_SNR;          /**< A signal-to-noise ratio (SNR) compares the level of the Wi-Fi signal to the level of background noise. Sources of noise can include microwave ovens, cordless phone, bluetooth devices, wireless video cameras, wireless game controllers, fluorescent lights and more. It is measured in decibels (dB). */
        CHAR  cli_InterferenceSources[64]; /**< Wi-Fi operates in two frequency ranges (2.4 Ghz and 5 Ghz) which may become crowded other radio products which operate in the same ranges. This parameter reports the probable interference sources that this Wi-Fi access point may be observing. The value of this parameter is a comma seperated list of the following possible sources: eg: MicrowaveOven,CordlessPhone,BluetoothDevices,FluorescentLights,ContinuousWaves,Others */
        ULONG cli_DataFramesSentAck;    /**< The DataFramesSentAck parameter indicates the total number of MSDU frames marked as duplicates and non duplicates acknowledged. The value of this counter may be reset to zero when the CPE is rebooted. Refer section A.2.3.14 of CableLabs Wi-Fi MGMT Specification. */
        ULONG cli_DataFramesSentNoAck;  /**< The DataFramesSentNoAck parameter indicates the total number of MSDU frames retransmitted out of the interface (i.e., marked as duplicate and non-duplicate) and not acknowledged, but does not exclude those defined in the DataFramesLost parameter. The value of this counter may be reset to zero when the CPE is rebooted. Refer section A.2.3.14 of CableLabs Wi-Fi MGMT Specification. */
        ULONG cli_BytesSent;    /**< The total number of bytes transmitted to the client device, including framing characters. */
        ULONG cli_BytesReceived;        /**< The total number of bytes received from the client device, including framing characters. */
        INT   cli_RSSI; /**< The Received Signal Strength Indicator, RSSI, parameter is the energy observed at the antenna receiver for transmissions from the device averaged over past 100 packets recevied from the device. */
        INT   cli_MinRSSI;      /**< The Minimum Received Signal Strength Indicator, RSSI, parameter is the minimum energy observed at the antenna receiver for past transmissions (100 packets). */
        INT   cli_MaxRSSI;      /**< The Maximum Received Signal Strength Indicator, RSSI, parameter is the energy observed at the antenna receiver for past transmissions (100 packets). */
        UINT  cli_Disassociations;      /**< This parameter  represents the total number of client disassociations. Reset the parameter evey 24hrs or reboot */
        UINT  cli_AuthenticationFailures;       /**< This parameter indicates the total number of authentication failures.  Reset the parameter evey 24hrs or reboot */

        ULLONG   cli_Associations;      /**<  Stats handle used to determine reconnects; increases for every association (stat delta calcualtion) */

        ULONG cli_PacketsSent; /**< The total number of packets transmitted to the Associated Device. */
        ULONG cli_PacketsReceived; /**< The total number of packets received from the Associated Device. */
        ULONG cli_ErrorsSent; /**< The total number of outbound packets that could not be transmitted because of errors. These might be due to the number of retransmissions exceeding the retry limit, or from other causes. */
        ULONG cli_RetransCount; /**< The total number of transmitted packets which were retransmissions for each client on the vAP. Two retransmissions of the same packet results in this counter incrementing by two. Three retransmissions of the same packet results in this counter incrementing by three.... */
        ULONG cli_FailedRetransCount;  /**< The number of packets that were not transmitted successfully due to the number of retransmission attempts exceeding an 802.11 retry limit. */
        ULONG cli_RetryCount;  /**< The number of packets that were successfully transmitted after one or more retransmissions */
        ULONG cli_MultipleRetryCount; /**< The number of packets that were successfully transmitted after more than one retransmission. */

       UINT  cli_MaxDownlinkRate; /**< The Max data transmit rate in Mbps for the access point to the associated device. */
       UINT  cli_MaxUplinkRate;   /**<  The Max data transmit rate in Mbps for the associated device to the access point. */
       wifi_ul_mu_stats_t  cli_DownlinkMuStats;
       wifi_dl_mu_stats_t  cli_UplinkMuStats;
       wifi_twt_dev_info_t cli_TwtParams; /**< TWT sessions that the device has joined */

       /* To facilitate retrieval of CSI data for specific associated client, an existing RDK-B Wi-Fi HAL 
        function is being extended. In current implementation wifi_getApAssociatedDeviceDiagnosticResult3 
        retrieves variety of statistics and state specific information for associated clients. 
        The wifi_associated_dev3_t data structure is filled by native WLAN drivers for each associated client 
        as and when the function is called by RDK-B application/process. A new component structure 
        wifi_csi_data_t is being defined that is part of wifi_associated_dev3_t structure and needs to be 
        allocated and filled for specific client or list of clients when 
        wifi_getApAssociatedDeviceDiagnosticResult3 API is called by RDK-B application/process. In cases when 
        application needs CSI data, the RDK-B application will call 
        INT wifi_getApAssociatedDeviceDiagnosticResult3(INT apIndex, wifi_associated_dev3_t **associated_dev_array, UINT *output_array_size) by allocating the associated_dev_array memory for output_array_size number of client
        devices. In other words output_array_size will specify the number of client devices in the array for 
        which CSI data needs to filled by driver. The cli_MACAddress will specify the client devices in each
        of wifi_associated_dev3_t. Wi-Fi HAL implementation in such case MUST allocate memory for cli_CSIData
        fill in required fields. The called in such cases is reposnsible for deallocation of memory. 
        The wifi_csi_data_t is defined above */

         wifi_csi_data_t  *cli_CsiData; 

        UINT cli_activeNumSpatialStreams; /**< The number of active spatial streams in the session between AP and client at the moment of polling */

} wifi_associated_dev3_t;

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/**
 * @brief Get HAL Capabilities
 *
 * @param[out]  cap             HAL Capabilities
 *
 * This API will return features/configuration supported by
 * the HAL
 *
 * @return The status of the operation
 * @retval WIFI_HAL_SUCCESS if successful
 * @retval WIFI_HAL_ERROR if an generic error is detected
 * @retval WIFI_HAL_INTERNAL_ERROR if an internal error is detected
 * @retval WIFI_HAL_UNSUPPORTED if the API is not supported
 * @retval WIFI_HAL_INVALID_ARGUMENTS if any of the arguments is invalid
 * @retval WIFI_HAL_INVALID_VALUE if the value is invalid
 *
 * @execution Synchronous
 * @sideeffect None
 *
 */
INT wifi_getHalCapability(wifi_hal_capability_t *cap);

/* wifi_factoryReset() function */
/**
* @brief Clears internal variables to implement a factory reset of the Wi-Fi subsystem.
*
* A Specific implementation may dictate some functionalities since different hardware implementations
* may have different requirements.
*
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//clears internal variables to implement a factory reset of the Wi-Fi subsystem
INT wifi_factoryReset();

/* wifi_setLED() function */
/**
* @brief Set the system LED status
*
* @param radioIndex  Index of Wi-Fi Radio channel
* @param enable      LED status
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Set the system LED status
INT wifi_setLED(INT radioIndex, BOOL enable);

/**
* @brief This function call initializes all Wi-Fi radios.
*
* A specific implementation  may dictate some functionality since different hardware implementations
* may have different initilization requirements.
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
// Initializes the wifi subsystem (all radios)
INT wifi_init();

/* wifi_reset() function */
/**
* @brief Resets the Wifi subsystem.
* This includes reset of all Access Point variables.
*
* Implementation specifics may dictate what is actualy reset since different hardware
* implementations may have different requirements.
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
// resets the wifi subsystem, deletes all APs
INT wifi_reset();

/* wifi_down() function */
/**
* @brief Turns off transmit power for the entire Wifi subsystem, for all radios.
*
* Implementation specifics may dictate some functionality since
* different hardware implementations may have different requirements.
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
// turns off transmit power for the entire Wifi subsystem, for all radios
INT wifi_down();

/* wifi_createInitialConfigFiles() function */
/**
* @brief This function creates wifi configuration files.
*
* The format and content of these files are implementation dependent.  This function call is
* used to trigger this task if necessary. Some implementations may not need this
* function. If an implementation does not need to create config files the function call can
* do nothing and return RETURN_OK.
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_createInitialConfigFiles();

/* wifi_createHostApdConfig() function */
/**
* @brief Creates configuration variables needed for WPA/WPS.
*
* These variables are implementation dependent and in some implementations these variables are used by hostapd when it is started.
* Specific variables that are needed are dependent on the hostapd implementation.
* These variables are set by WPA/WPS security functions in this wifi HAL.
* If not needed for a particular implementation this function may simply return no error.
*
* @param[in] apIndex       Access Point index
* @param[in] createWpsCfg  Enable/Disable WPS Configuration creation
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_createHostApdConfig(INT apIndex, BOOL createWpsCfg);       // creates configuration variables needed for WPA/WPS.  These variables are implementation dependent and in some implementations these variables are used by hostapd when it is started.  Specific variables that are needed are dependent on the hostapd implementation. These variables are set by WPA/WPS security functions in this wifi HAL.  If not needed for a particular implementation this function may simply return no error.

/* wifi_startHostApd() function */
/**
* @brief Starts hostapd.
*
* Uses the variables in the hostapd config with format compatible with the specific hostapd implementation.
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_startHostApd();                                            // starts hostapd, uses the variables in the hostapd config with format compatible with the specific hostapd implementation

/* wifi_stopHostApd() function */
/**
* @brief Stops hostapd
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_stopHostApd();                                             // stops hostapd

/** @} */  //END OF GROUP WIFI_HAL_APIS

#ifdef __cplusplus
}
#endif

#endif

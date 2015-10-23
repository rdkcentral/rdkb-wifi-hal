#ifndef __MSO_MGMT_HAL_H__
#define __MSO_MGMT_HAL_H__

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef ULONG
#define ULONG unsigned long
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

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef enum
{
    Invalid_PWD,
    Good_PWD,
    Unique_PWD,
    Expired_PWD, 
    TimeError
}
mso_pwd_ret_status;

/* mso_validatepwd() function */
/**
* Description: Validate whether the password passed in matches the password of the day for mso user.
* Parameters : pwd:a pointer to a buffer that was preallocated by the caller. 
* 
* @return The status of the operation.
* @retval mso_pwd_ret_status
            Invalid_PWD,
            Good_PWD,
            Unique_PWD,
            Expired_PWD, 
            TimeError
*
* @execution Synchronous.
* @sideeffect None.
*/
mso_pwd_ret_status mso_validatepwd(char *pwd);

#endif


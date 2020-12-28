/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C"
{
#endif

  const char aws_root_ca_pem[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n\
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n\
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n\
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n\
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n\
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n\
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n\
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n\
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n\
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n\
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n\
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n\
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n\
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n\
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n\
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n\
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n\
rqXRfboQnoZsG4q5WTP468SQvvG5\n\
-----END CERTIFICATE-----\n"};

  const char certificate_pem_crt[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWjCCAkKgAwIBAgIVAOBBvZGOCtPw3EGnZoQ3Sw7MN9O3MA0GCSqGSIb3DQEB\n\
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n\
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDA1MDMwNjA1\n\
MDlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n\
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC5umb2z1eQt0+v0owN\n\
FOnKXsWHSeynPeZVv0n3IrPnodWZgJveMFtLz5qGI5RRBb7gszxfPk5CCkxUrTZ5\n\
5lm0UbrocMyTAa/I0xaeEiOT1G+PF8+9LMOGcW9MtDJf0EFpj0UN1FPUJ0urDlAB\n\
ZpKp5NdLbz5XaTYTwvbbxsFp92NL2ZrO07MsQT7OaBPiXKyHPjh1OWcWCxu9Q0NS\n\
/ym2+0GNGxdZtTYlMlxYMXcCFuZECsiXjRECrFobFTmkBUmZA5hdg6860ZaS0axX\n\
X7/sLHhRlsCQ9+oPPG/4KfD9zuW3S25J8dDMocZ8URXuQYOV7rs6zQEjkTRa8HA5\n\
IIQ3AgMBAAGjYDBeMB8GA1UdIwQYMBaAFGhdqfuSLlr9nwCU7K/w2ummsuXJMB0G\n\
A1UdDgQWBBSC/e5VgvcIwNCZU9HtBb6+MSsgmTAMBgNVHRMBAf8EAjAAMA4GA1Ud\n\
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEArgA7n8cGwZ971BDDOAHvOXQz\n\
vHYzjMt/zn1CjldXy55UCyTqgoTZY8nF1/1ewp1aqt9Uh56UojYi1znuk+/GVCwH\n\
H3/8VIo+Un+wzhKe8OCdrjlC8lDo29+SNabyoGiEgcRBtQVXE7mHWiGXzS1YQbNA\n\
LeYxnwlzOOJ6PiNkhYGgzvkqV/PGYguGc8T32T7FDIlhT0zHANj3J9Dsne6HaAHn\n\
UaRAEeL6zQBCXFDa8fEr/BbpM6MjzgR1bBzm3ehUSO7x0D4CJll7zk9ER1Ik0oT5\n\
/474yCnTjBksBr/5rErSYeT9uaUAmNFrr5PSv4ZxthXd4HC3rq58WVmO/dyFjw==\n\
-----END CERTIFICATE-----\n"};

  const char private_pem_key[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAubpm9s9XkLdPr9KMDRTpyl7Fh0nspz3mVb9J9yKz56HVmYCb\n\
3jBbS8+ahiOUUQW+4LM8Xz5OQgpMVK02eeZZtFG66HDMkwGvyNMWnhIjk9RvjxfP\n\
vSzDhnFvTLQyX9BBaY9FDdRT1CdLqw5QAWaSqeTXS28+V2k2E8L228bBafdjS9ma\n\
ztOzLEE+zmgT4lyshz44dTlnFgsbvUNDUv8ptvtBjRsXWbU2JTJcWDF3AhbmRArI\n\
l40RAqxaGxU5pAVJmQOYXYOvOtGWktGsV1+/7Cx4UZbAkPfqDzxv+Cnw/c7lt0tu\n\
SfHQzKHGfFEV7kGDle67Os0BI5E0WvBwOSCENwIDAQABAoIBAH5eTNZbZzoI78gy\n\
mqX/976A0ydk7gcwv7rSB5KGYyAUZdAmyGbaQhQH8hyYsr6aCTC74zTuoLKgbSUk\n\
Ia+5QonFHkYvEZJokGE09uugbeKUpT8YNXmCrpqYLeFjre6xNQCMwbBSKqNsBTki\n\
6N67GslL8gzaaPFynZ++hNYumsTsqobAw/ptIu2cxcaFNJm5lHPXMubVgFVEcNNk\n\
mciPT6A8W3IZbWnlSNIa4kNNBBDUhCfz7CAWxWxbFPDITUl99CmCYPTI92Cnr3Ww\n\
NKPaB/KfEm8PZcp1roz3teYsCs9buwC0K/qwmHYaGSspS6qUvogcdrjFDPKH2Giu\n\
huq+TRkCgYEA8utHeUdZXC7q8HWPaZ0ay6jnpUL7iO2F2skeYkGAvFA2+sZFXk5q\n\
GGJlNKzhkBJtpT5wq3gajTcaGrvK1bZnh8Y5emmFgchU2hWuc2Sdw5wy3LmEevm1\n\
uZ7134coD0ERgn+JbUGJQ68cTKswSprpFKtZ+wRMZ7HoPVBD6V+LU+sCgYEAw7q6\n\
FalMQRPPNHni5R9k2hplwveuMlRU+IZ7QKaFHVhGvnyh3F33b6HQnV2jvKAZG3j8\n\
TYUd00v6lvtR6SafqM6RFSJFpySQOIc4iArrBh7BuVIN5GsYdRM3l5/Kqg7eUPbm\n\
ZIsobyGm2N1TQORSggGXXqXYj1eUXFQOgBpFmeUCgYAhU3PvyIES64Dh0k8Ffz8w\n\
15BIFONrSqLFfDgF5NSjgSG5z7+ui3V0uPMHgfxEBrMyK1nLvGNwIjIbns3Z+fdE\n\
Ika6a4WcY354mObg/9nA/0nfDDiHooBy4cL7kpBFX3jmfVa+PXJ2baylPAsZAR2e\n\
708d594Pj9G7r6pRdwEnVwKBgGmtD3tShNE+GMmEZXS/lnwLdJXnlC2oSphEQ5eM\n\
UKKfXtLKB7orIcUr4K6WOClHZ0bl85MHJCtJAmsyFe+D4wAJR1vZvTGZFCTxHRyW\n\
iH4tbPrZypZhHDtZvNIofAuFK5MbOxld6N7XlHXSSXjnzYRTx55afKon5vpSh+Gy\n\
TZHhAoGBAJ1JNPVz3vVn1XyXTSPpdfVtWokKCw+dEK82SQ7jOnAJtog4i1xYhG/B\n\
9+MCjJW+0lglCc9QNwAExJSnzjg06mPIQUNg27XHVdOTD7cwG7vT2R20sCIZLwg1\n\
BS5NBkqE3hxIyRGVjeNGvbeqFvmWW7rX7pEvcdAtNXopJiDCfiWc\n\
-----END RSA PRIVATE KEY-----\n"};

#ifdef __cplusplus
}
#endif

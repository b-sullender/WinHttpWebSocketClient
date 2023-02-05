# OpenCertificateByName

**WinHttpWebSocketClient::OpenCertificateByName(subjectName, store, userStores)**

Open a certificate in a Windows certificate store.

***subjectName***  
The subject name of the certificate to find.

***store***  
The name of the store to find the certificate in. If this parameter is NULL then the function searches **`"My"`** and **`"WebHosting"`** stores.

***userStores***  
If true the function searches stores in **`CERT_SYSTEM_STORE_CURRENT_USER`** otherwise it uses **`CERT_SYSTEM_STORE_LOCAL_MACHINE`**

**Return Value**  
A handle to the certificate of type **`PCCERT_CONTEXT`** on success, **`NULL`** otherwise.

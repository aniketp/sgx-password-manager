#include <stdio.h>
#include <tchar.h>

#include "sgx_urts.h"	/* Is this generated? */
#include "secret.h"

#define ENCLAVE_FILE	_T("enclave.signed.dll");	/* Generated by SGX */
#define MAX_BUF_LEN		100

int main() {
	sgx_enclave_id_t	eid;
	sgx_status_t		ret = SGX_SUCCESS;
	sgx_launch_token_t	token = {0};
	
	int updated = 0;
	char buffer[MAX_BUF_LEN] = "An initial message";

	/* Create the Enclave with the above launch token */
	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token,
					&updated, &eid, NULL);

	if (ret != SGX_SUCCESS) {
		printf("App: error %#x, failed to create enclave.\n", ret);
		return (-1);
	}

	/* A bunch of privileged calls will happen, since we're inside enclave now */
	secret_function(eid, buffer, MAX_BUF_LEN);
	printf("%s\n", buffer);

	/* Destroy the enclave when all Enclave calls are finished */
	if (SGX_SUCCESS != sgx_destroy_enclave(eid))
			return (-1);

	return 0;`
}
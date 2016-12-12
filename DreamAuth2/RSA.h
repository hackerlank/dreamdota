#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

#include <openssl\rsa.h>
#include "StringManager.h"

const uint32_t RSA_SIZE = 128;

__forceinline int RSA_PublicEncrypt(const uint8_t* in, uint32_t in_size, uint8_t out[RSA_SIZE]) {
	RSA *rsa = RSA_new();
	BIGNUM *bn_n = BN_new(), *bn_e = BN_new();
	uint32_t n_bin[RSA_SIZE / 4];
	uint32_t tmp = rand();

	StringManager::DecryptorsType decryptors;
	StringManager::GetDecryptorsData()->GetData(&decryptors);
	for (uint32_t i = 0; i < RSA_SIZE / 4; ++i)
		n_bin[i] = (decryptors.decryptors[i](tmp)) ^ tmp;
	memset(&decryptors, 0, sizeof(StringManager::DecryptorsType));

	bn_n = BN_bin2bn((uint8_t*)n_bin, RSA_SIZE, bn_n);
	BN_set_word(bn_e, RSA_F4);
	rsa->n = bn_n;
	rsa->e = bn_e;
	
	int rv = RSA_public_encrypt(in_size, (uint8_t*)in, out, rsa, RSA_PKCS1_PADDING);

	RSA_free(rsa);

	return rv;
}

__forceinline int RSA_PublicDecrypt(const uint8_t* in, uint32_t in_size, uint8_t out[RSA_SIZE]) {
	RSA *rsa = RSA_new();
	BIGNUM *bn_n = BN_new(), *bn_e = BN_new();
	uint32_t n_bin[RSA_SIZE / 4];
	uint32_t tmp = rand();

	StringManager::DecryptorsType decryptors;
	StringManager::GetDecryptorsData()->GetData(&decryptors);
	for (uint32_t i = 0; i < RSA_SIZE / 4; ++i)
		n_bin[i] = (decryptors.decryptors[i](tmp)) ^ tmp;
	memset(&decryptors, 0, sizeof(StringManager::DecryptorsType));

	bn_n = BN_bin2bn((uint8_t*)n_bin, RSA_SIZE, bn_n);
	BN_set_word(bn_e, RSA_F4);
	rsa->n = bn_n;
	rsa->e = bn_e;
	
	int rv = RSA_public_decrypt(in_size, (uint8_t*)in, out, rsa, RSA_PKCS1_PADDING);

	RSA_free(rsa);

	return rv;
}

#endif
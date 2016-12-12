#ifndef INLINE_UTILS_H_INCLUDED
#define INLINE_UTILS_H_INCLUDED

namespace InlineUtils {
	inline void GetPathA(char* buffer, uint32_t buffer_size, const char* filename) {
		GetCurrentDirectoryA(buffer_size, buffer);
		strcat_s(buffer, buffer_size, "/"); 
		strcat_s(buffer, buffer_size, filename); 
	}

	inline void GetPathW(wchar_t* buffer, uint32_t buffer_size, const wchar_t* filename) {
		GetCurrentDirectoryW(buffer_size, buffer);
		wcscat_s(buffer, buffer_size, L"/"); 
		wcscat_s(buffer, buffer_size, filename); 
	}

	__forceinline void memcpy(void* src, void* dst, uint32_t size) {
		uint32_t bytes_len = size % 4;
		size -= bytes_len;
		uint32_t i;
		for (i = 0; i < size / 4; i += 4)
			*(uint32_t*)((uint32_t)dst + i) = *(uint32_t*)((uint32_t)src + i);
		for (i = 0; i < bytes_len; ++i) {
			*(uint8_t*)((uint32_t)dst + i + size) = *(uint8_t*)((uint32_t)src + i + size);
		}
	}

	//不定长参数，无法inline?
	inline uint32_t MessageBoxFormat(HWND hwnd, uint32_t flags, const wchar_t *title, const wchar_t *format, ...) {
		wchar_t buffer[256];
		va_list args;
		va_start(args, format);
		vswprintf_s(buffer, 256, format, args);
		va_end(args);

		return MessageBoxW(hwnd, buffer, title, MB_SYSTEMMODAL | flags);
	}

	extern LARGE_INTEGER CounterFrequency;

	__forceinline void Init() {
		QueryPerformanceFrequency(&CounterFrequency);
	}

	__forceinline void Cleanup() {

	}

	#define RAND_A 28657
	#define RAND_C 0
	#define RAND_M 2971215073
	__forceinline uint32_t Rand(uint32_t* seed) {
		*seed = ((*seed) * RAND_A + RAND_C) % RAND_M;
		return *seed;
	}

#define ENCRYPT_KEY_SIZE 16

#define DELTA 0x9e300000
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (k[(p&3)^e] ^ z)))

	__forceinline void XXTEAEncrypt(unsigned char *data, size_t data_size, unsigned char key[ENCRYPT_KEY_SIZE]) {
		uint32_t *v = (uint32_t *)data;
		uint32_t n = data_size / 4;
		uint32_t* k = (uint32_t*)key;
		uint32_t y, z, sum;
		unsigned p, rounds, e;
		if (n)
		{
			rounds = 6 + 52/n;
			sum = 0;
			z = v[n-1];
			do {
			sum += (DELTA + 0x779b9);
			e = (sum >> 2) & 3;
			for (p=0; p<n-1; p++) {
			  y = v[p+1]; 
			  z = v[p] += MX;
			}
			y = v[0];
			z = v[n-1] += MX;
			} while (--rounds);
		}
	}

	__forceinline void XXTEADecrypt(unsigned char *data, size_t data_size, unsigned char key[ENCRYPT_KEY_SIZE]) {
		uint32_t *v = (uint32_t *)data;
		uint32_t n = data_size / 4;
		uint32_t* k = (uint32_t*)key;
		uint32_t y, z, sum;
		unsigned p, rounds, e;
		if (n) {
			rounds = 6 + 52/n;
			sum = rounds*(DELTA + 0x779b9);
			y = v[0];
			do {
				e = (sum >> 2) & 3;
				for (p=n-1; p>0; p--) {
					z = v[p-1];
					y = v[p] -= MX;
				}
				z = v[n-1];
				y = v[0] -= MX;
			} while ((sum -= (DELTA + 0x779b9)) != 0);
		}
	}

	__forceinline void XXTEAKeyDestroy(uint8_t key[ENCRYPT_KEY_SIZE]) {
		((uint32_t*)key)[0] = (uint32_t)&key[0];
		((uint32_t*)key)[1] = (uint32_t)&key[1];
		((uint32_t*)key)[2] = (uint32_t)&key[2];
		((uint32_t*)key)[3] = (uint32_t)&key[3];		
	}

	__forceinline void GenerateKey(uint32_t seed, uint8_t* key, uint32_t keySize) {
		uint32_t i;
		memset(key, 0, keySize);
		for (i = 0; i < keySize - 4; ++i) {
			*(uint32_t*)(key + i) = Rand(&seed);
		}
	}

	__forceinline uint32_t SimpleEncrypt(uint32_t src, uint32_t key) {
		return (src ^ '+w3u') + key;
	}

	__forceinline uint32_t SimpleDecrypt(uint32_t src, uint32_t key) {
		return (src - key) ^ '+w3u'; 
	}

	__forceinline void SimpleEncryptBlock(void* ptr, uint32_t size, uint32_t key) {
	#ifdef _DEBUG
		if (size % 4)
			OutputDebugStringA("SimpleEncryptBlock: size % 4 != 0");
	#endif
		uint32_t* blocks = (uint32_t*)ptr;
		for (uint32_t i = 0; i * 4 <= size - 4; ++i) {
			blocks[i] = SimpleEncrypt(blocks[i], key);
		}
	}

	__forceinline void SimpleDecryptBlock(void* ptr, uint32_t size, uint32_t key) {
	#ifdef _DEBUG
		if (size % 4)
			OutputDebugStringA("SimpleDecryptBlock: size % 4 != 0");
	#endif
		uint32_t* blocks = (uint32_t*)ptr;
		for (uint32_t i = 0; i * 4 <= size - 4; ++i) {
			blocks[i] = SimpleDecrypt(blocks[i], key);
		}
	}

	#undef get16bits
	#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
	  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
	#define get16bits(d) (*((const uint16_t *) (d)))
	#endif

	#if !defined (get16bits)
	#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
						   +(uint32_t)(((const uint8_t *)(d))[0]) )
	#endif

	__forceinline uint32_t Hash(const char * data, int len, uint32_t hash) {
		uint32_t tmp;
		int rem;

		if (len <= 0 || data == NULL) return 0;

		rem = len & 3;
		len >>= 2;

		/* Main loop */
		for (;len > 0; len--) {
			hash  += get16bits (data);
			tmp    = (get16bits (data+2) << 11) ^ hash;
			hash   = (hash << 16) ^ tmp;
			data  += 2*sizeof (uint16_t);
			hash  += hash >> 11;
		}

		/* Handle end cases */
		switch (rem) {
			case 3: hash += get16bits (data);
					hash ^= hash << 16;
					hash ^= data[sizeof (uint16_t)] << 18;
					hash += hash >> 11;
					break;
			case 2: hash += get16bits (data);
					hash ^= hash << 11;
					hash += hash >> 17;
					break;
			case 1: hash += *data;
					hash ^= hash << 10;
					hash += hash >> 1;
		}

		/* Force "avalanching" of final 127 bits */
		hash ^= hash << 3;
		hash += hash >> 5;
		hash ^= hash << 4;
		hash += hash >> 17;
		hash ^= hash << 25;
		hash += hash >> 6;

		return hash;
	}

	__forceinline uint32_t GetUniqueId() {
		//获取CPU信息
		int data[4];
		uint32_t rv = 0;
		memset(data, 0, sizeof(data));
		for (int a = 0; a < 5; a++) {
			if (a != 3) {
				__cpuid(data,a);
				rv ^= data[0];
			}
		}
		
		//QueryPerformanceFrequency
		rv ^= CounterFrequency.LowPart;
		rv ^= CounterFrequency.HighPart;

		//获取计算机名
		bool computerNameRetrieved = false;
		DWORD len = 30;
		wchar_t* computerName = NULL;
		while (!computerNameRetrieved) {
			if (computerName != NULL)
				delete [] computerName;
			computerName = new wchar_t[len];			
			if (TRUE == GetComputerNameW(computerName, &len)) {
				computerNameRetrieved = true;
			} else {
				if (GetLastError() != ERROR_BUFFER_OVERFLOW)
					break;
			}
		}
		if (computerNameRetrieved)
			rv ^= Hash((char*)computerName, sizeof(wchar_t) * len, NULL); 
		if (computerName)
			delete [] computerName;

		return rv;
	}
}

#endif